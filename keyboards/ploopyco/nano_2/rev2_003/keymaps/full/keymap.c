#include QMK_KEYBOARD_H

#include <raw_hid.h>

extern bool is_drag_scroll;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(DPI_CONFIG)

};

bool via_command_kb(uint8_t *data, uint8_t length) {

    switch (data[0]) {

        case 'S':

            is_drag_scroll = true;

            dprintf("RAW HID: DRAG_SCROLL ON\n");

            return true;

        case 's':

            is_drag_scroll = false;

            dprintf("RAW HID: DRAG_SCROLL OFF\n");

            return true;

        default:

            return false;
    }
}
