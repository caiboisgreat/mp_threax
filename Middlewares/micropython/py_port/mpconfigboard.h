/*
 * Board-specific configuration for STM32F405RG + ThreadX
 * Based on MicroPython pyboard v1.1
 */

#ifndef MICROPY_INCLUDED_MPCONFIGBOARD_H
#define MICROPY_INCLUDED_MPCONFIGBOARD_H

// Board and MCU name
#define MICROPY_HW_BOARD_NAME       "pyBaseV1.1"
#define MICROPY_HW_MCU_NAME         "STM32F405RG"

// The pyboard has 4 LEDs with PWM support on LED3 and LED4
#define MICROPY_HW_LED1             (&pin_A13) // red
#define MICROPY_HW_LED2             (&pin_A14) // green
#define MICROPY_HW_LED3             (&pin_A15) // yellow
#define MICROPY_HW_LED4             (&pin_B4)  // blue

// PWM configuration for LED3 (PA15 - TIM2_CH1) and LED4 (PB4 - TIM3_CH1)
#define MICROPY_HW_LED3_PWM         { TIM2, 2, TIM_CHANNEL_1, GPIO_AF1_TIM2 }
#define MICROPY_HW_LED4_PWM         { TIM3, 3, TIM_CHANNEL_1, GPIO_AF2_TIM3 }

// LED control macros
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// I2C buses (match Pyboard v1.1 X/Y headers)
#define MICROPY_HW_I2C1_NAME        "X"
#define MICROPY_HW_I2C1_SCL         (&pin_B6)  // X9
#define MICROPY_HW_I2C1_SDA         (&pin_B7)  // X10
#define MICROPY_HW_I2C2_NAME        "Y"
#define MICROPY_HW_I2C2_SCL         (&pin_B10) // Y9
#define MICROPY_HW_I2C2_SDA         (&pin_B11) // Y10

// SPI buses (match Pyboard v1.1 X/Y headers)
#define MICROPY_HW_SPI1_NAME        "X"
#define MICROPY_HW_SPI1_NSS         (&pin_A4)  // X5
#define MICROPY_HW_SPI1_SCK         (&pin_A5)  // X6
#define MICROPY_HW_SPI1_MISO        (&pin_A6)  // X7
#define MICROPY_HW_SPI1_MOSI        (&pin_A7)  // X8
#define MICROPY_HW_SPI2_NAME        "Y"
#define MICROPY_HW_SPI2_NSS         (&pin_B12) // Y5
#define MICROPY_HW_SPI2_SCK         (&pin_B13) // Y6
#define MICROPY_HW_SPI2_MISO        (&pin_B14) // Y7
#define MICROPY_HW_SPI2_MOSI        (&pin_B15) // Y8

#endif // MICROPY_INCLUDED_MPCONFIGBOARD_H
