#include "py/mpconfig.h"

#if MICROPY_MIN_USE_STDOUT
#include <unistd.h>
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
    // wait for RXNE
    while ((USART2_REPL->SR & (1 << 5)) == 0) {
    }
    c = (unsigned char)USART2_REPL->DR;
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
    while (len--) {
        // wait for TXE
        while ((USART2_REPL->SR & (1 << 7)) == 0) {
        }
        USART2_REPL->DR = (uint32_t)(uint8_t)(*str++);
    }
    #endif
    return ret;
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
