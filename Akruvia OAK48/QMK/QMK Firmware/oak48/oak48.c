// Copyright 2024 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "oak48.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(CAPSLOCK_LED_PIN);
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        gpio_write_pin(CAPSLOCK_LED_PIN, led_state.caps_lock);
    }
    return res;
}