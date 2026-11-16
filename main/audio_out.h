/*
 * Shared I2S audio output.
 *
 * A single I2S TX channel feeds the PCM5102A DAC. Audio sources push 16-bit
 * PCM into a ring buffer which is drained by a dedicated writer task.
 * Software volume control is applied while draining.
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"

/* Create the I2S channel, ring buffer and writer task. */
esp_err_t audio_out_init(uint32_t sample_rate, uint8_t channels);

/* Reconfigure the I2S clock/slot for a new stream format (no-op if unchanged). */
esp_err_t audio_out_set_format(uint32_t sample_rate, uint8_t channels);

/* Queue PCM data. Non-blocking when timeout_ms == 0; drops data if full. */
size_t audio_out_write(const void *data, size_t len, uint32_t timeout_ms);

/* Drop everything currently buffered (used when switching sources). */
void audio_out_flush(void);

/*
 * Hold playback until a decent amount of audio is buffered (or ~2 s pass).
 * Live streams arrive in bursts, so this avoids an immediate underrun.
 */
void audio_out_prefill(void);

/* Volume 0..100 (applied to all sources). */
void audio_out_set_volume(int percent);
int audio_out_get_volume(void);

/* Mute without losing the volume setting. */
void audio_out_set_mute(bool mute);
bool audio_out_is_muted(void);

/* Current format. */
uint32_t audio_out_get_rate(void);
uint8_t audio_out_get_channels(void);

/* Play a short sine beep (blocking, for self-test / UI feedback). */
void audio_out_play_tone(uint32_t freq_hz, uint32_t duration_ms);
