# DragScroll-LED

`dragscroll-led` uses the keyboard's ScrollLock LED state to control DragScroll on a Ploopy.

The idea is simple:

    KEYBOARD
        │
        │ ScrollLock LED state
        ▼
    PLOOPY
        │
        ▼
    DragScroll

## What happens

The keyboard changes its ScrollLock state.

The Ploopy receives the LED state.

The Ploopy firmware uses the ScrollLock state to set:

    is_drag_scroll

When ScrollLock is ON:

    is_drag_scroll = true

DragScroll is active.

When ScrollLock is OFF:

    is_drag_scroll = false

Normal pointer movement is active.

## Vertical Scrolling Only

**Vertical Scrolling Only** is a separate VIA setting.

When it is enabled while DragScroll is active:

- ball Y movement becomes vertical scrolling
- ball X movement is ignored

The setting is independent of the ScrollLock state.

ScrollLock remains the exclusive indicator and control for the full X+Y DragScroll mode.

## Ploopy firmware

The Ploopy firmware handles the LED state with:

    bool led_update_kb(led_t led_state) {
        is_drag_scroll = led_state.scroll_lock;
        return led_update_user(led_state);
    }

The important part is:

    is_drag_scroll = led_state.scroll_lock;

The ScrollLock LED state directly controls DragScroll.

## Ball movement

When DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling
- normal X/Y pointer movement is cleared

The firmware also keeps the fractional movement between reports.

This makes slow scrolling smoother.

## Platform

This method depends on the keyboard exposing its ScrollLock LED state in a way the Ploopy can receive.

The current implementation is supported on:

- Windows

It is not supported on Mac.

## Important

`dragscroll-led` does not use `dragscroll-hid`.

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

## Source

The Ploopy implementation is in:

    keyboards/ploopyco/ploopyco.c

The DragScroll state is stored in:

    is_drag_scroll

The LED state updates that variable directly.
