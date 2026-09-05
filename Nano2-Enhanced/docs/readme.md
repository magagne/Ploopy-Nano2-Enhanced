# Ploopy Nano2 Enhanced

Compared with the standard Nano2 firmware:

- **Keyboard-triggered DragScroll**
- **More DPI choices**
- **Pointer rotation**
- **Adjustable scroll speed**

- **Vertical Scrolling Only mode**

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

### 1.2 DragScroll

The Nano2 can work in two main ways:

- **Pointer** — move the mouse pointer
- **Scrolling** — move the ball to scroll

There are several ways to activate DragScroll.

                    PLOOPY BALL MOVEMENT
                              │
                 ┌────────────┴────────────┐
                 │                         │
              POINTER                  SCROLLING
                                           │
                              ┌────────────┴────────────┐
                              │                         │
                        NANO BUTTON                 KEYBOARD
                              │                         │
                              │                  ┌──────┴──────┐
                              │                  │             │
                              │             HID key code   ScrollLock LED state
                              │                  │             │
                              │                  ▼             ▼
                              │           dragscroll-hid  dragscroll-led
                              │                  │             │
                              │              Windows/Mac   Windows
                              │                  │             │
                              ▼                  ▼             ▼
                         DragScroll          DragScroll    DragScroll

The **ScrollLock LED state** method (`dragscroll-led`) is currently supported on **Windows only**. It is not supported on Mac.

#### dragscroll-hid

`dragscroll-hid` uses a HID key code to activate DragScroll.

It works on:

- Windows
- Mac

See [DragScroll-HID.md](DragScroll-HID.md).

#### dragscroll-led

`dragscroll-led` uses the keyboard's ScrollLock LED state to activate DragScroll.

This method is currently supported on Windows only.

See [DragScroll-LED.md](DragScroll-LED.md).

#### Nano2 button

The default Nano2 button changes the DPI setting.

Pressing it cycles through the six DPI settings.

See [Nano2-Button.md](Nano2-Button.md).

### 1.3 Rotation

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

### 1.4 Scroll Speed

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

### 1.5 Vertical Scrolling Only

**Vertical Scrolling Only** provides a Y-axis-only DragScroll mode.

When it is **OFF**:

- DragScroll converts ball **X movement** into horizontal scrolling.
- DragScroll converts ball **Y movement** into vertical scrolling.

When it is **ON**:

- DragScroll converts ball **Y movement** into vertical scrolling.
- Ball **X movement is ignored**.
- The existing fractional Y-axis accumulator is retained for smooth scrolling.

Vertical Scrolling Only does **not** activate DragScroll. DragScroll is still activated by the existing mechanism:

- `dragscroll-hid` — the `S` / `s` HID key controls DragScroll.
- `dragscroll-led` — the ScrollLock LED state controls DragScroll on Windows.

The Vertical Scrolling Only setting is independent of the ScrollLock LED and does not change what the LED represents. The LED remains the exclusive indicator/control of the overall DragScroll state.

Rotation is applied before DragScroll processing, so Vertical Scrolling Only operates on the already-rotated pointer coordinates.

The setting is available from the Nano2 VIA configuration menu and is **OFF by default**.

See [Vertical-Scrolling-Only.md](Vertical-Scrolling-Only.md).

## 2. Configuration

The configuration menu can change:

| Setting |
|---|
| DPI |
| Rotation |
| Scroll Speed |
| Vertical Scrolling Only |

The firmware also provides keycodes for the existing DPI, Rotation, and Scroll Speed settings.

Vertical Scrolling Only is a VIA configuration setting and does not have a physical keycode in the default keymap.

The default Nano2 keymap currently places:

    DPI_CONFIG

on the Nano2 button.

Other configuration keycodes are available in the firmware but are not placed on a key in the default keymap.

See [Configuration.md](Configuration.md).

## 3. Firmware

The project uses one firmware containing all Nano2 features.

Build the firmware with:

    BuildFirmware.sh

There are no separate firmware builds for the individual features.

The same firmware contains the complete Nano2 configuration.
