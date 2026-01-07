#ifndef MICROPY_INCLUDED_EXTMOD_NIMBLE_MPNIMBLEPORT_H
#define MICROPY_INCLUDED_EXTMOD_NIMBLE_MPNIMBLEPORT_H

// Port-specific configuration for MicroPython's NimBLE integration.
//
// STM32F405 does not have an on-chip BLE controller, so this port expects an
// external controller connected via HCI UART (H4).
//
// Note: The current bring-up uses USART2 (shared with REPL) as a placeholder.
// For real use, dedicate a separate UART for the BLE controller.

#ifndef MICROPY_HW_BLE_UART_ID
#define MICROPY_HW_BLE_UART_ID (2)
#endif

#ifndef MICROPY_HW_BLE_UART_BAUDRATE
#define MICROPY_HW_BLE_UART_BAUDRATE (115200)
#endif

// NimBLE syscfg expects HAL_UART_PARITY_NONE.
#ifndef HAL_UART_PARITY_NONE
#ifdef UART_PARITY_NONE
#define HAL_UART_PARITY_NONE UART_PARITY_NONE
#else
#define HAL_UART_PARITY_NONE (0)
#endif
#endif

#endif // MICROPY_INCLUDED_EXTMOD_NIMBLE_MPNIMBLEPORT_H
