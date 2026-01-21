/*
 * LED implementation for STM32F405 + ThreadX
 * Based on MicroPython stm32 port
 */

#include <stdio.h>
#include "py/runtime.h"
#include "py/mphal.h"
#include "led.h"
#include "pin.h"

// LED pin definitions (official pyboard v1.1)
// LED 1 (Red): PA13
// LED 2 (Green): PA14
// LED 3 (Yellow): PA15
// LED 4 (Blue): PB4

// Forward declare pin objects (will be defined in pins.c)
extern const machine_pin_obj_t pin_A13;
extern const machine_pin_obj_t pin_A14;
extern const machine_pin_obj_t pin_A15;
extern const machine_pin_obj_t pin_B4;

typedef struct _pyb_led_obj_t {
    mp_obj_base_t base;
    mp_uint_t led_id;
    const machine_pin_obj_t *led_pin;
} pyb_led_obj_t;

static const pyb_led_obj_t pyb_led_obj[] = {
    {{&pyb_led_type}, 1, &pin_A13},  // Red LED
    {{&pyb_led_type}, 2, &pin_A14},  // Green LED
    {{&pyb_led_type}, 3, &pin_A15},  // Yellow LED
    {{&pyb_led_type}, 4, &pin_B4},   // Blue LED
};

#define NUM_LEDS MP_ARRAY_SIZE(pyb_led_obj)

void led_init(void) {
    // Turn off LEDs and initialize
    for (int led = 0; led < NUM_LEDS; led++) {
        const machine_pin_obj_t *led_pin = pyb_led_obj[led].led_pin;
        mp_hal_gpio_clock_enable(led_pin->gpio);
        MICROPY_HW_LED_OFF(led_pin);
        mp_hal_pin_output(led_pin);
    }
}

void led_state(pyb_led_t led, int state) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }

    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    if (state == 0) {
        // turn LED off
        MICROPY_HW_LED_OFF(led_pin);
    } else {
        // turn LED on
        MICROPY_HW_LED_ON(led_pin);
    }
}

void led_toggle(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }

    // toggle the output data register to toggle the LED state
    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    led_pin->gpio->ODR ^= led_pin->pin_mask;
}

int led_get_intensity(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return 0;
    }

    const machine_pin_obj_t *led_pin = pyb_led_obj[led - 1].led_pin;
    GPIO_TypeDef *gpio = led_pin->gpio;

    if (gpio->ODR & led_pin->pin_mask) {
        // pin is high
        return MICROPY_HW_LED_INVERTED ? 0 : 255;
    } else {
        // pin is low
        return MICROPY_HW_LED_INVERTED ? 255 : 0;
    }
}

void led_set_intensity(pyb_led_t led, mp_int_t intensity) {
    // intensity not supported for this LED; just turn it on/off
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
