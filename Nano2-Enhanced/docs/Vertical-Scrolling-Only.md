# Vertical Scrolling Only

## Overview

**Vertical Scrolling Only** is a Nano2 Enhanced DragScroll mode that converts only vertical ball movement into vertical scrolling.

It is a filtering option for DragScroll. It does **not** activate or deactivate DragScroll.

## Behavior

### OFF

When Vertical Scrolling Only is **OFF**, DragScroll operates normally:

- Ball X movement produces horizontal scrolling.
- Ball Y movement produces vertical scrolling.

### ON

When Vertical Scrolling Only is **ON**:

- Ball Y movement produces vertical scrolling.
- Ball X movement is ignored.
- The fractional Y-axis accumulator remains active for smooth scrolling.

The existing scroll-speed settings continue to control the Y-axis scrolling rate.

## Processing Order

Pointer movement is processed in this order:

    Ball movement
         |
         v
    Pointer rotation
         |
         v
    DragScroll processing
         |
         v
    Vertical Scrolling Only filter
         |
         v
    Vertical wheel scrolling

This means that Vertical Scrolling Only operates on the already-rotated pointer coordinates.

## DragScroll Activation

Vertical Scrolling Only is independent of the mechanism used to activate DragScroll.

### dragscroll-led

With `dragscroll-led`:

- ScrollLock controls the overall DragScroll state.
- Vertical Scrolling Only is controlled independently through VIA.
- The ScrollLock LED remains the exclusive indicator/control of the overall DragScroll state.

### dragscroll-hid

With `dragscroll-hid`:

- `S` / `s` controls the overall DragScroll state.
- Vertical Scrolling Only is controlled independently through VIA.
- No additional `V` / `v` HID command is required.

## VIA Configuration

Vertical Scrolling Only is a VIA toggle:

- Channel: `0`
- Value ID: `4`
- Default: `OFF`

The setting is available from the Nano2 Enhanced VIA configuration.

## Persistence

Vertical Scrolling Only is stored in the Nano2 user configuration EEPROM.

The setting is restored when the keyboard starts.

If the stored configuration is invalid or uninitialized, Vertical Scrolling Only defaults to **OFF**.

## Keycodes

Vertical Scrolling Only does not have a physical keycode in the default Nano2 keymap.

It is controlled through the VIA configuration.

## Summary

| Vertical Scrolling Only | X movement | Y movement |
|---|---|---|
| OFF | Horizontal scrolling | Vertical scrolling |
| ON | Ignored | Vertical scrolling |
