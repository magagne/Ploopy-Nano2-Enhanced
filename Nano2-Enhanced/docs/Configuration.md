# Nano2 Enhanced Configuration

Nano2 Enhanced has five configurable settings:

- **DPI** — controls pointer speed.

- **Rotation** — rotates the pointer direction.

- **Scroll Speed** — controls scroll speed.

- **Vertical Scrolling Only** — limits DragScroll to vertical scrolling.

- **Automatic Mouse Layer** — enables or disables AutoMouseLayer.

## Settings

### DPI

| Value | DPI |
|---:|---:|
| 0 | 600 |
| 1 | 900 |
| 2 | 1200 |
| 3 | 1400 |
| 4 | 1600 |
| 5 | 2400 |

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

### Vertical Scrolling Only

When **OFF**, DragScroll converts both X and Y ball movement into horizontal
and vertical scrolling.

When **ON**, DragScroll converts only Y ball movement into vertical scrolling.
X movement is ignored. The fractional Y-axis accumulator remains active for
smooth scrolling.

Vertical Scrolling Only does not activate or deactivate DragScroll. It is
independent of the mechanism used to activate DragScroll.

Rotation is applied before DragScroll processing, so Vertical Scrolling Only
operates on the already-rotated pointer coordinates.

The setting is **OFF by default**.

The DragScroll activation mechanisms are:

- **macOS — DragScroll-HID:** `S` / `s` Raw HID commands forwarded by
  `Ploopy-Bridge-HID`.
- **Windows — DragScroll-LED:** Scroll Lock LED state controls DragScroll.

See [DragScroll-HID.md](DragScroll-HID.md).

See [DragScroll-LED.md](DragScroll-LED.md).

### AutoMouseLayer

AutoMouseLayer allows physical Ploopy movement to activate the configured
Mouse layer on the keyboard.

When **Automatic Mouse Layer** is **ON**, the Ploopy generates the AutoMouseLayer
signal when physical movement occurs.

The transport depends on the operating system:

- **macOS — AutoMouseLayer-HID:** Raw HID `A 01` notification forwarded by
  `Ploopy-Bridge-HID`.
- **Windows — AutoMouseLayer-LED:** Caps Lock keyboard event followed by the
  Caps Lock LED state sent by Windows to the keyboard.

When **Automatic Mouse Layer** is **OFF**, the Ploopy does not generate the
AutoMouseLayer signal through either transport.

The keyboard owns the AutoMouseLayer timeout and layer activation logic.

The current keyboard timeout is **700 ms**.

See [AutoMouseLayer-HID.md](AutoMouseLayer-HID.md).

See [AutoMouseLayer-LED.md](AutoMouseLayer-LED.md).

## VIA Configuration

The Nano2 Enhanced VIA configuration provides five Ploopy settings:

- **DPI**

- **Rotation**

- **Scroll Speed**

- **Vertical Scrolling Only**

- **Automatic Mouse Layer**

The five settings use one VIA channel:

- Channel `0` — Nano2 settings
- Value ID `1` — Rotation
- Value ID `2` — Scroll Speed
- Value ID `3` — DPI
- Value ID `4` — Vertical Scrolling Only
- Value ID `5` — Automatic Mouse Layer

VIA can read and write these values directly.

**Vertical Scrolling Only** is **OFF by default**.

**Automatic Mouse Layer** is **ON by default**.

User settings are persisted in EEPROM and restored when the Nano2 starts.

## Where values are defined

| Setting | Values are defined in | Behavior |
|---|---|---|
| DPI | `config.h` | Generic Ploopy DPI system |
| Rotation | `keymap.c` | Nano2-specific |
| Scroll Speed | `keymap.c` | Nano2-specific |
| Vertical Scrolling Only | `keymap.c` | Nano2-specific |
| Automatic Mouse Layer | `keymap.c` | Nano2-specific |

DPI is different because Nano2 uses the existing Ploopy DPI system and only
overrides its choices.

`config.h` is the place to add or change DPI choices for Nano2 Enhanced.

## Saving

Rotation, Scroll Speed, Vertical Scrolling Only, and Automatic Mouse Layer are
saved in the Nano2 user configuration.

DPI is saved by the normal Ploopy DPI system.

All five settings are restored when the Nano2 starts.

## Keycodes

- `DPI_CONFIG` — cycle through DPI settings
- `ROT_0` to `ROT_315` — select rotation
- `SCROLL_SPEED` — cycle through scroll speeds

The keycodes select the settings. The firmware implements their behavior.

## Default Button

The Nano2 has one physical button.

The default keymap assigns that button to `DPI_CONFIG`.

One press changes the DPI to the next setting.
