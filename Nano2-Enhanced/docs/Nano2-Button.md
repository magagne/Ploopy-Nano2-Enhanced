# Nano2 Button

The Nano2 button can activate DragScroll directly.

This is a separate path from the keyboard methods.

The idea is simple:

    NANO-2 BUTTON
          │
          ▼
    Nano2 firmware
          │
          ▼
      DragScroll

## What happens

The Nano2 button can be configured to control DragScroll.

When the button is pressed:

    DragScroll ON

When the button is pressed again:

    DragScroll OFF

The button can therefore be used as a toggle.

## Independent path

The Nano2 button does not use:

- `dragscroll-hid`
- `dragscroll-led`
- ScrollLock
- the keyboard

The Nano2 firmware controls the DragScroll state directly.

## Three ways to activate DragScroll

The complete picture is:

    KEYBOARD
        │
        ├── HID key code ──────► dragscroll-hid ───► PLOOPY
        │
        └── ScrollLock LED ────────────────────────► PLOOPY


    NANO-2 BUTTON
        │
        ▼
    Nano2 firmware
        │
        ▼
    DragScroll

All three methods have the same goal:

    DragScroll

Only the way DragScroll is activated is different.

## Configuration

The Nano2 button can be assigned to the DragScroll function.

The button behavior is handled by the Nano2 firmware.

The exact key or button configuration belongs to the Nano2 firmware configuration and is documented separately.

## Important

The Nano2 button is a direct hardware path.

It does not need a host-side bridge.

It does not depend on the keyboard's ScrollLock LED.

It does not depend on `dragscroll-hid`.

This makes it independent from the two keyboard-based activation methods.
