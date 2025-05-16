// Copyright 2025 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include <stdio.h>

void reset_trackpoint(void) {
	gpio_set_pin_output(PS2_RESET_PIN);
	gpio_write_pin(PS2_RESET_PIN, 1);
	wait_ms(1);
	gpio_write_pin(PS2_RESET_PIN, 0);
	wait_ms(1);
}

void keyboard_pre_init_kb(void) {
	reset_trackpoint();
    keyboard_pre_init_user();
}
