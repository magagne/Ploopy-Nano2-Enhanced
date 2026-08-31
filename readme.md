# Ploopy-VIA

Custom QMK firmware configuration for the **Ploopy Nano 2 Rev2.003**.

This repository adds a custom **VIA / Raw HID interface** that allows an external keyboard and host-side bridge to control the Ploopy's existing Drag Scroll functionality.

The customization also preserves and exposes the Ploopy's **Scroll Lock state and LED behavior** as part of the Drag Scroll functionality.

The custom functionality is isolated in the Nano 2 `scrolllock` keymap and does not require replacing the normal Ploopy Drag Scroll implementation.

## What This Repository Does

The Ploopy Nano 2 already contains the core Drag Scroll implementation.

This project adds the control path required by the external keyboard/bridge system:

* VIA is enabled.
* Raw HID is enabled.
* The VIA command hook accepts custom Drag Scroll commands.
* The commands change the Ploopy's existing `is_drag_scroll` state.
* The Ploopy's existing Drag Scroll engine performs the actual pointing/scrolling behavior.
* The Ploopy's existing Scroll Lock handling provides the corresponding Scroll Lock state and LED behavior.

The custom keymap therefore acts as an integration layer rather than replacing Ploopy's existing Drag Scroll engine.

## System Architecture

The complete system is divided into three independent parts.

```text
CORNE SIDE
──────────

QMK / VIAL
  └── modules/drag_scroll/
        ├── drag_scroll.c
        └── drag_scroll.h
             │
             │ sends Raw HID 'S' / 's'
             │
ZMK
  └── Drag Scroll implementation
             │
             │ sends Raw HID 'S' / 's'
             ▼
        Corne-Ploopy-Bridge
             │
             │ HID command
             ▼
PLOOPY SIDE
───────────
Ploopy-VIA
  └── scrolllock/keymap.c
        │
        └── via_command_kb()
              │
              └── is_drag_scroll
                    │
                    ▼
              Ploopy's existing
              Drag Scroll engine
                    │
                    ▼
              Scroll Lock / LED
```

Each component has a separate responsibility.

### Corne — QMK / VIAL

The QMK/VIAL implementation contains the custom `drag_scroll` module:

```text
src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/drag_scroll/
├── drag_scroll.c
└── drag_scroll.h
```

The module detects the Drag Scroll action and generates the corresponding Raw HID command.

### Corne — ZMK

The ZMK implementation provides equivalent Drag Scroll behavior using ZMK's HID/behavior mechanism.

The ZMK implementation is independent of the Ploopy firmware.

It generates the same protocol commands used by the QMK/VIAL implementation:

```text
'S'  (0x53) → Drag Scroll ON
's'  (0x73) → Drag Scroll OFF
```

This makes the host-side protocol independent of the keyboard firmware.

### Corne-Ploopy-Bridge

The host-side bridge receives the Raw HID command from the Corne.

It forwards the corresponding command to the Ploopy through its VIA/Raw HID interface.

The bridge does not need to know whether the command originated from QMK/VIAL or ZMK.

### Ploopy

The Ploopy receives the command through the custom VIA command hook:

```c
bool via_command_kb(uint8_t *data, uint8_t length)
```

The custom keymap translates the command into the existing Ploopy Drag Scroll state:

```text
'S' → is_drag_scroll = true
's' → is_drag_scroll = false
```

The actual Drag Scroll processing remains in the normal Ploopy firmware.

## Drag Scroll Integration

The Ploopy firmware already contains the Drag Scroll engine and the `is_drag_scroll` state.

The custom `scrolllock` keymap does not reimplement that functionality.

Instead, it provides an additional control path through VIA:

```text
VIA Raw HID command
        │
        ▼
via_command_kb()
        │
        ▼
is_drag_scroll
        │
        ▼
existing Ploopy Drag Scroll implementation
```

This keeps the custom code small and minimizes changes to the Ploopy firmware.

## Scroll Lock LED

The Ploopy firmware already uses the system Scroll Lock state as part of its Drag Scroll behavior.

The existing Ploopy firmware maintains:

```c
bool is_drag_scroll = false;
```

and updates that state from the Scroll Lock LED state.

The custom VIA control path provides an additional way to control the same `is_drag_scroll` state from the external keyboard/bridge system.

The important distinction is:

```text
Existing Ploopy firmware
        │
        ├── Scroll Lock state / LED handling
        │
        └── Drag Scroll engine
                  ▲
                  │
        custom VIA control path
                  │
             'S' / 's'
```

The repository therefore does not create a second Drag Scroll implementation.

It integrates the external Drag Scroll protocol with the existing Ploopy implementation and its Scroll Lock/LED behavior.

## Raw HID Protocol

The Drag Scroll protocol uses two command bytes:

```text
0x53 / 'S' → DRAG_SCROLL_ON
0x73 / 's' → DRAG_SCROLL_OFF
```

The protocol is intentionally simple.

The keyboard firmware generates the command.

The host bridge transports it.

The Ploopy VIA keymap receives it and changes `is_drag_scroll`.

The Ploopy firmware then performs the actual Drag Scroll behavior.

## Ploopy Custom Keymap

The custom keymap is located at:

```text
keyboards/ploopyco/nano_2/rev2_003/keymaps/scrolllock/
├── keymap.c
└── rules.mk
```

### `keymap.c`

The custom keymap:

* includes QMK Raw HID support
* uses the VIA command hook
* recognizes the custom Drag Scroll commands
* changes the existing Ploopy `is_drag_scroll` state

The relevant commands are:

```text
0x53 / 'S' → DRAG_SCROLL ON
0x73 / 's' → DRAG_SCROLL OFF
```

### `rules.mk`

The custom keymap enables the required QMK functionality:

```make
VIA_ENABLE = yes
RAW_ENABLE = yes
```

## Raw HID Interface

The Ploopy-side custom interface uses QMK's VIA command mechanism.

The external bridge sends the command byte to the Ploopy, where it reaches:

```c
via_command_kb()
```

The custom keymap handles the Drag Scroll commands it owns.

Unknown commands are not handled by the custom Drag Scroll cases and can continue through the normal VIA/QMK processing path.

## Firmware Separation

This repository intentionally keeps the custom integration separate from the normal Ploopy firmware architecture.

The normal Ploopy firmware continues to provide:

* pointing-device processing
* Drag Scroll implementation
* Scroll Lock handling
* Scroll Lock LED behavior
* other Ploopy functionality

This repository adds the external control interface needed for the Corne/bridge system.

The goal is to keep the customization small and isolated while reusing the existing Ploopy functionality.

## Project Structure

```text
Ploopy-VIA/
└── keyboards/
    └── ploopyco/
        └── nano_2/
            └── rev2_003/
                └── keymaps/
                    └── scrolllock/
                        ├── keymap.c
                        └── rules.mk
```

## Related Projects

The complete system uses three separate projects.

### Corne — QMK / VIAL

Contains the custom Drag Scroll module:

```text
Crkbd-VIAL/
└── src/vial-qmk/keyboards/crkbd/keymaps/vial/modules/drag_scroll/
    ├── drag_scroll.c
    └── drag_scroll.h
```

### Corne — ZMK

Provides the equivalent Drag Scroll behavior using ZMK.

The ZMK implementation produces the same Raw HID protocol commands as the QMK/VIAL implementation.

### Host Bridge

The host-side bridge receives the Corne Raw HID events and forwards the corresponding commands to the Ploopy.

The bridge is maintained separately from this repository.

## Design Goal

The design deliberately separates responsibilities.

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
               │ via_command_kb()
               ▼
         is_drag_scroll
               │
               ▼
      Ploopy Drag Scroll
               │
               ▼
        Scroll Lock / LED
```

The keyboard decides **when Drag Scroll should change**.

QMK/VIAL and ZMK are simply two different keyboard-firmware implementations capable of producing the same protocol.

The host bridge transports that command between devices.

The Ploopy integration translates the command into the Ploopy's existing Drag Scroll state.

The Ploopy firmware remains responsible for the actual Drag Scroll and Scroll Lock/LED behavior.
