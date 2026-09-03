# DPI

DPI controls how fast the Ploopy pointer moves.

The Nano2 firmware has five DPI settings:

    600
    900
    1200
    1600
    2400

## Changing DPI

The DPI can be changed with:

- the Nano2 button
- the configuration menu

### Nano2 button

The button can cycle through the DPI settings.

Each press moves to the next setting.

The cycle is:

    600
     ↓
    900
     ↓
    1200
     ↓
    1600
     ↓
    2400
     ↓
    600

### Configuration menu

The configuration menu can be used to select a DPI preset directly.

This is useful when you want to choose a specific DPI instead of cycling through the settings.

## Saving the setting

When DPI is changed, the selected setting is saved in the keyboard configuration.

The selected DPI is therefore kept for the next use.

## Applying the setting

The firmware applies the selected value to the pointing device.

The selected DPI is converted to the corresponding CPI value used by the pointing-device hardware.

## Default

The default DPI setting is:

    900 DPI

## Firmware

The DPI settings are defined in:

    keyboards/ploopyco/ploopyco.c

The firmware stores the current setting in:

    keyboard_config.dpi_config

The DPI values are stored in:

    dpi_array

The firmware changes the setting with:

    cycle_dpi()

The selected value is then applied with:

    pointing_device_set_cpi()

## Simple view

    DPI SETTING
         │
         ├── Nano2 button ──► cycle
         │
         └── Configuration menu ──► select
                                      │
                                      ▼
                                  Ploopy CPI
                                      │
                                      ▼
                                   Pointer
