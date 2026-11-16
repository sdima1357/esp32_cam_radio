#include "weather.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/ip_addr.h"

#include "wifi.h"
#include "radio.h"
#include "storage.h"

static const char *TAG = "weather";

/*
 * Open-Meteo is free and needs no API key.  The location comes from
 * /spiffs/weather.txt ("city|lat|lon"); the built-in default is a neutral
 * example.  The file is optional: without it the default is used.
 *
 * The request is done with a raw socket and static buffers on purpose: an
 * esp_http_client + cJSON fetch costs a few KB of heap exactly while an
 * HTTPS radio stream is running, and that was enough to make mbedTLS fail
 * its own buffer allocation.  A socket uses the lwIP pools instead.
 */
#define WX_CITY_DEFAULT "London"
#define WX_LAT_DEFAULT  "51.5074"
#define WX_LON_DEFAULT  "-0.1278"
#define WX_HOST         "api.open-meteo.com"
#define WX_FILE         STORAGE_BASE_PATH "/weather.txt"

static char s_city[40] = WX_CITY_DEFAULT;
static char s_lat[16]  = WX_LAT_DEFAULT;
static char s_lon[16]  = WX_LON_DEFAULT;
static char s_path[128];

#define WX_FIRST_MS     (10 * 1000)
#define WX_REFRESH_MS   (15 * 60 * 1000)
#define WX_RESP_MAX     1024

/* UTF-8 degree sign; the display font maps U+00B0 to its own glyph. */
#define DEG             "\xc2\xb0"

static portMUX_TYPE s_mux = portMUX_INITIALIZER_UNLOCKED;
static char s_text[48] = "-";

static SemaphoreHandle_t s_dns_done;
static ip_addr_t s_dns_addr;
static volatile bool s_dns_ok;

static char s_resp[WX_RESP_MAX];

/* WMO weather interpretation codes used by Open-Meteo (UTF-8 Russian). */
static const char *code_text(int code)
{
    switch (code) {
    case 0:  return "Ясно";
    case 1:  return "Почти ясно";
    case 2:  return "Перем. облач.";
    case 3:  return "Пасмурно";
    case 45:
    case 48: return "Туман";
    case 51:
    case 53:
    case 55: return "Морось";
    case 56:
    case 57: return "Лед. морось";
    case 61:
    case 63:
    case 65: return "Дождь";
    case 66:
    case 67: return "Лед. дождь";
    case 71:
    case 73:
    case 75: return "Снег";
    case 77: return "Снеж. крупа";
    case 80:
    case 81:
    case 82: return "Ливень";
    case 85:
    case 86: return "Снегопад";
    case 95: return "Гроза";
    case 96:
    case 99: return "Гроза, град";
    default: return "Облачно";
    }
}

static void set_text(const char *text)
{
    taskENTER_CRITICAL(&s_mux);
    strlcpy(s_text, text, sizeof(s_text));
    taskEXIT_CRITICAL(&s_mux);
}

void weather_get(char *buf, size_t len)
{
    if (len == 0) {
        return;
    }
    taskENTER_CRITICAL(&s_mux);
    strlcpy(buf, s_text, len);
    taskEXIT_CRITICAL(&s_mux);
}

static void dns_cb(const char *name, const ip_addr_t *ip, void *arg)
{
    if (ip != NULL) {
        s_dns_addr = *ip;
        s_dns_ok = true;
    }
    xSemaphoreGive(s_dns_done);
}

static bool resolve(void)
{
    s_dns_ok = false;
    err_t err = dns_gethostbyname(WX_HOST, &s_dns_addr, dns_cb, NULL);
    if (err == ERR_INPROGRESS) {
        if (xSemaphoreTake(s_dns_done, pdMS_TO_TICKS(5000)) != pdTRUE) {
            ESP_LOGW(TAG, "dns timeout");
            return false;
        }
    } else if (err != ERR_OK) {
        ESP_LOGW(TAG, "dns error %d", (int)err);
        return false;
    }
    return s_dns_ok;
}

static bool parse(const char *body)
{
    const char *cur = strstr(body, "\"current\":{");
    if (cur == NULL) {
        return false;
    }
    const char *t = strstr(cur, "\"temperature_2m\":");
    const char *c = strstr(cur, "\"weather_code\":");
    if (t == NULL || c == NULL) {
        return false;
    }

    double temp = strtod(t + strlen("\"temperature_2m\":"), NULL);
    int code = atoi(c + strlen("\"weather_code\":"));
    int rounded = (int)(temp >= 0 ? temp + 0.5 : temp - 0.5);

    char text[48];
    snprintf(text, sizeof(text), "%d" DEG "C %s", rounded, code_text(code));
    set_text(text);
    ESP_LOGI(TAG, "%s: %d C, code %d (%s)", s_city, rounded, code,
             code_text(code));
    return true;
}

static bool fetch(void)
{
    /*
     * A TLS handshake needs a 16 KB contiguous heap block.  Do not open
     * sockets while the radio is in the middle of one.
     */
    if (radio_get_state() == RADIO_CONNECTING) {
        return false;
    }
    if (!resolve()) {
        return false;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        ESP_LOGW(TAG, "socket: %d", errno);
        return false;
    }

    struct timeval tv = { .tv_sec = 8, .tv_usec = 0 };
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    struct sockaddr_in dest = {
        .sin_family = AF_INET,
        .sin_port = htons(80),
        .sin_addr.s_addr = ip4_addr_get_u32(ip_2_ip4(&s_dns_addr)),
    };

    bool ok = false;
    if (connect(sock, (struct sockaddr *)&dest, sizeof(dest)) != 0) {
        ESP_LOGW(TAG, "connect: %d", errno);
        goto out;
    }

    char req[192];
    int req_len = snprintf(req, sizeof(req),
                           "GET %s HTTP/1.0\r\n"
                           "Host: " WX_HOST "\r\n"
                           "User-Agent: esp32-radio\r\n"
                           "Connection: close\r\n\r\n", s_path);
    if (req_len <= 0 || req_len >= (int)sizeof(req)) {
        ESP_LOGW(TAG, "request too long");
        goto out;
    }
    if (send(sock, req, req_len, 0) != req_len) {
        ESP_LOGW(TAG, "send: %d", errno);
        goto out;
    }

    int len = 0;
    while (len < (int)sizeof(s_resp) - 1) {
        int r = recv(sock, s_resp + len, sizeof(s_resp) - 1 - len, 0);
        if (r <= 0) {
            break;
        }
        len += r;
    }
    s_resp[len] = '\0';

    if (len < 16 || strncmp(s_resp, "HTTP/1.", 7) != 0) {
        ESP_LOGW(TAG, "short/invalid response (%d bytes)", len);
        goto out;
    }
    if (strncmp(s_resp + 9, "200", 3) != 0) {
        ESP_LOGW(TAG, "http status %.3s", s_resp + 9);
        goto out;
    }

    const char *body = strstr(s_resp, "\r\n\r\n");
    if (body == NULL) {
        ESP_LOGW(TAG, "no body");
        goto out;
    }
    ok = parse(body + 4);

out:
    close(sock);
    return ok;
}

static void weather_task(void *arg)
{
    vTaskDelay(pdMS_TO_TICKS(WX_FIRST_MS));

    for (;;) {
        if (!wifi_is_connected()) {
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }
        if (radio_get_state() == RADIO_CONNECTING) {
            /* Retry soon, but stay out of the TLS handshake's way. */
            vTaskDelay(pdMS_TO_TICKS(5000));
            continue;
        }
        if (!fetch()) {
            char keep[48];
            weather_get(keep, sizeof(keep));
            ESP_LOGW(TAG, "update failed, keeping \"%s\"", keep);
            vTaskDelay(pdMS_TO_TICKS(60000));
            continue;
        }
        vTaskDelay(pdMS_TO_TICKS(WX_REFRESH_MS));
    }
}

/* Optional /spiffs/weather.txt: one line "city|lat|lon". */
static void load_location(void)
{
    char text[160];
    if (storage_read(WX_FILE, text, sizeof(text)) <= 0) {
        return;
    }
    char *bar1 = strchr(text, '|');
    if (bar1 == NULL) {
        return;
    }
    char *bar2 = strchr(bar1 + 1, '|');
    if (bar2 == NULL) {
        return;
    }
    *bar1 = '\0';
    *bar2 = '\0';
    char *lon = bar2 + 1;
    char *nl = strpbrk(lon, "\r\n");
    if (nl != NULL) {
        *nl = '\0';
    }
    if (text[0] != '\0') {
        strlcpy(s_city, text, sizeof(s_city));
    }
    if (bar1[1] != '\0') {
        strlcpy(s_lat, bar1 + 1, sizeof(s_lat));
    }
    if (lon[0] != '\0') {
        strlcpy(s_lon, lon, sizeof(s_lon));
    }
}

esp_err_t weather_init(void)
{
    load_location();
    snprintf(s_path, sizeof(s_path),
             "/v1/forecast?latitude=%s&longitude=%s"
             "&current=temperature_2m,weather_code", s_lat, s_lon);

    s_dns_done = xSemaphoreCreateBinary();
    if (s_dns_done == NULL) {
        return ESP_ERR_NO_MEM;
    }
    if (xTaskCreate(weather_task, "weather", 3072, NULL, 2, NULL) != pdPASS) {
        return ESP_ERR_NO_MEM;
    }
    ESP_LOGI(TAG, "Open-Meteo for %s (%s, %s)", s_city, s_lat, s_lon);
    return ESP_OK;
}
