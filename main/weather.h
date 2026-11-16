/*
 * Current weather for a configurable location (Open-Meteo, no API key).
 *
 * The display shows a short line such as "18\x7fC Partly cloudy".  The
 * module refreshes every 15 minutes in the background; when no data has
 * been received yet the string is "-".
 */
#pragma once

#include <stddef.h>
#include "esp_err.h"

esp_err_t weather_init(void);

/* Copy the current weather line into buf. */
void weather_get(char *buf, size_t len);
