# Nano2 Button

The Nano2 has one physical button.

## Default Action

The default Nano2 keymap assigns the button to:

`DPI_CONFIG`

Pressing the button changes the DPI to the next setting.

The order is:

**600 → 900 → 1200 → 1600 → 2400 → 600**

## VIA

The button can be assigned another available keycode through the keymap.

The default firmware does **not** use the button for Drag Scroll.

Drag Scroll is a separate function.

## Implementation

The default button assignment is defined in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c`

The default keymap is:

`LAYOUT(DPI_CONFIG)`
