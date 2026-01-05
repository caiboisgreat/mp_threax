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
    MP_QSTR_LockType,
    MP_QSTR_SSLError,
    MP_QSTR__decode_wbits,
    MP_QSTR__locked,
    MP_QSTR__thread_dot_py,
    MP_QSTR__tls,
    MP_QSTR_acquire,
    MP_QSTR_allocate_lock,
    MP_QSTR_compress,
    MP_QSTR_create_default_context,
    MP_QSTR_decompress,
    MP_QSTR_exc,
    MP_QSTR_exc_type,
    MP_QSTR_filename,
    MP_QSTR_fileobj,
    MP_QSTR_get_ident,
    MP_QSTR_gzip_dot_py,
    MP_QSTR_locked,
    MP_QSTR_mode,
    MP_QSTR_rb,
    MP_QSTR_release,
    MP_QSTR_release_space_unlocked_space_lock,
    MP_QSTR_sock,
    MP_QSTR_ssl_dot_py,
    MP_QSTR_ssl_context,
    MP_QSTR_stack_size,
    MP_QSTR_start_new_thread,
    MP_QSTR_tb,
    MP_QSTR_waitflag,
    MP_QSTR_wbits,
    MP_QSTR_zlib_dot_py,
};

const qstr_hash_t mp_qstr_frozen_const_hashes[] = {
    48391,
    8246,
    27025,
    34514,
    15344,
    42611,
    3025,
    54045,
    60908,
    31395,
    1333,
    64354,
    9435,
    52220,
    21732,
    19460,
    45566,
    56646,
    47631,
    49190,
    28885,
    36844,
    51606,
    40913,
    48942,
    36681,
    15153,
    9687,
    28563,
    2338,
    27294,
    20191,
};

const qstr_len_t mp_qstr_frozen_const_lengths[] = {
    8,
    8,
    8,
    13,
    7,
    10,
    4,
    7,
    13,
    8,
    22,
    10,
    3,
    8,
    8,
    7,
    9,
    7,
    6,
    4,
    2,
    7,
    21,
    4,
    6,
    11,
    10,
    16,
    2,
    8,
    5,
    7,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    &mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    true, // is_sorted
    10, // allocated entries
    32, // used entries
    (qstr_hash_t *)mp_qstr_frozen_const_hashes,
    (qstr_len_t *)mp_qstr_frozen_const_lengths,
    {
        "GzipFile",
        "LockType",
        "SSLError",
        "_decode_wbits",
        "_locked",
        "_thread.py",
        "_tls",
        "acquire",
        "allocate_lock",
        "compress",
        "create_default_context",
        "decompress",
        "exc",
        "exc_type",
        "filename",
        "fileobj",
        "get_ident",
        "gzip.py",
        "locked",
        "mode",
        "rb",
        "release",
        "release unlocked lock",
        "sock",
        "ssl.py",
        "ssl_context",
        "stack_size",
        "start_new_thread",
        "tb",
        "waitflag",
        "wbits",
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
// collection of all frozen modules

const char mp_frozen_names[] = {
    #ifdef MP_FROZEN_STR_NAMES
    MP_FROZEN_STR_NAMES
    #endif
    "zlib.py\0"
    "gzip.py\0"
    "_thread.py\0"
    "ssl.py\0"
    "\0"
};

const mp_frozen_module_t *const mp_frozen_mpy_content[] = {
    &frozen_module_zlib,
    &frozen_module_gzip,
    &frozen_module__thread,
    &frozen_module_ssl,
};

#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("zlib", "zlib.py")
MICROPY_FROZEN_LIST_ITEM("gzip", "gzip.py")
MICROPY_FROZEN_LIST_ITEM("_thread", "_thread.py")
MICROPY_FROZEN_LIST_ITEM("ssl", "ssl.py")
#endif

/*
byte sizes:
qstr content: 32 unique, 397 bytes
bc content: 906
const str content: 0
const int content: 0
const obj content: 0
const table qstr content: 0 entries, 0 bytes
const table ptr content: 1 entries, 4 bytes
raw code content: 26 * 4 = 416
mp_frozen_mpy_names_content: 35
mp_frozen_mpy_content_size: 16
total: 1774
*/
