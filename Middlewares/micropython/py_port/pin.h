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

#endif // MICROPY_INCLUDED_PY_PORT_PIN_H
