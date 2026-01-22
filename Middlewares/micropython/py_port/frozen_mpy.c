#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"
#include "py/nativeglue.h"

#if MICROPY_LONGINT_IMPL != 2
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MPZ_DIG_SIZE != 16
#error "incompatible MPZ_DIG_SIZE"
#endif

#if MICROPY_PY_BUILTINS_FLOAT
typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;
#endif

#if MICROPY_PY_BUILTINS_COMPLEX
typedef struct _mp_obj_complex_t {
    mp_obj_base_t base;
    mp_float_t real;
    mp_float_t imag;
} mp_obj_complex_t;
#endif

enum {
    MP_QSTR_GzipFile = MP_QSTRnumber_of,
    MP_QSTR_LANDSCAPE_UPSIDEDOWN,
    MP_QSTR_LockType,
    MP_QSTR_PORTRAIT_UPSIDEDOWN,
    MP_QSTR_SSLError,
    MP_QSTR_STARTUP_DECO_INFO,
    MP_QSTR_STARTUP_DECO_MLOGO,
    MP_QSTR_STARTUP_DECO_NONE,
    MP_QSTR_X,
    MP_QSTR_XY,
    MP_QSTR_Y,
    MP_QSTR_YX,
    MP_QSTR__decode_wbits,
    MP_QSTR__locked,
    MP_QSTR__recv_cmd,
    MP_QSTR__send_cmd,
    MP_QSTR__thread_dot_py,
    MP_QSTR__tls,
    MP_QSTR_acquire,
    MP_QSTR_allocate_lock,
    MP_QSTR_b,
    MP_QSTR_bg,
    MP_QSTR_bold,
    MP_QSTR_c,
    MP_QSTR_calib,
    MP_QSTR_cmd,
    MP_QSTR_color,
    MP_QSTR_compress,
    MP_QSTR_create_default_context,
    MP_QSTR_decompress,
    MP_QSTR_dot_no_clip,
    MP_QSTR_exc,
    MP_QSTR_exc_type,
    MP_QSTR_fast_spi,
    MP_QSTR_feed_wdt,
    MP_QSTR_fg,
    MP_QSTR_filename,
    MP_QSTR_fileobj,
    MP_QSTR_font,
    MP_QSTR_g,
    MP_QSTR_get_ident,
    MP_QSTR_get_line,
    MP_QSTR_get_pixel,
    MP_QSTR_gzip_dot_py,
    MP_QSTR_h,
    MP_QSTR_i2c,
    MP_QSTR_i2c_addr,
    MP_QSTR_jpeg,
    MP_QSTR_jpeg_data,
    MP_QSTR_jpeg_start,
    MP_QSTR_lcd160cr_dot_py,
    MP_QSTR_line_no_clip,
    MP_QSTR_locked,
    MP_QSTR_n_data,
    MP_QSTR_orient,
    MP_QSTR_pat,
    MP_QSTR_pwr,
    MP_QSTR_rect_interior,
    MP_QSTR_rect_interior_no_clip,
    MP_QSTR_rect_no_clip,
    MP_QSTR_rect_outline,
    MP_QSTR_rect_outline_no_clip,
    MP_QSTR_release,
    MP_QSTR_release_space_unlocked_space_lock,
    MP_QSTR_s,
    MP_QSTR_save,
    MP_QSTR_save_to_flash,
    MP_QSTR_scale,
    MP_QSTR_screen_dump,
    MP_QSTR_screen_load,
    MP_QSTR_set_i2c_addr,
    MP_QSTR_set_pixel,
    MP_QSTR_set_scroll,
    MP_QSTR_set_scroll_buf,
    MP_QSTR_set_scroll_win,
    MP_QSTR_set_spi_win,
    MP_QSTR_set_startup_deco,
    MP_QSTR_set_uart_baudrate,
    MP_QSTR_show_framebuf,
    MP_QSTR_sock,
    MP_QSTR_spi,
    MP_QSTR_ssl_dot_py,
    MP_QSTR_ssl_context,
    MP_QSTR_stack_size,
    MP_QSTR_start_new_thread,
    MP_QSTR_tb,
    MP_QSTR_total_len,
    MP_QSTR_touch_config,
    MP_QSTR_trans,
    MP_QSTR_unknown_space_connect_space_value,
    MP_QSTR_vec,
    MP_QSTR_w,
    MP_QSTR_waitflag,
    MP_QSTR_wbits,
    MP_QSTR_win,
    MP_QSTR_x,
    MP_QSTR_x1,
    MP_QSTR_x2,
    MP_QSTR_y,
    MP_QSTR_y1,
    MP_QSTR_y2,
    MP_QSTR_zlib_dot_py,
};

const qstr_hash_t mp_qstr_frozen_const_hashes[] = {
    48391,
    16597,
    8246,
    46337,
    27025,
    4291,
    1067,
    44967,
    46589,
    30148,
    46588,
    29988,
    34514,
    15344,
    25261,
    31347,
    42611,
    3025,
    54045,
    60908,
    46535,
    28352,
    15424,
    46534,
    60864,
    19503,
    1752,
    31395,
    1333,
    64354,
    30189,
    9435,
    52220,
    15088,
    26431,
    28228,
    21732,
    19460,
    11158,
    46530,
    45566,
    10370,
    6052,
    56646,
    46541,
    24413,
    7953,
    59261,
    4178,
    59938,
    42447,
    20060,
    47631,
    56164,
    33166,
    29408,
    28720,
    5322,
    32413,
    29554,
    7386,
    2701,
    36844,
    51606,
    46550,
    33700,
    16143,
    20861,
    23962,
    59920,
    59276,
    55984,
    45621,
    6683,
    26586,
    6301,
    48783,
    55749,
    25973,
    40913,
    36303,
    48942,
    36681,
    15153,
    9687,
    28563,
    41279,
    39189,
    17759,
    1144,
    31605,
    46546,
    2338,
    27294,
    32693,
    46557,
    29004,
    29007,
    46556,
    29037,
    29038,
    20191,
};

const qstr_len_t mp_qstr_frozen_const_lengths[] = {
    8,
    20,
    8,
    19,
    8,
    17,
    18,
    17,
    1,
    2,
    1,
    2,
    13,
    7,
    9,
    9,
    10,
    4,
    7,
    13,
    1,
    2,
    4,
    1,
    5,
    3,
    5,
    8,
    22,
    10,
    11,
    3,
    8,
    8,
    8,
    2,
    8,
    7,
    4,
    1,
    9,
    8,
    9,
    7,
    1,
    3,
    8,
    4,
    9,
    10,
    11,
    12,
    6,
    6,
    6,
    3,
    3,
    13,
    21,
    12,
    12,
    20,
    7,
    21,
    1,
    4,
    13,
    5,
    11,
    11,
    12,
    9,
    10,
    14,
    14,
    11,
    16,
    17,
    13,
    4,
    3,
    6,
    11,
    10,
    16,
    2,
    9,
    12,
    5,
    21,
    3,
    1,
    8,
    5,
    3,
    1,
    2,
    2,
    1,
    2,
    2,
    7,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    &mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    true, // is_sorted
    10, // allocated entries
    102, // used entries
    (qstr_hash_t *)mp_qstr_frozen_const_hashes,
    (qstr_len_t *)mp_qstr_frozen_const_lengths,
    {
        "GzipFile",
        "LANDSCAPE_UPSIDEDOWN",
        "LockType",
        "PORTRAIT_UPSIDEDOWN",
        "SSLError",
        "STARTUP_DECO_INFO",
        "STARTUP_DECO_MLOGO",
        "STARTUP_DECO_NONE",
        "X",
        "XY",
        "Y",
        "YX",
        "_decode_wbits",
        "_locked",
        "_recv_cmd",
        "_send_cmd",
        "_thread.py",
        "_tls",
        "acquire",
        "allocate_lock",
        "b",
        "bg",
        "bold",
        "c",
        "calib",
        "cmd",
        "color",
        "compress",
        "create_default_context",
        "decompress",
        "dot_no_clip",
        "exc",
        "exc_type",
        "fast_spi",
        "feed_wdt",
        "fg",
        "filename",
        "fileobj",
        "font",
        "g",
        "get_ident",
        "get_line",
        "get_pixel",
        "gzip.py",
        "h",
        "i2c",
        "i2c_addr",
        "jpeg",
        "jpeg_data",
        "jpeg_start",
        "lcd160cr.py",
        "line_no_clip",
        "locked",
        "n_data",
        "orient",
        "pat",
        "pwr",
        "rect_interior",
        "rect_interior_no_clip",
        "rect_no_clip",
        "rect_outline",
        "rect_outline_no_clip",
        "release",
        "release unlocked lock",
        "s",
        "save",
        "save_to_flash",
        "scale",
        "screen_dump",
        "screen_load",
        "set_i2c_addr",
        "set_pixel",
        "set_scroll",
        "set_scroll_buf",
        "set_scroll_win",
        "set_spi_win",
        "set_startup_deco",
        "set_uart_baudrate",
        "show_framebuf",
        "sock",
        "spi",
        "ssl.py",
        "ssl_context",
        "stack_size",
        "start_new_thread",
        "tb",
        "total_len",
        "touch_config",
        "trans",
        "unknown connect value",
        "vec",
        "w",
        "waitflag",
        "wbits",
        "win",
        "x",
        "x1",
        "x2",
        "y",
        "y1",
        "y2",
        "zlib.py",
    },
};

////////////////////////////////////////////////////////////////////////////////
// frozen module zlib
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\zlib.mpy
// - frozen file name: zlib.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file zlib.py, scope zlib__lt_module_gt_
static const byte fun_data_zlib__lt_module_gt_[57] = {
    0x10,0x12, // prelude
    0x01, // names: <module>
    0x60,0x6c,0x40,0x84,0x12,0x4c,0x88,0x07, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'io'
    0x16,0x02, // STORE_NAME 'io'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'deflate'
    0x16,0x03, // STORE_NAME 'deflate'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x06, // STORE_NAME '_decode_wbits'
    0x11,0x11, // LOAD_NAME 'hasattr'
    0x11,0x03, // LOAD_NAME 'deflate'
    0x13,0x04, // LOAD_ATTR 'DeflateIO'
    0x10,0x05, // LOAD_CONST_STRING 'write'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x8f, // LOAD_CONST_SMALL_INT 15
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x0c, // STORE_NAME 'compress'
    0x8f, // LOAD_CONST_SMALL_INT 15
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x0f, // STORE_NAME 'decompress'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of zlib__lt_module_gt_
// frozen bytecode for file zlib.py, scope zlib__decode_wbits
static const byte fun_data_zlib__decode_wbits[143] = {
    0x22,0x22, // prelude
    0x06,0x0b,0x0f, // names: _decode_wbits, wbits, decompress
    0x80,0x09,0x2f,0x20,0x24,0x45,0x2f,0x2b,0x25,0x27,0x2f,0x2d,0x2f,0x4a, // code info
    0x71, // LOAD_CONST_SMALL_INT -15
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x04, // JUMP_IF_FALSE_OR_POP 4
    0x7b, // LOAD_CONST_SMALL_INT -5
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x13,0x07, // LOAD_ATTR 'RAW'
    0xb0, // LOAD_FAST 0
    0xd1, // UNARY_OP 1 __neg__
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0x85, // LOAD_CONST_SMALL_INT 5
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x04, // JUMP_IF_FALSE_OR_POP 4
    0x8f, // LOAD_CONST_SMALL_INT 15
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x13,0x08, // LOAD_ATTR 'ZLIB'
    0xb0, // LOAD_FAST 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb0, // LOAD_FAST 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x13,0x08, // LOAD_ATTR 'ZLIB'
    0x2a,0x01, // BUILD_TUPLE 1
    0x63, // RETURN_VALUE
    0x95, // LOAD_CONST_SMALL_INT 21
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x04, // JUMP_IF_FALSE_OR_POP 4
    0x9f, // LOAD_CONST_SMALL_INT 31
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x13,0x09, // LOAD_ATTR 'GZIP'
    0xb0, // LOAD_FAST 0
    0x90, // LOAD_CONST_SMALL_INT 16
    0xf3, // BINARY_OP 28 __sub__
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x44,0x59, // POP_JUMP_IF_FALSE 25
    0xa3, // LOAD_CONST_SMALL_INT 35
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x04, // JUMP_IF_FALSE_OR_POP 4
    0xaf, // LOAD_CONST_SMALL_INT 47
    0xda, // BINARY_OP 3 __le__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x13,0x0a, // LOAD_ATTR 'AUTO'
    0xb0, // LOAD_FAST 0
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xf3, // BINARY_OP 28 __sub__
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0x12,0x12, // LOAD_GLOBAL 'ValueError'
    0x10,0x0b, // LOAD_CONST_STRING 'wbits'
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_zlib__decode_wbits = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_zlib__decode_wbits,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 143,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_zlib__decode_wbits + 5,
        .line_info_top = fun_data_zlib__decode_wbits + 19,
        .opcodes = fun_data_zlib__decode_wbits + 19,
    },
    #endif
    #endif
};
#else
#define proto_fun_zlib__decode_wbits fun_data_zlib__decode_wbits[0]
#endif

// child of zlib__lt_module_gt_
// frozen bytecode for file zlib.py, scope zlib_compress
static const byte fun_data_zlib_compress[51] = {
    0xce,0x01,0x10, // prelude
    0x0c,0x13,0x0b, // names: compress, data, wbits
    0x80,0x1d,0x27,0x31,0x2a, // code info
    0x12,0x02, // LOAD_GLOBAL 'io'
    0x14,0x0d, // LOAD_METHOD 'BytesIO'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x14,0x04, // LOAD_METHOD 'DeflateIO'
    0xb2, // LOAD_FAST 2
    0x12,0x06, // LOAD_GLOBAL '_decode_wbits'
    0xb1, // LOAD_FAST 1
    0x50, // LOAD_CONST_FALSE
    0x34,0x02, // CALL_FUNCTION 2
    0x82, // LOAD_CONST_SMALL_INT 2
    0x37,0x02, // CALL_METHOD_VAR_KW 2
    0x47,0x09, // SETUP_WITH 9
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x05, // LOAD_METHOD 'write'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0xb2, // LOAD_FAST 2
    0x14,0x0e, // LOAD_METHOD 'getvalue'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_zlib_compress = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_zlib_compress,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 51,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_zlib_compress + 6,
        .line_info_top = fun_data_zlib_compress + 11,
        .opcodes = fun_data_zlib_compress + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_zlib_compress fun_data_zlib_compress[0]
#endif

// child of zlib__lt_module_gt_
// frozen bytecode for file zlib.py, scope zlib_decompress
static const byte fun_data_zlib_decompress[45] = {
    0xce,0x01,0x0e, // prelude
    0x0f,0x13,0x0b, // names: decompress, data, wbits
    0x80,0x24,0x28,0x31, // code info
    0x12,0x02, // LOAD_GLOBAL 'io'
    0x14,0x0d, // LOAD_METHOD 'BytesIO'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0x12,0x03, // LOAD_GLOBAL 'deflate'
    0x14,0x04, // LOAD_METHOD 'DeflateIO'
    0xb2, // LOAD_FAST 2
    0x12,0x06, // LOAD_GLOBAL '_decode_wbits'
    0xb1, // LOAD_FAST 1
    0x52, // LOAD_CONST_TRUE
    0x34,0x02, // CALL_FUNCTION 2
    0x82, // LOAD_CONST_SMALL_INT 2
    0x37,0x02, // CALL_METHOD_VAR_KW 2
    0x47,0x07, // SETUP_WITH 7
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x10, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_zlib_decompress = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_zlib_decompress,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 45,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_zlib_decompress + 6,
        .line_info_top = fun_data_zlib_decompress + 10,
        .opcodes = fun_data_zlib_decompress + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_zlib_decompress fun_data_zlib_decompress[0]
#endif

static const mp_raw_code_t *const children_zlib__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_zlib__decode_wbits,
    (const mp_raw_code_t *)&proto_fun_zlib_compress,
    (const mp_raw_code_t *)&proto_fun_zlib_decompress,
};

static const mp_raw_code_truncated_t proto_fun_zlib__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_zlib__lt_module_gt_,
    .children = (void *)&children_zlib__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 57,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_zlib__lt_module_gt_ + 3,
        .line_info_top = fun_data_zlib__lt_module_gt_ + 11,
        .opcodes = fun_data_zlib__lt_module_gt_ + 11,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_zlib[20] = {
    MP_QSTR_zlib_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_io,
    MP_QSTR_deflate,
    MP_QSTR_DeflateIO,
    MP_QSTR_write,
    MP_QSTR__decode_wbits,
    MP_QSTR_RAW,
    MP_QSTR_ZLIB,
    MP_QSTR_GZIP,
    MP_QSTR_AUTO,
    MP_QSTR_wbits,
    MP_QSTR_compress,
    MP_QSTR_BytesIO,
    MP_QSTR_getvalue,
    MP_QSTR_decompress,
    MP_QSTR_read,
    MP_QSTR_hasattr,
    MP_QSTR_ValueError,
    MP_QSTR_data,
};

static const mp_frozen_module_t frozen_module_zlib = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_zlib,
        .obj_table = NULL,
    },
    .proto_fun = &proto_fun_zlib__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module gzip
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\gzip.mpy
// - frozen file name: gzip.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file gzip.py, scope gzip__lt_module_gt_
static const byte fun_data_gzip__lt_module_gt_[66] = {
    0x10,0x16, // prelude
    0x01, // names: <module>
    0x60,0x40,0x72,0x64,0x20,0x69,0x20,0x4c,0x84,0x07, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'builtins'
    0x16,0x02, // STORE_NAME 'builtins'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'io'
    0x16,0x03, // STORE_NAME 'io'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x04, // IMPORT_NAME 'deflate'
    0x16,0x04, // STORE_NAME 'deflate'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x08, // STORE_NAME 'GzipFile'
    0x10,0x05, // LOAD_CONST_STRING 'rb'
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x0a, // STORE_NAME 'open'
    0x11,0x11, // LOAD_NAME 'hasattr'
    0x11,0x04, // LOAD_NAME 'deflate'
    0x13,0x06, // LOAD_ATTR 'DeflateIO'
    0x10,0x07, // LOAD_CONST_STRING 'write'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0b, // STORE_NAME 'compress'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0f, // STORE_NAME 'decompress'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of gzip__lt_module_gt_
// frozen bytecode for file gzip.py, scope gzip_GzipFile
static const byte fun_data_gzip_GzipFile[19] = {
    0x29,0x08, // prelude
    0x08,0x0d, // names: GzipFile, fileobj
    0x80,0x09, // code info
    0x12,0x04, // LOAD_GLOBAL 'deflate'
    0x14,0x06, // LOAD_METHOD 'DeflateIO'
    0xb0, // LOAD_FAST 0
    0x12,0x04, // LOAD_GLOBAL 'deflate'
    0x13,0x09, // LOAD_ATTR 'GZIP'
    0x8f, // LOAD_CONST_SMALL_INT 15
    0x36,0x03, // CALL_METHOD 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_gzip_GzipFile = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_gzip_GzipFile,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data_gzip_GzipFile + 4,
        .line_info_top = fun_data_gzip_GzipFile + 6,
        .opcodes = fun_data_gzip_GzipFile + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_gzip_GzipFile fun_data_gzip_GzipFile[0]
#endif

// child of gzip__lt_module_gt_
// frozen bytecode for file gzip.py, scope gzip_open
static const byte fun_data_gzip_open[29] = {
    0xba,0x01,0x0a, // prelude
    0x0a,0x12,0x13, // names: open, filename, mode
    0x80,0x0d, // code info
    0x12,0x04, // LOAD_GLOBAL 'deflate'
    0x14,0x06, // LOAD_METHOD 'DeflateIO'
    0x12,0x02, // LOAD_GLOBAL 'builtins'
    0x14,0x0a, // LOAD_METHOD 'open'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x12,0x04, // LOAD_GLOBAL 'deflate'
    0x13,0x09, // LOAD_ATTR 'GZIP'
    0x8f, // LOAD_CONST_SMALL_INT 15
    0x52, // LOAD_CONST_TRUE
    0x36,0x04, // CALL_METHOD 4
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_gzip_open = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_gzip_open,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 29,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_gzip_open + 6,
        .line_info_top = fun_data_gzip_open + 8,
        .opcodes = fun_data_gzip_open + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_gzip_open fun_data_gzip_open[0]
#endif

// child of gzip__lt_module_gt_
// frozen bytecode for file gzip.py, scope gzip_compress
static const byte fun_data_gzip_compress[43] = {
    0x3d,0x0e, // prelude
    0x0b,0x14, // names: compress, data
    0x80,0x13,0x27,0x2b,0x2a, // code info
    0x12,0x03, // LOAD_GLOBAL 'io'
    0x14,0x0c, // LOAD_METHOD 'BytesIO'
    0x36,0x00, // CALL_METHOD 0
    0xc1, // STORE_FAST 1
    0x12,0x08, // LOAD_GLOBAL 'GzipFile'
    0x10,0x0d, // LOAD_CONST_STRING 'fileobj'
    0xb1, // LOAD_FAST 1
    0x34,0x82,0x00, // CALL_FUNCTION 256
    0x47,0x09, // SETUP_WITH 9
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x07, // LOAD_METHOD 'write'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0xb1, // LOAD_FAST 1
    0x14,0x0e, // LOAD_METHOD 'getvalue'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_gzip_compress = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_gzip_compress,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 43,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 11,
        .line_info = fun_data_gzip_compress + 4,
        .line_info_top = fun_data_gzip_compress + 9,
        .opcodes = fun_data_gzip_compress + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_gzip_compress fun_data_gzip_compress[0]
#endif

// child of gzip__lt_module_gt_
// frozen bytecode for file gzip.py, scope gzip_decompress
static const byte fun_data_gzip_decompress[37] = {
    0x3d,0x0c, // prelude
    0x0f,0x14, // names: decompress, data
    0x80,0x1a,0x28,0x2b, // code info
    0x12,0x03, // LOAD_GLOBAL 'io'
    0x14,0x0c, // LOAD_METHOD 'BytesIO'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0x12,0x08, // LOAD_GLOBAL 'GzipFile'
    0x10,0x0d, // LOAD_CONST_STRING 'fileobj'
    0xb1, // LOAD_FAST 1
    0x34,0x82,0x00, // CALL_FUNCTION 256
    0x47,0x07, // SETUP_WITH 7
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x10, // LOAD_METHOD 'read'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_gzip_decompress = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_gzip_decompress,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_gzip_decompress + 4,
        .line_info_top = fun_data_gzip_decompress + 8,
        .opcodes = fun_data_gzip_decompress + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_gzip_decompress fun_data_gzip_decompress[0]
#endif

static const mp_raw_code_t *const children_gzip__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_gzip_GzipFile,
    (const mp_raw_code_t *)&proto_fun_gzip_open,
    (const mp_raw_code_t *)&proto_fun_gzip_compress,
    (const mp_raw_code_t *)&proto_fun_gzip_decompress,
};

static const mp_raw_code_truncated_t proto_fun_gzip__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_gzip__lt_module_gt_,
    .children = (void *)&children_gzip__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 66,
    .n_children = 4,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_gzip__lt_module_gt_ + 3,
        .line_info_top = fun_data_gzip__lt_module_gt_ + 13,
        .opcodes = fun_data_gzip__lt_module_gt_ + 13,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_gzip[21] = {
    MP_QSTR_gzip_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_builtins,
    MP_QSTR_io,
    MP_QSTR_deflate,
    MP_QSTR_rb,
    MP_QSTR_DeflateIO,
    MP_QSTR_write,
    MP_QSTR_GzipFile,
    MP_QSTR_GZIP,
    MP_QSTR_open,
    MP_QSTR_compress,
    MP_QSTR_BytesIO,
    MP_QSTR_fileobj,
    MP_QSTR_getvalue,
    MP_QSTR_decompress,
    MP_QSTR_read,
    MP_QSTR_hasattr,
    MP_QSTR_filename,
    MP_QSTR_mode,
    MP_QSTR_data,
};

static const mp_frozen_module_t frozen_module_gzip = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_gzip,
        .obj_table = NULL,
    },
    .proto_fun = &proto_fun_gzip__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module _thread
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\_thread.mpy
// - frozen file name: _thread.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file _thread.py, scope _thread__lt_module_gt_
static const byte fun_data__thread__lt_module_gt_[46] = {
    0x10,0x1a, // prelude
    0x01, // names: <module>
    0x80,0x09,0x89,0x1e,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x40, // code info
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x02, // LOAD_CONST_STRING 'LockType'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x02, // STORE_NAME 'LockType'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x03, // STORE_NAME 'allocate_lock'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x04, // STORE_NAME 'start_new_thread'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x05, // STORE_NAME 'get_ident'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x06, // STORE_NAME 'stack_size'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x07, // STORE_NAME 'exit'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_LockType
static const byte fun_data__thread_LockType[51] = {
    0x08,0x16, // prelude
    0x02, // names: LockType
    0x88,0x0a,0x64,0x64,0x88,0x09,0x64,0x40,0x64,0x20, // code info
    0x11,0x0f, // LOAD_NAME '__name__'
    0x16,0x10, // STORE_NAME '__module__'
    0x10,0x02, // LOAD_CONST_STRING 'LockType'
    0x16,0x11, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x08, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0a, // STORE_NAME 'locked'
    0x52, // LOAD_CONST_TRUE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x0b, // STORE_NAME 'acquire'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0c, // STORE_NAME 'release'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x0d, // STORE_NAME '__enter__'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x0e, // STORE_NAME '__exit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType___init__
static const byte fun_data__thread_LockType___init__[12] = {
    0x11,0x08, // prelude
    0x08,0x14, // names: __init__, self
    0x80,0x0b, // code info
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR '_locked'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 12,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 8,
        .line_info = fun_data__thread_LockType___init__ + 4,
        .line_info_top = fun_data__thread_LockType___init__ + 6,
        .opcodes = fun_data__thread_LockType___init__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType___init__ fun_data__thread_LockType___init__[0]
#endif

// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType_locked
static const byte fun_data__thread_LockType_locked[10] = {
    0x09,0x08, // prelude
    0x0a,0x14, // names: locked, self
    0x80,0x0e, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '_locked'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType_locked = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType_locked,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data__thread_LockType_locked + 4,
        .line_info_top = fun_data__thread_LockType_locked + 6,
        .opcodes = fun_data__thread_LockType_locked + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType_locked fun_data__thread_LockType_locked[0]
#endif

// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType_acquire
static const byte fun_data__thread_LockType_acquire[32] = {
    0x9a,0x01,0x14, // prelude
    0x0b,0x14,0x15, // names: acquire, self, waitflag
    0x80,0x12,0x25,0x23,0x23,0x22,0x24, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '_locked'
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb1, // LOAD_FAST 1
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x12,0x12, // LOAD_GLOBAL 'NotImplementedError'
    0x65, // RAISE_OBJ
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR '_locked'
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType_acquire = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType_acquire,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 11,
        .line_info = fun_data__thread_LockType_acquire + 6,
        .line_info_top = fun_data__thread_LockType_acquire + 13,
        .opcodes = fun_data__thread_LockType_acquire + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType_acquire fun_data__thread_LockType_acquire[0]
#endif

// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType_release
static const byte fun_data__thread_LockType_release[26] = {
    0x11,0x0c, // prelude
    0x0c,0x14, // names: release, self
    0x80,0x1a,0x25,0x27, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '_locked'
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x16, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR '_locked'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType_release = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType_release,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data__thread_LockType_release + 4,
        .line_info_top = fun_data__thread_LockType_release + 8,
        .opcodes = fun_data__thread_LockType_release + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType_release fun_data__thread_LockType_release[0]
#endif

// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType___enter__
static const byte fun_data__thread_LockType___enter__[16] = {
    0x19,0x0a, // prelude
    0x0d,0x14, // names: __enter__, self
    0x80,0x1f,0x27, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0b, // LOAD_METHOD 'acquire'
    0x52, // LOAD_CONST_TRUE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType___enter__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType___enter__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data__thread_LockType___enter__ + 4,
        .line_info_top = fun_data__thread_LockType___enter__ + 7,
        .opcodes = fun_data__thread_LockType___enter__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType___enter__ fun_data__thread_LockType___enter__[0]
#endif

// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType___exit__
static const byte fun_data__thread_LockType___exit__[19] = {
    0xa8,0x04,0x10, // prelude
    0x0e,0x14,0x17,0x18,0x19, // names: __exit__, self, exc_type, exc, tb
    0x80,0x23,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0c, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_LockType___exit__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType___exit__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 19,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data__thread_LockType___exit__ + 8,
        .line_info_top = fun_data__thread_LockType___exit__ + 11,
        .opcodes = fun_data__thread_LockType___exit__ + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_LockType___exit__ fun_data__thread_LockType___exit__[0]
#endif

static const mp_raw_code_t *const children__thread_LockType[] = {
    (const mp_raw_code_t *)&proto_fun__thread_LockType___init__,
    (const mp_raw_code_t *)&proto_fun__thread_LockType_locked,
    (const mp_raw_code_t *)&proto_fun__thread_LockType_acquire,
    (const mp_raw_code_t *)&proto_fun__thread_LockType_release,
    (const mp_raw_code_t *)&proto_fun__thread_LockType___enter__,
    (const mp_raw_code_t *)&proto_fun__thread_LockType___exit__,
};

static const mp_raw_code_truncated_t proto_fun__thread_LockType = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_LockType,
    .children = (void *)&children__thread_LockType,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 51,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 2,
        .line_info = fun_data__thread_LockType + 3,
        .line_info_top = fun_data__thread_LockType + 13,
        .opcodes = fun_data__thread_LockType + 13,
    },
    #endif
    #endif
};

// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_allocate_lock
static const byte fun_data__thread_allocate_lock[10] = {
    0x00,0x06, // prelude
    0x03, // names: allocate_lock
    0x80,0x28, // code info
    0x12,0x02, // LOAD_GLOBAL 'LockType'
    0x34,0x00, // CALL_FUNCTION 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_allocate_lock = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_allocate_lock,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 3,
        .line_info = fun_data__thread_allocate_lock + 3,
        .line_info_top = fun_data__thread_allocate_lock + 5,
        .opcodes = fun_data__thread_allocate_lock + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_allocate_lock fun_data__thread_allocate_lock[0]
#endif

// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_start_new_thread
static const byte fun_data__thread_start_new_thread[11] = {
    0x90,0x80,0xc0,0x40,0x06, // prelude
    0x04, // names: start_new_thread
    0x80,0x2c, // code info
    0x12,0x12, // LOAD_GLOBAL 'NotImplementedError'
    0x65, // RAISE_OBJ
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_start_new_thread = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_start_new_thread,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 11,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 6,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 4,
        .line_info = fun_data__thread_start_new_thread + 6,
        .line_info_top = fun_data__thread_start_new_thread + 8,
        .opcodes = fun_data__thread_start_new_thread + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_start_new_thread fun_data__thread_start_new_thread[0]
#endif

// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_get_ident
static const byte fun_data__thread_get_ident[7] = {
    0x00,0x06, // prelude
    0x05, // names: get_ident
    0x80,0x30, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_get_ident = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_get_ident,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 7,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 5,
        .line_info = fun_data__thread_get_ident + 3,
        .line_info_top = fun_data__thread_get_ident + 5,
        .opcodes = fun_data__thread_get_ident + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_get_ident fun_data__thread_get_ident[0]
#endif

// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_stack_size
static const byte fun_data__thread_stack_size[10] = {
    0x90,0x80,0xc0,0x40,0x06, // prelude
    0x06, // names: stack_size
    0x80,0x35, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_stack_size = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_stack_size,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 10,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 6,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data__thread_stack_size + 6,
        .line_info_top = fun_data__thread_stack_size + 8,
        .opcodes = fun_data__thread_stack_size + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_stack_size fun_data__thread_stack_size[0]
#endif

// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_exit
static const byte fun_data__thread_exit[8] = {
    0x00,0x06, // prelude
    0x07, // names: exit
    0x80,0x39, // code info
    0x12,0x13, // LOAD_GLOBAL 'SystemExit'
    0x65, // RAISE_OBJ
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__thread_exit = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread_exit,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 8,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 7,
        .line_info = fun_data__thread_exit + 3,
        .line_info_top = fun_data__thread_exit + 5,
        .opcodes = fun_data__thread_exit + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun__thread_exit fun_data__thread_exit[0]
#endif

static const mp_raw_code_t *const children__thread__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun__thread_LockType,
    (const mp_raw_code_t *)&proto_fun__thread_allocate_lock,
    (const mp_raw_code_t *)&proto_fun__thread_start_new_thread,
    (const mp_raw_code_t *)&proto_fun__thread_get_ident,
    (const mp_raw_code_t *)&proto_fun__thread_stack_size,
    (const mp_raw_code_t *)&proto_fun__thread_exit,
};

static const mp_raw_code_truncated_t proto_fun__thread__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__thread__lt_module_gt_,
    .children = (void *)&children__thread__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data__thread__lt_module_gt_ + 3,
        .line_info_top = fun_data__thread__lt_module_gt_ + 15,
        .opcodes = fun_data__thread__lt_module_gt_ + 15,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data__thread[26] = {
    MP_QSTR__thread_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_LockType,
    MP_QSTR_allocate_lock,
    MP_QSTR_start_new_thread,
    MP_QSTR_get_ident,
    MP_QSTR_stack_size,
    MP_QSTR_exit,
    MP_QSTR___init__,
    MP_QSTR__locked,
    MP_QSTR_locked,
    MP_QSTR_acquire,
    MP_QSTR_release,
    MP_QSTR___enter__,
    MP_QSTR___exit__,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_NotImplementedError,
    MP_QSTR_SystemExit,
    MP_QSTR_self,
    MP_QSTR_waitflag,
    MP_QSTR_RuntimeError,
    MP_QSTR_exc_type,
    MP_QSTR_exc,
    MP_QSTR_tb,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data__thread[1] = {
    MP_ROM_QSTR(MP_QSTR_release_space_unlocked_space_lock),
};

static const mp_frozen_module_t frozen_module__thread = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data__thread,
        .obj_table = (mp_obj_t *)&const_obj_table_data__thread,
    },
    .proto_fun = &proto_fun__thread__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module ssl
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\ssl.mpy
// - frozen file name: ssl.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file ssl.py, scope ssl__lt_module_gt_
static const byte fun_data_ssl__lt_module_gt_[86] = {
    0x18,0x1c, // prelude
    0x01, // names: <module>
    0x80,0x0a,0x66,0x6b,0x40,0x46,0x26,0x46,0x26,0x26,0x66,0x64,0x60, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'tls'
    0x16,0x0f, // STORE_NAME '_tls'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x03, // LOAD_CONST_STRING 'SSLError'
    0x11,0x10, // LOAD_NAME 'OSError'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x03, // STORE_NAME 'SSLError'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x04, // LOAD_ATTR 'SSLContext'
    0x16,0x04, // STORE_NAME 'SSLContext'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x05, // LOAD_ATTR 'PROTOCOL_TLS_CLIENT'
    0x16,0x05, // STORE_NAME 'PROTOCOL_TLS_CLIENT'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x06, // LOAD_ATTR 'PROTOCOL_TLS_SERVER'
    0x16,0x06, // STORE_NAME 'PROTOCOL_TLS_SERVER'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x07, // LOAD_ATTR 'CERT_NONE'
    0x16,0x07, // STORE_NAME 'CERT_NONE'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x08, // LOAD_ATTR 'CERT_OPTIONAL'
    0x16,0x08, // STORE_NAME 'CERT_OPTIONAL'
    0x11,0x0f, // LOAD_NAME '_tls'
    0x13,0x09, // LOAD_ATTR 'CERT_REQUIRED'
    0x16,0x09, // STORE_NAME 'CERT_REQUIRED'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0a, // STORE_NAME 'create_default_context'
    0x50, // LOAD_CONST_FALSE
    0x52, // LOAD_CONST_TRUE
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2a,0x04, // BUILD_TUPLE 4
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x0b, // STORE_NAME 'wrap_socket'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ssl__lt_module_gt_
// frozen bytecode for file ssl.py, scope ssl_SSLError
static const byte fun_data_ssl_SSLError[15] = {
    0x00,0x06, // prelude
    0x03, // names: SSLError
    0x88,0x0e, // code info
    0x11,0x11, // LOAD_NAME '__name__'
    0x16,0x12, // STORE_NAME '__module__'
    0x10,0x03, // LOAD_CONST_STRING 'SSLError'
    0x16,0x13, // STORE_NAME '__qualname__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_SSLError = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_SSLError,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 1,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 3,
        .line_info = fun_data_ssl_SSLError + 3,
        .line_info_top = fun_data_ssl_SSLError + 5,
        .opcodes = fun_data_ssl_SSLError + 5,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_SSLError fun_data_ssl_SSLError[0]
#endif

// child of ssl__lt_module_gt_
// frozen bytecode for file ssl.py, scope ssl_create_default_context
static const byte fun_data_ssl_create_default_context[15] = {
    0x98,0x80,0xc0,0x40,0x06, // prelude
    0x0a, // names: create_default_context
    0x80,0x1f, // code info
    0x12,0x04, // LOAD_GLOBAL 'SSLContext'
    0x12,0x05, // LOAD_GLOBAL 'PROTOCOL_TLS_CLIENT'
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_create_default_context = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_create_default_context,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 15,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 6,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 10,
        .line_info = fun_data_ssl_create_default_context + 6,
        .line_info_top = fun_data_ssl_create_default_context + 8,
        .opcodes = fun_data_ssl_create_default_context + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_create_default_context fun_data_ssl_create_default_context[0]
#endif

// child of ssl__lt_module_gt_
// frozen bytecode for file ssl.py, scope ssl_wrap_socket
static const byte fun_data_ssl_wrap_socket[42] = {
    0xf1,0x84,0xc0,0x01,0x14, // prelude
    0x0b,0x14,0x0c,0x0d,0x0e,0x15, // names: wrap_socket, sock, server_side, do_handshake_on_connect, server_hostname, ssl_context
    0x80,0x25,0x25,0x25, // code info
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x12,0x0a, // LOAD_GLOBAL 'create_default_context'
    0x34,0x00, // CALL_FUNCTION 0
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x14,0x0b, // LOAD_METHOD 'wrap_socket'
    0xb0, // LOAD_FAST 0
    0x10,0x0c, // LOAD_CONST_STRING 'server_side'
    0xb1, // LOAD_FAST 1
    0x10,0x0d, // LOAD_CONST_STRING 'do_handshake_on_connect'
    0xb2, // LOAD_FAST 2
    0x10,0x0e, // LOAD_CONST_STRING 'server_hostname'
    0xb3, // LOAD_FAST 3
    0x36,0x86,0x01, // CALL_METHOD 769
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ssl_wrap_socket = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl_wrap_socket,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 42,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 0,
        .scope_flags = 2,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 4,
        .qstr_block_name_idx = 11,
        .line_info = fun_data_ssl_wrap_socket + 11,
        .line_info_top = fun_data_ssl_wrap_socket + 15,
        .opcodes = fun_data_ssl_wrap_socket + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_ssl_wrap_socket fun_data_ssl_wrap_socket[0]
#endif

static const mp_raw_code_t *const children_ssl__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_ssl_SSLError,
    (const mp_raw_code_t *)&proto_fun_ssl_create_default_context,
    (const mp_raw_code_t *)&proto_fun_ssl_wrap_socket,
};

static const mp_raw_code_truncated_t proto_fun_ssl__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ssl__lt_module_gt_,
    .children = (void *)&children_ssl__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 86,
    .n_children = 3,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_ssl__lt_module_gt_ + 3,
        .line_info_top = fun_data_ssl__lt_module_gt_ + 16,
        .opcodes = fun_data_ssl__lt_module_gt_ + 16,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_ssl[22] = {
    MP_QSTR_ssl_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_tls,
    MP_QSTR_SSLError,
    MP_QSTR_SSLContext,
    MP_QSTR_PROTOCOL_TLS_CLIENT,
    MP_QSTR_PROTOCOL_TLS_SERVER,
    MP_QSTR_CERT_NONE,
    MP_QSTR_CERT_OPTIONAL,
    MP_QSTR_CERT_REQUIRED,
    MP_QSTR_create_default_context,
    MP_QSTR_wrap_socket,
    MP_QSTR_server_side,
    MP_QSTR_do_handshake_on_connect,
    MP_QSTR_server_hostname,
    MP_QSTR__tls,
    MP_QSTR_OSError,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_sock,
    MP_QSTR_ssl_context,
};

static const mp_frozen_module_t frozen_module_ssl = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_ssl,
        .obj_table = NULL,
    },
    .proto_fun = &proto_fun_ssl__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module lcd160cr
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\lcd160cr.mpy
// - frozen file name: lcd160cr.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file lcd160cr.py, scope lcd160cr__lt_module_gt_
static const byte fun_data_lcd160cr__lt_module_gt_[177] = {
    0x2c,0x34, // prelude
    0x01, // names: <module>
    0x80,0x07,0x2c,0x2c,0x46,0x22,0x26,0x26,0x4f,0x23,0x23,0x46,0x22,0x4f,0x46,0x22,0x4f,0x66,0x23,0x23,0x23,0x63,0x23,0x23,0x63, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x02, // LOAD_CONST_STRING 'const'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME 'micropython'
    0x1c,0x02, // IMPORT_FROM 'const'
    0x16,0x02, // STORE_NAME 'const'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x04, // LOAD_CONST_STRING 'sleep_ms'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x05, // IMPORT_NAME 'time'
    0x1c,0x04, // IMPORT_FROM 'sleep_ms'
    0x16,0x04, // STORE_NAME 'sleep_ms'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x06, // IMPORT_NAME 'machine'
    0x16,0x06, // STORE_NAME 'machine'
    0x48,0x14, // SETUP_EXCEPT 20
    0x11,0x06, // LOAD_NAME 'machine'
    0x13,0x07, // LOAD_ATTR 'Pin'
    0x16,0x07, // STORE_NAME 'Pin'
    0x11,0x06, // LOAD_NAME 'machine'
    0x13,0x08, // LOAD_ATTR 'I2C'
    0x16,0x08, // STORE_NAME 'I2C'
    0x11,0x06, // LOAD_NAME 'machine'
    0x13,0x09, // LOAD_ATTR 'SPI'
    0x16,0x09, // STORE_NAME 'SPI'
    0x4a,0x13, // POP_EXCEPT_JUMP 19
    0x57, // DUP_TOP
    0x11,0x5d, // LOAD_NAME 'AttributeError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x16,0x07, // STORE_NAME 'Pin'
    0x51, // LOAD_CONST_NONE
    0x16,0x08, // STORE_NAME 'I2C'
    0x51, // LOAD_CONST_NONE
    0x16,0x09, // STORE_NAME 'SPI'
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x48,0x08, // SETUP_EXCEPT 8
    0x11,0x06, // LOAD_NAME 'machine'
    0x13,0x0a, // LOAD_ATTR 'SoftI2C'
    0x16,0x0a, // STORE_NAME 'SoftI2C'
    0x4a,0x0d, // POP_EXCEPT_JUMP 13
    0x57, // DUP_TOP
    0x11,0x5d, // LOAD_NAME 'AttributeError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x16,0x0a, // STORE_NAME 'SoftI2C'
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x48,0x08, // SETUP_EXCEPT 8
    0x11,0x06, // LOAD_NAME 'machine'
    0x13,0x0b, // LOAD_ATTR 'SoftSPI'
    0x16,0x0b, // STORE_NAME 'SoftSPI'
    0x4a,0x0d, // POP_EXCEPT_JUMP 13
    0x57, // DUP_TOP
    0x11,0x5d, // LOAD_NAME 'AttributeError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x16,0x0b, // STORE_NAME 'SoftSPI'
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x5e, // STORE_NAME 'PORTRAIT'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x5f, // STORE_NAME 'LANDSCAPE'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x60, // STORE_NAME 'PORTRAIT_UPSIDEDOWN'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x16,0x61, // STORE_NAME 'LANDSCAPE_UPSIDEDOWN'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x62, // STORE_NAME 'STARTUP_DECO_NONE'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x63, // STORE_NAME 'STARTUP_DECO_MLOGO'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x64, // STORE_NAME 'STARTUP_DECO_INFO'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x0c, // LOAD_CONST_STRING 'LCD160CR'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0c, // STORE_NAME 'LCD160CR'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of lcd160cr__lt_module_gt_
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR
static const byte fun_data_lcd160cr_LCD160CR[362] = {
    0x38,0xc0,0x02, // prelude
    0x0c, // names: LCD160CR
    0x88,0x2b,0x40,0x68,0x40,0x7b,0x80,0x74,0x89,0x07,0x64,0x40,0x64,0x20,0x84,0x08,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x20,0x6b,0x40,0x64,0x20,0x84,0x09,0x64,0x40,0x64,0x40,0x64,0x20,0x88,0x07,0x64,0x60,0x64,0x20,0x64,0x40,0x64,0x40,0x8b,0x0e,0x64,0x60,0x8a,0x09,0x64,0x20,0x71,0x80,0x0c,0x64,0x40,0x84,0x09,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x40,0x64,0x40,0x64,0x20,0x64,0x20, // code info
    0x11,0x65, // LOAD_NAME '__name__'
    0x16,0x66, // STORE_NAME '__module__'
    0x10,0x0c, // LOAD_CONST_STRING 'LCD160CR'
    0x16,0x67, // STORE_NAME '__qualname__'
    0x11,0x68, // LOAD_NAME 'staticmethod'
    0x32,0x00, // MAKE_FUNCTION 0
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x11, // STORE_NAME 'rgb'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x2c,0x00, // BUILD_MAP 0
    0x51, // LOAD_CONST_NONE
    0x10,0x0d, // LOAD_CONST_STRING 'pwr'
    0x62, // STORE_MAP
    0x51, // LOAD_CONST_NONE
    0x10,0x0e, // LOAD_CONST_STRING 'i2c'
    0x62, // STORE_MAP
    0x51, // LOAD_CONST_NONE
    0x10,0x0f, // LOAD_CONST_STRING 'spi'
    0x62, // STORE_MAP
    0x22,0x80,0x62, // LOAD_CONST_SMALL_INT 98
    0x10,0x10, // LOAD_CONST_STRING 'i2c_addr'
    0x62, // STORE_MAP
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x12, // STORE_NAME '__init__'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x2c, // STORE_NAME '_send_cmd'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x2e, // STORE_NAME '_recv_cmd'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x30, // STORE_NAME 'set_power'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x31, // STORE_NAME 'set_orient'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x32, // STORE_NAME 'set_brightness'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x33, // STORE_NAME 'set_pen'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x34, // STORE_NAME 'erase'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x35, // STORE_NAME 'dot'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x36, // STORE_NAME 'rect'
    0x32,0x0b, // MAKE_FUNCTION 11
    0x16,0x37, // STORE_NAME 'rect_outline'
    0x32,0x0c, // MAKE_FUNCTION 12
    0x16,0x38, // STORE_NAME 'rect_interior'
    0x32,0x0d, // MAKE_FUNCTION 13
    0x16,0x39, // STORE_NAME 'line'
    0x32,0x0e, // MAKE_FUNCTION 14
    0x16,0x3a, // STORE_NAME 'dot_no_clip'
    0x32,0x0f, // MAKE_FUNCTION 15
    0x16,0x3b, // STORE_NAME 'rect_no_clip'
    0x32,0x10, // MAKE_FUNCTION 16
    0x16,0x3c, // STORE_NAME 'rect_outline_no_clip'
    0x32,0x11, // MAKE_FUNCTION 17
    0x16,0x3d, // STORE_NAME 'rect_interior_no_clip'
    0x32,0x12, // MAKE_FUNCTION 18
    0x16,0x3e, // STORE_NAME 'line_no_clip'
    0x32,0x13, // MAKE_FUNCTION 19
    0x16,0x3f, // STORE_NAME 'set_text_color'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x04, // BUILD_TUPLE 4
    0x53, // LOAD_NULL
    0x33,0x14, // MAKE_FUNCTION_DEFARGS 20
    0x16,0x40, // STORE_NAME 'set_font'
    0x32,0x15, // MAKE_FUNCTION 21
    0x16,0x41, // STORE_NAME 'set_pos'
    0x32,0x16, // MAKE_FUNCTION 22
    0x16,0x42, // STORE_NAME 'write'
    0x32,0x17, // MAKE_FUNCTION 23
    0x16,0x45, // STORE_NAME 'is_touched'
    0x32,0x18, // MAKE_FUNCTION 24
    0x16,0x46, // STORE_NAME 'get_touch'
    0x32,0x19, // MAKE_FUNCTION 25
    0x16,0x47, // STORE_NAME 'set_spi_win'
    0x52, // LOAD_CONST_TRUE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x1a, // MAKE_FUNCTION_DEFARGS 26
    0x16,0x48, // STORE_NAME 'fast_spi'
    0x32,0x1b, // MAKE_FUNCTION 27
    0x16,0x49, // STORE_NAME 'show_framebuf'
    0x32,0x1c, // MAKE_FUNCTION 28
    0x16,0x4a, // STORE_NAME 'set_pixel'
    0x32,0x1d, // MAKE_FUNCTION 29
    0x16,0x4b, // STORE_NAME 'get_pixel'
    0x32,0x1e, // MAKE_FUNCTION 30
    0x16,0x4c, // STORE_NAME 'get_line'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0x2a,0x04, // BUILD_TUPLE 4
    0x53, // LOAD_NULL
    0x33,0x1f, // MAKE_FUNCTION_DEFARGS 31
    0x16,0x4e, // STORE_NAME 'screen_dump'
    0x32,0x20, // MAKE_FUNCTION 32
    0x16,0x4f, // STORE_NAME 'screen_load'
    0x50, // LOAD_CONST_FALSE
    0x50, // LOAD_CONST_FALSE
    0x51, // LOAD_CONST_NONE
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x21, // MAKE_FUNCTION_DEFARGS 33
    0x16,0x50, // STORE_NAME 'touch_config'
    0x32,0x22, // MAKE_FUNCTION 34
    0x16,0x51, // STORE_NAME 'set_scroll'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x22,0x8f,0x60, // LOAD_CONST_SMALL_INT 2016
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x08, // BUILD_TUPLE 8
    0x53, // LOAD_NULL
    0x33,0x23, // MAKE_FUNCTION_DEFARGS 35
    0x16,0x52, // STORE_NAME 'set_scroll_win'
    0x32,0x24, // MAKE_FUNCTION 36
    0x16,0x53, // STORE_NAME 'set_scroll_buf'
    0x32,0x25, // MAKE_FUNCTION 37
    0x16,0x54, // STORE_NAME 'jpeg'
    0x32,0x26, // MAKE_FUNCTION 38
    0x16,0x55, // STORE_NAME 'jpeg_start'
    0x32,0x27, // MAKE_FUNCTION 39
    0x16,0x56, // STORE_NAME 'jpeg_data'
    0x32,0x28, // MAKE_FUNCTION 40
    0x16,0x57, // STORE_NAME 'feed_wdt'
    0x32,0x29, // MAKE_FUNCTION 41
    0x16,0x58, // STORE_NAME 'reset'
    0x32,0x2a, // MAKE_FUNCTION 42
    0x16,0x59, // STORE_NAME 'set_uart_baudrate'
    0x32,0x2b, // MAKE_FUNCTION 43
    0x16,0x5a, // STORE_NAME 'set_startup_deco'
    0x32,0x2c, // MAKE_FUNCTION 44
    0x16,0x5b, // STORE_NAME 'save_to_flash'
    0x32,0x2d, // MAKE_FUNCTION 45
    0x16,0x5c, // STORE_NAME 'set_i2c_addr'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rgb
static const byte fun_data_lcd160cr_LCD160CR_rgb[29] = {
    0x2b,0x0e, // prelude
    0x11,0x69,0x6a,0x6b, // names: rgb, r, g, b
    0x80,0x2f,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x22,0x81,0x78, // LOAD_CONST_SMALL_INT 248
    0xef, // BINARY_OP 24 __and__
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7c, // LOAD_CONST_SMALL_INT 252
    0xef, // BINARY_OP 24 __and__
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xb2, // LOAD_FAST 2
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf1, // BINARY_OP 26 __rshift__
    0xed, // BINARY_OP 22 __or__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rgb = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rgb,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 29,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 17,
        .line_info = fun_data_lcd160cr_LCD160CR_rgb + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rgb + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_rgb + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rgb fun_data_lcd160cr_LCD160CR_rgb[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR___init__
static const byte fun_data_lcd160cr_LCD160CR___init__[924] = {
    0xea,0x81,0x80,0x88,0x40,0xbc,0x02, // prelude
    0x12,0x6c,0x6d,0x0d,0x0e,0x0f,0x10, // names: __init__, self, connect, pwr, i2c, spi, i2c_addr
    0x80,0x33,0x80,0x0a,0x27,0x26,0x47,0x27,0x35,0x25,0x27,0x2b,0x27,0x5a,0x49,0x24,0x26,0x27,0x2b,0x27,0x1f,0x43,0x49,0x27,0x27,0x35,0x25,0x27,0x2b,0x27,0x5a,0x49,0x24,0x26,0x27,0x2b,0x27,0x1f,0x43,0x49,0x27,0x27,0x35,0x25,0x27,0x2b,0x27,0x5a,0x49,0x24,0x26,0x27,0x2b,0x27,0x1f,0x43,0x49,0x27,0x27,0x35,0x25,0x27,0x2b,0x27,0x5a,0x49,0x24,0x26,0x27,0x2b,0x27,0x1f,0x43,0x49,0x46,0x69,0x2f,0x27,0x24,0x24,0x44,0x64,0x26,0x66,0x29,0x66,0x29, // code info
    0xb1, // LOAD_FAST 1
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0xdd,0x85, // POP_JUMP_IF_FALSE 733
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x10,0x13, // LOAD_CONST_STRING 'X'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xab,0x81, // POP_JUMP_IF_FALSE 171
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x14, // LOAD_CONST_STRING 'X4'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x13,0x15, // LOAD_ATTR 'OUT'
    0x34,0x02, // CALL_FUNCTION 2
    0x42,0x41, // JUMP 1
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'pwr'
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x7c, // POP_JUMP_IF_FALSE 60
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x10,0x13, // LOAD_CONST_STRING 'X'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x68, // JUMP 40
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x10,0x16, // LOAD_CONST_STRING 'scl'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x17, // LOAD_CONST_STRING 'X9'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x18, // LOAD_CONST_STRING 'sda'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x19, // LOAD_CONST_STRING 'X10'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x84,0x00, // CALL_FUNCTION 512
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0xc4,0x80, // POP_JUMP_IF_FALSE 68
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x10,0x13, // LOAD_CONST_STRING 'X'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x70, // JUMP 48
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x62, // POP_JUMP_IF_FALSE 34
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x10,0x1a, // LOAD_CONST_STRING 'sck'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1b, // LOAD_CONST_STRING 'X6'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1c, // LOAD_CONST_STRING 'mosi'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1d, // LOAD_CONST_STRING 'X8'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1e, // LOAD_CONST_STRING 'miso'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1f, // LOAD_CONST_STRING 'X7'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x86,0x00, // CALL_FUNCTION 768
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x9c,0x84, // JUMP 540
    0xb1, // LOAD_FAST 1
    0x10,0x20, // LOAD_CONST_STRING 'Y'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xab,0x81, // POP_JUMP_IF_FALSE 171
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x21, // LOAD_CONST_STRING 'Y4'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x13,0x15, // LOAD_ATTR 'OUT'
    0x34,0x02, // CALL_FUNCTION 2
    0x42,0x41, // JUMP 1
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'pwr'
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x7c, // POP_JUMP_IF_FALSE 60
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x10,0x20, // LOAD_CONST_STRING 'Y'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x68, // JUMP 40
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x10,0x16, // LOAD_CONST_STRING 'scl'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x22, // LOAD_CONST_STRING 'Y9'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x18, // LOAD_CONST_STRING 'sda'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x23, // LOAD_CONST_STRING 'Y10'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x84,0x00, // CALL_FUNCTION 512
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0xc4,0x80, // POP_JUMP_IF_FALSE 68
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x10,0x20, // LOAD_CONST_STRING 'Y'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x70, // JUMP 48
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x62, // POP_JUMP_IF_FALSE 34
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x10,0x1a, // LOAD_CONST_STRING 'sck'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x24, // LOAD_CONST_STRING 'Y6'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1c, // LOAD_CONST_STRING 'mosi'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x25, // LOAD_CONST_STRING 'Y8'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1e, // LOAD_CONST_STRING 'miso'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x26, // LOAD_CONST_STRING 'Y7'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x86,0x00, // CALL_FUNCTION 768
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0xea,0x82, // JUMP 362
    0xb1, // LOAD_FAST 1
    0x10,0x27, // LOAD_CONST_STRING 'XY'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xab,0x81, // POP_JUMP_IF_FALSE 171
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x14, // LOAD_CONST_STRING 'X4'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x13,0x15, // LOAD_ATTR 'OUT'
    0x34,0x02, // CALL_FUNCTION 2
    0x42,0x41, // JUMP 1
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'pwr'
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x7c, // POP_JUMP_IF_FALSE 60
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x10,0x20, // LOAD_CONST_STRING 'Y'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x68, // JUMP 40
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x10,0x16, // LOAD_CONST_STRING 'scl'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x22, // LOAD_CONST_STRING 'Y9'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x18, // LOAD_CONST_STRING 'sda'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x23, // LOAD_CONST_STRING 'Y10'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x84,0x00, // CALL_FUNCTION 512
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0xc4,0x80, // POP_JUMP_IF_FALSE 68
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x10,0x13, // LOAD_CONST_STRING 'X'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x70, // JUMP 48
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x62, // POP_JUMP_IF_FALSE 34
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x10,0x1a, // LOAD_CONST_STRING 'sck'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1b, // LOAD_CONST_STRING 'X6'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1c, // LOAD_CONST_STRING 'mosi'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1d, // LOAD_CONST_STRING 'X8'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1e, // LOAD_CONST_STRING 'miso'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x1f, // LOAD_CONST_STRING 'X7'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x86,0x00, // CALL_FUNCTION 768
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0xb8,0x81, // JUMP 184
    0xb1, // LOAD_FAST 1
    0x10,0x28, // LOAD_CONST_STRING 'YX'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xaa,0x81, // POP_JUMP_IF_FALSE 170
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x21, // LOAD_CONST_STRING 'Y4'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x13,0x15, // LOAD_ATTR 'OUT'
    0x34,0x02, // CALL_FUNCTION 2
    0x42,0x41, // JUMP 1
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'pwr'
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x7c, // POP_JUMP_IF_FALSE 60
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x08, // LOAD_GLOBAL 'I2C'
    0x10,0x13, // LOAD_CONST_STRING 'X'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x68, // JUMP 40
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0x12,0x0a, // LOAD_GLOBAL 'SoftI2C'
    0x10,0x16, // LOAD_CONST_STRING 'scl'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x17, // LOAD_CONST_STRING 'X9'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x18, // LOAD_CONST_STRING 'sda'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x19, // LOAD_CONST_STRING 'X10'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x84,0x00, // CALL_FUNCTION 512
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0xc4,0x80, // POP_JUMP_IF_FALSE 68
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x09, // LOAD_GLOBAL 'SPI'
    0x10,0x20, // LOAD_CONST_STRING 'Y'
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x70, // JUMP 48
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x62, // POP_JUMP_IF_FALSE 34
    0x12,0x0b, // LOAD_GLOBAL 'SoftSPI'
    0x10,0x1a, // LOAD_CONST_STRING 'sck'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x24, // LOAD_CONST_STRING 'Y6'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1c, // LOAD_CONST_STRING 'mosi'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x25, // LOAD_CONST_STRING 'Y8'
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x1e, // LOAD_CONST_STRING 'miso'
    0x12,0x07, // LOAD_GLOBAL 'Pin'
    0x10,0x26, // LOAD_CONST_STRING 'Y7'
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x86,0x00, // CALL_FUNCTION 768
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x47, // JUMP 7
    0x12,0x6e, // LOAD_GLOBAL 'ImportError'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x44, // JUMP 4
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0x42,0x47, // JUMP 7
    0x12,0x6f, // LOAD_GLOBAL 'ValueError'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x42,0x62, // JUMP 34
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x43,0x4a, // POP_JUMP_IF_TRUE 10
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x43,0x45, // POP_JUMP_IF_TRUE 5
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x6f, // LOAD_GLOBAL 'ValueError'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x0d, // STORE_ATTR 'pwr'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x0e, // STORE_ATTR 'i2c'
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x18,0x0f, // STORE_ATTR 'spi'
    0xb5, // LOAD_FAST 5
    0xb0, // LOAD_FAST 0
    0x18,0x10, // STORE_ATTR 'i2c_addr'
    0x22,0x81,0x20, // LOAD_CONST_SMALL_INT 160
    0xb0, // LOAD_FAST 0
    0x18,0x29, // STORE_ATTR 'w'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 'h'
    0xb0, // LOAD_FAST 0
    0x13,0x0d, // LOAD_ATTR 'pwr'
    0x14,0x2b, // LOAD_METHOD 'value'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x04, // LOAD_GLOBAL 'sleep_ms'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x12,0x04, // LOAD_GLOBAL 'sleep_ms'
    0x22,0x32, // LOAD_CONST_SMALL_INT 50
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 924,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 8,
        .n_pos_args = 2,
        .n_kwonly_args = 4,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_lcd160cr_LCD160CR___init__ + 14,
        .line_info_top = fun_data_lcd160cr_LCD160CR___init__ + 101,
        .opcodes = fun_data_lcd160cr_LCD160CR___init__ + 101,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR___init__ fun_data_lcd160cr_LCD160CR___init__[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR__send_cmd
static const byte fun_data_lcd160cr_LCD160CR__send_cmd[50] = {
    0xbb,0x01,0x14, // prelude
    0x2c,0x6c,0x70,0x71, // names: _send_cmd, self, cmd, data
    0x80,0xaa,0x20,0x2c,0x24,0x27, // code info
    0x12,0x72, // LOAD_GLOBAL 'bytearray'
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x56, // STORE_SUBSCR
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'i2c'
    0x14,0x2d, // LOAD_METHOD 'writeto'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'i2c_addr'
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR__send_cmd = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR__send_cmd,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 50,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_lcd160cr_LCD160CR__send_cmd + 7,
        .line_info_top = fun_data_lcd160cr_LCD160CR__send_cmd + 13,
        .opcodes = fun_data_lcd160cr_LCD160CR__send_cmd + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR__send_cmd fun_data_lcd160cr_LCD160CR__send_cmd[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR__recv_cmd
static const byte fun_data_lcd160cr_LCD160CR__recv_cmd[40] = {
    0x3b,0x10, // prelude
    0x2e,0x6c,0x70,0x74, // names: _recv_cmd, self, cmd, n_data
    0x80,0xb1,0x20,0x32, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'i2c'
    0x14,0x2d, // LOAD_METHOD 'writeto'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'i2c_addr'
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'i2c'
    0x14,0x2f, // LOAD_METHOD 'readfrom'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'i2c_addr'
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR__recv_cmd = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR__recv_cmd,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 46,
        .line_info = fun_data_lcd160cr_LCD160CR__recv_cmd + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR__recv_cmd + 10,
        .opcodes = fun_data_lcd160cr_LCD160CR__recv_cmd + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR__recv_cmd fun_data_lcd160cr_LCD160CR__recv_cmd[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_power
static const byte fun_data_lcd160cr_LCD160CR_set_power[30] = {
    0x32,0x0c, // prelude
    0x30,0x6c,0x76, // names: set_power, self, on
    0x80,0xb6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_power = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_power,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 30,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 48,
        .line_info = fun_data_lcd160cr_LCD160CR_set_power + 5,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_power + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_power + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_power fun_data_lcd160cr_LCD160CR_set_power[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_orient
static const byte fun_data_lcd160cr_LCD160CR_set_orient[55] = {
    0x32,0x12, // prelude
    0x31,0x6c,0x77, // names: set_orient, self, orient
    0x80,0xba,0x20,0x2e,0x26,0x4c, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x23,0x07, // LOAD_CONST_OBJ 7
    0xdd, // BINARY_OP 6 <in>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xb0, // LOAD_FAST 0
    0x18,0x29, // STORE_ATTR 'w'
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 'h'
    0x42,0x4a, // JUMP 10
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xb0, // LOAD_FAST 0
    0x18,0x29, // STORE_ATTR 'w'
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR 'h'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_orient = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_orient,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 55,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 49,
        .line_info = fun_data_lcd160cr_LCD160CR_set_orient + 5,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_orient + 11,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_orient + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_orient fun_data_lcd160cr_LCD160CR_set_orient[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_brightness
static const byte fun_data_lcd160cr_LCD160CR_set_brightness[26] = {
    0x3a,0x0c, // prelude
    0x32,0x6c,0x2b, // names: set_brightness, self, value
    0x80,0xc2,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x9f, // LOAD_CONST_SMALL_INT 31
    0xef, // BINARY_OP 24 __and__
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_brightness = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_brightness,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 50,
        .line_info = fun_data_lcd160cr_LCD160CR_set_brightness + 5,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_brightness + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_brightness + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_brightness fun_data_lcd160cr_LCD160CR_set_brightness[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_pen
static const byte fun_data_lcd160cr_LCD160CR_set_pen[40] = {
    0x5b,0x0e, // prelude
    0x33,0x6c,0x39,0x78, // names: set_pen, self, line, fill
    0x80,0xc6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_pen = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_pen,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 51,
        .line_info = fun_data_lcd160cr_LCD160CR_set_pen + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_pen + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_pen + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_pen fun_data_lcd160cr_LCD160CR_set_pen[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_erase
static const byte fun_data_lcd160cr_LCD160CR_erase[16] = {
    0x19,0x0a, // prelude
    0x34,0x6c, // names: erase, self
    0x80,0xca,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa0, // LOAD_CONST_SMALL_INT 32
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_erase = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_erase,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 16,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_lcd160cr_LCD160CR_erase + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_erase + 7,
        .opcodes = fun_data_lcd160cr_LCD160CR_erase + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_erase fun_data_lcd160cr_LCD160CR_erase[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_dot
static const byte fun_data_lcd160cr_LCD160CR_dot[26] = {
    0x43,0x0e, // prelude
    0x35,0x6c,0x79,0x7a, // names: dot, self, x, y
    0x80,0xce,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa1, // LOAD_CONST_SMALL_INT 33
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_dot = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_dot,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 53,
        .line_info = fun_data_lcd160cr_LCD160CR_dot + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_dot + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_dot + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_dot fun_data_lcd160cr_LCD160CR_dot[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect
static const byte fun_data_lcd160cr_LCD160CR_rect[31] = {
    0xe1,0x04,0x12, // prelude
    0x36,0x6c,0x79,0x7a,0x29,0x2a, // names: rect, self, x, y, w, h
    0x80,0xd2,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa2, // LOAD_CONST_SMALL_INT 34
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 31,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 54,
        .line_info = fun_data_lcd160cr_LCD160CR_rect + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect fun_data_lcd160cr_LCD160CR_rect[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect_outline
static const byte fun_data_lcd160cr_LCD160CR_rect_outline[31] = {
    0xe1,0x04,0x12, // prelude
    0x37,0x6c,0x79,0x7a,0x29,0x2a, // names: rect_outline, self, x, y, w, h
    0x80,0xd6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa3, // LOAD_CONST_SMALL_INT 35
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect_outline = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect_outline,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 31,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 55,
        .line_info = fun_data_lcd160cr_LCD160CR_rect_outline + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect_outline + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect_outline + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect_outline fun_data_lcd160cr_LCD160CR_rect_outline[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect_interior
static const byte fun_data_lcd160cr_LCD160CR_rect_interior[31] = {
    0xe1,0x04,0x12, // prelude
    0x38,0x6c,0x79,0x7a,0x29,0x2a, // names: rect_interior, self, x, y, w, h
    0x80,0xda,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa4, // LOAD_CONST_SMALL_INT 36
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect_interior = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect_interior,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 31,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 56,
        .line_info = fun_data_lcd160cr_LCD160CR_rect_interior + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect_interior + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect_interior + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect_interior fun_data_lcd160cr_LCD160CR_rect_interior[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_line
static const byte fun_data_lcd160cr_LCD160CR_line[31] = {
    0xe1,0x04,0x12, // prelude
    0x39,0x6c,0x7b,0x7c,0x7d,0x7e, // names: line, self, x1, y1, x2, y2
    0x80,0xde,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0xa5, // LOAD_CONST_SMALL_INT 37
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_line = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_line,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 31,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 57,
        .line_info = fun_data_lcd160cr_LCD160CR_line + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_line + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_line + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_line fun_data_lcd160cr_LCD160CR_line[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_dot_no_clip
static const byte fun_data_lcd160cr_LCD160CR_dot_no_clip[27] = {
    0x43,0x0e, // prelude
    0x3a,0x6c,0x79,0x7a, // names: dot_no_clip, self, x, y
    0x80,0xe2,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x31, // LOAD_CONST_SMALL_INT 49
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_dot_no_clip = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_dot_no_clip,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 27,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_lcd160cr_LCD160CR_dot_no_clip + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_dot_no_clip + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_dot_no_clip + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_dot_no_clip fun_data_lcd160cr_LCD160CR_dot_no_clip[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect_no_clip
static const byte fun_data_lcd160cr_LCD160CR_rect_no_clip[32] = {
    0xe1,0x04,0x12, // prelude
    0x3b,0x6c,0x79,0x7a,0x29,0x2a, // names: rect_no_clip, self, x, y, w, h
    0x80,0xe6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x32, // LOAD_CONST_SMALL_INT 50
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect_no_clip = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect_no_clip,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 59,
        .line_info = fun_data_lcd160cr_LCD160CR_rect_no_clip + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect_no_clip + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect_no_clip + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect_no_clip fun_data_lcd160cr_LCD160CR_rect_no_clip[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect_outline_no_clip
static const byte fun_data_lcd160cr_LCD160CR_rect_outline_no_clip[32] = {
    0xe1,0x04,0x12, // prelude
    0x3c,0x6c,0x79,0x7a,0x29,0x2a, // names: rect_outline_no_clip, self, x, y, w, h
    0x80,0xea,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x33, // LOAD_CONST_SMALL_INT 51
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect_outline_no_clip = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect_outline_no_clip,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 60,
        .line_info = fun_data_lcd160cr_LCD160CR_rect_outline_no_clip + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect_outline_no_clip + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect_outline_no_clip + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect_outline_no_clip fun_data_lcd160cr_LCD160CR_rect_outline_no_clip[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_rect_interior_no_clip
static const byte fun_data_lcd160cr_LCD160CR_rect_interior_no_clip[32] = {
    0xe1,0x04,0x12, // prelude
    0x3d,0x6c,0x79,0x7a,0x29,0x2a, // names: rect_interior_no_clip, self, x, y, w, h
    0x80,0xee,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x34, // LOAD_CONST_SMALL_INT 52
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_rect_interior_no_clip = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_rect_interior_no_clip,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 61,
        .line_info = fun_data_lcd160cr_LCD160CR_rect_interior_no_clip + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_rect_interior_no_clip + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_rect_interior_no_clip + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_rect_interior_no_clip fun_data_lcd160cr_LCD160CR_rect_interior_no_clip[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_line_no_clip
static const byte fun_data_lcd160cr_LCD160CR_line_no_clip[32] = {
    0xe1,0x04,0x12, // prelude
    0x3e,0x6c,0x7b,0x7c,0x7d,0x7e, // names: line_no_clip, self, x1, y1, x2, y2
    0x80,0xf2,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x35, // LOAD_CONST_SMALL_INT 53
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_line_no_clip = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_line_no_clip,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 62,
        .line_info = fun_data_lcd160cr_LCD160CR_line_no_clip + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_line_no_clip + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_line_no_clip + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_line_no_clip fun_data_lcd160cr_LCD160CR_line_no_clip[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_text_color
static const byte fun_data_lcd160cr_LCD160CR_set_text_color[43] = {
    0x5b,0x10, // prelude
    0x3f,0x6c,0x7f,0x81,0x00, // names: set_text_color, self, fg, bg
    0x80,0xf6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x40, // LOAD_CONST_SMALL_INT 64
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_text_color = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_text_color,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 43,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 63,
        .line_info = fun_data_lcd160cr_LCD160CR_set_text_color + 7,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_text_color + 10,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_text_color + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_text_color fun_data_lcd160cr_LCD160CR_set_text_color[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_font
static const byte fun_data_lcd160cr_LCD160CR_set_font[62] = {
    0xe2,0x84,0x80,0x01,0x20, // prelude
    0x40,0x6c,0x81,0x01,0x81,0x02,0x81,0x03,0x81,0x04,0x81,0x05, // names: set_font, self, font, scale, bold, trans, scroll
    0x80,0xfa,0x20,0x36, // code info
    0xb2, // LOAD_FAST 2
    0x83, // LOAD_CONST_SMALL_INT 3
    0xef, // BINARY_OP 24 __and__
    0xb3, // LOAD_FAST 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0xef, // BINARY_OP 24 __and__
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0xef, // BINARY_OP 24 __and__
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xb5, // LOAD_FAST 5
    0x81, // LOAD_CONST_SMALL_INT 1
    0xef, // BINARY_OP 24 __and__
    0x84, // LOAD_CONST_SMALL_INT 4
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x41, // LOAD_CONST_SMALL_INT 65
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb6, // LOAD_FAST 6
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_font = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_font,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 62,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 4,
        .qstr_block_name_idx = 64,
        .line_info = fun_data_lcd160cr_LCD160CR_set_font + 17,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_font + 21,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_font + 21,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_font fun_data_lcd160cr_LCD160CR_set_font[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_pos
static const byte fun_data_lcd160cr_LCD160CR_set_pos[28] = {
    0x43,0x0e, // prelude
    0x41,0x6c,0x79,0x7a, // names: set_pos, self, x, y
    0x80,0xff,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x42, // LOAD_CONST_SMALL_INT 66
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_pos = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_pos,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 28,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 65,
        .line_info = fun_data_lcd160cr_LCD160CR_set_pos + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_pos + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_pos + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_pos fun_data_lcd160cr_LCD160CR_set_pos[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_write
static const byte fun_data_lcd160cr_LCD160CR_write[72] = {
    0x4a,0x16, // prelude
    0x42,0x6c,0x81,0x06, // names: write, self, s
    0x90,0x03,0x20,0x2b,0x48,0x2a,0x29, // code info
    0x12,0x81,0x07, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x81,0x08, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb1, // LOAD_FAST 1
    0x14,0x43, // LOAD_METHOD 'encode'
    0x10,0x44, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x57, // JUMP 23
    0x57, // DUP_TOP
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb2, // LOAD_FAST 2
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xf2, // BINARY_OP 27 __add__
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x43, // LOAD_CONST_SMALL_INT 67
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x24, // POP_JUMP_IF_TRUE -28
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 72,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 66,
        .line_info = fun_data_lcd160cr_LCD160CR_write + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_write + 13,
        .opcodes = fun_data_lcd160cr_LCD160CR_write + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_write fun_data_lcd160cr_LCD160CR_write[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_is_touched
static const byte fun_data_lcd160cr_LCD160CR_is_touched[24] = {
    0x29,0x0c, // prelude
    0x45,0x6c, // names: is_touched, self
    0x90,0x0c,0x20,0x2a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD '_recv_cmd'
    0x22,0x80,0x50, // LOAD_CONST_SMALL_INT 80
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x02, // CALL_METHOD 2
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_is_touched = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_is_touched,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 24,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 69,
        .line_info = fun_data_lcd160cr_LCD160CR_is_touched + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_is_touched + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_is_touched + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_is_touched fun_data_lcd160cr_LCD160CR_is_touched[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_get_touch
static const byte fun_data_lcd160cr_LCD160CR_get_touch[36] = {
    0x29,0x0c, // prelude
    0x46,0x6c, // names: get_touch, self
    0x90,0x11,0x20,0x2a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD '_recv_cmd'
    0x22,0x80,0x51, // LOAD_CONST_SMALL_INT 81
    0x84, // LOAD_CONST_SMALL_INT 4
    0x36,0x02, // CALL_METHOD 2
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xb1, // LOAD_FAST 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xed, // BINARY_OP 22 __or__
    0xb1, // LOAD_FAST 1
    0x83, // LOAD_CONST_SMALL_INT 3
    0x55, // LOAD_SUBSCR
    0x2a,0x03, // BUILD_TUPLE 3
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_get_touch = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_get_touch,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 70,
        .line_info = fun_data_lcd160cr_LCD160CR_get_touch + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_get_touch + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_get_touch + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_get_touch fun_data_lcd160cr_LCD160CR_get_touch[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_spi_win
static const byte fun_data_lcd160cr_LCD160CR_set_spi_win[33] = {
    0xe1,0x04,0x12, // prelude
    0x47,0x6c,0x79,0x7a,0x29,0x2a, // names: set_spi_win, self, x, y, w, h
    0x90,0x16,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x60, // LOAD_CONST_SMALL_INT 96
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_spi_win = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_spi_win,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 33,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 71,
        .line_info = fun_data_lcd160cr_LCD160CR_set_spi_win + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_spi_win + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_spi_win + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_spi_win fun_data_lcd160cr_LCD160CR_set_spi_win[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_fast_spi
static const byte fun_data_lcd160cr_LCD160CR_fast_spi[25] = {
    0x9a,0x01,0x12, // prelude
    0x48,0x6c,0x81,0x09, // names: fast_spi, self, flush
    0x90,0x1a,0x20,0x43,0x26, // code info
    0xb1, // LOAD_FAST 1
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x04, // LOAD_GLOBAL 'sleep_ms'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0f, // LOAD_ATTR 'spi'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_fast_spi = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_fast_spi,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 25,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 72,
        .line_info = fun_data_lcd160cr_LCD160CR_fast_spi + 7,
        .line_info_top = fun_data_lcd160cr_LCD160CR_fast_spi + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_fast_spi + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_fast_spi fun_data_lcd160cr_LCD160CR_fast_spi[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_show_framebuf
static const byte fun_data_lcd160cr_LCD160CR_show_framebuf[40] = {
    0x42,0x12, // prelude
    0x49,0x6c,0x81,0x0a, // names: show_framebuf, self, buf
    0x90,0x21,0x20,0x2e,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x47, // LOAD_METHOD 'set_spi_win'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR 'w'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'h'
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x48, // LOAD_METHOD 'fast_spi'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x42, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_show_framebuf = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_show_framebuf,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 73,
        .line_info = fun_data_lcd160cr_LCD160CR_show_framebuf + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_show_framebuf + 11,
        .opcodes = fun_data_lcd160cr_LCD160CR_show_framebuf + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_show_framebuf fun_data_lcd160cr_LCD160CR_show_framebuf[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_pixel
static const byte fun_data_lcd160cr_LCD160CR_set_pixel[39] = {
    0xe0,0x04,0x12, // prelude
    0x4a,0x6c,0x79,0x7a,0x81,0x0b, // names: set_pixel, self, x, y, c
    0x90,0x27,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x70, // LOAD_CONST_SMALL_INT 112
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_pixel = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_pixel,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 39,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 74,
        .line_info = fun_data_lcd160cr_LCD160CR_set_pixel + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_pixel + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_pixel + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_pixel fun_data_lcd160cr_LCD160CR_set_pixel[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_get_pixel
static const byte fun_data_lcd160cr_LCD160CR_get_pixel[30] = {
    0x3b,0x10, // prelude
    0x4b,0x6c,0x79,0x7a, // names: get_pixel, self, x, y
    0x90,0x2b,0x20,0x2a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2e, // LOAD_METHOD '_recv_cmd'
    0x22,0x80,0x71, // LOAD_CONST_SMALL_INT 113
    0x82, // LOAD_CONST_SMALL_INT 2
    0x36,0x02, // CALL_METHOD 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb3, // LOAD_FAST 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xed, // BINARY_OP 22 __or__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_get_pixel = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_get_pixel,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 30,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 75,
        .line_info = fun_data_lcd160cr_LCD160CR_get_pixel + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_get_pixel + 10,
        .opcodes = fun_data_lcd160cr_LCD160CR_get_pixel + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_get_pixel fun_data_lcd160cr_LCD160CR_get_pixel[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_get_line
static const byte fun_data_lcd160cr_LCD160CR_get_line[51] = {
    0xd8,0x04,0x14, // prelude
    0x4c,0x6c,0x79,0x7a,0x81,0x0a, // names: get_line, self, x, y, buf
    0x90,0x30,0x20,0x38, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x80,0x72, // LOAD_CONST_SMALL_INT 114
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf6, // BINARY_OP 31 __floordiv__
    0x2b,0x03, // BUILD_LIST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0e, // LOAD_ATTR 'i2c'
    0x14,0x4d, // LOAD_METHOD 'readfrom_into'
    0xb0, // LOAD_FAST 0
    0x13,0x10, // LOAD_ATTR 'i2c_addr'
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_get_line = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_get_line,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 51,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 76,
        .line_info = fun_data_lcd160cr_LCD160CR_get_line + 9,
        .line_info_top = fun_data_lcd160cr_LCD160CR_get_line + 13,
        .opcodes = fun_data_lcd160cr_LCD160CR_get_line + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_get_line fun_data_lcd160cr_LCD160CR_get_line[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_screen_dump
static const byte fun_data_lcd160cr_LCD160CR_screen_dump[109] = {
    0x82,0x94,0x80,0x01,0x28, // prelude
    0x4e,0x6c,0x81,0x0a,0x79,0x7a,0x29,0x2a, // names: screen_dump, self, buf, x, y, w, h
    0x90,0x35,0x20,0x25,0x26,0x25,0x46,0x2a,0x22,0x28,0x29,0x30, // code info
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR 'w'
    0xb2, // LOAD_FAST 2
    0xf3, // BINARY_OP 28 __sub__
    0xc4, // STORE_FAST 4
    0xb5, // LOAD_FAST 5
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'h'
    0xb3, // LOAD_FAST 3
    0xf3, // BINARY_OP 28 __sub__
    0xc5, // STORE_FAST 5
    0x12,0x72, // LOAD_GLOBAL 'bytearray'
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf4, // BINARY_OP 29 __mul__
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc7, // STORE_FAST 7
    0xb3, // LOAD_FAST 3
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0xb3, // LOAD_FAST 3
    0x42,0x63, // JUMP 35
    0x57, // DUP_TOP
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x14,0x4c, // LOAD_METHOD 'get_line'
    0xb2, // LOAD_FAST 2
    0xb8, // LOAD_FAST 8
    0xb6, // LOAD_FAST 6
    0x36,0x03, // CALL_METHOD 3
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xb1, // LOAD_FAST 1
    0xb7, // LOAD_FAST 7
    0xb7, // LOAD_FAST 7
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf4, // BINARY_OP 29 __mul__
    0xf2, // BINARY_OP 27 __add__
    0x2e,0x02, // BUILD_SLICE 2
    0x56, // STORE_SUBSCR
    0xb7, // LOAD_FAST 7
    0xb4, // LOAD_FAST 4
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf4, // BINARY_OP 29 __mul__
    0xe5, // BINARY_OP 14 __iadd__
    0xc7, // STORE_FAST 7
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x18, // POP_JUMP_IF_TRUE -40
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_screen_dump = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_screen_dump,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 109,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 4,
        .qstr_block_name_idx = 78,
        .line_info = fun_data_lcd160cr_LCD160CR_screen_dump + 13,
        .line_info_top = fun_data_lcd160cr_LCD160CR_screen_dump + 25,
        .opcodes = fun_data_lcd160cr_LCD160CR_screen_dump + 25,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_screen_dump fun_data_lcd160cr_LCD160CR_screen_dump[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_screen_load
static const byte fun_data_lcd160cr_LCD160CR_screen_load[40] = {
    0x42,0x12, // prelude
    0x4f,0x6c,0x81,0x0a, // names: screen_load, self, buf
    0x90,0x43,0x20,0x2e,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x47, // LOAD_METHOD 'set_spi_win'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR 'w'
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR 'h'
    0x36,0x04, // CALL_METHOD 4
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x48, // LOAD_METHOD 'fast_spi'
    0x36,0x00, // CALL_METHOD 0
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x42, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_screen_load = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_screen_load,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 40,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 79,
        .line_info = fun_data_lcd160cr_LCD160CR_screen_load + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_screen_load + 11,
        .opcodes = fun_data_lcd160cr_LCD160CR_screen_load + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_screen_load fun_data_lcd160cr_LCD160CR_screen_load[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_touch_config
static const byte fun_data_lcd160cr_LCD160CR_touch_config[67] = {
    0xc8,0x85,0x01,0x1e, // prelude
    0x50,0x6c,0x81,0x0c,0x81,0x0d,0x81,0x0e, // names: touch_config, self, calib, save, irq
    0x90,0x49,0x20,0x22,0x27,0x27,0x54, // code info
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb2, // LOAD_FAST 2
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0x42,0x45, // JUMP 5
    0xb3, // LOAD_FAST 3
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x03, // BUILD_LIST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xb4, // LOAD_FAST 4
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_touch_config = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_touch_config,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 67,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 80,
        .line_info = fun_data_lcd160cr_LCD160CR_touch_config + 12,
        .line_info_top = fun_data_lcd160cr_LCD160CR_touch_config + 19,
        .opcodes = fun_data_lcd160cr_LCD160CR_touch_config + 19,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_touch_config fun_data_lcd160cr_LCD160CR_touch_config[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_scroll
static const byte fun_data_lcd160cr_LCD160CR_set_scroll[32] = {
    0x32,0x0c, // prelude
    0x51,0x6c,0x76, // names: set_scroll, self, on
    0x90,0x52,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x10, // LOAD_CONST_SMALL_INT 144
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_scroll = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_scroll,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 32,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 81,
        .line_info = fun_data_lcd160cr_LCD160CR_set_scroll + 5,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_scroll + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_scroll + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_scroll fun_data_lcd160cr_LCD160CR_set_scroll[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_scroll_win
static const byte fun_data_lcd160cr_LCD160CR_set_scroll_win[88] = {
    0xba,0x90,0x84,0x80,0x01,0x34, // prelude
    0x52,0x6c,0x81,0x0f,0x79,0x7a,0x29,0x2a,0x81,0x10,0x81,0x11,0x78,0x81,0x12, // names: set_scroll_win, self, win, x, y, w, h, vec, pat, fill, color
    0x90,0x56,0x20,0x22,0x23,0x68,0x20,0x25,0x25,0x28,0x4d, // code info
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x87, // LOAD_CONST_SMALL_INT 7
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb7, // LOAD_FAST 7
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb8, // LOAD_FAST 8
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb8, // LOAD_FAST 8
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb9, // LOAD_FAST 9
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb9, // LOAD_FAST 9
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x0b, // BUILD_LIST 11
    0x34,0x01, // CALL_FUNCTION 1
    0xca, // STORE_FAST 10
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x11, // LOAD_CONST_SMALL_INT 145
    0xba, // LOAD_FAST 10
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_scroll_win = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_scroll_win,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 88,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 24,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 10,
        .n_kwonly_args = 0,
        .n_def_pos_args = 8,
        .qstr_block_name_idx = 82,
        .line_info = fun_data_lcd160cr_LCD160CR_set_scroll_win + 21,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_scroll_win + 32,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_scroll_win + 32,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_scroll_win fun_data_lcd160cr_LCD160CR_set_scroll_win[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_scroll_buf
static const byte fun_data_lcd160cr_LCD160CR_set_scroll_buf[13] = {
    0x1b,0x12, // prelude
    0x53,0x6c,0x81,0x0f,0x81,0x0a, // names: set_scroll_buf, self, win, buf
    0x90,0x65,0x40, // code info
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_scroll_buf = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_scroll_buf,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 83,
        .line_info = fun_data_lcd160cr_LCD160CR_set_scroll_buf + 8,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_scroll_buf + 11,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_scroll_buf + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_scroll_buf fun_data_lcd160cr_LCD160CR_set_scroll_buf[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_jpeg
static const byte fun_data_lcd160cr_LCD160CR_jpeg[83] = {
    0x52,0x14, // prelude
    0x54,0x6c,0x81,0x0a, // names: jpeg, self, buf
    0x90,0x6a,0x40,0x5f,0x2a,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x20, // LOAD_CONST_SMALL_INT 160
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x12,0x73, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x57, // JUMP 23
    0x57, // DUP_TOP
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb2, // LOAD_FAST 2
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xf2, // BINARY_OP 27 __add__
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x21, // LOAD_CONST_SMALL_INT 161
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x24, // POP_JUMP_IF_TRUE -28
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_jpeg = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_jpeg,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 83,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 84,
        .line_info = fun_data_lcd160cr_LCD160CR_jpeg + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_jpeg + 12,
        .opcodes = fun_data_lcd160cr_LCD160CR_jpeg + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_jpeg fun_data_lcd160cr_LCD160CR_jpeg[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_jpeg_start
static const byte fun_data_lcd160cr_LCD160CR_jpeg_start[34] = {
    0x42,0x0e, // prelude
    0x55,0x6c,0x81,0x13, // names: jpeg_start, self, total_len
    0x90,0x73,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x20, // LOAD_CONST_SMALL_INT 160
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x02, // BUILD_LIST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_jpeg_start = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_jpeg_start,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 34,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 85,
        .line_info = fun_data_lcd160cr_LCD160CR_jpeg_start + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_jpeg_start + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_jpeg_start + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_jpeg_start fun_data_lcd160cr_LCD160CR_jpeg_start[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_jpeg_data
static const byte fun_data_lcd160cr_LCD160CR_jpeg_data[21] = {
    0x2a,0x0e, // prelude
    0x56,0x6c,0x81,0x0a, // names: jpeg_data, self, buf
    0x90,0x77,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x21, // LOAD_CONST_SMALL_INT 161
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_jpeg_data = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_jpeg_data,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 21,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 86,
        .line_info = fun_data_lcd160cr_LCD160CR_jpeg_data + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_jpeg_data + 9,
        .opcodes = fun_data_lcd160cr_LCD160CR_jpeg_data + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_jpeg_data fun_data_lcd160cr_LCD160CR_jpeg_data[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_feed_wdt
static const byte fun_data_lcd160cr_LCD160CR_feed_wdt[18] = {
    0x19,0x0a, // prelude
    0x57,0x6c, // names: feed_wdt, self
    0x90,0x7b,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x30, // LOAD_CONST_SMALL_INT 176
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_feed_wdt = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_feed_wdt,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 87,
        .line_info = fun_data_lcd160cr_LCD160CR_feed_wdt + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_feed_wdt + 7,
        .opcodes = fun_data_lcd160cr_LCD160CR_feed_wdt + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_feed_wdt fun_data_lcd160cr_LCD160CR_feed_wdt[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_reset
static const byte fun_data_lcd160cr_LCD160CR_reset[26] = {
    0x21,0x0c, // prelude
    0x58,0x6c, // names: reset, self
    0x90,0x7f,0x20,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x12,0x04, // LOAD_GLOBAL 'sleep_ms'
    0x22,0x32, // LOAD_CONST_SMALL_INT 50
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_reset = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_reset,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 26,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 88,
        .line_info = fun_data_lcd160cr_LCD160CR_reset + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_reset + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_reset + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_reset fun_data_lcd160cr_LCD160CR_reset[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_uart_baudrate
static const byte fun_data_lcd160cr_LCD160CR_set_uart_baudrate[54] = {
    0x5a,0x10, // prelude
    0x59,0x6c,0x81,0x14, // names: set_uart_baudrate, self, baudrate
    0x90,0x84,0x20,0x25, // code info
    0xb1, // LOAD_FAST 1
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0xef, // BINARY_OP 24 __and__
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x40, // LOAD_CONST_SMALL_INT 192
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb2, // LOAD_FAST 2
    0x98, // LOAD_CONST_SMALL_INT 24
    0xf1, // BINARY_OP 26 __rshift__
    0xb2, // LOAD_FAST 2
    0x90, // LOAD_CONST_SMALL_INT 16
    0xf1, // BINARY_OP 26 __rshift__
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xb2, // LOAD_FAST 2
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_uart_baudrate = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_uart_baudrate,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 54,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 89,
        .line_info = fun_data_lcd160cr_LCD160CR_set_uart_baudrate + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_uart_baudrate + 10,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_uart_baudrate + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_uart_baudrate fun_data_lcd160cr_LCD160CR_set_uart_baudrate[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_startup_deco
static const byte fun_data_lcd160cr_LCD160CR_set_startup_deco[30] = {
    0x3a,0x0c, // prelude
    0x5a,0x6c,0x2b, // names: set_startup_deco, self, value
    0x90,0x89,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x41, // LOAD_CONST_SMALL_INT 193
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_startup_deco = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_startup_deco,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 30,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 90,
        .line_info = fun_data_lcd160cr_LCD160CR_set_startup_deco + 5,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_startup_deco + 8,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_startup_deco + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_startup_deco fun_data_lcd160cr_LCD160CR_set_startup_deco[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_save_to_flash
static const byte fun_data_lcd160cr_LCD160CR_save_to_flash[18] = {
    0x19,0x0a, // prelude
    0x5b,0x6c, // names: save_to_flash, self
    0x90,0x8d,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x42, // LOAD_CONST_SMALL_INT 194
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_save_to_flash = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_save_to_flash,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 18,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 91,
        .line_info = fun_data_lcd160cr_LCD160CR_save_to_flash + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR_save_to_flash + 7,
        .opcodes = fun_data_lcd160cr_LCD160CR_save_to_flash + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_save_to_flash fun_data_lcd160cr_LCD160CR_save_to_flash[0]
#endif

// child of lcd160cr_LCD160CR
// frozen bytecode for file lcd160cr.py, scope lcd160cr_LCD160CR_set_i2c_addr
static const byte fun_data_lcd160cr_LCD160CR_set_i2c_addr[36] = {
    0x3a,0x10, // prelude
    0x5c,0x6c,0x81,0x15, // names: set_i2c_addr, self, addr
    0x90,0x91,0x20,0x34, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x2c, // LOAD_METHOD '_send_cmd'
    0x22,0x81,0x43, // LOAD_CONST_SMALL_INT 195
    0x12,0x75, // LOAD_GLOBAL 'bytes'
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7e, // LOAD_CONST_SMALL_INT 254
    0xef, // BINARY_OP 24 __and__
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x10, // STORE_ATTR 'i2c_addr'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR_set_i2c_addr = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR_set_i2c_addr,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 36,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 92,
        .line_info = fun_data_lcd160cr_LCD160CR_set_i2c_addr + 6,
        .line_info_top = fun_data_lcd160cr_LCD160CR_set_i2c_addr + 10,
        .opcodes = fun_data_lcd160cr_LCD160CR_set_i2c_addr + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_lcd160cr_LCD160CR_set_i2c_addr fun_data_lcd160cr_LCD160CR_set_i2c_addr[0]
#endif

static const mp_raw_code_t *const children_lcd160cr_LCD160CR[] = {
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rgb,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR___init__,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR__send_cmd,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR__recv_cmd,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_power,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_orient,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_brightness,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_pen,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_erase,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_dot,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect_outline,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect_interior,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_line,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_dot_no_clip,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect_no_clip,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect_outline_no_clip,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_rect_interior_no_clip,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_line_no_clip,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_text_color,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_font,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_pos,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_write,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_is_touched,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_get_touch,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_spi_win,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_fast_spi,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_show_framebuf,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_pixel,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_get_pixel,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_get_line,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_screen_dump,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_screen_load,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_touch_config,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_scroll,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_scroll_win,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_scroll_buf,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_jpeg,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_jpeg_start,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_jpeg_data,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_feed_wdt,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_reset,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_uart_baudrate,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_startup_deco,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_save_to_flash,
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR_set_i2c_addr,
};

static const mp_raw_code_truncated_t proto_fun_lcd160cr_LCD160CR = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr_LCD160CR,
    .children = (void *)&children_lcd160cr_LCD160CR,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 362,
    .n_children = 46,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_lcd160cr_LCD160CR + 4,
        .line_info_top = fun_data_lcd160cr_LCD160CR + 99,
        .opcodes = fun_data_lcd160cr_LCD160CR + 99,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_lcd160cr__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_lcd160cr_LCD160CR,
};

static const mp_raw_code_truncated_t proto_fun_lcd160cr__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_lcd160cr__lt_module_gt_,
    .children = (void *)&children_lcd160cr__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 177,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 6,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_lcd160cr__lt_module_gt_ + 3,
        .line_info_top = fun_data_lcd160cr__lt_module_gt_ + 28,
        .opcodes = fun_data_lcd160cr__lt_module_gt_ + 28,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_lcd160cr[150] = {
    MP_QSTR_lcd160cr_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_const,
    MP_QSTR_micropython,
    MP_QSTR_sleep_ms,
    MP_QSTR_time,
    MP_QSTR_machine,
    MP_QSTR_Pin,
    MP_QSTR_I2C,
    MP_QSTR_SPI,
    MP_QSTR_SoftI2C,
    MP_QSTR_SoftSPI,
    MP_QSTR_LCD160CR,
    MP_QSTR_pwr,
    MP_QSTR_i2c,
    MP_QSTR_spi,
    MP_QSTR_i2c_addr,
    MP_QSTR_rgb,
    MP_QSTR___init__,
    MP_QSTR_X,
    MP_QSTR_X4,
    MP_QSTR_OUT,
    MP_QSTR_scl,
    MP_QSTR_X9,
    MP_QSTR_sda,
    MP_QSTR_X10,
    MP_QSTR_sck,
    MP_QSTR_X6,
    MP_QSTR_mosi,
    MP_QSTR_X8,
    MP_QSTR_miso,
    MP_QSTR_X7,
    MP_QSTR_Y,
    MP_QSTR_Y4,
    MP_QSTR_Y9,
    MP_QSTR_Y10,
    MP_QSTR_Y6,
    MP_QSTR_Y8,
    MP_QSTR_Y7,
    MP_QSTR_XY,
    MP_QSTR_YX,
    MP_QSTR_w,
    MP_QSTR_h,
    MP_QSTR_value,
    MP_QSTR__send_cmd,
    MP_QSTR_writeto,
    MP_QSTR__recv_cmd,
    MP_QSTR_readfrom,
    MP_QSTR_set_power,
    MP_QSTR_set_orient,
    MP_QSTR_set_brightness,
    MP_QSTR_set_pen,
    MP_QSTR_erase,
    MP_QSTR_dot,
    MP_QSTR_rect,
    MP_QSTR_rect_outline,
    MP_QSTR_rect_interior,
    MP_QSTR_line,
    MP_QSTR_dot_no_clip,
    MP_QSTR_rect_no_clip,
    MP_QSTR_rect_outline_no_clip,
    MP_QSTR_rect_interior_no_clip,
    MP_QSTR_line_no_clip,
    MP_QSTR_set_text_color,
    MP_QSTR_set_font,
    MP_QSTR_set_pos,
    MP_QSTR_write,
    MP_QSTR_encode,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR_is_touched,
    MP_QSTR_get_touch,
    MP_QSTR_set_spi_win,
    MP_QSTR_fast_spi,
    MP_QSTR_show_framebuf,
    MP_QSTR_set_pixel,
    MP_QSTR_get_pixel,
    MP_QSTR_get_line,
    MP_QSTR_readfrom_into,
    MP_QSTR_screen_dump,
    MP_QSTR_screen_load,
    MP_QSTR_touch_config,
    MP_QSTR_set_scroll,
    MP_QSTR_set_scroll_win,
    MP_QSTR_set_scroll_buf,
    MP_QSTR_jpeg,
    MP_QSTR_jpeg_start,
    MP_QSTR_jpeg_data,
    MP_QSTR_feed_wdt,
    MP_QSTR_reset,
    MP_QSTR_set_uart_baudrate,
    MP_QSTR_set_startup_deco,
    MP_QSTR_save_to_flash,
    MP_QSTR_set_i2c_addr,
    MP_QSTR_AttributeError,
    MP_QSTR_PORTRAIT,
    MP_QSTR_LANDSCAPE,
    MP_QSTR_PORTRAIT_UPSIDEDOWN,
    MP_QSTR_LANDSCAPE_UPSIDEDOWN,
    MP_QSTR_STARTUP_DECO_NONE,
    MP_QSTR_STARTUP_DECO_MLOGO,
    MP_QSTR_STARTUP_DECO_INFO,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_staticmethod,
    MP_QSTR_r,
    MP_QSTR_g,
    MP_QSTR_b,
    MP_QSTR_self,
    MP_QSTR_connect,
    MP_QSTR_ImportError,
    MP_QSTR_ValueError,
    MP_QSTR_cmd,
    MP_QSTR_data,
    MP_QSTR_bytearray,
    MP_QSTR_len,
    MP_QSTR_n_data,
    MP_QSTR_bytes,
    MP_QSTR_on,
    MP_QSTR_orient,
    MP_QSTR_fill,
    MP_QSTR_x,
    MP_QSTR_y,
    MP_QSTR_x1,
    MP_QSTR_y1,
    MP_QSTR_x2,
    MP_QSTR_y2,
    MP_QSTR_fg,
    MP_QSTR_bg,
    MP_QSTR_font,
    MP_QSTR_scale,
    MP_QSTR_bold,
    MP_QSTR_trans,
    MP_QSTR_scroll,
    MP_QSTR_s,
    MP_QSTR_isinstance,
    MP_QSTR_str,
    MP_QSTR_flush,
    MP_QSTR_buf,
    MP_QSTR_c,
    MP_QSTR_calib,
    MP_QSTR_save,
    MP_QSTR_irq,
    MP_QSTR_win,
    MP_QSTR_vec,
    MP_QSTR_pat,
    MP_QSTR_color,
    MP_QSTR_total_len,
    MP_QSTR_baudrate,
    MP_QSTR_addr,
};

// constants
static const mp_obj_str_t const_obj_lcd160cr_1 = {{&mp_type_str}, 26125, 38, (const byte*)"\x6d\x61\x63\x68\x69\x6e\x65\x2e\x50\x69\x6e\x20\x6e\x6f\x74\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x20\x69\x6e\x20\x74\x68\x69\x73\x20\x70\x6f\x72\x74"};
static const mp_obj_str_t const_obj_lcd160cr_2 = {{&mp_type_str}, 23803, 46, (const byte*)"\x6d\x61\x63\x68\x69\x6e\x65\x2e\x49\x32\x43\x2f\x53\x6f\x66\x74\x49\x32\x43\x20\x6e\x6f\x74\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x20\x69\x6e\x20\x74\x68\x69\x73\x20\x70\x6f\x72\x74"};
static const mp_obj_str_t const_obj_lcd160cr_3 = {{&mp_type_str}, 51387, 46, (const byte*)"\x6d\x61\x63\x68\x69\x6e\x65\x2e\x53\x50\x49\x2f\x53\x6f\x66\x74\x53\x50\x49\x20\x6e\x6f\x74\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x20\x69\x6e\x20\x74\x68\x69\x73\x20\x70\x6f\x72\x74"};
static const mp_obj_str_t const_obj_lcd160cr_5 = {{&mp_type_str}, 16010, 42, (const byte*)"\x6d\x75\x73\x74\x20\x73\x70\x65\x63\x69\x66\x79\x20\x65\x69\x74\x68\x65\x72\x20\x63\x6f\x6e\x6e\x65\x63\x74\x20\x6f\x72\x20\x70\x77\x72\x2c\x69\x32\x63\x2c\x73\x70\x69"};
static const mp_obj_str_t const_obj_lcd160cr_6 = {{&mp_type_bytes}, 46501, 1, (const byte*)"\x00"};
static const mp_rom_obj_tuple_t const_obj_lcd160cr_7 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(0),
    MP_ROM_INT(2),
}};
static const mp_rom_obj_tuple_t const_obj_lcd160cr_8 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(160),
    MP_ROM_INT(128),
}};
static const mp_rom_obj_tuple_t const_obj_lcd160cr_9 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(128),
    MP_ROM_INT(160),
}};
static const mp_obj_int_t const_obj_lcd160cr_10 = {{&mp_type_int}, {.neg=0, .fixed_dig=1, .alloc=2, .len=2, .dig=(uint16_t*)(const uint16_t[]){0xffff,0xffff}}};

// constant table
static const mp_rom_obj_t const_obj_table_data_lcd160cr[11] = {
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_lcd160cr_1),
    MP_ROM_PTR(&const_obj_lcd160cr_2),
    MP_ROM_PTR(&const_obj_lcd160cr_3),
    MP_ROM_QSTR(MP_QSTR_unknown_space_connect_space_value),
    MP_ROM_PTR(&const_obj_lcd160cr_5),
    MP_ROM_PTR(&const_obj_lcd160cr_6),
    MP_ROM_PTR(&const_obj_lcd160cr_7),
    MP_ROM_PTR(&const_obj_lcd160cr_8),
    MP_ROM_PTR(&const_obj_lcd160cr_9),
    MP_ROM_PTR(&const_obj_lcd160cr_10),
};

static const mp_frozen_module_t frozen_module_lcd160cr = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_lcd160cr,
        .obj_table = (mp_obj_t *)&const_obj_table_data_lcd160cr,
    },
    .proto_fun = &proto_fun_lcd160cr__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// collection of all frozen modules

const char mp_frozen_names[] = {
    #ifdef MP_FROZEN_STR_NAMES
    MP_FROZEN_STR_NAMES
    #endif
    "zlib.py\0"
    "gzip.py\0"
    "_thread.py\0"
    "ssl.py\0"
    "lcd160cr.py\0"
    "\0"
};

const mp_frozen_module_t *const mp_frozen_mpy_content[] = {
    &frozen_module_zlib,
    &frozen_module_gzip,
    &frozen_module__thread,
    &frozen_module_ssl,
    &frozen_module_lcd160cr,
};

#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("zlib", "zlib.py")
MICROPY_FROZEN_LIST_ITEM("gzip", "gzip.py")
MICROPY_FROZEN_LIST_ITEM("_thread", "_thread.py")
MICROPY_FROZEN_LIST_ITEM("ssl", "ssl.py")
MICROPY_FROZEN_LIST_ITEM("lcd160cr", "lcd160cr.py")
#endif

/*
byte sizes:
qstr content: 104 unique, 1254 bytes
bc content: 4112
const str content: 173
const int content: 4
const obj content: 96
const table qstr content: 0 entries, 0 bytes
const table ptr content: 12 entries, 48 bytes
raw code content: 74 * 4 = 1184
mp_frozen_mpy_names_content: 47
mp_frozen_mpy_content_size: 20
total: 6938
*/
