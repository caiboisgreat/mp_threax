#ifndef MICROPY_INCLUDED_PY_PORT_FCNTL_H
#define MICROPY_INCLUDED_PY_PORT_FCNTL_H

// Minimal fcntl.h shim for bare-metal builds (Keil/armclang).
// MicroPython's btree module includes <fcntl.h> but does not rely on full POSIX.

// Common open() flags (values match typical POSIX but are only placeholders here).
#ifndef O_RDONLY
#define O_RDONLY (0)
#endif
#ifndef O_WRONLY
#define O_WRONLY (1)
#endif
#ifndef O_RDWR
#define O_RDWR   (2)
#endif
#ifndef O_CREAT
#define O_CREAT  (0x0100)
#endif
#ifndef O_TRUNC
#define O_TRUNC  (0x0200)
#endif
#ifndef O_APPEND
#define O_APPEND (0x0400)
#endif

#endif // MICROPY_INCLUDED_PY_PORT_FCNTL_H
