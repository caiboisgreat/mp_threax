#pragma once

#include <metal/atomic.h>
#include <stdint.h>
#include <metal/errno.h>

struct metal_condition {
    atomic_uintptr_t mptr;
    atomic_int v;
};

#define METAL_CONDITION_INIT { ATOMIC_VAR_INIT(0), ATOMIC_VAR_INIT(0) }

static inline void metal_condition_init(struct metal_condition *cv) {
    atomic_init(&cv->mptr, 0);
    atomic_init(&cv->v, 0);
}

static inline int metal_condition_signal(struct metal_condition *cv) {
    if (!cv) {
        return -EINVAL;
    }
    atomic_fetch_add(&cv->v, 1);
    return 0;
}

static inline int metal_condition_broadcast(struct metal_condition *cv) {
    return metal_condition_signal(cv);
}
