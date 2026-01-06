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

// Provide a coarse libc-style time() for mbedTLS.
// This is based on the HAL tick and is suitable for relative timeouts.
time_t time(time_t *t) {
    time_t now = (time_t)(HAL_GetTick() / 1000);
    if (t != NULL) {
        *t = now;
    }
    return now;
}

#endif
