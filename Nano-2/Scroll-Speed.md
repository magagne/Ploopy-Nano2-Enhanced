# Scroll Speed

Scroll Speed controls how fast the ball scrolls when DragScroll is active.

The Nano-2 has five scroll speed settings:

    SLOWER
    SLOW
    NORMAL
    FAST
    FASTER

## Speed settings

    SLOWER  = 128
    SLOW    = 96
    NORMAL  = 64
    FAST    = 48
    FASTER  = 32

A larger number means slower scrolling.

A smaller number means faster scrolling.

## How it works

The ball movement goes through DragScroll:

    Ball movement
         │
         ▼
      DragScroll
         │
         ▼
    Scroll speed
         │
         ▼
      Scrolling

The selected speed is used for both:

    Horizontal scrolling
    Vertical scrolling

## Changing the speed

The firmware provides:

    SCROLL_SPEED

Each press moves to the next setting.

The cycle is:

    NORMAL
       ↓
    SLOW
       ↓
    SLOWER
       ↓
    FAST
       ↓
    FASTER
       ↓
    NORMAL

The selected speed is applied immediately.

The selected speed is also saved.

## Configuration menu

The configuration menu can select the scroll speed directly.

The firmware uses these values:

    0 = NORMAL
    1 = SLOW
    2 = SLOWER
    3 = FAST
    4 = FASTER

## Saving

The selected scroll speed is stored in the Nano-2 user configuration.

The firmware reads it when the Nano-2 starts.

## Firmware

The setting is stored in:

    scroll_speed_index

The speed values are stored in:

    scroll_speed_divisors

The firmware applies the selected speed with:

    apply_scroll_speed()

The scroll speed controls:

    ploopy_dragscroll_divisor_h
    ploopy_dragscroll_divisor_v

## Source

The implementation is in:

    keyboards/ploopyco/nano_2/rev2_003/keymaps/default/keymap.c
