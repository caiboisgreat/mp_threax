/*
 * Pin definitions for STM32F405RGT6
 * 这个文件定义了所有可用的GPIO引脚
 */

#include "py/obj.h"
#include "py/mphal.h"
#include "pin.h"

// 定义引脚宏
#define PIN(p_port, p_pin, p_name) \
    const machine_pin_obj_t pin_##p_name = { \
        { &pin_type }, \
        .name = MP_QSTR_##p_name, \
        .gpio = GPIO##p_port, \
        .pin = (p_pin), \
        .pin_mask = (1 << (p_pin)), \
        .port = (#p_port[0] - 'A'), \
    }

// STM32F405RGT6 has ports A, B, C, D, E, H
// Define all available pins

// Port A
PIN(A, 0, A0);
PIN(A, 1, A1);
PIN(A, 2, A2);
PIN(A, 3, A3);
PIN(A, 4, A4);
PIN(A, 5, A5);
PIN(A, 6, A6);
PIN(A, 7, A7);
PIN(A, 8, A8);
PIN(A, 9, A9);
PIN(A, 10, A10);
PIN(A, 11, A11);
PIN(A, 12, A12);
PIN(A, 13, A13);
PIN(A, 14, A14);
PIN(A, 15, A15);

// Port B
PIN(B, 0, B0);
PIN(B, 1, B1);
PIN(B, 2, B2);
PIN(B, 3, B3);
PIN(B, 4, B4);
PIN(B, 5, B5);
PIN(B, 6, B6);
PIN(B, 7, B7);
PIN(B, 8, B8);
PIN(B, 9, B9);
PIN(B, 10, B10);
PIN(B, 11, B11);
PIN(B, 12, B12);
PIN(B, 13, B13);
PIN(B, 14, B14);
PIN(B, 15, B15);

// Port C
PIN(C, 0, C0);
PIN(C, 1, C1);
PIN(C, 2, C2);
PIN(C, 3, C3);
PIN(C, 4, C4);
PIN(C, 5, C5);
PIN(C, 6, C6);
PIN(C, 7, C7);
PIN(C, 8, C8);
PIN(C, 9, C9);
PIN(C, 10, C10);
PIN(C, 11, C11);
PIN(C, 12, C12);
PIN(C, 13, C13);
PIN(C, 14, C14);
PIN(C, 15, C15);

// Port D
PIN(D, 0, D0);
PIN(D, 1, D1);
PIN(D, 2, D2);
PIN(D, 3, D3);
PIN(D, 4, D4);
PIN(D, 5, D5);
PIN(D, 6, D6);
PIN(D, 7, D7);
PIN(D, 8, D8);
PIN(D, 9, D9);
PIN(D, 10, D10);
PIN(D, 11, D11);
PIN(D, 12, D12);
PIN(D, 13, D13);
PIN(D, 14, D14);
PIN(D, 15, D15);

// Port E
PIN(E, 0, E0);
PIN(E, 1, E1);
PIN(E, 2, E2);
PIN(E, 3, E3);
PIN(E, 4, E4);
PIN(E, 5, E5);
PIN(E, 6, E6);
PIN(E, 7, E7);
PIN(E, 8, E8);
PIN(E, 9, E9);
PIN(E, 10, E10);
PIN(E, 11, E11);
PIN(E, 12, E12);
PIN(E, 13, E13);
PIN(E, 14, E14);
PIN(E, 15, E15);

// Port H (limited pins on STM32F405)
PIN(H, 0, H0);
PIN(H, 1, H1);

// Board-specific pin names (from main.h)
// #define yello_led_Pin GPIO_PIN_15, yello_led_GPIO_Port GPIOA
// #define blue_led_Pin GPIO_PIN_4, blue_led_GPIO_Port GPIOB

// CPU pins dict (all pins accessible by CPU name like A0, B4, etc.)
static const mp_rom_map_elem_t pin_cpu_pins_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_A0), MP_ROM_PTR(&pin_A0) },
    { MP_ROM_QSTR(MP_QSTR_A1), MP_ROM_PTR(&pin_A1) },
    { MP_ROM_QSTR(MP_QSTR_A2), MP_ROM_PTR(&pin_A2) },
    { MP_ROM_QSTR(MP_QSTR_A3), MP_ROM_PTR(&pin_A3) },
    { MP_ROM_QSTR(MP_QSTR_A4), MP_ROM_PTR(&pin_A4) },
    { MP_ROM_QSTR(MP_QSTR_A5), MP_ROM_PTR(&pin_A5) },
    { MP_ROM_QSTR(MP_QSTR_A6), MP_ROM_PTR(&pin_A6) },
    { MP_ROM_QSTR(MP_QSTR_A7), MP_ROM_PTR(&pin_A7) },
    { MP_ROM_QSTR(MP_QSTR_A8), MP_ROM_PTR(&pin_A8) },
    { MP_ROM_QSTR(MP_QSTR_A9), MP_ROM_PTR(&pin_A9) },
    { MP_ROM_QSTR(MP_QSTR_A10), MP_ROM_PTR(&pin_A10) },
    { MP_ROM_QSTR(MP_QSTR_A11), MP_ROM_PTR(&pin_A11) },
    { MP_ROM_QSTR(MP_QSTR_A12), MP_ROM_PTR(&pin_A12) },
    { MP_ROM_QSTR(MP_QSTR_A13), MP_ROM_PTR(&pin_A13) },
    { MP_ROM_QSTR(MP_QSTR_A14), MP_ROM_PTR(&pin_A14) },
    { MP_ROM_QSTR(MP_QSTR_A15), MP_ROM_PTR(&pin_A15) },

    { MP_ROM_QSTR(MP_QSTR_B0), MP_ROM_PTR(&pin_B0) },
    { MP_ROM_QSTR(MP_QSTR_B1), MP_ROM_PTR(&pin_B1) },
    { MP_ROM_QSTR(MP_QSTR_B2), MP_ROM_PTR(&pin_B2) },
    { MP_ROM_QSTR(MP_QSTR_B3), MP_ROM_PTR(&pin_B3) },
    { MP_ROM_QSTR(MP_QSTR_B4), MP_ROM_PTR(&pin_B4) },
    { MP_ROM_QSTR(MP_QSTR_B5), MP_ROM_PTR(&pin_B5) },
    { MP_ROM_QSTR(MP_QSTR_B6), MP_ROM_PTR(&pin_B6) },
    { MP_ROM_QSTR(MP_QSTR_B7), MP_ROM_PTR(&pin_B7) },
    { MP_ROM_QSTR(MP_QSTR_B8), MP_ROM_PTR(&pin_B8) },
    { MP_ROM_QSTR(MP_QSTR_B9), MP_ROM_PTR(&pin_B9) },
    { MP_ROM_QSTR(MP_QSTR_B10), MP_ROM_PTR(&pin_B10) },
    { MP_ROM_QSTR(MP_QSTR_B11), MP_ROM_PTR(&pin_B11) },
    { MP_ROM_QSTR(MP_QSTR_B12), MP_ROM_PTR(&pin_B12) },
    { MP_ROM_QSTR(MP_QSTR_B13), MP_ROM_PTR(&pin_B13) },
    { MP_ROM_QSTR(MP_QSTR_B14), MP_ROM_PTR(&pin_B14) },
    { MP_ROM_QSTR(MP_QSTR_B15), MP_ROM_PTR(&pin_B15) },

    { MP_ROM_QSTR(MP_QSTR_C0), MP_ROM_PTR(&pin_C0) },
    { MP_ROM_QSTR(MP_QSTR_C1), MP_ROM_PTR(&pin_C1) },
    { MP_ROM_QSTR(MP_QSTR_C2), MP_ROM_PTR(&pin_C2) },
    { MP_ROM_QSTR(MP_QSTR_C3), MP_ROM_PTR(&pin_C3) },
    { MP_ROM_QSTR(MP_QSTR_C4), MP_ROM_PTR(&pin_C4) },
    { MP_ROM_QSTR(MP_QSTR_C5), MP_ROM_PTR(&pin_C5) },
    { MP_ROM_QSTR(MP_QSTR_C6), MP_ROM_PTR(&pin_C6) },
    { MP_ROM_QSTR(MP_QSTR_C7), MP_ROM_PTR(&pin_C7) },
    { MP_ROM_QSTR(MP_QSTR_C8), MP_ROM_PTR(&pin_C8) },
    { MP_ROM_QSTR(MP_QSTR_C9), MP_ROM_PTR(&pin_C9) },
    { MP_ROM_QSTR(MP_QSTR_C10), MP_ROM_PTR(&pin_C10) },
    { MP_ROM_QSTR(MP_QSTR_C11), MP_ROM_PTR(&pin_C11) },
    { MP_ROM_QSTR(MP_QSTR_C12), MP_ROM_PTR(&pin_C12) },
    { MP_ROM_QSTR(MP_QSTR_C13), MP_ROM_PTR(&pin_C13) },
    { MP_ROM_QSTR(MP_QSTR_C14), MP_ROM_PTR(&pin_C14) },
    { MP_ROM_QSTR(MP_QSTR_C15), MP_ROM_PTR(&pin_C15) },

    { MP_ROM_QSTR(MP_QSTR_D0), MP_ROM_PTR(&pin_D0) },
    { MP_ROM_QSTR(MP_QSTR_D1), MP_ROM_PTR(&pin_D1) },
    { MP_ROM_QSTR(MP_QSTR_D2), MP_ROM_PTR(&pin_D2) },
    { MP_ROM_QSTR(MP_QSTR_D3), MP_ROM_PTR(&pin_D3) },
    { MP_ROM_QSTR(MP_QSTR_D4), MP_ROM_PTR(&pin_D4) },
    { MP_ROM_QSTR(MP_QSTR_D5), MP_ROM_PTR(&pin_D5) },
    { MP_ROM_QSTR(MP_QSTR_D6), MP_ROM_PTR(&pin_D6) },
    { MP_ROM_QSTR(MP_QSTR_D7), MP_ROM_PTR(&pin_D7) },
    { MP_ROM_QSTR(MP_QSTR_D8), MP_ROM_PTR(&pin_D8) },
    { MP_ROM_QSTR(MP_QSTR_D9), MP_ROM_PTR(&pin_D9) },
    { MP_ROM_QSTR(MP_QSTR_D10), MP_ROM_PTR(&pin_D10) },
    { MP_ROM_QSTR(MP_QSTR_D11), MP_ROM_PTR(&pin_D11) },
    { MP_ROM_QSTR(MP_QSTR_D12), MP_ROM_PTR(&pin_D12) },
    { MP_ROM_QSTR(MP_QSTR_D13), MP_ROM_PTR(&pin_D13) },
    { MP_ROM_QSTR(MP_QSTR_D14), MP_ROM_PTR(&pin_D14) },
    { MP_ROM_QSTR(MP_QSTR_D15), MP_ROM_PTR(&pin_D15) },

    { MP_ROM_QSTR(MP_QSTR_E0), MP_ROM_PTR(&pin_E0) },
    { MP_ROM_QSTR(MP_QSTR_E1), MP_ROM_PTR(&pin_E1) },
    { MP_ROM_QSTR(MP_QSTR_E2), MP_ROM_PTR(&pin_E2) },
    { MP_ROM_QSTR(MP_QSTR_E3), MP_ROM_PTR(&pin_E3) },
    { MP_ROM_QSTR(MP_QSTR_E4), MP_ROM_PTR(&pin_E4) },
    { MP_ROM_QSTR(MP_QSTR_E5), MP_ROM_PTR(&pin_E5) },
    { MP_ROM_QSTR(MP_QSTR_E6), MP_ROM_PTR(&pin_E6) },
    { MP_ROM_QSTR(MP_QSTR_E7), MP_ROM_PTR(&pin_E7) },
    { MP_ROM_QSTR(MP_QSTR_E8), MP_ROM_PTR(&pin_E8) },
    { MP_ROM_QSTR(MP_QSTR_E9), MP_ROM_PTR(&pin_E9) },
    { MP_ROM_QSTR(MP_QSTR_E10), MP_ROM_PTR(&pin_E10) },
    { MP_ROM_QSTR(MP_QSTR_E11), MP_ROM_PTR(&pin_E11) },
    { MP_ROM_QSTR(MP_QSTR_E12), MP_ROM_PTR(&pin_E12) },
    { MP_ROM_QSTR(MP_QSTR_E13), MP_ROM_PTR(&pin_E13) },
    { MP_ROM_QSTR(MP_QSTR_E14), MP_ROM_PTR(&pin_E14) },
    { MP_ROM_QSTR(MP_QSTR_E15), MP_ROM_PTR(&pin_E15) },

    { MP_ROM_QSTR(MP_QSTR_H0), MP_ROM_PTR(&pin_H0) },
    { MP_ROM_QSTR(MP_QSTR_H1), MP_ROM_PTR(&pin_H1) },
};
MP_DEFINE_CONST_DICT(machine_pin_cpu_pins_locals_dict, pin_cpu_pins_locals_dict_table);

// Board pins dict (user-friendly names)
static const mp_rom_map_elem_t pin_board_pins_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_LED_RED), MP_ROM_PTR(&pin_A13) },
    { MP_ROM_QSTR(MP_QSTR_LED_GREEN), MP_ROM_PTR(&pin_A14) },
    { MP_ROM_QSTR(MP_QSTR_LED_YELLOW), MP_ROM_PTR(&pin_A15) },
    { MP_ROM_QSTR(MP_QSTR_LED_BLUE), MP_ROM_PTR(&pin_B4) },
};
MP_DEFINE_CONST_DICT(machine_pin_board_pins_locals_dict, pin_board_pins_locals_dict_table);

// Pin.board type
static void pin_board_pins_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    mp_obj_t obj = mp_obj_dict_get(MP_OBJ_FROM_PTR(&machine_pin_board_pins_locals_dict), MP_OBJ_NEW_QSTR(attr));
    dest[0] = obj;
}

MP_DEFINE_CONST_OBJ_TYPE(
    pin_board_pins_obj_type,
    MP_QSTR_board,
    MP_TYPE_FLAG_NONE,
    attr, pin_board_pins_obj_attr
);

// Pin.cpu type
static void pin_cpu_pins_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    mp_obj_t obj = mp_obj_dict_get(MP_OBJ_FROM_PTR(&machine_pin_cpu_pins_locals_dict), MP_OBJ_NEW_QSTR(attr));
    dest[0] = obj;
}

MP_DEFINE_CONST_OBJ_TYPE(
    pin_cpu_pins_obj_type,
    MP_QSTR_cpu,
    MP_TYPE_FLAG_NONE,
    attr, pin_cpu_pins_obj_attr
);
