#include "py/mpconfig.h"

#if MICROPY_PY_BLUETOOTH

#include <stddef.h>
#include <stdint.h>

#include "py/mphal.h"

#include "extmod/mpbthci.h"
#include "extmod/nimble/hal/hal_uart.h"

// This port currently uses USART2 for the REPL (see uart_core.c).
// For a real BLE setup you almost certainly want to dedicate a separate UART
// to the BLE controller (HCI H4), and update this binding to use that UART.
#include "usart.h"

// Scratch buffer used by NimBLE hal_uart.c when sending HCI commands.
uint8_t mp_bluetooth_hci_cmd_buf[4 + 256];

// ---------------------------------------------------------------------------
// Optional controller power-management hooks.

int mp_bluetooth_hci_controller_init(void) {
    return 0;
}

int mp_bluetooth_hci_controller_deinit(void) {
    return 0;
}

int mp_bluetooth_hci_controller_sleep_maybe(void) {
    return 0;
}

bool mp_bluetooth_hci_controller_woken(void) {
    return false;
}

int mp_bluetooth_hci_controller_wakeup(void) {
    return 0;
}

// ---------------------------------------------------------------------------
// HCI UART bindings required by extmod/mpbthci.h

int mp_bluetooth_hci_uart_init(uint32_t port, uint32_t baudrate) {
    (void)port;
    (void)baudrate;

    // UART init is assumed to be done by CubeMX-generated init (e.g. MX_USARTx_UART_Init).
    // If you want to change baudrate at runtime, enable and implement it here.
    return 0;
}

int mp_bluetooth_hci_uart_deinit(void) {
    return 0;
}

int mp_bluetooth_hci_uart_set_baudrate(uint32_t baudrate) {
    (void)baudrate;
    return 0;
}

int mp_bluetooth_hci_uart_any(void) {
    // RXNE
    return __HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) ? 1 : 0;
}

int mp_bluetooth_hci_uart_write(const uint8_t *buf, size_t len) {
    // Blocking transmit. For best performance this should be DMA.
    if (HAL_UART_Transmit(&huart2, (uint8_t *)(void *)buf, (uint16_t)len, 1000) != HAL_OK) {
        return -1;
    }
    return (int)len;
}

int mp_bluetooth_hci_uart_readchar(void) {
    uint8_t c;

    // Non-blocking receive.
    if (HAL_UART_Receive(&huart2, &c, 1, 0) == HAL_OK) {
        return (int)c;
    }
    return -1;
}

int mp_bluetooth_hci_uart_readpacket(mp_bluetooth_hci_uart_readchar_t handler) {
    // This port uses byte-read mode by default, so packet mode is not required.
    // Implement this if you switch MICROPY_PY_BLUETOOTH_HCI_READ_MODE to PACKET.
    (void)handler;
    return -1;
}

// ---------------------------------------------------------------------------
// Required by extmod/nimble/nimble/nimble_npl_os.c

void mp_bluetooth_nimble_hci_uart_wfi(void) {
    // Poll the HCI UART without running NimBLE eventq (needed for synchronous HCI acks).
    mp_bluetooth_nimble_hci_uart_process(false);

    // Yield a little to avoid a tight spin.
    mp_hal_delay_ms(1);
}

#endif // MICROPY_PY_BLUETOOTH
