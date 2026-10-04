#pragma once

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1
#define VIA_FIRMWARE_VERSION 0x00010001

/*
 * Nano2-Enhanced DPI settings.
 * These override the generic Ploopy defaults.
 */
#define PLOOPY_DPI_OPTIONS { 900, 1000, 1200, 1400, 1600, 1800 }
#define PLOOPY_DPI_DEFAULT 2

#define PLOOPY_DRAGSCROLL_INVERT
