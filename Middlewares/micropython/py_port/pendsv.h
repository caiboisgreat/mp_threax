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
#ifndef MICROPY_INCLUDED_STM32_PENDSV_H
#define MICROPY_INCLUDED_STM32_PENDSV_H

// PendSV is used for thread/task scheduling in MicroPython.
// In ThreadX RTOS environment, we may not need this functionality
// as ThreadX handles scheduling. This header is kept minimal for
// compatibility with STM32 port code that includes it.

// PendSV dispatch flags (bitfield)
#define PENDSV_DISPATCH_SOFT_TIMER  (0x01)
#define PENDSV_DISPATCH_BLUETOOTH_HCI (0x02)
#define PENDSV_DISPATCH_LWIP        (0x04)
#define PENDSV_DISPATCH_NETWORKING  (0x08)

// PendSV dispatch function type
typedef void (*pendsv_dispatch_t)(void);

// Function declarations (may be empty implementations if not needed)
void pendsv_init(void);
void pendsv_suspend(void);
void pendsv_resume(void);
void pendsv_schedule_dispatch(size_t flags, pendsv_dispatch_t f);
void pendsv_dispatch_handler(void);

// Optional: If ThreadX handles scheduling, these can be empty inline functions
static inline void pendsv_kbd_intr(void) {
    // Keyboard interrupt handling - can be no-op in ThreadX environment
}

#endif // MICROPY_INCLUDED_STM32_PENDSV_H
