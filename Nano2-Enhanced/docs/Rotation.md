# Rotation

Rotation changes the direction of the pointer.

Nano2 Enhanced has eight rotation settings:

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

The default is **0°**.

## Configuration

The rotation can be selected from the configuration menu.

The rotation can also be selected directly with the rotation keycodes.

The keycodes select the rotation. The firmware implements the rotation.

The selected rotation is saved and restored when the Nano2 starts.

## Implementation

The current rotation is stored in:

`rotation_index`

The firmware applies the rotation with:

`apply_rotation()`

The rotation is applied to pointer movement in:

`pointing_device_task_user()`

The rotation keycodes are:

`ROT_0` through `ROT_315`

The implementation is in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`
