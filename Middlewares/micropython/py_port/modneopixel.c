#include <stdint.h>
#include <string.h>

#include "py/runtime.h"
#include "py/objarray.h"
#include "py/mperrno.h"

#include "stm32f4xx_hal.h"

// Minimal WS2812/NeoPixel driver for STM32F405.
// Does not depend on machine.Pin; instead, pin is specified as ("A", 5) / ("B", 3) etc.

// WS2812 timing (ns). Typical: T0H=350ns, T0L=800ns, T1H=700ns, T1L=600ns.
// We implement delays using DWT cycle counter at runtime SystemCoreClock.

static inline void neopixel_dwt_init(void) {
    // Enable TRC
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // Enable cycle counter
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

static inline void neopixel_delay_cycles(uint32_t cycles) {
    uint32_t start = DWT->CYCCNT;
    while ((uint32_t)(DWT->CYCCNT - start) < cycles) {
        __NOP();
    }
}

static GPIO_TypeDef *neopixel_gpio_port_from_char(char c) {
    switch (c) {
        case 'A': return GPIOA;
        case 'B': return GPIOB;
        case 'C': return GPIOC;
        case 'D': return GPIOD;
        case 'E': return GPIOE;
        case 'F': return GPIOF;
        case 'G': return GPIOG;
        case 'H': return GPIOH;
        case 'I': return GPIOI;
        default: return NULL;
    }
}

static void neopixel_gpio_enable_clock(GPIO_TypeDef *port) {
    if (port == GPIOA) { __HAL_RCC_GPIOA_CLK_ENABLE(); }
    else if (port == GPIOB) { __HAL_RCC_GPIOB_CLK_ENABLE(); }
    else if (port == GPIOC) { __HAL_RCC_GPIOC_CLK_ENABLE(); }
    else if (port == GPIOD) { __HAL_RCC_GPIOD_CLK_ENABLE(); }
    else if (port == GPIOE) { __HAL_RCC_GPIOE_CLK_ENABLE(); }
    else if (port == GPIOF) { __HAL_RCC_GPIOF_CLK_ENABLE(); }
    else if (port == GPIOG) { __HAL_RCC_GPIOG_CLK_ENABLE(); }
    else if (port == GPIOH) { __HAL_RCC_GPIOH_CLK_ENABLE(); }
    else if (port == GPIOI) { __HAL_RCC_GPIOI_CLK_ENABLE(); }
}

static void neopixel_gpio_config_output(GPIO_TypeDef *port, uint16_t pin_mask) {
    GPIO_InitTypeDef init;
    memset(&init, 0, sizeof(init));
    init.Pin = pin_mask;
    init.Mode = GPIO_MODE_OUTPUT_PP;
    init.Pull = GPIO_NOPULL;
    init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(port, &init);
}

static void neopixel_write_ws2812(GPIO_TypeDef *port, uint16_t pin_mask, const uint8_t *data, size_t len,
    uint32_t t0h_ns, uint32_t t0l_ns, uint32_t t1h_ns, uint32_t t1l_ns) {

    // Convert ns to cycles.
    uint32_t hz = SystemCoreClock;
    // cycles = ns * hz / 1e9
    uint32_t t0h = (uint32_t)(((uint64_t)t0h_ns * hz) / 1000000000ULL);
    uint32_t t0l = (uint32_t)(((uint64_t)t0l_ns * hz) / 1000000000ULL);
    uint32_t t1h = (uint32_t)(((uint64_t)t1h_ns * hz) / 1000000000ULL);
    uint32_t t1l = (uint32_t)(((uint64_t)t1l_ns * hz) / 1000000000ULL);

    // Ensure minimum cycles (avoid 0 on slow clocks).
    if (t0h < 1) t0h = 1;
    if (t0l < 1) t0l = 1;
    if (t1h < 1) t1h = 1;
    if (t1l < 1) t1l = 1;

    uint32_t set_mask = pin_mask;
    uint32_t clr_mask = ((uint32_t)pin_mask) << 16;

    uint32_t irq = __get_PRIMASK();
    __disable_irq();

    for (size_t i = 0; i < len; ++i) {
        uint8_t byte = data[i];
        for (int bit = 7; bit >= 0; --bit) {
            if (byte & (1u << bit)) {
                port->BSRR = set_mask;
                neopixel_delay_cycles(t1h);
                port->BSRR = clr_mask;
                neopixel_delay_cycles(t1l);
            } else {
                port->BSRR = set_mask;
                neopixel_delay_cycles(t0h);
                port->BSRR = clr_mask;
                neopixel_delay_cycles(t0l);
            }
        }
    }

    if (!irq) {
        __enable_irq();
    }

    // Latch/reset: >50us low.
    // Use a conservative delay.
    uint32_t reset_cycles = (uint32_t)(((uint64_t)60 * hz) / 1000000ULL);
    neopixel_delay_cycles(reset_cycles);
}

// NeoPixel class

typedef struct _neopixel_obj_t {
    mp_obj_base_t base;
    GPIO_TypeDef *port;
    uint16_t pin_mask;
    size_t n;
    uint8_t bpp;
    mp_obj_t buf_obj; // bytearray
    uint32_t t0h_ns, t0l_ns, t1h_ns, t1l_ns;
} neopixel_obj_t;

static mp_obj_t neopixel_subscr(mp_obj_t self_in, mp_obj_t index_in, mp_obj_t value);

static mp_obj_t neopixel_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    enum { ARG_pin, ARG_n, ARG_bpp, ARG_timing };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_pin, MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
        { MP_QSTR_n, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_bpp, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 3} },
        // timing: (t0h, t0l, t1h, t1l) in ns
        { MP_QSTR_timing, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
    };

    mp_arg_val_t parsed[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, parsed);

    // pin must be ("A", 5) or (b"A", 5)
    mp_obj_t *pin_items;
    mp_obj_get_array_fixed_n(parsed[ARG_pin].u_obj, 2, &pin_items);

    const char *port_s = mp_obj_str_get_str(pin_items[0]);
    if (port_s == NULL || port_s[0] == '\0') {
        mp_raise_ValueError(MP_ERROR_TEXT("pin"));
    }
    char port_c = port_s[0];
    if (port_c >= 'a' && port_c <= 'z') {
        port_c = (char)(port_c - 'a' + 'A');
    }
    GPIO_TypeDef *port = neopixel_gpio_port_from_char(port_c);
    if (port == NULL) {
        mp_raise_ValueError(MP_ERROR_TEXT("pin"));
    }

    int pin_num = mp_obj_get_int(pin_items[1]);
    if (pin_num < 0 || pin_num > 15) {
        mp_raise_ValueError(MP_ERROR_TEXT("pin"));
    }

    int n = parsed[ARG_n].u_int;
    if (n <= 0) {
        mp_raise_ValueError(MP_ERROR_TEXT("n"));
    }

    int bpp = parsed[ARG_bpp].u_int;
    if (bpp != 3 && bpp != 4) {
        mp_raise_ValueError(MP_ERROR_TEXT("bpp"));
    }

    uint32_t t0h_ns = 350, t0l_ns = 800, t1h_ns = 700, t1l_ns = 600;
    if (parsed[ARG_timing].u_obj != mp_const_none) {
        mp_obj_t *timing_items;
        mp_obj_get_array_fixed_n(parsed[ARG_timing].u_obj, 4, &timing_items);
        t0h_ns = (uint32_t)mp_obj_get_int(timing_items[0]);
        t0l_ns = (uint32_t)mp_obj_get_int(timing_items[1]);
        t1h_ns = (uint32_t)mp_obj_get_int(timing_items[2]);
        t1l_ns = (uint32_t)mp_obj_get_int(timing_items[3]);
    }

    neopixel_obj_t *self = mp_obj_malloc(neopixel_obj_t, type);
    self->port = port;
    self->pin_mask = (uint16_t)(1u << pin_num);
    self->n = (size_t)n;
    self->bpp = (uint8_t)bpp;
    self->t0h_ns = t0h_ns;
    self->t0l_ns = t0l_ns;
    self->t1h_ns = t1h_ns;
    self->t1l_ns = t1l_ns;

    self->buf_obj = mp_obj_new_bytearray(self->n * self->bpp, NULL);

    neopixel_gpio_enable_clock(port);
    neopixel_gpio_config_output(port, self->pin_mask);
    neopixel_dwt_init();

    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t neopixel_write(mp_obj_t self_in) {
    neopixel_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_array_t *arr = MP_OBJ_TO_PTR(self->buf_obj);

    neopixel_write_ws2812(self->port, self->pin_mask, (const uint8_t *)arr->items, arr->len,
        self->t0h_ns, self->t0l_ns, self->t1h_ns, self->t1l_ns);

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(neopixel_write_obj, neopixel_write);

static mp_obj_t neopixel_fill(mp_obj_t self_in, mp_obj_t col_in) {
    neopixel_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_array_t *arr = MP_OBJ_TO_PTR(self->buf_obj);

    mp_obj_t *items;
    size_t n_items;
    mp_obj_get_array(col_in, &n_items, &items);

    if ((self->bpp == 3 && n_items < 3) || (self->bpp == 4 && n_items < 4)) {
        mp_raise_ValueError(MP_ERROR_TEXT("color"));
    }

    uint8_t r = (uint8_t)mp_obj_get_int(items[0]);
    uint8_t g = (uint8_t)mp_obj_get_int(items[1]);
    uint8_t b = (uint8_t)mp_obj_get_int(items[2]);
    uint8_t w = 0;
    if (self->bpp == 4) {
        w = (uint8_t)mp_obj_get_int(items[3]);
    }

    // Store as GRB (and optional W at end) as per common NeoPixel convention.
    for (size_t i = 0; i < self->n; ++i) {
        size_t off = i * self->bpp;
        ((uint8_t *)arr->items)[off + 0] = g;
        ((uint8_t *)arr->items)[off + 1] = r;
        ((uint8_t *)arr->items)[off + 2] = b;
        if (self->bpp == 4) {
            ((uint8_t *)arr->items)[off + 3] = w;
        }
    }

    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(neopixel_fill_obj, neopixel_fill);

static mp_obj_t neopixel_buf(mp_obj_t self_in) {
    neopixel_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return self->buf_obj;
}
static MP_DEFINE_CONST_FUN_OBJ_1(neopixel_buf_obj, neopixel_buf);

static mp_obj_t neopixel_len(mp_obj_t self_in) {
    neopixel_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int_from_uint(self->n);
}
static MP_DEFINE_CONST_FUN_OBJ_1(neopixel_len_obj, neopixel_len);

static mp_obj_t neopixel_subscr(mp_obj_t self_in, mp_obj_t index_in, mp_obj_t value) {
    neopixel_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_obj_array_t *arr = MP_OBJ_TO_PTR(self->buf_obj);
    uint8_t *buf = (uint8_t *)arr->items;

    size_t idx = (size_t)mp_obj_get_int(index_in);
    if (idx >= self->n) {
        mp_raise_IndexError(MP_ERROR_TEXT("index"));
    }

    size_t off = idx * self->bpp;

    if (value == MP_OBJ_SENTINEL) {
        // Load: return (r,g,b[,w])
        if (self->bpp == 3) {
            // stored as GRB
            return mp_obj_new_tuple(3, (mp_obj_t[]) {
                mp_obj_new_int(buf[off + 1]),
                mp_obj_new_int(buf[off + 0]),
                mp_obj_new_int(buf[off + 2]),
            });
        } else {
            // stored as GRBW
            return mp_obj_new_tuple(4, (mp_obj_t[]) {
                mp_obj_new_int(buf[off + 1]),
                mp_obj_new_int(buf[off + 0]),
                mp_obj_new_int(buf[off + 2]),
                mp_obj_new_int(buf[off + 3]),
            });
        }
    }

    if (value == mp_const_none) {
        mp_raise_TypeError(MP_ERROR_TEXT("can't delete"));
    }

    // Store: accept tuple/list of (r,g,b[,w])
    mp_obj_t *items;
    size_t n_items;
    mp_obj_get_array(value, &n_items, &items);

    if ((self->bpp == 3 && n_items < 3) || (self->bpp == 4 && n_items < 4)) {
        mp_raise_ValueError(MP_ERROR_TEXT("color"));
    }

    uint8_t r = (uint8_t)mp_obj_get_int(items[0]);
    uint8_t g = (uint8_t)mp_obj_get_int(items[1]);
    uint8_t b = (uint8_t)mp_obj_get_int(items[2]);
    buf[off + 0] = g;
    buf[off + 1] = r;
    buf[off + 2] = b;
    if (self->bpp == 4) {
        uint8_t w = (uint8_t)mp_obj_get_int(items[3]);
        buf[off + 3] = w;
    }

    return mp_const_none;
}

static const mp_rom_map_elem_t neopixel_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&neopixel_write_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill), MP_ROM_PTR(&neopixel_fill_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf), MP_ROM_PTR(&neopixel_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR___len__), MP_ROM_PTR(&neopixel_len_obj) },
};
static MP_DEFINE_CONST_DICT(neopixel_locals_dict, neopixel_locals_dict_table);

static MP_DEFINE_CONST_OBJ_TYPE(
    neopixel_type,
    MP_QSTR_NeoPixel,
    MP_TYPE_FLAG_NONE,
    make_new, neopixel_make_new,
    subscr, neopixel_subscr,
    locals_dict, &neopixel_locals_dict
    );

static const mp_rom_map_elem_t neopixel_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_neopixel) },
    { MP_ROM_QSTR(MP_QSTR_NeoPixel), MP_ROM_PTR(&neopixel_type) },
};
static MP_DEFINE_CONST_DICT(neopixel_module_globals, neopixel_module_globals_table);

const mp_obj_module_t mp_module_neopixel = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&neopixel_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_neopixel, mp_module_neopixel);
