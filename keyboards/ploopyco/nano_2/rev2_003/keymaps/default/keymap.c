#include QMK_KEYBOARD_H

#include <raw_hid.h>

extern bool is_drag_scroll;

enum custom_keycodes {
    ROT_0 = SAFE_RANGE,
    ROT_45,
    ROT_90,
    ROT_135,
    ROT_180,
    ROT_225,
    ROT_270,
    ROT_315,
};

static uint8_t rotation_index = 0;

static inline int8_t clamp_mouse_xy(int16_t value) {
    if (value < -127) {
        return -127;
    }
    if (value > 127) {
        return 127;
    }
    return (int8_t)value;
}

static report_mouse_t apply_rotation(report_mouse_t mouse_report) {
    int16_t x = mouse_report.x;
    int16_t y = mouse_report.y;
    int16_t new_x;
    int16_t new_y;

    switch (rotation_index) {
        case 0:
            /* 0 degrees */
            new_x = x;
            new_y = y;
            break;

        case 1:
            /* 45 degrees */
            new_x = (x * 181 - y * 181) / 256;
            new_y = (x * 181 + y * 181) / 256;
            break;

        case 2:
            /* 90 degrees */
            new_x = -y;
            new_y = x;
            break;

        case 3:
            /* 135 degrees */
            new_x = (-x * 181 - y * 181) / 256;
            new_y = (x * 181 - y * 181) / 256;
            break;

        case 4:
            /* 180 degrees */
            new_x = -x;
            new_y = -y;
            break;

        case 5:
            /* 225 degrees */
            new_x = (-x * 181 + y * 181) / 256;
            new_y = (-x * 181 - y * 181) / 256;
            break;

        case 6:
            /* 270 degrees */
            new_x = y;
            new_y = -x;
            break;

        case 7:
            /* 315 degrees */
            new_x = (x * 181 + y * 181) / 256;
            new_y = (-x * 181 + y * 181) / 256;
            break;

        default:
            new_x = x;
            new_y = y;
            break;
    }

    mouse_report.x = clamp_mouse_xy(new_x);
    mouse_report.y = clamp_mouse_xy(new_y);

    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return apply_rotation(mouse_report);
}

#define ROTATION_CHANNEL 0
#define ROTATION_VALUE_ID 1

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id != ROTATION_CHANNEL) {
        *command_id = id_unhandled;
        return;
    }

    switch (*command_id) {
        case id_custom_set_value:
            if (value_id_and_data[0] == ROTATION_VALUE_ID) {
                if (value_id_and_data[1] < 8) {
                    rotation_index = value_id_and_data[1];
                }
            }
            break;

        case id_custom_get_value:
            if (value_id_and_data[0] == ROTATION_VALUE_ID) {
                value_id_and_data[1] = rotation_index;
            }
            break;

        case id_custom_save:
            /* Rotation is currently volatile and is not saved. */
            break;

        default:
            *command_id = id_unhandled;
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case ROT_0:
            rotation_index = 0;
            return false;

        case ROT_45:
            rotation_index = 1;
            return false;

        case ROT_90:
            rotation_index = 2;
            return false;

        case ROT_135:
            rotation_index = 3;
            return false;

        case ROT_180:
            rotation_index = 4;
            return false;

        case ROT_225:
            rotation_index = 5;
            return false;

        case ROT_270:
            rotation_index = 6;
            return false;

        case ROT_315:
            rotation_index = 7;
            return false;

        default:
            return true;
    }
}

/*
 * Existing Drag Scroll RAW HID implementation.
 */
bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t response[length];
    memset(response, 0, length);

    switch (data[0]) {
        case 'S':
            is_drag_scroll = true;

            response[0] = 'O';
            response[1] = 'N';

            raw_hid_send(response, length);

            return true;

        case 's':
            is_drag_scroll = false;

            response[0] = 'O';
            response[1] = 'F';
            response[2] = 'F';

            raw_hid_send(response, length);

            return true;

        default:
            return false;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(DPI_CONFIG)
};
