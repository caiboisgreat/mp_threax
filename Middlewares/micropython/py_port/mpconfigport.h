#include <stdint.h>

// options to control how MicroPython is built

// Enable a reasonably complete feature set (standard modules) while still
// keeping hardware/network/filesystem features explicitly opt-in for this
// project.
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)

// Core runtime features
#define MICROPY_ENABLE_GC                 (1)
#define MICROPY_ENABLE_COMPILER           (1)

// Run MicroPython in a single-VM/single-thread configuration for now.
// The project runs MicroPython inside a ThreadX thread, but does not yet
// integrate MicroPython's own thread/GIL subsystem (mp_thread_*).
// Keeping this off avoids per-thread MP_STATE corruption that can lead to
// nlr_jump_fail during exception unwinding.
#define MICROPY_PY_THREAD                 (0)
#define MICROPY_PY_THREAD_GIL             (0)

// Float/complex are needed for math/cmath.
#define MICROPY_FLOAT_IMPL                (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_PY_BUILTINS_FLOAT         (1)
#define MICROPY_PY_BUILTINS_COMPLEX       (1)

// Keep VFS/filesystem features off for now (device/filesystem porting comes
// next). This still allows many standard modules to be built-in.
#define MICROPY_VFS                       (0)
#define MICROPY_VFS_FAT                   (0)
#define MICROPY_VFS_LFS1                  (0)
#define MICROPY_VFS_LFS2                  (0)

// Keep network stack off in the "standard module" phase.
#define MICROPY_PY_NETWORK                (0)
#define MICROPY_PY_LWIP                   (0)
#define MICROPY_PY_SOCKET                 (0)
#define MICROPY_PY_USSL                   (0)

// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
#define MICROPY_ENABLE_COMPILER     (1)

// Note: MICROPY_QSTR_EXTRA_POOL requires a generated qstr pool (mp_qstr_frozen_const_pool).
// This minimal Keil project doesn't generate it, so disable to avoid link/runtime issues.
// (You can re-enable once you generate and compile the frozen qstr pool.)
// #define MICROPY_QSTR_EXTRA_POOL           mp_qstr_frozen_const_pool
#define MICROPY_HELPER_REPL               (1)
#define MICROPY_MODULE_FROZEN_MPY         (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT    (1)

#define MICROPY_ALLOC_PATH_MAX            (256)

// Use the minimum headroom in the chunk allocator for parse nodes.
#define MICROPY_ALLOC_PARSE_CHUNK_INIT    (16)

// sys module (and the legacy aliases usys, uos, utime, ...)
#define MICROPY_PY_SYS                    (1)
#define MICROPY_PY_SYS_MODULES            (1)
#define MICROPY_PY_SYS_EXIT               (1)
#define MICROPY_PY_SYS_PATH               (1)
#define MICROPY_PY_SYS_ARGV               (1)

// Standard modules (C built-ins)
#define MICROPY_PY_MATH                   (1)
#define MICROPY_PY_CMATH                  (1)
#define MICROPY_PY_OS                     (1)
#define MICROPY_PY_TIME                   (1)
#define MICROPY_PY_JSON                   (1)
#define MICROPY_PY_BINASCII               (1)
#define MICROPY_PY_UCTYPES                (1)
#define MICROPY_PY_RE                     (1)
#define MICROPY_PY_SELECT                 (1)
#define MICROPY_PY_RANDOM                 (1)
#define MICROPY_PY_HEAPQ                  (1)
#define MICROPY_PY_HASHLIB                (1)
#define MICROPY_PY_CRYPTOLIB              (0)
#define MICROPY_PY_ZLIB                   (1)
#define MICROPY_PY_ASYNCIO                (1)

// Temporarily disable `platform` until the build/genhdr setup is fully stable.
// This module is not essential for the initial “standard modules” milestone.
#define MICROPY_PY_PLATFORM                (0)

// type definitions for the specific machine

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// Provide alloca() in a way that works across embedded toolchains.
// Keil/ARM toolchains typically don't ship <alloca.h>.
#if defined(_MSC_VER)
	#include <malloc.h>
	#define alloca _alloca
#elif defined(__clang__) || defined(__GNUC__) || defined(__ARMCOMPILER_VERSION) || defined(__CC_ARM) || defined(__ARMCC_VERSION)
	#define alloca __builtin_alloca
#else
	#include <alloca.h>
#endif

#define MICROPY_HW_BOARD_NAME "PYBASE"
#define MICROPY_HW_MCU_NAME "STM32F405RG6"

#if defined(__linux__) || defined(__APPLE__)
#define MICROPY_MIN_USE_STDOUT (1)
#define MICROPY_HEAP_SIZE      (25600) // heap size 25 kilobytes
#endif

#ifdef __thumb__
// When building this STM32 project with Keil/ARMClang, startup and vector table
// are provided by the project startup assembly (startup_stm32f407xx.s).
// The minimal port's built-in Reset_Handler/vector table conflicts with that
// and also uses patterns not accepted by ARMClang for naked functions.
#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__ARMCOMPILER_VERSION)
#define MICROPY_MIN_USE_CORTEX_CPU (0)
#else
#define MICROPY_MIN_USE_CORTEX_CPU (1)
#endif

#define MICROPY_MIN_USE_STM32_MCU (1)
#define MICROPY_HEAP_SIZE      (32768) // heap size 32 kilobytes
#endif

#define MP_STATE_PORT MP_STATE_VM

#define MP_ENDIANNESS_LITTLE (1)
// Use native ARM Thumb NLR implementation (see py/nlrthumb.c).
// The setjmp/longjmp implementation is often not robust on Cortex-M bare-metal/RTOS toolchains
// (especially with LTO/optimisations), and can lead to corrupted nlr_top and nlr_jump_fail.
#define MICROPY_NLR_SETJMP (0)
// Collect GC root registers using the port's assembly helper, not setjmp.
#define MICROPY_GCREGS_SETJMP (0)
#define MP_UNREACHABLE for (;;);
#define MICROPY_USE_INTERNAL_ERRNO (1)
