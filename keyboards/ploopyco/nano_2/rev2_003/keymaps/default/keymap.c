#include QMK_KEYBOARD_H

#include <raw_hid.h>

extern bool is_drag_scroll;
extern bool is_vertical_scrolling_only;

/*
 * Nano-2 has a single physical button.
 * The default button action is DPI_CONFIG.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(DPI_CONFIG)
};

#define ROTATION_COUNT 8
#define SETTINGS_CHANNEL 0
#define ROTATION_VALUE_ID 1
#define SCROLL_SPEED_VALUE_ID 2
#define DPI_VALUE_ID 3
#define VERTICAL_SCROLLING_ONLY_VALUE_ID 4
#define USER_CONFIG_MAGIC 0xA5

enum rotation_angle {
    ROT_0 = SAFE_RANGE,
    ROT_45,
    ROT_90,
    ROT_135,
    ROT_180,
    ROT_225,
    ROT_270,
    ROT_315,
};

enum scroll_speed {
    SCROLL_SPEED_SLOWER = 0,
    SCROLL_SPEED_SLOW,
    SCROLL_SPEED_NORMAL,
    SCROLL_SPEED_FAST,
    SCROLL_SPEED_FASTER,
};

static const uint8_t scroll_speed_divisors[] = {
    [SCROLL_SPEED_SLOWER] = 128,
    [SCROLL_SPEED_SLOW]   = 96,
    [SCROLL_SPEED_NORMAL] = 64,
    [SCROLL_SPEED_FAST]   = 48,
    [SCROLL_SPEED_FASTER] = 32,
};

static uint8_t rotation_index = 0;
static uint8_t scroll_speed_index = SCROLL_SPEED_NORMAL;


typedef union {
    uint32_t raw;
    struct {
        uint8_t rotation_index;
        uint8_t scroll_speed_index;
        uint8_t vertical_scrolling_only;
        uint8_t magic;
    };
} nano2_user_config_t;

static void apply_scroll_speed(void) {
    float divisor = scroll_speed_divisors[scroll_speed_index];

    ploopy_dragscroll_divisor_h = divisor;
    ploopy_dragscroll_divisor_v = divisor;
}

static void save_user_config(void) {
    nano2_user_config_t config;
    config.raw = 0;
    config.rotation_index = rotation_index;
    config.scroll_speed_index = scroll_speed_index;
    config.vertical_scrolling_only = is_vertical_scrolling_only ? 1 : 0;
    config.magic = USER_CONFIG_MAGIC;

    eeconfig_update_user(config.raw);
}

void keyboard_post_init_user(void) {
    nano2_user_config_t config;
    config.raw = eeconfig_read_user();

    if (config.magic != USER_CONFIG_MAGIC) {
        rotation_index = 0;
        scroll_speed_index = SCROLL_SPEED_NORMAL;
        is_vertical_scrolling_only = false;
        save_user_config();
    } else {
        rotation_index = (config.rotation_index < ROTATION_COUNT) ? config.rotation_index : 0;

        scroll_speed_index =
            (config.scroll_speed_index < ARRAY_SIZE(scroll_speed_divisors))
                ? config.scroll_speed_index
                : SCROLL_SPEED_NORMAL;

        is_vertical_scrolling_only = config.vertical_scrolling_only ? true : false;
    }

    apply_scroll_speed();
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
        case 0:
            new_x = x;
            new_y = y;
            break;

        case 1:
            new_x = (x * 181 - y * 181) / 256;
            new_y = (x * 181 + y * 181) / 256;
            break;

        case 2:
            new_x = -y;
            new_y = x;
            break;

        case 3:
            new_x = (-x * 181 - y * 181) / 256;
            new_y = (x * 181 - y * 181) / 256;
            break;

        case 4:
            new_x = -x;
            new_y = -y;
            break;

        case 5:
            new_x = (-x * 181 + y * 181) / 256;
            new_y = (-x * 181 - y * 181) / 256;
            break;

        case 6:
            new_x = y;
            new_y = -x;
            break;

        case 7:
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


void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id != SETTINGS_CHANNEL) {
        *command_id = id_unhandled;
        return;
    }

    switch (*command_id) {
        case id_custom_set_value:
            if (value_id_and_data[0] == ROTATION_VALUE_ID) {
                if (value_id_and_data[1] < ROTATION_COUNT) {
                    rotation_index = value_id_and_data[1];
                }
            } else if (value_id_and_data[0] == SCROLL_SPEED_VALUE_ID) {
                if (value_id_and_data[1] < ARRAY_SIZE(scroll_speed_divisors)) {
                    scroll_speed_index = value_id_and_data[1];
                    apply_scroll_speed();
                }
            } else if (value_id_and_data[0] == DPI_VALUE_ID) {
                if (value_id_and_data[1] < 5) {
                    keyboard_config.dpi_config = value_id_and_data[1];
                    eeconfig_update_kb(keyboard_config.raw);
                    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
                }
            } else if (value_id_and_data[0] == VERTICAL_SCROLLING_ONLY_VALUE_ID) {
                if (value_id_and_data[1] <= 1) {
                    is_vertical_scrolling_only = value_id_and_data[1] != 0;
                }
            }
            break;

        case id_custom_get_value:
            if (value_id_and_data[0] == ROTATION_VALUE_ID) {
                value_id_and_data[1] = rotation_index;
            } else if (value_id_and_data[0] == SCROLL_SPEED_VALUE_ID) {
                value_id_and_data[1] = scroll_speed_index;
            } else if (value_id_and_data[0] == DPI_VALUE_ID) {
                value_id_and_data[1] = keyboard_config.dpi_config;
            } else if (value_id_and_data[0] == VERTICAL_SCROLLING_ONLY_VALUE_ID) {
                value_id_and_data[1] = is_vertical_scrolling_only ? 1 : 0;
            }
            break;

        case id_custom_save:
            save_user_config();
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
        case ROT_45:
        case ROT_90:
        case ROT_135:
        case ROT_180:
        case ROT_225:
        case ROT_270:
        case ROT_315:
            rotation_index = keycode - ROT_0;
            return false;

        case SCROLL_SPEED:
            scroll_speed_index++;

            if (scroll_speed_index >= ARRAY_SIZE(scroll_speed_divisors)) {
                scroll_speed_index = SCROLL_SPEED_NORMAL;
            }

            apply_scroll_speed();
            save_user_config();

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
