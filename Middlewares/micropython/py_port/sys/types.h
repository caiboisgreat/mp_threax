#ifndef MICROPY_SYS_TYPES_H
#define MICROPY_SYS_TYPES_H

#include <stddef.h>
#include <stdint.h>

// Minimal POSIX types for bare-metal builds.
// Used when MICROPY_STREAMS_POSIX_API is enabled.

// Prevent berkeley-db headers from re-typedef'ing standard integer types.
// They key off __BIT_TYPES_DEFINED__ (a BSD libc macro), not on <stdint.h>.
#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__
#endif

// BSD-style unsigned integer aliases used by berkeley-db headers.
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

// BSD-style sized unsigned integer aliases used by berkeley-db headers.
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

// BSD legacy pointer type used by some berkeley-db headers.
typedef char *caddr_t;

// Stream/seek related types.
typedef intptr_t ssize_t;
typedef long off_t;

// Let other shims detect that ssize_t/off_t are available.
#ifndef _MICROPY_SSIZE_T_DEFINED
#define _MICROPY_SSIZE_T_DEFINED 1
#endif
#ifndef _MICROPY_OFF_T_DEFINED
#define _MICROPY_OFF_T_DEFINED 1
#endif

#endif // MICROPY_SYS_TYPES_H
