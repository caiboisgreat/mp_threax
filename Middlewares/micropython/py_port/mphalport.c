/*
 * HAL port implementation for STM32F405 + ThreadX
 */

#include "py/mphal.h"
#include "py/runtime.h"
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

mp_hal_pin_obj_t mp_hal_get_pin_obj(mp_obj_t pin) {
    return pin_find(pin);
}

qstr mp_hal_pin_name(mp_hal_pin_obj_t pin) {
    return pin->name;
}

static uint32_t mp_hal_mode_to_gpio(uint32_t mode) {
    switch (mode) {
        case MP_HAL_PIN_MODE_ALT_OPEN_DRAIN:
            return GPIO_MODE_AF_OD;
        case MP_HAL_PIN_MODE_ALT:
            return GPIO_MODE_AF_PP;
        case MP_HAL_PIN_MODE_OPEN_DRAIN:
            return GPIO_MODE_OUTPUT_OD;
        case MP_HAL_PIN_MODE_OUTPUT:
            return GPIO_MODE_OUTPUT_PP;
        case MP_HAL_PIN_MODE_ANALOG:
            return GPIO_MODE_ANALOG;
        case MP_HAL_PIN_MODE_INPUT:
        default:
            return GPIO_MODE_INPUT;
    }
}

static uint32_t mp_hal_pull_to_gpio(uint32_t pull) {
    switch (pull) {
        case MP_HAL_PIN_PULL_UP:
            return GPIO_PULLUP;
        case MP_HAL_PIN_PULL_DOWN:
            return GPIO_PULLDOWN;
        case MP_HAL_PIN_PULL_NONE:
        default:
            return GPIO_NOPULL;
    }
}

bool mp_hal_pin_config_alt(mp_hal_pin_obj_t pin, uint32_t mode, uint32_t pull, uint32_t af_fn, uint32_t unit) {
    uint32_t af = 0xFFFFFFFFu;

    if (af_fn == AF_FN_I2C) {
        if (unit == 1) {
            if ((pin->gpio == GPIOB && pin->pin == 6) || (pin->gpio == GPIOB && pin->pin == 7)) {
                af = GPIO_AF4_I2C1;
            }
        } else if (unit == 2) {
            if ((pin->gpio == GPIOB && pin->pin == 10) || (pin->gpio == GPIOB && pin->pin == 11)) {
                af = GPIO_AF4_I2C2;
            }
        }
    } else if (af_fn == AF_FN_SPI) {
        if (unit == 1) {
            if ((pin->gpio == GPIOA && pin->pin == 4)
                || (pin->gpio == GPIOA && pin->pin == 5)
                || (pin->gpio == GPIOA && pin->pin == 6)
                || (pin->gpio == GPIOA && pin->pin == 7)) {
                af = GPIO_AF5_SPI1;
            }
        } else if (unit == 2) {
            if ((pin->gpio == GPIOB && pin->pin == 12)
                || (pin->gpio == GPIOB && pin->pin == 13)
                || (pin->gpio == GPIOB && pin->pin == 14)
                || (pin->gpio == GPIOB && pin->pin == 15)) {
                af = GPIO_AF5_SPI2;
            }
        }
    } else if (af_fn == AF_FN_UART) {
        // STM32F4: USART1-3 use AF7, UART4-5 and USART6 use AF8
        if (unit == 1) {
            af = GPIO_AF7_USART1;
        } else if (unit == 2) {
            af = GPIO_AF7_USART2;
        } else if (unit == 3) {
            af = GPIO_AF7_USART3;
        } else if (unit == 4) {
            af = GPIO_AF8_UART4;
        } else if (unit == 5) {
            af = GPIO_AF8_UART5;
        } else if (unit == 6) {
            af = GPIO_AF8_USART6;
        }
    } else if (af_fn == AF_FN_LPUART) {
        // STM32F405 has no LPUART, return failure
        return false;
    }

    if (af == 0xFFFFFFFFu) {
        return false;
    }

    mp_hal_pin_config(pin, mp_hal_mode_to_gpio(mode), mp_hal_pull_to_gpio(pull), af);
    return true;
}

void mp_hal_pin_open_drain(mp_hal_pin_obj_t pin) {
    mp_hal_pin_config(pin, GPIO_MODE_OUTPUT_OD, GPIO_PULLUP, 0);
}

void mp_hal_pin_od_high(mp_hal_pin_obj_t pin) {
    mp_hal_pin_open_drain(pin);
    mp_hal_pin_write(pin, 1);
}

void mp_hal_pin_od_low(mp_hal_pin_obj_t pin) {
    mp_hal_pin_open_drain(pin);
    mp_hal_pin_write(pin, 0);
}

