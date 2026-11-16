/*
 * ST7789 320x240 SPI display.
 *
 * Shows the current station, playback state, volume, WiFi and the Israel
 * clock.  The UI is rendered in small horizontal strips so no full-screen
 * frame buffer is needed (the ESP32 has to share RAM with WiFi and TLS).
 */
#pragma once

#include "esp_err.h"

/* Bring up the panel and start the UI refresh task. */
esp_err_t display_init(void);
