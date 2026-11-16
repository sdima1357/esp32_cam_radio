/*
 * Small web UI: station list, playback control, volume and the station
 * list editor.  Served on port 80 once WiFi is up.
 */
#pragma once

#include "esp_err.h"

esp_err_t webui_start(void);
