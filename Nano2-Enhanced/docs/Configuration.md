# Configuration

The Nano2 has settings for:

    DPI
    Rotation
    Scroll Speed

The configuration menu can change these settings.

## DPI

DPI uses five settings:

    0 = 600
    1 = 900
    2 = 1200
    3 = 1600
    4 = 2400

The default is:

    900 DPI

## Rotation

Rotation uses eight settings:

    0 = 0°
    1 = 45°
    2 = 90°
    3 = 135°
    4 = 180°
    5 = 225°
    6 = 270°
    7 = 315°

## Scroll Speed

Scroll Speed uses five settings:

    0 = NORMAL
    1 = SLOW
    2 = SLOWER
    3 = FAST
    4 = FASTER

## Configuration values

The Nano2 configuration menu uses three value IDs:

    1 = Rotation
    2 = Scroll Speed
    3 = DPI

These values are handled by the Nano2 firmware.

## Saving

The Nano2 saves:

    Rotation
    Scroll Speed

in the user configuration.

The firmware reads these settings when the Nano2 starts.

DPI is stored separately in the keyboard configuration.

## Keycodes

The firmware also provides keycodes for changing settings.

Rotation:

    ROT_0
    ROT_45
    ROT_90
    ROT_135
    ROT_180
    ROT_225
    ROT_270
    ROT_315

Scroll Speed:

    SCROLL_SPEED

DPI:

    DPI_CONFIG

A keycode can be placed on a key or button by a keymap.

## Default keymap

The default Nano2 keymap currently contains:

    DPI_CONFIG

The other configuration keycodes are provided by the firmware but are not placed on a key in the default keymap.

## Simple view

    CONFIGURATION MENU
           │
           ├── DPI ─────────────► Ploopy DPI
           │
           ├── Rotation ────────► Pointer direction
           │
           └── Scroll Speed ────► Scroll speed

The configuration menu changes the Nano2 settings directly.

## Source

The configuration implementation is in:

    keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c

The DPI implementation is also in:

    keyboards/ploopyco/ploopyco.c
