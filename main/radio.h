/*
 * Internet radio player.
 *
 * One task opens an HTTP MP3 stream, decodes it with libhelix and pushes
 * PCM into the shared I2S output.  Commands are just a "wanted station
 * index" variable, so stop/next/prev never block.
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

typedef enum {
    RADIO_STOPPED = 0,
    RADIO_CONNECTING,
    RADIO_PLAYING,
    RADIO_ERROR,
} radio_state_t;

esp_err_t radio_init(void);

/* Start (or switch to) a station. Index is into the station list. */
esp_err_t radio_play(int index);
void radio_stop(void);

/* Wait until the radio task has stopped and released the decoder/TLS buffers. */
esp_err_t radio_wait_idle(uint32_t timeout_ms);
void radio_next(void);
void radio_prev(void);

radio_state_t radio_get_state(void);
int radio_get_index(void);

/* Station name currently selected ("" when stopped). */
const char *radio_get_name(void);

/* Human readable status: "playing 128 kbps 44100 Hz", "http 404", ... */
const char *radio_get_detail(void);

uint32_t radio_get_bitrate(void);
uint32_t radio_get_sample_rate(void);
