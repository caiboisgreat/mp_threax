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
#ifndef MICROPY_INCLUDED_STM32_IRQ_H
#define MICROPY_INCLUDED_STM32_IRQ_H

#include "py/mpconfig.h"

// IRQ priority levels for STM32 - lower number = higher priority
// STM32 NVIC has 16 priority levels (4 bits), we use priorities 0-15
#define IRQ_PRI_SYSTICK     (0)    // Highest priority for SysTick
#define IRQ_PRI_PENDSV      (15)   // Lowest priority for PendSV
#define IRQ_PRI_UART        (13)   // UART interrupt priority
#define IRQ_PRI_SDIO        (14)   // SDIO interrupt priority
#define IRQ_PRI_DMA         (13)   // DMA interrupt priority
#define IRQ_PRI_TIM         (14)   // Timer interrupt priority
#define IRQ_PRI_EXTI        (14)   // External interrupt priority
#define IRQ_PRI_USB         (6)    // USB interrupt priority
#define IRQ_PRI_RTC_WKUP    (15)   // RTC wakeup interrupt priority
#define IRQ_PRI_ETH_WKUP    (15)   // Ethernet wakeup interrupt priority
#define IRQ_PRI_CAN         (11)   // CAN interrupt priority
#define IRQ_PRI_I2C_EV      (13)   // I2C event interrupt priority
#define IRQ_PRI_I2C_ER      (13)   // I2C error interrupt priority
#define IRQ_PRI_SPI         (13)   // SPI interrupt priority

// Macro to handle IRQ numbers that may be negative (used in STM32 HAL)
// If IRQn < 0, it's a core system exception (not NVIC), return 0
// If IRQn >= 0, it's a peripheral interrupt
#define IRQn_NONNEG(irq)    ((irq) < 0 ? 0 : (irq))

// Enable/disable all interrupts using PRIMASK
static inline uint32_t raise_irq_pri(uint32_t pri) {
    uint32_t basepri = __get_BASEPRI();
    // Cortex-M masks 4 MSB bits of priority
    __set_BASEPRI(pri << (8 - __NVIC_PRIO_BITS));
    return basepri;
}

static inline void restore_irq_pri(uint32_t basepri) {
    __set_BASEPRI(basepri);
}

// Disable all interrupts (critical section)
static inline uint32_t disable_irq(void) {
    uint32_t state = __get_PRIMASK();
    __disable_irq();
    return state;
}

// Enable all interrupts (exit critical section)
static inline void enable_irq(uint32_t state) {
    __set_PRIMASK(state);
}

// Query if IRQs are enabled
static inline int query_irq(void) {
    return __get_PRIMASK() == 0;
}

#endif // MICROPY_INCLUDED_STM32_IRQ_H
