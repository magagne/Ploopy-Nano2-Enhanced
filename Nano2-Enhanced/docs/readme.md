# Ploopy Nano2 Enhanced

Compared with the standard Nano2 firmware, Nano2 Enhanced provides:

- More DPI choices
- Pointer rotation
- Adjustable scroll speed
- Vertical Scrolling Only
- DragScroll
- AutoMouseLayer

## 1. Features

### 1.1 DPI

The Nano2 can use six DPI settings:

| Value | DPI |
|---:|---:|
| 0 | 600 |
| 1 | 900 |
| 2 | 1200 |
| 3 | 1400 |
| 4 | 1600 |
| 5 | 2400 |

The default is **900 DPI**.

DPI can be changed with the Nano2 button or selected from the configuration menu.

See [DPI.md](DPI.md).

### 1.2 Rotation

The Nano2 can change the direction of pointer movement.

There are eight rotation settings:

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

Rotation can be selected from the configuration menu.

See [Rotation.md](Rotation.md).

### 1.3 Scroll Speed

The Nano2 can change the speed of scrolling.

There are five settings:

| Value | Speed |
|---:|---|
| 0 | SLOWER |
| 1 | SLOW |
| 2 | NORMAL |
| 3 | FAST |
| 4 | FASTER |

See [Scroll-Speed.md](Scroll-Speed.md).

### 1.4 Vertical Scrolling Only

**Vertical Scrolling Only** provides a Y-axis-only mode for DragScroll.

When it is **OFF**:

- DragScroll converts ball **X movement** into horizontal scrolling.
- DragScroll converts ball **Y movement** into vertical scrolling.

When it is **ON**:

- DragScroll converts ball **Y movement** into vertical scrolling.
- Ball **X movement is ignored**.
- The existing fractional Y-axis accumulator is retained for smooth scrolling.

Vertical Scrolling Only does not activate or deactivate DragScroll. It only changes how movement is processed while DragScroll is active.

See [Vertical-Scrolling-Only.md](Vertical-Scrolling-Only.md).

### 1.5 DragScroll

**DragScroll** converts Ploopy ball movement into scrolling while DragScroll is active.

The direction of the transport is:

    Keyboard → Ploopy

Two independent transports are provided:

#### macOS

`DragScroll-HID` uses Raw HID to send the DragScroll state from the keyboard to the Ploopy.

See [DragScroll-HID.md](DragScroll-HID.md).

#### Windows

`DragScroll-LED` uses the Scroll Lock LED state.

The keyboard changes Scroll Lock, Windows sends the resulting LED state to the Ploopy, and the Ploopy uses that state to enable or disable DragScroll.

See [DragScroll-LED.md](DragScroll-LED.md).

The LED assignment is:

- **ScrollLock — DragScroll**

Vertical Scrolling Only changes how movement is processed while DragScroll is active. See [Vertical-Scrolling-Only.md](Vertical-Scrolling-Only.md).

### 1.6 AutoMouseLayer

**AutoMouseLayer** uses physical Ploopy movement to activate the configured Mouse layer on the keyboard.

The direction of the transport is:

    Ploopy → Keyboard

The keyboard owns the layer activation and timeout logic.

Two independent transports are provided:

#### macOS

`AutoMouseLayer-HID` uses a Raw HID notification:

    A 01

The Ploopy sends a 32-byte Raw HID packet. The first physical movement is reported immediately and subsequent notifications are rate-limited.

`Ploopy-Bridge-HID` forwards the notification to the keyboard.

See [AutoMouseLayer-HID.md](AutoMouseLayer-HID.md).

#### Windows

`AutoMouseLayer-LED` uses the Caps Lock LED state.

The Ploopy generates a Caps Lock keyboard event. Windows updates the Caps Lock state and sends the resulting LED state to the keyboard.

No bridge is required.

See [AutoMouseLayer-LED.md](AutoMouseLayer-LED.md).

The LED assignment is:

- **Caps Lock — AutoMouseLayer**

The current Corne configuration uses:

| OS | Base layer | Mouse layer |
|---|---:|---:|
| macOS | 0 | 3 |
| Windows | 4 | 7 |

The current keyboard AutoMouseLayer timeout is **700 ms**.

AutoMouseLayer is enabled by default through the Nano2 VIA configuration.

## 2. Configuration

The Nano2 Enhanced VIA configuration provides five settings:

| Setting |
|---|
| DPI |
| Rotation |
| Scroll Speed |
| Vertical Scrolling Only |
| Automatic Mouse Layer |

**Automatic Mouse Layer** is the exact VIA setting name.

The firmware also provides keycodes for the existing DPI, Rotation, and Scroll Speed settings.

The default Nano2 keymap currently places:

    DPI_CONFIG

on the Nano2 button.

See [Configuration.md](Configuration.md).

## 3. Firmware

The project uses one firmware containing all Nano2 features.

Build the firmware with:

    BuildFirmware.sh

There are no separate firmware builds for individual features.

The same firmware contains the complete Nano2 configuration.
