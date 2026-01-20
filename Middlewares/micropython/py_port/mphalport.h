#pragma once

#include "py/mpconfig.h"

// Make mp_hal_set_interrupt_char/mp_interrupt_char available to the core.
#include "shared/runtime/interrupt_char.h"

// Timing/ticks API used by extmod/modtime.c and other core features.
mp_uint_t mp_hal_ticks_ms(void);
mp_uint_t mp_hal_ticks_us(void);
void mp_hal_delay_ms(mp_uint_t ms);
void mp_hal_delay_us(mp_uint_t us);
