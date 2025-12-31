#include <stdint.h>

// options to control how MicroPython is built

// Use the minimal starting configuration (disables all optional features).
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

// You can disable the built-in MicroPython compiler by setting the following
// config option to 0.  If you do this then you won't get a REPL prompt, but you
// will still be able to execute pre-compiled scripts, compiled with mpy-cross.
#define MICROPY_ENABLE_COMPILER     (1)

// Note: MICROPY_QSTR_EXTRA_POOL requires a generated qstr pool (mp_qstr_frozen_const_pool).
// This minimal Keil project doesn't generate it, so disable to avoid link/runtime issues.
// (You can re-enable once you generate and compile the frozen qstr pool.)
// #define MICROPY_QSTR_EXTRA_POOL           mp_qstr_frozen_const_pool
#define MICROPY_ENABLE_GC                 (1)
#define MICROPY_HELPER_REPL               (1)
#define MICROPY_MODULE_FROZEN_MPY         (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT    (1)

#define MICROPY_PY_GC                     (1)

#define MICROPY_ALLOC_PATH_MAX            (256)

// Use the minimum headroom in the chunk allocator for parse nodes.
#define MICROPY_ALLOC_PARSE_CHUNK_INIT    (16)

// Disable all optional sys module features.
#define MICROPY_PY_SYS_MODULES            (0)
#define MICROPY_PY_SYS_EXIT               (0)
#define MICROPY_PY_SYS_PATH               (0)
#define MICROPY_PY_SYS_ARGV               (0)

// type definitions for the specific machine

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

#define MICROPY_HW_BOARD_NAME "minimal"
#define MICROPY_HW_MCU_NAME "unknown-cpu"

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
#define MICROPY_HEAP_SIZE      (2048) // heap size 2 kilobytes
#endif

#define MP_STATE_PORT MP_STATE_VM

#define MP_ENDIANNESS_LITTLE (1)
#define MICROPY_NLR_SETJMP (1)
#define MP_UNREACHABLE for (;;);
#define MICROPY_USE_INTERNAL_ERRNO (1)
