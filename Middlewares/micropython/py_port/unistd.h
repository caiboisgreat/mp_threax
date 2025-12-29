
#ifndef MICROPY_PORT_MINIMAL_UNISTD_H
#define MICROPY_PORT_MINIMAL_UNISTD_H

// Minimal unistd.h shim for bare-metal builds (e.g. Keil/armcc/armclang).
// MicroPython includes <unistd.h> mainly for ssize_t, STD* file descriptors,
// and SEEK_* whence constants.

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef ptrdiff_t ssize_t;

#ifndef STDIN_FILENO
#define STDIN_FILENO (0)
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO (1)
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO (2)
#endif

#ifndef SEEK_SET
#define SEEK_SET (0)
#endif

#ifndef SEEK_CUR
#define SEEK_CUR (1)
#endif

#ifndef SEEK_END
#define SEEK_END (2)
#endif

// Optional POSIX-like syscall prototypes.
// Provide implementations only if your port routes stdio via semihosting.
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);

#ifdef __cplusplus
}
#endif

#endif // MICROPY_PORT_MINIMAL_UNISTD_H

