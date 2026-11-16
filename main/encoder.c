#include "encoder.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "app_mode.h"
#include "board.h"
#include "audio_out.h"
#include "bt_audio.h"
#include "radio.h"

static const char *TAG = "encoder";

/* Volume change per detent (1 so every level, including 0 and 1, is reachable). */
#define ENC_VOLUME_STEP     1

/* A KY-040 detent is one full quadrature cycle = 4 valid transitions. */
#define ENC_STEPS_PER_DETENT 4

/* Flip to -1 if the direction feels reversed on your module. */
#define ENC_DIR             1

/* Ignore button bounces / repeated presses within this window. */
#define ENC_BTN_DEBOUNCE_US (200 * 1000)

/* Drop contact noise this soon after an edge in the ISR itself. */
#define ENC_BTN_GLITCH_US   (30 * 1000)

/* Hold the button longer than this to toggle the audio mode. */
#define ENC_BTN_LONG_US     (700 * 1000)

typedef enum {
    ENC_EV_ROTATE,
    ENC_EV_BUTTON,
} enc_ev_type_t;

typedef struct {
    enc_ev_type_t type;
    int delta;
} enc_ev_t;

static QueueHandle_t s_queue;
static volatile int s_prev_state;
static volatile int s_acc;
static volatile int64_t s_sw_last_edge;

/*
 * Quadrature transition table.  State = (A << 1) | B, index = (prev << 2) | cur.
 * +1 / -1 for a valid one-step move, 0 for no move or an invalid jump.
 */
static const int8_t QUAD_TABLE[16] = {
     0, -1,  1,  0,
     1,  0,  0, -1,
    -1,  0,  0,  1,
     0,  1, -1,  0,
};

static void IRAM_ATTR enc_isr(void *arg)
{
    int a = gpio_get_level(BOARD_ENC_A_GPIO);
    int b = gpio_get_level(BOARD_ENC_B_GPIO);
    int cur = (a << 1) | b;
    int idx = (s_prev_state << 2) | cur;
    s_prev_state = cur;

    int8_t d = QUAD_TABLE[idx];
    if (d == 0) {
        return;
    }

    s_acc += d;
    if (s_acc >= ENC_STEPS_PER_DETENT) {
        s_acc = 0;
        enc_ev_t ev = { .type = ENC_EV_ROTATE, .delta = ENC_DIR };
        xQueueSendFromISR(s_queue, &ev, NULL);
    } else if (s_acc <= -ENC_STEPS_PER_DETENT) {
        s_acc = 0;
        enc_ev_t ev = { .type = ENC_EV_ROTATE, .delta = -ENC_DIR };
        xQueueSendFromISR(s_queue, &ev, NULL);
    }
}

static void IRAM_ATTR sw_isr(void *arg)
{
    /*
     * The KY-040 switch bounces for a few ms.  Filter that here so the
     * queue does not fill with edges that would later look like a second
     * press once the task gets around to them.
     */
    int64_t now = esp_timer_get_time();
    if (now - s_sw_last_edge < ENC_BTN_GLITCH_US) {
        return;
    }
    s_sw_last_edge = now;

    enc_ev_t ev = { .type = ENC_EV_BUTTON, .delta = 0 };
    xQueueSendFromISR(s_queue, &ev, NULL);
}

static void short_press(void)
{
    if (app_mode_is_bt()) {
        bt_audio_play_pause();
        ESP_LOGI(TAG, "BT play/pause");
    } else {
        radio_next();
        ESP_LOGI(TAG, "next: %s", radio_get_name());
    }
}

static void long_press(void)
{
    app_mode_toggle();
    ESP_LOGI(TAG, "mode: %s", app_mode_name(app_mode_get()));
}

static void encoder_task(void *arg)
{
    enc_ev_t ev;
    int64_t last_btn = 0;
    int64_t press_start = 0;
    bool btn_armed = true;
    bool btn_down = false;

    for (;;) {
        /*
         * Track the button level here rather than in the ISR: the SW pin only
         * interrupts on the falling edge, so release is detected by polling.
         * A press is classified as short or long when the shaft is released.
         */
        bool pressed = (gpio_get_level(BOARD_ENC_SW_GPIO) == 0);

        if (!pressed && btn_down) {
            int64_t held = esp_timer_get_time() - press_start;
            btn_down = false;
            if (held >= ENC_BTN_LONG_US) {
                long_press();
            } else {
                short_press();
            }
        }

        /*
         * Re-arm the button only after it has been released.  This makes a
         * single physical press produce exactly one action even if the
         * contact bounces again while it is still held down.
         */
        if (!btn_armed && !pressed) {
            btn_armed = true;
        }

        if (xQueueReceive(s_queue, &ev, pdMS_TO_TICKS(20)) != pdTRUE) {
            continue;
        }

        if (ev.type == ENC_EV_ROTATE) {
            int vol = audio_out_get_volume() + ev.delta * ENC_VOLUME_STEP;
            if (vol < 0) {
                vol = 0;
            } else if (vol > 100) {
                vol = 100;
            }
            if (vol != audio_out_get_volume()) {
                audio_out_set_volume(vol);
                ESP_LOGI(TAG, "volume %d", vol);
            }
        } else {
            if (!btn_armed) {
                continue;
            }
            int64_t now = esp_timer_get_time();
            if (now - last_btn < ENC_BTN_DEBOUNCE_US) {
                continue;
            }
            last_btn = now;
            btn_armed = false;
            btn_down = true;
            press_start = now;
        }
    }
}

esp_err_t encoder_init(void)
{
    s_queue = xQueueCreate(16, sizeof(enc_ev_t));
    if (s_queue == NULL) {
        return ESP_ERR_NO_MEM;
    }

    /* A/B: the KY-040 board has its own 10k pull-ups. */
    gpio_config_t io = {
        .pin_bit_mask = (1ULL << BOARD_ENC_A_GPIO) | (1ULL << BOARD_ENC_B_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&io), TAG, "gpio_config A/B");

    /* SW: input-only pin, pulled up on the KY-040 board; press pulls it low. */
    gpio_config_t sw = {
        .pin_bit_mask = 1ULL << BOARD_ENC_SW_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&sw), TAG, "gpio_config SW");

    s_prev_state = (gpio_get_level(BOARD_ENC_A_GPIO) << 1) |
                   gpio_get_level(BOARD_ENC_B_GPIO);

    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "gpio_install_isr_service: %s", esp_err_to_name(err));
        return err;
    }

    ESP_RETURN_ON_ERROR(gpio_isr_handler_add(BOARD_ENC_A_GPIO, enc_isr, NULL),
                        TAG, "isr A");
    ESP_RETURN_ON_ERROR(gpio_isr_handler_add(BOARD_ENC_B_GPIO, enc_isr, NULL),
                        TAG, "isr B");
    ESP_RETURN_ON_ERROR(gpio_isr_handler_add(BOARD_ENC_SW_GPIO, sw_isr, NULL),
                        TAG, "isr SW");

    if (xTaskCreate(encoder_task, "encoder", 2560, NULL, 4, NULL) != pdPASS) {
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGI(TAG, "KY-040 ready: A=%d B=%d SW=%d (rotate=volume, press=next)",
             BOARD_ENC_A_GPIO, BOARD_ENC_B_GPIO, BOARD_ENC_SW_GPIO);
    return ESP_OK;
}
