# DragScroll-LED

`DragScroll-LED` uses the keyboard's Scroll Lock LED state to control DragScroll on a Ploopy.

The transport direction is:

    Keyboard → Ploopy

## What happens

The keyboard changes its Scroll Lock state.

Windows sends the resulting LED state to the Ploopy.

The Ploopy firmware uses the Scroll Lock state to set:

    is_drag_scroll

When Scroll Lock is ON:

    is_drag_scroll = true

DragScroll is active.

When Scroll Lock is OFF:

    is_drag_scroll = false

Normal pointer movement is active.

## Vertical Scrolling Only

**Vertical Scrolling Only** is a separate VIA setting that filters the movement processed by DragScroll.

When it is **OFF** and DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling

When it is **ON** and DragScroll is active:

- ball Y movement becomes vertical scrolling
- ball X movement is ignored

The setting does **not** activate or deactivate DragScroll.

Scroll Lock continues to control the overall DragScroll state.

See [Vertical-Scrolling-Only.md](Vertical-Scrolling-Only.md).

## Ploopy firmware

The Ploopy firmware handles the LED state with:

    bool led_update_kb(led_t led_state) {
        is_drag_scroll = led_state.scroll_lock;
        return led_update_user(led_state);
    }

The important part is:

    is_drag_scroll = led_state.scroll_lock;

The Scroll Lock LED state directly controls DragScroll.

## Ball movement

When DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling
- normal X/Y pointer movement is cleared

The firmware also keeps the fractional movement between reports.

This makes slow scrolling smoother.

## Platform

This method depends on the keyboard exposing its Scroll Lock LED state in a way the Ploopy can receive.

The current implementation is supported on:

- Windows

It is not supported on Mac.

## Implementation

`DragScroll-LED` does not use `DragScroll-HID`.

There is no host-side bridge between the keyboard and the Ploopy.

The path is:

    KEYBOARD
        │
        │ ScrollLock LED state
        ▼
    PLOOPY
        │
        │ led_update_kb()
        ▼
    is_drag_scroll
        │
        ▼
    DragScroll

The Ploopy implementation is in:

    keyboards/ploopyco/ploopyco.c

The DragScroll state is stored in:

    is_drag_scroll

The LED state updates that variable directly.
