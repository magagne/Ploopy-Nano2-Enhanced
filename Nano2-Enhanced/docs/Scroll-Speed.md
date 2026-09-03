# Scroll Speed

Controls how fast the ball scrolls when DragScroll is active.

Nano2 Enhanced has five scroll speed settings:

| Value | Speed | Divisor |
|---:|---|---:|
| 0 | SLOWER | 128 |
| 1 | SLOW | 96 |
| 2 | NORMAL | 64 |
| 3 | FAST | 48 |
| 4 | FASTER | 32 |

The default is **NORMAL**.

A larger divisor means slower scrolling.

## Changing the speed

Use `SCROLL_SPEED` to cycle through the settings.

The selected speed is applied immediately by the firmware.

The selected speed is saved and restored when the Nano2 starts.

## Configuration

The speed can also be selected directly from the configuration menu.

## Implementation

The current speed is stored in:

`scroll_speed_index`

The values are stored in:

`scroll_speed_divisors`

The implementation is in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`
