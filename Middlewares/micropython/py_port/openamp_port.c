#include <stdint.h>

// Backing memory used by modopenamp.c via openamp_config_port.h.
// Align to 32 bytes to satisfy VRING_ALIGNMENT.
__attribute__((aligned(32))) uint8_t mp_openamp_shm[0x8000];
__attribute__((aligned(32))) uint8_t mp_openamp_rsc[0x400];

// OpenAMP expects the platform to provide a notification function.
// For this STM32F405 single-core build, this is a stub.
int metal_rproc_notify(void *priv, uint32_t id) {
    (void)priv;
    (void)id;
    return 0;
}
