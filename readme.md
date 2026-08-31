# Ploopy-VIA

Custom QMK firmware configuration for the **Ploopy Nano 2 Rev2.003**.

This repository provides a custom **VIA / Raw HID interface** for controlling the Ploopy's existing Drag Scroll functionality and adds configurable **pointer rotation**.

The project currently maintains three Nano-2 keymaps:

* `scrolllock` — standalone Drag Scroll / Scroll Lock integration
* `rotation` — standalone pointer rotation
* `full` — combined firmware containing both functions

The standalone versions are intentionally retained during development and hardware validation so that each function can be tested independently if troubleshooting is required.

The `full` firmware is the intended final firmware.

---

## What This Repository Does

The Ploopy Nano 2 already contains the core Drag Scroll implementation.

This project adds two pieces of functionality around the existing Ploopy firmware:

1. **Drag Scroll / Scroll Lock control through VIA Raw HID**
2. **Configurable pointer rotation**

The Drag Scroll integration does not replace the Ploopy's existing Drag Scroll engine.

The rotation implementation transforms the pointing-device X/Y coordinates before they reach the Ploopy Drag Scroll processing.

This is important because **Drag Scroll must use the same rotated coordinate system as normal pointer movement**.

Therefore:

```text
Nano 2 sensor
     │
     ▼
X / Y movement
     │
     ▼
Pointer rotation
     │
     ▼
Rotated X / Y
     │
     ▼
Ploopy pointing-device processing
     │
     ├── Normal pointer movement
     │
     └── Drag Scroll
             │
             ▼
       Scroll Lock movement
```

The final firmware therefore provides a consistent coordinate system for both pointer movement and Drag Scroll.

---

## System Architecture

The complete system consists of the Corne, the host bridge, and the Ploopy.

```text
CORNE SIDE
──────────

QMK / VIAL
    │
    └── modules/drag_scroll/
          ├── drag_scroll.c
          └── drag_scroll.h
                 │
                 │ Raw HID 'S' / 's'
                 │
ZMK
    │
    └── equivalent Drag Scroll behavior
                 │
                 │ Raw HID 'S' / 's'
                 ▼
        Corne-Ploopy-Bridge
                 │
                 │ HID command
                 ▼

PLOOPY SIDE
───────────

Ploopy-VIA
    │
    ├── Drag Scroll / Scroll Lock control
    │
    └── Pointer rotation
             │
             ▼
      Ploopy pointing-device
      processing
             │
             ├── Normal pointer
             │
             └── Drag Scroll
                    │
                    ▼
              Scroll Lock / LED
```

Each component has a separate responsibility.

---

## Corne — QMK / VIAL

The QMK/VIAL implementation contains the custom `drag_scroll` module:

```text
src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/drag_scroll/

├── drag_scroll.c
└── drag_scroll.h
```

The module detects the Drag Scroll action and generates the corresponding Raw HID command.

---

## Corne — ZMK

The ZMK implementation provides equivalent Drag Scroll behavior using ZMK's HID/behavior mechanism.

The ZMK implementation is independent of the Ploopy firmware.

It generates the same protocol commands used by the QMK/VIAL implementation:

```text
'S'  (0x53) → Drag Scroll ON

's'  (0x73) → Drag Scroll OFF
```

This keeps the host-side protocol independent of the keyboard firmware.

---

## Corne-Ploopy-Bridge

The host-side bridge receives the Raw HID command from the Corne.

It forwards the corresponding command to the Ploopy through its VIA/Raw HID interface.

The bridge does not need to know whether the command originated from QMK/VIAL or ZMK.

---

# Ploopy Nano 2

The Ploopy side contains the custom keymaps and firmware builders.

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/

├── scrolllock/
├── rotation/
└── full/
```

The three keymaps have different purposes.

---

## Scroll Lock / Drag Scroll

The `scrolllock` keymap provides the external control path for the Ploopy's existing Drag Scroll implementation.

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/scrolllock/

├── keymap.c
└── rules.mk
```

The custom keymap receives the Raw HID command through:

```c
bool via_command_kb(uint8_t *data, uint8_t length)
```

It translates the command into the existing Ploopy Drag Scroll state:

```text
'S' → is_drag_scroll = true

's' → is_drag_scroll = false
```

The actual Drag Scroll processing remains in the normal Ploopy firmware.

### `rules.mk`

```make
VIA_ENABLE = yes
RAW_ENABLE = yes
```

---

## Pointer Rotation

The `rotation` keymap provides standalone testing of the pointer rotation implementation.

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/rotation/

├── config.h
├── keymap.c
├── rotation.c
└── rules.mk
```

Rotation supports:

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

The rotation implementation is contained in:

```text
rotation.c
```

It transforms the pointing-device X/Y coordinates before they continue through the Ploopy pointing-device processing.

The 90° convention is:

```text
X' = Y
Y' = -X
```

The 45° rotations use an integer approximation of `1 / sqrt(2)` suitable for the microcontroller.

### VIA configuration

The rotation value is stored using VIA's custom EEPROM configuration:

```text
VIA_EEPROM_CUSTOM_CONFIG_SIZE = 1
```

This allows the selected rotation to persist across firmware restarts.

---

# Combined Full Firmware

The `full` keymap combines the two independently developed functions:

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/full/

├── config.h
├── keymap.c
├── rotation.c
└── rules.mk
```

Its `rules.mk` enables:

```make
VIA_ENABLE = yes
RAW_ENABLE = yes

SRC += rotation.c
```

The `keymap.c` contains the Drag Scroll / Scroll Lock control path.

The `rotation.c` contains the pointer rotation implementation.

This separation keeps the two functions easy to identify and maintain while allowing them to operate together in a single firmware.

---

## Rotation and Drag Scroll

This is the most important functional requirement of the combined firmware.

Pointer rotation must apply to the X/Y coordinates **before Ploopy's Drag Scroll conversion**.

Therefore, if the pointer is rotated, the Drag Scroll / Scroll Lock direction must rotate with it.

For example, with a 90° rotation:

```text
Physical X/Y
     │
     ▼
90° rotation
     │
     ▼
Rotated X/Y
     │
     ├── Normal pointer movement
     │
     └── Drag Scroll movement
```

Normal pointer movement and Drag Scroll therefore remain aligned.

The combined firmware should not produce one coordinate system for the pointer and another for scrolling.

### Functional acceptance requirement

The final firmware is considered correct only when:

1. Normal pointer movement follows the selected rotation.
2. Drag Scroll continues to function.
3. Drag Scroll follows the same rotated coordinate system.
4. Scroll Lock direction therefore corresponds to the rotated pointer direction.
5. VIA configuration of the rotation works correctly.

---

# Scroll Lock LED

The Ploopy firmware already provides the Scroll Lock state and LED behavior associated with its Drag Scroll implementation.

The custom firmware does not create a second Drag Scroll engine.

Instead, the external control path changes the existing:

```c
is_drag_scroll
```

state.

Conceptually:

```text
External keyboard
       │
       │ Raw HID 'S' / 's'
       ▼
Ploopy VIA command hook
       │
       ▼
is_drag_scroll
       │
       ▼
Existing Ploopy Drag Scroll
       │
       ▼
Scroll Lock / LED behavior
```

---

# Raw HID Protocol

The Drag Scroll protocol uses two command bytes:

```text
0x53 / 'S' → DRAG_SCROLL_ON

0x73 / 's' → DRAG_SCROLL_OFF
```

The protocol is intentionally simple.

```text
Keyboard
   │
   │ 'S' / 's'
   ▼
Corne-Ploopy-Bridge
   │
   │ VIA / Raw HID
   ▼
Ploopy
   │
   ▼
via_command_kb()
   │
   ▼
is_drag_scroll
```

The keyboard determines when Drag Scroll should change.

The host bridge transports the command.

The Ploopy integration translates the command into the existing Ploopy Drag Scroll state.

---

# Firmware Builders

The Nano-2 firmware has three build scripts.

```text
_Firmware/Nano-2/

├── BuildScrollLock.sh
├── BuildRotation.sh
└── BuildFirmware.sh
```

### `BuildScrollLock.sh`

Builds the standalone Drag Scroll / Scroll Lock firmware:

```text
ploopyco/nano_2/rev2_003:scrolllock
```

Output:

```text
ploopy_nano_2_rev2_003_scrolllock.uf2
```

### `BuildRotation.sh`

Builds the standalone pointer rotation firmware:

```text
ploopyco/nano_2/rev2_003:rotation
```

Output:

```text
ploopy_nano_2_rev2_003_rotation.uf2
```

### `BuildFirmware.sh`

Builds the combined firmware:

```text
ploopyco/nano_2/rev2_003:full
```

The combined firmware is the intended final firmware.

---

# Development and Troubleshooting

The standalone `scrolllock` and `rotation` keymaps are retained intentionally during development.

They provide independent firmware builds that can be used to isolate problems.

```text
scrolllock
    │
    └── Test Drag Scroll / Scroll Lock integration

rotation
    │
    └── Test pointer rotation

full
    │
    └── Test both functions together
```

This is particularly useful during hardware validation.

Once the combined firmware has been successfully flashed and fully validated on the Nano 2, the standalone keymaps and their build scripts may no longer be necessary and can eventually be removed.

Until that validation is complete, they should be retained.

---

# Firmware Separation

The normal Ploopy firmware continues to provide:

* pointing-device processing
* Drag Scroll implementation
* Scroll Lock handling
* Scroll Lock LED behavior
* other Ploopy functionality

This repository adds:

* the external VIA / Raw HID Drag Scroll control path
* configurable pointer rotation
* the combined firmware configuration

The goal is to keep the customization small and isolated while reusing the existing Ploopy functionality.

---

# Project Structure

The relevant Nano-2 portion of the repository is:

```text
Ploopy-VIA/

├── _Firmware/
│   └── Nano-2/
│       ├── BuildFirmware.sh
│       ├── BuildRotation.sh
│       └── BuildScrollLock.sh
│
└── keyboards/
    └── ploopyco/
        └── nano_2/
            └── rev2_003/
                └── keymaps/
                    ├── full/
                    │   ├── config.h
                    │   ├── keymap.c
                    │   ├── rotation.c
                    │   └── rules.mk
                    │
                    ├── rotation/
                    │   ├── config.h
                    │   ├── keymap.c
                    │   ├── rotation.c
                    │   └── rules.mk
                    │
                    └── scrolllock/
                        ├── keymap.c
                        └── rules.mk
```

---

# Related Projects

The complete system uses three separate projects.

## Corne — QMK / VIAL

Contains the custom Drag Scroll module:

```text
Crkbd-VIAL/

└── src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/drag_scroll/

    ├── drag_scroll.c
    └── drag_scroll.h
```

## Corne — ZMK

Provides the equivalent Drag Scroll behavior using ZMK.

The ZMK implementation produces the same Raw HID protocol commands as the QMK/VIAL implementation.

## Host Bridge

The host-side bridge receives the Corne Raw HID events and forwards the corresponding commands to the Ploopy.

The bridge is maintained separately from this repository.

---

# Design Goal

The project deliberately separates responsibilities:

```text
QMK / VIAL
    │
    │ DRAG_SCROLL action
    ▼
drag_scroll module
    │
    │ Raw HID 'S' / 's'
    │
    ├──────────────────────┐
    │                      │
    │                 ZMK equivalent
    │                      │
    │                 Raw HID 'S' / 's'
    │                      │
    └──────────┬───────────┘
               ▼
      Corne-Ploopy-Bridge
               │
               │ VIA / Raw HID
               ▼
          Ploopy-VIA
               │
        ┌──────┴──────┐
        │             │
        ▼             ▼
   Pointer        Drag Scroll
   Rotation           │
        │             │
        └──────┬──────┘
               ▼
       Same rotated X/Y
               │
               ▼
        Scroll Lock / LED
```

The keyboard decides **when Drag Scroll should change**.

QMK/VIAL and ZMK are two different keyboard-firmware implementations capable of producing the same protocol.

The host bridge transports that command between devices.

The Ploopy integration translates the command into the Ploopy's existing Drag Scroll state.

The rotation module transforms the pointer coordinates.

The final firmware combines both functions so that **pointer movement and Drag Scroll share the same rotated coordinate system**.
