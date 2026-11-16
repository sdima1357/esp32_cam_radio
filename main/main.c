/*
 * ESP32-CAM AI-Thinker internet radio + Bluetooth speaker
 *
 *  - PCM5102A I2S DAC as the single audio output
 *  - Internet radio: MP3 over HTTP, station list in /spiffs/stations.txt
 *  - Bluetooth A2DP sink: a phone streams to "ESP32-CAM Radio"
 *  - ST7789 320x240 display on the camera FPC connector
 *  - KY-040 encoder: rotate = volume, short press = next / play-pause,
 *    long press = toggle radio/Bluetooth
 *  - Web UI and serial console for control without the encoder
 *
 * Only one audio source is active at a time (see app_mode.c).
 */
#include <string.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_app_desc.h"
#include "esp_ota_ops.h"
#include "nvs_flash.h"

#include "board.h"
#include "app_mode.h"
#include "audio_out.h"
#include "bt_audio.h"
#include "status_led.h"
#include "storage.h"
#include "stations.h"
#include "wifi.h"
#include "radio.h"
#include "webui.h"
#include "console.h"
#include "clock.h"
#include "encoder.h"
#include "display.h"
#include "weather.h"

static const char *TAG = "app";

static void heap_report(void)
{
    ESP_LOGI(TAG, "free heap: %" PRIu32 " bytes, largest block: %" PRIu32
                  ", PSRAM free: %u KB",
             esp_get_free_heap_size(),
             (uint32_t)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT),
             (unsigned)(heap_caps_get_free_size(MALLOC_CAP_SPIRAM) / 1024));
}

void app_main(void)
{
    const esp_app_desc_t *app = esp_app_get_description();
    const esp_partition_t *boot = esp_ota_get_running_partition();
    ESP_LOGI(TAG, "=== ESP32-CAM internet radio + Bluetooth speaker ===");
    ESP_LOGI(TAG, "firmware %s (%s %s), boot partition %s",
             app->version, app->date, app->time,
             boot != NULL ? boot->label : "?");

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    ESP_ERROR_CHECK(audio_out_init(BOARD_AUDIO_RATE, 2));
    status_led_init();

    /* Short beep: confirms the I2S DAC path without a phone. */
    audio_out_play_tone(880, 90);

    /* Configuration files + station list. */
    ESP_ERROR_CHECK(storage_init());
    ESP_ERROR_CHECK(stations_init());

    /* Network.  The web UI and the radio both need it; Bluetooth does not. */
    ESP_ERROR_CHECK(wifi_init());
    if (wifi_wait_connected(20000) == ESP_OK) {
        ESP_LOGI(TAG, "wifi up: http://%s/", wifi_get_ip());
    } else {
        ESP_LOGW(TAG, "wifi not connected yet, web ui will follow the IP");
    }
    /* Wall clock (NTP) and weather, independent of playback. */
    clock_init();
    ESP_ERROR_CHECK(weather_init());

    heap_report();

    /* Player + Bluetooth stack. */
    ESP_ERROR_CHECK(radio_init());

    /*
     * Bring the classic BT stack up once at boot so switching modes is
     * instant.  It stays non-discoverable until Bluetooth mode is selected.
     * A failure must not stop the radio.
     */
    esp_err_t berr = bt_audio_init();
    if (berr != ESP_OK) {
        ESP_LOGW(TAG, "Bluetooth init failed: %s", esp_err_to_name(berr));
    }

    app_mode_init();

    ESP_ERROR_CHECK(webui_start());
    console_init();
    ESP_ERROR_CHECK(encoder_init());

    /* Display is optional: a wiring problem must not stop the radio. */
    esp_err_t derr = display_init();
    if (derr != ESP_OK) {
        ESP_LOGW(TAG, "display init failed: %s", esp_err_to_name(derr));
    }
    heap_report();

    /*
     * A freshly uploaded OTA image boots in "pending verify".  WiFi, the web
     * UI and the display are up at this point, so confirm the image and stop
     * the bootloader from rolling back.  Harmless for a serial-flashed image.
     */
    esp_err_t oerr = esp_ota_mark_app_valid_cancel_rollback();
    if (oerr != ESP_OK) {
        ESP_LOGD(TAG, "mark valid: %s", esp_err_to_name(oerr));
    }

    ESP_LOGI(TAG, "ready: open http://%s/", wifi_get_ip());

    /* Start playing the first station right after boot. */
    if (stations_count() > 0) {
        ESP_LOGI(TAG, "autoplay: %s", stations_get(0)->name);
        radio_play(0);
    }

    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(30000));
        heap_report();
    }
}
