#include "bt_audio.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_system.h"
#include "esp_heap_caps.h"

#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"

#include "audio_out.h"
#include "board.h"
#include "status_led.h"

static const char *TAG = "bt";

static volatile bt_audio_state_t s_state = BT_AUDIO_OFF;
static volatile bool s_enabled = false;
static volatile bool s_connected = false;
static volatile bool s_playing = false;
static volatile bool s_avrc_connected = false;

static esp_bd_addr_t s_remote_bda;
static char s_remote_name[ESP_BT_GAP_MAX_BDNAME_LEN + 1] = "";
static char s_detail[64] = "off";

static bool s_stack_ready = false;

/*
 * The classic BT stack costs 60-90 KB of internal RAM, which the HTTPS
 * client needs for its TLS handshake.  It is therefore brought up lazily on
 * the first switch to Bluetooth mode and torn down again when the radio is
 * selected, so radio-only operation always has the full internal heap.
 */
static SemaphoreHandle_t s_init_mutex = NULL;
static SemaphoreHandle_t s_init_done = NULL;
static esp_err_t s_init_result = ESP_ERR_INVALID_STATE;
static bool s_init_started = false;

#define BT_INIT_TASK_STACK  6144
#define BT_INIT_TASK_PRIO   5
#define BT_INIT_TIMEOUT_MS  15000

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */

static void set_detail(const char *text)
{
    strlcpy(s_detail, text, sizeof(s_detail));
}

static void update_state(void)
{
    if (!s_enabled) {
        s_state = BT_AUDIO_OFF;
        set_detail("off");
        status_led_set(LED_MODE_OFF);
        return;
    }

    if (s_playing) {
        s_state = BT_AUDIO_PLAYING;
        set_detail("playing 44.1 kHz");
        status_led_set(LED_MODE_ON);
    } else if (s_connected) {
        s_state = BT_AUDIO_CONNECTED;
        set_detail("connected, paused");
        status_led_set(LED_MODE_ON);
    } else {
        s_state = BT_AUDIO_DISCOVERABLE;
        set_detail("discoverable");
        status_led_set(LED_MODE_BLINK_SLOW);
    }
}

static void bda_to_str(const uint8_t *bda, char *out, size_t out_len)
{
    snprintf(out, out_len, "%02x:%02x:%02x:%02x:%02x:%02x",
             bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);
}

/* ------------------------------------------------------------------ */
/* A2DP                                                                */
/* ------------------------------------------------------------------ */

static void a2d_data_cb(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0) {
        return;
    }
    /* The Bluedroid A2DP sink always delivers 44.1 kHz stereo 16-bit PCM. */
    audio_out_set_format(44100, 2);
    audio_out_write(data, len, 0);
}

static void a2d_cb(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param)
{
    switch (event) {
    case ESP_A2D_CONNECTION_STATE_EVT: {
        char bda[18];
        bda_to_str(param->conn_stat.remote_bda, bda, sizeof(bda));
        switch (param->conn_stat.state) {
        case ESP_A2D_CONNECTION_STATE_CONNECTED:
            memcpy(s_remote_bda, param->conn_stat.remote_bda, ESP_BD_ADDR_LEN);
            s_connected = true;
            ESP_LOGI(TAG, "A2DP connected: %s", bda);
            break;
        case ESP_A2D_CONNECTION_STATE_DISCONNECTED:
            s_connected = false;
            s_playing = false;
            audio_out_flush();
            ESP_LOGI(TAG, "A2DP disconnected: %s", bda);
            break;
        case ESP_A2D_CONNECTION_STATE_CONNECTING:
            ESP_LOGI(TAG, "A2DP connecting: %s", bda);
            break;
        case ESP_A2D_CONNECTION_STATE_DISCONNECTING:
            ESP_LOGI(TAG, "A2DP disconnecting: %s", bda);
            break;
        default:
            break;
        }
        update_state();
        break;
    }
    case ESP_A2D_AUDIO_STATE_EVT:
        if (param->audio_stat.state == ESP_A2D_AUDIO_STATE_STARTED) {
            s_playing = true;
            audio_out_flush();
            ESP_LOGI(TAG, "A2DP audio started");
        } else {
            s_playing = false;
            audio_out_flush();
            ESP_LOGI(TAG, "A2DP audio suspended");
        }
        update_state();
        break;
    case ESP_A2D_AUDIO_CFG_EVT: {
        esp_a2d_mcc_t *mcc = &param->audio_cfg.mcc;
        if (mcc->type == ESP_A2D_MCT_SBC) {
            ESP_LOGI(TAG, "A2DP SBC config: rate idx %d, ch mode %d",
                     mcc->cie.sbc[0] >> 4, (mcc->cie.sbc[0] >> 2) & 0x03);
        } else {
            ESP_LOGI(TAG, "A2DP codec type %d", mcc->type);
        }
        break;
    }
    case ESP_A2D_PROF_STATE_EVT:
        ESP_LOGI(TAG, "A2DP profile state: %d", param->a2d_prof_stat.init_state);
        break;
    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* AVRCP                                                               */
/* ------------------------------------------------------------------ */

static void avrc_ct_cb(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param)
{
    switch (event) {
    case ESP_AVRC_CT_CONNECTION_STATE_EVT:
        s_avrc_connected = param->conn_stat.connected;
        ESP_LOGI(TAG, "AVRCP CT %s",
                 s_avrc_connected ? "connected" : "disconnected");
        break;
    case ESP_AVRC_CT_REMOTE_FEATURES_EVT:
        ESP_LOGI(TAG, "AVRCP remote features 0x%08" PRIx32,
                 param->rmt_feats.feat_mask);
        break;
    default:
        break;
    }
}

static void avrc_tg_cb(esp_avrc_tg_cb_event_t event, esp_avrc_tg_cb_param_t *param)
{
    switch (event) {
    case ESP_AVRC_TG_CONNECTION_STATE_EVT:
        ESP_LOGI(TAG, "AVRCP TG %s",
                 param->conn_stat.connected ? "connected" : "disconnected");
        break;
    case ESP_AVRC_TG_SET_ABSOLUTE_VOLUME_CMD_EVT: {
        int vol = (int)param->set_abs_vol.volume * 100 / 0x7f;
        ESP_LOGI(TAG, "phone volume: %d%%", vol);
        audio_out_set_volume(vol);
        break;
    }
    case ESP_AVRC_TG_REGISTER_NOTIFICATION_EVT:
        if (param->reg_ntf.event_id == ESP_AVRC_RN_VOLUME_CHANGE) {
            esp_avrc_rn_param_t rn = {
                .volume = (uint8_t)(audio_out_get_volume() * 0x7f / 100),
            };
            esp_avrc_tg_send_rn_rsp(ESP_AVRC_RN_VOLUME_CHANGE,
                                    ESP_AVRC_RN_RSP_INTERIM, &rn);
        }
        break;
    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* GAP                                                                 */
/* ------------------------------------------------------------------ */

static void gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT:
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            strlcpy(s_remote_name, (const char *)param->auth_cmpl.device_name,
                    sizeof(s_remote_name));
            ESP_LOGI(TAG, "paired with \"%s\"", s_remote_name);
        } else {
            ESP_LOGW(TAG, "authentication failed: %d", param->auth_cmpl.stat);
        }
        break;
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(TAG, "SSP confirm request: %" PRIu32, param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(TAG, "SSP passkey: %" PRIu32, param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(TAG, "SSP passkey requested");
        break;
    case ESP_BT_GAP_ACL_CONN_CMPL_STAT_EVT:
        ESP_LOGI(TAG, "ACL connected, status 0x%x",
                 param->acl_conn_cmpl_stat.stat);
        break;
    case ESP_BT_GAP_ACL_DISCONN_CMPL_STAT_EVT:
        ESP_LOGI(TAG, "ACL disconnected, reason 0x%x",
                 param->acl_disconn_cmpl_stat.reason);
        break;
    case ESP_BT_GAP_MODE_CHG_EVT:
        ESP_LOGD(TAG, "BT mode %d", param->mode_chg.mode);
        break;
    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

void bt_audio_preinit(void)
{
    if (s_init_mutex == NULL) {
        s_init_mutex = xSemaphoreCreateMutex();
    }
    if (s_init_done == NULL) {
        s_init_done = xSemaphoreCreateBinary();
    }
}

static void bt_init_task(void *arg)
{
    (void)arg;
    s_init_result = bt_audio_init();
    xSemaphoreGive(s_init_done);
    vTaskDelete(NULL);
}

esp_err_t bt_audio_ensure_init(void)
{
    if (s_stack_ready) {
        return ESP_OK;
    }
    if (s_init_mutex == NULL || s_init_done == NULL) {
        bt_audio_preinit();
    }
    if (s_init_mutex == NULL || s_init_done == NULL) {
        return ESP_ERR_NO_MEM;
    }
    /* Serialise concurrent calls (web UI, encoder, console). */
    if (xSemaphoreTake(s_init_mutex, pdMS_TO_TICKS(20000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    esp_err_t err = ESP_OK;
    if (!s_stack_ready) {
        if (!s_init_started) {
            s_init_started = true;
            if (xTaskCreate(bt_init_task, "bt_init", BT_INIT_TASK_STACK, NULL,
                            BT_INIT_TASK_PRIO, NULL) != pdPASS) {
                s_init_started = false;
                err = ESP_ERR_NO_MEM;
            }
        }
        if (err == ESP_OK) {
            /* Also waits for an init started by an earlier, timed-out call. */
            if (xSemaphoreTake(s_init_done,
                               pdMS_TO_TICKS(BT_INIT_TIMEOUT_MS)) != pdTRUE) {
                err = ESP_ERR_TIMEOUT;
            } else {
                err = s_init_result;
                if (err != ESP_OK) {
                    /* Allow a later retry. */
                    s_init_started = false;
                }
            }
        }
    }

    xSemaphoreGive(s_init_mutex);
    return err;
}

esp_err_t bt_audio_init(void)
{
    if (s_stack_ready) {
        return ESP_OK;
    }

    esp_err_t err = esp_bt_controller_mem_release(ESP_BT_MODE_BLE);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGW(TAG, "BLE memory release: %s", esp_err_to_name(err));
    }

    esp_bt_controller_config_t cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_RETURN_ON_ERROR(esp_bt_controller_init(&cfg), TAG, "controller init");
    ESP_RETURN_ON_ERROR(esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT),
                        TAG, "controller enable");

    esp_bluedroid_config_t bluedroid_cfg = BT_BLUEDROID_INIT_CONFIG_DEFAULT();
    ESP_RETURN_ON_ERROR(esp_bluedroid_init_with_cfg(&bluedroid_cfg),
                        TAG, "bluedroid init");
    ESP_RETURN_ON_ERROR(esp_bluedroid_enable(), TAG, "bluedroid enable");

    /* "Just works" pairing; 1234 is the legacy fallback PIN. */
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_NONE;
    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(iocap));

    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
    esp_bt_pin_code_t pin_code = { '1', '2', '3', '4' };
    esp_bt_gap_set_pin(pin_type, 4, pin_code);

    esp_bt_gap_register_callback(gap_cb);
    esp_bt_gap_set_device_name(BOARD_BT_NAME);

    ESP_RETURN_ON_ERROR(esp_avrc_ct_init(), TAG, "avrc ct init");
    ESP_RETURN_ON_ERROR(esp_avrc_ct_register_callback(avrc_ct_cb),
                        TAG, "avrc ct callback");
    ESP_RETURN_ON_ERROR(esp_avrc_tg_init(), TAG, "avrc tg init");
    ESP_RETURN_ON_ERROR(esp_avrc_tg_register_callback(avrc_tg_cb),
                        TAG, "avrc tg callback");

    esp_avrc_rn_evt_cap_mask_t evt_set = {0};
    esp_avrc_rn_evt_bit_mask_operation(ESP_AVRC_BIT_MASK_OP_SET, &evt_set,
                                       ESP_AVRC_RN_VOLUME_CHANGE);
    esp_avrc_tg_set_rn_evt_cap(&evt_set);

    ESP_RETURN_ON_ERROR(esp_a2d_sink_init(), TAG, "a2dp sink init");
    esp_a2d_register_callback(a2d_cb);
    esp_a2d_sink_register_data_callback(a2d_data_cb);

    esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);

    s_stack_ready = true;
    s_state = BT_AUDIO_OFF;
    set_detail("off");
    ESP_LOGI(TAG, "ready as \"%s\" (heap %" PRIu32 ", internal free %u)",
             BOARD_BT_NAME, esp_get_free_heap_size(),
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    return ESP_OK;
}

esp_err_t bt_audio_deinit(void)
{
    if (!s_stack_ready) {
        return ESP_OK;
    }

    /* Do not race with an init in progress. */
    if (s_init_mutex != NULL) {
        if (xSemaphoreTake(s_init_mutex, pdMS_TO_TICKS(20000)) != pdTRUE) {
            return ESP_ERR_TIMEOUT;
        }
    }

    /* Disconnect and hide before tearing the stack down. */
    if (s_enabled) {
        bt_audio_set_enabled(false);
        /* Let the asynchronous A2DP disconnect complete first. */
        vTaskDelay(pdMS_TO_TICKS(300));
    }

    esp_err_t err = esp_a2d_sink_deinit();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "a2dp deinit: %s", esp_err_to_name(err));
    }
    err = esp_avrc_tg_deinit();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "avrc tg deinit: %s", esp_err_to_name(err));
    }
    err = esp_avrc_ct_deinit();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "avrc ct deinit: %s", esp_err_to_name(err));
    }
    err = esp_bluedroid_disable();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "bluedroid disable: %s", esp_err_to_name(err));
    }
    err = esp_bluedroid_deinit();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "bluedroid deinit: %s", esp_err_to_name(err));
    }
    err = esp_bt_controller_disable();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "controller disable: %s", esp_err_to_name(err));
    }
    err = esp_bt_controller_deinit();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "controller deinit: %s", esp_err_to_name(err));
    }
    /*
     * Deliberately no esp_bt_controller_mem_release() here: it hands the
     * controller's reserved regions to the general heap, so a later
     * esp_bt_controller_init() would use memory that may already be
     * allocated.  The dynamic allocations freed above are what the TLS
     * handshake needs; the static regions were never part of the heap.
     */

    s_stack_ready = false;
    s_enabled = false;
    s_connected = false;
    s_playing = false;
    s_avrc_connected = false;
    s_remote_name[0] = '\0';
    s_state = BT_AUDIO_OFF;
    set_detail("off");
    status_led_set(LED_MODE_OFF);

    /* Allow the next Bluetooth switch to start the stack again. */
    s_init_started = false;
    s_init_result = ESP_ERR_INVALID_STATE;

    ESP_LOGI(TAG, "stack released (heap %" PRIu32 ", internal free %u)",
             esp_get_free_heap_size(),
             (unsigned)heap_caps_get_free_size(MALLOC_CAP_INTERNAL));

    if (s_init_mutex != NULL) {
        xSemaphoreGive(s_init_mutex);
    }
    return ESP_OK;
}

esp_err_t bt_audio_set_enabled(bool enabled)
{
    if (!s_stack_ready) {
        return ESP_ERR_INVALID_STATE;
    }

    s_enabled = enabled;

    if (enabled) {
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        ESP_LOGI(TAG, "discoverable as \"%s\"", BOARD_BT_NAME);
    } else {
        if (s_connected) {
            esp_a2d_sink_disconnect(s_remote_bda);
        }
        esp_bt_gap_set_scan_mode(ESP_BT_NON_CONNECTABLE, ESP_BT_NON_DISCOVERABLE);
        s_connected = false;
        s_playing = false;
        audio_out_flush();
        ESP_LOGI(TAG, "disabled");
    }

    update_state();
    return ESP_OK;
}

bt_audio_state_t bt_audio_get_state(void)
{
    return s_state;
}

bool bt_audio_is_connected(void)
{
    return s_connected;
}

const char *bt_audio_get_detail(void)
{
    return s_detail;
}

const char *bt_audio_get_remote_name(void)
{
    return s_remote_name;
}

void bt_audio_play_pause(void)
{
    if (!s_avrc_connected) {
        ESP_LOGW(TAG, "play/pause: AVRCP not connected");
        return;
    }
    esp_avrc_ct_send_passthrough_cmd(0, ESP_AVRC_PT_CMD_PLAY,
                                     ESP_AVRC_PT_CMD_STATE_PRESSED);
    esp_avrc_ct_send_passthrough_cmd(0, ESP_AVRC_PT_CMD_PLAY,
                                     ESP_AVRC_PT_CMD_STATE_RELEASED);
}
