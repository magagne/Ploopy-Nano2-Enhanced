# DragScroll-HID

`dragscroll-hid` lets a keyboard tell a Ploopy to use DragScroll.

The idea is simple:

    KEYBOARD
        │
        │ HID key code
        ▼
    dragscroll-hid
        │
        │ HID command
        ▼
    PLOOPY
        │
        ▼
    DragScroll

## What happens

The keyboard sends a Raw HID message.

There are two commands:

- `S` = DragScroll ON
- `s` = DragScroll OFF

`dragscroll-hid` receives the message and sends the command to the connected Ploopy.

The Ploopy firmware changes its DragScroll state.

## Vertical Scrolling Only

**Vertical Scrolling Only** is controlled independently through the Nano2 VIA configuration.

When it is enabled while DragScroll is active:

- ball Y movement becomes vertical scrolling
- ball X movement is ignored

The existing `S` and `s` HID commands continue to control the overall DragScroll state.

No additional `V` or `v` HID command is required.

## Raw HID

`dragscroll-hid` looks for this Raw HID interface:

- Usage Page: `0xFF60`
- Usage: `0x0061`

The bridge does not depend on a specific keyboard VID or PID.

This makes it possible for compatible keyboards to use the same bridge.

## Ploopy

The Ploopy firmware receives the DragScroll command and changes its DragScroll state.

When DragScroll is active:

- ball X movement becomes horizontal scrolling
- ball Y movement becomes vertical scrolling
- normal pointer movement is stopped

The Ploopy firmware also keeps small movement values between reports so scrolling stays smooth.

## Connection

`dragscroll-hid` continuously looks for compatible HID devices.

It handles:

- connection
- disconnection
- reconnection
- hot-plug

The bridge can therefore keep running while a device is temporarily disconnected.

## macOS

macOS needs shared access to the Raw HID device.

The bridge explicitly enables this when running on macOS.

The repository also contains a macOS LaunchAgent for starting the bridge automatically.

Service name:

    com.dragscroll-hid

## Windows

The HID bridge also works on Windows.

The core bridge is not tied to macOS.

Startup configuration is handled separately from the HID code.

## Debug

Use:

    python3 src/drag_scroll_hid.py --debug

Debug mode shows information about:

- detected devices
- connections
- disconnections
- HID messages received
- HID commands sent

## Main file

The main implementation is:

    src/drag_scroll_hid.py

The bridge is kept separate from:

- keyboard firmware
- Ploopy firmware

This keeps the different parts simple and independent.
