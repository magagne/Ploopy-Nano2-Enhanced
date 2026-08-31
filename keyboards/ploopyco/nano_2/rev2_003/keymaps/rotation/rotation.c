#include QMK_KEYBOARD_H
#include "via.h"

enum {
    id_ploopy_rotation = 1,
};

enum {
    ROTATION_0 = 0,
    ROTATION_45,
    ROTATION_90,
    ROTATION_135,
    ROTATION_180,
    ROTATION_225,
    ROTATION_270,
    ROTATION_315,
    ROTATION_COUNT
};

static uint8_t rotation_index = ROTATION_0;

/*
 * 181 / 256 = 0.70703125, a close integer approximation of 1 / sqrt(2).
 *
 * The 90-degree convention matches QMK's built-in pointing-device rotation:
 *
 *     90°: X' = Y
 *          Y' = -X
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

static report_mouse_t apply_rotation(report_mouse_t mouse_report) {
    int16_t x = mouse_report.x;
    int16_t y = mouse_report.y;
    int16_t new_x;
    int16_t new_y;

    switch (rotation_index) {
        case ROTATION_45:
            new_x = rotate_45_scale(x + y);
            new_y = rotate_45_scale(-x + y);
            break;

        case ROTATION_90:
            new_x = y;
            new_y = -x;
            break;

        case ROTATION_135:
            new_x = rotate_45_scale(-x + y);
            new_y = rotate_45_scale(-x - y);
            break;

        case ROTATION_180:
            new_x = -x;
            new_y = -y;
            break;

        case ROTATION_225:
            new_x = rotate_45_scale(-x - y);
            new_y = rotate_45_scale(x - y);
            break;

        case ROTATION_270:
            new_x = -y;
            new_y = x;
            break;

        case ROTATION_315:
            new_x = rotate_45_scale(x - y);
            new_y = rotate_45_scale(x + y);
            break;

        case ROTATION_0:
        default:
            return mouse_report;
    }

    mouse_report.x = clamp_mouse_xy(new_x);
    mouse_report.y = clamp_mouse_xy(new_y);

    return mouse_report;
}

void via_init_kb(void) {
    rotation_index = ROTATION_0;

    if (via_eeprom_is_valid()) {
        via_read_custom_config(&rotation_index, 0, 1);

        if (rotation_index >= ROTATION_COUNT) {
            rotation_index = ROTATION_0;
        }
    }
}

/*
 * This callback is invoked by Ploopy's pointing-device code before
 * its Drag Scroll conversion. Therefore Drag Scroll automatically
 * receives the rotated X/Y coordinates.
 */
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return apply_rotation(mouse_report);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &data[0];
    uint8_t *channel_id = &data[1];
    uint8_t *value_id_and_data = &data[2];

    if (*channel_id != id_custom_channel) {
        *command_id = id_unhandled;
        return;
    }

    switch (*command_id) {
        case id_custom_set_value:
            if (value_id_and_data[0] == id_ploopy_rotation) {
                if (value_id_and_data[1] < ROTATION_COUNT) {
                    rotation_index = value_id_and_data[1];
                } else {
                    *command_id = id_unhandled;
                }
            } else {
                *command_id = id_unhandled;
            }
            break;

        case id_custom_get_value:
            if (value_id_and_data[0] == id_ploopy_rotation) {
                value_id_and_data[1] = rotation_index;
            } else {
                *command_id = id_unhandled;
            }
            break;

        case id_custom_save:
            via_update_custom_config(&rotation_index, 0, 1);
            break;

        default:
            *command_id = id_unhandled;
            break;
    }
}
