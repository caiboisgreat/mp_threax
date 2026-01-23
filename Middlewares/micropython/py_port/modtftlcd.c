/**
 ******************************************************************************
 * Based on 01Studio ILI9341 driver for STM32
 * Adapted for ThreadX MicroPython with LCD24 API
 ******************************************************************************
**/

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include "py/runtime.h"
#include "py/mphal.h"
#include "spi.h"
#include "pin.h"
#include "font.h"

#ifndef STATIC
#define STATIC static
#endif

#if (MICROPY_ENABLE_TFTLCD && MICROPY_ENABLE_SPILCD)

typedef struct _lcd_spibus_obj_t {
    mp_obj_base_t base;
    const spi_t *spi;
    const machine_pin_obj_t *pin_dc;
    const machine_pin_obj_t *pin_rst;
    const machine_pin_obj_t *pin_cs;
} lcd_spibus_obj_t;

typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes;
} lcd_init_cmd_t;

STATIC lcd_spibus_obj_t *p_lcd = NULL;

STATIC const lcd_init_cmd_t ili9341_init_cmds[] = {
    {0xCF, {0x00, 0x83, 0x30}, 3},
    {0xED, {0x64, 0x03, 0x12, 0x81}, 4},
    {0xE8, {0x85, 0x01, 0x79}, 3},
    {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
    {0xF7, {0x20}, 1},
    {0xEA, {0x00, 0x00}, 2},
    {0xC0, {0x26}, 1},
    {0xC1, {0x11}, 1},
    {0xC5, {0x35, 0x3E}, 2},
    {0xC7, {0xBE}, 1},
    {0x36, {0x48}, 1},
    {0x3A, {0x55}, 1},
    {0xB1, {0x00, 0x1B}, 2},
    {0xF2, {0x08}, 1},
    {0x26, {0x01}, 1},
    {0xE0, {0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0x87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00}, 15},
    {0xE1, {0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F}, 15},
    {0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
    {0x2B, {0x00, 0x00, 0x01, 0x3F}, 4},
    {0x2C, {0}, 0},
    {0xB7, {0x07}, 1},
    {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
    {0x11, {0}, 0x80},
    {0x29, {0}, 0x80},
    {0, {0}, 0xFF},
};

STATIC uint16_t lcd_width = 240;
STATIC uint16_t lcd_height = 320;

// Low-level SPI functions
STATIC void lcd_delay(void) {
    __asm volatile ("nop\nnop");
}

STATIC void lcd_spibus_send(lcd_spibus_obj_t *self, const uint8_t *data, uint32_t length) {
    mp_hal_pin_low(self->pin_cs);
    lcd_delay();
    HAL_SPI_Transmit(self->spi->spi, (uint8_t *)data, length, 1000);
    lcd_delay();
    mp_hal_pin_high(self->pin_cs);
}

STATIC void lcd_spibus_send_cmd(lcd_spibus_obj_t *self, uint8_t cmd) {
    mp_hal_pin_low(self->pin_dc);
    lcd_delay();
    lcd_spibus_send(self, &cmd, 1);
}

STATIC void lcd_spibus_send_data(lcd_spibus_obj_t *self, const void *data, uint32_t length) {
    mp_hal_pin_high(self->pin_dc);
    lcd_delay();
    lcd_spibus_send(self, data, length);
}

// Initialize ILI9341
STATIC void ili9341_init(void) {
    uint16_t cmd = 0;
    while (ili9341_init_cmds[cmd].databytes != 0xFF) {
        lcd_spibus_send_cmd(p_lcd, ili9341_init_cmds[cmd].cmd);
        lcd_spibus_send_data(p_lcd, ili9341_init_cmds[cmd].data, ili9341_init_cmds[cmd].databytes & 0x1F);
        if (ili9341_init_cmds[cmd].databytes & 0x80) {
            mp_hal_delay_ms(100);
        }
        cmd++;
    }
}

// Set LCD direction
STATIC void ili9341_set_dir(uint8_t dir) {
    uint8_t dir_data = 0;
    switch (dir) {
        case 2:
            dir_data = 0x28;
            lcd_width = 320;
            lcd_height = 240;
            break;
        case 3:
            dir_data = 0x88;
            lcd_width = 240;
            lcd_height = 320;
            break;
        case 4:
            dir_data = 0xE8;
            lcd_width = 320;
            lcd_height = 240;
            break;
        default:
            dir_data = 0x48;
            lcd_width = 240;
            lcd_height = 320;
            break;
    }

    uint8_t data[4];
    lcd_spibus_send_cmd(p_lcd, 0x2A);
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = (lcd_width - 1) >> 8;
    data[3] = (lcd_width - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x2B);
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = (lcd_height - 1) >> 8;
    data[3] = (lcd_height - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x36);
    data[0] = dir_data;
    lcd_spibus_send_data(p_lcd, data, 1);
}

// Draw pixel
STATIC void ili9341_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
    uint8_t data[2];

    lcd_spibus_send_cmd(p_lcd, 0x2A);
    data[0] = (x >> 8);
    data[1] = (x & 0xFF);
    lcd_spibus_send_data(p_lcd, data, 2);

    lcd_spibus_send_cmd(p_lcd, 0x2B);
    data[0] = (y >> 8);
    data[1] = (y & 0xFF);
    lcd_spibus_send_data(p_lcd, data, 2);

    lcd_spibus_send_cmd(p_lcd, 0x2C);
    data[0] = (color >> 8);
    data[1] = (color & 0xFF);
    lcd_spibus_send_data(p_lcd, data, 2);
}

// Fill area
STATIC void ili9341_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color) {
    uint8_t data[4];
    uint32_t size = ((ex - sx)) * ((ey - sy));

    lcd_spibus_send_cmd(p_lcd, 0x2A);
    data[0] = (sx >> 8) & 0xFF;
    data[1] = sx & 0xFF;
    data[2] = ((ex - 1) >> 8) & 0xFF;
    data[3] = (ex - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x2B);
    data[0] = (sy >> 8) & 0xFF;
    data[1] = sy & 0xFF;
    data[2] = ((ey - 1) >> 8) & 0xFF;
    data[3] = (ey - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x2C);

    // Fill in chunks to avoid large memory allocation (153600 bytes for full screen!)
    #define CHUNK_SIZE 512  // pixels per chunk (1KB buffer)
    uint8_t color_buf[CHUNK_SIZE * 2];
    for (uint32_t i = 0; i < CHUNK_SIZE * 2; i += 2) {
        color_buf[i] = color >> 8;
        color_buf[i + 1] = color & 0xFF;
    }
    
    uint32_t remaining = size;
    while (remaining > 0) {
        uint32_t chunk = (remaining > CHUNK_SIZE) ? CHUNK_SIZE : remaining;
        lcd_spibus_send_data(p_lcd, color_buf, chunk * 2);
        remaining -= chunk;
    }
}

// MicroPython object definition
typedef struct _lcd24_obj_t {
    mp_obj_base_t base;
} lcd24_obj_t;

STATIC uint16_t color_from_tuple(mp_obj_t color_obj) {
    size_t len;
    mp_obj_t *items;
    mp_obj_get_array(color_obj, &len, &items);
    if (len != 3) {
        mp_raise_ValueError(MP_ERROR_TEXT("color must be (r,g,b)"));
    }
    uint8_t r = mp_obj_get_int(items[0]);
    uint8_t g = mp_obj_get_int(items[1]);
    uint8_t b = mp_obj_get_int(items[2]);
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// fill((r,g,b))
STATIC mp_obj_t lcd24_fill(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_fillcolor, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    if (args[0].u_obj != MP_OBJ_NULL) {
        uint16_t color = color_from_tuple(args[0].u_obj);
        ili9341_Fill(0, 0, lcd_width, lcd_height, color);
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_fill_obj, 1, lcd24_fill);

// drawPixel(x, y, (r,g,b))
STATIC mp_obj_t lcd24_drawPixel(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_x, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_color, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    if (args[2].u_obj != MP_OBJ_NULL) {
        uint16_t color = color_from_tuple(args[2].u_obj);
        ili9341_DrawPoint(args[0].u_int, args[1].u_int, color);
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_drawPixel_obj, 1, lcd24_drawPixel);

// drawLine(x0, y0, x1, y1, (r,g,b))
STATIC mp_obj_t lcd24_drawLine(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_x0, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y0, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_x1, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y1, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_color, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    if (args[4].u_obj != MP_OBJ_NULL) {
        uint16_t color = color_from_tuple(args[4].u_obj);
        int16_t x0 = args[0].u_int, y0 = args[1].u_int;
        int16_t x1 = args[2].u_int, y1 = args[3].u_int;
        
        int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int16_t dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int16_t err = (dx > dy ? dx : -dy) / 2;

        while (1) {
            ili9341_DrawPoint(x0, y0, color);
            if (x0 == x1 && y0 == y1) break;
            int16_t e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_drawLine_obj, 1, lcd24_drawLine);

// drawRect(x, y, width, height, color=(r,g,b), border=1, fillcolor=(r,g,b))
STATIC mp_obj_t lcd24_drawRect(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_x, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_width, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_height, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_color, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_border, MP_ARG_INT, {.u_int = 1} },
        { MP_QSTR_fillcolor, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    uint16_t x = args[0].u_int, y = args[1].u_int;
    uint16_t w = args[2].u_int, h = args[3].u_int;
    uint16_t border = args[5].u_int;

    if (args[6].u_obj != MP_OBJ_NULL) {
        uint16_t fill_color = color_from_tuple(args[6].u_obj);
        ili9341_Fill(x + border, y + border, x + w - border, y + h - border, fill_color);
    }

    if (args[4].u_obj != MP_OBJ_NULL) {
        uint16_t border_color = color_from_tuple(args[4].u_obj);
        for (uint16_t i = 0; i < border; i++) {
            for (uint16_t j = 0; j < w; j++) {
                ili9341_DrawPoint(x + j, y + i, border_color);
                ili9341_DrawPoint(x + j, y + h - 1 - i, border_color);
            }
            for (uint16_t j = 0; j < h; j++) {
                ili9341_DrawPoint(x + i, y + j, border_color);
                ili9341_DrawPoint(x + w - 1 - i, y + j, border_color);
            }
        }
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_drawRect_obj, 1, lcd24_drawRect);

// drawCircle(x, y, radius, color=(r,g,b), border=1, fillcolor=(r,g,b))
STATIC mp_obj_t lcd24_drawCircle(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_x, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_radius, MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_color, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_border, MP_ARG_INT, {.u_int = 1} },
        { MP_QSTR_fillcolor, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    int16_t cx = args[0].u_int, cy = args[1].u_int, r = args[2].u_int;

    if (args[5].u_obj != MP_OBJ_NULL) {
        uint16_t fill_color = color_from_tuple(args[5].u_obj);
        for (int16_t i = 0; i < args[4].u_int; i++) {
            int16_t ri = r - i;
            for (int16_t dy = -ri; dy <= ri; dy++) {
                int16_t dx = (int16_t)sqrtf(ri * ri - dy * dy);
                for (int16_t x = cx - dx; x <= cx + dx; x++) {
                    ili9341_DrawPoint(x, cy + dy, fill_color);
                }
            }
        }
    }

    if (args[3].u_obj != MP_OBJ_NULL) {
        uint16_t border_color = color_from_tuple(args[3].u_obj);
        int16_t x = r, y = 0, err = 0;
        while (x >= y) {
            for (uint16_t b = 0; b < args[4].u_int; b++) {
                ili9341_DrawPoint(cx + x - b, cy + y, border_color);
                ili9341_DrawPoint(cx + y, cy + x - b, border_color);
                ili9341_DrawPoint(cx - y, cy + x - b, border_color);
                ili9341_DrawPoint(cx - x + b, cy + y, border_color);
                ili9341_DrawPoint(cx - x + b, cy - y, border_color);
                ili9341_DrawPoint(cx - y, cy - x + b, border_color);
                ili9341_DrawPoint(cx + y, cy - x + b, border_color);
                ili9341_DrawPoint(cx + x - b, cy - y, border_color);
            }
            if (err <= 0) {
                y += 1;
                err += 2 * y + 1;
            }
            if (err > 0) {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_drawCircle_obj, 1, lcd24_drawCircle);

// 01Studio字符绘制函数
#define BUF_LEN 1160
STATIC uint16_t str_buf[BUF_LEN] = {0}; // 字体缓冲区

STATIC void grap_drawChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t color, uint16_t backcolor) {
    uint8_t temp, t1, t;
    uint16_t y0 = 0, x0 = 0;
    uint16_t str_h, str_w;
    uint16_t csize = ((size >> 3) + ((size % 8) ? 1 : 0)) * (size >> 1);
    num = num - ' ';

    str_h = size;
    str_w = size >> 1;

    for (t = 0; t < csize; t++) {
        if (size == 24)
            temp = asc2_2412[num][t];
        else if (size == 32)
            temp = asc2_3216[num][t];
        else if (size == 48)
            temp = asc2_4824[num][t];
        else
            temp = asc2_1608[num][t];

        for (t1 = 0; t1 < 8; t1++) {
            if (temp & 0x80) {
                str_buf[y0 * str_w + x0] = color;
            } else {
                str_buf[y0 * str_w + x0] = backcolor;
            }
            y0++;
            if (y0 >= size) {
                y0 = 0;
                x0++;
            }
            temp <<= 1;
        }
    }
    
    // Flush buffer to screen
    uint8_t data[4];
    lcd_spibus_send_cmd(p_lcd, 0x2A);
    data[0] = (x >> 8) & 0xFF;
    data[1] = x & 0xFF;
    data[2] = ((x + str_w - 1) >> 8) & 0xFF;
    data[3] = (x + str_w - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x2B);
    data[0] = (y >> 8) & 0xFF;
    data[1] = y & 0xFF;
    data[2] = ((y + str_h - 1) >> 8) & 0xFF;
    data[3] = (y + str_h - 1) & 0xFF;
    lcd_spibus_send_data(p_lcd, data, 4);

    lcd_spibus_send_cmd(p_lcd, 0x2C);
    
    // Convert uint16_t buffer to uint8_t with proper byte order for RGB565
    uint8_t send_buf[BUF_LEN * 2];
    for (uint16_t i = 0; i < str_w * str_h; i++) {
        send_buf[i * 2] = str_buf[i] >> 8;
        send_buf[i * 2 + 1] = str_buf[i] & 0xFF;
    }
    lcd_spibus_send_data(p_lcd, send_buf, str_w * str_h * 2);
}

STATIC void grap_drawStr(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                         uint8_t size, const char *p, uint16_t color, uint16_t backcolor) {
    uint8_t x0 = x;
    width += x;
    height += y;
    while ((*p <= '~') && (*p >= ' ')) {
        if (x >= width) {
            x = x0;
            y += size;
        }
        if (y >= height) break;

        grap_drawChar(x, y, *p, size, color, backcolor);
        x += (size >> 1);
        p++;
    }
}

// printStr(text, x, y, color=(r,g,b), backcolor=(r,g,b), size=2)
STATIC mp_obj_t lcd24_printStr(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_text, MP_ARG_REQUIRED | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_x, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_y, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_color, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_backcolor, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_size, MP_ARG_INT, {.u_int = 2} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    const char *text = mp_obj_str_get_str(args[0].u_obj);
    uint16_t x = args[1].u_int, y = args[2].u_int;
    uint16_t text_size = args[5].u_int;
    uint16_t color = args[3].u_obj != MP_OBJ_NULL ? color_from_tuple(args[3].u_obj) : 0xFFFF;
    uint16_t bg_color = args[4].u_obj != MP_OBJ_NULL ? color_from_tuple(args[4].u_obj) : 0x0000;

    // size mapping: 1->16, 2->24, 3->32, 4->48
    if (text_size == 1) text_size = 16;
    else if (text_size == 2) text_size = 24;
    else if (text_size == 3) text_size = 32;
    else if (text_size == 4) text_size = 48;
    else text_size = 16;

    grap_drawStr(x, y, text_size * strlen(text), text_size, text_size, text, color, bg_color);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(lcd24_printStr_obj, 1, lcd24_printStr);

// Class methods
STATIC const mp_rom_map_elem_t lcd24_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_fill), MP_ROM_PTR(&lcd24_fill_obj) },
    { MP_ROM_QSTR(MP_QSTR_drawPixel), MP_ROM_PTR(&lcd24_drawPixel_obj) },
    { MP_ROM_QSTR(MP_QSTR_drawLine), MP_ROM_PTR(&lcd24_drawLine_obj) },
    { MP_ROM_QSTR(MP_QSTR_drawRect), MP_ROM_PTR(&lcd24_drawRect_obj) },
    { MP_ROM_QSTR(MP_QSTR_drawCircle), MP_ROM_PTR(&lcd24_drawCircle_obj) },
    { MP_ROM_QSTR(MP_QSTR_printStr), MP_ROM_PTR(&lcd24_printStr_obj) },
};
STATIC MP_DEFINE_CONST_DICT(lcd24_locals_dict, lcd24_locals_dict_table);

// Constructor
STATIC mp_obj_t lcd24_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum { ARG_portrait };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_portrait, MP_ARG_INT, {.u_int = 1} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // Initialize SPI bus
    spi_init0();
    const spi_t *spi = &spi_obj[MICROPY_HW_LCD_SPI_ID - 1];
    spi_set_params(spi, 0xffffffff, 16000000, 0, 0, 8, MICROPY_PY_MACHINE_SPI_MSB);
    spi_init(spi, true);

    // Initialize LCD object
    p_lcd = m_new_obj(lcd_spibus_obj_t);
    p_lcd->base.type = type;
    p_lcd->spi = spi;
    p_lcd->pin_dc = LCD_PIN_DC;
    p_lcd->pin_rst = LCD_PIN_RST;
    p_lcd->pin_cs = LCD_PIN_CS;

    // Configure GPIO
    mp_hal_gpio_clock_enable(p_lcd->pin_dc->gpio);
    mp_hal_pin_output(p_lcd->pin_dc);
    mp_hal_pin_high(p_lcd->pin_dc);

    mp_hal_gpio_clock_enable(p_lcd->pin_rst->gpio);
    mp_hal_pin_output(p_lcd->pin_rst);
    mp_hal_pin_high(p_lcd->pin_rst);

    mp_hal_gpio_clock_enable(p_lcd->pin_cs->gpio);
    mp_hal_pin_output(p_lcd->pin_cs);
    mp_hal_pin_high(p_lcd->pin_cs);

    // Reset LCD
    mp_hal_pin_low(p_lcd->pin_rst);
    mp_hal_delay_ms(100);
    mp_hal_pin_high(p_lcd->pin_rst);
    mp_hal_delay_ms(100);

    // Initialize ILI9341
    ili9341_init();
    ili9341_set_dir(args[ARG_portrait].u_int);
    ili9341_Fill(0, 0, lcd_width, lcd_height, 0x0000);

    lcd24_obj_t *self = m_new_obj(lcd24_obj_t);
    self->base.type = type;
    return MP_OBJ_FROM_PTR(self);
}

MP_DEFINE_CONST_OBJ_TYPE(
    mp_type_lcd24,
    MP_QSTR_LCD24,
    MP_TYPE_FLAG_NONE,
    make_new, lcd24_make_new,
    locals_dict, &lcd24_locals_dict
);

STATIC const mp_rom_map_elem_t tftlcd_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_tftlcd) },
    { MP_ROM_QSTR(MP_QSTR_LCD24), MP_ROM_PTR(&mp_type_lcd24) },
};
STATIC MP_DEFINE_CONST_DICT(tftlcd_module_globals, tftlcd_module_globals_table);

const mp_obj_module_t mp_module_tftlcd = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&tftlcd_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tftlcd, mp_module_tftlcd);

#endif // MICROPY_ENABLE_TFTLCD && MICROPY_ENABLE_SPILCD
