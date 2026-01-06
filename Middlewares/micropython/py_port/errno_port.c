// Provide a weak errno symbol for bare-metal builds.
//
// Some toolchain configurations do not provide a visible `errno` object, but
// MicroPython's POSIX stream compatibility layer takes `&errno`.
//
// Mark it weak so that if the C library provides a strong definition, that one
// is used instead.

#if !defined(errno)
__attribute__((weak)) int errno;
#endif
