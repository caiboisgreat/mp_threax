#pragma once

#if defined(NDEBUG)
#define metal_sys_assert(cond) ((void)0)
#else
#define metal_sys_assert(cond) do { if (!(cond)) { __builtin_trap(); } } while (0)
#endif
