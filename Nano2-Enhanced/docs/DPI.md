# DPI

Nano2 Enhanced has five DPI settings:

| Value | DPI |
|---:|---:|
| 0 | 600 |
| 1 | 900 |
| 2 | 1200 |
| 3 | 1600 |
| 4 | 2400 |

The default is **900 DPI**.

## Button

The default Nano2 button is `DPI_CONFIG`.

Press the button to move to the next DPI setting:

**600 → 900 → 1200 → 1600 → 2400 → 600**

## VIA

VIA can select any DPI setting directly.

The Nano2 uses VIA:

- Channel `0`
- DPI Value ID `3`

## Saving

The selected DPI is saved in the keyboard configuration.

It is restored when the Nano2 starts.

## Implementation

The generic Ploopy firmware provides the DPI system.

It stores the current DPI in:

`keyboard_config.dpi_config`

It applies the selected DPI with:

`pointing_device_set_cpi()`

Nano2 Enhanced sets its own DPI choices and default in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/config.h`

It uses:

`PLOOPY_DPI_OPTIONS`

and

`PLOOPY_DPI_DEFAULT`

The generic implementation remains in:

`keyboards/ploopyco/ploopyco.c`
