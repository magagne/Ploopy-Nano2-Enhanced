# Nano2 Enhanced Configuration

Nano2 Enhanced has three settings:

- **DPI** — controls pointer speed.
- **Rotation** — rotates the pointer direction.
- **Scroll Speed** — controls scroll speed.

## Settings

### DPI

| Value | DPI |
|---:|---:|
| 0 | 600 |
| 1 | 900 |
| 2 | 1200 |
| 3 | 1600 |
| 4 | 2400 |

Default: **900 DPI**.

### Rotation

| Value | Rotation |
|---:|---:|
| 0 | 0° |
| 1 | 45° |
| 2 | 90° |
| 3 | 135° |
| 4 | 180° |
| 5 | 225° |
| 6 | 270° |
| 7 | 315° |

### Scroll Speed

| Value | Speed | Divisor |
|---:|---|---:|
| 0 | Slower | 128 |
| 1 | Slow | 96 |
| 2 | Normal | 64 |
| 3 | Fast | 48 |
| 4 | Faster | 32 |

## VIA Configuration

The three settings use one VIA channel:

- Channel `0` — Nano2 settings
- Value ID `1` — Rotation
- Value ID `2` — Scroll Speed
- Value ID `3` — DPI

VIA can read and write these values directly.

## Saving

Rotation and Scroll Speed are saved in the Nano2 user configuration.

DPI is saved by the normal Ploopy DPI system.

All three settings are restored when the Nano2 starts.

## Keycodes

- `DPI_CONFIG` — cycle through DPI settings
- `ROT_0` to `ROT_315` — set rotation
- `SCROLL_SPEED` — cycle through scroll speeds

## Default Button

The Nano2 has one physical button.

The default keymap assigns that button to `DPI_CONFIG`.

One press changes the DPI to the next setting.

## Implementation

The Nano2-specific configuration is implemented in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`

The Nano2 DPI choices and default are set in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/config.h`

The generic Ploopy DPI system is implemented in:

`keyboards/ploopyco/ploopyco.c`
