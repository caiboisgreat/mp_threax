/*
 * HAL port implementation for STM32F405 + ThreadX
 */

#include "py/mphal.h"
#include "pin.h"
#include "stm32f4xx_hal.h"

// Enable GPIO clock for a port
void mp_hal_gpio_clock_enable(GPIO_TypeDef *gpio) {
    if (gpio == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (gpio == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (gpio == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (gpio == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (gpio == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (gpio == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }
}

// Configure pin
void mp_hal_pin_config(const machine_pin_obj_t *pin, uint32_t mode, uint32_t pull, uint32_t alt) {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pin->pin_mask;
    GPIO_InitStructure.Mode = mode;
    GPIO_InitStructure.Pull = pull;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Alternate = alt;
    HAL_GPIO_Init(pin->gpio, &GPIO_InitStructure);
}

// Set pin as output
void mp_hal_pin_output(const machine_pin_obj_t *pin) {
    mp_hal_pin_config(pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
}

// Set pin as input
void mp_hal_pin_input(const machine_pin_obj_t *pin) {
    mp_hal_pin_config(pin, GPIO_MODE_INPUT, GPIO_NOPULL, 0);
}

// Set pin low
void mp_hal_pin_low(const machine_pin_obj_t *pin) {
    pin->gpio->BSRR = pin->pin_mask << 16;
}

// Set pin high
void mp_hal_pin_high(const machine_pin_obj_t *pin) {
    pin->gpio->BSRR = pin->pin_mask;
}

