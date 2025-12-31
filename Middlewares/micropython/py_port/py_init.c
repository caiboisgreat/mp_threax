#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "py/builtin.h"
#include "py/compile.h"
#include "py/nlr.h"
#include "py/runtime.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mperrno.h"
#include "py/mphal.h"
#include "py/stackctrl.h"
#include "py/mpstate.h"
#include "shared/runtime/gchelper.h"
#include "shared/runtime/pyexec.h"

// Minimal frozen-module stubs for bare-metal builds that don't generate
// frozen content tables.
// These are required when MICROPY_MODULE_FROZEN is enabled by the core config.
const char mp_frozen_names[] = "";
#if MICROPY_MODULE_FROZEN_MPY
#include "py/emitglue.h"
const mp_frozen_module_t *const mp_frozen_mpy_content[] = { NULL };
#endif

// Note: This project uses the upstream MicroPython REPL implementation from
// shared/runtime/pyexec.c (added to the Keil project).
// A local minimal REPL existed previously for bring-up, but is now disabled to
// avoid duplicate symbols and to get full REPL behavior (expression printing,
// multiline, history, etc).

#if MICROPY_ENABLE_GC
static char heap[MICROPY_HEAP_SIZE];
#endif

//int main(int argc, char **argv) {
int micro_python_init(void *stack_top, uint32_t stack_len_bytes) {
    // IMPORTANT (ThreadX): mp_stack_set_top() must be the *true* top of the
    // current thread's C stack.  If it's set to a local variable then the GC
    // will scan only a tiny slice of stack and may miss roots, causing
    // use-after-free/corruption that can manifest as nlr_top becoming NULL.
    if (stack_top != NULL) {
        mp_stack_set_top(stack_top);
        #if MICROPY_STACK_CHECK
        if (stack_len_bytes > 1024u) {
            // Leave some headroom for interrupts/port code.
            mp_stack_set_limit((mp_uint_t)(stack_len_bytes - 512u));
        }
        #endif
    } else {
        volatile int stack_dummy;
        mp_stack_set_top((void *)&stack_dummy);
    }

    #if MICROPY_ENABLE_GC
    gc_init(heap, heap + sizeof(heap));
    #endif
    mp_init();
    #if MICROPY_ENABLE_COMPILER
    #if MICROPY_REPL_EVENT_DRIVEN
    // Top-level exception handler: protects the event-driven REPL processing.
    // Without this, any exception raised during input/editing (eg history alloc)
    // will call nlr_jump_fail because there is no active nlr handler.
    pyexec_event_repl_init();
    for (;;) {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0) {
            for (;;) {
                int c = mp_hal_stdin_rx_chr();
                if (pyexec_event_repl_process_char(c)) {
                    break;
                }
            }
            nlr_pop();
            break;
        } else {
            mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(nlr.ret_val));
        }
    }
    #else
    // Top-level exception handler: protects friendly REPL + readline.
    // Friendly REPL calls into readline, which can allocate (line editing/history)
    // and therefore can raise MemoryError. Catch here so we don't hit nlr_jump_fail.
    for (;;) {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0) {
            int ret = pyexec_friendly_repl();
            nlr_pop();
            if (ret & PYEXEC_FORCED_EXIT) {
                break;
            }
        } else {
            mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(nlr.ret_val));
        }
    }
    #endif
    // do_str("print('hello world!', list(x+1 for x in range(10)), end='eol\\n')", MP_PARSE_SINGLE_INPUT);
    // do_str("for i in range(10):\r\n  print(i)", MP_PARSE_FILE_INPUT);
    #else
    pyexec_frozen_module("frozentest.py", false);
    #endif
    mp_deinit();
    return 0;
}

#if MICROPY_ENABLE_GC
void gc_collect(void) {
    gc_collect_start();
    // Collect roots from CPU registers and the C stack.
    gc_helper_collect_regs_and_stack();
    gc_collect_end();
}
#endif

mp_lexer_t *mp_lexer_new_from_file(qstr filename) {
    mp_raise_OSError(MP_ENOENT);
}

mp_import_stat_t mp_import_stat(const char *path) {
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_obj_t mp_builtin_open(size_t n_args, const mp_obj_t *args, mp_map_t *kwargs) {
    (void)n_args;
    (void)args;
    (void)kwargs;
    // Filesystem/VFS not ported yet in this project.
    mp_raise_OSError(MP_ENODEV);
}

MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

void nlr_jump_fail(void *val) {
    (void)val;
    #if MICROPY_MIN_USE_STM32_MCU
    // Best-effort panic message over USART2 (polling, no HAL), then spin.
    typedef struct {
        volatile uint32_t SR;
        volatile uint32_t DR;
    } periph_uart_t;
    #define USART2_DBG ((periph_uart_t *)0x40004400)
    // Print a minimal diagnostic: nlr_top should never be NULL if an exception
    // unwinds within an active nlr_push scope.
    uint32_t ipsr = 0;
    uint32_t msp = 0;
    uint32_t psp = 0;
    uint32_t sp = 0;
    __asm volatile ("mrs %0, ipsr" : "=r"(ipsr));
    __asm volatile ("mrs %0, msp" : "=r"(msp));
    __asm volatile ("mrs %0, psp" : "=r"(psp));
    __asm volatile ("mov %0, sp" : "=r"(sp));

    mp_printf(&mp_plat_print,
        "\r\nFATAL: nlr_jump_fail val=%p nlr_top=%p nlr_top@%p IPSR=%lu SP=%p MSP=%p PSP=%p\r\n",
        val, MP_STATE_THREAD(nlr_top), &MP_STATE_THREAD(nlr_top),
        (unsigned long)ipsr, (void *)sp, (void *)msp, (void *)psp);
    const char *s = "";
    while (*s) {
        while ((USART2_DBG->SR & (1u << 7)) == 0u) {
        }
        USART2_DBG->DR = (uint32_t)(uint8_t)(*s++);
    }
    #endif
    while (1) {
        ;
    }
}

void MP_NORETURN __fatal_error(const char *msg) {
    #if MICROPY_MIN_USE_STM32_MCU
    typedef struct {
        volatile uint32_t SR;
        volatile uint32_t DR;
    } periph_uart_t;
    #define USART2_DBG ((periph_uart_t *)0x40004400)
    const char *p = "\r\nFATAL: __fatal_error ";
    while (*p) {
        while ((USART2_DBG->SR & (1u << 7)) == 0u) {
        }
        USART2_DBG->DR = (uint32_t)(uint8_t)(*p++);
    }
    if (msg) {
        while (*msg) {
            while ((USART2_DBG->SR & (1u << 7)) == 0u) {
            }
            USART2_DBG->DR = (uint32_t)(uint8_t)(*msg++);
        }
    }
    const char *nl = "\r\n";
    while (*nl) {
        while ((USART2_DBG->SR & (1u << 7)) == 0u) {
        }
        USART2_DBG->DR = (uint32_t)(uint8_t)(*nl++);
    }
    #endif
    while (1) {
        ;
    }
}

// Arm Compiler may emit calls to __aeabi_assert for assert() even in freestanding
// builds. Provide a minimal implementation to satisfy the linker.
void __aeabi_assert(const char *expr, const char *file, int line) {
    (void)expr;
    (void)file;
    (void)line;
    __fatal_error("assert");
}

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

#if MICROPY_MIN_USE_CORTEX_CPU && (defined(__GNUC__) || defined(__clang__))

// this is a minimal IRQ and reset framework for any Cortex-M CPU

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;

void Reset_Handler(void) __attribute__((naked));
void Reset_Handler(void) {
    // set stack pointer
    __asm volatile ("ldr sp, =_estack");
    // copy .data section from flash to RAM
    for (uint32_t *src = &_sidata, *dest = &_sdata; dest < &_edata;) {
        *dest++ = *src++;
    }
    // zero out .bss section
    for (uint32_t *dest = &_sbss; dest < &_ebss;) {
        *dest++ = 0;
    }
    // jump to board initialisation
    void _start(void);
    _start();
}

void Default_Handler(void) {
    for (;;) {
    }
}

const uint32_t isr_vector[] __attribute__((section(".isr_vector"))) = {
    (uint32_t)&_estack,
    (uint32_t)&Reset_Handler,
    (uint32_t)&Default_Handler, // NMI_Handler
    (uint32_t)&Default_Handler, // HardFault_Handler
    (uint32_t)&Default_Handler, // MemManage_Handler
    (uint32_t)&Default_Handler, // BusFault_Handler
    (uint32_t)&Default_Handler, // UsageFault_Handler
    0,
    0,
    0,
    0,
    (uint32_t)&Default_Handler, // SVC_Handler
    (uint32_t)&Default_Handler, // DebugMon_Handler
    0,
    (uint32_t)&Default_Handler, // PendSV_Handler
    (uint32_t)&Default_Handler, // SysTick_Handler
};

void _start(void) {
    // when we get here: stack is initialised, bss is clear, data is copied

    // SCB->CCR: enable 8-byte stack alignment for IRQ handlers, in accord with EABI
    *((volatile uint32_t *)0xe000ed14) |= 1 << 9;

    // initialise the cpu and peripherals
    #if MICROPY_MIN_USE_STM32_MCU
    void stm32_init(void);
    stm32_init();
    #endif

    // now that we have a basic system up and running we can call main
    main(0, NULL);

    // we must not return
    for (;;) {
    }
}

#endif

#if MICROPY_MIN_USE_STM32_MCU

// this is minimal set-up code for an STM32 MCU

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    uint32_t _1[8];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t _2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} periph_rcc_t;

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint16_t BSRRL;
    volatile uint16_t BSRRH;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} periph_gpio_t;

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
} periph_uart_t;

#define USART1 ((periph_uart_t *)0x40011000)
#define GPIOA  ((periph_gpio_t *)0x40020000)
#define GPIOB  ((periph_gpio_t *)0x40020400)
#define RCC    ((periph_rcc_t *)0x40023800)

// simple GPIO interface
#define GPIO_MODE_IN (0)
#define GPIO_MODE_OUT (1)
#define GPIO_MODE_ALT (2)
#define GPIO_PULL_NONE (0)
#define GPIO_PULL_UP (0)
#define GPIO_PULL_DOWN (1)
void gpio_init(periph_gpio_t *gpio, int pin, int mode, int pull, int alt) {
    gpio->MODER = (gpio->MODER & ~(3 << (2 * pin))) | (mode << (2 * pin));
    // OTYPER is left as default push-pull
    // OSPEEDR is left as default low speed
    gpio->PUPDR = (gpio->PUPDR & ~(3 << (2 * pin))) | (pull << (2 * pin));
    gpio->AFR[pin >> 3] = (gpio->AFR[pin >> 3] & ~(15 << (4 * (pin & 7)))) | (alt << (4 * (pin & 7)));
}
#define gpio_get(gpio, pin) ((gpio->IDR >> (pin)) & 1)
#define gpio_set(gpio, pin, value) do { gpio->ODR = (gpio->ODR & ~(1 << (pin))) | (value << pin); } while (0)
#define gpio_low(gpio, pin) do { gpio->BSRRH = (1 << (pin)); } while (0)
#define gpio_high(gpio, pin) do { gpio->BSRRL = (1 << (pin)); } while (0)

void stm32_init(void) {
    // basic MCU config
    RCC->CR |= (uint32_t)0x00000001; // set HSION
    RCC->CFGR = 0x00000000; // reset all
    RCC->CR &= (uint32_t)0xfef6ffff; // reset HSEON, CSSON, PLLON
    RCC->PLLCFGR = 0x24003010; // reset PLLCFGR
    RCC->CR &= (uint32_t)0xfffbffff; // reset HSEBYP
    RCC->CIR = 0x00000000; // disable IRQs

    // leave the clock as-is (internal 16MHz)

    // enable GPIO clocks
    RCC->AHB1ENR |= 0x00000003; // GPIOAEN, GPIOBEN

    // turn on an LED! (on pyboard it's the red one)
    gpio_init(GPIOA, 13, GPIO_MODE_OUT, GPIO_PULL_NONE, 0);
    gpio_high(GPIOA, 13);

    // enable UART1 at 9600 baud (TX=B6, RX=B7)
    gpio_init(GPIOB, 6, GPIO_MODE_ALT, GPIO_PULL_NONE, 7);
    gpio_init(GPIOB, 7, GPIO_MODE_ALT, GPIO_PULL_NONE, 7);
    RCC->APB2ENR |= 0x00000010; // USART1EN
    USART1->BRR = (104 << 4) | 3; // 16MHz/(16*104.1875) = 9598 baud
    USART1->CR1 = 0x0000200c; // USART enable, tx enable, rx enable
}

#endif
