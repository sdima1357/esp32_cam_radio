#include "console.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

#include "app_mode.h"
#include "audio_out.h"
#include "bt_audio.h"
#include "radio.h"
#include "stations.h"
#include "wifi.h"
#include "clock.h"

static const char *TAG = "console";

static void print_help(void)
{
    printf("\n--- commands ---\n"
           " p  play station 1     n  next station     b  previous\n"
           " s  stop radio         +  volume up        -  volume down\n"
           " l  list stations      w  wifi status      m  memory\n"
           " t  time and date      i  mode/BT status\n"
           " M  toggle Radio/BT    B  BT play/pause\n"
           " h  help\n"
           "----------------\n");
}

static void print_stations(void)
{
    printf("\n%d station(s):\n", stations_count());
    for (int i = 0; i < stations_count(); i++) {
        const station_t *st = stations_get(i);
        printf(" %2d. %-24s %s\n", i + 1, st->name, st->url);
    }
}

static void print_wifi(void)
{
    printf("wifi: %s, ip %s, rssi %d dBm\n",
           wifi_is_connected() ? "connected" : "down", wifi_get_ip(), wifi_get_rssi());
}

static void handle(uint8_t c)
{
    switch (c) {
    case 'p':
        if (app_mode_is_bt()) {
            app_mode_set(APP_MODE_RADIO);
        }
        radio_play(0);
        printf("play: %s\n", radio_get_name());
        break;
    case 'n':
        if (app_mode_is_bt()) {
            app_mode_set(APP_MODE_RADIO);
        }
        radio_next();
        printf("play: %s\n", radio_get_name());
        break;
    case 'b':
        if (app_mode_is_bt()) {
            app_mode_set(APP_MODE_RADIO);
        }
        radio_prev();
        printf("play: %s\n", radio_get_name());
        break;
    case 's':
        radio_stop();
        printf("stopped\n");
        break;
    case 'M':
        app_mode_toggle();
        printf("mode: %s\n", app_mode_name(app_mode_get()));
        break;
    case 'B':
        bt_audio_play_pause();
        printf("BT play/pause\n");
        break;
    case 'i':
        printf("mode: %s\n", app_mode_name(app_mode_get()));
        printf("radio: state %d, station %d \"%s\", %s\n",
               (int)radio_get_state(), radio_get_index() + 1,
               radio_get_name(), radio_get_detail());
        printf("bt: %s, remote \"%s\"\n",
               bt_audio_get_detail(), bt_audio_get_remote_name());
        break;
    case '+': {
        int v = audio_out_get_volume() + 10;
        audio_out_set_volume(v);
        printf("volume %d\n", audio_out_get_volume());
        break;
    }
    case '-': {
        int v = audio_out_get_volume() - 10;
        audio_out_set_volume(v);
        printf("volume %d\n", audio_out_get_volume());
        break;
    }
    case 'l':
        print_stations();
        break;
    case 'w':
        print_wifi();
        break;
    case 't': {
        char buf[48];
        clock_format(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %Z");
        printf("time: %s (%s)\n", buf, clock_is_synced() ? "synced" : "not synced");
        break;
    }
    case 'm':
        printf("heap: %u bytes free, largest %u\n",
               (unsigned)esp_get_free_heap_size(),
               (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
        break;
    case 'h':
    case '?':
        print_help();
        break;
    default:
        break;
    }
}

static void console_task(void *arg)
{
    uint8_t c;
    for (;;) {
        if (uart_read_bytes(UART_NUM_0, &c, 1, portMAX_DELAY) == 1) {
            handle(c);
        }
    }
}

esp_err_t console_init(void)
{
    esp_err_t err = uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGW(TAG, "uart driver: %s", esp_err_to_name(err));
        return err;
    }
    xTaskCreate(console_task, "console", 2560, NULL, 3, NULL);
    ESP_LOGI(TAG, "serial console ready (send 'h' for help)");
    return ESP_OK;
}
