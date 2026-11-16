/*
 * Bluetooth A2DP sink (classic Bluetooth speaker).
 *
 * The ESP32-CAM acts as an A2DP sink: a phone connects to "ESP32-CAM Radio"
 * and streams SBC audio.  The decoded 44.1 kHz stereo PCM is pushed into the
 * same I2S ring buffer that the internet radio uses.
 */
#pragma once

#include <stdbool.h>
#include "esp_err.h"

typedef enum {
    BT_AUDIO_OFF = 0,
    BT_AUDIO_DISCOVERABLE,
    BT_AUDIO_CONNECTED,
    BT_AUDIO_PLAYING,
} bt_audio_state_t;

/* Initialise the classic BT controller, Bluedroid, A2DP sink and AVRCP. */
esp_err_t bt_audio_init(void);

/* Make the speaker discoverable/connectable, or disconnect and hide it. */
esp_err_t bt_audio_set_enabled(bool enabled);

bt_audio_state_t bt_audio_get_state(void);
bool bt_audio_is_connected(void);

/* Short human readable state for the display / web UI. */
const char *bt_audio_get_detail(void);

/* Remote device name ("" until a phone has paired). */
const char *bt_audio_get_remote_name(void);

/* Send AVRCP play/pause to the connected phone (best effort). */
void bt_audio_play_pause(void);
