/*
 * Pin implementation for STM32F405 + ThreadX
 * Based on MicroPython stm32 port - simplified version
 */

#include "py/runtime.h"
#include "py/mphal.h"
#include "extmod/virtpin.h"
#include "pin.h"

// Pin class variables
static bool pin_class_debug = false;

void pin_init0(void) {
    MP_STATE_PORT(pin_class_mapper) = mp_const_none;
    MP_STATE_PORT(pin_class_map_dict) = mp_const_none;
    pin_class_debug = false;
}

// C API used to convert a user-supplied pin name into an ordinal pin number
const machine_pin_obj_t *pin_find(mp_obj_t user_obj) {
    const machine_pin_obj_t *pin_obj;

    // If a pin was provided, then use it
    if (mp_obj_is_type(user_obj, &pin_type)) {
        pin_obj = MP_OBJ_TO_PTR(user_obj);
        return pin_obj;
    }

    if (MP_STATE_PORT(pin_class_mapper) != mp_const_none) {
        mp_obj_t o = mp_call_function_1(MP_STATE_PORT(pin_class_mapper), user_obj);
        if (o != mp_const_none) {
            if (!mp_obj_is_type(o, &pin_type)) {
                mp_raise_ValueError(MP_ERROR_TEXT("Pin.mapper didn't return a Pin object"));
            }
            return MP_OBJ_TO_PTR(o);
        }
    }

    if (MP_STATE_PORT(pin_class_map_dict) != mp_const_none) {
        mp_map_t *pin_map_map = mp_obj_dict_get_map(MP_STATE_PORT(pin_class_map_dict));
        mp_map_elem_t *elem = mp_map_lookup(pin_map_map, user_obj, MP_MAP_LOOKUP);
        if (elem != NULL && elem->value != MP_OBJ_NULL) {
            return MP_OBJ_TO_PTR(elem->value);
        }
    }

    // See if the pin name matches a board pin
    pin_obj = pin_find_named_pin(&machine_pin_board_pins_locals_dict, user_obj);
    if (pin_obj) {
        return pin_obj;
    }

    // See if the pin name matches a cpu pin
    pin_obj = pin_find_named_pin(&machine_pin_cpu_pins_locals_dict, user_obj);
    if (pin_obj) {
        return pin_obj;
    }

    mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("Pin(%s) doesn't exist"), mp_obj_str_get_str(user_obj));
}

const machine_pin_obj_t *pin_find_named_pin(const mp_obj_dict_t *named_pins, mp_obj_t name) {
    const mp_map_t *named_map = &named_pins->map;
    mp_map_elem_t *named_elem = mp_map_lookup((mp_map_t *)named_map, name, MP_MAP_LOOKUP);
    if (named_elem != NULL && named_elem->value != MP_OBJ_NULL) {
        return MP_OBJ_TO_PTR(named_elem->value);
    }
    return NULL;
}

uint32_t pin_get_mode(const machine_pin_obj_t *pin) {
    GPIO_TypeDef *gpio = pin->gpio;
    uint32_t pin_num = pin->pin;
    return (gpio->MODER >> (pin_num * 2)) & 0x03;
}

uint32_t pin_get_pull(const machine_pin_obj_t *pin) {
    GPIO_TypeDef *gpio = pin->gpio;
    uint32_t pin_num = pin->pin;
    return (gpio->PUPDR >> (pin_num * 2)) & 0x03;
}

uint32_t pin_get_af(const machine_pin_obj_t *pin) {
    GPIO_TypeDef *gpio = pin->gpio;
    uint32_t pin_num = pin->pin;
    if (pin_num < 8) {
        return (gpio->AFR[0] >> (pin_num * 4)) & 0x0F;
    } else {
        return (gpio->AFR[1] >> ((pin_num - 8) * 4)) & 0x0F;
    }
}

static void pin_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);

    // pin name
    mp_printf(print, "Pin(Pin.cpu.%q, mode=Pin.", self->name);

    uint32_t mode = pin_get_mode(self);
    if (mode == GPIO_MODE_ANALOG) {
        mp_print_str(print, "ANALOG)");
    } else {
        qstr mode_qst;
        if (mode == GPIO_MODE_INPUT) {
            mode_qst = MP_QSTR_IN;
        } else if (mode == GPIO_MODE_OUTPUT_PP) {
            mode_qst = MP_QSTR_OUT;
        } else if (mode == GPIO_MODE_OUTPUT_OD) {
            mode_qst = MP_QSTR_OPEN_DRAIN;
        } else {
            if (mode == GPIO_MODE_AF_PP) {
                mode_qst = MP_QSTR_ALT;
            } else {
                mode_qst = MP_QSTR_ALT_OPEN_DRAIN;
            }
        }
        mp_print_str(print, qstr_str(mode_qst));

        uint32_t pull = pin_get_pull(self);
        if (pull == GPIO_PULLUP) {
            mp_printf(print, ", pull=Pin.PULL_UP");
        } else if (pull == GPIO_PULLDOWN) {
            mp_printf(print, ", pull=Pin.PULL_DOWN");
        }
        mp_print_str(print, ")");
    }
}

static mp_obj_t pin_obj_init_helper(const machine_pin_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args);

// Note: mp_pin_make_new is declared in extmod/virtpin.h as non-static, so we don't use static here
mp_obj_t mp_pin_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    // Run an argument through the mapper and return the result
    const machine_pin_obj_t *pin = pin_find(args[0]);

    if (n_args > 1 || n_kw > 0) {
        // pin mode given, so configure this GPIO
        mp_map_t kw_args;
        mp_map_init_fixed_table(&kw_args, n_kw, args + n_args);
        pin_obj_init_helper(pin, n_args - 1, args + 1, &kw_args);
    } else {
        // enable the peripheral clock so pin reading at least works
        mp_hal_gpio_clock_enable(pin->gpio);
    }

    return MP_OBJ_FROM_PTR(pin);
}

// fast method for getting/setting pin value
static mp_obj_t pin_call(mp_obj_t self_in, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    if (n_args == 0) {
        // get pin
        return MP_OBJ_NEW_SMALL_INT(mp_hal_pin_read(self));
    } else {
        // set pin
        mp_hal_pin_write(self, mp_obj_is_true(args[0]));
        return mp_const_none;
    }
}

static mp_obj_t pin_obj_init_helper(const machine_pin_obj_t *self, size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_mode, ARG_pull, ARG_value, ARG_alt };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_mode, MP_ARG_REQUIRED | MP_ARG_INT },
        { MP_QSTR_pull, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE}},
        { MP_QSTR_value, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL}},
        { MP_QSTR_alt, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = -1}},
    };

    // parse args
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // get io mode
    uint mode = args[ARG_mode].u_int;
    if (!IS_GPIO_MODE(mode)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("invalid pin mode: %d"), mode);
    }

    // get pull mode
    uint pull = GPIO_NOPULL;
    if (args[ARG_pull].u_obj != mp_const_none) {
        pull = mp_obj_get_int(args[ARG_pull].u_obj);
    }
    if (!IS_GPIO_PULL(pull)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("invalid pin pull: %d"), pull);
    }

    mp_int_t af = args[ARG_alt].u_int;
    if ((mode == GPIO_MODE_AF_PP || mode == GPIO_MODE_AF_OD) && !IS_GPIO_AF(af)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("invalid pin af: %d"), af);
    }

    // enable the peripheral clock for the port of this pin
    mp_hal_gpio_clock_enable(self->gpio);

    // if given, set the pin value before initialising to prevent glitches
    if (args[ARG_value].u_obj != MP_OBJ_NULL) {
        mp_hal_pin_write(self, mp_obj_is_true(args[ARG_value].u_obj));
    }

    // configure the GPIO as requested
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = self->pin_mask;
    GPIO_InitStructure.Mode = mode;
    GPIO_InitStructure.Pull = pull;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Alternate = af;
    HAL_GPIO_Init(self->gpio, &GPIO_InitStructure);

    return mp_const_none;
}

static mp_obj_t pin_obj_init(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args) {
    return pin_obj_init_helper(MP_OBJ_TO_PTR(args[0]), n_args - 1, args + 1, kw_args);
}
static MP_DEFINE_CONST_FUN_OBJ_KW(pin_init_obj, 1, pin_obj_init);

static mp_obj_t pin_value(size_t n_args, const mp_obj_t *args) {
    return pin_call(args[0], n_args - 1, 0, args + 1);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(pin_value_obj, 1, 2, pin_value);

static mp_obj_t pin_off(mp_obj_t self_in) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_hal_pin_low(self);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(pin_off_obj, pin_off);

static mp_obj_t pin_on(mp_obj_t self_in) {
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_hal_pin_high(self);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(pin_on_obj, pin_on);

static mp_obj_t pin_mode(mp_obj_t self_in) {
    return MP_OBJ_NEW_SMALL_INT(pin_get_mode(MP_OBJ_TO_PTR(self_in)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(pin_mode_obj, pin_mode);

static mp_obj_t pin_pull(mp_obj_t self_in) {
    return MP_OBJ_NEW_SMALL_INT(pin_get_pull(MP_OBJ_TO_PTR(self_in)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(pin_pull_obj, pin_pull);

static const mp_rom_map_elem_t pin_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&pin_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&pin_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&pin_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&pin_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_low), MP_ROM_PTR(&pin_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_high), MP_ROM_PTR(&pin_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_mode), MP_ROM_PTR(&pin_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_pull), MP_ROM_PTR(&pin_pull_obj) },

    // class attributes
    { MP_ROM_QSTR(MP_QSTR_board), MP_ROM_PTR(&pin_board_pins_obj_type) },
    { MP_ROM_QSTR(MP_QSTR_cpu), MP_ROM_PTR(&pin_cpu_pins_obj_type) },

    // class constants
    { MP_ROM_QSTR(MP_QSTR_IN), MP_ROM_INT(GPIO_MODE_INPUT) },
    { MP_ROM_QSTR(MP_QSTR_OUT), MP_ROM_INT(GPIO_MODE_OUTPUT_PP) },
    { MP_ROM_QSTR(MP_QSTR_OUT_PP), MP_ROM_INT(GPIO_MODE_OUTPUT_PP) },
    { MP_ROM_QSTR(MP_QSTR_OUT_OD), MP_ROM_INT(GPIO_MODE_OUTPUT_OD) },
    { MP_ROM_QSTR(MP_QSTR_OPEN_DRAIN), MP_ROM_INT(GPIO_MODE_OUTPUT_OD) },
    { MP_ROM_QSTR(MP_QSTR_ALT), MP_ROM_INT(GPIO_MODE_AF_PP) },
    { MP_ROM_QSTR(MP_QSTR_ALT_PP), MP_ROM_INT(GPIO_MODE_AF_PP) },
    { MP_ROM_QSTR(MP_QSTR_ALT_OD), MP_ROM_INT(GPIO_MODE_AF_OD) },
    { MP_ROM_QSTR(MP_QSTR_ALT_OPEN_DRAIN), MP_ROM_INT(GPIO_MODE_AF_OD) },
    { MP_ROM_QSTR(MP_QSTR_ANALOG), MP_ROM_INT(GPIO_MODE_ANALOG) },
    { MP_ROM_QSTR(MP_QSTR_PULL_NONE), MP_ROM_INT(GPIO_NOPULL) },
    { MP_ROM_QSTR(MP_QSTR_PULL_UP), MP_ROM_INT(GPIO_PULLUP) },
    { MP_ROM_QSTR(MP_QSTR_PULL_DOWN), MP_ROM_INT(GPIO_PULLDOWN) },
    { MP_ROM_QSTR(MP_QSTR_IRQ_RISING), MP_ROM_INT(GPIO_MODE_IT_RISING) },
    { MP_ROM_QSTR(MP_QSTR_IRQ_FALLING), MP_ROM_INT(GPIO_MODE_IT_FALLING) },
};
static MP_DEFINE_CONST_DICT(pin_locals_dict, pin_locals_dict_table);

static mp_uint_t pin_ioctl(mp_obj_t self_in, mp_uint_t request, uintptr_t arg, int *errcode) {
    (void)errcode;
    machine_pin_obj_t *self = MP_OBJ_TO_PTR(self_in);

    switch (request) {
        case MP_PIN_READ: {
            return mp_hal_pin_read(self);
        }
        case MP_PIN_WRITE: {
            mp_hal_pin_write(self, arg);
            return 0;
        }
    }
    return -1;
}

static const mp_pin_p_t pin_pin_p = {
    .ioctl = pin_ioctl,
};

MP_DEFINE_CONST_OBJ_TYPE(
    pin_type,
    MP_QSTR_Pin,
    MP_TYPE_FLAG_NONE,
    make_new, mp_pin_make_new,
    print, pin_print,
    call, pin_call,
    protocol, &pin_pin_p,
    locals_dict, &pin_locals_dict
);

MP_REGISTER_ROOT_POINTER(mp_obj_t pin_class_mapper);
MP_REGISTER_ROOT_POINTER(mp_obj_t pin_class_map_dict);
