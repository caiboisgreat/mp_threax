/*
 * Minimal hardware SPI support for STM32F405 (pyBaseV1.1)
 */

#include "py/runtime.h"
#include "py/mperrno.h"
#include <string.h>
#include "spi.h"
#include "mphalport.h"

#if MICROPY_PY_MACHINE_SPI

static SPI_HandleTypeDef SPIHandle1;
static SPI_HandleTypeDef SPIHandle2;

const spi_t spi_obj[2] = {
#if defined(MICROPY_HW_SPI1_SCK)
    { &SPIHandle1 },
#else
    { NULL },
#endif
#if defined(MICROPY_HW_SPI2_SCK)
    { &SPIHandle2 },
#else
    { NULL },
#endif
};

void spi_init0(void) {
#if defined(MICROPY_HW_SPI1_SCK)
    SPIHandle1.Instance = SPI1;
#endif
#if defined(MICROPY_HW_SPI2_SCK)
    SPIHandle2.Instance = SPI2;
#endif
}

static uint32_t spi_get_source_freq(SPI_HandleTypeDef *spi) {
    if (spi->Instance == SPI1) {
        return HAL_RCC_GetPCLK2Freq();
    }
    return HAL_RCC_GetPCLK1Freq();
}

static uint32_t spi_prescaler_from_baudrate(uint32_t src, uint32_t baudrate) {
    uint32_t div = (baudrate == 0) ? 256 : (src + baudrate - 1) / baudrate;
    if (div <= 2) return SPI_BAUDRATEPRESCALER_2;
    if (div <= 4) return SPI_BAUDRATEPRESCALER_4;
    if (div <= 8) return SPI_BAUDRATEPRESCALER_8;
    if (div <= 16) return SPI_BAUDRATEPRESCALER_16;
    if (div <= 32) return SPI_BAUDRATEPRESCALER_32;
    if (div <= 64) return SPI_BAUDRATEPRESCALER_64;
    if (div <= 128) return SPI_BAUDRATEPRESCALER_128;
    return SPI_BAUDRATEPRESCALER_256;
}

int spi_find_index(mp_obj_t id) {
    int spi_id = 0;
    if (mp_obj_is_str(id)) {
        const char *port = mp_obj_str_get_str(id);
        if (0) {
#ifdef MICROPY_HW_SPI1_NAME
        } else if (strcmp(port, MICROPY_HW_SPI1_NAME) == 0) {
            spi_id = 1;
#endif
#ifdef MICROPY_HW_SPI2_NAME
        } else if (strcmp(port, MICROPY_HW_SPI2_NAME) == 0) {
            spi_id = 2;
#endif
        } else {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("SPI(%s) doesn't exist"), port);
        }
    } else {
        spi_id = mp_obj_get_int(id);
        if (spi_id < 1 || spi_id > (int)MP_ARRAY_SIZE(spi_obj) || spi_obj[spi_id - 1].spi == NULL) {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("SPI(%d) doesn't exist"), spi_id);
        }
    }

    if (spi_obj[spi_id - 1].spi == NULL) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("SPI(%d) doesn't exist"), spi_id);
    }
    return spi_id;
}

void spi_set_params(const spi_t *spi_obj, uint32_t prescale, int32_t baudrate,
    int32_t polarity, int32_t phase, int32_t bits, int32_t firstbit) {
    SPI_HandleTypeDef *spi = spi_obj->spi;
    SPI_InitTypeDef *init = &spi->Init;

    if (prescale != 0xffffffff || baudrate != -1) {
        uint32_t src = spi_get_source_freq(spi);
        uint32_t prescaler = (prescale == 0xffffffff) ? spi_prescaler_from_baudrate(src, baudrate) : prescale;
        init->BaudRatePrescaler = prescaler;
    }

    if (polarity != -1) {
        init->CLKPolarity = polarity == 0 ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
    }
    if (phase != -1) {
        init->CLKPhase = phase == 0 ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
    }
    if (bits != -1) {
        init->DataSize = (bits == 16) ? SPI_DATASIZE_16BIT : SPI_DATASIZE_8BIT;
    }
    if (firstbit != -1) {
        init->FirstBit = firstbit;
    }
}

static int spi_config_pins(const spi_t *self, bool enable_nss_pin, uint32_t unit) {
    const machine_pin_obj_t *pins[4] = { NULL, NULL, NULL, NULL };
    if (unit == 1) {
#if defined(MICROPY_HW_SPI1_NSS)
        pins[0] = MICROPY_HW_SPI1_NSS;
#endif
        pins[1] = MICROPY_HW_SPI1_SCK;
#if defined(MICROPY_HW_SPI1_MISO)
        pins[2] = MICROPY_HW_SPI1_MISO;
#endif
        pins[3] = MICROPY_HW_SPI1_MOSI;
        __HAL_RCC_SPI1_CLK_ENABLE();
    } else if (unit == 2) {
#if defined(MICROPY_HW_SPI2_NSS)
        pins[0] = MICROPY_HW_SPI2_NSS;
#endif
        pins[1] = MICROPY_HW_SPI2_SCK;
#if defined(MICROPY_HW_SPI2_MISO)
        pins[2] = MICROPY_HW_SPI2_MISO;
#endif
        pins[3] = MICROPY_HW_SPI2_MOSI;
        __HAL_RCC_SPI2_CLK_ENABLE();
    } else {
        return -MP_EINVAL;
    }

    uint32_t mode = MP_HAL_PIN_MODE_ALT;
    uint32_t pull = MP_HAL_PIN_PULL_NONE;
    for (uint32_t i = (enable_nss_pin ? 0 : 1); i < 4; i++) {
        if (pins[i] == NULL) {
            continue;
        }
        mp_hal_gpio_clock_enable(pins[i]->gpio);
        if (!mp_hal_pin_config_alt(pins[i], mode, pull, AF_FN_SPI, unit)) {
            return -MP_EINVAL;
        }
    }

    return 0;
}

int spi_init(const spi_t *spi, bool enable_nss_pin) {
    SPI_HandleTypeDef *hspi = spi->spi;
    uint32_t unit = (hspi->Instance == SPI1) ? 1 : 2;

    int ret = spi_config_pins(spi, enable_nss_pin, unit);
    if (ret != 0) {
        return ret;
    }

    hspi->Init.Mode = SPI_MODE_MASTER;
    hspi->Init.Direction = SPI_DIRECTION_2LINES;
    hspi->Init.NSS = SPI_NSS_SOFT;
    hspi->Init.TIMode = SPI_TIMODE_DISABLE;
    hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi->Init.CRCPolynomial = 0;

    if (hspi->Init.BaudRatePrescaler == 0) {
        spi_set_params(spi, 0xffffffff, 500000, 0, 0, 8, SPI_FIRSTBIT_MSB);
    }

    if (HAL_SPI_Init(hspi) != HAL_OK) {
        return -MP_EIO;
    }

    return 0;
}

void spi_deinit(const spi_t *spi_obj) {
    SPI_HandleTypeDef *spi = spi_obj->spi;
    HAL_SPI_DeInit(spi);
    if (spi->Instance == SPI1) {
        __HAL_RCC_SPI1_FORCE_RESET();
        __HAL_RCC_SPI1_RELEASE_RESET();
        __HAL_RCC_SPI1_CLK_DISABLE();
    } else if (spi->Instance == SPI2) {
        __HAL_RCC_SPI2_FORCE_RESET();
        __HAL_RCC_SPI2_RELEASE_RESET();
        __HAL_RCC_SPI2_CLK_DISABLE();
    }
}

void spi_transfer(const spi_t *self, size_t len, const uint8_t *src, uint8_t *dest, uint32_t timeout) {
    HAL_StatusTypeDef status;
    if (src == NULL) {
        status = HAL_SPI_Receive(self->spi, dest, len, timeout);
    } else if (dest == NULL) {
        status = HAL_SPI_Transmit(self->spi, (uint8_t *)src, len, timeout);
    } else {
        status = HAL_SPI_TransmitReceive(self->spi, (uint8_t *)src, dest, len, timeout);
    }

    if (status != HAL_OK) {
        mp_raise_OSError(status == HAL_TIMEOUT ? MP_ETIMEDOUT : MP_EIO);
    }
}

void spi_print(const mp_print_t *print, const spi_t *spi_obj, bool legacy) {
    SPI_HandleTypeDef *spi = spi_obj->spi;
    uint32_t spi_num = (spi->Instance == SPI1) ? 1 : 2;
    mp_printf(print, "SPI(%u", (unsigned)spi_num);
    if (spi->State != HAL_SPI_STATE_RESET) {
        uint32_t src = spi_get_source_freq(spi);
        uint32_t presc = spi->Init.BaudRatePrescaler >> 3;
        uint32_t baudrate = src >> (presc + 1);
        mp_printf(print, ", baudrate=%u, polarity=%u, phase=%u, bits=%u",
            baudrate,
            spi->Init.CLKPolarity == SPI_POLARITY_LOW ? 0 : 1,
            spi->Init.CLKPhase == SPI_PHASE_1EDGE ? 0 : 1,
            spi->Init.DataSize == SPI_DATASIZE_8BIT ? 8 : 16);
        if (legacy) {
            mp_printf(print, ", prescaler=%u", 1u << (presc + 1));
        }
    }
    mp_print_str(print, ")");
}

#endif // MICROPY_PY_MACHINE_SPI