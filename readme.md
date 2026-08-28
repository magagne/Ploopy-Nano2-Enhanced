# Ploopy Nano 2 — VIA Drag Scroll

Custom QMK firmware for the **Ploopy Nano 2 Rev2.003**, with a custom **DRAG_SCROLL** module integrated into the `via_scrolllock` keymap.

## Project structure

```text
keyboards/ploopyco/nano_2/rev2_003/
└── keymaps/
    └── via_scrolllock/
        ├── keymap.c
        ├── rules.mk
        └── modules/
            └── drag_scroll/
                ├── drag_scroll.c
                └── drag_scroll.h
eof
