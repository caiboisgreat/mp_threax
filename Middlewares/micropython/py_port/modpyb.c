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

#include <stdint.h>
#include <stdio.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "led.h"
#include "pin.h"

#if MICROPY_PY_PYB

// ------------------------------------------------------------------------
// pyb.info() - print information about the board
// ------------------------------------------------------------------------
static mp_obj_t pyb_info(size_t n_args, const mp_obj_t *args) {
    (void)n_args;
    (void)args;
    
    // Print basic system information
    mp_printf(&mp_plat_print, "--------------------------------\n");
    mp_printf(&mp_plat_print, "MicroPython on ThreadX\n");
    mp_printf(&mp_plat_print, "Board: %s\n", MICROPY_HW_BOARD_NAME);
    mp_printf(&mp_plat_print, "MCU: %s\n", MICROPY_HW_MCU_NAME);
    mp_printf(&mp_plat_print, "--------------------------------\n");
    
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(pyb_info_obj, 0, 1, pyb_info);

// ------------------------------------------------------------------------
// pyb.delay(ms) - delay for given number of milliseconds
// ------------------------------------------------------------------------
static mp_obj_t pyb_delay(mp_obj_t ms_in) {
    mp_int_t ms = mp_obj_get_int(ms_in);
    if (ms > 0) {
        mp_hal_delay_ms(ms);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(pyb_delay_obj, pyb_delay);

// ------------------------------------------------------------------------
// pyb.udelay(us) - delay for given number of microseconds
// ------------------------------------------------------------------------
static mp_obj_t pyb_udelay(mp_obj_t us_in) {
    mp_int_t us = mp_obj_get_int(us_in);
    if (us > 0) {
        mp_hal_delay_us(us);
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(pyb_udelay_obj, pyb_udelay);

// ------------------------------------------------------------------------
// pyb.millis() - get millisecond counter
// ------------------------------------------------------------------------
static mp_obj_t pyb_millis(void) {
    return mp_obj_new_int(mp_hal_ticks_ms());
}
static MP_DEFINE_CONST_FUN_OBJ_0(pyb_millis_obj, pyb_millis);

// ------------------------------------------------------------------------
// pyb.micros() - get microsecond counter
// ------------------------------------------------------------------------
static mp_obj_t pyb_micros(void) {
    return mp_obj_new_int(mp_hal_ticks_us());
}
static MP_DEFINE_CONST_FUN_OBJ_0(pyb_micros_obj, pyb_micros);

// ------------------------------------------------------------------------
// pyb.elapsed_millis(start) - get elapsed milliseconds since start
// ------------------------------------------------------------------------
static mp_obj_t pyb_elapsed_millis(mp_obj_t start) {
    uint32_t startMillis = mp_obj_get_int(start);
    uint32_t currMillis = mp_hal_ticks_ms();
    return MP_OBJ_NEW_SMALL_INT((currMillis - startMillis) & 0x3fffffff);
}
static MP_DEFINE_CONST_FUN_OBJ_1(pyb_elapsed_millis_obj, pyb_elapsed_millis);

// ------------------------------------------------------------------------
// pyb.elapsed_micros(start) - get elapsed microseconds since start
// ------------------------------------------------------------------------
static mp_obj_t pyb_elapsed_micros(mp_obj_t start) {
    uint32_t startMicros = mp_obj_get_int(start);
    uint32_t currMicros = mp_hal_ticks_us();
    return MP_OBJ_NEW_SMALL_INT((currMicros - startMicros) & 0x3fffffff);
}
static MP_DEFINE_CONST_FUN_OBJ_1(pyb_elapsed_micros_obj, pyb_elapsed_micros);

// ------------------------------------------------------------------------
// pyb module globals table
// ------------------------------------------------------------------------
static const mp_rom_map_elem_t pyb_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_pyb) },
    
    // Functions
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&pyb_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_delay), MP_ROM_PTR(&pyb_delay_obj) },
    { MP_ROM_QSTR(MP_QSTR_udelay), MP_ROM_PTR(&pyb_udelay_obj) },
    { MP_ROM_QSTR(MP_QSTR_millis), MP_ROM_PTR(&pyb_millis_obj) },
    { MP_ROM_QSTR(MP_QSTR_micros), MP_ROM_PTR(&pyb_micros_obj) },
    { MP_ROM_QSTR(MP_QSTR_elapsed_millis), MP_ROM_PTR(&pyb_elapsed_millis_obj) },
    { MP_ROM_QSTR(MP_QSTR_elapsed_micros), MP_ROM_PTR(&pyb_elapsed_micros_obj) },
    
    // Classes
    { MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&pyb_led_type) },
    { MP_ROM_QSTR(MP_QSTR_Pin), MP_ROM_PTR(&pin_type) },
};

static MP_DEFINE_CONST_DICT(pyb_module_globals, pyb_module_globals_table);

const mp_obj_module_t mp_module_pyb = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&pyb_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_pyb, mp_module_pyb);

#endif // MICROPY_PY_PYB
