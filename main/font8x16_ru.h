/*
 * 8x16 font with Cyrillic, taken from RUMG1C_D.c (see font8x16_ru.c).
 *
 * Glyph index layout:
 *   0x20-0x7E  ASCII
 *   0x80-0x9F  Cyrillic А..Я
 *   0xA0-0xAF  Cyrillic а..п
 *   0xE0-0xEF  Cyrillic р..я
 *   0xF8       degree sign
 */
#pragma once

#include <stdint.h>

#define FONT8X16_W 8
#define FONT8X16_H 16

extern const uint8_t Font8x16_Table[];
