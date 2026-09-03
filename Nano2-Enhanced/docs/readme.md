# Ploopy Nano2

This project adds extra features to the Ploopy Nano2.

The goal is simple:

- make the Nano2 comfortable to use
- make the main settings easy to change
- keep everything in one firmware
- keep the project easy to understand

## 1. Features

### 1.1 DPI

The Nano2 can use five DPI settings:

    600
    900
    1200
    1600
    2400

The default is:

    900 DPI

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

Pressing it cycles through the five DPI settings.

See [Nano2-Button.md](Nano2-Button.md).

### 1.3 Rotation

The Nano2 can change the direction of pointer movement.

There are eight rotation settings:

    0°
    45°
    90°
    135°
    180°
    225°
    270°
    315°

Rotation can be selected from the configuration menu.

See [Rotation.md](Rotation.md).

### 1.4 Scroll Speed

The Nano2 can change the speed of scrolling.

There are five settings:

    0 - SLOWER = 128
    1 - SLOW = 96
    2 - NORMAL = 64
    3 - FAST = 48
    4 - FASTER = 32
Scroll Speed can be selected from the configuration menu.

See [Scroll-Speed.md](Scroll-Speed.md).

## 2. Configuration

The configuration menu can change:

    DPI
    Rotation
    Scroll Speed

The firmware also provides keycodes for these settings.

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
