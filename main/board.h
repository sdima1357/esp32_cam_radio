/*
 * Board definitions for the ESP32-CAM AI-Thinker + peripherals.
 *
 * The camera is not used.  The 24-pin camera FPC connector is repurposed
 * through a 24-pin-to-2.54mm adapter for the SPI LCD.
 *
 * Left 8-pin header (P1):  5V  GND  GPIO12  GPIO13  GPIO15  GPIO14  GPIO2  GPIO4
 * Right 8-pin header (P2): 3V3 GND  GPIO16  GPIO0   GND     3V3/5V  GPIO3  GPIO1
 *
 * Notes:
 *  - GPIO16 is used by the on-board PSRAM.  Do not use it.
 *  - GPIO0 and EN are driven by the FTDI auto-reset circuit.  Do not use them.
 *  - GPIO12 and GPIO15 are boot strapping pins.  They are used here as I2S
 *    outputs (high-Z at boot) and encoder inputs (the KY-040 pull-ups hold
 *    them high, which is the required boot state).
 *  - GPIO4 also drives the on-board white flash LED through transistor Q1 and
 *    resistor R13.  R13 has been removed on this board, so GPIO4 is free for
 *    I2S data and the flash LED stays off.
 *  - The SD card slot is not used.  Do not insert a card: its pins are shared
 *    with GPIO2/4/12/13/14/15.
 */
#pragma once

/* ---- I2S audio DAC (PCM5102A) on the left header ---- */
#define BOARD_I2S_BCK_GPIO      12
#define BOARD_I2S_WS_GPIO       13
#define BOARD_I2S_DOUT_GPIO      4

/* ---- ST7789 320x240 SPI display via the camera FPC adapter ----
 *
 * Cam1 FPC pin -> camera net -> GPIO -> LCD signal:
 *   pin  4  Y3   / CSI_D1    GPIO18  SCLK
 *   pin 16  HREF / CSI_HSYNC GPIO23  MOSI
 *   pin  6  Y2   / CSI_D0    GPIO5   CS
 *   pin  3  Y4   / CSI_D2    GPIO19  DC
 *   pin  5  Y5   / CSI_D3    GPIO21  RST
 *   pin  8  PCLK / CSI_PCLK  GPIO22  BL
 *   pin 10  DGND             GND     GND
 * LCD VCC comes from the board 3V3 header, not from the camera connector
 * (DOVDD/DVDD/AVDD there are 2.8 V / 1.2 V).
 */
#define BOARD_LCD_SCLK_GPIO     18
#define BOARD_LCD_MOSI_GPIO     23
#define BOARD_LCD_CS_GPIO        5
#define BOARD_LCD_DC_GPIO       19
#define BOARD_LCD_RST_GPIO      21
#define BOARD_LCD_BL_GPIO       22

/* 2.4" 320x240 module: ST7789 with a 240x320 GRAM used in landscape. */
#define BOARD_LCD_H_RES          320
#define BOARD_LCD_V_RES          240
#define BOARD_LCD_X_OFFSET       0
#define BOARD_LCD_Y_OFFSET       0

/* Panel tuning: flip these if the image is rotated, mirrored or colour-swapped. */
#define BOARD_LCD_SWAP_XY        1
#define BOARD_LCD_MIRROR_X       1
#define BOARD_LCD_MIRROR_Y       0
#define BOARD_LCD_INVERT         0
#define BOARD_LCD_BGR            0

#define BOARD_LCD_SPI_HZ         (26 * 1000 * 1000)
#define BOARD_LCD_STRIP_ROWS     4
#define BOARD_LCD_SELFTEST       1
#define BOARD_LCD_BL_ACTIVE_LOW  0

/* ---- KY-040 rotary encoder on the left header ---- */
#define BOARD_ENC_A_GPIO         2
#define BOARD_ENC_B_GPIO        15
#define BOARD_ENC_SW_GPIO       14

/* ---- On-board red LED (GPIO33, active low) ---- */
#define BOARD_LED_GPIO          33
#define BOARD_LED_ACTIVE_LOW     1

/* ---- Bluetooth ---- */
#define BOARD_BT_NAME           "ESP32-CAM Radio"

/* ---- Defaults ---- */
#define BOARD_AUDIO_RATE        44100
