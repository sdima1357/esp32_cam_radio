#include "audio_out.h"

#include <string.h>
#include <inttypes.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"
#include "driver/i2s_std.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_log.h"

#include "board.h"

static const char *TAG = "audio";

/* Enough to ride out WiFi/TLS hiccups without adding a lot of latency. */
#define RINGBUF_SIZE        (96 * 1024)
#define WRITE_CHUNK         (1024)
/* Start playing only once this much audio is buffered (live streams jitter). */
#define PREFILL_BYTES       (48 * 1024)
#define PREFILL_TIMEOUT_MS  2000

static i2s_chan_handle_t s_tx = NULL;
static RingbufHandle_t s_rb = NULL;
static SemaphoreHandle_t s_io_lock = NULL;
static TaskHandle_t s_task = NULL;

static volatile bool s_muted = false;
static volatile bool s_prefill = false;
static volatile uint32_t s_prefill_start = 0;
static volatile int s_volume = 10;

static volatile uint32_t s_bytes_in = 0;    /* queued by a source */
static volatile uint32_t s_bytes_out = 0;   /* written to I2S */
static volatile uint32_t s_underruns = 0;
static volatile uint32_t s_drops = 0;

static uint32_t s_rate = BOARD_AUDIO_RATE;
static uint8_t s_channels = 2;

/* ------------------------------------------------------------------ */

static void apply_volume(uint8_t *data, size_t len)
{
    int vol = s_volume;
    /*
     * Volume 0 means "monitor off" and volume 1 means "picture on, still
     * silent"; audible output starts at volume 2.
     */
    if (s_muted || vol <= 1) {
        memset(data, 0, len);
        return;
    }
    if (vol >= 100) {
        return;
    }

    int32_t gain = (int32_t)((vol * 32768) / 100);
    int16_t *s = (int16_t *)data;
    size_t n = len / sizeof(int16_t);
    for (size_t i = 0; i < n; i++) {
        s[i] = (int16_t)(((int32_t)s[i] * gain) >> 15);
    }
}

static void writer_task(void *arg)
{
    uint32_t last_log = 0;

    for (;;) {
        if (s_prefill) {
            size_t free_bytes = 0;
            vRingbufferGetInfo(s_rb, &free_bytes, NULL, NULL, NULL, NULL);
            uint32_t waited = xTaskGetTickCount() - s_prefill_start;
            if (RINGBUF_SIZE - free_bytes < PREFILL_BYTES &&
                waited < pdMS_TO_TICKS(PREFILL_TIMEOUT_MS)) {
                vTaskDelay(pdMS_TO_TICKS(10));
                continue;
            }
            s_prefill = false;
        }

        size_t size = 0;
        uint8_t *data = (uint8_t *)xRingbufferReceiveUpTo(s_rb, &size,
                                                          pdMS_TO_TICKS(100),
                                                          WRITE_CHUNK);
        if (data == NULL || size == 0) {
            /* Nothing buffered: the I2S auto-clear keeps the DAC silent. */
            s_underruns++;
            continue;
        }

        apply_volume(data, size);

        if (xSemaphoreTake(s_io_lock, pdMS_TO_TICKS(100)) == pdTRUE) {
            size_t written = 0;
            esp_err_t err = i2s_channel_write(s_tx, data, size, &written,
                                              pdMS_TO_TICKS(100));
            if (err == ESP_OK) {
                s_bytes_out += written;
            } else {
                ESP_LOGW(TAG, "i2s write: %s", esp_err_to_name(err));
            }
            xSemaphoreGive(s_io_lock);
        }
        vRingbufferReturnItem(s_rb, data);

        uint32_t now = xTaskGetTickCount();
        if (now - last_log > pdMS_TO_TICKS(5000)) {
            last_log = now;
            size_t free_bytes = 0;
            vRingbufferGetInfo(s_rb, &free_bytes, NULL, NULL, NULL, NULL);
            ESP_LOGI(TAG, "in=%" PRIu32 " out=%" PRIu32 " underruns=%" PRIu32
                          " drops=%" PRIu32 " free=%u vol=%d",
                     s_bytes_in, s_bytes_out, s_underruns, s_drops,
                     (unsigned)free_bytes, s_volume);
        }
    }
}

/* ------------------------------------------------------------------ */

esp_err_t audio_out_init(uint32_t sample_rate, uint8_t channels)
{
    if (sample_rate == 0) {
        sample_rate = BOARD_AUDIO_RATE;
    }
    if (channels != 1) {
        channels = 2;
    }

    s_rate = sample_rate;
    s_channels = channels;

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true;
    chan_cfg.dma_desc_num = 8;
    chan_cfg.dma_frame_num = 256;

    ESP_RETURN_ON_ERROR(i2s_new_channel(&chan_cfg, &s_tx, NULL), TAG, "i2s_new_channel");

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(s_rate),
        /* PCM5102A with FMT tied low expects standard (Philips) I2S. */
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT,
                                                       s_channels == 1 ? I2S_SLOT_MODE_MONO
                                                                       : I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = BOARD_I2S_BCK_GPIO,
            .ws = BOARD_I2S_WS_GPIO,
            .dout = BOARD_I2S_DOUT_GPIO,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    ESP_RETURN_ON_ERROR(i2s_channel_init_std_mode(s_tx, &std_cfg), TAG, "i2s init std");
    ESP_RETURN_ON_ERROR(i2s_channel_enable(s_tx), TAG, "i2s enable");

    s_io_lock = xSemaphoreCreateMutex();

    /*
     * Keep the 46 KB audio buffer out of internal RAM: WiFi + Bluedroid
     * need most of it.  The I2S driver copies each chunk into its own DMA
     * buffers, so a PSRAM source is fine.  Fall back to internal RAM on
     * boards without PSRAM.
     */
    s_rb = xRingbufferCreateWithCaps(RINGBUF_SIZE, RINGBUF_TYPE_BYTEBUF,
                                     MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    if (s_rb == NULL) {
        s_rb = xRingbufferCreate(RINGBUF_SIZE, RINGBUF_TYPE_BYTEBUF);
    }
    if (s_io_lock == NULL || s_rb == NULL) {
        ESP_LOGE(TAG, "out of memory");
        return ESP_ERR_NO_MEM;
    }

    /* Core 1: core 0 is busy with WiFi and the network stack. */
    xTaskCreatePinnedToCore(writer_task, "audio_out", 3072, NULL,
                            configMAX_PRIORITIES - 3, &s_task, 1);

    ESP_LOGI(TAG, "I2S out ready: %" PRIu32 " Hz, %d ch, BCK=%d WS=%d DOUT=%d",
             s_rate, s_channels, BOARD_I2S_BCK_GPIO, BOARD_I2S_WS_GPIO, BOARD_I2S_DOUT_GPIO);
    return ESP_OK;
}

esp_err_t audio_out_set_format(uint32_t sample_rate, uint8_t channels)
{
    if (sample_rate == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    if (channels != 1) {
        channels = 2;
    }
    if (sample_rate == s_rate && channels == s_channels) {
        return ESP_OK;
    }

    if (xSemaphoreTake(s_io_lock, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2s_channel_disable(s_tx);

    i2s_std_clk_config_t clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(sample_rate);
    i2s_std_slot_config_t slot_cfg =
        I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT,
                                            channels == 1 ? I2S_SLOT_MODE_MONO
                                                          : I2S_SLOT_MODE_STEREO);

    esp_err_t err = i2s_channel_reconfig_std_clock(s_tx, &clk_cfg);
    if (err == ESP_OK) {
        err = i2s_channel_reconfig_std_slot(s_tx, &slot_cfg);
    }
    i2s_channel_enable(s_tx);
    xSemaphoreGive(s_io_lock);

    if (err == ESP_OK) {
        s_rate = sample_rate;
        s_channels = channels;
        ESP_LOGI(TAG, "format -> %" PRIu32 " Hz, %d ch", s_rate, s_channels);
    } else {
        ESP_LOGE(TAG, "format change failed: %s", esp_err_to_name(err));
    }
    return err;
}

size_t audio_out_write(const void *data, size_t len, uint32_t timeout_ms)
{
    if (s_rb == NULL || data == NULL || len == 0) {
        return 0;
    }

    if (!xRingbufferSend(s_rb, data, len, pdMS_TO_TICKS(timeout_ms))) {
        s_drops++;
        return 0;
    }
    s_bytes_in += len;
    return len;
}

void audio_out_prefill(void)
{
    s_prefill_start = xTaskGetTickCount();
    s_prefill = true;
}

void audio_out_flush(void)
{
    if (s_rb == NULL) {
        return;
    }
    size_t size = 0;
    void *data = NULL;
    while ((data = xRingbufferReceiveUpTo(s_rb, &size, 0, WRITE_CHUNK)) != NULL) {
        vRingbufferReturnItem(s_rb, data);
    }
}

void audio_out_set_volume(int percent)
{
    if (percent < 0) {
        percent = 0;
    } else if (percent > 100) {
        percent = 100;
    }
    s_volume = percent;
}

int audio_out_get_volume(void)
{
    return s_volume;
}

void audio_out_set_mute(bool mute)
{
    s_muted = mute;
}

bool audio_out_is_muted(void)
{
    return s_muted;
}

uint32_t audio_out_get_rate(void)
{
    return s_rate;
}

uint8_t audio_out_get_channels(void)
{
    return s_channels;
}

void audio_out_play_tone(uint32_t freq_hz, uint32_t duration_ms)
{
    enum { FRAMES = 256 };
    int16_t buf[FRAMES * 2];
    uint32_t rate = s_rate ? s_rate : BOARD_AUDIO_RATE;
    uint32_t total = (uint64_t)rate * duration_ms / 1000;

    for (uint32_t done = 0; done < total; ) {
        uint32_t n = total - done;
        if (n > FRAMES) {
            n = FRAMES;
        }
        for (uint32_t i = 0; i < n; i++) {
            float t = (float)(done + i) / (float)rate;
            /* fade in/out to avoid clicks */
            float env = 1.0f;
            uint32_t ms = (uint32_t)((uint64_t)(done + i) * 1000 / rate);
            if (ms < 10) {
                env = ms / 10.0f;
            } else if (duration_ms > 20 && ms > duration_ms - 10) {
                env = (duration_ms - ms) / 10.0f;
            }
            int16_t v = (int16_t)(sinf(2.0f * (float)M_PI * freq_hz * t) * 9000.0f * env);
            buf[i * 2] = v;
            buf[i * 2 + 1] = v;
        }
        audio_out_write(buf, n * 4, 100);
        done += n;
    }
}
