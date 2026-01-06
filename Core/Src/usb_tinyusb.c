#include "usb_tinyusb.h"

#include "stm32f4xx_hal.h"

// TinyUSB
#include "tusb.h"

// TinyUSB requires a timebase in milliseconds.
uint32_t tusb_time_millis_api(void) {
    return HAL_GetTick();
}

// MicroPython TinyUSB descriptor helper expects this hook.
// It must write a NUL-terminated ASCII string, up to MICROPY_HW_USB_DESC_STR_MAX chars.
void mp_usbd_port_get_serial_number(char *buf) {
    if (buf == NULL) {
        return;
    }

    // STM32F4 unique device ID: 96-bit at 0x1FFF7A10.
    const uint32_t *uid = (const uint32_t *)0x1FFF7A10u;
    uint8_t bytes[12];
    bytes[0]  = (uint8_t)(uid[0] >> 0);
    bytes[1]  = (uint8_t)(uid[0] >> 8);
    bytes[2]  = (uint8_t)(uid[0] >> 16);
    bytes[3]  = (uint8_t)(uid[0] >> 24);
    bytes[4]  = (uint8_t)(uid[1] >> 0);
    bytes[5]  = (uint8_t)(uid[1] >> 8);
    bytes[6]  = (uint8_t)(uid[1] >> 16);
    bytes[7]  = (uint8_t)(uid[1] >> 24);
    bytes[8]  = (uint8_t)(uid[2] >> 0);
    bytes[9]  = (uint8_t)(uid[2] >> 8);
    bytes[10] = (uint8_t)(uid[2] >> 16);
    bytes[11] = (uint8_t)(uid[2] >> 24);

    static const char hex[] = "0123456789ABCDEF";
    // 12 bytes -> 24 hex chars
    for (int i = 0; i < 12; i++) {
        buf[i * 2 + 0] = hex[(bytes[i] >> 4) & 0xF];
        buf[i * 2 + 1] = hex[(bytes[i] >> 0) & 0xF];
    }
    buf[24] = '\0';
}

void mp_threadx_usb_fs_init(void) {
    // Enable GPIOA for USB pins
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &gpio);

    // Enable USB OTG FS clock
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

    // Disable VBUS sensing (works even if PA9 is not wired).
    // This matches common bare-metal bring-up patterns.
    USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
    USB_OTG_FS->GCCFG &= ~(USB_OTG_GCCFG_VBUSASEN | USB_OTG_GCCFG_VBUSBSEN);

    // Enable USB interrupts
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);

    // Optional: wakeup interrupt is not required for basic MSC.
    // HAL_NVIC_SetPriority(OTG_FS_WKUP_IRQn, 5, 0);
    // HAL_NVIC_EnableIRQ(OTG_FS_WKUP_IRQn);
}

// If the linker pulls this file, ensure TinyUSB can call connect.
// (No additional glue required here.)
