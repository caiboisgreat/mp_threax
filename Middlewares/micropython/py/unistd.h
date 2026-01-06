#ifndef MICROPY_INCLUDED_UNISTD_H

#define MICROPY_INCLUDED_UNISTD_H

// For bare-metal ports we provide a minimal <sys/types.h> in py_port.
// Use that for ssize_t to avoid conflicting typedefs.
#include <sys/types.h>

#define F_OK 0

#define W_OK 2

#define R_OK 4

#define STDIN_FILENO  0

#define STDOUT_FILENO 1

#define STDERR_FILENO 2

#define SEEK_CUR 1

#define SEEK_END 2

#define SEEK_SET 0

#endif