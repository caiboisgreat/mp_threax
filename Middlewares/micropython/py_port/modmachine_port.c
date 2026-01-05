#include <string.h>

#include "py/runtime.h"

// CMSIS / STM32 headers (for __WFI, NVIC_SystemReset, UID_BASE, SystemCoreClock).
#include "stm32f4xx.h"

extern const mp_obj_type_t machine_sdcard_type;

#ifndef MICROPY_PY_MACHINE_EXTRA_GLOBALS
#define MICROPY_PY_MACHINE_EXTRA_GLOBALS \
    { MP_ROM_QSTR(MP_QSTR_SDCard), MP_ROM_PTR(&machine_sdcard_type) },
#endif

// This file is text-included by extmod/modmachine.c via MICROPY_PY_MACHINE_INCLUDEFILE.
// It must provide the static low-level hooks that modmachine.c declares.

static void mp_machine_idle(void) {
    __WFI();
}

#if MICROPY_PY_MACHINE_RESET
MP_NORETURN static void mp_machine_reset(void) {
    NVIC_SystemReset();
}

static mp_int_t mp_machine_reset_cause(void) {
    // This minimal port does not currently track reset cause.
    // Ports with RCC reset flags can implement a proper mapping.
    return 0;
}
#endif

#if MICROPY_PY_MACHINE_BARE_METAL_FUNCS
static mp_obj_t mp_machine_unique_id(void) {
    // STM32 unique device ID is 96 bits.
    uint8_t id[12];
    const uint32_t *uid = (const uint32_t *)UID_BASE;
    memcpy(&id[0], &uid[0], 4);
    memcpy(&id[4], &uid[1], 4);
    memcpy(&id[8], &uid[2], 4);
    return mp_obj_new_bytes(id, sizeof(id));
}

static mp_obj_t mp_machine_get_freq(void) {
    // Return core clock in Hz.
    return mp_obj_new_int_from_uint(SystemCoreClock);
}

static void mp_machine_set_freq(size_t n_args, const mp_obj_t *args) {
    (void)n_args;
    (void)args;
    mp_raise_NotImplementedError(MP_ERROR_TEXT("set_freq"));
}

static void mp_machine_lightsleep(size_t n_args, const mp_obj_t *args) {
    (void)n_args;
    (void)args;
    __WFI();
}

MP_NORETURN static void mp_machine_deepsleep(size_t n_args, const mp_obj_t *args) {
    (void)n_args;
    (void)args;
    // Minimal behavior: deepsleep maps to reset.
    NVIC_SystemReset();
}
#endif
