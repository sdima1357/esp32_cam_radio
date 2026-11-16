/*
 * Station list, stored in /spiffs/stations.txt so it can be edited from a
 * browser (or by replacing the file).
 *
 * Format, one station per line:
 *
 *   # comment
 *   Name|http://stream.example.com/live.mp3
 *
 * Blank lines and lines starting with '#' are ignored.  A line without '|'
 * is used as the URL and the host name becomes the station name.
 */
#pragma once

#include <stddef.h>
#include "esp_err.h"

#define STATION_MAX          40
#define STATION_NAME_LEN     48
#define STATION_URL_LEN      200

typedef struct {
    char name[STATION_NAME_LEN];
    char url[STATION_URL_LEN];
} station_t;

/* Mount independent: call after storage_init(). Creates a default list. */
esp_err_t stations_init(void);

int stations_count(void);
const station_t *stations_get(int index);

/* Re-parse the file (after an edit). */
esp_err_t stations_reload(void);

/* Replace the file contents and reload. */
esp_err_t stations_save_text(const char *text, size_t len);

const char *stations_path(void);
