#pragma once

#include <metal/atomic.h>

typedef struct {
    atomic_int v;
} metal_mutex_t;

#define METAL_MUTEX_UNLOCKED 0
#define METAL_MUTEX_LOCKED   1

#define METAL_MUTEX_INIT(m) { ATOMIC_VAR_INIT(METAL_MUTEX_UNLOCKED) }
#define METAL_MUTEX_DEFINE(m) metal_mutex_t m = METAL_MUTEX_INIT(m)

static inline void __metal_mutex_init(metal_mutex_t *mutex) {
    atomic_store(&mutex->v, METAL_MUTEX_UNLOCKED);
}

static inline void __metal_mutex_deinit(metal_mutex_t *mutex) {
    (void)mutex;
}

static inline int __metal_mutex_try_acquire(metal_mutex_t *mutex) {
    int unlocked = METAL_MUTEX_UNLOCKED;
    if (atomic_compare_exchange_strong(&mutex->v, &unlocked, METAL_MUTEX_LOCKED)) {
        return 1;
    }
    return 0;
}

static inline void __metal_mutex_acquire(metal_mutex_t *mutex) {
    int unlocked = METAL_MUTEX_UNLOCKED;
    while (!atomic_compare_exchange_weak(&mutex->v, &unlocked, METAL_MUTEX_LOCKED)) {
        ;
    }
}

static inline void __metal_mutex_release(metal_mutex_t *mutex) {
    atomic_store(&mutex->v, METAL_MUTEX_UNLOCKED);
}

static inline int __metal_mutex_is_acquired(metal_mutex_t *mutex) {
    return atomic_load(&mutex->v);
}
