/*
 * LED implementation for STM32F405 + ThreadX
 * Based on official MicroPython stm32 port with PWM support
 */

#include <stdio.h>
#include "py/runtime.h"
#include "py/mphal.h"
#include "led.h"
#include "pin.h"
#include "mpconfigboard.h"
#include "stm32f4xx_hal.h"

#if defined(MICROPY_HW_LED1)

// Forward declare pin objects (defined in pins.c)
extern const machine_pin_obj_t pin_A13;
extern const machine_pin_obj_t pin_A14;
extern const machine_pin_obj_t pin_A15;
extern const machine_pin_obj_t pin_B4;

typedef struct _pyb_led_obj_t {
    mp_obj_base_t base;
    mp_uint_t led_id;
    const machine_pin_obj_t *led_pin;
} pyb_led_obj_t;

#if defined(MICROPY_HW_LED1)
static const pyb_led_obj_t pyb_led_obj[] = {
    {{&pyb_led_type}, 1, MICROPY_HW_LED1},
    #if defined(MICROPY_HW_LED2)
    {{&pyb_led_type}, 2, MICROPY_HW_LED2},
    #if defined(MICROPY_HW_LED3)
    {{&pyb_led_type}, 3, MICROPY_HW_LED3},
    #if defined(MICROPY_HW_LED4)
    {{&pyb_led_type}, 4, MICROPY_HW_LED4},
    #endif
    #endif
    #endif
};

#define NUM_LEDS MP_ARRAY_SIZE(pyb_led_obj)
#endif

void led_init(void) {
    /* Turn off LEDs and initialize */
    for (int led = 0; led < NUM_LEDS; led++) {
        const machine_pin_obj_t *led_pin = pyb_led_obj[led].led_pin;
        mp_hal_gpio_clock_enable(led_pin->gpio);
        MICROPY_HW_LED_OFF(led_pin);
        mp_hal_pin_output(led_pin);
    }
}

// PWM support for LED intensity control
#if defined(MICROPY_HW_LED1_PWM) \
    || defined(MICROPY_HW_LED2_PWM) \
    || defined(MICROPY_HW_LED3_PWM) \
    || defined(MICROPY_HW_LED4_PWM)

#define LED_PWM_ENABLED (1)

#ifndef MICROPY_HW_LED1_PWM
#define MICROPY_HW_LED1_PWM { NULL, 0, 0, 0 }
#endif
#ifndef MICROPY_HW_LED2_PWM
#define MICROPY_HW_LED2_PWM { NULL, 0, 0, 0 }
#endif
#ifndef MICROPY_HW_LED3_PWM
#define MICROPY_HW_LED3_PWM { NULL, 0, 0, 0 }
#endif
#ifndef MICROPY_HW_LED4_PWM
#define MICROPY_HW_LED4_PWM { NULL, 0, 0, 0 }
#endif

#define LED_PWM_TIM_PERIOD (10000) // TIM runs at 1MHz and fires every 10ms

// Get CCR register address for channels 1-4
#define LED_PWM_CCR(pwm_cfg) ((volatile uint32_t *)&(pwm_cfg)->tim->CCR1 + ((pwm_cfg)->tim_channel >> 2))

typedef struct _led_pwm_config_t {
    TIM_TypeDef *tim;
    uint8_t tim_id;
    uint8_t tim_channel;
    uint8_t alt_func;
} led_pwm_config_t;

static const led_pwm_config_t led_pwm_config[] = {
    MICROPY_HW_LED1_PWM,
    MICROPY_HW_LED2_PWM,
    MICROPY_HW_LED3_PWM,
    MICROPY_HW_LED4_PWM,
};

static uint8_t led_pwm_state = 0;

static inline bool led_pwm_is_enabled(int led) {
    return (led_pwm_state & (1 << led)) != 0;
}

// Get timer source frequency (APB1/APB2 timer clock)
static uint32_t timer_get_source_freq(uint8_t tim_id) {
    uint32_t pclk;
    if (tim_id == 1 || tim_id >= 8) {
        // TIM1, TIM8-TIM11 are on APB2
        pclk = HAL_RCC_GetPCLK2Freq();
    } else {
        // TIM2-TIM7 are on APB1
        pclk = HAL_RCC_GetPCLK1Freq();
    }
    // Timer clock is 2x APB clock if APB prescaler is not 1
    RCC_ClkInitTypeDef clk_init;
    uint32_t flash_latency;
    HAL_RCC_GetClockConfig(&clk_init, &flash_latency);
    
    if (tim_id == 1 || tim_id >= 8) {
        if (clk_init.APB2CLKDivider != RCC_HCLK_DIV1) {
            pclk *= 2;
        }
    } else {
        if (clk_init.APB1CLKDivider != RCC_HCLK_DIV1) {
            pclk *= 2;
        }
    }
    return pclk;
}

// Initialize PWM for LED (large stack, not inlined)
static void led_pwm_init(int led) __attribute__((noinline));
static void led_pwm_init(int led) {
    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    const led_pwm_config_t *pwm_cfg = &led_pwm_config[led - 1];

    // GPIO configuration for alternate function
    mp_hal_pin_config(led_pin, GPIO_MODE_AF_PP, GPIO_NOPULL, pwm_cfg->alt_func);

    // Enable timer clock
    switch (pwm_cfg->tim_id) {
        case 1:
            __HAL_RCC_TIM1_CLK_ENABLE();
            break;
        case 2:
            __HAL_RCC_TIM2_CLK_ENABLE();
            break;
        case 3:
            __HAL_RCC_TIM3_CLK_ENABLE();
            break;
        default:
            return;
    }

    // Timer configuration
    TIM_HandleTypeDef tim = {0};
    tim.Instance = pwm_cfg->tim;
    tim.Init.Period = LED_PWM_TIM_PERIOD - 1;
    tim.Init.Prescaler = timer_get_source_freq(pwm_cfg->tim_id) / 1000000 - 1; // 1MHz
    tim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim.Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(&tim);

    // PWM channel configuration
    TIM_OC_InitTypeDef oc_init = {0};
    oc_init.OCMode = TIM_OCMODE_PWM1;
    oc_init.Pulse = 0; // Start with LED off
    oc_init.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc_init.OCFastMode = TIM_OCFAST_DISABLE;
    oc_init.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    oc_init.OCIdleState = TIM_OCIDLESTATE_SET;
    oc_init.OCNIdleState = TIM_OCNIDLESTATE_SET;
    HAL_TIM_PWM_ConfigChannel(&tim, &oc_init, pwm_cfg->tim_channel);
    HAL_TIM_PWM_Start(&tim, pwm_cfg->tim_channel);

    // Mark LED as using PWM
    led_pwm_state |= 1 << led;
}

static void led_pwm_deinit(int led) {
    // Convert LED pin back to standard GPIO output
    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    mp_hal_pin_output(led_pin);
    led_pwm_state &= ~(1 << led);
}

#else
#define LED_PWM_ENABLED (0)
#endif

void led_state(pyb_led_t led, int state) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }

    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    if (state == 0) {
        MICROPY_HW_LED_OFF(led_pin);
    } else {
        MICROPY_HW_LED_ON(led_pin);
    }

    #if LED_PWM_ENABLED
    if (led_pwm_is_enabled(led)) {
        led_pwm_deinit(led);
    }
    #endif
}

void led_toggle(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }

    #if LED_PWM_ENABLED
    if (led_pwm_is_enabled(led)) {
        // If PWM enabled, LED has non-zero intensity, so turn it off
        led_state(led, 0);
        return;
    }
    #endif

    // Toggle the output data register
    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    led_pin->gpio->ODR ^= led_pin->pin_mask;
}

int led_get_intensity(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return 0;
    }

    #if LED_PWM_ENABLED
    if (led_pwm_is_enabled(led)) {
        const led_pwm_config_t *pwm_cfg = &led_pwm_config[led - 1];
        mp_uint_t i = (*LED_PWM_CCR(pwm_cfg) * 255 + LED_PWM_TIM_PERIOD - 2) / (LED_PWM_TIM_PERIOD - 1);
        if (i > 255) {
            i = 255;
        }
        return i;
    }
    #endif

    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    GPIO_TypeDef *gpio = led_pin->gpio;

    if (gpio->ODR & led_pin->pin_mask) {
        return 255; // LED on
    } else {
        return 0;   // LED off
    }
}

void led_set_intensity(pyb_led_t led, mp_int_t intensity) {
    #if LED_PWM_ENABLED
    if (intensity > 0 && intensity < 255) {
        const led_pwm_config_t *pwm_cfg = &led_pwm_config[led - 1];
        if (pwm_cfg->tim != NULL) {
            // Set intensity using PWM
            if (!led_pwm_is_enabled(led)) {
                led_pwm_init(led);
            }
            *LED_PWM_CCR(pwm_cfg) = intensity * (LED_PWM_TIM_PERIOD - 1) / 255;
            return;
        }
    }
    #endif

    // No PWM support or intensity is 0/255, just turn on/off
    led_state(led, intensity > 0);
}

void led_debug(int n, int delay) {
    led_state(1, n & 1);
    led_state(2, n & 2);
    led_state(3, n & 4);
    led_state(4, n & 8);
    mp_hal_delay_ms(delay);
}

/******************************************************************************/
/* MicroPython bindings                                                       */

static void led_obj_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "LED(%u)", (unsigned int)self->led_id);
}

static mp_obj_t led_obj_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, 1, false);

    // get led number
    mp_int_t led_id = mp_obj_get_int(args[0]);

    // check led number
    if (!(1 <= led_id && led_id <= NUM_LEDS)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("LED(%d) doesn't exist"), led_id);
    }

    // return static led object
    return MP_OBJ_FROM_PTR(&pyb_led_obj[led_id - 1]);
}

static mp_obj_t led_obj_on(mp_obj_t self_in) {
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    led_state(self->led_id, 1);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(led_obj_on_obj, led_obj_on);

static mp_obj_t led_obj_off(mp_obj_t self_in) {
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    led_state(self->led_id, 0);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(led_obj_off_obj, led_obj_off);

static mp_obj_t led_obj_toggle(mp_obj_t self_in) {
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    led_toggle(self->led_id);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(led_obj_toggle_obj, led_obj_toggle);

static mp_obj_t led_obj_intensity(size_t n_args, const mp_obj_t *args) {
    pyb_led_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    if (n_args == 1) {
        return mp_obj_new_int(led_get_intensity(self->led_id));
    } else {
        led_set_intensity(self->led_id, mp_obj_get_int(args[1]));
        return mp_const_none;
    }
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(led_obj_intensity_obj, 1, 2, led_obj_intensity);

static const mp_rom_map_elem_t led_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&led_obj_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&led_obj_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&led_obj_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_intensity), MP_ROM_PTR(&led_obj_intensity_obj) },
};
static MP_DEFINE_CONST_DICT(led_locals_dict, led_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    pyb_led_type,
    MP_QSTR_LED,
    MP_TYPE_FLAG_NONE,
    make_new, led_obj_make_new,
    print, led_obj_print,
    locals_dict, &led_locals_dict
);

#else
// For boards with no LEDs
void led_init(void) {
}
void led_state(pyb_led_t led, int state) {
}
void led_toggle(pyb_led_t led) {
}
#endif // defined(MICROPY_HW_LED1)
