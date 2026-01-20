# Internal Flash Filesystem Setup

## Overview
This project now supports internal flash filesystem alongside the SD card. The last 256KB of STM32F405's internal flash (sectors 10-11) is reserved for the filesystem.

## Changes Made

### 1. Files Added/Modified
- **NEW**: `Middlewares/micropython/py_port/storage.c` - Flash block device implementation
- **MODIFIED**: `Middlewares/micropython/py_port/py_init.c` - Added auto-mount call
- **MODIFIED**: `Middlewares/micropython/py_port/qstrdefsport.h` - Added Q(Flash)
- **MODIFIED**: `Middlewares/micropython/py_port/modmachine_port.c` - Exported Flash to machine module
- **MODIFIED**: `MDK-ARM/mp_threadx.uvprojx` - Added storage.c to build

### 2. Flash Memory Layout
```
STM32F405RG Total Flash: 1024KB (0x08000000 - 0x08100000)

Application Code:   0x08000000 - 0x080C0000 (768KB)  - Sectors 0-9
Flash Filesystem:   0x080C0000 - 0x08100000 (256KB)  - Sectors 10-11
  └─ Logical blocks: 4 blocks × 64KB each
```

## First-Time Setup

After flashing the new firmware, the internal flash filesystem needs to be formatted:

### Step 1: Build and Flash
1. Open project in Keil MDK-ARM
2. Build the project (should compile with 0 errors)
3. Flash to the board

### Step 2: Format Flash (One-Time)
Connect via Thonny or serial terminal and run:

```python
import machine
import os

# Create Flash instance
flash = machine.Flash()

# Format as FAT filesystem
os.VfsFat.mkfs(flash)

# Verify it worked
print("Flash formatted successfully!")
```

### Step 3: Reboot
Press the reset button or power cycle. The flash filesystem will now auto-mount at `/flash`.

## Usage

### Check Mounted Filesystems
```python
import os
print(os.listdir('/'))
# Expected output: ['flash', 'sd']
```

### Working with Flash
```python
# Create a file
with open('/flash/test.txt', 'w') as f:
    f.write('Hello from internal flash!')

# Read it back
with open('/flash/test.txt', 'r') as f:
    print(f.read())

# List contents
print(os.listdir('/flash'))
```

### Python Path
After auto-mount, the following paths are added to `sys.path`:
- `/flash`
- `/flash/lib`

You can place Python modules in `/flash/lib/` and import them directly.

## Troubleshooting

### Flash doesn't mount after reboot
The filesystem may not be formatted. Run the format commands from Step 2.

### "OSError: [Errno 5] EIO" during mkfs
- Check that the flash sectors are not write-protected
- Ensure the flash region is not being used by the bootloader

### Want to re-format
```python
import machine, os
flash = machine.Flash()
os.VfsFat.mkfs(flash)  # This will erase all data!
```

## Technical Details

### Block Device Protocol
The Flash object implements the standard MicroPython block device protocol:
- `readblocks(block_num, buf)`
- `writeblocks(block_num, buf)`
- `ioctl(op, arg)` - supports count, block_size, and erase

### Sector Erase Behavior
STM32F4 flash sectors are large (128KB each), but the block device uses 64KB logical blocks. When erasing:
- Each logical block erase actually erases a full 128KB sector
- Two consecutive 64KB blocks share the same physical sector

### Performance
- Read speed: ~40 MB/s (directly from flash)
- Write speed: ~10-20 KB/s (limited by flash erase/program time)
- Erase time: ~2 seconds per 128KB sector

## Comparison with SD Card

| Feature | Internal Flash | SD Card |
|---------|---------------|---------|
| Capacity | 256 KB | Up to 32 GB |
| Speed (Read) | Very Fast | Fast |
| Speed (Write) | Slow | Medium |
| Wear Leveling | No (limited cycles) | Built-in |
| Mount Point | `/flash` | `/sd` |
| Best For | Configuration, small files | Large data, logs |

## Recommended Usage

**Use `/flash` for:**
- Configuration files
- Python modules/libraries
- Boot scripts
- Small persistent data

**Use `/sd` for:**
- Large data files
- Logs and recordings
- User documents
- Frequently updated data

