/*
 * WiFi station connection.
 *
 * Credentials come from /spiffs/wifi.txt.  Several networks may be listed,
 * one "ssid="/"pass=" block each:
 *
 *   ssid=YOUR_SSID
 *   pass=YOUR_PASSWORD
 *
 *   ssid=AnotherNetwork
 *   pass=AnotherPassword
 *
 * At boot (and whenever the current link is lost) the device scans for
 * access points and joins the configured network with the strongest signal.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"

esp_err_t wifi_init(void);

bool wifi_is_connected(void);

/* Block until an IP is obtained (or timeout). Returns ESP_OK on success. */
esp_err_t wifi_wait_connected(uint32_t timeout_ms);

/* Dotted IP string, or "0.0.0.0" when not connected. */
const char *wifi_get_ip(void);

/* RSSI in dBm, 0 when not connected. */
int wifi_get_rssi(void);

/* Re-read wifi.txt and reconnect. */
esp_err_t wifi_reconnect(void);

const char *wifi_get_ssid(void);
