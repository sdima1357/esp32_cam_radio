/*
 * Tiny serial console on UART0, for use before the display/encoder exist.
 * Single key commands, no line editing:
 *
 *   p play station 1      n next        b previous     s stop
 *   + / -  volume         l list        w wifi         m memory
 *   h help
 */
#pragma once

#include "esp_err.h"

esp_err_t console_init(void);
