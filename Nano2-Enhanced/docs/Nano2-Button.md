# Nano2 Button

The Nano2 has one physical button.

## Default Action

The default button action is `DPI_CONFIG`.

Press the button to cycle through the DPI settings.

## Configuration

The button can be assigned another available keycode through the keymap.

The default firmware does not use the button for Drag Scroll.

Drag Scroll is a separate function.

## Implementation

The default button assignment is defined in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`

The default keymap is:

`LAYOUT(DPI_CONFIG)`
