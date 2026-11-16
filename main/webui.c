#include "webui.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_check.h"

#include "app_mode.h"
#include "audio_out.h"
#include "bt_audio.h"
#include "radio.h"
#include "stations.h"
#include "storage.h"
#include "wifi.h"
#include "clock.h"

static const char *TAG = "web";

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */

static void html_escape(const char *in, char *out, size_t out_len)
{
    size_t o = 0;
    for (const char *p = in; *p && o + 7 < out_len; p++) {
        switch (*p) {
        case '&':  o += snprintf(out + o, out_len - o, "&amp;"); break;
        case '<':  o += snprintf(out + o, out_len - o, "&lt;"); break;
        case '>':  o += snprintf(out + o, out_len - o, "&gt;"); break;
        case '"':  o += snprintf(out + o, out_len - o, "&quot;"); break;
        default:   out[o++] = *p; break;
        }
    }
    out[o] = '\0';
}

static void json_escape(const char *in, char *out, size_t out_len)
{
    size_t o = 0;
    for (const char *p = in; *p && o + 2 < out_len; p++) {
        if (*p == '"' || *p == '\\') {
            out[o++] = '\\';
        }
        out[o++] = (*p == '\n') ? ' ' : *p;
    }
    out[o] = '\0';
}

static int hexval(int c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static void url_decode(const char *in, size_t in_len, char *out, size_t out_len)
{
    size_t o = 0;
    for (size_t i = 0; i < in_len && o + 1 < out_len; i++) {
        char c = in[i];
        if (c == '+') {
            out[o++] = ' ';
        } else if (c == '%' && i + 2 < in_len) {
            int hi = hexval(in[i + 1]), lo = hexval(in[i + 2]);
            if (hi >= 0 && lo >= 0) {
                out[o++] = (char)((hi << 4) | lo);
                i += 2;
            } else {
                out[o++] = c;
            }
        } else {
            out[o++] = c;
        }
    }
    out[o] = '\0';
}

/* Value of a query string parameter, decoded. */
static void query_param(httpd_req_t *req, const char *name, char *out, size_t out_len)
{
    out[0] = '\0';
    size_t qlen = httpd_req_get_url_query_len(req) + 1;
    if (qlen <= 1) {
        return;
    }
    char *q = malloc(qlen);
    if (q == NULL) {
        return;
    }
    if (httpd_req_get_url_query_str(req, q, qlen) == ESP_OK) {
        char raw[64];
        if (httpd_query_key_value(q, name, raw, sizeof(raw)) == ESP_OK) {
            url_decode(raw, strlen(raw), out, out_len);
        }
    }
    free(q);
}

/* ------------------------------------------------------------------ */
/* Pages                                                               */
/* ------------------------------------------------------------------ */

static const char *PAGE_HEAD =
    "<!doctype html><html><head><meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
    "<title>ESP32 Radio</title><style>"
    "body{font-family:system-ui,sans-serif;background:#12141a;color:#e6e8ee;"
    "margin:0;padding:16px;max-width:760px}"
    "h1{font-size:20px;margin:0 0 4px}"
    ".sub{color:#8b93a7;font-size:13px;margin-bottom:16px}"
    ".now{background:#1b1f2a;border-radius:10px;padding:12px 14px;margin-bottom:14px}"
    ".now b{font-size:17px}"
    ".det{color:#8b93a7;font-size:13px;margin-top:4px}"
    ".row{display:flex;align-items:center;gap:8px;padding:8px 10px;border-radius:8px;"
    "background:#1b1f2a;margin-bottom:6px}"
    ".row .n{flex:1;font-size:14px}"
    ".row.act{outline:1px solid #4f8cff}"
    "button{background:#2a3142;color:#e6e8ee;border:0;border-radius:7px;"
    "padding:8px 12px;font-size:14px;cursor:pointer}"
    "button.p{background:#3b6ef5}"
    "button:hover{filter:brightness(1.2)}"
    "a{color:#7aa2ff}"
    "input[type=range]{width:100%;margin:6px 0 14px}"
    ".bar{display:flex;gap:8px;margin-bottom:14px}"
    "textarea{width:100%;height:60vh;background:#0d0f14;color:#dfe4ee;border:1px solid #2a3142;"
    "border-radius:8px;padding:10px;font-family:ui-monospace,monospace;font-size:13px}"
    "</style></head><body>";

static esp_err_t index_get(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_sendstr_chunk(req, PAGE_HEAD);

    /* Keep each snprintf small: the httpd task stack is only a few KB. */
    char buf[512];
    snprintf(buf, sizeof(buf),
             "<h1>ESP32 Radio</h1><div class=\"sub\">%s &middot; "
             "<a href=\"/edit\">edit stations</a></div>"
             "<div class=\"now\"><b id=\"nm\">stopped</b>"
             "<div class=\"det\" id=\"dt\">-</div>"
             "<div class=\"det\" id=\"tm\">-</div></div>",
             wifi_get_ip());
    httpd_resp_sendstr_chunk(req, buf);

    snprintf(buf, sizeof(buf),
             "<div class=\"bar\">"
             "<button onclick=\"c('prev')\">&#9198;</button>"
             "<button class=\"p\" onclick=\"c('stop')\">Stop</button>"
             "<button onclick=\"c('next')\">&#9197;</button>"
             "<button onclick=\"c('mode')\">Radio / BT</button>"
             "<button onclick=\"c('btplay')\">BT play/pause</button></div>"
             "<div>Volume <span id=\"vv\">%d</span></div>"
             "<input type=\"range\" min=\"0\" max=\"100\" value=\"%d\" "
             "oninput=\"sv(this.value)\">",
             audio_out_get_volume(), audio_out_get_volume());
    httpd_resp_sendstr_chunk(req, buf);

    for (int i = 0; i < stations_count(); i++) {
        const station_t *st = stations_get(i);
        char name[STATION_NAME_LEN * 6];
        html_escape(st->name, name, sizeof(name));
        snprintf(buf, sizeof(buf),
                 "<div class=\"row\" data-i=\"%d\"><span class=\"n\">%s</span>"
                 "<button class=\"p\" onclick=\"c('play&i=%d')\">Play</button></div>",
                 i, name, i);
        httpd_resp_sendstr_chunk(req, buf);
    }

    httpd_resp_sendstr_chunk(req,
        "<script>"
        "function c(a){fetch('/api/cmd?c='+a)}"
        "function sv(v){document.getElementById('vv').textContent=v;"
        "fetch('/api/cmd?c=vol&v='+v)}"
        "function upd(){fetch('/api/status').then(r=>r.json()).then(s=>{"
        "var bt=(s.mode===1);"
        "document.getElementById('nm').textContent=bt?"
        "('Bluetooth'+(s.bt_remote?' \\u00b7 '+s.bt_remote:'')):(s.name||'stopped');"
        "document.getElementById('dt').textContent=(bt?s.bt_detail:s.detail)+"
        "' | wifi '+(s.wifi?s.ip:'down');"
        "document.getElementById('tm').textContent=s.time;"
        "document.getElementById('vv').textContent=s.vol;"
        "document.querySelectorAll('.row').forEach(e=>"
        "e.classList.toggle('act',!bt&&(+e.dataset.i===s.index)&&s.state>0));"
        "}).catch(()=>{})}"
        "setInterval(upd,2000);upd();"
        "</script></body></html>");
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

static esp_err_t edit_get(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_sendstr_chunk(req, PAGE_HEAD);
    httpd_resp_sendstr_chunk(req,
        "<h1>Station list</h1><div class=\"sub\">One station per line: "
        "<code>Name|URL</code> &middot; <a href=\"/\">back</a></div>"
        "<form method=\"post\" action=\"/save\">"
        "<textarea name=\"text\" spellcheck=\"false\">");

    /* Escape and stream the file in small pieces to keep RAM use low. */
    FILE *f = fopen(stations_path(), "r");
    if (f != NULL) {
        /* Keep these small: the httpd task stack is only 3.5 KB. */
        char raw[128];
        char esc[128 * 6];
        size_t n;
        while ((n = fread(raw, 1, sizeof(raw) - 1, f)) > 0) {
            raw[n] = '\0';
            html_escape(raw, esc, sizeof(esc));
            if (httpd_resp_sendstr_chunk(req, esc) != ESP_OK) {
                break;
            }
        }
        fclose(f);
    }

    httpd_resp_sendstr_chunk(req,
        "</textarea><p><button class=\"p\" type=\"submit\">Save</button></p>"
        "</form></body></html>");
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

static esp_err_t save_post(httpd_req_t *req)
{
    int total = req->content_len;
    if (total <= 0 || total > 8192) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "bad size");
        return ESP_FAIL;
    }

    char *body = malloc(total + 1);
    if (body == NULL) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "oom");
        return ESP_FAIL;
    }

    int got = 0;
    while (got < total) {
        int r = httpd_req_recv(req, body + got, total - got);
        if (r <= 0) {
            free(body);
            httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "recv");
            return ESP_FAIL;
        }
        got += r;
    }
    body[got] = '\0';

    char *field = strstr(body, "text=");
    if (field == NULL) {
        free(body);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "no text field");
        return ESP_FAIL;
    }
    field += 5;

    /* Decode in place: the output is never longer than the input, so this
     * saves a second 8 KB allocation while an HTTPS stream is running. */
    size_t field_len = strlen(field);
    url_decode(field, field_len, field, total + 1 - (size_t)(field - body));

    esp_err_t err = stations_save_text(field, strlen(field));
    free(body);

    if (err != ESP_OK) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "save failed");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "station list saved (%d stations)", stations_count());
    httpd_resp_set_status(req, "303 See Other");
    httpd_resp_set_hdr(req, "Location", "/");
    httpd_resp_sendstr(req, "");
    return ESP_OK;
}

static esp_err_t status_get(httpd_req_t *req)
{
    char name[64], detail[96], timestr[40];
    char bt_detail[64], bt_remote[64];
    json_escape(radio_get_name(), name, sizeof(name));
    json_escape(radio_get_detail(), detail, sizeof(detail));
    json_escape(bt_audio_get_detail(), bt_detail, sizeof(bt_detail));
    json_escape(bt_audio_get_remote_name(), bt_remote, sizeof(bt_remote));
    clock_format(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S %Z");

    char buf[512];
    snprintf(buf, sizeof(buf),
             "{\"state\":%d,\"index\":%d,\"name\":\"%s\",\"detail\":\"%s\","
             "\"mode\":%d,\"bt\":%d,\"bt_detail\":\"%s\",\"bt_remote\":\"%s\","
             "\"vol\":%d,\"wifi\":%s,\"ip\":\"%s\",\"rssi\":%d,\"time\":\"%s\"}",
             (int)radio_get_state(), radio_get_index(), name, detail,
             (int)app_mode_get(), (int)bt_audio_get_state(),
             bt_detail, bt_remote,
             audio_out_get_volume(), wifi_is_connected() ? "true" : "false",
             wifi_get_ip(), wifi_get_rssi(), timestr);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    return httpd_resp_sendstr(req, buf);
}

static esp_err_t cmd_get(httpd_req_t *req)
{
    char cmd[24], val[16];
    query_param(req, "c", cmd, sizeof(cmd));

    if (strcmp(cmd, "play") == 0) {
        query_param(req, "i", val, sizeof(val));
        int i = atoi(val);
        if (i >= 0 && i < stations_count()) {
            /* Playing a station always means radio mode. */
            if (app_mode_is_bt()) {
                app_mode_set(APP_MODE_RADIO);
            }
            radio_play(i);
        }
    } else if (strcmp(cmd, "stop") == 0) {
        radio_stop();
    } else if (strcmp(cmd, "next") == 0) {
        if (app_mode_is_bt()) {
            app_mode_set(APP_MODE_RADIO);
        }
        radio_next();
    } else if (strcmp(cmd, "prev") == 0) {
        if (app_mode_is_bt()) {
            app_mode_set(APP_MODE_RADIO);
        }
        radio_prev();
    } else if (strcmp(cmd, "vol") == 0) {
        query_param(req, "v", val, sizeof(val));
        audio_out_set_volume(atoi(val));
    } else if (strcmp(cmd, "mode") == 0) {
        app_mode_toggle();
    } else if (strcmp(cmd, "mode_radio") == 0) {
        app_mode_set(APP_MODE_RADIO);
    } else if (strcmp(cmd, "mode_bt") == 0) {
        app_mode_set(APP_MODE_BT);
    } else if (strcmp(cmd, "btplay") == 0) {
        bt_audio_play_pause();
    } else {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "unknown command");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    return httpd_resp_sendstr(req, "{\"ok\":true}");
}

/* ------------------------------------------------------------------ */

esp_err_t webui_start(void)
{
    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    /* The status JSON and the edit page need more than the 3.5 KB default. */
    cfg.stack_size = 5120;
    cfg.max_open_sockets = 2;
    cfg.max_uri_handlers = 8;
    cfg.lru_purge_enable = true;

    httpd_handle_t server = NULL;
    esp_err_t err = httpd_start(&server, &cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "httpd_start: %s", esp_err_to_name(err));
        return err;
    }

    static const httpd_uri_t uris[] = {
        { .uri = "/",           .method = HTTP_GET,  .handler = index_get  },
        { .uri = "/edit",       .method = HTTP_GET,  .handler = edit_get   },
        { .uri = "/save",       .method = HTTP_POST, .handler = save_post  },
        { .uri = "/api/status", .method = HTTP_GET,  .handler = status_get },
        { .uri = "/api/cmd",    .method = HTTP_GET,  .handler = cmd_get    },
    };
    for (size_t i = 0; i < sizeof(uris) / sizeof(uris[0]); i++) {
        ESP_RETURN_ON_ERROR(httpd_register_uri_handler(server, &uris[i]),
                            TAG, "register %s", uris[i].uri);
    }

    ESP_LOGI(TAG, "web ui on http://%s/", wifi_get_ip());
    return ESP_OK;
}
