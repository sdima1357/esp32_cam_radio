/*
 * Top-level audio mode: internet radio or Bluetooth speaker.
 *
 * Only one source is active at a time.  Switching to Bluetooth stops the
 * radio stream and makes the A2DP sink discoverable; switching back restarts
 * the last radio station.
 */
#pragma once

#include <stdbool.h>

typedef enum {
    APP_MODE_RADIO = 0,
    APP_MODE_BT,
} app_mode_t;

void app_mode_init(void);

app_mode_t app_mode_get(void);
bool app_mode_is_radio(void);
bool app_mode_is_bt(void);

void app_mode_set(app_mode_t mode);
void app_mode_toggle(void);

const char *app_mode_name(app_mode_t mode);
