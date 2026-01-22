/*
 * Minimal hardware I2C support for STM32F405 (pyBaseV1.1)
 */

#include "py/runtime.h"
#include "py/mperrno.h"
#include <string.h>
#include "i2c.h"
#include "mphalport.h"

#if MICROPY_HW_ENABLE_HW_I2C

static I2C_HandleTypeDef I2CHandle1;
static I2C_HandleTypeDef I2CHandle2;
static uint16_t i2c_timeout_ms[MICROPY_HW_MAX_I2C];

void i2c_init0(void) {
#if defined(MICROPY_HW_I2C1_SCL)
    I2CHandle1.Instance = I2C1;
#endif
#if defined(MICROPY_HW_I2C2_SCL)
    I2CHandle2.Instance = I2C2;
#endif
}

I2C_HandleTypeDef *i2c_get_handle(i2c_t *i2c) {
    if (i2c == I2C1) {
        return &I2CHandle1;
    }
#if defined(I2C2)
    if (i2c == I2C2) {
        return &I2CHandle2;
    }
#endif
    return NULL;
}

static int i2c_hal_status_to_errno(HAL_StatusTypeDef status, I2C_HandleTypeDef *hi2c) {
    if (status == HAL_OK) {
        return 0;
    }
    if (status == HAL_TIMEOUT) {
        return -MP_ETIMEDOUT;
    }
    if (status == HAL_BUSY) {
        return -MP_EBUSY;
    }
    if (hi2c && (hi2c->ErrorCode & HAL_I2C_ERROR_AF)) {
        return -MP_ENODEV;
    }
    return -MP_EIO;
}

int i2c_init(i2c_t *i2c, mp_hal_pin_obj_t scl, mp_hal_pin_obj_t sda, uint32_t freq, uint16_t timeout_ms) {
    int i2c_id = 0;
    if (i2c == I2C1) {
        i2c_id = 1;
        __HAL_RCC_I2C1_CLK_ENABLE();
    }
#if defined(I2C2)
    else if (i2c == I2C2) {
        i2c_id = 2;
        __HAL_RCC_I2C2_CLK_ENABLE();
    }
#endif
    else {
        return -MP_EINVAL;
    }

    mp_hal_gpio_clock_enable(scl->gpio);
    mp_hal_gpio_clock_enable(sda->gpio);

    if (!mp_hal_pin_config_alt(scl, MP_HAL_PIN_MODE_ALT_OPEN_DRAIN, MP_HAL_PIN_PULL_UP, AF_FN_I2C, i2c_id)) {
        return -MP_EPERM;
    }
    if (!mp_hal_pin_config_alt(sda, MP_HAL_PIN_MODE_ALT_OPEN_DRAIN, MP_HAL_PIN_PULL_UP, AF_FN_I2C, i2c_id)) {
        return -MP_EPERM;
    }

    I2C_HandleTypeDef *hi2c = i2c_get_handle(i2c);
    if (hi2c == NULL) {
        return -MP_EINVAL;
    }

    hi2c->Init.ClockSpeed = (freq > 400000) ? 400000 : freq;
    hi2c->Init.DutyCycle = (hi2c->Init.ClockSpeed > 100000) ? I2C_DUTYCYCLE_2 : I2C_DUTYCYCLE_2;
    hi2c->Init.OwnAddress1 = 0;
    hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c->Init.OwnAddress2 = 0;
    hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(hi2c) != HAL_OK) {
        return -MP_EIO;
    }

    i2c_timeout_ms[i2c_id - 1] = timeout_ms;
    return 0;
}

int i2c_transfer(i2c_t *i2c, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags) {
    I2C_HandleTypeDef *hi2c = i2c_get_handle(i2c);
    if (hi2c == NULL) {
        return -MP_EINVAL;
    }

    int i2c_id = (i2c == I2C1) ? 1 : 2;
    uint32_t timeout = i2c_timeout_ms[i2c_id - 1];
    if (timeout == 0) {
        timeout = 50;
    }

    bool read = (flags & MP_MACHINE_I2C_FLAG_READ) != 0;
    int num_acks = 0;

    for (size_t i = 0; i < n; ++i) {
        HAL_StatusTypeDef status;
        if (read) {
            status = HAL_I2C_Master_Receive(hi2c, addr << 1, bufs[i].buf, bufs[i].len, timeout);
        } else {
            status = HAL_I2C_Master_Transmit(hi2c, addr << 1, bufs[i].buf, bufs[i].len, timeout);
            if (status == HAL_OK) {
                num_acks += bufs[i].len;
            }
        }

        int err = i2c_hal_status_to_errno(status, hi2c);
        if (err != 0) {
            return err;
        }
    }

    return num_acks;
}

int i2c_find_peripheral(mp_obj_t id) {
    int i2c_id = 0;
    if (mp_obj_is_str(id)) {
        const char *port = mp_obj_str_get_str(id);
        if (0) {
#ifdef MICROPY_HW_I2C1_NAME
        } else if (strcmp(port, MICROPY_HW_I2C1_NAME) == 0) {
            i2c_id = 1;
#endif
#ifdef MICROPY_HW_I2C2_NAME
        } else if (strcmp(port, MICROPY_HW_I2C2_NAME) == 0) {
            i2c_id = 2;
#endif
        } else {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("I2C(%s) doesn't exist"), port);
        }
    } else {
        i2c_id = mp_obj_get_int(id);
        if (i2c_id < 1 || i2c_id > MICROPY_HW_MAX_I2C) {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("I2C(%d) doesn't exist"), i2c_id);
        }
#if !defined(MICROPY_HW_I2C1_SCL)
        if (i2c_id == 1) {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("I2C(%d) doesn't exist"), i2c_id);
        }
#endif
#if !defined(MICROPY_HW_I2C2_SCL)
        if (i2c_id == 2) {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("I2C(%d) doesn't exist"), i2c_id);
        }
#endif
    }
    return i2c_id;
}

#endif // MICROPY_HW_ENABLE_HW_I2C