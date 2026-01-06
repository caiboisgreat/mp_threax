#ifndef MICROPY_SYS_CDEFS_H
#define MICROPY_SYS_CDEFS_H

// Minimal sys/cdefs.h shim for Berkeley DB headers on bare metal.

#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#ifndef __P
#if defined(__STDC__) || defined(__cplusplus)
#define __P(protos) protos
#else
#define __P(protos) ()
#endif
#endif

#endif // MICROPY_SYS_CDEFS_H
