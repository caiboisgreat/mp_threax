#ifndef MICROPY_INCLUDED_PY_PORT_SYS_PARAM_H
#define MICROPY_INCLUDED_PY_PORT_SYS_PARAM_H

// Minimal BSD-style <sys/param.h> shim for building berkeley-db-1.xx.
// Provides endianness macros used by berkeley-db's hash implementation.

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 4321
#endif

#ifndef BYTE_ORDER
// STM32 (Cortex-M4) is little-endian.
#define BYTE_ORDER LITTLE_ENDIAN
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#endif // MICROPY_INCLUDED_PY_PORT_SYS_PARAM_H
