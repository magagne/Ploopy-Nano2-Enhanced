/* MATTHIEU */

#include QMK_KEYBOARD_H
#include <raw_hid.h>

extern bool is_drag_scroll;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(DPI_CONFIG)
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < 1) {
        return;
    }

    switch (data[0]) {
        case 'S':
            is_drag_scroll = true;
            dprintf("RAW HID: DRAG_SCROLL ON\n");
            break;

        case 's':
            is_drag_scroll = false;
            dprintf("RAW HID: DRAG_SCROLL OFF\n");
            break;

        default:
            dprintf("RAW HID: unknown command 0x%02X\n", data[0]);
            break;
    }
}
