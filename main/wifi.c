#include "wifi.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_mac.h"
#include "esp_check.h"
#include "storage.h"

static const char *TAG = "wifi";

#define WIFI_FILE   STORAGE_BASE_PATH "/wifi.txt"

#define BIT_CONNECTED   BIT0

#define WIFI_MAX_NETWORKS   8
#define WIFI_SCAN_MAX       32
#define WIFI_RETRIES_SAME   3
#define WIFI_CONNECT_MS     15000

typedef struct {
    char ssid[33];
    char pass[65];
} wifi_cred_t;

static EventGroupHandle_t s_events;
static TaskHandle_t s_task;
static esp_netif_t *s_netif;
static char s_ip[16] = "0.0.0.0";
static char s_ssid[33] = "";

static wifi_cred_t s_nets[WIFI_MAX_NETWORKS];
static int s_net_count = 0;
static int s_current = -1;
/* Networks that just failed repeatedly; skipped until a link succeeds. */
static uint32_t s_skip_mask = 0;

/* Bump when the default list changes, so an old file is replaced. */
#define CONFIG_VERSION "# v2"

static const char *DEFAULT_CONFIG =
    CONFIG_VERSION "\n"
    "# WiFi credentials (2.4 GHz only). One block per network:\n"
    "#   ssid=NAME\n"
    "#   pass=PASSWORD\n"
    "# The device scans and joins the configured network with the best signal.\n"
    "\n"
    "ssid=YOUR_SSID\n"
    "pass=YOUR_PASSWORD\n"
    "\n"
    "# Add more networks like this:\n"
    "# ssid=AnotherNetwork\n"
    "# pass=AnotherPassword\n";

/* ------------------------------------------------------------------ */
/* Configuration file                                                  */
/* ------------------------------------------------------------------ */

static void load_config(void)
{
    static char text[1024];
    s_net_count = 0;
    s_current = -1;

    if (storage_read(WIFI_FILE, text, sizeof(text)) > 0) {
        char *line = text;
        while (line != NULL && *line) {
            char *nl = strchr(line, '\n');
            if (nl != NULL) {
                *nl = '\0';
            }

            char *s = line;
            while (*s && isspace((unsigned char)*s)) {
                s++;
            }
            char *end = s + strlen(s);
            while (end > s && isspace((unsigned char)end[-1])) {
                *--end = '\0';
            }

            if (strncmp(s, "ssid=", 5) == 0) {
                if (s_net_count < WIFI_MAX_NETWORKS) {
                    wifi_cred_t *n = &s_nets[s_net_count++];
                    memset(n, 0, sizeof(*n));
                    strlcpy(n->ssid, s + 5, sizeof(n->ssid));
                }
            } else if (strncmp(s, "pass=", 5) == 0 && s_net_count > 0) {
                strlcpy(s_nets[s_net_count - 1].pass, s + 5,
                        sizeof(s_nets[0].pass));
            }

            line = (nl != NULL) ? nl + 1 : NULL;
        }
    }

    /* Drop entries without an SSID. */
    int w = 0;
    for (int i = 0; i < s_net_count; i++) {
        if (s_nets[i].ssid[0] != '\0') {
            s_nets[w++] = s_nets[i];
        }
    }
    s_net_count = w;

    ESP_LOGI(TAG, "%d configured network(s):", s_net_count);
    for (int i = 0; i < s_net_count; i++) {
        ESP_LOGI(TAG, "  %d: \"%s\"%s", i + 1, s_nets[i].ssid,
                 s_nets[i].pass[0] ? "" : " (open)");
    }
}

/* ------------------------------------------------------------------ */
/* Choosing a network                                                  */
/* ------------------------------------------------------------------ */

/*
 * Scan for access points and return the configured network with the
 * strongest signal.  Falls back to the first configured entry when the
 * scan fails or none of the names is in range.
 */
static int pick_best_network(void)
{
    if (s_net_count == 0) {
        return -1;
    }
    if (s_net_count == 1) {
        return 0;
    }

    wifi_scan_config_t sc = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = false,
        .scan_type = WIFI_SCAN_TYPE_ACTIVE,
    };

    esp_err_t err = esp_wifi_scan_start(&sc, true);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "scan failed: %s", esp_err_to_name(err));
        return 0;
    }

    wifi_ap_record_t *recs = calloc(WIFI_SCAN_MAX, sizeof(*recs));
    if (recs == NULL) {
        return 0;
    }

    uint16_t num = WIFI_SCAN_MAX;
    esp_wifi_scan_get_ap_records(&num, recs);

    /* If every configured network is marked bad, start over. */
    uint32_t allowed = 0;
    for (int n = 0; n < s_net_count; n++) {
        allowed |= (1u << n);
    }
    if ((s_skip_mask & allowed) == allowed) {
        s_skip_mask = 0;
    }

    int best = -1;
    int best_rssi = -128;

    for (int i = 0; i < num; i++) {
        for (int n = 0; n < s_net_count; n++) {
            if ((s_skip_mask & (1u << n)) != 0) {
                continue;
            }
            if (strcmp((const char *)recs[i].ssid, s_nets[n].ssid) == 0 &&
                recs[i].rssi > best_rssi) {
                best = n;
                best_rssi = recs[i].rssi;
            }
        }
        ESP_LOGD(TAG, "  ap \"%s\" %d dBm", (const char *)recs[i].ssid,
                 recs[i].rssi);
    }
    free(recs);

    if (best < 0) {
        ESP_LOGW(TAG, "none of the configured networks is in range");
        /* Try the first entry anyway (it may be hidden). */
        for (int n = 0; n < s_net_count; n++) {
            if ((s_skip_mask & (1u << n)) == 0) {
                return n;
            }
        }
        return 0;
    }

    ESP_LOGI(TAG, "best network: \"%s\" (%d dBm)", s_nets[best].ssid, best_rssi);
    return best;
}

static esp_err_t connect_to(int idx)
{
    if (idx < 0 || idx >= s_net_count) {
        return ESP_ERR_INVALID_ARG;
    }

    wifi_config_t wc = { 0 };
    strlcpy((char *)wc.sta.ssid, s_nets[idx].ssid, sizeof(wc.sta.ssid));
    strlcpy((char *)wc.sta.password, s_nets[idx].pass, sizeof(wc.sta.password));
    wc.sta.threshold.authmode = s_nets[idx].pass[0] ? WIFI_AUTH_WPA2_PSK
                                                    : WIFI_AUTH_OPEN;

    s_current = idx;
    strlcpy(s_ssid, s_nets[idx].ssid, sizeof(s_ssid));
    xEventGroupClearBits(s_events, BIT_CONNECTED);

    esp_wifi_disconnect();
    ESP_RETURN_ON_ERROR(esp_wifi_set_config(WIFI_IF_STA, &wc), TAG, "set config");
    return esp_wifi_connect();
}

/* ------------------------------------------------------------------ */
/* Events + connection manager                                         */
/* ------------------------------------------------------------------ */

static void event_handler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    if (base == WIFI_EVENT && id == WIFI_EVENT_STA_START) {
        if (s_task != NULL) {
            xTaskNotifyGive(s_task);
        }
    } else if (base == WIFI_EVENT && id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_event_sta_disconnected_t *ev = (wifi_event_sta_disconnected_t *)data;
        xEventGroupClearBits(s_events, BIT_CONNECTED);
        strlcpy(s_ip, "0.0.0.0", sizeof(s_ip));
        ESP_LOGW(TAG, "disconnected (reason %d)", ev->reason);
        if (s_task != NULL) {
            xTaskNotifyGive(s_task);
        }
    } else if (base == IP_EVENT && id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *ev = (ip_event_got_ip_t *)data;
        snprintf(s_ip, sizeof(s_ip), IPSTR, IP2STR(&ev->ip_info.ip));
        ESP_LOGI(TAG, "connected to \"%s\", ip %s", s_ssid, s_ip);
        s_skip_mask = 0;
        xEventGroupSetBits(s_events, BIT_CONNECTED);
    }
}

static void wifi_task(void *arg)
{
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        int fails = 0;
        while (!wifi_is_connected()) {
            int idx;

            if (fails < WIFI_RETRIES_SAME && s_current >= 0) {
                idx = s_current;            /* retry the same network */
            } else {
                idx = pick_best_network();  /* rescan after failures */
            }

            if (idx < 0) {
                ESP_LOGE(TAG, "no network configured in %s", WIFI_FILE);
                vTaskDelay(pdMS_TO_TICKS(30000));
                continue;
            }

            ESP_LOGI(TAG, "connecting to \"%s\"", s_nets[idx].ssid);
            if (connect_to(idx) != ESP_OK) {
                ESP_LOGW(TAG, "connect request failed");
            }

            EventBits_t bits = xEventGroupWaitBits(s_events, BIT_CONNECTED,
                                                   pdFALSE, pdFALSE,
                                                   pdMS_TO_TICKS(WIFI_CONNECT_MS));
            if (bits & BIT_CONNECTED) {
                fails = 0;
                break;
            }

            fails++;
            if (fails >= WIFI_RETRIES_SAME) {
                fails = 0;
                if (s_current >= 0) {
                    ESP_LOGW(TAG, "giving up on \"%s\" for now",
                             s_nets[s_current].ssid);
                    s_skip_mask |= (1u << s_current);
                }
                s_current = -1;             /* force a scan next round */
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

esp_err_t wifi_init(void)
{
    static char text[1024];
    bool need_default = true;

    if (storage_read(WIFI_FILE, text, sizeof(text)) > 0 &&
        strstr(text, CONFIG_VERSION) != NULL) {
        need_default = false;
    }

    if (need_default) {
        ESP_LOGI(TAG, "writing default wifi config");
        ESP_RETURN_ON_ERROR(storage_write(WIFI_FILE, DEFAULT_CONFIG,
                                          strlen(DEFAULT_CONFIG)),
                            TAG, "write config");
    }
    load_config();

    s_events = xEventGroupCreate();
    if (s_events == NULL) {
        return ESP_ERR_NO_MEM;
    }

    ESP_RETURN_ON_ERROR(esp_netif_init(), TAG, "netif init");
    esp_err_t err = esp_event_loop_create_default();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        return err;
    }

    s_netif = esp_netif_create_default_wifi_sta();
    if (s_netif == NULL) {
        return ESP_FAIL;
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_RETURN_ON_ERROR(esp_wifi_init(&cfg), TAG, "wifi init");

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                        event_handler, NULL, NULL);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                        event_handler, NULL, NULL);

    ESP_RETURN_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), TAG, "set mode");
    esp_wifi_set_ps(WIFI_PS_NONE);

    /* Create the manager before starting, so STA_START is not missed. */
    if (xTaskCreate(wifi_task, "wifi", 4096, NULL, 4, &s_task) != pdPASS) {
        return ESP_ERR_NO_MEM;
    }

    ESP_RETURN_ON_ERROR(esp_wifi_start(), TAG, "start");
    return ESP_OK;
}

bool wifi_is_connected(void)
{
    return s_events != NULL &&
           (xEventGroupGetBits(s_events) & BIT_CONNECTED) != 0;
}

esp_err_t wifi_wait_connected(uint32_t timeout_ms)
{
    if (s_events == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    EventBits_t bits = xEventGroupWaitBits(s_events, BIT_CONNECTED,
                                           pdFALSE, pdFALSE,
                                           pdMS_TO_TICKS(timeout_ms));
    return (bits & BIT_CONNECTED) ? ESP_OK : ESP_ERR_TIMEOUT;
}

const char *wifi_get_ip(void)
{
    return s_ip;
}

int wifi_get_rssi(void)
{
    wifi_ap_record_t ap;
    if (!wifi_is_connected() || esp_wifi_sta_get_ap_info(&ap) != ESP_OK) {
        return 0;
    }
    return ap.rssi;
}

esp_err_t wifi_reconnect(void)
{
    load_config();
    s_current = -1;
    xEventGroupClearBits(s_events, BIT_CONNECTED);
    esp_wifi_disconnect();
    if (s_task != NULL) {
        xTaskNotifyGive(s_task);
    }
    return ESP_OK;
}

const char *wifi_get_ssid(void)
{
    return s_ssid;
}
