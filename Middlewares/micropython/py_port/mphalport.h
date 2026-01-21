#pragma once

#include "py/mpconfig.h"
#include "pin.h"

// Make mp_hal_set_interrupt_char/mp_interrupt_char available to the core.
#include "shared/runtime/interrupt_char.h"

// Timing/ticks API used by extmod/modtime.c and other core features.
mp_uint_t mp_hal_ticks_ms(void);
mp_uint_t mp_hal_ticks_us(void);
void mp_hal_delay_ms(mp_uint_t ms);
void mp_hal_delay_us(mp_uint_t us);

// GPIO pin access macros (override py/mphal.h defaults)
// These operate directly on machine_pin_obj_t* instead of going through virtual pin layer
#define mp_hal_pin_read(pin) (((pin)->gpio->IDR & (pin)->pin_mask) ? 1 : 0)
#define mp_hal_pin_write(pin, v) do { \
    if (v) { \
        (pin)->gpio->BSRR = (pin)->pin_mask; \
    } else { \
        (pin)->gpio->BSRR = (pin)->pin_mask << 16; \
    } \
} while (0)
