#pragma once

#include <metal/config.h>

// Declarations for cache maintenance hooks (implemented by the port).
void metal_machine_cache_flush(void *addr, unsigned int len);
void metal_machine_cache_invalidate(void *addr, unsigned int len);

static inline void __metal_cache_flush(void *addr, unsigned int len) {
    metal_machine_cache_flush(addr, len);
}

static inline void __metal_cache_invalidate(void *addr, unsigned int len) {
    metal_machine_cache_invalidate(addr, len);
}
