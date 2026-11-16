#include "app_mode.h"

#include "esp_err.h"
#include "esp_log.h"

#include "audio_out.h"
#include "bt_audio.h"
#include "radio.h"
#include "stations.h"

static const char *TAG = "mode";

static volatile app_mode_t s_mode = APP_MODE_RADIO;

void app_mode_init(void)
{
    s_mode = APP_MODE_RADIO;
}

app_mode_t app_mode_get(void)
{
    return s_mode;
}

bool app_mode_is_radio(void)
{
    return s_mode == APP_MODE_RADIO;
}

bool app_mode_is_bt(void)
{
    return s_mode == APP_MODE_BT;
}

const char *app_mode_name(app_mode_t mode)
{
    return mode == APP_MODE_BT ? "Bluetooth" : "Radio";
}

void app_mode_set(app_mode_t mode)
{
    if (mode == s_mode) {
        return;
    }

    ESP_LOGI(TAG, "mode -> %s", app_mode_name(mode));

    if (mode == APP_MODE_BT) {
        /* Set the mode first so the radio task does not fight over the LED. */
        s_mode = APP_MODE_BT;
        radio_stop();
        audio_out_flush();
        esp_err_t err = bt_audio_set_enabled(true);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "BT enable failed: %s", esp_err_to_name(err));
        }
    } else {
        s_mode = APP_MODE_RADIO;
        bt_audio_set_enabled(false);
        audio_out_flush();

        int idx = radio_get_index();
        if (idx < 0 && stations_count() > 0) {
            idx = 0;
        }
        if (idx >= 0) {
            radio_play(idx);
        }
    }
}

void app_mode_toggle(void)
{
    app_mode_set(s_mode == APP_MODE_RADIO ? APP_MODE_BT : APP_MODE_RADIO);
}
