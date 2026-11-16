#include "clock.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_sntp.h"

static const char *TAG = "clock";

/* Asia/Jerusalem: DST starts last Friday of March 02:00, ends last Sunday
 * of October 02:00. */
#define TZ_ISRAEL   "IST-2IDT,M3.4.4/2,M10.5.0/2"

/* Any time before this is the unsynced epoch (1970). */
#define EPOCH_VALID 1700000000

static volatile bool s_synced = false;

static void sync_cb(struct timeval *tv)
{
    s_synced = true;

    time_t now = tv->tv_sec;
    struct tm tm;
    localtime_r(&now, &tm);
    char buf[32];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %Z", &tm);
    ESP_LOGI(TAG, "time synchronised: %s", buf);
}

esp_err_t clock_init(void)
{
    setenv("TZ", TZ_ISRAEL, 1);
    tzset();

    esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_setservername(1, "time.google.com");
    esp_sntp_setservername(2, "il.pool.ntp.org");
    esp_sntp_set_time_sync_notification_cb(sync_cb);
    esp_sntp_init();

    ESP_LOGI(TAG, "SNTP started, timezone Asia/Jerusalem");
    return ESP_OK;
}

bool clock_is_synced(void)
{
    return s_synced || time(NULL) >= EPOCH_VALID;
}

bool clock_get_local(struct tm *out)
{
    time_t now = time(NULL);
    if (now < EPOCH_VALID) {
        return false;
    }
    localtime_r(&now, out);
    return true;
}

void clock_format(char *buf, size_t len, const char *fmt)
{
    struct tm tm;
    if (!clock_get_local(&tm)) {
        snprintf(buf, len, "not synced");
        return;
    }
    strftime(buf, len, fmt, &tm);
}
