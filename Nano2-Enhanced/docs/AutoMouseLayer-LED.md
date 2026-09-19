# AutoMouseLayer-LED

`AutoMouseLayer-LED` is the Windows transport used to notify the keyboard when
the Ploopy Nano 2 detects physical trackball movement.

This transport does not require `Ploopy-Bridge-HID`.

## Windows Transport

When physical Ploopy movement occurs, the Ploopy generates a Caps Lock
keyboard event.

Windows updates the Caps Lock state and sends the resulting Caps Lock LED
state to the keyboard.

The ZMK firmware uses the current Caps Lock LED state as the
AutoMouseLayer signal:

- Caps Lock ON → Windows Mouse layer ON
- Caps Lock OFF → Windows Mouse layer OFF

The transport therefore follows this path:

    Ploopy
      |
      v
    Caps Lock keyboard event
      |
      v
    Windows
      |
      v
    Caps Lock LED state
      |
      v
    Corne

## LED Assignments

The keyboard uses separate LED states for the two behaviors:

- **Caps Lock — AutoMouseLayer**
- **ScrollLock — DragScroll**

ScrollLock remains exclusively associated with DragScroll.

## Layer Configuration

The current Corne configuration maps:

| OS | Base layer | Mouse layer |
|---|---:|---:|
| Windows | 4 | 7 |

The keyboard owns the layer activation logic.

This Windows path is state-based and does not use the normal
AutoMouseLayer timeout. The Nano keeps Caps Lock ON while physical movement
continues and turns it OFF after **400 ms without movement**.

## No Bridge Required

`AutoMouseLayer-LED` is a Windows HID LED-state mechanism.

The Raw HID `Ploopy-Bridge-HID` transport is not involved.

## Relationship with DragScroll

`AutoMouseLayer-LED` is independent of DragScroll.

DragScroll continues to use the ScrollLock LED state.

AutoMouseLayer uses the Caps Lock LED state.
