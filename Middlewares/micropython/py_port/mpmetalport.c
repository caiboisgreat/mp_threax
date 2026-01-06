#include <stdint.h>

#include "py/mpconfig.h"
#include "py/mphal.h"

#if defined(STM32F405xx) || defined(STM32F4xx)
#include "stm32f4xx_hal.h"
#endif

#include "core_cm4.h"

// libmetal core headers (resolved via the libmetal wrapper include layout).
#include <metal/sys.h>
#include <metal/io.h>

struct metal_state _metal;

int __metal_sleep_usec(unsigned int usec) {
    mp_hal_delay_us((mp_uint_t)usec);
    return 0;
}

unsigned int sys_irq_save_disable(void) {
    uint32_t primask = __get_PRIMASK();
    __disable_irq();
    return primask;
}

void sys_irq_restore_enable(unsigned int flags) {
    __set_PRIMASK(flags);
}

void sys_irq_enable(unsigned int vector) {
    NVIC_EnableIRQ((IRQn_Type)vector);
}

void sys_irq_disable(unsigned int vector) {
    NVIC_DisableIRQ((IRQn_Type)vector);
}

int metal_sys_init(const struct metal_init_params *params) {
    (void)params;
    return 0;
}

void metal_sys_finish(void) {
}

void metal_sys_io_mem_map(struct metal_io_region *io) {
    (void)io;
}

void metal_machine_cache_flush(void *addr, unsigned int len) {
    (void)addr;
    (void)len;
}

void metal_machine_cache_invalidate(void *addr, unsigned int len) {
    (void)addr;
    (void)len;
}

unsigned long long metal_get_timestamp(void) {
    return (unsigned long long)mp_hal_ticks_us();
}
