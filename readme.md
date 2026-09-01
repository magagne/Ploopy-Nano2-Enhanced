# Ploopy-VIA

Custom QMK/VIAL firmware for the **Ploopy Nano 2 Rev2.003**.

This repository extends the existing Ploopy firmware with a configurable **VIA / Raw HID interface**, **Scroll Lock / Drag Scroll integration**, and **pointer rotation**.

The project is designed around a single Nano-2 firmware configuration. The different functions are integrated into the same firmware rather than maintained as separate keymaps.

---

## Current Features

The current Nano-2 firmware provides:

* **VIAL support**
* **Raw HID support**
* **Scroll Lock / Drag Scroll control**
* **Scroll Lock LED state integration**
* **Configurable pointer rotation**
* **Persistent rotation configuration through VIA EEPROM**
* **VIA device definition for the Nano 2**

The firmware is based on the existing Ploopy pointing-device implementation rather than replacing it.

---

# Architecture

The project has three main parts:

```text
Corne
  │
  │ Raw HID Drag Scroll command
  │
  ▼
Corne-Ploopy-Bridge
  │
  │ VIA / Raw HID
  │
  ▼
Ploopy Nano 2
  │
  ├── Pointer rotation
  │
  ▼
Rotated X / Y
  │
  ├── Normal pointer movement
  │
  └── Existing Ploopy Drag Scroll
          │
          ▼
     Scroll Lock / LED
```

The important architectural requirement is that **pointer rotation is applied to the pointing-device X/Y coordinates before they reach the existing Ploopy processing**.

This means that normal pointer movement and Drag Scroll operate in the same rotated coordinate system.

---

# Ploopy Nano 2

The Nano 2 firmware is based on the Ploopy Nano 2 Rev2.003 QMK keyboard definition:

```text
keyboards/ploopyco/nano_2/rev2_003/
```

The custom firmware uses a single keymap:

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/default/
```

The custom keymap contains the integrated functionality for:

* VIAL
* Raw HID
* Drag Scroll / Scroll Lock control
* pointer rotation
* VIA configuration

There are no separate `scrolllock`, `rotation`, or `full` keymap directories.

---

# VIAL

The Nano 2 firmware is configured for VIAL.

The VIAL device definition is:

```text
_Firmware/Nano-2/nano2.json
```

This definition describes the Nano 2 to VIAL and allows the firmware's keymap and custom keycodes to be configured through the VIAL interface.

The firmware therefore combines the QMK functionality with a VIAL-compatible configuration without requiring separate firmware variants.

---

# Scroll Lock / Drag Scroll

The Ploopy firmware already contains the actual Drag Scroll implementation.

This project does **not** replace the Ploopy Drag Scroll engine.

Instead, the custom firmware provides an external control path that changes the existing Ploopy Drag Scroll state.

The control flow is:

```text
Keyboard
   │
   │ Raw HID
   ▼
via_command_kb()
   │
   ▼
is_drag_scroll
   │
   ▼
Existing Ploopy Drag Scroll
```

The Raw HID protocol uses two command bytes:

```text
'S'  (0x53) → Drag Scroll ON

's'  (0x73) → Drag Scroll OFF
```

This allows the Corne and the Ploopy to communicate using a very small and stable protocol.

---

# Scroll Lock LED

The Scroll Lock state is integrated at the common Ploopy firmware level.

The implementation is located in:

```text
keyboards/ploopyco/ploopyco.c
```

The existing Ploopy LED update hook receives the host Scroll Lock state:

```c
bool led_update_kb(led_t led_state) {
    is_drag_scroll = led_state.scroll_lock;
    return led_update_user(led_state);
}
```

This connects the host's Scroll Lock state to the Ploopy's existing Drag Scroll mechanism.

The project therefore does not create:

* a second Drag Scroll engine
* a separate Scroll Lock implementation
* a separate LED system

Instead, it reuses the functionality already present in the Ploopy firmware.

The Scroll Lock / Drag Scroll behavior has been **tested and confirmed working on the Nano 2**.

---

# Pointer Rotation

The firmware provides configurable rotation of the pointing-device coordinates.

The supported angles are:

```text
0°
45°
90°
135°
180°
225°
270°
315°
```

Rotation is applied to the X/Y coordinates before normal Ploopy pointing-device processing.

For example, the 90° rotation uses:

```text
X' = Y
Y' = -X
```

The 45° rotations use an integer approximation of `1 / sqrt(2)` suitable for the microcontroller.

The rotation implementation is part of the main Nano-2 firmware rather than a separate keymap.

---

# Rotation Configuration

The selected rotation is configurable through VIA.

The rotation value is stored using VIA's custom EEPROM configuration:

```text
VIA_EEPROM_CUSTOM_CONFIG_SIZE = 1
```

This allows the selected rotation to persist across firmware restarts.

The firmware can therefore retain the user's selected physical orientation without requiring the rotation to be hard-coded into the firmware.

---

# Rotation and Drag Scroll

Rotation and Drag Scroll must use the same coordinate system.

The processing order is:

```text
Physical sensor X / Y
        │
        ▼
Pointer rotation
        │
        ▼
Rotated X / Y
        │
        ├──────────────► Normal pointer movement
        │
        └──────────────► Existing Ploopy Drag Scroll
```

For example:

```text
Physical X / Y
      │
      ▼
   90° rotation
      │
      ▼
Rotated X / Y
      │
      ├── Pointer movement
      │
      └── Drag Scroll
```

This is important because rotating only normal pointer movement while leaving Drag Scroll unrotated would produce two different coordinate systems.

The intended behavior is that **Drag Scroll follows exactly the same physical rotation as the pointer**.

---

# Raw HID Protocol

The Drag Scroll protocol intentionally uses two simple command bytes:

```text
0x53 / 'S' → DRAG_SCROLL_ON

0x73 / 's' → DRAG_SCROLL_OFF
```

The complete communication path is:

```text
Corne
  │
  │ 'S' / 's'
  ▼
Corne-Ploopy-Bridge
  │
  │ VIA / Raw HID
  ▼
Ploopy Nano 2
  │
  ▼
via_command_kb()
  │
  ▼
is_drag_scroll
  │
  ▼
Existing Ploopy Drag Scroll
```

The keyboard determines when Drag Scroll should change.

The bridge transports the command.

The Ploopy firmware translates the command into the existing Drag Scroll state.

---

# Firmware Organization

The custom Nano-2 firmware is intentionally kept as a single integrated firmware.

The important files are:

```text
_Firmware/Nano-2/
    ├── BuildFirmware.sh
    └── nano2.json

keyboards/ploopyco/
    ├── ploopyco.c
    │
    └── nano_2/
        └── rev2_003/
            └── keymaps/
                └── default/
                    └── keymap.c
```

The exact contents of the Nano-2 keymap may evolve as additional functionality is added.

The architecture deliberately avoids maintaining multiple firmware variants for individual features.

---

# Build

The Nano-2 firmware is built from the repository using the project build script:

```bash
./_Firmware/Nano-2/BuildFirmware.sh
```

The script handles the firmware build using the Nano-2 Rev2.003 target and the project's current configuration.

The direct QMK target is:

```text
ploopyco/nano_2/rev2_003
```

The active keymap is:

```text
default
```

The equivalent direct QMK build command is:

```bash
qmk compile -kb ploopyco/nano_2/rev2_003 -km default
```

---

# Flashing

The firmware can be flashed using the QMK CLI:

```bash
qmk flash -kb ploopyco/nano_2/rev2_003 -km default
```

Alternatively, if the build process produces a UF2 firmware file, the Nano 2 can be placed into its bootloader and the generated `.uf2` file can be copied to the bootloader volume.

The exact generated firmware filename should be taken from the build output rather than assumed.

---

# Development Workflow

The project is now developed as a **single firmware**.

The development cycle is:

```text
Modify firmware
      │
      ▼
Build Nano 2 firmware
      │
      ▼
Flash Nano 2
      │
      ▼
Test VIAL / pointer / Drag Scroll
      │
      ▼
Commit verified changes
```

Individual features are no longer isolated into separate keymap directories.

This makes the repository reflect the firmware that is actually being developed and used.

---

# Firmware Separation

The normal Ploopy firmware continues to provide:

* pointing-device processing
* Drag Scroll implementation
* Scroll Lock handling
* Scroll Lock LED behavior
* other Ploopy functionality

This project adds:

* VIAL configuration
* Raw HID Drag Scroll control
* configurable pointer rotation
* Nano-2-specific firmware integration

The design goal is to reuse the existing Ploopy functionality wherever possible instead of duplicating it.

---

# Project Structure

The relevant parts of the repository are:

```text
Ploopy-VIA/

├── _Firmware/
│   └── Nano-2/
│       ├── BuildFirmware.sh
│       └── nano2.json
│
└── keyboards/
    └── ploopyco/
        ├── ploopyco.c
        │
        └── nano_2/
            └── rev2_003/
                └── keymaps/
                    └── default/
                        └── keymap.c
```

The common Ploopy implementation remains separate from the Nano-2-specific keymap.

This allows the custom Nano-2 functionality to build on top of the existing Ploopy firmware architecture.

---

# Related Projects

The complete system uses three projects.

## Corne — QMK / VIAL

The QMK/VIAL Corne firmware contains the custom Drag Scroll module.

The module generates the Raw HID commands used by the Ploopy:

```text
'S' → Drag Scroll ON

's' → Drag Scroll OFF
```

## Corne — ZMK

The ZMK implementation provides equivalent Drag Scroll behavior using ZMK.

It uses the same Raw HID protocol as the QMK/VIAL implementation.

The ZMK implementation is independent of the Ploopy firmware.

## Corne-Ploopy-Bridge

The host-side bridge receives the Raw HID commands from the Corne and forwards them to the Ploopy through its VIA / Raw HID interface.

The bridge is maintained separately from this repository.

---

# Design Goals

The project follows a few simple principles:

### Reuse the Ploopy firmware

The existing Ploopy Drag Scroll implementation should remain the source of truth for Drag Scroll behavior.

### Keep the protocol simple

The external Drag Scroll protocol uses only two command bytes:

```text
'S' / 's'
```

### Keep pointer and Drag Scroll coordinates consistent

Rotation is applied before both normal pointer movement and Drag Scroll processing.

### Use one firmware configuration

The Nano 2 is developed as one integrated firmware rather than a collection of feature-specific keymaps.

### Keep the customization isolated

The project adds only the functionality required for VIA control, Raw HID communication, and pointer rotation while leaving the rest of the Ploopy firmware intact.

```
```
