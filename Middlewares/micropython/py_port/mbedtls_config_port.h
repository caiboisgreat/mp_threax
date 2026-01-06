#ifndef MICROPY_INCLUDED_MBEDTLS_CONFIG_PORT_H
#define MICROPY_INCLUDED_MBEDTLS_CONFIG_PORT_H

// Port-level mbedTLS configuration for this STM32/ThreadX build.
//
// Keep this header minimal and layered on top of MicroPython's common config.

#include <stdint.h>

// Bare-metal builds may not have a libc <time.h>. mbedTLS uses time_t in a few
// places when MBEDTLS_HAVE_TIME is enabled, so provide a minimal definition.
typedef int64_t time_t;
time_t time(time_t *t);

#include "../extmod/mbedtls/mbedtls_config_common.h"

// mbedTLS requires MBEDTLS_PLATFORM_C when using the platform time hooks.
#define MBEDTLS_PLATFORM_C

// Enable time support to satisfy mbedTLS config prerequisites, but provide a
// custom time type/function so we don't depend on libc <time.h>.
#define MBEDTLS_HAVE_TIME
#define MBEDTLS_PLATFORM_TIME_TYPE_MACRO int64_t

// This target is neither Unix nor Windows, so disable platform entropy polling
// provided by mbedTLS. A proper hardware RNG should be integrated later.
#define MBEDTLS_NO_PLATFORM_ENTROPY

// Provide mbedtls_ms_time() via a port implementation (HAL tick-based).
#define MBEDTLS_PLATFORM_MS_TIME_ALT

// No filesystem/VFS in this firmware build (MICROPY_VFS=0), so disable
// mbedTLS file IO to avoid pulling in headers that may not exist.
#ifdef MBEDTLS_FS_IO
#undef MBEDTLS_FS_IO
#endif

#endif // MICROPY_INCLUDED_MBEDTLS_CONFIG_PORT_H
