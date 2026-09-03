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

## Changing the DPI

The default button action is `DPI_CONFIG`.

Press the button to cycle through the DPI settings.

## Configuration

VIA can select any DPI setting directly.

The selected DPI is saved and restored when the Nano2 starts.

## Implementation

The generic Ploopy firmware stores the current DPI in `keyboard_config.dpi_config`.

It applies the selected DPI with `pointing_device_set_cpi()`.

Nano2 Enhanced sets its DPI choices and default in:

`keyboards/ploopyco/nano_2/rev2_003/keymaps/default/config.h`

It uses:

`PLOOPY_DPI_OPTIONS`

and

`PLOOPY_DPI_DEFAULT`

The generic implementation is in:

`keyboards/ploopyco/ploopyco.c`
