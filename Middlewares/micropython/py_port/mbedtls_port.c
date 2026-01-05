#include "py/mpconfig.h"

#if MICROPY_PY_SSL && MICROPY_SSL_MBEDTLS

#include "mbedtls/platform_time.h"

// Use STM32 HAL tick as a monotonic-ish millisecond source.
// This is sufficient for mbedTLS session ticket timing.
//
// Note: This does not provide cryptographic entropy.
#include "stm32f4xx_hal.h"

mbedtls_ms_time_t mbedtls_ms_time(void) {
    return (mbedtls_ms_time_t)HAL_GetTick();
}

#endif
