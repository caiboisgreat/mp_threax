#ifndef MICROPY_INCLUDED_MPMETALPORT_H
#define MICROPY_INCLUDED_MPMETALPORT_H

// libmetal configuration overrides for this MicroPython port.
// These are consumed by Middlewares/micropython/extmod/libmetal/metal/config.h.

// libmetal needs 2 regions in the generic device for: shm + resource table.
#ifndef METAL_MAX_DEVICE_REGIONS
#define METAL_MAX_DEVICE_REGIONS 2
#endif

// These feature macros are used by libmetal's config header. Keep them off.
#ifndef METAL_HAVE_STDATOMIC_H
#define METAL_HAVE_STDATOMIC_H 0
#endif

#ifndef METAL_HAVE_FUTEX_H
#define METAL_HAVE_FUTEX_H 0
#endif

#endif // MICROPY_INCLUDED_MPMETALPORT_H
