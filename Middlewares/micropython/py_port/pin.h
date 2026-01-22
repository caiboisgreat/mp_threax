/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef MICROPY_INCLUDED_PY_PORT_PIN_H
#define MICROPY_INCLUDED_PY_PORT_PIN_H

#include "py/obj.h"
#include "stm32f4xx_hal.h"

// Pin object structure
typedef struct {
    mp_obj_base_t base;
    qstr name;
    GPIO_TypeDef *gpio;
    uint32_t pin;       // Pin number (0-15)
    uint32_t pin_mask;  // Pin mask (1 << pin)
    uint8_t port;       // Port number (0=A, 1=B, etc.)
} machine_pin_obj_t;

extern const mp_obj_type_t pin_type;
extern const mp_obj_type_t pin_board_pins_obj_type;
extern const mp_obj_type_t pin_cpu_pins_obj_type;

// CPU pin objects (defined in pins.c)
extern const machine_pin_obj_t pin_A0;
extern const machine_pin_obj_t pin_A1;
extern const machine_pin_obj_t pin_A2;
extern const machine_pin_obj_t pin_A3;
extern const machine_pin_obj_t pin_A4;
extern const machine_pin_obj_t pin_A5;
extern const machine_pin_obj_t pin_A6;
extern const machine_pin_obj_t pin_A7;
extern const machine_pin_obj_t pin_A8;
extern const machine_pin_obj_t pin_A9;
extern const machine_pin_obj_t pin_A10;
extern const machine_pin_obj_t pin_A11;
extern const machine_pin_obj_t pin_A12;
extern const machine_pin_obj_t pin_A13;
extern const machine_pin_obj_t pin_A14;
extern const machine_pin_obj_t pin_A15;

extern const machine_pin_obj_t pin_B0;
extern const machine_pin_obj_t pin_B1;
extern const machine_pin_obj_t pin_B2;
extern const machine_pin_obj_t pin_B3;
extern const machine_pin_obj_t pin_B4;
extern const machine_pin_obj_t pin_B5;
extern const machine_pin_obj_t pin_B6;
extern const machine_pin_obj_t pin_B7;
extern const machine_pin_obj_t pin_B8;
extern const machine_pin_obj_t pin_B9;
extern const machine_pin_obj_t pin_B10;
extern const machine_pin_obj_t pin_B11;
extern const machine_pin_obj_t pin_B12;
extern const machine_pin_obj_t pin_B13;
extern const machine_pin_obj_t pin_B14;
extern const machine_pin_obj_t pin_B15;

extern const machine_pin_obj_t pin_C0;
extern const machine_pin_obj_t pin_C1;
extern const machine_pin_obj_t pin_C2;
extern const machine_pin_obj_t pin_C3;
extern const machine_pin_obj_t pin_C4;
extern const machine_pin_obj_t pin_C5;
extern const machine_pin_obj_t pin_C6;
extern const machine_pin_obj_t pin_C7;
extern const machine_pin_obj_t pin_C8;
extern const machine_pin_obj_t pin_C9;
extern const machine_pin_obj_t pin_C10;
extern const machine_pin_obj_t pin_C11;
extern const machine_pin_obj_t pin_C12;
extern const machine_pin_obj_t pin_C13;
extern const machine_pin_obj_t pin_C14;
extern const machine_pin_obj_t pin_C15;

extern const machine_pin_obj_t pin_D0;
extern const machine_pin_obj_t pin_D1;
extern const machine_pin_obj_t pin_D2;
extern const machine_pin_obj_t pin_D3;
extern const machine_pin_obj_t pin_D4;
extern const machine_pin_obj_t pin_D5;
extern const machine_pin_obj_t pin_D6;
extern const machine_pin_obj_t pin_D7;
extern const machine_pin_obj_t pin_D8;
extern const machine_pin_obj_t pin_D9;
extern const machine_pin_obj_t pin_D10;
extern const machine_pin_obj_t pin_D11;
extern const machine_pin_obj_t pin_D12;
extern const machine_pin_obj_t pin_D13;
extern const machine_pin_obj_t pin_D14;
extern const machine_pin_obj_t pin_D15;

extern const machine_pin_obj_t pin_E0;
extern const machine_pin_obj_t pin_E1;
extern const machine_pin_obj_t pin_E2;
extern const machine_pin_obj_t pin_E3;
extern const machine_pin_obj_t pin_E4;
extern const machine_pin_obj_t pin_E5;
extern const machine_pin_obj_t pin_E6;
extern const machine_pin_obj_t pin_E7;
extern const machine_pin_obj_t pin_E8;
extern const machine_pin_obj_t pin_E9;
extern const machine_pin_obj_t pin_E10;
extern const machine_pin_obj_t pin_E11;
extern const machine_pin_obj_t pin_E12;
extern const machine_pin_obj_t pin_E13;
extern const machine_pin_obj_t pin_E14;
extern const machine_pin_obj_t pin_E15;

extern const machine_pin_obj_t pin_H0;
extern const machine_pin_obj_t pin_H1;

// Board pin definitions
extern const mp_obj_dict_t machine_pin_board_pins_locals_dict;
extern const mp_obj_dict_t machine_pin_cpu_pins_locals_dict;

// Pin functions
const machine_pin_obj_t *pin_find(mp_obj_t user_obj);
const machine_pin_obj_t *pin_find_named_pin(const mp_obj_dict_t *named_pins, mp_obj_t name);
uint32_t pin_get_mode(const machine_pin_obj_t *pin);
uint32_t pin_get_pull(const machine_pin_obj_t *pin);
uint32_t pin_get_af(const machine_pin_obj_t *pin);

void pin_init0(void);

// HAL functions (mp_hal_pin_* are defined in mphalport.c)
// Note: mp_virtual_pin_read/write are declared in extmod/virtpin.h
void mp_hal_gpio_clock_enable(GPIO_TypeDef *gpio);
void mp_hal_pin_config(const machine_pin_obj_t *pin, uint32_t mode, uint32_t pull, uint32_t alt);
void mp_hal_pin_output(const machine_pin_obj_t *pin);
void mp_hal_pin_input(const machine_pin_obj_t *pin);
void mp_hal_pin_low(const machine_pin_obj_t *pin);
void mp_hal_pin_high(const machine_pin_obj_t *pin);

// Pin constants
#define MP_HAL_PIN_MODE_INPUT           (0)
#define MP_HAL_PIN_MODE_OUTPUT          (1)
#define MP_HAL_PIN_MODE_ALT             (2)
#define MP_HAL_PIN_MODE_ANALOG          (3)
#define MP_HAL_PIN_MODE_OPEN_DRAIN      (5)
#define MP_HAL_PIN_MODE_ALT_OPEN_DRAIN  (6)
#define MP_HAL_PIN_PULL_NONE            (0)
#define MP_HAL_PIN_PULL_UP              (1)
#define MP_HAL_PIN_PULL_DOWN            (2)

// Alternate-function identifiers (minimal set for this port)
#define AF_FN_I2C                        (1)
#define AF_FN_SPI                        (2)

#endif // MICROPY_INCLUDED_PY_PORT_PIN_H
