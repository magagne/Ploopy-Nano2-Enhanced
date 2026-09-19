# AutoMouseLayer-HID

`AutoMouseLayer-HID` is the Raw HID transport used to notify the keyboard when
the Ploopy Nano 2 detects physical trackball movement.

This transport is currently used on macOS.

## Protocol

The Ploopy sends a 32-byte Raw HID packet beginning with:

    A 01

The remaining bytes are zero.

The first physical movement is notified immediately. Subsequent notifications
are rate-limited to approximately one every 30 ms.

## macOS Transport

The Ploopy sends the notification through its Raw HID interface.

`Ploopy-Bridge-HID` receives the packet and forwards it unchanged to the
keyboard Raw HID interface.

The bridge is a transport only. It does not implement keyboard layer policy.

The ZMK firmware receives the `A 01` notification and activates the configured
Mac Mouse layer.

## Layer Configuration

The current Corne configuration maps:

| OS | Base layer | Mouse layer |
|---|---:|---:|
| macOS | 0 | 3 |

The keyboard owns the AutoMouseLayer timeout and layer activation logic.

## Relationship with DragScroll

`AutoMouseLayer-HID` is independent of DragScroll.

DragScroll continues to use its existing HID mechanism.

AutoMouseLayer uses:

    A 01

for the AutoMouseLayer notification.
