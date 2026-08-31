#include QMK_KEYBOARD_H

#include <raw_hid.h>

extern bool is_drag_scroll;

/*
 * PROOF OF CONCEPT:
 *
 * Rotate the physical Nano-2 sensor coordinates by -45 degrees
 * before Ploopy's existing pointing-device processing.
 *
 * No VIA configuration yet.
 * No EEPROM.
 * No menu.
 *
 * This is deliberately hardcoded so we can first prove that
 * coordinate rotation actually works on the Nano-2.
 */

static inline int16_t rotate_45_scale(int16_t value) {
    return (value * 181) / 256;
}

static inline int8_t clamp_mouse_xy(int16_t value) {
    if (value < -127) {
        return -127;
    }

    if (value > 127) {
        return 127;
    }

    return (int8_t)value;
}

/*
 * -45 degree rotation:
 *
 * new_x =  cos(45) * x + sin(45) * y
 * new_y = -sin(45) * x + cos(45) * y
 *
 * Using 181/256 ~= 0.707.
 */
static report_mouse_t apply_rotation(report_mouse_t mouse_report) {
    int16_t x = mouse_report.x;
    int16_t y = mouse_report.y;

    int16_t new_x = rotate_45_scale(x + y);
    int16_t new_y = rotate_45_scale(-x + y);

    mouse_report.x = clamp_mouse_xy(new_x);
    mouse_report.y = clamp_mouse_xy(new_y);

    return mouse_report;
}

/*
 * Sensor report enters here before Ploopy's existing
 * pointing_device_task_kb() processing.
 */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return apply_rotation(mouse_report);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(DPI_CONFIG)
};

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t response[length];
    memset(response, 0, length);

    switch (data[0]) {
        case 'S':
            is_drag_scroll = true;
            response[0] = 'O';
            response[1] = 'N';
            raw_hid_send(response, length);
            dprintf("RAW HID: DRAG_SCROLL ON\n");
            return true;

        case 's':
            is_drag_scroll = false;
            response[0] = 'O';
            response[1] = 'F';
            response[2] = 'F';
            raw_hid_send(response, length);
            dprintf("RAW HID: DRAG_SCROLL OFF\n");
            return true;

        default:
            return false;
    }
}
