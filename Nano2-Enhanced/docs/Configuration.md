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

Default: **0°**.

### Scroll Speed

| Value | Speed | Divisor |
|---:|---|---:|
| 0 | Slower | 128 |
| 1 | Slow | 96 |
| 2 | Normal | 64 |
| 3 | Fast | 48 |
| 4 | Faster | 32 |

Default: **NORMAL**.

## Where values are defined

| Setting | Values are defined in | Behavior |
|---|---|---|
| DPI | `config.h` | Generic Ploopy DPI system |
| Rotation | `keymap.c` | Nano2-specific |
| Scroll Speed | `keymap.c` | Nano2-specific |

DPI is different because Nano2 uses the existing Ploopy DPI system and only overrides its choices.

`config.h` is the place to add or change DPI choices for Nano2 Enhanced.

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
- `ROT_0` to `ROT_315` — select rotation
- `SCROLL_SPEED` — cycle through scroll speeds

The keycodes select the settings. The firmware implements their behavior.

## Default Button

The Nano2 has one physical button.

The default keymap assigns that button to `DPI_CONFIG`.

One press changes the DPI to the next setting.
