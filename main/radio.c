#include "radio.h"

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_heap_caps.h"

#include "mp3dec.h"

#include "app_mode.h"
#include "audio_out.h"
#include "stations.h"
#include "wifi.h"
#include "status_led.h"

static const char *TAG = "radio";

#define IN_BUF_SIZE     4096
#define PCM_SAMPLES_MAX (1152 * 2)
#define TASK_STACK      7168
#define TASK_PRIO       5

static volatile int s_want = -1;    /* requested station, -1 = stopped */
static volatile int s_index = -1;   /* station being streamed */
/* Bumped on every play request so that pressing play on the station that is
 * already streaming (e.g. after editing its URL) reconnects. */
static volatile uint32_t s_generation = 0;
static volatile radio_state_t s_state = RADIO_STOPPED;
static volatile uint32_t s_bitrate = 0;
static volatile uint32_t s_rate = 0;

static char s_detail[80] = "idle";
static SemaphoreHandle_t s_detail_lock;
static HMP3Decoder s_decoder;
static uint32_t s_decode_errors;

static uint8_t s_in[IN_BUF_SIZE];
static short s_pcm[PCM_SAMPLES_MAX];

/* ------------------------------------------------------------------ */

static void set_detail(const char *fmt, ...)
{
    char buf[sizeof(s_detail)];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    if (xSemaphoreTake(s_detail_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
        strlcpy(s_detail, buf, sizeof(s_detail));
        xSemaphoreGive(s_detail_lock);
    }
}

static void set_state(radio_state_t st)
{
    s_state = st;

    /* In Bluetooth mode the BT stack owns the status LED. */
    if (!app_mode_is_radio()) {
        return;
    }

    switch (st) {
    case RADIO_PLAYING:
        status_led_set(LED_MODE_ON);
        break;
    case RADIO_CONNECTING:
        status_led_set(LED_MODE_BLINK_FAST);
        break;
    case RADIO_ERROR:
        status_led_set(LED_MODE_BLINK_SLOW);
        break;
    default:
        status_led_set(LED_MODE_OFF);
        break;
    }
}

/* ------------------------------------------------------------------ */
/* MP3 decoding                                                        */
/* ------------------------------------------------------------------ */

/*
 * Decode as much as possible from s_in[0..*fill).  Keeps the trailing
 * partial frame in the buffer for the next read.
 */
static void decode_buffer(int *fill, bool *got_frame)
{
    int offset = 0;

    while (*fill - offset >= 4) {
        int sync = MP3FindSyncWord(s_in + offset, *fill - offset);
        if (sync < 0) {
            /* No frame start here: keep the last 3 bytes (partial sync). */
            offset = (*fill - offset > 3) ? *fill - 3 : offset;
            break;
        }
        offset += sync;

        unsigned char *in = s_in + offset;
        int left = *fill - offset;
        int err = MP3Decode(s_decoder, &in, &left, s_pcm, 0);

        if (err == ERR_MP3_INDATA_UNDERFLOW) {
            break;                      /* need more data */
        }
        if (err != ERR_MP3_NONE) {
            if (s_decode_errors < 100000) {
                s_decode_errors++;
            }
            ESP_LOGD(TAG, "mp3 decode error %d, resync", err);
            offset++;                   /* skip a byte and look again */
            continue;
        }

        offset = (int)(in - s_in);

        MP3FrameInfo info;
        MP3GetLastFrameInfo(s_decoder, &info);
        if (info.outputSamps > 0) {
            s_bitrate = info.bitrate;
            s_rate = info.samprate;
            audio_out_set_format(info.samprate, info.nChans);
            audio_out_write(s_pcm, info.outputSamps * sizeof(short), 200);
            *got_frame = true;
        }
    }

    if (offset > 0) {
        memmove(s_in, s_in + offset, *fill - offset);
        *fill -= offset;
    }
}

/* ------------------------------------------------------------------ */
/* Streaming                                                           */
/* ------------------------------------------------------------------ */

static bool station_changed(int index, uint32_t generation)
{
    return s_want != index || s_generation != generation;
}

static void stream_station(int index, const char *url, uint32_t generation)
{
    esp_http_client_config_t cfg = {
        .url = url,
        .timeout_ms = 12000,
        .buffer_size = 1024,
        .buffer_size_tx = 512,
        .keep_alive_enable = false,
        .disable_auto_redirect = false,
    };
    if (strncmp(url, "https://", 8) == 0) {
        /* Validate the server against the built-in CA bundle. */
        cfg.crt_bundle_attach = esp_crt_bundle_attach;
    }

    esp_http_client_handle_t client = esp_http_client_init(&cfg);
    if (client == NULL) {
        set_detail("out of memory");
        set_state(RADIO_ERROR);
        return;
    }

    esp_http_client_set_header(client, "Icy-MetaData", "0");
    esp_http_client_set_header(client, "User-Agent", "ESP32-Radio/1.0");

    ESP_LOGI(TAG, "opening %s", url);
    set_detail("connecting...");
    set_state(RADIO_CONNECTING);

    /*
     * esp_http_client only follows redirects inside esp_http_client_perform().
     * This code uses open/read for streaming, so handle 3xx here.  Some
     * stations (e.g. SRG SSR) answer with a temporary redirect to the actual
     * stream server.
     */
    int status = 0;
    int64_t content_len = 0;
    for (int hop = 0; ; hop++) {
        esp_err_t err = esp_http_client_open(client, 0);
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "connect failed: %s", esp_err_to_name(err));
            set_detail("connect failed (%s)", esp_err_to_name(err));
            set_state(RADIO_ERROR);
            esp_http_client_cleanup(client);
            return;
        }

        esp_http_client_fetch_headers(client);
        status = esp_http_client_get_status_code(client);
        content_len = esp_http_client_get_content_length(client);
        ESP_LOGI(TAG, "http %d, content-length %lld, heap %" PRIu32,
                 status, (long long)content_len, esp_get_free_heap_size());

        bool redirect = status == 301 || status == 302 || status == 303 ||
                        status == 307 || status == 308;
        if (!redirect) {
            break;
        }
        if (hop >= 5) {
            ESP_LOGW(TAG, "too many redirects");
            set_detail("redirect loop");
            set_state(RADIO_ERROR);
            esp_http_client_close(client);
            esp_http_client_cleanup(client);
            return;
        }
        esp_http_client_close(client);
        if (esp_http_client_set_redirection(client) != ESP_OK) {
            ESP_LOGW(TAG, "redirect %d without a usable Location", status);
            set_detail("bad redirect");
            set_state(RADIO_ERROR);
            esp_http_client_cleanup(client);
            return;
        }
        ESP_LOGI(TAG, "redirect %d, following", status);
        set_detail("redirect...");
    }

    if (status != 200) {
        set_detail("http %d", status);
        set_state(RADIO_ERROR);
        esp_http_client_close(client);
        esp_http_client_cleanup(client);
        return;
    }

    audio_out_flush();
    audio_out_prefill();
    set_state(RADIO_PLAYING);

    int fill = 0;
    uint64_t total = 0;
    uint32_t no_sync_bytes = 0;
    bool got_frame = false;
    uint32_t last_log = 0;

    while (!station_changed(index, generation)) {
        if (fill == IN_BUF_SIZE) {
            /* Decoder could not consume anything: drop the buffer. */
            ESP_LOGW(TAG, "input buffer full, dropping");
            fill = 0;
        }

        /* Small reads keep the PCM ring buffer evenly topped up. */
        int want = IN_BUF_SIZE - fill;
        if (want > 512) {
            want = 512;
        }
        int n = esp_http_client_read(client, (char *)s_in + fill, want);
        if (n <= 0) {
            ESP_LOGW(TAG, "read returned %d (errno %d)", n, esp_http_client_get_errno(client));
            set_detail(n == 0 ? "stream ended" : "read error");
            set_state(RADIO_ERROR);
            break;
        }

        fill += n;
        total += n;

        int before = fill;
        decode_buffer(&fill, &got_frame);
        if (!got_frame) {
            no_sync_bytes += (uint32_t)(before - fill);
            if (no_sync_bytes > 200000) {
                ESP_LOGW(TAG, "no MP3 frames found, wrong stream format?");
                set_detail("not an MP3 stream");
                set_state(RADIO_ERROR);
                break;
            }
        } else {
            no_sync_bytes = 0;
        }

        uint32_t now = xTaskGetTickCount();
        if (now - last_log > pdMS_TO_TICKS(10000)) {
            last_log = now;
            ESP_LOGI(TAG, "streaming: %llu bytes in, %" PRIu32 " kbps, %" PRIu32 " Hz, errors %" PRIu32 ", heap %" PRIu32 ", stack %u",
                     (unsigned long long)total, s_bitrate / 1000, s_rate,
                     s_decode_errors, esp_get_free_heap_size(),
                     (unsigned)uxTaskGetStackHighWaterMark(NULL));
            if (s_state == RADIO_PLAYING) {
                set_detail("playing %" PRIu32 " kbps %" PRIu32 " Hz", s_bitrate / 1000, s_rate);
            }
        }
    }

    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}

/* ------------------------------------------------------------------ */

static void radio_task(void *arg)
{
    int fails = 0;

    for (;;) {
        int want = s_want;
        uint32_t generation = s_generation;

        if (want < 0) {
            fails = 0;

            /* Radio is idle: release the decoder while nothing plays. */
            if (s_decoder != NULL) {
                MP3FreeDecoder(s_decoder);
                s_decoder = NULL;
                ESP_LOGI(TAG, "decoder released, heap %" PRIu32, esp_get_free_heap_size());
            }
            if (s_want < 0) {
                set_state(RADIO_STOPPED);
            }
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        const station_t *st = stations_get(want);
        if (st == NULL) {
            ESP_LOGW(TAG, "station %d does not exist", want);
            s_want = -1;
            set_state(RADIO_ERROR);
            set_detail("no such station");
            continue;
        }

        if (s_decoder == NULL) {
            s_decoder = MP3InitDecoder();
            if (s_decoder == NULL) {
                ESP_LOGE(TAG, "MP3InitDecoder failed, heap %" PRIu32, esp_get_free_heap_size());
                set_detail("out of memory");
                set_state(RADIO_ERROR);
                s_want = -1;
                continue;
            }
        }

        if (!wifi_is_connected()) {
            set_state(RADIO_CONNECTING);
            set_detail("waiting for wifi");
            if (wifi_wait_connected(20000) != ESP_OK) {
                set_detail("no wifi");
                set_state(RADIO_ERROR);
                vTaskDelay(pdMS_TO_TICKS(2000));
                continue;
            }
        }

        s_index = want;
        ESP_LOGI(TAG, "play %d: %s", want, st->name);

        stream_station(want, st->url, generation);

        if (s_want != want || s_generation != generation) {
            fails = 0;
            continue;                   /* user moved on */
        }

        fails++;
        if (fails > 5) {
            ESP_LOGW(TAG, "too many failures, stopping");
            s_want = -1;
            set_state(RADIO_ERROR);
            set_detail("stopped after errors");
            continue;
        }

        ESP_LOGW(TAG, "reconnecting in %d ms (attempt %d)", fails > 2 ? 5000 : 1500, fails);
        set_detail("reconnecting (%d)", fails);
        vTaskDelay(pdMS_TO_TICKS(fails > 2 ? 5000 : 1500));
    }
}

/* ------------------------------------------------------------------ */

esp_err_t radio_init(void)
{
    s_detail_lock = xSemaphoreCreateMutex();
    if (s_detail_lock == NULL) {
        return ESP_ERR_NO_MEM;
    }

    if (xTaskCreate(radio_task, "radio", TASK_STACK, NULL, TASK_PRIO, NULL) != pdPASS) {
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGI(TAG, "ready (heap %" PRIu32 ")", esp_get_free_heap_size());
    return ESP_OK;
}

esp_err_t radio_play(int index)
{
    if (stations_get(index) == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    s_index = index;
    s_want = index;
    s_generation++;
    set_state(RADIO_CONNECTING);
    set_detail("starting");
    return ESP_OK;
}

void radio_stop(void)
{
    s_want = -1;
    set_state(RADIO_STOPPED);
    set_detail("stopped");
    audio_out_flush();
}

void radio_next(void)
{
    int n = stations_count();
    if (n == 0) {
        return;
    }
    int cur = s_want < 0 ? -1 : s_want;
    radio_play((cur + 1) % n);
}

void radio_prev(void)
{
    int n = stations_count();
    if (n == 0) {
        return;
    }
    int cur = s_want < 0 ? 0 : s_want;
    radio_play((cur - 1 + n) % n);
}

radio_state_t radio_get_state(void)
{
    return s_state;
}

int radio_get_index(void)
{
    return s_index;
}

const char *radio_get_name(void)
{
    const station_t *st = stations_get(s_index);
    return st ? st->name : "";
}

const char *radio_get_detail(void)
{
    static char copy[sizeof(s_detail)];
    if (s_detail_lock && xSemaphoreTake(s_detail_lock, pdMS_TO_TICKS(50)) == pdTRUE) {
        strlcpy(copy, s_detail, sizeof(copy));
        xSemaphoreGive(s_detail_lock);
    } else {
        strlcpy(copy, s_detail, sizeof(copy));
    }
    return copy;
}

uint32_t radio_get_bitrate(void)
{
    return s_bitrate;
}

uint32_t radio_get_sample_rate(void)
{
    return s_rate;
}
