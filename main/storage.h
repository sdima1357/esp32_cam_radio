/*
 * SPIFFS storage for the user editable configuration files.
 *
 * Everything lives in the "storage" partition and is mounted at /spiffs:
 *   /spiffs/stations.txt   station list
 *   /spiffs/wifi.txt       network credentials
 */
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

#define STORAGE_BASE_PATH   "/spiffs"

esp_err_t storage_init(void);

bool storage_exists(const char *path);

/* Read a whole text file into buf (NUL terminated). Returns bytes read or -1. */
int storage_read(const char *path, char *buf, size_t size);

/* Create or overwrite a file. */
esp_err_t storage_write(const char *path, const char *data, size_t len);

/* Write the file only if it does not exist yet. */
esp_err_t storage_write_default(const char *path, const char *data);
