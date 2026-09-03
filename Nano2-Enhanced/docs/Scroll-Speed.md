# Scroll Speed

Controls how fast the ball scrolls when DragScroll is active.

Five settings:

- **SLOWER**
- **SLOW**
- **NORMAL**
- **FAST**
- **FASTER**

## Changing the speed

Use `SCROLL_SPEED` to cycle through the settings:

SLOWER → SLOW → NORMAL → FAST → FASTER → SLOWER

The selected speed is applied immediately and saved.

## Configuration

The speed can also be selected directly from the configuration menu.

Default: **NORMAL**

## Implementation

The scroll speed values are:

| Setting | Divisor |
|---|---:|
| SLOWER | 128 |
| SLOW | 96 |
| NORMAL | 64 |
| FAST | 48 |
| FASTER | 32 |

A larger divisor means slower scrolling.

The setting is stored in `scroll_speed_index`.

The values are stored in `scroll_speed_divisors`.

The implementation is in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`
