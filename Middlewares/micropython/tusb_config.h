// Thin wrapper so TinyUSB can find tusb_config.h via the existing include paths
// (Keil project already includes ../Middlewares/micropython in IncludePath).
//
// The actual MicroPython TinyUSB configuration lives in shared/tinyusb.
#pragma once

#include "shared/tinyusb/tusb_config.h"

// TinyUSB versions use either CFG_TUD_MSC_BUFSIZE or CFG_TUD_MSC_EP_BUFSIZE.
// MicroPython's shared config defines CFG_TUD_MSC_BUFSIZE, but TinyUSB 0.19
// expects CFG_TUD_MSC_EP_BUFSIZE.
#if MICROPY_HW_ENABLE_USBDEV
	#if !defined(CFG_TUD_MSC_BUFSIZE) && defined(MICROPY_FATFS_MAX_SS)
		#define CFG_TUD_MSC_BUFSIZE (MICROPY_FATFS_MAX_SS)
	#endif
	#if !defined(CFG_TUD_MSC_EP_BUFSIZE) && defined(CFG_TUD_MSC_BUFSIZE)
		#define CFG_TUD_MSC_EP_BUFSIZE (CFG_TUD_MSC_BUFSIZE)
	#endif
	#ifndef CFG_TUD_ENDPOINT0_SIZE
		#define CFG_TUD_ENDPOINT0_SIZE 64
	#endif
#endif
