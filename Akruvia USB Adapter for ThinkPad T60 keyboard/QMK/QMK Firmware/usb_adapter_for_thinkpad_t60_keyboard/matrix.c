// Copyright 2025 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "quantum.h"
#include "debounce.h"
#include <stdio.h>

#include <print.h>

ioline_t selectPins[] = {SELECT_PIN0, SELECT_PIN1, SELECT_PIN2, SELECT_PIN3, SELECT_PIN4, SELECT_PIN5, SELECT_PIN6, SELECT_PIN7};

ioline_t inputPins[] = {INPUT_PIN0, INPUT_PIN1, INPUT_PIN2, INPUT_PIN3, INPUT_PIN4, INPUT_PIN5, INPUT_PIN6, INPUT_PIN7,
						INPUT_PIN8, INPUT_PIN9, INPUT_PIN10, INPUT_PIN11, INPUT_PIN12, INPUT_PIN13, INPUT_PIN14, INPUT_PIN15};

uint8_t numberOfSelectPins = sizeof(selectPins) / sizeof(selectPins[0]);
uint8_t numberOfInputPins = sizeof(inputPins) / sizeof(inputPins[0]);

extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values

void set_or_clear_row_column(matrix_row_t *curr_matrix, uint8_t row, uint8_t col, uint8_t value) {
	if(value) {
		curr_matrix[row] |= (1 << col);
	} else {
		curr_matrix[row] &= ~(1 << col);
	}
}

void set_or_clear_matrix_location(matrix_row_t *curr_matrix, uint8_t select_pin, uint8_t input_pin, uint8_t value) {
	if(select_pin == 0) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 4, 6, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 1, 5, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 1, 4, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 4, 5, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 4, 11, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 1, 3, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 0, 4, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 0, 0, value);
		} else if(input_pin == 13) {
			set_or_clear_row_column(curr_matrix, 6, 9, value);
		} else if(input_pin == 15) {
			set_or_clear_row_column(curr_matrix, 6, 3, value);
		}
	} else if(select_pin == 1) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 2, 6, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 2, 12, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 1, 8, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 1, 7, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 2, 5, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 2, 11, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 1, 1, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 1, 12, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 1, 0, value);
		} else if(input_pin == 9) {
			set_or_clear_row_column(curr_matrix, 0, 9, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 2, 0, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 0, 11, value);
		} else if(input_pin == 13) {
			set_or_clear_row_column(curr_matrix, 0, 10, value);
		} else if(input_pin == 14) {
			set_or_clear_row_column(curr_matrix, 6, 1, value);
		}
	} else if(select_pin == 2) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 3, 6, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 3, 12, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 2, 13, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 1, 6, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 3, 5, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 3, 11, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 1, 2, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 0, 2, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 4, 0, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 3, 0, value);
		} else if(input_pin == 12) {
			set_or_clear_row_column(curr_matrix, 5, 0, value);
		}
	} else if(select_pin == 3) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 3, 7, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 3, 8, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 3, 9, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 3, 4, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 3, 10, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 3, 3, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 0, 3, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 3, 2, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 3, 1, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 6, 2, value);
		} else if(input_pin == 15) {
			set_or_clear_row_column(curr_matrix, 0, 7, value);
		}
	} else if(select_pin == 4) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 4, 7, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 4, 8, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 3, 13, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 4, 9, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 4, 4, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 4, 10, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 4, 3, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 0, 1, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 4, 2, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 4, 1, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 6, 6, value);
		}
	} else if(select_pin == 5) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 2, 7, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 2, 8, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 1, 9, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 2, 9, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 2, 4, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 2, 10, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 2, 3, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 1, 10, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 2, 2, value);
		} else if(input_pin == 9) {
			set_or_clear_row_column(curr_matrix, 1, 11, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 2, 1, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 1, 14, value);
		} else if(input_pin == 13) {
			set_or_clear_row_column(curr_matrix, 1, 13, value);
		} else if(input_pin == 15) {
			set_or_clear_row_column(curr_matrix, 0, 6, value);
		}
	} else if(select_pin == 6) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 5, 7, value);
		} else if(input_pin == 1) {
			set_or_clear_row_column(curr_matrix, 5, 8, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 4, 12, value);
		} else if(input_pin == 3) {
			set_or_clear_row_column(curr_matrix, 5, 9, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 5, 4, value);
		} else if(input_pin == 6) {
			set_or_clear_row_column(curr_matrix, 5, 3, value);
		} else if(input_pin == 8) {
			set_or_clear_row_column(curr_matrix, 5, 2, value);
		} else if(input_pin == 10) {
			set_or_clear_row_column(curr_matrix, 5, 1, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 6, 8, value);
		} else if(input_pin == 12) {
			set_or_clear_row_column(curr_matrix, 5, 11, value);
		} else if(input_pin == 13) {
			set_or_clear_row_column(curr_matrix, 0, 8, value);
		} else if(input_pin == 14) {
			set_or_clear_row_column(curr_matrix, 6, 7, value);
		}
	} else if(select_pin == 7) {
		if(input_pin == 0) {
			set_or_clear_row_column(curr_matrix, 5, 6, value);
		} else if(input_pin == 2) {
			set_or_clear_row_column(curr_matrix, 6, 4, value);
		} else if(input_pin == 4) {
			set_or_clear_row_column(curr_matrix, 5, 5, value);
		} else if(input_pin == 5) {
			set_or_clear_row_column(curr_matrix, 5, 10, value);
		} else if(input_pin == 7) {
			set_or_clear_row_column(curr_matrix, 7, 9, value);
		} else if(input_pin == 9) {
			set_or_clear_row_column(curr_matrix, 7, 10, value);
		} else if(input_pin == 11) {
			set_or_clear_row_column(curr_matrix, 6, 10, value);
		} else if(input_pin == 13) {
			set_or_clear_row_column(curr_matrix, 7, 8, value);
		} else if(input_pin == 15) {
			set_or_clear_row_column(curr_matrix, 6, 5, value);
		}
	}
}

void matrix_init_custom(void) {
    for(uint8_t i = 0; i < numberOfSelectPins; i++) {
		gpio_set_pin_output(selectPins[i]);
	}
	
    for(uint8_t i = 0; i < numberOfInputPins; i++) {
		gpio_set_pin_input_high(inputPins[i]);
	}
	
	gpio_set_pin_input_high(POWER_KEY_PIN);
	gpio_set_pin_input_high(FN_KEY_PIN);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

	uint8_t a, b, c;
	for(a = 0; a < numberOfSelectPins; a++) {
		uint8_t selectValue = ~(1 << a);
		for(b = 0; b < numberOfSelectPins; b++) {
			gpio_write_pin(selectPins[b], selectValue & (1 << b)); 
		}
		wait_ms(1);
		for(c = 0; c < numberOfInputPins; c++) {
			if(!gpio_read_pin(inputPins[c])) {
				ATOMIC_BLOCK_FORCEON {
					uprintf("Select: %d\t Input: %d\n", a, c);
					set_or_clear_matrix_location(curr_matrix, a, c, 1);
				}
			}else {
				ATOMIC_BLOCK_FORCEON {
					set_or_clear_matrix_location(curr_matrix, a, c, 0);
				}
			}
				
		}
	}
	
	if(!gpio_read_pin(POWER_KEY_PIN)) {
		ATOMIC_BLOCK_FORCEON {
			print("Physical power key\n");
			set_or_clear_row_column(curr_matrix, 0, 5, 1);
		}
	} else {
		ATOMIC_BLOCK_FORCEON {
			set_or_clear_row_column(curr_matrix, 0, 5, 0);
		}
	}
	
	if(!gpio_read_pin(FN_KEY_PIN)) {
		ATOMIC_BLOCK_FORCEON {
			print("Physical FN key\n");
			set_or_clear_row_column(curr_matrix, 6, 0, 1);
		}
	} else {
		ATOMIC_BLOCK_FORCEON {
			set_or_clear_row_column(curr_matrix, 6, 0, 0);
		}
	}
	

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));
    changed = debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    matrix_scan_kb();

    return changed;
}
