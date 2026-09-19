# DragScroll-HID

`DragScroll-HID` lets a keyboard tell a Ploopy to use DragScroll.

The transport direction is:

    Keyboard → Ploopy

## What happens

The keyboard sends a Raw HID message.

There are two commands:

- `S` = DragScroll ON
- `s` = DragScroll OFF

`Ploopy-Bridge-HID` receives the message and forwards the command to the connected Ploopy.

The Ploopy firmware changes its DragScroll state.

## Vertical Scrolling Only

**Vertical Scrolling Only** is controlled independently through the Nano2 VIA configuration.

When it is **OFF** and DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling

When it is **ON** and DragScroll is active:

- ball Y movement becomes vertical scrolling
- ball X movement is ignored

The existing `S` and `s` HID commands continue to control the overall DragScroll state.

No additional HID command is required for Vertical Scrolling Only.

See [Vertical-Scrolling-Only.md](Vertical-Scrolling-Only.md).

## Raw HID

`DragScroll-HID` uses this Raw HID interface:

- Usage Page: `0xFF60`
- Usage: `0x0061`

The bridge does not depend on a specific keyboard VID or PID.

Compatible keyboard endpoints can therefore use the same bridge.

## Ploopy

The Ploopy firmware receives the DragScroll command and changes its DragScroll state.

When DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling
- normal pointer movement is stopped

The Ploopy firmware also keeps small movement values between reports so scrolling stays smooth.

## Connection

`Ploopy-Bridge-HID` continuously looks for compatible HID devices.

It handles:

- connection
- disconnection
- reconnection
- hot-plug

The bridge can therefore keep running while a device is temporarily disconnected.

## Platform

The current `DragScroll-HID` transport is used on **macOS** through `Ploopy-Bridge-HID`.

macOS requires shared access to the Raw HID device.

The bridge explicitly enables this when running on macOS.

The repository also contains a macOS LaunchAgent for starting the bridge automatically.

Service name:

    com.ploopy-bridge-hid

## Implementation

The main bridge implementation is:

    src/ploopy_bridge_hid.py

The bridge is kept separate from:

- keyboard firmware
- Ploopy firmware

This keeps the transport independent from the keyboard and Ploopy behavior.
