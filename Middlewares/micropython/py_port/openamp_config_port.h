#ifndef MICROPY_INCLUDED_OPENAMP_CONFIG_PORT_H
#define MICROPY_INCLUDED_OPENAMP_CONFIG_PORT_H

#include <stdint.h>

// Shared memory backing store for OpenAMP vrings/buffers.
extern uint8_t mp_openamp_shm[];
extern uint8_t mp_openamp_rsc[];

// libmetal generic device name.
#define METAL_SHM_NAME   "mp_openamp_shm"

// Use a statically allocated RAM buffer for shm and resource table.
#define METAL_SHM_ADDR   ((uintptr_t)mp_openamp_shm)
#define METAL_SHM_SIZE   (0x8000u)

// Resource table area; type is opaque here (assigned to the proper type later).
#define METAL_RSC_ADDR   ((void *)mp_openamp_rsc)
#define METAL_RSC_SIZE   (0x400u)

#endif // MICROPY_INCLUDED_OPENAMP_CONFIG_PORT_H
