#include "stations.h"

#include <string.h>
#include <ctype.h>
#include "esp_log.h"
#include "storage.h"

static const char *TAG = "stations";

#define STATIONS_FILE STORAGE_BASE_PATH "/stations.txt"

static station_t s_stations[STATION_MAX];
static int s_count = 0;

/* Bump the marker when the default list changes, so an old file is replaced. */
#define LIST_VERSION "# v3"

static const char *DEFAULT_LIST =
    LIST_VERSION "\n"
    "# ESP32 radio station list\n"
    "# Format:  Name|URL     (one per line, http:// or https:// MP3 streams)\n"
    "# Edit this file from the web page.\n"
    "\n"
    "Radio Paradise|http://stream.radioparadise.com/mp3-128\n"
    "FIP|http://icecast.radiofrance.fr/fip-midfi.mp3\n"
    "FIP Jazz|http://icecast.radiofrance.fr/fipjazz-midfi.mp3\n"
    "FIP Rock|http://icecast.radiofrance.fr/fiprock-midfi.mp3\n"
    "France Inter|http://icecast.radiofrance.fr/franceinter-midfi.mp3\n"
    "Dorozhnoe Radio|http://dorognoe.hostingradio.ru:8000/dorognoe\n"
    "Evropa Plus|http://ep128.hostingradio.ru:8030/ep128\n"
    "Retro FM|http://retroserver.streamr.ru:8043/retro256.mp3\n"
    "181.FM Classical|http://listen.181fm.com/181-classical_128k.mp3\n"
    "Galgaltz|http://glzwizzlv.bynetcdn.com/glz_mp3\n"
    "Shanson|http://listen.rusongs.ru/ru-mp3-128\n"
    "Kol Ha Musica|https://27873.live.streamtheworld.com/KAN_KOL_HAMUSICA.mp3\n"
    "Radio Swiss Classic|http://stream.srg-ssr.ch/m/rsc_de/mp3_128\n"
    "Radio Classique|https://radioclassique.ice.infomaniak.ch/radioclassique-high.mp3\n"
    "Classic FM|https://media-ssl.musicradio.com/ClassicFMMP3\n"
    "WQXR|https://stream.wqxr.org/wqxr\n";

const char *stations_path(void)
{
    return STATIONS_FILE;
}

static char *trim(char *s)
{
    while (*s && isspace((unsigned char)*s)) {
        s++;
    }
    char *end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1])) {
        *--end = '\0';
    }
    return s;
}

/* "http://host:port/path" -> "host" */
static void name_from_url(const char *url, char *out, size_t out_len)
{
    const char *p = strstr(url, "://");
    p = p ? p + 3 : url;
    size_t i = 0;
    while (p[i] && p[i] != '/' && p[i] != ':' && i + 1 < out_len) {
        out[i] = p[i];
        i++;
    }
    out[i] = '\0';
    if (i == 0) {
        strlcpy(out, "Station", out_len);
    }
}

esp_err_t stations_reload(void)
{
    static char text[8192];
    int n = storage_read(STATIONS_FILE, text, sizeof(text));
    if (n < 0) {
        ESP_LOGW(TAG, "cannot read %s", STATIONS_FILE);
        s_count = 0;
        return ESP_FAIL;
    }

    /*
     * Parse into a local counter and publish it only at the end, so a
     * concurrent reader never sees a half-empty list while a save is in
     * progress.
     */
    int count = 0;
    char *line = text;
    while (line != NULL && *line && count < STATION_MAX) {
        char *nl = strchr(line, '\n');
        if (nl != NULL) {
            *nl = '\0';
        }

        char *l = trim(line);
        if (*l != '\0' && *l != '#') {
            char *bar = strchr(l, '|');
            station_t *st = &s_stations[count];
            if (bar != NULL) {
                *bar = '\0';
                char *name = trim(l);
                char *url = trim(bar + 1);
                strlcpy(st->name, *name ? name : "Station", sizeof(st->name));
                strlcpy(st->url, url, sizeof(st->url));
            } else {
                strlcpy(st->url, l, sizeof(st->url));
                name_from_url(st->url, st->name, sizeof(st->name));
            }
            if (st->url[0] != '\0') {
                count++;
            }
        }

        line = (nl != NULL) ? nl + 1 : NULL;
    }
    s_count = count;

    ESP_LOGI(TAG, "loaded %d station(s)", s_count);
    for (int i = 0; i < s_count; i++) {
        ESP_LOGD(TAG, "  %d: %s -> %s", i, s_stations[i].name, s_stations[i].url);
    }
    return ESP_OK;
}

esp_err_t stations_init(void)
{
    static char text[8192];
    bool need_default = true;

    if (storage_read(STATIONS_FILE, text, sizeof(text)) > 0 &&
        strstr(text, LIST_VERSION) != NULL) {
        need_default = false;
    }

    if (need_default) {
        ESP_LOGI(TAG, "writing default station list");
        esp_err_t err = storage_write(STATIONS_FILE, DEFAULT_LIST, strlen(DEFAULT_LIST));
        if (err != ESP_OK) {
            return err;
        }
    }
    return stations_reload();
}

int stations_count(void)
{
    return s_count;
}

const station_t *stations_get(int index)
{
    if (index < 0 || index >= s_count) {
        return NULL;
    }
    return &s_stations[index];
}

esp_err_t stations_save_text(const char *text, size_t len)
{
    esp_err_t err = storage_write(STATIONS_FILE, text, len);
    if (err != ESP_OK) {
        return err;
    }
    return stations_reload();
}
