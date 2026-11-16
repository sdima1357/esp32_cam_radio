#pragma once

typedef enum {
    LED_MODE_OFF = 0,
    LED_MODE_ON,
    LED_MODE_BLINK_SLOW,   /* discoverable / idle */
    LED_MODE_BLINK_FAST,   /* connecting */
} led_mode_t;

void status_led_init(void);
void status_led_set(led_mode_t mode);
