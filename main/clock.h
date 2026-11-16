/*
 * Wall clock: SNTP synchronisation and Israel local time.
 *
 * The timezone is Asia/Jerusalem (IST/IDT with automatic daylight saving),
 * expressed as a POSIX TZ string so newlib can apply the DST rules without a
 * full tzdata database:
 *
 *   IST-2IDT,M3.4.4/2,M10.5.0/2
 *
 * DST starts on the last Friday of March at 02:00 and ends on the last Sunday
 * of October at 02:00.
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "esp_err.h"

/* Set the timezone and start SNTP. Call once the network is up. */
esp_err_t clock_init(void);

/* True once at least one NTP reply has been applied. */
bool clock_is_synced(void);

/* Fill *out with local time. False while the clock is not set yet. */
bool clock_get_local(struct tm *out);

/* strftime into buf; writes "not synced" when the time is not available. */
void clock_format(char *buf, size_t len, const char *fmt);
