#include "py/mpconfig.h"

// Avoid pulling in py/repl.h (it depends on MP_SYS_MUTABLE_PS1/PS2 which this
// bare-metal port does not define). We only need Ctrl-A here.
#ifndef CHAR_CTRL_A
#define CHAR_CTRL_A (1)
#endif

#if MICROPY_MIN_USE_STDOUT
#include <unistd.h>
#endif

#include <string.h>
#include <stdio.h>

// DEBUG: track recent control characters for Thonny raw-REPL troubleshooting
#define CTRL_TRACE_SIZE 32
static volatile uint8_t ctrl_trace[CTRL_TRACE_SIZE];
static volatile uint8_t ctrl_trace_idx = 0;
static void trace_ctrl(uint8_t c) {
    if (c > 0 && c < 0x20) {
        ctrl_trace[ctrl_trace_idx] = c;
        ctrl_trace_idx = (ctrl_trace_idx + 1) % CTRL_TRACE_SIZE;
    }
}

#if MICROPY_MIN_USE_STM32_MCU
#include "stm32f4xx_hal.h"
#include "usart.h"
extern UART_HandleTypeDef huart2;
#endif

/*
 * Core UART functions to implement for a port
 */

#if MICROPY_MIN_USE_STM32_MCU
typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
} periph_uart_t;
// STM32F405: USART2 base is 0x40004400. This project configures REPL on USART2.
#define USART2_REPL ((periph_uart_t *)0x40004400)

// Interrupt-driven RX ring buffer for USART2 (REPL).
// Motivation: host tools (Thonny/mpremote/pyboard) often send bursts of bytes
// (e.g. "\r\x03\x03\x01") while the firmware is also printing prompts. If the
// firmware reads RX in a blocking, byte-at-a-time way, it's easy to trigger
// UART overrun and lose Ctrl-A, which breaks entry to raw REPL.
#ifndef MICROPY_REPL_UART_RX_BUF_SIZE
#define MICROPY_REPL_UART_RX_BUF_SIZE (256u)
#endif

static volatile uint16_t uart2_rx_head;
static volatile uint16_t uart2_rx_tail;
static uint8_t uart2_rx_buf[MICROPY_REPL_UART_RX_BUF_SIZE];

static inline uint16_t uart2_rx_next(uint16_t idx) {
    return (uint16_t)((idx + 1u) % MICROPY_REPL_UART_RX_BUF_SIZE);
}

static inline int uart2_rxbuf_get(void) {
    uint16_t tail = uart2_rx_tail;
    if (tail == uart2_rx_head) {
        return -1;
    }
    int c = uart2_rx_buf[tail];
    uart2_rx_tail = uart2_rx_next(tail);
    return c;
}

static inline int uart2_rxbuf_peek(void) {
    uint16_t tail = uart2_rx_tail;
    if (tail == uart2_rx_head) {
        return -1;
    }
    return uart2_rx_buf[tail];
}

static inline void uart2_rxbuf_drop(void) {
    uint16_t tail = uart2_rx_tail;
    if (tail != uart2_rx_head) {
        uart2_rx_tail = uart2_rx_next(tail);
    }
}

void USART2_IRQHandler(void) {
    // Read all pending bytes.
    // Clearing of RXNE/ORE/etc is done by reading SR followed by DR.
    for (;;) {
        uint32_t sr = USART2_REPL->SR;

        // Handle and clear errors by reading SR then DR.
        if (sr & ((uint32_t)(1u << 3) /*ORE*/ | (uint32_t)(1u << 2) /*NE*/ | (uint32_t)(1u << 1) /*FE*/ | (uint32_t)(1u << 0) /*PE*/)) {
            (void)USART2_REPL->DR;
        }

        if ((sr & (1u << 5) /*RXNE*/) == 0u) {
            break;
        }

        uint8_t c = (uint8_t)USART2_REPL->DR;
        trace_ctrl(c);  // record control chars for debug
        uint16_t head = uart2_rx_head;
        uint16_t next = uart2_rx_next(head);
        if (next != uart2_rx_tail) {
            uart2_rx_buf[head] = c;
            uart2_rx_head = next;
        } else {
            // Buffer full: drop byte.
        }
    }
}
#endif

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    #if MICROPY_MIN_USE_STM32_MCU
    // Single-byte pushback buffer used to avoid losing a character when
    // normalising CRLF. This is critical for hosts (e.g. Thonny) that send
    // sequences like "\r\x01" (CR then Ctrl-A) to enter raw REPL.
    static int pushback_char = -1;
    if (pushback_char >= 0) {
        int c = pushback_char;
        pushback_char = -1;
        return c;
    }
    #endif
    unsigned char c = 0;
    #if MICROPY_MIN_USE_STDOUT
    int r = read(STDIN_FILENO, &c, 1);
    (void)r;
    #elif MICROPY_MIN_USE_STM32_MCU
    // Interrupt-driven RX: block until a byte is available in the ring buffer.
    int ci;
    for (;;) {
        ci = uart2_rxbuf_get();
        if (ci >= 0) {
            c = (unsigned char)ci;
            break;
        }
    }

    // Normalise line endings for MicroPython's readline(): it treats '\r' as
    // the end-of-line character (see shared/readline/readline.c).
    // - If the terminal sends CRLF, swallow the LF and return '\r'.
    // - If the terminal sends LF only, map it to '\r'.
    if (c == '\r') {
        // Host tools often send bursts like "\r\x03\x03\x01" or "\r\x01".
        // When bytes arrive back-to-back the IRQ will buffer them, but the
        // second byte may still be in-flight when we pop '\r'.  Briefly wait
        // for one more byte so we can:
        // - swallow CRLF
        // - prioritise Ctrl-A (enter raw REPL) over treating CR as empty line
        int c2 = -1;
        for (int i = 0; i < 2000; ++i) {
            c2 = uart2_rxbuf_get();
            if (c2 >= 0) {
                break;
            }
        }

        if (c2 == '\n') {
            return '\r';
        }
        if (c2 == CHAR_CTRL_A) {
            return CHAR_CTRL_A;
        }
        if (c2 >= 0) {
            // Preserve the byte for the next call.
            pushback_char = c2;
        }
        return '\r';
    }
    if (c == '\n') {
        return '\r';
    }
    #endif
    return c;
}

// Send string of given length
mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    mp_uint_t ret = len;
    #if MICROPY_MIN_USE_STDOUT
    int r = write(STDOUT_FILENO, str, len);
    if (r >= 0) {
        // in case of an error in the syscall, report no bytes written
        ret = 0;
    }
    #elif MICROPY_MIN_USE_STM32_MCU
    // HAL-based TX: uses the configured baud rate and state machine.
    // Use a bounded timeout proportional to length.
    uint32_t timeout = 200 + (uint32_t)len;
    if (HAL_UART_Transmit(&huart2, (uint8_t *)(void *)str, (uint16_t)len, timeout) != HAL_OK) {
        ret = 0;
    }
    #endif
    return ret;
}

// Send zero-terminated string
void mp_hal_stdout_tx_str(const char *str) {
    mp_hal_stdout_tx_strn(str, (mp_uint_t)strlen(str));
}

// Cooked output: translate \n to \r\n.
void mp_hal_stdout_tx_strn_cooked(const char *str, size_t len) {
    const char *last = str;
    const char *top = str + len;
    while (str < top) {
        if (*str == '\n') {
            if (str > last) {
                mp_hal_stdout_tx_strn(last, (mp_uint_t)(str - last));
            }
            mp_hal_stdout_tx_strn("\r\n", 2);
            ++str;
            last = str;
        } else {
            ++str;
        }
    }
    if (str > last) {
        mp_hal_stdout_tx_strn(last, (mp_uint_t)(str - last));
    }
}

// Diagnostic: print the last control chars received (for debugging raw-REPL entry)
void mp_hal_dump_ctrl_trace(void) {
    mp_hal_stdout_tx_str("\r\n[CTRL trace (last 32)]: ");
    for (int i = 0; i < CTRL_TRACE_SIZE; i++) {
        uint8_t c = ctrl_trace[(ctrl_trace_idx + i) % CTRL_TRACE_SIZE];
        if (c > 0 && c < 0x20) {
            char buf[8];
            snprintf(buf, sizeof(buf), "0x%02X ", c);
            mp_hal_stdout_tx_str(buf);
        }
    }
    mp_hal_stdout_tx_str("\r\n");
}
