#include <string.h>

#include "py/runtime.h"
#include "py/mperrno.h"
#include "extmod/vfs.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_sd.h"

// ---- SDIO hardware (STM32F405) -------------------------------------------------
//
// This project’s CubeMX .ioc does not configure SDIO/SDMMC, so we provide a
// minimal SDIO bring-up here, using the standard STM32F4 SDIO pinout:
//   PC8  SDIO_D0 (AF12)
//   PC9  SDIO_D1 (AF12)
//   PC10 SDIO_D2 (AF12)
//   PC11 SDIO_D3 (AF12)
//   PC12 SDIO_CK (AF12)
//   PD2  SDIO_CMD (AF12)
//
// If your board uses SPI mode for SD, we can switch later, but SDIO is the
// typical/standard wiring on STM32F4 dev boards.

#ifndef MICROPY_HW_SDCARD_MOUNT_POINT
#define MICROPY_HW_SDCARD_MOUNT_POINT "/sd"
#endif

#define SDCARD_BLOCK_SIZE (512u)

static SD_HandleTypeDef hsd;
static bool sd_inited = false;
static uint32_t sd_num_blocks = 0;

static int sdcard_init_if_needed(void) {
    if (sd_inited) {
        return 0;
    }

    memset(&hsd, 0, sizeof(hsd));
    hsd.Instance = SDIO;

    // A conservative default configuration; HAL_SD_Init will do card init.
    // ClockDiv is for identification phase (should be slow).
    hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
    hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd.Init.ClockDiv = SDIO_INIT_CLK_DIV;

    if (HAL_SD_Init(&hsd) != HAL_OK) {
        return -MP_ENODEV;
    }

    // Try to switch to 4-bit bus (most SDIO sockets are wired for 4-bit).
    (void)HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B);

    HAL_SD_CardInfoTypeDef info;
    if (HAL_SD_GetCardInfo(&hsd, &info) != HAL_OK) {
        return -MP_EIO;
    }

    sd_num_blocks = info.BlockNbr;
    if (sd_num_blocks == 0) {
        return -MP_EIO;
    }

    sd_inited = true;
    return 0;
}

void HAL_SD_MspInit(SD_HandleTypeDef *hsd_) {
    if (hsd_->Instance != SDIO) {
        return;
    }

    __HAL_RCC_SDIO_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;

    // PC8-12: D0..D3, CK
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // PD2: CMD
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd_) {
    if (hsd_->Instance != SDIO) {
        return;
    }

    __HAL_RCC_SDIO_CLK_DISABLE();

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
}

// ---- MicroPython machine.SDCard block device ----------------------------------

typedef struct _mp_obj_sdcard_t {
    mp_obj_base_t base;
} mp_obj_sdcard_t;

static mp_obj_t sdcard_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    mp_obj_sdcard_t *self = mp_obj_malloc(mp_obj_sdcard_t, type);
    int ret = sdcard_init_if_needed();
    if (ret != 0) {
        mp_raise_OSError(-ret);
    }
    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t sdcard_readblocks(mp_obj_t self_in, mp_obj_t block_num_in, mp_obj_t buf_in) {
    (void)self_in;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf_in, &bufinfo, MP_BUFFER_WRITE);

    uint32_t block_num = (uint32_t)mp_obj_get_int(block_num_in);
    uint32_t num_blocks = (uint32_t)(bufinfo.len / SDCARD_BLOCK_SIZE);
    if (num_blocks == 0 || (bufinfo.len % SDCARD_BLOCK_SIZE) != 0) {
        return MP_OBJ_NEW_SMALL_INT(-MP_EINVAL);
    }

    int ret = sdcard_init_if_needed();
    if (ret != 0) {
        return MP_OBJ_NEW_SMALL_INT(ret);
    }

    if (HAL_SD_ReadBlocks(&hsd, (uint8_t *)bufinfo.buf, block_num, num_blocks, 5000) != HAL_OK) {
        return MP_OBJ_NEW_SMALL_INT(-MP_EIO);
    }

    // Wait for card ready.
    uint32_t start = HAL_GetTick();
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER) {
        if ((HAL_GetTick() - start) > 5000) {
            return MP_OBJ_NEW_SMALL_INT(-MP_ETIMEDOUT);
        }
    }

    return MP_OBJ_NEW_SMALL_INT(0);
}
static MP_DEFINE_CONST_FUN_OBJ_3(sdcard_readblocks_obj, sdcard_readblocks);

static mp_obj_t sdcard_writeblocks(mp_obj_t self_in, mp_obj_t block_num_in, mp_obj_t buf_in) {
    (void)self_in;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf_in, &bufinfo, MP_BUFFER_READ);

    uint32_t block_num = (uint32_t)mp_obj_get_int(block_num_in);
    uint32_t num_blocks = (uint32_t)(bufinfo.len / SDCARD_BLOCK_SIZE);
    if (num_blocks == 0 || (bufinfo.len % SDCARD_BLOCK_SIZE) != 0) {
        return MP_OBJ_NEW_SMALL_INT(-MP_EINVAL);
    }

    int ret = sdcard_init_if_needed();
    if (ret != 0) {
        return MP_OBJ_NEW_SMALL_INT(ret);
    }

    if (HAL_SD_WriteBlocks(&hsd, (uint8_t *)bufinfo.buf, block_num, num_blocks, 5000) != HAL_OK) {
        return MP_OBJ_NEW_SMALL_INT(-MP_EIO);
    }

    uint32_t start = HAL_GetTick();
    while (HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER) {
        if ((HAL_GetTick() - start) > 5000) {
            return MP_OBJ_NEW_SMALL_INT(-MP_ETIMEDOUT);
        }
    }

    return MP_OBJ_NEW_SMALL_INT(0);
}
static MP_DEFINE_CONST_FUN_OBJ_3(sdcard_writeblocks_obj, sdcard_writeblocks);

static mp_obj_t sdcard_ioctl(mp_obj_t self_in, mp_obj_t cmd_in, mp_obj_t arg_in) {
    (void)self_in;
    mp_int_t cmd = mp_obj_get_int(cmd_in);

    switch (cmd) {
        case MP_BLOCKDEV_IOCTL_INIT: {
            int ret = sdcard_init_if_needed();
            return MP_OBJ_NEW_SMALL_INT(ret);
        }
        case MP_BLOCKDEV_IOCTL_DEINIT:
            if (sd_inited) {
                (void)HAL_SD_DeInit(&hsd);
            }
            sd_inited = false;
            sd_num_blocks = 0;
            return MP_OBJ_NEW_SMALL_INT(0);

        case MP_BLOCKDEV_IOCTL_SYNC:
            return MP_OBJ_NEW_SMALL_INT(0);

        case MP_BLOCKDEV_IOCTL_BLOCK_COUNT: {
            int ret = sdcard_init_if_needed();
            if (ret != 0) {
                return MP_OBJ_NEW_SMALL_INT(ret);
            }
            return MP_OBJ_NEW_SMALL_INT((mp_int_t)sd_num_blocks);
        }

        case MP_BLOCKDEV_IOCTL_BLOCK_SIZE:
            return MP_OBJ_NEW_SMALL_INT((mp_int_t)SDCARD_BLOCK_SIZE);

        default:
            return MP_OBJ_NEW_SMALL_INT(-MP_EINVAL);
    }
}
static MP_DEFINE_CONST_FUN_OBJ_3(sdcard_ioctl_obj, sdcard_ioctl);

static const mp_rom_map_elem_t sdcard_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_readblocks), MP_ROM_PTR(&sdcard_readblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_writeblocks), MP_ROM_PTR(&sdcard_writeblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_ioctl), MP_ROM_PTR(&sdcard_ioctl_obj) },
};
static MP_DEFINE_CONST_DICT(sdcard_locals_dict, sdcard_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    machine_sdcard_type,
    MP_QSTR_SDCard,
    MP_TYPE_FLAG_NONE,
    make_new, sdcard_make_new,
    locals_dict, &sdcard_locals_dict
    );

// ---- Auto-mount ---------------------------------------------------------------

void mp_threadx_try_mount_sdcard(void) {
#if MICROPY_VFS && MICROPY_VFS_FAT
    // Best-effort only: no prints, no exceptions escaping.
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        mp_obj_t sd = MP_OBJ_TYPE_GET_SLOT(&machine_sdcard_type, make_new)(&machine_sdcard_type, 0, 0, NULL);
        mp_obj_t mount_point = mp_obj_new_str(MICROPY_HW_SDCARD_MOUNT_POINT, strlen(MICROPY_HW_SDCARD_MOUNT_POINT));
        (void)mp_vfs_mount_and_chdir_protected(sd, mount_point);

        // Add to sys.path: /sd and /sd/lib
        #if MICROPY_PY_SYS_PATH
        mp_obj_list_append(mp_sys_path, mount_point);
        mp_obj_t lib_path = mp_obj_new_str(MICROPY_HW_SDCARD_MOUNT_POINT "/lib", sizeof(MICROPY_HW_SDCARD_MOUNT_POINT "/lib") - 1);
        mp_obj_list_append(mp_sys_path, lib_path);
        #endif

        nlr_pop();
    } else {
        // ignore
    }
#endif
}
