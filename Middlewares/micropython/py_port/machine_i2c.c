/*
 * Hardware I2C bindings for machine.I2C (STM32F405)
 */

#include "py/runtime.h"
#include "py/mperrno.h"
#include "extmod/modmachine.h"
#include "i2c.h"

#if MICROPY_PY_MACHINE_I2C

typedef struct _machine_hard_i2c_obj_t {
    mp_obj_base_t base;
    i2c_t *i2c;
    mp_hal_pin_obj_t scl;
    mp_hal_pin_obj_t sda;
} machine_hard_i2c_obj_t;

static const machine_hard_i2c_obj_t machine_hard_i2c_obj[MICROPY_HW_MAX_I2C] = {
#if defined(MICROPY_HW_I2C1_SCL)
    [0] = { { &machine_i2c_type }, I2C1, MICROPY_HW_I2C1_SCL, MICROPY_HW_I2C1_SDA },
#else
    [0] = { { &machine_i2c_type }, NULL, NULL, NULL },
#endif
#if defined(MICROPY_HW_I2C2_SCL)
    [1] = { { &machine_i2c_type }, I2C2, MICROPY_HW_I2C2_SCL, MICROPY_HW_I2C2_SDA },
#else
    [1] = { { &machine_i2c_type }, NULL, NULL, NULL },
#endif
};

static void machine_hard_i2c_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind;
    machine_hard_i2c_obj_t *self = MP_OBJ_TO_PTR(self_in);
    uint32_t freq = 0;
    I2C_HandleTypeDef *hi2c = i2c_get_handle(self->i2c);
    if (hi2c != NULL) {
        freq = hi2c->Init.ClockSpeed;
    }
    mp_printf(print, "I2C(%u, scl=%q, sda=%q, freq=%u)",
        (unsigned)(self - &machine_hard_i2c_obj[0]) + 1,
        mp_hal_pin_name(self->scl), mp_hal_pin_name(self->sda), freq);
}

static void machine_hard_i2c_init(machine_hard_i2c_obj_t *self, uint32_t freq, uint32_t timeout_us) {
    i2c_init0();
    if (self->i2c == NULL) {
        mp_raise_ValueError(MP_ERROR_TEXT("I2C does not exist"));
    }
    uint32_t timeout_ms = (timeout_us + 999) / 1000;
    int ret = i2c_init(self->i2c, self->scl, self->sda, freq, timeout_ms);
    if (ret < 0) {
        mp_raise_OSError(-ret);
    }
}

static int machine_hard_i2c_transfer(mp_obj_base_t *self_in, uint16_t addr, size_t n, mp_machine_i2c_buf_t *bufs, unsigned int flags) {
    machine_hard_i2c_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return i2c_transfer(self->i2c, addr, n, bufs, flags);
}

mp_obj_t machine_hard_i2c_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    MP_MACHINE_I2C_CHECK_FOR_LEGACY_SOFTI2C_CONSTRUCTION(n_args, n_kw, all_args);

    enum { ARG_id, ARG_scl, ARG_sda, ARG_freq, ARG_timeout };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_id, MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_scl, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_sda, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_freq, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 400000} },
        { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 50000} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    int i2c_id = i2c_find_peripheral(args[ARG_id].u_obj);
    machine_hard_i2c_obj_t *self = (machine_hard_i2c_obj_t *)&machine_hard_i2c_obj[i2c_id - 1];

    if (args[ARG_scl].u_obj != MP_OBJ_NULL || args[ARG_sda].u_obj != MP_OBJ_NULL) {
        mp_raise_ValueError(MP_ERROR_TEXT("explicit choice of scl/sda is not implemented"));
    }

    machine_hard_i2c_init(self, args[ARG_freq].u_int, args[ARG_timeout].u_int);
    return MP_OBJ_FROM_PTR(self);
}

static const mp_machine_i2c_p_t machine_hard_i2c_p = {
    .transfer = machine_hard_i2c_transfer,
};

MP_DEFINE_CONST_OBJ_TYPE(
    machine_i2c_type,
    MP_QSTR_I2C,
    MP_TYPE_FLAG_NONE,
    make_new, machine_hard_i2c_make_new,
    print, machine_hard_i2c_print,
    protocol, &machine_hard_i2c_p,
    locals_dict, &mp_machine_i2c_locals_dict
    );

#endif // MICROPY_PY_MACHINE_I2C