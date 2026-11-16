/*
 * KY-040 rotary encoder.
 *
 *   A  = GPIO2
 *   B  = GPIO15
 *   SW = GPIO14 (push button, active low)
 *
 * Rotation changes the volume.  A short press goes to the next radio station
 * in radio mode, or sends AVRCP play/pause in Bluetooth mode.  Holding the
 * shaft for ~0.7 s toggles between radio and Bluetooth.
 * The A/B pins are decoded in a GPIO interrupt with a full quadrature state
 * machine, so no polling task is needed and fast turns are not missed.
 */
#pragma once

#include "esp_err.h"

/* Configure the pins, install the GPIO ISR and start the handler task. */
esp_err_t encoder_init(void);
