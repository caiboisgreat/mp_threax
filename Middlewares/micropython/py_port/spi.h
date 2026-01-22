/*
 * Minimal hardware SPI support for STM32F405 (pyBaseV1.1)
 */
#pragma once

#include <stdint.h>
#include "py/obj.h"
#include "drivers/bus/spi.h"
#include "stm32f4xx_hal.h"

typedef struct _spi_t {
    SPI_HandleTypeDef *spi;
} spi_t;

typedef struct _machine_hard_spi_obj_t {
    mp_obj_base_t base;
    const spi_t *spi;
} machine_hard_spi_obj_t;

extern const spi_t spi_obj[2];

void spi_init0(void);
int spi_init(const spi_t *spi, bool enable_nss_pin);
void spi_deinit(const spi_t *spi_obj);
int spi_find_index(mp_obj_t id);
void spi_set_params(const spi_t *spi_obj, uint32_t prescale, int32_t baudrate,
    int32_t polarity, int32_t phase, int32_t bits, int32_t firstbit);
void spi_transfer(const spi_t *self, size_t len, const uint8_t *src, uint8_t *dest, uint32_t timeout);
void spi_print(const mp_print_t *print, const spi_t *spi_obj, bool legacy);

// Transfer timeout (ms) for len bytes.
#define SPI_TRANSFER_TIMEOUT(len) ((len) + 100)