#pragma once

#include <metal/config.h>

struct metal_io_region;

// Memory mapping hook used by libmetal; for MCUs this is typically a no-op.
void metal_sys_io_mem_map(struct metal_io_region *io);
