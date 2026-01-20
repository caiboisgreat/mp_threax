// Internal flash filesystem for STM32F405
// Provides a block device interface to a reserved region of internal flash
// for use with VfsFat or VfsLfs2

#include "py/runtime.h"
#include "py/mphal.h"
#include "py/obj.h"
#include "extmod/vfs.h"
#include "extmod/vfs_fat.h"

#if MICROPY_VFS

#include "stm32f4xx_hal.h"
#include <string.h>

// Forward declaration
extern const mp_obj_type_t pyb_flash_type;

// Flash configuration for STM32F405RG (1MB total flash)
// Reserve last 256KB for filesystem (sectors 10-11)
// Program code uses sectors 0-9 (~643KB, up to 768KB max)
// Sectors 10-11: 256KB at 0x080C0000 - 0x08100000
#define FLASH_SECTOR_SIZE       (0x40000)  // 256KB (2 sectors)
#define FLASH_FS_START_ADDR     (0x080C0000)  // Sector 10 start
#define FLASH_BLOCK_SIZE        (512)       // 512 bytes per block (FAT sector size)
#define FLASH_FS_NUM_BLOCKS     (512)       // 512 blocks × 512 bytes = 256KB total

typedef struct _pyb_flash_obj_t {
    mp_obj_base_t base;
    uint32_t start_addr;
    uint32_t num_blocks;
} pyb_flash_obj_t;

// Track whether sectors 10-11 have been erased (to avoid erasing twice)
static bool sectors_erased = false;

static pyb_flash_obj_t pyb_flash_obj = {
    .base = {&pyb_flash_type},
    .start_addr = FLASH_FS_START_ADDR,
    .num_blocks = FLASH_FS_NUM_BLOCKS,
};

// Factory function to create Flash instances
static mp_obj_t pyb_flash_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // No arguments accepted
    mp_arg_check_num(n_args, n_kw, 0, 0, false);
    // Return the singleton flash object
    return MP_OBJ_FROM_PTR(&pyb_flash_obj);
}

// Read blocks from internal flash
static mp_obj_t pyb_flash_readblocks(size_t n_args, const mp_obj_t *args) {
    pyb_flash_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    uint32_t block_num = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_WRITE);
    
    uint32_t offset = 0;
    if (n_args == 4) {
        offset = mp_obj_get_int(args[3]);
    }
    
    if (block_num >= self->num_blocks) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("invalid block %u"), block_num);
    }
    
    uint32_t src_addr = self->start_addr + block_num * FLASH_BLOCK_SIZE + offset;
    memcpy(bufinfo.buf, (void *)src_addr, bufinfo.len);
    
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(pyb_flash_readblocks_obj, 3, 4, pyb_flash_readblocks);

// Write blocks to internal flash
static mp_obj_t pyb_flash_writeblocks(size_t n_args, const mp_obj_t *args) {
    pyb_flash_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    uint32_t block_num = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_READ);
    
    uint32_t offset = 0;
    if (n_args == 4) {
        offset = mp_obj_get_int(args[3]);
    }
    
    if (block_num >= self->num_blocks) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("invalid block %u"), block_num);
    }
    
    uint32_t dest_addr = self->start_addr + block_num * FLASH_BLOCK_SIZE + offset;
    
    // Unlock flash for writing
    HAL_FLASH_Unlock();
    
    // STM32 flash must be erased before writing
    // All 4 blocks are in sectors 10-11 (256KB total)
    // Only erase if the sectors haven't been erased yet in this session
    if (offset == 0 && !sectors_erased) {
        FLASH_EraseInitTypeDef erase_init;
        erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
        erase_init.Sector = FLASH_SECTOR_10;
        erase_init.NbSectors = 2;  // Erase both sectors 10 and 11
        erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
        uint32_t sector_error;
        
        HAL_StatusTypeDef erase_status = HAL_FLASHEx_Erase(&erase_init, &sector_error);
        if (erase_status != HAL_OK) {
            HAL_FLASH_Lock();
            mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("flash erase error"));
        }
        sectors_erased = true;  // Mark as erased
    }
    
    // Write data using word (32-bit) programming for better reliability
    // STM32F4 flash programming works best with 32-bit aligned writes
    uint8_t *src_bytes = (uint8_t *)bufinfo.buf;
    uint32_t bytes_written = 0;
    
    // Handle unaligned start
    while (bytes_written < bufinfo.len && ((dest_addr + bytes_written) & 0x3)) {
        HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, 
                                                      dest_addr + bytes_written, 
                                                      src_bytes[bytes_written]);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("flash write error (unaligned start)"));
        }
        bytes_written++;
    }
    
    // Write aligned words
    while (bytes_written + 4 <= bufinfo.len) {
        uint32_t word;
        memcpy(&word, &src_bytes[bytes_written], 4);
        HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                                                      dest_addr + bytes_written, 
                                                      word);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("flash write error (word)"));
        }
        bytes_written += 4;
    }
    
    // Handle remaining bytes
    while (bytes_written < bufinfo.len) {
        HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, 
                                                      dest_addr + bytes_written, 
                                                      src_bytes[bytes_written]);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            mp_raise_msg(&mp_type_OSError, MP_ERROR_TEXT("flash write error (remaining)"));
        }
        bytes_written++;
    }
    
    HAL_FLASH_Lock();
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(pyb_flash_writeblocks_obj, 3, 4, pyb_flash_writeblocks);

// ioctl for block device protocol
static mp_obj_t pyb_flash_ioctl(size_t n_args, const mp_obj_t *args) {
    pyb_flash_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    mp_int_t cmd = mp_obj_get_int(args[1]);
    
    // arg may not be provided for some commands
    mp_obj_t arg_in = (n_args > 2) ? args[2] : MP_OBJ_NEW_SMALL_INT(0);
    
    switch (cmd) {
        case MP_BLOCKDEV_IOCTL_INIT:
            sectors_erased = false;  // Reset erase flag on init
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_DEINIT:
            sectors_erased = false;  // Reset erase flag on deinit
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_SYNC:
            return MP_OBJ_NEW_SMALL_INT(0);
        case MP_BLOCKDEV_IOCTL_BLOCK_COUNT:
            return MP_OBJ_NEW_SMALL_INT(self->num_blocks);
        case MP_BLOCKDEV_IOCTL_BLOCK_SIZE:
            return MP_OBJ_NEW_SMALL_INT(FLASH_BLOCK_SIZE);
        case MP_BLOCKDEV_IOCTL_BLOCK_ERASE: {
            mp_int_t block_num = mp_obj_get_int(arg_in);
            if (block_num >= self->num_blocks) {
                return MP_OBJ_NEW_SMALL_INT(-1);
            }
            // Erase sectors 10-11 (256KB total)
            // Only erase if not already erased to avoid data loss
            if (!sectors_erased) {
                HAL_FLASH_Unlock();
                FLASH_EraseInitTypeDef erase_init;
                erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
                erase_init.Sector = FLASH_SECTOR_10;
                erase_init.NbSectors = 2;  // Erase sectors 10 and 11
                erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
                uint32_t sector_error;
                HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&erase_init, &sector_error);
                HAL_FLASH_Lock();
                if (status == HAL_OK) {
                    sectors_erased = true;
                }
                return MP_OBJ_NEW_SMALL_INT(status == HAL_OK ? 0 : -1);
            }
            return MP_OBJ_NEW_SMALL_INT(0);  // Already erased
        }
        default:
            return MP_OBJ_NEW_SMALL_INT(-1);  // Unsupported operation
    }
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(pyb_flash_ioctl_obj, 2, 3, pyb_flash_ioctl);

static const mp_rom_map_elem_t pyb_flash_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_readblocks), MP_ROM_PTR(&pyb_flash_readblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_writeblocks), MP_ROM_PTR(&pyb_flash_writeblocks_obj) },
    { MP_ROM_QSTR(MP_QSTR_ioctl), MP_ROM_PTR(&pyb_flash_ioctl_obj) },
};
static MP_DEFINE_CONST_DICT(pyb_flash_locals_dict, pyb_flash_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    pyb_flash_type,
    MP_QSTR_Flash,
    MP_TYPE_FLAG_NONE,
    make_new, pyb_flash_make_new,
    locals_dict, &pyb_flash_locals_dict
);

// Auto-mount flash filesystem at startup
void mp_threadx_try_mount_flash(void) {
#if MICROPY_VFS && MICROPY_VFS_FAT
    mp_obj_t flash_obj = MP_OBJ_FROM_PTR(&pyb_flash_obj);
    mp_obj_t mount_point = mp_obj_new_str("/flash", 6);
    
    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        // Try to mount existing filesystem
        mp_vfs_mount_and_chdir_protected(flash_obj, mount_point);
        
        // Add to sys.path
        #if MICROPY_PY_SYS_PATH
        mp_obj_list_append(mp_sys_path, mount_point);
        mp_obj_t lib_path = mp_obj_new_str("/flash/lib", 10);
        mp_obj_list_append(mp_sys_path, lib_path);
        #endif
        
        nlr_pop();
    } else {
        // Mount failed - try to format and mount
        
        nlr_buf_t nlr2;
        if (nlr_push(&nlr2) == 0) {
            // Format the flash
            mp_obj_t mkfs_args[2] = {
                MP_OBJ_TYPE_GET_SLOT(&mp_fat_vfs_type, make_new)(&mp_fat_vfs_type, 1, 0, &flash_obj),
                flash_obj
            };
            
            // Call VfsFat.mkfs(flash)
            fs_user_mount_t *vfs = MP_OBJ_TO_PTR(mkfs_args[0]);
            uint8_t working_buf[512];
            FRESULT res = f_mkfs(&vfs->fatfs, FM_FAT | FM_SFD, 0, working_buf, sizeof(working_buf));
            if (res == FR_MKFS_ABORTED) {
                res = f_mkfs(&vfs->fatfs, FM_FAT32, 0, working_buf, sizeof(working_buf));
            }
            
            if (res == FR_OK) {
                // Now try to mount again
                mp_vfs_mount_and_chdir_protected(flash_obj, mount_point);
                
                #if MICROPY_PY_SYS_PATH
                mp_obj_list_append(mp_sys_path, mount_point);
                mp_obj_t lib_path = mp_obj_new_str("/flash/lib", 10);
                mp_obj_list_append(mp_sys_path, lib_path);
                #endif
            }
            
            nlr_pop();
        } else {
        }
    }
#endif
}

#endif // MICROPY_VFS
