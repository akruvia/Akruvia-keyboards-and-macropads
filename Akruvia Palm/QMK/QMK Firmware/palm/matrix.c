// Copyright 2024 akruvia (@akruvia)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "quantum.h"
#include "pca9505.h"
#include "debounce.h"

#define PCA9505_0_ADDRESS 0x20
#define PCA9505_1_ADDRESS 0x21

#define NUMBER_OF_PCA9505 2
#define NUMBER_OF_BITS_IN_A_PC9505_PORT 8

extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values

enum {
    SWITCH_0,
    SWITCH_1,
    SWITCH_2,
    SWITCH_3,
    SWITCH_4,
    SWITCH_5,
    SWITCH_6,
    SWITCH_7,
    SWITCH_8,
    SWITCH_9,
    SWITCH_10,
    SWITCH_11,
    SWITCH_12,
    SWITCH_13,
    SWITCH_14,
    SWITCH_15,
    SWITCH_16,
    SWITCH_17,
    SWITCH_18,
    SWITCH_19,
    SWITCH_20,
    SWITCH_21,
    SWITCH_22,
    SWITCH_23,
    SWITCH_24,
    SWITCH_25,
    SWITCH_26,
    SWITCH_27,
    SWITCH_28,
    SWITCH_29,
    SWITCH_30,
    SWITCH_31,
    SWITCH_32,
    SWITCH_33,
    SWITCH_34,
    SWITCH_35,
    SWITCH_36,
    SWITCH_37,
    SWITCH_38,
    SWITCH_39,
    SWITCH_40,
    SWITCH_41,
    SWITCH_42,
    SWITCH_43,
    SWITCH_44,
    SWITCH_45,
    SWITCH_46,
    SWITCH_47,
    NO_SWITCH = 255
};

typedef struct {
    uint8_t address;
    uint8_t switches_in_input_ports[5][8];
} pca9505;

pca9505 pca9505_chip[NUMBER_OF_PCA9505] = {
    {
        PCA9505_0_ADDRESS,
        {
            {SWITCH_0, SWITCH_12, NO_SWITCH, SWITCH_28, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH},
            {SWITCH_13, SWITCH_15, SWITCH_14, SWITCH_16, NO_SWITCH, SWITCH_1, SWITCH_3, SWITCH_29},
            {SWITCH_17, SWITCH_5, SWITCH_4, SWITCH_2, SWITCH_24, SWITCH_36, SWITCH_41, NO_SWITCH},
            {NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, SWITCH_37},
            {SWITCH_38, NO_SWITCH, NO_SWITCH, SWITCH_40, SWITCH_39, SWITCH_25, SWITCH_27, SWITCH_26}
        }
    },
    {
        PCA9505_1_ADDRESS,
        {
            {SWITCH_18, SWITCH_6, SWITCH_20, SWITCH_34, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH},
            {NO_SWITCH, SWITCH_21, SWITCH_19, SWITCH_22, SWITCH_7, SWITCH_9, NO_SWITCH, SWITCH_35},
            {SWITCH_23, SWITCH_11, SWITCH_10, SWITCH_8, SWITCH_47, NO_SWITCH, NO_SWITCH, SWITCH_30},
            {SWITCH_42, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, NO_SWITCH, SWITCH_43},
            {SWITCH_44, NO_SWITCH, NO_SWITCH, SWITCH_45, SWITCH_46, SWITCH_33, SWITCH_32, SWITCH_31}
        }
    }
};

void pca9505_reset_all(void) {
    writePinLow(GP6);
    wait_ms(10);
    writePinHigh(GP6);
    wait_ms(10);
}

void pca9505_invert_all_input_port_logic(void) {
    for (uint8_t currentPCA9505 = 0; currentPCA9505 < NUMBER_OF_PCA9505; currentPCA9505++) {
        for (uint8_t currentPort = PCA9505_PORT0; currentPort <= PCA9505_PORT4; currentPort++) {
            pca9505_set_polarity(pca9505_chip[currentPCA9505].address, currentPort, ALL_INVERTED);
        }
    }
}

void pca9505_initialize_all(void) {
    pca9505_reset_all();
    pca9505_init(pca9505_chip[0].address);
    pca9505_init(pca9505_chip[1].address);
    pca9505_invert_all_input_port_logic();
}

void matrix_init_custom(void) {
    pca9505_initialize_all();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    uint8_t read_data;
    for (uint8_t currentPCA9505 = 0; currentPCA9505 < NUMBER_OF_PCA9505; currentPCA9505++) {
        for (uint8_t currentPort = PCA9505_PORT0; currentPort <= PCA9505_PORT4; currentPort++) {
            pca9505_readPins(pca9505_chip[currentPCA9505].address, currentPort, &read_data);
            for (uint8_t currentBit = 0; currentBit < NUMBER_OF_BITS_IN_A_PC9505_PORT; currentBit++) {
                uint8_t switchNumber = pca9505_chip[currentPCA9505].switches_in_input_ports[currentPort][currentBit];
                if (switchNumber != NO_SWITCH) {
                    uint8_t currentRow = switchNumber / MATRIX_COLS;
                    uint8_t currentCol = switchNumber % MATRIX_COLS;
                    if ((read_data >> currentBit) & 1) {
                        curr_matrix[currentRow] |= (1 << currentCol);
                    } else {
                        curr_matrix[currentRow] &= ~(1 << currentCol);
                    }
                }
            }
        }
    }

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));
    changed = debounce(raw_matrix, matrix, ROWS_PER_HAND, changed);
    matrix_scan_kb();

    return changed;
}