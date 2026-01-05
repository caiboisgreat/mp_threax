#include <stdint.h>

#include "lib/oofatfs/ff.h"

// FatFs timestamp callback.
//
// Return value format (local time):
//  bit31:25 year from 1980 (0..127)
//  bit24:21 month (1..12)
//  bit20:16 day (1..31)
//  bit15:11 hour (0..23)
//  bit10:5  minute (0..59)
//  bit4:0   second/2 (0..29)
//
// This port does not yet have an RTC/time service exposed to MicroPython, so
// return 0 (1980-01-01 00:00:00).
DWORD get_fattime(void) {
    return 0;
}
