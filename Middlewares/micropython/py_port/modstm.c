/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2023 Damien P. George
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

#include <stdio.h>
#include <string.h>

#include "py/runtime.h"
#include "py/mphal.h"

#if defined(STM32F405xx) || defined(STM32F4xx)
#include "stm32f4xx_hal.h"
#endif

// ------------------------------------------------------------------------
// Memory access functions
// ------------------------------------------------------------------------

// stm.mem8[addr] = value  or  value = stm.mem8[addr]
static void stm_mem_set(mp_obj_t addr_obj, mp_obj_t val_obj, size_t size) {
    mp_uint_t addr = mp_obj_get_int_truncated(addr_obj);
    mp_uint_t val = mp_obj_get_int_truncated(val_obj);
    
    switch (size) {
        case 1:
            *(volatile uint8_t *)addr = val;
            break;
        case 2:
            *(volatile uint16_t *)addr = val;
            break;
        case 4:
            *(volatile uint32_t *)addr = val;
            break;
        default:
            mp_raise_ValueError(MP_ERROR_TEXT("invalid size"));
    }
}

static mp_uint_t stm_mem_get(mp_obj_t addr_obj, size_t size) {
    mp_uint_t addr = mp_obj_get_int_truncated(addr_obj);
    
    switch (size) {
        case 1:
            return *(volatile uint8_t *)addr;
        case 2:
            return *(volatile uint16_t *)addr;
        case 4:
            return *(volatile uint32_t *)addr;
        default:
            mp_raise_ValueError(MP_ERROR_TEXT("invalid size"));
            return 0;
    }
}

// stm.mem8 object
typedef struct _stm_mem_obj_t {
    mp_obj_base_t base;
    size_t elem_size; // in bytes: 1, 2, 4
} stm_mem_obj_t;

static void stm_mem_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    stm_mem_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "<stm.mem%u>", (unsigned int)(self->elem_size * 8));
}

static mp_obj_t stm_mem_subscr(mp_obj_t self_in, mp_obj_t index, mp_obj_t value) {
    stm_mem_obj_t *self = MP_OBJ_TO_PTR(self_in);
    
    if (value == MP_OBJ_NULL) {
        // delete not supported
        return MP_OBJ_NULL;
    } else if (value == MP_OBJ_SENTINEL) {
        // load
        return mp_obj_new_int(stm_mem_get(index, self->elem_size));
    } else {
        // store
        stm_mem_set(index, value, self->elem_size);
        return mp_const_none;
    }
}

static MP_DEFINE_CONST_OBJ_TYPE(
    stm_mem_type,
    MP_QSTR_mem,
    MP_TYPE_FLAG_NONE,
    print, stm_mem_print,
    subscr, stm_mem_subscr
);

static const stm_mem_obj_t stm_mem8_obj = {{&stm_mem_type}, 1};
static const stm_mem_obj_t stm_mem16_obj = {{&stm_mem_type}, 2};
static const stm_mem_obj_t stm_mem32_obj = {{&stm_mem_type}, 4};

// ------------------------------------------------------------------------
// RF core control functions (for STM32WBxx)
// ------------------------------------------------------------------------

#if defined(STM32WB)
static mp_obj_t stm_rfcore_status(void) {
    // Placeholder for STM32WB RF core status
    return mp_obj_new_int(0);
}
static MP_DEFINE_CONST_FUN_OBJ_0(stm_rfcore_status_obj, stm_rfcore_status);

static mp_obj_t stm_rfcore_fw_version(size_t n_args, const mp_obj_t *args) {
    // Placeholder for STM32WB RF core firmware version
    mp_obj_t tuple[3] = {
        mp_obj_new_int(0),
        mp_obj_new_int(0),
        mp_obj_new_int(0),
    };
    return mp_obj_new_tuple(3, tuple);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(stm_rfcore_fw_version_obj, 0, 1, stm_rfcore_fw_version);

static mp_obj_t stm_rfcore_sys_hci(size_t n_args, const mp_obj_t *args) {
    // Placeholder for STM32WB RF core HCI command
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(stm_rfcore_sys_hci_obj, 2, 3, stm_rfcore_sys_hci);
#endif

// ------------------------------------------------------------------------
// Module globals
// ------------------------------------------------------------------------

static const mp_rom_map_elem_t stm_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_stm) },
    
    // Memory access objects
    { MP_ROM_QSTR(MP_QSTR_mem8), MP_ROM_PTR(&stm_mem8_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem16), MP_ROM_PTR(&stm_mem16_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem32), MP_ROM_PTR(&stm_mem32_obj) },
    
    #if defined(STM32WB)
    // RF core functions (STM32WBxx only)
    { MP_ROM_QSTR(MP_QSTR_rfcore_status), MP_ROM_PTR(&stm_rfcore_status_obj) },
    { MP_ROM_QSTR(MP_QSTR_rfcore_fw_version), MP_ROM_PTR(&stm_rfcore_fw_version_obj) },
    { MP_ROM_QSTR(MP_QSTR_rfcore_sys_hci), MP_ROM_PTR(&stm_rfcore_sys_hci_obj) },
    #endif
    
    // Peripheral base addresses (STM32F405)
    #if defined(STM32F405xx) || defined(STM32F4xx)
    // GPIO
    { MP_ROM_QSTR(MP_QSTR_GPIOA), MP_ROM_INT(GPIOA_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOB), MP_ROM_INT(GPIOB_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOC), MP_ROM_INT(GPIOC_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOD), MP_ROM_INT(GPIOD_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOE), MP_ROM_INT(GPIOE_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOF), MP_ROM_INT(GPIOF_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOG), MP_ROM_INT(GPIOG_BASE) },
    { MP_ROM_QSTR(MP_QSTR_GPIOH), MP_ROM_INT(GPIOH_BASE) },
    
    // RCC
    { MP_ROM_QSTR(MP_QSTR_RCC), MP_ROM_INT(RCC_BASE) },
    
    // SYSCFG
    { MP_ROM_QSTR(MP_QSTR_SYSCFG), MP_ROM_INT(SYSCFG_BASE) },
    
    // TIM
    { MP_ROM_QSTR(MP_QSTR_TIM1), MP_ROM_INT(TIM1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM2), MP_ROM_INT(TIM2_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM3), MP_ROM_INT(TIM3_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM4), MP_ROM_INT(TIM4_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM5), MP_ROM_INT(TIM5_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM6), MP_ROM_INT(TIM6_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM7), MP_ROM_INT(TIM7_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM8), MP_ROM_INT(TIM8_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM9), MP_ROM_INT(TIM9_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM10), MP_ROM_INT(TIM10_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM11), MP_ROM_INT(TIM11_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM12), MP_ROM_INT(TIM12_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM13), MP_ROM_INT(TIM13_BASE) },
    { MP_ROM_QSTR(MP_QSTR_TIM14), MP_ROM_INT(TIM14_BASE) },
    
    // USART/UART
    { MP_ROM_QSTR(MP_QSTR_USART1), MP_ROM_INT(USART1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_USART2), MP_ROM_INT(USART2_BASE) },
    { MP_ROM_QSTR(MP_QSTR_USART3), MP_ROM_INT(USART3_BASE) },
    { MP_ROM_QSTR(MP_QSTR_UART4), MP_ROM_INT(UART4_BASE) },
    { MP_ROM_QSTR(MP_QSTR_UART5), MP_ROM_INT(UART5_BASE) },
    { MP_ROM_QSTR(MP_QSTR_USART6), MP_ROM_INT(USART6_BASE) },
    
    // SPI
    { MP_ROM_QSTR(MP_QSTR_SPI1), MP_ROM_INT(SPI1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_SPI2), MP_ROM_INT(SPI2_BASE) },
    { MP_ROM_QSTR(MP_QSTR_SPI3), MP_ROM_INT(SPI3_BASE) },
    
    // I2C
    { MP_ROM_QSTR(MP_QSTR_I2C1), MP_ROM_INT(I2C1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_I2C2), MP_ROM_INT(I2C2_BASE) },
    { MP_ROM_QSTR(MP_QSTR_I2C3), MP_ROM_INT(I2C3_BASE) },
    
    // ADC
    { MP_ROM_QSTR(MP_QSTR_ADC1), MP_ROM_INT(ADC1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_ADC2), MP_ROM_INT(ADC2_BASE) },
    { MP_ROM_QSTR(MP_QSTR_ADC3), MP_ROM_INT(ADC3_BASE) },
    
    // DAC
    { MP_ROM_QSTR(MP_QSTR_DAC), MP_ROM_INT(DAC_BASE) },
    
    // PWR
    { MP_ROM_QSTR(MP_QSTR_PWR), MP_ROM_INT(PWR_BASE) },
    
    // DMA
    { MP_ROM_QSTR(MP_QSTR_DMA1), MP_ROM_INT(DMA1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_DMA2), MP_ROM_INT(DMA2_BASE) },
    
    // CAN
    { MP_ROM_QSTR(MP_QSTR_CAN1), MP_ROM_INT(CAN1_BASE) },
    { MP_ROM_QSTR(MP_QSTR_CAN2), MP_ROM_INT(CAN2_BASE) },
    
    // USB
    { MP_ROM_QSTR(MP_QSTR_USB_OTG_FS), MP_ROM_INT(USB_OTG_FS_PERIPH_BASE) },
    { MP_ROM_QSTR(MP_QSTR_USB_OTG_HS), MP_ROM_INT(USB_OTG_HS_PERIPH_BASE) },
    
    // SDIO
    { MP_ROM_QSTR(MP_QSTR_SDIO), MP_ROM_INT(SDIO_BASE) },
    
    // RTC
    { MP_ROM_QSTR(MP_QSTR_RTC), MP_ROM_INT(RTC_BASE) },
    
    // IWDG
    { MP_ROM_QSTR(MP_QSTR_IWDG), MP_ROM_INT(IWDG_BASE) },
    
    // WWDG
    { MP_ROM_QSTR(MP_QSTR_WWDG), MP_ROM_INT(WWDG_BASE) },
    #endif
};

static MP_DEFINE_CONST_DICT(stm_module_globals, stm_module_globals_table);

const mp_obj_module_t mp_module_stm = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&stm_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_stm, mp_module_stm);
