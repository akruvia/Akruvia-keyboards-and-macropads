// Copyright 2024 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(GP6);
    keyboard_pre_init_user();
}