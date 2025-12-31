#include "py/mpconfig.h"

#if MICROPY_MIN_USE_STDOUT
#include <unistd.h>
#endif

#include <string.h>

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
#endif

// Receive single character
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    #if MICROPY_MIN_USE_STDOUT
    int r = read(STDIN_FILENO, &c, 1);
    (void)r;
    #elif MICROPY_MIN_USE_STM32_MCU
    // Prefer HAL-based RX to play nicely with Cube/HAL init and potential ISR state.
    // This blocks until a byte arrives.
    if (HAL_UART_Receive(&huart2, &c, 1, HAL_MAX_DELAY) != HAL_OK) {
        // If RX errors happen, clear common flags and retry.
        __HAL_UART_CLEAR_OREFLAG(&huart2);
        __HAL_UART_CLEAR_NEFLAG(&huart2);
        __HAL_UART_CLEAR_FEFLAG(&huart2);
        __HAL_UART_CLEAR_PEFLAG(&huart2);
        (void)HAL_UART_Receive(&huart2, &c, 1, HAL_MAX_DELAY);
    }

    // Normalise line endings for MicroPython's readline(): it treats '\r' as
    // the end-of-line character (see shared/readline/readline.c).
    // - If the terminal sends CRLF, swallow the LF and return '\r'.
    // - If the terminal sends LF only, map it to '\r'.
    if (c == '\r') {
        // Best-effort consume a following '\n' if it is already pending.
        if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE)) {
            unsigned char c2;
            (void)HAL_UART_Receive(&huart2, &c2, 1, 0);
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
