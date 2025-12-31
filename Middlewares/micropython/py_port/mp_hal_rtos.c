#include "py/mpconfig.h"
#include "py/mphal.h"
#include "py/stream.h"

#if defined(STM32F405xx) || defined(STM32F4xx)
#include "stm32f4xx_hal.h"
#endif

#include "core_cm4.h"

static inline void mp_hal_dwt_init_once(void) {
	static uint8_t inited = 0;
	if (inited) {
		return;
	}
	inited = 1;

	// Enable DWT CYCCNT for microsecond timing.
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

// Provide a fast CPU-cycle counter for time.ticks_cpu().
mp_uint_t mp_hal_ticks_cpu(void) {
	mp_hal_dwt_init_once();
	return (mp_uint_t)DWT->CYCCNT;
}

// Simple poll implementation for sys stdio streams.
uintptr_t mp_hal_stdio_poll(uintptr_t poll_flags) {
	uintptr_t ret = 0;

	// STM32F405: USART2 base is 0x40004400. This project configures REPL on USART2.
	#if MICROPY_MIN_USE_STM32_MCU
	typedef struct {
		volatile uint32_t SR;
		volatile uint32_t DR;
	} periph_uart_t;
	#define USART2_REPL ((periph_uart_t *)0x40004400)

	if (poll_flags & MP_STREAM_POLL_RD) {
		// RXNE
		if (USART2_REPL->SR & (1 << 5)) {
			ret |= MP_STREAM_POLL_RD;
		}
	}
	if (poll_flags & MP_STREAM_POLL_WR) {
		// TXE
		if (USART2_REPL->SR & (1 << 7)) {
			ret |= MP_STREAM_POLL_WR;
		}
	}
	#else
	// Fallback: assume ready.
	ret = poll_flags;
	#endif

	return ret;
}

mp_uint_t mp_hal_ticks_ms(void) {
	#if defined(HAL_GetTick)
	return (mp_uint_t)HAL_GetTick();
	#else
	return 0;
	#endif
}

mp_uint_t mp_hal_ticks_us(void) {
	mp_hal_dwt_init_once();

	uint32_t sysclk = SystemCoreClock;
	if (sysclk == 0) {
		return 0;
	}
	return (mp_uint_t)(DWT->CYCCNT / (sysclk / 1000000u));
}

void mp_hal_delay_ms(mp_uint_t ms) {
	#if defined(HAL_Delay)
	HAL_Delay((uint32_t)ms);
	#else
	// Fallback: crude delay.
	volatile mp_uint_t n = ms * 1000u;
	while (n--) {
		__NOP();
	}
	#endif
}

void mp_hal_delay_us(mp_uint_t us) {
	mp_hal_dwt_init_once();

	uint32_t sysclk = SystemCoreClock;
	if (sysclk == 0) {
		return;
	}

	uint64_t cycles = ((uint64_t)us * (uint64_t)sysclk) / 1000000ull;
	uint32_t start = DWT->CYCCNT;
	while ((uint32_t)(DWT->CYCCNT - start) < (uint32_t)cycles) {
		__NOP();
	}
}
