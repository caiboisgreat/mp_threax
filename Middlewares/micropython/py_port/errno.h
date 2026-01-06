#ifndef MICROPY_PY_PORT_ERRNO_H
#define MICROPY_PY_PORT_ERRNO_H

// This port provides a wrapper around the toolchain's <errno.h> to fill in
// any missing error codes needed by embedded builds.
//
// Note: this header is intentionally named "errno.h" so that includes of
// <errno.h> from third-party code (e.g. berkeley-db) can resolve here first
// via the project's -I include paths.

#if defined(__clang__) || defined(__GNUC__)
// Use include_next to avoid recursive inclusion of this header.
#include_next <errno.h>

// Some bare-metal/newlib configurations don't provide a visible errno symbol.
// MicroPython's POSIX stream shims take &errno, so ensure it's declared.
#if !defined(errno)
extern int errno;
#endif
#else
// Fallback: provide a minimal set if include_next isn't available.
// (Avoid including <errno.h> here to prevent recursion.)
extern int errno;
#endif

#ifndef EPERM
#define EPERM 1
#endif

#ifndef ENOENT
#define ENOENT 2
#endif

#ifndef EINVAL
#define EINVAL 22
#endif

#ifndef ENXIO
#define ENXIO 6
#endif

#ifndef ENOMEM
#define ENOMEM 12
#endif

#ifndef EEXIST
#define EEXIST 17
#endif

#ifndef ENODEV
#define ENODEV 19
#endif

#ifndef ERANGE
#define ERANGE 34
#endif

#ifndef EFTYPE
#define EFTYPE 79
#endif

#endif // MICROPY_PY_PORT_ERRNO_H
