#include "display.h"

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"
#include "esp_attr.h"
#include "esp_check.h"
#include "esp_log.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_st7789.h"
#include "esp_lcd_panel_vendor.h"

#include "app_mode.h"
#include "audio_out.h"
#include "board.h"
#include "bt_audio.h"
#include "font8x16_ru.h"
#include "radio.h"
#include "clock.h"
#include "wifi.h"
#include "weather.h"

static const char *TAG = "display";

/* ---- colours (RGB565) ---- */
#define COL_BG      0x0863  /* dark neutral blue-grey */
#define COL_TEXT    0xFFFF
#define COL_GRAY    0x8410
#define COL_SEP     0x3186
#define COL_PLAY    0x07E0
#define COL_WAIT    0xFBE0  /* amber */
#define COL_ERR     0xF800  /* red */
#define COL_DATE    0x07E0  /* green */
#define COL_BT      0x07FF  /* cyan */

/* ---- backlight PWM (status LED uses timer 0 / channel 0) ---- */
#define BL_LEDC_MODE    LEDC_LOW_SPEED_MODE
#define BL_LEDC_TIMER   LEDC_TIMER_1
#define BL_LEDC_CH      LEDC_CHANNEL_1
#define BL_LEDC_RES     LEDC_TIMER_8_BIT
#define BL_LEDC_FREQ    5000

static esp_lcd_panel_io_handle_t s_io;
static esp_lcd_panel_handle_t s_panel;
static uint32_t s_draw_errors;
static SemaphoreHandle_t s_color_done;

/* One horizontal strip, reused for every band of the screen.
 * 4-byte aligned so the SPI DMA engine can read it directly (no bounce
 * buffer, which would otherwise cost several KB during TLS). */
static WORD_ALIGNED_ATTR uint16_t s_strip[BOARD_LCD_H_RES * BOARD_LCD_STRIP_ROWS];

typedef struct {
    int mode;
    int state;
    int bt_state;
    int index;
    char name[64];
    char detail[64];
    char bt_detail[64];
    char bt_remote[48];
    char date[32];
    char time[16];
    char ip[20];
    char wx[48];
} ui_snapshot_t;

/* ------------------------------------------------------------------ */
/* Backlight                                                           */
/* ------------------------------------------------------------------ */

static void backlight_set(bool on)
{
    bool high = BOARD_LCD_BL_ACTIVE_LOW ? !on : on;
    uint32_t duty = high ? 255 : 0;
    ledc_set_duty(BL_LEDC_MODE, BL_LEDC_CH, duty);
    ledc_update_duty(BL_LEDC_MODE, BL_LEDC_CH);
}

static void backlight_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = BL_LEDC_MODE,
        .duty_resolution = BL_LEDC_RES,
        .timer_num = BL_LEDC_TIMER,
        .freq_hz = BL_LEDC_FREQ,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t ch = {
        .gpio_num = BOARD_LCD_BL_GPIO,
        .speed_mode = BL_LEDC_MODE,
        .channel = BL_LEDC_CH,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = BL_LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ch));
}

/* ------------------------------------------------------------------ */
/* Strip drawing primitives                                            */
/* ------------------------------------------------------------------ */

static void strip_clear(uint16_t color)
{
    for (int i = 0; i < BOARD_LCD_H_RES * BOARD_LCD_STRIP_ROWS; i++) {
        s_strip[i] = color;
    }
}

/* Decode one UTF-8 character; returns the number of bytes consumed. */
static int utf8_decode(const char *s, uint32_t *cp)
{
    const unsigned char *p = (const unsigned char *)s;
    if (p[0] < 0x80) {
        *cp = p[0];
        return 1;
    }
    if ((p[0] & 0xE0) == 0xC0 && (p[1] & 0xC0) == 0x80) {
        *cp = ((uint32_t)(p[0] & 0x1F) << 6) | (p[1] & 0x3F);
        return 2;
    }
    if ((p[0] & 0xF0) == 0xE0 && (p[1] & 0xC0) == 0x80 &&
        (p[2] & 0xC0) == 0x80) {
        *cp = ((uint32_t)(p[0] & 0x0F) << 12) |
              ((uint32_t)(p[1] & 0x3F) << 6) | (p[2] & 0x3F);
        return 3;
    }
    *cp = '?';
    return 1;
}

/* Map a Unicode code point to a glyph index in Font8x16_Table. */
static int glyph_index(uint32_t cp)
{
    if (cp < 0x80) {
        return (int)cp;
    }
    if (cp >= 0x0410 && cp <= 0x042F) {          /* А..Я */
        return 0x80 + (int)(cp - 0x0410);
    }
    if (cp >= 0x0430 && cp <= 0x043F) {          /* а..п */
        return 0xA0 + (int)(cp - 0x0430);
    }
    if (cp >= 0x0440 && cp <= 0x044F) {          /* р..я */
        return 0xE0 + (int)(cp - 0x0440);
    }
    if (cp == 0x0401) {
        return 0x85;                             /* Ё -> Е */
    }
    if (cp == 0x0451) {
        return 0xA5;                             /* ё -> е */
    }
    if (cp == 0x00B0) {
        return 0xF8;                             /* degree sign */
    }
    return '?';
}

static int utf8_chars(const char *s)
{
    int n = 0;
    while (*s) {
        uint32_t cp;
        s += utf8_decode(s, &cp);
        n++;
    }
    return n;
}

static void strip_text(const char *text, int x, int y, int scale,
                       uint16_t color, int y0)
{
    if (scale < 1) {
        scale = 1;
    }
    if (y + FONT8X16_H * scale <= y0 ||
        y >= y0 + BOARD_LCD_STRIP_ROWS) {
        return;
    }

    int i = 0;
    while (*text) {
        uint32_t cp;
        text += utf8_decode(text, &cp);
        const uint8_t *glyph =
            &Font8x16_Table[glyph_index(cp) * FONT8X16_H];
        int gx = x + i * FONT8X16_W * scale;
        i++;

        for (int row = 0; row < FONT8X16_H; row++) {
            uint8_t bits = glyph[row];
            if (!bits) {
                continue;
            }
            int py = y + row * scale;
            if (py + scale <= y0 || py >= y0 + BOARD_LCD_STRIP_ROWS) {
                continue;
            }
            for (int col = 0; col < FONT8X16_W; col++) {
                if (!(bits & (0x80 >> col))) {
                    continue;
                }
                int px = gx + col * scale;
                for (int dy = 0; dy < scale; dy++) {
                    int sy = py + dy - y0;
                    if (sy < 0 || sy >= BOARD_LCD_STRIP_ROWS) {
                        continue;
                    }
                    uint16_t *line = &s_strip[sy * BOARD_LCD_H_RES];
                    for (int dx = 0; dx < scale; dx++) {
                        int sx = px + dx;
                        if (sx >= 0 && sx < BOARD_LCD_H_RES) {
                            line[sx] = color;
                        }
                    }
                }
            }
        }
    }
}

static int text_x_centered(const char *text, int scale)
{
    int w = utf8_chars(text) * FONT8X16_W * scale;
    int x = (BOARD_LCD_H_RES - w) / 2;
    return x < 0 ? 0 : x;
}

/* Copy at most max_chars characters, appending ".." when truncated. */
static void fit_text(char *dst, size_t dst_len, const char *src, int max_chars)
{
    int total = utf8_chars(src);
    int keep = total <= max_chars ? total : max_chars - 2;
    if (keep < 0) {
        keep = 0;
    }

    size_t out = 0;
    const char *p = src;
    for (int i = 0; i < keep && *p; i++) {
        uint32_t cp;
        int n = utf8_decode(p, &cp);
        if (out + (size_t)n >= dst_len) {
            break;
        }
        memcpy(dst + out, p, n);
        out += n;
        p += n;
    }
    if (total > max_chars && out + 2 < dst_len) {
        dst[out++] = '.';
        dst[out++] = '.';
    }
    dst[out] = '\0';
}

static uint16_t state_color(int state)
{
    switch (state) {
    case RADIO_PLAYING:
        return COL_PLAY;
    case RADIO_CONNECTING:
        return COL_WAIT;
    case RADIO_ERROR:
        return COL_ERR;
    default:
        return COL_GRAY;
    }
}

static uint16_t bt_state_color(int state)
{
    switch (state) {
    case BT_AUDIO_PLAYING:
    case BT_AUDIO_CONNECTED:
        return COL_PLAY;
    case BT_AUDIO_DISCOVERABLE:
        return COL_WAIT;
    default:
        return COL_GRAY;
    }
}

/* ------------------------------------------------------------------ */
/* UI                                                                  */
/* ------------------------------------------------------------------ */

static void render_strip(int y0, const ui_snapshot_t *s)
{
    strip_clear(COL_BG);

    /* Clock first, at 4x and without seconds (green, like the date). */
    strip_text(s->time, text_x_centered(s->time, 4), 6, 4, COL_DATE, y0);

    /* Weather at 2x. */
    char wx[48];
    fit_text(wx, sizeof(wx), s->wx[0] ? s->wx : "-", 19);
    strip_text(wx, text_x_centered(wx, 2), 78, 2, COL_TEXT, y0);

    /* Source line: station in radio mode, remote device in Bluetooth mode. */
    char label[80], shown[80];
    uint16_t color;
    const char *detail_src;

    if (s->mode == APP_MODE_BT) {
        if (s->bt_remote[0]) {
            snprintf(label, sizeof(label), "BT: %s", s->bt_remote);
        } else {
            snprintf(label, sizeof(label), "Bluetooth");
        }
        color = bt_state_color(s->bt_state);
        detail_src = s->bt_detail;
    } else {
        if (s->index >= 0) {
            snprintf(label, sizeof(label), "%d: %s", s->index + 1,
                     s->name[0] ? s->name : "Stopped");
        } else {
            snprintf(label, sizeof(label), "-: %s",
                     s->name[0] ? s->name : "Stopped");
        }
        color = state_color(s->state);
        detail_src = s->detail;
    }

    int lscale = (utf8_chars(label) <= 19) ? 2 : 1;
    fit_text(shown, sizeof(shown), label, lscale == 2 ? 19 : 39);
    strip_text(shown, text_x_centered(shown, lscale), 118, lscale,
               color, y0);

    /* Playback / Bluetooth detail. */
    char detail[48];
    fit_text(detail, sizeof(detail), detail_src, 39);
    strip_text(detail, text_x_centered(detail, 1), 156, 1, COL_TEXT, y0);

    /* Date (green, 2x) just above the network address. */
    strip_text(s->date, text_x_centered(s->date, 2), 180, 2, COL_DATE, y0);

    char ip[24];
    snprintf(ip, sizeof(ip), "IP %s", s->ip[0] ? s->ip : "-");
    strip_text(ip, text_x_centered(ip, 1), 216, 1, COL_GRAY, y0);
}

static esp_err_t draw_strip(int y0);

static void render_all(const ui_snapshot_t *s)
{
    for (int y0 = 0; y0 < BOARD_LCD_V_RES; y0 += BOARD_LCD_STRIP_ROWS) {
        render_strip(y0, s);
        esp_err_t err = draw_strip(y0);
        if (err != ESP_OK) {
            if (s_draw_errors++ < 5) {
                ESP_LOGW(TAG, "draw failed: %s", esp_err_to_name(err));
            }
            return;
        }
    }
}

/*
 * The panel IO queues the colour transfer and returns; the buffer must stay
 * intact until the callback fires.  Wait for it so one strip buffer is enough.
 */
static bool IRAM_ATTR color_done_cb(esp_lcd_panel_io_handle_t io,
                                    esp_lcd_panel_io_event_data_t *edata,
                                    void *user_ctx)
{
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(s_color_done, &woken);
    return woken == pdTRUE;
}

static esp_err_t draw_strip(int y0)
{
    esp_err_t err = esp_lcd_panel_draw_bitmap(s_panel, 0, y0,
                                              BOARD_LCD_H_RES,
                                              y0 + BOARD_LCD_STRIP_ROWS,
                                              s_strip);
    if (err == ESP_OK &&
        xSemaphoreTake(s_color_done, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }
    return err;
}

static void fill_screen(uint16_t color)
{
    for (int i = 0; i < BOARD_LCD_H_RES * BOARD_LCD_STRIP_ROWS; i++) {
        s_strip[i] = color;
    }
    for (int y0 = 0; y0 < BOARD_LCD_V_RES; y0 += BOARD_LCD_STRIP_ROWS) {
        if (draw_strip(y0) != ESP_OK) {
            return;
        }
    }
}

/* Russian weekday and month abbreviations (UTF-8). */
static const char *WD_RU[7] = { "Вс", "Пн", "Вт", "Ср", "Чт", "Пт", "Сб" };
static const char *MON_RU[12] = {
    "янв", "фев", "мар", "апр", "май", "июн",
    "июл", "авг", "сен", "окт", "ноя", "дек",
};

static void gather(ui_snapshot_t *s)
{
    memset(s, 0, sizeof(*s));
    s->mode = (int)app_mode_get();
    s->state = (int)radio_get_state();
    s->bt_state = (int)bt_audio_get_state();
    s->index = radio_get_index();
    snprintf(s->name, sizeof(s->name), "%s", radio_get_name());
    snprintf(s->detail, sizeof(s->detail), "%s", radio_get_detail());
    snprintf(s->bt_detail, sizeof(s->bt_detail), "%s", bt_audio_get_detail());
    snprintf(s->bt_remote, sizeof(s->bt_remote), "%s", bt_audio_get_remote_name());

    struct tm tm;
    if (clock_get_local(&tm) && tm.tm_wday >= 0 && tm.tm_wday < 7 &&
        tm.tm_mon >= 0 && tm.tm_mon < 12) {
        snprintf(s->date, sizeof(s->date), "%s %d %s %d",
                 WD_RU[tm.tm_wday], tm.tm_mday, MON_RU[tm.tm_mon],
                 tm.tm_year + 1900);
        snprintf(s->time, sizeof(s->time), "%02d:%02d",
                 tm.tm_hour, tm.tm_min);
    } else {
        snprintf(s->date, sizeof(s->date), "нет времени");
        snprintf(s->time, sizeof(s->time), "--:--");
    }

    snprintf(s->ip, sizeof(s->ip), "%s", wifi_get_ip());
    weather_get(s->wx, sizeof(s->wx));
}

static void display_task(void *arg)
{
    ui_snapshot_t prev, cur;
    memset(&prev, 0, sizeof(prev));
    bool bl_on = true;

    for (;;) {
        /*
         * Volume 0 switches the monitor off (and the audio layer mutes).
         * Volume 1 brings the picture back but stays silent; sound starts
         * at volume 2.
         */
        bool want_bl = audio_out_get_volume() > 0;
        if (want_bl != bl_on) {
            backlight_set(want_bl);
            bl_on = want_bl;
        }

        if (want_bl) {
            gather(&cur);
            if (memcmp(&prev, &cur, sizeof(cur)) != 0) {
                render_all(&cur);
                prev = cur;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

/* ------------------------------------------------------------------ */
/* Init                                                                */
/* ------------------------------------------------------------------ */

esp_err_t display_init(void)
{
    backlight_init();
    backlight_set(false);

    s_color_done = xSemaphoreCreateBinary();
    if (s_color_done == NULL) {
        return ESP_ERR_NO_MEM;
    }

    spi_bus_config_t bus = {
        .mosi_io_num = BOARD_LCD_MOSI_GPIO,
        .miso_io_num = -1,
        .sclk_io_num = BOARD_LCD_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = BOARD_LCD_H_RES * BOARD_LCD_STRIP_ROWS *
                           sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(SPI2_HOST, &bus, SPI_DMA_CH_AUTO),
                        TAG, "spi bus init");

    esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = BOARD_LCD_CS_GPIO,
        .dc_gpio_num = BOARD_LCD_DC_GPIO,
        .spi_mode = 0,
        .pclk_hz = BOARD_LCD_SPI_HZ,
        .trans_queue_depth = 1,
        .on_color_trans_done = color_done_cb,
        .user_ctx = NULL,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST,
                                 &io_config, &s_io),
        TAG, "panel io");

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = BOARD_LCD_RST_GPIO,
        .rgb_ele_order = BOARD_LCD_BGR ? LCD_RGB_ELEMENT_ORDER_BGR
                                       : LCD_RGB_ELEMENT_ORDER_RGB,
        /* The strip buffer holds little-endian RGB565 words. */
        .data_endian = LCD_RGB_DATA_ENDIAN_LITTLE,
        .bits_per_pixel = 16,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_st7789(s_io, &panel_config, &s_panel),
                        TAG, "panel");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel), TAG, "reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel), TAG, "init");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_invert_color(s_panel, BOARD_LCD_INVERT),
                        TAG, "invert");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_swap_xy(s_panel, BOARD_LCD_SWAP_XY),
                        TAG, "swap xy");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_mirror(s_panel, BOARD_LCD_MIRROR_X,
                                             BOARD_LCD_MIRROR_Y),
                        TAG, "mirror");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_set_gap(s_panel, BOARD_LCD_X_OFFSET,
                                              BOARD_LCD_Y_OFFSET),
                        TAG, "gap");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "disp on");

    backlight_set(true);

#if BOARD_LCD_SELFTEST
    /* Quick R/G/B flash: confirms wiring, colour order and inversion. */
    fill_screen(0xF800);
    vTaskDelay(pdMS_TO_TICKS(150));
    fill_screen(0x07E0);
    vTaskDelay(pdMS_TO_TICKS(150));
    fill_screen(0x001F);
    vTaskDelay(pdMS_TO_TICKS(150));
    fill_screen(COL_BG);
    vTaskDelay(pdMS_TO_TICKS(150));
#endif

    if (xTaskCreate(display_task, "display", 4096, NULL, 2, NULL) != pdPASS) {
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGI(TAG, "ST7789 %dx%d ready (SPI %d MHz)",
             BOARD_LCD_H_RES, BOARD_LCD_V_RES, BOARD_LCD_SPI_HZ / 1000000);
    return ESP_OK;
}
