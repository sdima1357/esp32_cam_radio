#include "status_led.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_log.h"

#include "board.h"

static const char *TAG = "led";

#define LEDC_MODE       LEDC_LOW_SPEED_MODE
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_DUTY_RES   LEDC_TIMER_8_BIT
#define LEDC_FREQ_HZ    5000

static volatile led_mode_t s_mode = LED_MODE_OFF;

static void led_set(bool on)
{
#if BOARD_LED_ACTIVE_LOW
    uint32_t duty = on ? 0 : 255;
#else
    uint32_t duty = on ? 255 : 0;
#endif
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

static void led_task(void *arg)
{
    bool on = false;

    for (;;) {
        led_mode_t mode = s_mode;
        switch (mode) {
        case LED_MODE_ON:
            led_set(true);
            vTaskDelay(pdMS_TO_TICKS(200));
            break;
        case LED_MODE_BLINK_SLOW:
            on = !on;
            led_set(on);
            vTaskDelay(pdMS_TO_TICKS(700));
            break;
        case LED_MODE_BLINK_FAST:
            on = !on;
            led_set(on);
            vTaskDelay(pdMS_TO_TICKS(120));
            break;
        case LED_MODE_OFF:
        default:
            led_set(false);
            on = false;
            vTaskDelay(pdMS_TO_TICKS(200));
            break;
        }
    }
}

void status_led_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    ledc_channel_config_t ch = {
        .gpio_num = BOARD_LED_GPIO,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ch));

    led_set(false);
    xTaskCreate(led_task, "status_led", 2048, NULL, 3, NULL);
    ESP_LOGI(TAG, "status LED on GPIO%d", BOARD_LED_GPIO);
}

void status_led_set(led_mode_t mode)
{
    s_mode = mode;
}
