# Rotation

Rotation changes the direction of the pointer.

The Nano2 has eight rotation settings:

    0°
    45°
    90°
    135°
    180°
    225°
    270°
    315°

## Rotation settings

The settings are:

    0° ───► normal direction

    45° ──► turn the pointer direction 45°

    90° ──► turn the pointer direction 90°

    135° ─► turn the pointer direction 135°

    180° ─► turn the pointer direction 180°

    225° ─► turn the pointer direction 225°

    270° ─► turn the pointer direction 270°

    315° ─► turn the pointer direction 315°

## How it works

The Nano2 receives the ball movement:

    Ball
      │
      ▼
    X / Y movement
      │
      ▼
    Rotation
      │
      ▼
    New X / Y movement
      │
      ▼
    Pointer

The firmware changes the X and Y values according to the selected rotation.

## Configuration menu

The rotation can be selected from the configuration menu.

The menu uses a rotation value from:

    0 to 7

The values correspond to:

    0 = 0°
    1 = 45°
    2 = 90°
    3 = 135°
    4 = 180°
    5 = 225°
    6 = 270°
    7 = 315°

## Firmware

The rotation setting is stored in:

    rotation_index

The firmware applies the rotation with:

    apply_rotation()

The rotation is applied to the pointer movement with:

    pointing_device_task_user()

## Saving

The rotation setting is stored in the Nano2 user configuration.

The firmware reads the saved rotation when the Nano2 starts.

The configuration can also be saved through the configuration menu.

## Keycodes

The firmware provides eight rotation keycodes:

    ROT_0
    ROT_45
    ROT_90
    ROT_135
    ROT_180
    ROT_225
    ROT_270
    ROT_315

These keycodes select the corresponding rotation directly.

## Source

The implementation is in:

    keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c
