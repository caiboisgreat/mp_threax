/*
 * Minimal hardware I2C support for STM32F405 (pyBaseV1.1)
 */
#pragma once

#include <stdint.h>
#include "py/obj.h"
#include "py/mphal.h"
#include "extmod/modmachine.h"
#include "pin.h"
#include "stm32f4xx_hal.h"

typedef I2C_TypeDef i2c_t;

void i2c_init0(void);
I2C_HandleTypeDef *i2c_get_handle(i2c_t *i2c);
int i2c_init(i2c_t *i2c, mp_hal_pin_obj_t scl, mp_hal_pin_obj_t sda, uint32_t freq, uint16_t timeout_ms);
int i2c_transfer(i2c_t *i2c, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags);
int i2c_find_peripheral(mp_obj_t id);