#pragma once

#include "py/mpconfig.h"
#include "py/obj.h"
#include "py/qstr.h"
#include "pin.h"

// Pin object type for mp_hal (define as macro so py/mphal.h doesn't override)
#define mp_hal_pin_obj_t const machine_pin_obj_t *

// Make mp_hal_set_interrupt_char/mp_interrupt_char available to the core.
#include "shared/runtime/interrupt_char.h"

// Timing/ticks API used by extmod/modtime.c and other core features.
mp_uint_t mp_hal_ticks_ms(void);
mp_uint_t mp_hal_ticks_us(void);
void mp_hal_delay_ms(mp_uint_t ms);
void mp_hal_delay_us(mp_uint_t us);

// Pin helpers used by SoftI2C/SoftSPI and peripherals
mp_hal_pin_obj_t mp_hal_get_pin_obj(mp_obj_t pin);
qstr mp_hal_pin_name(mp_hal_pin_obj_t pin);
bool mp_hal_pin_config_alt(mp_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, uint32_t af_fn, uint32_t unit);
void mp_hal_pin_open_drain(mp_hal_pin_obj_t pin);
void mp_hal_pin_od_high(mp_hal_pin_obj_t pin);
void mp_hal_pin_od_low(mp_hal_pin_obj_t pin);

// Format string for pin names in mp_printf
#define MP_HAL_PIN_FMT "%q"

// Fast delay used by SoftI2C
#define mp_hal_delay_us_fast(us) mp_hal_delay_us(us)

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
