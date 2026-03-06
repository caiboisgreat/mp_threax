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
    MP_QSTR__0x0a_1_dot__space__0x6d4b__0x8bd5__space_greet_paren_open__paren_close_ = MP_QSTRnumber_of,
    MP_QSTR__0x0a_3_dot__space__0x6d4b__0x8bd5__space_DataBuffer,
    MP_QSTR__0x0a_4_dot__space__0x6d4b__0x8bd5__space_RingBuffer,
    MP_QSTR__0x0a_5_dot__space__0x6d4b__0x8bd5__space_MovingAverage,
    MP_QSTR__space__space_,
    MP_QSTR__space__space__space__0x2705__space__0x901a__0x8fc7_,
    MP_QSTR__space_0,
    MP_QSTR__comma_,
    MP_QSTR__dot_,
    MP_QSTR_0o,
    MP_QSTR_1_space_target_space_name_space__percent_s,
    MP_QSTR_1_dot_0_dot_0,
    MP_QSTR_2_space_target_space_name_space__percent_s,
    MP_QSTR_2026_hyphen_01_hyphen_28,
    MP_QSTR__colon_,
    MP_QSTR__equals_,
    MP_QSTR_ACK,
    MP_QSTR_ALLOW_1K_BLOCK,
    MP_QSTR_ALLOW_YMODEM_G,
    MP_QSTR_CAN,
    MP_QSTR_CRC,
    MP_QSTR_CaiBo,
    MP_QSTR_DEBUG,
    MP_QSTR_DEFAULT_CONFIG,
    MP_QSTR_DataBuffer,
    MP_QSTR_EOT,
    MP_QSTR_File_space__bracket_open__brace_open__brace_close__bracket_close__space_is_space_not_space_exists_dot_,
    MP_QSTR_FileNotFoundError,
    MP_QSTR_GzipFile,
    MP_QSTR_Hello,
    MP_QSTR_Hello_comma__space_Test_bang_,
    MP_QSTR_Hello_comma__space__brace_open__brace_close__bang_,
    MP_QSTR_IOError,
    MP_QSTR_LANDSCAPE_UPSIDEDOWN,
    MP_QSTR_LockType,
    MP_QSTR_Modem,
    MP_QSTR_MovingAverage,
    MP_QSTR_NAK,
    MP_QSTR_PORTRAIT_UPSIDEDOWN,
    MP_QSTR_Queue,
    MP_QSTR_RingBuffer,
    MP_QSTR_SOH,
    MP_QSTR_SSLError,
    MP_QSTR_STARTUP_DECO_INFO,
    MP_QSTR_STARTUP_DECO_MLOGO,
    MP_QSTR_STARTUP_DECO_NONE,
    MP_QSTR_STATUS_BUSY,
    MP_QSTR_STATUS_ERROR,
    MP_QSTR_STATUS_OK,
    MP_QSTR_STATUS_TIMEOUT,
    MP_QSTR_STX,
    MP_QSTR_Serial,
    MP_QSTR_TEST,
    MP_QSTR_Test,
    MP_QSTR_USE_DATE_FIELD,
    MP_QSTR_USE_LENGTH_FIELD,
    MP_QSTR_USE_MODE_FIELD,
    MP_QSTR_USE_SN_FIELD,
    MP_QSTR_Unix,
    MP_QSTR_World,
    MP_QSTR_X,
    MP_QSTR_XY,
    MP_QSTR_Y,
    MP_QSTR_YX,
    MP_QSTR__bracket_open_Sender_bracket_close__colon__space_Reached_space_EOF,
    MP_QSTR__bracket_open_Sender_bracket_close__colon__space_Received_space__percent_r,
    MP_QSTR__bracket_open_Sender_bracket_close__colon__space_data_colon__space__brace_open__brace_close_,
    MP_QSTR__bracket_open__bracket_close_,
    MP_QSTR__MAIN_UART_,
    MP_QSTR___author__,
    MP_QSTR___date__,
    MP_QSTR___deque,
    MP_QSTR___lock_queue,
    MP_QSTR___lock_signal,
    MP_QSTR___pop,
    MP_QSTR___put,
    MP_QSTR___version__,
    MP_QSTR__calc_checksum,
    MP_QSTR__calc_crc,
    MP_QSTR__check_path,
    MP_QSTR__decode_wbits,
    MP_QSTR__delete_failed_file,
    MP_QSTR__get_file_header,
    MP_QSTR__in_transfer_mode,
    MP_QSTR__locked,
    MP_QSTR__make_file_body_info,
    MP_QSTR__make_file_header_info,
    MP_QSTR__make_send_checksum,
    MP_QSTR__make_send_header,
    MP_QSTR__print,
    MP_QSTR__queue,
    MP_QSTR__recv_cmd,
    MP_QSTR__recv_file_mtime,
    MP_QSTR__recv_file_name,
    MP_QSTR__recv_mode,
    MP_QSTR__recv_sn,
    MP_QSTR__remaining_data_length,
    MP_QSTR__send_cmd,
    MP_QSTR__send_end_packet,
    MP_QSTR__thread,
    MP_QSTR__thread_dot_py,
    MP_QSTR__timer,
    MP_QSTR__timer_cb,
    MP_QSTR__tls,
    MP_QSTR__uart,
    MP_QSTR__uart_cb,
    MP_QSTR__verify_complement,
    MP_QSTR__verify_recv_checksum,
    MP_QSTR__wait_c,
    MP_QSTR__wait_nak_ack,
    MP_QSTR__wrapper,
    MP_QSTR_abort,
    MP_QSTR_acquire,
    MP_QSTR_allocate_lock,
    MP_QSTR_available,
    MP_QSTR_b,
    MP_QSTR_baud_rate,
    MP_QSTR_bg,
    MP_QSTR_bold,
    MP_QSTR_buadrate,
    MP_QSTR_buffer_size,
    MP_QSTR_c,
    MP_QSTR_calculate_checksum,
    MP_QSTR_calib,
    MP_QSTR_can_space_not_space_find_colon__space__squot__percent_s_squot_,
    MP_QSTR_char,
    MP_QSTR_check_file,
    MP_QSTR_checksum,
    MP_QSTR_clamp,
    MP_QSTR_cmd,
    MP_QSTR_compress,
    MP_QSTR_crc,
    MP_QSTR_crc_mode,
    MP_QSTR_crc_table,
    MP_QSTR_create_default_context,
    MP_QSTR_cyam,
    MP_QSTR_d,
    MP_QSTR_databits,
    MP_QSTR_debug,
    MP_QSTR_decompress,
    MP_QSTR_dot_no_clip,
    MP_QSTR_dstFile,
    MP_QSTR_empty,
    MP_QSTR_enter_ymodem,
    MP_QSTR_error_count,
    MP_QSTR_exc,
    MP_QSTR_exc_type,
    MP_QSTR_fast_spi,
    MP_QSTR_feed_wdt,
    MP_QSTR_fg,
    MP_QSTR_file_copy,
    MP_QSTR_file_type,
    MP_QSTR_filename,
    MP_QSTR_fileobj,
    MP_QSTR_filepath,
    MP_QSTR_filled,
    MP_QSTR_flowctl,
    MP_QSTR_font,
    MP_QSTR_free,
    MP_QSTR_func,
    MP_QSTR_g,
    MP_QSTR_get_ident,
    MP_QSTR_get_line,
    MP_QSTR_get_pixel,
    MP_QSTR_getsizeof,
    MP_QSTR_greet,
    MP_QSTR_gzip_dot_py,
    MP_QSTR_h,
    MP_QSTR_head,
    MP_QSTR_hex_dump,
    MP_QSTR_i,
    MP_QSTR_i2c,
    MP_QSTR_i2c_addr,
    MP_QSTR_in_max,
    MP_QSTR_in_min,
    MP_QSTR_indent,
    MP_QSTR_is_empty,
    MP_QSTR_is_full,
    MP_QSTR_item,
    MP_QSTR_jpeg,
    MP_QSTR_jpeg_data,
    MP_QSTR_jpeg_start,
    MP_QSTR_kimp,
    MP_QSTR_lcd160cr_dot_py,
    MP_QSTR_length,
    MP_QSTR_line_no_clip,
    MP_QSTR_ljust,
    MP_QSTR_localtime,
    MP_QSTR_locked,
    MP_QSTR_map_range,
    MP_QSTR_max_val,
    MP_QSTR_min_val,
    MP_QSTR_mkdirs,
    MP_QSTR_mktime,
    MP_QSTR_mtime,
    MP_QSTR_myutils_space__0x6a21__0x5757__0x81ea__0x6d4b__0x8bd5_,
    MP_QSTR_myutils_dot_py,
    MP_QSTR_n_data,
    MP_QSTR_nbytes,
    MP_QSTR_obj,
    MP_QSTR_offset,
    MP_QSTR_orient,
    MP_QSTR_out_max,
    MP_QSTR_out_min,
    MP_QSTR_packet_size,
    MP_QSTR_pat,
    MP_QSTR_path_dirname,
    MP_QSTR_path_exists,
    MP_QSTR_path_getsize,
    MP_QSTR_pos,
    MP_QSTR_print_dict,
    MP_QSTR_program,
    MP_QSTR_program_features,
    MP_QSTR_pwr,
    MP_QSTR_pyam,
    MP_QSTR_ql_fs,
    MP_QSTR_ql_fs_dot_py,
    MP_QSTR_queue,
    MP_QSTR_queue_dot_py,
    MP_QSTR_rbsb,
    MP_QSTR_read_json,
    MP_QSTR_reader,
    MP_QSTR_rect_interior,
    MP_QSTR_rect_interior_no_clip,
    MP_QSTR_rect_no_clip,
    MP_QSTR_rect_outline,
    MP_QSTR_rect_outline_no_clip,
    MP_QSTR_release,
    MP_QSTR_release_space_unlocked_space_lock,
    MP_QSTR_retry,
    MP_QSTR_rmdirs,
    MP_QSTR_rtos,
    MP_QSTR_rzsz,
    MP_QSTR_s,
    MP_QSTR_save,
    MP_QSTR_save_to_flash,
    MP_QSTR_scale,
    MP_QSTR_screen_dump,
    MP_QSTR_screen_load,
    MP_QSTR_self_test,
    MP_QSTR_send_file,
    MP_QSTR_sequence,
    MP_QSTR_serial_trans,
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
    MP_QSTR_source,
    MP_QSTR_source_colon__space__percent_s_comma__space_target_colon__space__percent_s,
    MP_QSTR_spi,
    MP_QSTR_srcFile,
    MP_QSTR_ssl_dot_py,
    MP_QSTR_ssl_context,
    MP_QSTR_stack_size,
    MP_QSTR_start_new_thread,
    MP_QSTR_stopbits,
    MP_QSTR_stream,
    MP_QSTR_success_count,
    MP_QSTR_tail,
    MP_QSTR_tb,
    MP_QSTR_total_len,
    MP_QSTR_total_size,
    MP_QSTR_touch,
    MP_QSTR_touch_config,
    MP_QSTR_trans,
    MP_QSTR_trans_file,
    MP_QSTR_trans_file_colon__space__percent_s,
    MP_QSTR_uart,
    MP_QSTR_ujson,
    MP_QSTR_unknown_space_connect_space_value,
    MP_QSTR_uos,
    MP_QSTR_utime,
    MP_QSTR_vec,
    MP_QSTR_w,
    MP_QSTR_waitflag,
    MP_QSTR_wb_plus_,
    MP_QSTR_wbits,
    MP_QSTR_win,
    MP_QSTR_window,
    MP_QSTR_window_size,
    MP_QSTR_wrapper,
    MP_QSTR_write_json,
    MP_QSTR_writer,
    MP_QSTR_x2,
    MP_QSTR_xmodem,
    MP_QSTR_xmodem1k,
    MP_QSTR_y2,
    MP_QSTR_ymodem,
    MP_QSTR_ymodem_dot_py,
    MP_QSTR_ymodem1k,
    MP_QSTR_zlib_dot_py,
    MP_QSTR__brace_open__colon_02x_brace_close_,
    MP_QSTR__brace_open__colon_08x_brace_close__colon__space__brace_open__brace_close__space__space__brace_open__brace_close_,
    MP_QSTR__0x6240__0x6709__0x6d4b__0x8bd5__0x901a__0x8fc7__bang__space__0x2705_,
};

const qstr_hash_t mp_qstr_frozen_const_hashes[] = {
    40922,
    17000,
    2317,
    51561,
    26117,
    4125,
    26133,
    46473,
    46475,
    26714,
    13108,
    27924,
    32727,
    44360,
    46495,
    46488,
    46924,
    36239,
    12,
    53129,
    53559,
    65315,
    27956,
    10683,
    17653,
    42971,
    546,
    35192,
    48391,
    11783,
    27932,
    22828,
    50363,
    16597,
    8246,
    33707,
    19090,
    54273,
    46337,
    4788,
    63863,
    5201,
    27025,
    4291,
    1067,
    44967,
    56627,
    51574,
    11242,
    23157,
    4474,
    58853,
    53043,
    21267,
    5008,
    54424,
    9447,
    53497,
    52847,
    4359,
    46589,
    30148,
    46588,
    29988,
    36994,
    38346,
    35230,
    30179,
    8227,
    26448,
    50641,
    26021,
    13696,
    47407,
    41162,
    40212,
    38975,
    11237,
    52634,
    11438,
    34514,
    27430,
    25813,
    49429,
    15344,
    3327,
    8272,
    27177,
    61179,
    43979,
    40843,
    25261,
    42150,
    4697,
    2148,
    44986,
    5930,
    31347,
    44097,
    724,
    42611,
    45725,
    10883,
    3025,
    14472,
    7990,
    59576,
    60706,
    9709,
    30524,
    9833,
    65359,
    54045,
    60908,
    28572,
    46535,
    8586,
    28352,
    15424,
    51829,
    54719,
    46534,
    7219,
    60864,
    44085,
    59101,
    48026,
    16968,
    36598,
    19503,
    31395,
    19735,
    58251,
    32310,
    1333,
    9747,
    46529,
    13145,
    21972,
    64354,
    30189,
    49600,
    57264,
    46181,
    14401,
    9435,
    52220,
    15088,
    26431,
    28228,
    24089,
    22756,
    21732,
    19460,
    48974,
    39979,
    58860,
    11158,
    15089,
    26651,
    46530,
    45566,
    10370,
    6052,
    9215,
    39076,
    56646,
    46541,
    24045,
    2819,
    46540,
    24413,
    7953,
    10889,
    11159,
    13945,
    10581,
    18707,
    8592,
    59261,
    4178,
    59938,
    410,
    42447,
    34649,
    20060,
    13745,
    18045,
    47631,
    4857,
    40213,
    59275,
    26991,
    11158,
    9213,
    25321,
    13633,
    56164,
    30418,
    23554,
    15432,
    33166,
    36160,
    35934,
    11223,
    29408,
    41167,
    2519,
    30788,
    29481,
    43057,
    40657,
    62089,
    28720,
    45024,
    59442,
    61269,
    4756,
    36147,
    60324,
    11248,
    20288,
    5322,
    32413,
    29554,
    7386,
    2701,
    36844,
    51606,
    685,
    36758,
    45759,
    52644,
    46550,
    33700,
    16143,
    20861,
    23962,
    59920,
    12720,
    27584,
    27482,
    63680,
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
    30904,
    30661,
    36303,
    61217,
    48942,
    36681,
    15153,
    9687,
    19921,
    54361,
    42586,
    41333,
    28563,
    41279,
    57757,
    58752,
    39189,
    17759,
    61478,
    39562,
    6775,
    12520,
    1144,
    26604,
    40421,
    31605,
    46546,
    2338,
    32347,
    27294,
    32693,
    50057,
    36051,
    3766,
    51135,
    48106,
    29007,
    51923,
    50473,
    29038,
    35314,
    18709,
    51208,
    20191,
    8355,
    49331,
    12682,
};

const qstr_len_t mp_qstr_frozen_const_lengths[] = {
    18,
    21,
    21,
    24,
    2,
    13,
    2,
    1,
    1,
    2,
    16,
    5,
    16,
    10,
    1,
    1,
    3,
    14,
    14,
    3,
    3,
    5,
    5,
    14,
    10,
    3,
    24,
    17,
    8,
    5,
    12,
    10,
    7,
    20,
    8,
    5,
    13,
    3,
    19,
    5,
    10,
    3,
    8,
    17,
    18,
    17,
    11,
    12,
    9,
    14,
    3,
    6,
    4,
    4,
    14,
    16,
    14,
    12,
    4,
    5,
    1,
    2,
    1,
    2,
    21,
    21,
    18,
    2,
    11,
    10,
    8,
    7,
    12,
    13,
    5,
    5,
    11,
    14,
    9,
    11,
    13,
    19,
    16,
    17,
    7,
    20,
    22,
    19,
    17,
    6,
    6,
    9,
    16,
    15,
    10,
    8,
    22,
    9,
    16,
    7,
    10,
    6,
    9,
    4,
    5,
    8,
    18,
    21,
    7,
    13,
    8,
    5,
    7,
    13,
    9,
    1,
    9,
    2,
    4,
    8,
    11,
    1,
    18,
    5,
    18,
    4,
    10,
    8,
    5,
    3,
    8,
    3,
    8,
    9,
    22,
    4,
    1,
    8,
    5,
    10,
    11,
    7,
    5,
    12,
    11,
    3,
    8,
    8,
    8,
    2,
    9,
    9,
    8,
    7,
    8,
    6,
    7,
    4,
    4,
    4,
    1,
    9,
    8,
    9,
    9,
    5,
    7,
    1,
    4,
    8,
    1,
    3,
    8,
    6,
    6,
    6,
    8,
    7,
    4,
    4,
    9,
    10,
    4,
    11,
    6,
    12,
    5,
    9,
    6,
    9,
    7,
    7,
    6,
    6,
    5,
    23,
    10,
    6,
    6,
    3,
    6,
    6,
    7,
    7,
    11,
    3,
    12,
    11,
    12,
    3,
    10,
    7,
    16,
    3,
    4,
    5,
    8,
    5,
    8,
    4,
    9,
    6,
    13,
    21,
    12,
    12,
    20,
    7,
    21,
    5,
    6,
    4,
    4,
    1,
    4,
    13,
    5,
    11,
    11,
    9,
    9,
    8,
    12,
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
    6,
    22,
    3,
    7,
    6,
    11,
    10,
    16,
    8,
    6,
    13,
    4,
    2,
    9,
    10,
    5,
    12,
    5,
    10,
    14,
    4,
    5,
    21,
    3,
    5,
    3,
    1,
    8,
    3,
    5,
    3,
    6,
    11,
    7,
    10,
    6,
    2,
    6,
    8,
    2,
    6,
    9,
    8,
    7,
    6,
    14,
    23,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    &mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    true, // is_sorted
    10, // allocated entries
    300, // used entries
    (qstr_hash_t *)mp_qstr_frozen_const_hashes,
    (qstr_len_t *)mp_qstr_frozen_const_lengths,
    {
        "\x0a\x31\x2e\x20\xe6\xb5\x8b\xe8\xaf\x95\x20\x67\x72\x65\x65\x74\x28\x29",
        "\x0a\x33\x2e\x20\xe6\xb5\x8b\xe8\xaf\x95\x20\x44\x61\x74\x61\x42\x75\x66\x66\x65\x72",
        "\x0a\x34\x2e\x20\xe6\xb5\x8b\xe8\xaf\x95\x20\x52\x69\x6e\x67\x42\x75\x66\x66\x65\x72",
        "\x0a\x35\x2e\x20\xe6\xb5\x8b\xe8\xaf\x95\x20\x4d\x6f\x76\x69\x6e\x67\x41\x76\x65\x72\x61\x67\x65",
        "  ",
        "\x20\x20\x20\xe2\x9c\x85\x20\xe9\x80\x9a\xe8\xbf\x87",
        " 0",
        ",",
        ".",
        "0o",
        "1 target name %s",
        "1.0.0",
        "2 target name %s",
        "2026-01-28",
        ":",
        "=",
        "ACK",
        "ALLOW_1K_BLOCK",
        "ALLOW_YMODEM_G",
        "CAN",
        "CRC",
        "CaiBo",
        "DEBUG",
        "DEFAULT_CONFIG",
        "DataBuffer",
        "EOT",
        "File [{}] is not exists.",
        "FileNotFoundError",
        "GzipFile",
        "Hello",
        "Hello, Test!",
        "Hello, {}!",
        "IOError",
        "LANDSCAPE_UPSIDEDOWN",
        "LockType",
        "Modem",
        "MovingAverage",
        "NAK",
        "PORTRAIT_UPSIDEDOWN",
        "Queue",
        "RingBuffer",
        "SOH",
        "SSLError",
        "STARTUP_DECO_INFO",
        "STARTUP_DECO_MLOGO",
        "STARTUP_DECO_NONE",
        "STATUS_BUSY",
        "STATUS_ERROR",
        "STATUS_OK",
        "STATUS_TIMEOUT",
        "STX",
        "Serial",
        "TEST",
        "Test",
        "USE_DATE_FIELD",
        "USE_LENGTH_FIELD",
        "USE_MODE_FIELD",
        "USE_SN_FIELD",
        "Unix",
        "World",
        "X",
        "XY",
        "Y",
        "YX",
        "[Sender]: Reached EOF",
        "[Sender]: Received %r",
        "[Sender]: data: {}",
        "[]",
        "_MAIN_UART_",
        "__author__",
        "__date__",
        "__deque",
        "__lock_queue",
        "__lock_signal",
        "__pop",
        "__put",
        "__version__",
        "_calc_checksum",
        "_calc_crc",
        "_check_path",
        "_decode_wbits",
        "_delete_failed_file",
        "_get_file_header",
        "_in_transfer_mode",
        "_locked",
        "_make_file_body_info",
        "_make_file_header_info",
        "_make_send_checksum",
        "_make_send_header",
        "_print",
        "_queue",
        "_recv_cmd",
        "_recv_file_mtime",
        "_recv_file_name",
        "_recv_mode",
        "_recv_sn",
        "_remaining_data_length",
        "_send_cmd",
        "_send_end_packet",
        "_thread",
        "_thread.py",
        "_timer",
        "_timer_cb",
        "_tls",
        "_uart",
        "_uart_cb",
        "_verify_complement",
        "_verify_recv_checksum",
        "_wait_c",
        "_wait_nak_ack",
        "_wrapper",
        "abort",
        "acquire",
        "allocate_lock",
        "available",
        "b",
        "baud_rate",
        "bg",
        "bold",
        "buadrate",
        "buffer_size",
        "c",
        "calculate_checksum",
        "calib",
        "can not find: '%s'",
        "char",
        "check_file",
        "checksum",
        "clamp",
        "cmd",
        "compress",
        "crc",
        "crc_mode",
        "crc_table",
        "create_default_context",
        "cyam",
        "d",
        "databits",
        "debug",
        "decompress",
        "dot_no_clip",
        "dstFile",
        "empty",
        "enter_ymodem",
        "error_count",
        "exc",
        "exc_type",
        "fast_spi",
        "feed_wdt",
        "fg",
        "file_copy",
        "file_type",
        "filename",
        "fileobj",
        "filepath",
        "filled",
        "flowctl",
        "font",
        "free",
        "func",
        "g",
        "get_ident",
        "get_line",
        "get_pixel",
        "getsizeof",
        "greet",
        "gzip.py",
        "h",
        "head",
        "hex_dump",
        "i",
        "i2c",
        "i2c_addr",
        "in_max",
        "in_min",
        "indent",
        "is_empty",
        "is_full",
        "item",
        "jpeg",
        "jpeg_data",
        "jpeg_start",
        "kimp",
        "lcd160cr.py",
        "length",
        "line_no_clip",
        "ljust",
        "localtime",
        "locked",
        "map_range",
        "max_val",
        "min_val",
        "mkdirs",
        "mktime",
        "mtime",
        "\x6d\x79\x75\x74\x69\x6c\x73\x20\xe6\xa8\xa1\xe5\x9d\x97\xe8\x87\xaa\xe6\xb5\x8b\xe8\xaf\x95",
        "myutils.py",
        "n_data",
        "nbytes",
        "obj",
        "offset",
        "orient",
        "out_max",
        "out_min",
        "packet_size",
        "pat",
        "path_dirname",
        "path_exists",
        "path_getsize",
        "pos",
        "print_dict",
        "program",
        "program_features",
        "pwr",
        "pyam",
        "ql_fs",
        "ql_fs.py",
        "queue",
        "queue.py",
        "rbsb",
        "read_json",
        "reader",
        "rect_interior",
        "rect_interior_no_clip",
        "rect_no_clip",
        "rect_outline",
        "rect_outline_no_clip",
        "release",
        "release unlocked lock",
        "retry",
        "rmdirs",
        "rtos",
        "rzsz",
        "s",
        "save",
        "save_to_flash",
        "scale",
        "screen_dump",
        "screen_load",
        "self_test",
        "send_file",
        "sequence",
        "serial_trans",
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
        "source",
        "source: %s, target: %s",
        "spi",
        "srcFile",
        "ssl.py",
        "ssl_context",
        "stack_size",
        "start_new_thread",
        "stopbits",
        "stream",
        "success_count",
        "tail",
        "tb",
        "total_len",
        "total_size",
        "touch",
        "touch_config",
        "trans",
        "trans_file",
        "trans_file: %s",
        "uart",
        "ujson",
        "unknown connect value",
        "uos",
        "utime",
        "vec",
        "w",
        "waitflag",
        "wb+",
        "wbits",
        "win",
        "window",
        "window_size",
        "wrapper",
        "write_json",
        "writer",
        "x2",
        "xmodem",
        "xmodem1k",
        "y2",
        "ymodem",
        "ymodem.py",
        "ymodem1k",
        "zlib.py",
        "{:02x}",
        "{:08x}: {}  {}",
        "\xe6\x89\x80\xe6\x9c\x89\xe6\xb5\x8b\xe8\xaf\x95\xe9\x80\x9a\xe8\xbf\x87\x21\x20\xe2\x9c\x85",
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
static const byte fun_data__thread__lt_module_gt_[53] = {
    0x10,0x1c, // prelude
    0x01, // names: <module>
    0x80,0x09,0x46,0x89,0x1f,0x64,0x20,0x64,0x20,0x64,0x20,0x64,0x40, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'utime'
    0x16,0x11, // STORE_NAME 'time'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x03, // LOAD_CONST_STRING 'LockType'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x03, // STORE_NAME 'LockType'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x04, // STORE_NAME 'allocate_lock'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x05, // STORE_NAME 'start_new_thread'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x06, // STORE_NAME 'get_ident'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x07, // STORE_NAME 'stack_size'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x08, // STORE_NAME 'exit'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of _thread__lt_module_gt_
// frozen bytecode for file _thread.py, scope _thread_LockType
static const byte fun_data__thread_LockType[51] = {
    0x08,0x16, // prelude
    0x03, // names: LockType
    0x88,0x0c,0x64,0x64,0x88,0x0a,0x64,0x40,0x64,0x20, // code info
    0x11,0x12, // LOAD_NAME '__name__'
    0x16,0x13, // STORE_NAME '__module__'
    0x10,0x03, // LOAD_CONST_STRING 'LockType'
    0x16,0x14, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x09, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0b, // STORE_NAME 'locked'
    0x52, // LOAD_CONST_TRUE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x0c, // STORE_NAME 'acquire'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0e, // STORE_NAME 'release'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x0f, // STORE_NAME '__enter__'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x10, // STORE_NAME '__exit__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of _thread_LockType
// frozen bytecode for file _thread.py, scope _thread_LockType___init__
static const byte fun_data__thread_LockType___init__[12] = {
    0x11,0x08, // prelude
    0x09,0x17, // names: __init__, self
    0x80,0x0d, // code info
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x0a, // STORE_ATTR '_locked'
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
        .qstr_block_name_idx = 9,
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
    0x0b,0x17, // names: locked, self
    0x80,0x10, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR '_locked'
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
        .qstr_block_name_idx = 11,
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
static const byte fun_data__thread_LockType_acquire[45] = {
    0xa2,0x01,0x16, // prelude
    0x0c,0x17,0x18, // names: acquire, self, waitflag
    0x80,0x14,0x25,0x23,0x22,0x22,0x2d,0x24, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR '_locked'
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb1, // LOAD_FAST 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0x48, // JUMP 8
    0x12,0x11, // LOAD_GLOBAL 'time'
    0x14,0x0d, // LOAD_METHOD 'sleep_ms'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR '_locked'
    0x43,0x33, // POP_JUMP_IF_TRUE -13
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x0a, // STORE_ATTR '_locked'
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
    .fun_data_len = 45,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 12,
        .line_info = fun_data__thread_LockType_acquire + 6,
        .line_info_top = fun_data__thread_LockType_acquire + 14,
        .opcodes = fun_data__thread_LockType_acquire + 14,
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
    0x0e,0x17, // names: release, self
    0x80,0x1d,0x25,0x27, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x0a, // LOAD_ATTR '_locked'
    0x43,0x47, // POP_JUMP_IF_TRUE 7
    0x12,0x19, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x0a, // STORE_ATTR '_locked'
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
        .qstr_block_name_idx = 14,
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
    0x0f,0x17, // names: __enter__, self
    0x80,0x22,0x27, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0c, // LOAD_METHOD 'acquire'
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
        .qstr_block_name_idx = 15,
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
    0x10,0x17,0x1a,0x1b,0x1c, // names: __exit__, self, exc_type, exc, tb
    0x80,0x26,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x0e, // LOAD_METHOD 'release'
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
        .qstr_block_name_idx = 16,
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
        .qstr_block_name_idx = 3,
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
    0x04, // names: allocate_lock
    0x80,0x2b, // code info
    0x12,0x03, // LOAD_GLOBAL 'LockType'
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
        .qstr_block_name_idx = 4,
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
    0x05, // names: start_new_thread
    0x80,0x2f, // code info
    0x12,0x15, // LOAD_GLOBAL 'NotImplementedError'
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
        .qstr_block_name_idx = 5,
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
    0x06, // names: get_ident
    0x80,0x33, // code info
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
        .qstr_block_name_idx = 6,
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
    0x07, // names: stack_size
    0x80,0x38, // code info
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
        .qstr_block_name_idx = 7,
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
    0x08, // names: exit
    0x80,0x3c, // code info
    0x12,0x16, // LOAD_GLOBAL 'SystemExit'
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
        .qstr_block_name_idx = 8,
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
    .fun_data_len = 53,
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
        .line_info_top = fun_data__thread__lt_module_gt_ + 16,
        .opcodes = fun_data__thread__lt_module_gt_ + 16,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data__thread[29] = {
    MP_QSTR__thread_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_utime,
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
    MP_QSTR_sleep_ms,
    MP_QSTR_release,
    MP_QSTR___enter__,
    MP_QSTR___exit__,
    MP_QSTR_time,
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
// frozen module myutils
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\myutils.mpy
// - frozen file name: myutils.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file myutils.py, scope myutils__lt_module_gt_
static const byte fun_data_myutils__lt_module_gt_[177] = {
    0x10,0x52, // prelude
    0x01, // names: <module>
    0x80,0x12,0x24,0x24,0x84,0x07,0x23,0x23,0x63,0x22,0x27,0x26,0x26,0x66,0x20,0x23,0x23,0x23,0x63,0x60,0x89,0x10,0x84,0x14,0x88,0x20,0x84,0x14,0x84,0x16,0x89,0x56,0x89,0x4e,0x89,0x3e,0x88,0x10,0x84,0x20, // code info
    0x10,0x02, // LOAD_CONST_STRING '1.0.0'
    0x16,0x40, // STORE_NAME '__version__'
    0x10,0x03, // LOAD_CONST_STRING 'CaiBo'
    0x16,0x41, // STORE_NAME '__author__'
    0x10,0x04, // LOAD_CONST_STRING '2026-01-28'
    0x16,0x42, // STORE_NAME '__date__'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x43, // STORE_NAME 'LED_RED'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x44, // STORE_NAME 'LED_GREEN'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x45, // STORE_NAME 'LED_BLUE'
    0x2c,0x04, // BUILD_MAP 4
    0x22,0x87,0x84,0x00, // LOAD_CONST_SMALL_INT 115200
    0x10,0x05, // LOAD_CONST_STRING 'baud_rate'
    0x62, // STORE_MAP
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x10,0x06, // LOAD_CONST_STRING 'timeout'
    0x62, // STORE_MAP
    0x22,0x82,0x00, // LOAD_CONST_SMALL_INT 256
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x62, // STORE_MAP
    0x50, // LOAD_CONST_FALSE
    0x10,0x07, // LOAD_CONST_STRING 'debug'
    0x62, // STORE_MAP
    0x16,0x46, // STORE_NAME 'DEFAULT_CONFIG'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x16,0x47, // STORE_NAME 'STATUS_OK'
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x16,0x48, // STORE_NAME 'STATUS_ERROR'
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x16,0x49, // STORE_NAME 'STATUS_TIMEOUT'
    0x7d, // LOAD_CONST_SMALL_INT -3
    0x16,0x4a, // STORE_NAME 'STATUS_BUSY'
    0x10,0x08, // LOAD_CONST_STRING 'World'
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x0c, // STORE_NAME 'greet'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x0f, // STORE_NAME 'calculate_checksum'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x11, // STORE_NAME 'hex_dump'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x18, // STORE_NAME 'clamp'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x19, // STORE_NAME 'map_range'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x05, // MAKE_FUNCTION 5
    0x10,0x09, // LOAD_CONST_STRING 'DataBuffer'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x09, // STORE_NAME 'DataBuffer'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x06, // MAKE_FUNCTION 6
    0x10,0x0a, // LOAD_CONST_STRING 'RingBuffer'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0a, // STORE_NAME 'RingBuffer'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x07, // MAKE_FUNCTION 7
    0x10,0x0b, // LOAD_CONST_STRING 'MovingAverage'
    0x34,0x02, // CALL_FUNCTION 2
    0x16,0x0b, // STORE_NAME 'MovingAverage'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x08, // MAKE_FUNCTION_DEFARGS 8
    0x16,0x1a, // STORE_NAME 'print_dict'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x1f, // STORE_NAME 'sizeof'
    0x32,0x0a, // MAKE_FUNCTION 10
    0x16,0x22, // STORE_NAME 'self_test'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_greet
static const byte fun_data_myutils_greet[17] = {
    0x99,0x01,0x0c, // prelude
    0x0c,0x4b, // names: greet, name
    0x80,0x32,0x80,0x0d, // code info
    0x10,0x0d, // LOAD_CONST_STRING 'Hello, {}!'
    0x14,0x0e, // LOAD_METHOD 'format'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_greet = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_greet,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_myutils_greet + 5,
        .line_info_top = fun_data_myutils_greet + 9,
        .opcodes = fun_data_myutils_greet + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_greet fun_data_myutils_greet[0]
#endif

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_calculate_checksum
static const byte fun_data_myutils_calculate_checksum[35] = {
    0x19,0x10, // prelude
    0x0f,0x4c, // names: calculate_checksum, data
    0x80,0x42,0x80,0x0f,0x29,0x26, // code info
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x14,0x10, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc0, // STORE_FAST 0
    0x12,0x3d, // LOAD_GLOBAL 'sum'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_calculate_checksum = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_calculate_checksum,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 35,
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
        .qstr_block_name_idx = 15,
        .line_info = fun_data_myutils_calculate_checksum + 4,
        .line_info_top = fun_data_myutils_calculate_checksum + 10,
        .opcodes = fun_data_myutils_calculate_checksum + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_calculate_checksum fun_data_myutils_calculate_checksum[0]
#endif

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_hex_dump
static const byte fun_data_myutils_hex_dump[127] = {
    0x82,0x11,0x22, // prelude
    0x11,0x4c,0x4f, // names: hex_dump, data, width
    0x80,0x56,0x80,0x0b,0x29,0x46,0x23,0x2f,0x69,0x2d,0x6b,0x6d,0x2a,0x4a, // code info
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x14,0x10, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc0, // STORE_FAST 0
    0x2b,0x00, // BUILD_LIST 0
    0xc2, // STORE_FAST 2
    0x12,0x50, // LOAD_GLOBAL 'range'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x12,0x51, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0xb1, // LOAD_FAST 1
    0x34,0x03, // CALL_FUNCTION 3
    0x5f, // GET_ITER_STACK
    0x4b,0x43, // FOR_ITER 67
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0xb3, // LOAD_FAST 3
    0xb3, // LOAD_FAST 3
    0xb1, // LOAD_FAST 1
    0xf2, // BINARY_OP 27 __add__
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc4, // STORE_FAST 4
    0x10,0x12, // LOAD_CONST_STRING ' '
    0x14,0x13, // LOAD_METHOD 'join'
    0x32,0x00, // MAKE_FUNCTION 0
    0xb4, // LOAD_FAST 4
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x14,0x14, // LOAD_METHOD 'ljust'
    0xb1, // LOAD_FAST 1
    0x83, // LOAD_CONST_SMALL_INT 3
    0xf4, // BINARY_OP 29 __mul__
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf3, // BINARY_OP 28 __sub__
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0x10,0x15, // LOAD_CONST_STRING ''
    0x14,0x13, // LOAD_METHOD 'join'
    0x32,0x01, // MAKE_FUNCTION 1
    0xb4, // LOAD_FAST 4
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0xc6, // STORE_FAST 6
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x14,0x0e, // LOAD_METHOD 'format'
    0xb3, // LOAD_FAST 3
    0xb5, // LOAD_FAST 5
    0xb6, // LOAD_FAST 6
    0x36,0x03, // CALL_METHOD 3
    0xc7, // STORE_FAST 7
    0xb2, // LOAD_FAST 2
    0x14,0x16, // LOAD_METHOD 'append'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0xbb,0x7f, // JUMP -69
    0x10,0x17, // LOAD_CONST_STRING '\n'
    0x14,0x13, // LOAD_METHOD 'join'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
// child of myutils_hex_dump
// frozen bytecode for file myutils.py, scope myutils_hex_dump__lt_genexpr_gt_
static const byte fun_data_myutils_hex_dump__lt_genexpr_gt_[27] = {
    0xc1,0x40,0x08, // prelude
    0x2c,0x69, // names: <genexpr>, *
    0x80,0x69, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0c, // FOR_ITER 12
    0xc1, // STORE_FAST 1
    0x10,0x2d, // LOAD_CONST_STRING '{:02x}'
    0x14,0x0e, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x32, // JUMP -14
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_hex_dump__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_myutils_hex_dump__lt_genexpr_gt_,
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
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_myutils_hex_dump__lt_genexpr_gt_ + 5,
        .line_info_top = fun_data_myutils_hex_dump__lt_genexpr_gt_ + 7,
        .opcodes = fun_data_myutils_hex_dump__lt_genexpr_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_hex_dump__lt_genexpr_gt_ fun_data_myutils_hex_dump__lt_genexpr_gt_[0]
#endif

// child of myutils_hex_dump
// frozen bytecode for file myutils.py, scope myutils_hex_dump__lt_genexpr_gt_2
static const byte fun_data_myutils_hex_dump__lt_genexpr_gt_2[46] = {
    0xc1,0x40,0x08, // prelude
    0x2c,0x69, // names: <genexpr>, *
    0x80,0x6d, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x1f, // FOR_ITER 31
    0xc1, // STORE_FAST 1
    0xa0, // LOAD_CONST_SMALL_INT 32
    0xb1, // LOAD_FAST 1
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xda, // BINARY_OP 3 __le__
    0x46,0x06, // JUMP_IF_FALSE_OR_POP 6
    0x22,0x80,0x7f, // LOAD_CONST_SMALL_INT 127
    0xd7, // BINARY_OP 0 __lt__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x6a, // LOAD_GLOBAL 'chr'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x42,0x42, // JUMP 2
    0x10,0x2e, // LOAD_CONST_STRING '.'
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x1f, // JUMP -33
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_hex_dump__lt_genexpr_gt_2 = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_myutils_hex_dump__lt_genexpr_gt_2,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_myutils_hex_dump__lt_genexpr_gt_2 + 5,
        .line_info_top = fun_data_myutils_hex_dump__lt_genexpr_gt_2 + 7,
        .opcodes = fun_data_myutils_hex_dump__lt_genexpr_gt_2 + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_hex_dump__lt_genexpr_gt_2 fun_data_myutils_hex_dump__lt_genexpr_gt_2[0]
#endif

static const mp_raw_code_t *const children_myutils_hex_dump[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_hex_dump__lt_genexpr_gt_,
    (const mp_raw_code_t *)&proto_fun_myutils_hex_dump__lt_genexpr_gt_2,
};

static const mp_raw_code_truncated_t proto_fun_myutils_hex_dump = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_hex_dump,
    .children = (void *)&children_myutils_hex_dump,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 127,
    .n_children = 2,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 17,
        .line_info = fun_data_myutils_hex_dump + 6,
        .line_info_top = fun_data_myutils_hex_dump + 20,
        .opcodes = fun_data_myutils_hex_dump + 20,
    },
    #endif
    #endif
};

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_clamp
static const byte fun_data_myutils_clamp[22] = {
    0x3b,0x10, // prelude
    0x18,0x52,0x53,0x54, // names: clamp, value, min_val, max_val
    0x80,0x76,0x80,0x11, // code info
    0x12,0x55, // LOAD_GLOBAL 'max'
    0xb1, // LOAD_FAST 1
    0x12,0x56, // LOAD_GLOBAL 'min'
    0xb0, // LOAD_FAST 0
    0xb2, // LOAD_FAST 2
    0x34,0x02, // CALL_FUNCTION 2
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_clamp = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_clamp,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
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
        .qstr_block_name_idx = 24,
        .line_info = fun_data_myutils_clamp + 6,
        .line_info_top = fun_data_myutils_clamp + 10,
        .opcodes = fun_data_myutils_clamp + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_clamp fun_data_myutils_clamp[0]
#endif

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_map_range
static const byte fun_data_myutils_map_range[27] = {
    0xb9,0x04,0x14, // prelude
    0x19,0x52,0x57,0x58,0x59,0x5a, // names: map_range, value, in_min, in_max, out_min, out_max
    0x80,0x8a,0x80,0x0f, // code info
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0xf3, // BINARY_OP 28 __sub__
    0xb4, // LOAD_FAST 4
    0xb3, // LOAD_FAST 3
    0xf3, // BINARY_OP 28 __sub__
    0xf4, // BINARY_OP 29 __mul__
    0xb2, // LOAD_FAST 2
    0xb1, // LOAD_FAST 1
    0xf3, // BINARY_OP 28 __sub__
    0xf7, // BINARY_OP 32 __truediv__
    0xb3, // LOAD_FAST 3
    0xf2, // BINARY_OP 27 __add__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_map_range = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_map_range,
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
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 25,
        .line_info = fun_data_myutils_map_range + 9,
        .line_info_top = fun_data_myutils_map_range + 13,
        .opcodes = fun_data_myutils_map_range + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_map_range fun_data_myutils_map_range[0]
#endif

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_DataBuffer
static const byte fun_data_myutils_DataBuffer[73] = {
    0x08,0x26, // prelude
    0x09, // names: DataBuffer
    0x88,0xa0,0x80,0x0b,0x8a,0x0b,0x84,0x18,0x88,0x11,0x64,0x60,0x64,0x20,0x64,0x20,0x64,0x20, // code info
    0x11,0x5b, // LOAD_NAME '__name__'
    0x16,0x5c, // STORE_NAME '__module__'
    0x10,0x09, // LOAD_CONST_STRING 'DataBuffer'
    0x16,0x5d, // STORE_NAME '__qualname__'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x2f, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x27, // STORE_NAME 'write'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x2a, // STORE_NAME 'read'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x33, // STORE_NAME 'clear'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x29, // STORE_NAME 'available'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x34, // STORE_NAME 'free'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x35, // STORE_NAME 'is_full'
    0x32,0x07, // MAKE_FUNCTION 7
    0x16,0x36, // STORE_NAME 'is_empty'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer___init__
static const byte fun_data_myutils_DataBuffer___init__[30] = {
    0x9a,0x01,0x12, // prelude
    0x2f,0x6b,0x32, // names: __init__, self, size
    0x80,0xac,0x60,0x60,0x28,0x24, // code info
    0x12,0x64, // LOAD_GLOBAL 'bytearray'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x30, // STORE_ATTR 'buffer'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x31, // STORE_ATTR 'pos'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x32, // STORE_ATTR 'size'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer___init__,
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
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 47,
        .line_info = fun_data_myutils_DataBuffer___init__ + 6,
        .line_info_top = fun_data_myutils_DataBuffer___init__ + 12,
        .opcodes = fun_data_myutils_DataBuffer___init__ + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer___init__ fun_data_myutils_DataBuffer___init__[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_write
static const byte fun_data_myutils_DataBuffer_write[82] = {
    0x52,0x20, // prelude
    0x27,0x6b,0x4c, // names: write, self, data
    0x80,0xb7,0x80,0x09,0x29,0x46,0x22,0x25,0x29,0x28,0x29,0x46,0x48, // code info
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb1, // LOAD_FAST 1
    0x14,0x10, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x5f, // GET_ITER_STACK
    0x4b,0x29, // FOR_ITER 41
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x31, // LOAD_ATTR 'pos'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x31, // STORE_ATTR 'pos'
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x42,0x46, // JUMP 6
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x15, // JUMP -43
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 82,
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
        .qstr_block_name_idx = 39,
        .line_info = fun_data_myutils_DataBuffer_write + 5,
        .line_info_top = fun_data_myutils_DataBuffer_write + 18,
        .opcodes = fun_data_myutils_DataBuffer_write + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_write fun_data_myutils_DataBuffer_write[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_read
static const byte fun_data_myutils_DataBuffer_read[46] = {
    0xaa,0x01,0x14, // prelude
    0x2a,0x6b,0x6c, // names: read, self, length
    0x80,0xcf,0x80,0x09,0x25,0x46,0x49, // code info
    0xb1, // LOAD_FAST 1
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0xc1, // STORE_FAST 1
    0x42,0x49, // JUMP 9
    0x12,0x56, // LOAD_GLOBAL 'min'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0x34,0x02, // CALL_FUNCTION 2
    0xc1, // STORE_FAST 1
    0x12,0x63, // LOAD_GLOBAL 'bytes'
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0x51, // LOAD_CONST_NONE
    0xb1, // LOAD_FAST 1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 42,
        .line_info = fun_data_myutils_DataBuffer_read + 6,
        .line_info_top = fun_data_myutils_DataBuffer_read + 13,
        .opcodes = fun_data_myutils_DataBuffer_read + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_read fun_data_myutils_DataBuffer_read[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_clear
static const byte fun_data_myutils_DataBuffer_clear[38] = {
    0x31,0x0e, // prelude
    0x33,0x6b, // names: clear, self
    0x80,0xe0,0x20,0x24,0x28, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x31, // STORE_ATTR 'pos'
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x4a, // JUMP 10
    0x57, // DUP_TOP
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0xb1, // LOAD_FAST 1
    0x56, // STORE_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x31, // POP_JUMP_IF_TRUE -15
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_clear = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_clear,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 38,
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
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 51,
        .line_info = fun_data_myutils_DataBuffer_clear + 4,
        .line_info_top = fun_data_myutils_DataBuffer_clear + 9,
        .opcodes = fun_data_myutils_DataBuffer_clear + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_clear fun_data_myutils_DataBuffer_clear[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_available
static const byte fun_data_myutils_DataBuffer_available[11] = {
    0x09,0x0a, // prelude
    0x29,0x6b, // names: available, self
    0x80,0xe6,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_available = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_available,
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
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_myutils_DataBuffer_available + 4,
        .line_info_top = fun_data_myutils_DataBuffer_available + 7,
        .opcodes = fun_data_myutils_DataBuffer_available + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_available fun_data_myutils_DataBuffer_available[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_free
static const byte fun_data_myutils_DataBuffer_free[15] = {
    0x11,0x0a, // prelude
    0x34,0x6b, // names: free, self
    0x80,0xea,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0xf3, // BINARY_OP 28 __sub__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_free = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_free,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_myutils_DataBuffer_free + 4,
        .line_info_top = fun_data_myutils_DataBuffer_free + 7,
        .opcodes = fun_data_myutils_DataBuffer_free + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_free fun_data_myutils_DataBuffer_free[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_is_full
static const byte fun_data_myutils_DataBuffer_is_full[15] = {
    0x11,0x0a, // prelude
    0x35,0x6b, // names: is_full, self
    0x80,0xee,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xdb, // BINARY_OP 4 __ge__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_is_full = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_is_full,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 53,
        .line_info = fun_data_myutils_DataBuffer_is_full + 4,
        .line_info_top = fun_data_myutils_DataBuffer_is_full + 7,
        .opcodes = fun_data_myutils_DataBuffer_is_full + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_is_full fun_data_myutils_DataBuffer_is_full[0]
#endif

// child of myutils_DataBuffer
// frozen bytecode for file myutils.py, scope myutils_DataBuffer_is_empty
static const byte fun_data_myutils_DataBuffer_is_empty[13] = {
    0x11,0x0a, // prelude
    0x36,0x6b, // names: is_empty, self
    0x80,0xf2,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x31, // LOAD_ATTR 'pos'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer_is_empty = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer_is_empty,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 54,
        .line_info = fun_data_myutils_DataBuffer_is_empty + 4,
        .line_info_top = fun_data_myutils_DataBuffer_is_empty + 7,
        .opcodes = fun_data_myutils_DataBuffer_is_empty + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_DataBuffer_is_empty fun_data_myutils_DataBuffer_is_empty[0]
#endif

static const mp_raw_code_t *const children_myutils_DataBuffer[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer___init__,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_write,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_read,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_clear,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_available,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_free,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_is_full,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer_is_empty,
};

static const mp_raw_code_truncated_t proto_fun_myutils_DataBuffer = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_DataBuffer,
    .children = (void *)&children_myutils_DataBuffer,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 73,
    .n_children = 8,
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
        .qstr_block_name_idx = 9,
        .line_info = fun_data_myutils_DataBuffer + 3,
        .line_info_top = fun_data_myutils_DataBuffer + 21,
        .opcodes = fun_data_myutils_DataBuffer + 21,
    },
    #endif
    #endif
};

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_RingBuffer
static const byte fun_data_myutils_RingBuffer[65] = {
    0x08,0x22, // prelude
    0x0a, // names: RingBuffer
    0x88,0xf6,0x80,0x0d,0x84,0x0d,0x84,0x11,0x88,0x0c,0x88,0x08,0x64,0x20,0x64,0x20, // code info
    0x11,0x5b, // LOAD_NAME '__name__'
    0x16,0x5c, // STORE_NAME '__module__'
    0x10,0x0a, // LOAD_CONST_STRING 'RingBuffer'
    0x16,0x5d, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x2f, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x27, // STORE_NAME 'write'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x2a, // STORE_NAME 'read'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x3a, // STORE_NAME 'peek'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x29, // STORE_NAME 'available'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x34, // STORE_NAME 'free'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x33, // STORE_NAME 'clear'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer___init__
static const byte fun_data_myutils_RingBuffer___init__[39] = {
    0x1a,0x16, // prelude
    0x2f,0x6b,0x32, // names: __init__, self, size
    0x90,0x04,0x60,0x60,0x28,0x24,0x24,0x24, // code info
    0x12,0x64, // LOAD_GLOBAL 'bytearray'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x30, // STORE_ATTR 'buffer'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x32, // STORE_ATTR 'size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x37, // STORE_ATTR 'head'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x38, // STORE_ATTR 'tail'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x39, // STORE_ATTR 'count'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer___init__,
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
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 47,
        .line_info = fun_data_myutils_RingBuffer___init__ + 5,
        .line_info_top = fun_data_myutils_RingBuffer___init__ + 13,
        .opcodes = fun_data_myutils_RingBuffer___init__ + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer___init__ fun_data_myutils_RingBuffer___init__[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_write
static const byte fun_data_myutils_RingBuffer_write[94] = {
    0x52,0x20, // prelude
    0x27,0x6b,0x4c, // names: write, self, data
    0x90,0x11,0x20,0x29,0x46,0x22,0x25,0x29,0x28,0x2c,0x29,0x46,0x48, // code info
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb1, // LOAD_FAST 1
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb1, // LOAD_FAST 1
    0x14,0x10, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x5f, // GET_ITER_STACK
    0x4b,0x35, // FOR_ITER 53
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x39, // LOAD_ATTR 'count'
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x63, // POP_JUMP_IF_FALSE 35
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0xb0, // LOAD_FAST 0
    0x13,0x37, // LOAD_ATTR 'head'
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x37, // LOAD_ATTR 'head'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xf8, // BINARY_OP 33 __mod__
    0xb0, // LOAD_FAST 0
    0x18,0x37, // STORE_ATTR 'head'
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x39, // LOAD_ATTR 'count'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x39, // STORE_ATTR 'count'
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc2, // STORE_FAST 2
    0x42,0x46, // JUMP 6
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x09, // JUMP -55
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_write,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 94,
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
        .qstr_block_name_idx = 39,
        .line_info = fun_data_myutils_RingBuffer_write + 5,
        .line_info_top = fun_data_myutils_RingBuffer_write + 18,
        .opcodes = fun_data_myutils_RingBuffer_write + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_write fun_data_myutils_RingBuffer_write[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_read
static const byte fun_data_myutils_RingBuffer_read[82] = {
    0xc2,0x01,0x18, // prelude
    0x2a,0x6b,0x6c, // names: read, self, length
    0x90,0x22,0x20,0x29,0x46,0x26,0x2a,0x2c,0x52, // code info
    0x12,0x56, // LOAD_GLOBAL 'min'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x39, // LOAD_ATTR 'count'
    0x34,0x02, // CALL_FUNCTION 2
    0xc1, // STORE_FAST 1
    0x12,0x64, // LOAD_GLOBAL 'bytearray'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x63, // JUMP 35
    0x57, // DUP_TOP
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0xb0, // LOAD_FAST 0
    0x13,0x38, // LOAD_ATTR 'tail'
    0x55, // LOAD_SUBSCR
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x13,0x38, // LOAD_ATTR 'tail'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xf8, // BINARY_OP 33 __mod__
    0xb0, // LOAD_FAST 0
    0x18,0x38, // STORE_ATTR 'tail'
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x39, // LOAD_ATTR 'count'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe6, // BINARY_OP 15 __isub__
    0x5a, // ROT_TWO
    0x18,0x39, // STORE_ATTR 'count'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x18, // POP_JUMP_IF_TRUE -40
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x12,0x63, // LOAD_GLOBAL 'bytes'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 82,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 42,
        .line_info = fun_data_myutils_RingBuffer_read + 6,
        .line_info_top = fun_data_myutils_RingBuffer_read + 15,
        .opcodes = fun_data_myutils_RingBuffer_read + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_read fun_data_myutils_RingBuffer_read[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_peek
static const byte fun_data_myutils_RingBuffer_peek[37] = {
    0xa2,0x01,0x12, // prelude
    0x3a,0x6b,0x6d, // names: peek, self, offset
    0x90,0x2e,0x20,0x27,0x42,0x2a, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x39, // LOAD_ATTR 'count'
    0xdb, // BINARY_OP 4 __ge__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x13,0x38, // LOAD_ATTR 'tail'
    0xb1, // LOAD_FAST 1
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xf8, // BINARY_OP 33 __mod__
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x30, // LOAD_ATTR 'buffer'
    0xb2, // LOAD_FAST 2
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_peek = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_peek,
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
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 58,
        .line_info = fun_data_myutils_RingBuffer_peek + 6,
        .line_info_top = fun_data_myutils_RingBuffer_peek + 12,
        .opcodes = fun_data_myutils_RingBuffer_peek + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_peek fun_data_myutils_RingBuffer_peek[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_available
static const byte fun_data_myutils_RingBuffer_available[11] = {
    0x09,0x0a, // prelude
    0x29,0x6b, // names: available, self
    0x90,0x36,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x39, // LOAD_ATTR 'count'
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_available = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_available,
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
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 41,
        .line_info = fun_data_myutils_RingBuffer_available + 4,
        .line_info_top = fun_data_myutils_RingBuffer_available + 7,
        .opcodes = fun_data_myutils_RingBuffer_available + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_available fun_data_myutils_RingBuffer_available[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_free
static const byte fun_data_myutils_RingBuffer_free[15] = {
    0x11,0x0a, // prelude
    0x34,0x6b, // names: free, self
    0x90,0x3a,0x20, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xb0, // LOAD_FAST 0
    0x13,0x39, // LOAD_ATTR 'count'
    0xf3, // BINARY_OP 28 __sub__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_free = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_free,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 52,
        .line_info = fun_data_myutils_RingBuffer_free + 4,
        .line_info_top = fun_data_myutils_RingBuffer_free + 7,
        .opcodes = fun_data_myutils_RingBuffer_free + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_free fun_data_myutils_RingBuffer_free[0]
#endif

// child of myutils_RingBuffer
// frozen bytecode for file myutils.py, scope myutils_RingBuffer_clear
static const byte fun_data_myutils_RingBuffer_clear[23] = {
    0x11,0x0e, // prelude
    0x33,0x6b, // names: clear, self
    0x90,0x3e,0x20,0x24,0x24, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x37, // STORE_ATTR 'head'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x38, // STORE_ATTR 'tail'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x39, // STORE_ATTR 'count'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer_clear = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer_clear,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 23,
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
        .qstr_block_name_idx = 51,
        .line_info = fun_data_myutils_RingBuffer_clear + 4,
        .line_info_top = fun_data_myutils_RingBuffer_clear + 9,
        .opcodes = fun_data_myutils_RingBuffer_clear + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_RingBuffer_clear fun_data_myutils_RingBuffer_clear[0]
#endif

static const mp_raw_code_t *const children_myutils_RingBuffer[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer___init__,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_write,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_read,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_peek,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_available,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_free,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer_clear,
};

static const mp_raw_code_truncated_t proto_fun_myutils_RingBuffer = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_RingBuffer,
    .children = (void *)&children_myutils_RingBuffer,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 65,
    .n_children = 7,
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
        .qstr_block_name_idx = 10,
        .line_info = fun_data_myutils_RingBuffer + 3,
        .line_info_top = fun_data_myutils_RingBuffer + 19,
        .opcodes = fun_data_myutils_RingBuffer + 19,
    },
    #endif
    #endif
};

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_MovingAverage
static const byte fun_data_myutils_MovingAverage[37] = {
    0x08,0x12, // prelude
    0x0b, // names: MovingAverage
    0x98,0x44,0x80,0x09,0x88,0x0d,0x84,0x1c, // code info
    0x11,0x5b, // LOAD_NAME '__name__'
    0x16,0x5c, // STORE_NAME '__module__'
    0x10,0x0b, // LOAD_CONST_STRING 'MovingAverage'
    0x16,0x5d, // STORE_NAME '__qualname__'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x2f, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x2b, // STORE_NAME 'update'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x3f, // STORE_NAME 'reset'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of myutils_MovingAverage
// frozen bytecode for file myutils.py, scope myutils_MovingAverage___init__
static const byte fun_data_myutils_MovingAverage___init__[40] = {
    0x9a,0x01,0x16, // prelude
    0x2f,0x6b,0x6e, // names: __init__, self, window_size
    0x90,0x4e,0x60,0x60,0x28,0x24,0x24,0x24, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2b,0x01, // BUILD_LIST 1
    0xb1, // LOAD_FAST 1
    0xf4, // BINARY_OP 29 __mul__
    0xb0, // LOAD_FAST 0
    0x18,0x3b, // STORE_ATTR 'window'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x32, // STORE_ATTR 'size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3c, // STORE_ATTR 'index'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3d, // STORE_ATTR 'sum'
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x3e, // STORE_ATTR 'filled'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_MovingAverage___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_MovingAverage___init__,
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
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 47,
        .line_info = fun_data_myutils_MovingAverage___init__ + 6,
        .line_info_top = fun_data_myutils_MovingAverage___init__ + 14,
        .opcodes = fun_data_myutils_MovingAverage___init__ + 14,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_MovingAverage___init__ fun_data_myutils_MovingAverage___init__[0]
#endif

// child of myutils_MovingAverage
// frozen bytecode for file myutils.py, scope myutils_MovingAverage_update
static const byte fun_data_myutils_MovingAverage_update[103] = {
    0x32,0x1c, // prelude
    0x2b,0x6b,0x52, // names: update, self, value
    0x90,0x5b,0x80,0x0a,0x6f,0x28,0x69,0x6c,0x2c,0x64,0x2e, // code info
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x3d, // LOAD_ATTR 'sum'
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR 'window'
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR 'index'
    0x55, // LOAD_SUBSCR
    0xe6, // BINARY_OP 15 __isub__
    0x5a, // ROT_TWO
    0x18,0x3d, // STORE_ATTR 'sum'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR 'window'
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR 'index'
    0x56, // STORE_SUBSCR
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x3d, // LOAD_ATTR 'sum'
    0xb1, // LOAD_FAST 1
    0xe5, // BINARY_OP 14 __iadd__
    0x5a, // ROT_TWO
    0x18,0x3d, // STORE_ATTR 'sum'
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR 'index'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xf8, // BINARY_OP 33 __mod__
    0xb0, // LOAD_FAST 0
    0x18,0x3c, // STORE_ATTR 'index'
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR 'index'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb0, // LOAD_FAST 0
    0x13,0x3e, // LOAD_ATTR 'filled'
    0x43,0x44, // POP_JUMP_IF_TRUE 4
    0x52, // LOAD_CONST_TRUE
    0xb0, // LOAD_FAST 0
    0x18,0x3e, // STORE_ATTR 'filled'
    0xb0, // LOAD_FAST 0
    0x13,0x3e, // LOAD_ATTR 'filled'
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0x42,0x43, // JUMP 3
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR 'index'
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0xb0, // LOAD_FAST 0
    0x13,0x3d, // LOAD_ATTR 'sum'
    0xb2, // LOAD_FAST 2
    0xf7, // BINARY_OP 32 __truediv__
    0x63, // RETURN_VALUE
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_MovingAverage_update = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_MovingAverage_update,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 103,
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
        .qstr_block_name_idx = 43,
        .line_info = fun_data_myutils_MovingAverage_update + 5,
        .line_info_top = fun_data_myutils_MovingAverage_update + 16,
        .opcodes = fun_data_myutils_MovingAverage_update + 16,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_MovingAverage_update fun_data_myutils_MovingAverage_update[0]
#endif

// child of myutils_MovingAverage
// frozen bytecode for file myutils.py, scope myutils_MovingAverage_reset
static const byte fun_data_myutils_MovingAverage_reset[34] = {
    0x11,0x10, // prelude
    0x3f,0x6b, // names: reset, self
    0x90,0x77,0x20,0x2a,0x24,0x24, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2b,0x01, // BUILD_LIST 1
    0xb0, // LOAD_FAST 0
    0x13,0x32, // LOAD_ATTR 'size'
    0xf4, // BINARY_OP 29 __mul__
    0xb0, // LOAD_FAST 0
    0x18,0x3b, // STORE_ATTR 'window'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3c, // STORE_ATTR 'index'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3d, // STORE_ATTR 'sum'
    0x50, // LOAD_CONST_FALSE
    0xb0, // LOAD_FAST 0
    0x18,0x3e, // STORE_ATTR 'filled'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_MovingAverage_reset = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_MovingAverage_reset,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 63,
        .line_info = fun_data_myutils_MovingAverage_reset + 4,
        .line_info_top = fun_data_myutils_MovingAverage_reset + 10,
        .opcodes = fun_data_myutils_MovingAverage_reset + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_MovingAverage_reset fun_data_myutils_MovingAverage_reset[0]
#endif

static const mp_raw_code_t *const children_myutils_MovingAverage[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_MovingAverage___init__,
    (const mp_raw_code_t *)&proto_fun_myutils_MovingAverage_update,
    (const mp_raw_code_t *)&proto_fun_myutils_MovingAverage_reset,
};

static const mp_raw_code_truncated_t proto_fun_myutils_MovingAverage = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_MovingAverage,
    .children = (void *)&children_myutils_MovingAverage,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 37,
    .n_children = 3,
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
        .qstr_block_name_idx = 11,
        .line_info = fun_data_myutils_MovingAverage + 3,
        .line_info_top = fun_data_myutils_MovingAverage + 11,
        .opcodes = fun_data_myutils_MovingAverage + 11,
    },
    #endif
    #endif
};

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_print_dict
static const byte fun_data_myutils_print_dict[85] = {
    0xda,0x01,0x18, // prelude
    0x1a,0x5e,0x5f, // names: print_dict, d, indent
    0x90,0x82,0x80,0x07,0x2c,0x37,0x29,0x25,0x4b, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x1b, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x5f, // GET_ITER_STACK
    0x4b,0x3c, // FOR_ITER 60
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc2, // STORE_FAST 2
    0xc3, // STORE_FAST 3
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x10,0x1c, // LOAD_CONST_STRING '  '
    0xb1, // LOAD_FAST 1
    0xf4, // BINARY_OP 29 __mul__
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x10,0x1d, // LOAD_CONST_STRING ':'
    0xf2, // BINARY_OP 27 __add__
    0x10,0x1e, // LOAD_CONST_STRING 'end'
    0x10,0x12, // LOAD_CONST_STRING ' '
    0x34,0x82,0x01, // CALL_FUNCTION 257
    0x59, // POP_TOP
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb3, // LOAD_FAST 3
    0x12,0x61, // LOAD_GLOBAL 'dict'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x50, // POP_JUMP_IF_FALSE 16
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x34,0x00, // CALL_FUNCTION 0
    0x59, // POP_TOP
    0x12,0x1a, // LOAD_GLOBAL 'print_dict'
    0xb3, // LOAD_FAST 3
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x42,0x46, // JUMP 6
    0x12,0x60, // LOAD_GLOBAL 'print'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x02, // JUMP -62
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_print_dict = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_print_dict,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 85,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 26,
        .line_info = fun_data_myutils_print_dict + 6,
        .line_info_top = fun_data_myutils_print_dict + 15,
        .opcodes = fun_data_myutils_print_dict + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_print_dict fun_data_myutils_print_dict[0]
#endif

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_sizeof
static const byte fun_data_myutils_sizeof[139] = {
    0x31,0x22, // prelude
    0x1f,0x62, // names: sizeof, obj
    0x90,0x92,0x80,0x09,0x65,0x42,0x29,0x29,0x2d,0x29,0x2d,0x2d,0x29,0x51,0x53, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x20, // IMPORT_NAME 'sys'
    0xc1, // STORE_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x4e, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x51, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0x42,0xdd,0x80, // JUMP 93
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x63, // LOAD_GLOBAL 'bytes'
    0x12,0x64, // LOAD_GLOBAL 'bytearray'
    0x2a,0x02, // BUILD_TUPLE 2
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x51, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0x42,0xc7,0x80, // JUMP 71
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x65, // LOAD_GLOBAL 'list'
    0x12,0x66, // LOAD_GLOBAL 'tuple'
    0x2a,0x02, // BUILD_TUPLE 2
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0x12,0x3d, // LOAD_GLOBAL 'sum'
    0x32,0x00, // MAKE_FUNCTION 0
    0xb0, // LOAD_FAST 0
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0x42,0x6d, // JUMP 45
    0x12,0x4d, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x61, // LOAD_GLOBAL 'dict'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x12,0x3d, // LOAD_GLOBAL 'sum'
    0x32,0x01, // MAKE_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x14,0x1b, // LOAD_METHOD 'items'
    0x36,0x00, // CALL_METHOD 0
    0x5e, // GET_ITER
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0x42,0x53, // JUMP 19
    0x12,0x67, // LOAD_GLOBAL 'hasattr'
    0xb1, // LOAD_FAST 1
    0x10,0x21, // LOAD_CONST_STRING 'getsizeof'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb1, // LOAD_FAST 1
    0x14,0x21, // LOAD_METHOD 'getsizeof'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
// child of myutils_sizeof
// frozen bytecode for file myutils.py, scope myutils_sizeof__lt_genexpr_gt_
static const byte fun_data_myutils_sizeof__lt_genexpr_gt_[25] = {
    0xb9,0x40,0x08, // prelude
    0x2c,0x69, // names: <genexpr>, *
    0x90,0xa5, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x0a, // FOR_ITER 10
    0xc1, // STORE_FAST 1
    0x12,0x1f, // LOAD_GLOBAL 'sizeof'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x34, // JUMP -12
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_sizeof__lt_genexpr_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_myutils_sizeof__lt_genexpr_gt_,
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
        .n_state = 8,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_myutils_sizeof__lt_genexpr_gt_ + 5,
        .line_info_top = fun_data_myutils_sizeof__lt_genexpr_gt_ + 7,
        .opcodes = fun_data_myutils_sizeof__lt_genexpr_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_sizeof__lt_genexpr_gt_ fun_data_myutils_sizeof__lt_genexpr_gt_[0]
#endif

// child of myutils_sizeof
// frozen bytecode for file myutils.py, scope myutils_sizeof__lt_genexpr_gt_2
static const byte fun_data_myutils_sizeof__lt_genexpr_gt_2[34] = {
    0xc9,0x40,0x08, // prelude
    0x2c,0x69, // names: <genexpr>, *
    0x90,0xa7, // code info
    0x53, // LOAD_NULL
    0xb0, // LOAD_FAST 0
    0x53, // LOAD_NULL
    0x53, // LOAD_NULL
    0x4b,0x13, // FOR_ITER 19
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0x12,0x1f, // LOAD_GLOBAL 'sizeof'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x12,0x1f, // LOAD_GLOBAL 'sizeof'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x67, // YIELD_VALUE
    0x59, // POP_TOP
    0x42,0x2b, // JUMP -21
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_sizeof__lt_genexpr_gt_2 = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 1,
    .fun_data = fun_data_myutils_sizeof__lt_genexpr_gt_2,
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
        .n_state = 10,
        .n_exc_stack = 0,
        .scope_flags = 1,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 44,
        .line_info = fun_data_myutils_sizeof__lt_genexpr_gt_2 + 5,
        .line_info_top = fun_data_myutils_sizeof__lt_genexpr_gt_2 + 7,
        .opcodes = fun_data_myutils_sizeof__lt_genexpr_gt_2 + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_sizeof__lt_genexpr_gt_2 fun_data_myutils_sizeof__lt_genexpr_gt_2[0]
#endif

static const mp_raw_code_t *const children_myutils_sizeof[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_sizeof__lt_genexpr_gt_,
    (const mp_raw_code_t *)&proto_fun_myutils_sizeof__lt_genexpr_gt_2,
};

static const mp_raw_code_truncated_t proto_fun_myutils_sizeof = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_sizeof,
    .children = (void *)&children_myutils_sizeof,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 139,
    .n_children = 2,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 31,
        .line_info = fun_data_myutils_sizeof + 4,
        .line_info_top = fun_data_myutils_sizeof + 19,
        .opcodes = fun_data_myutils_sizeof + 19,
    },
    #endif
    #endif
};

// child of myutils__lt_module_gt_
// frozen bytecode for file myutils.py, scope myutils_self_test
static const byte fun_data_myutils_self_test[332] = {
    0x38,0x48, // prelude
    0x22, // names: self_test
    0x90,0xb2,0x80,0x07,0x2a,0x27,0x6a,0x27,0x2e,0x67,0x27,0x2f,0x2d,0x67,0x27,0x26,0x28,0x2c,0x2e,0x67,0x27,0x26,0x28,0x2e,0x2c,0x67,0x27,0x26,0x27,0x27,0x27,0x30,0x47,0x2d,0x27, // code info
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x10,0x23, // LOAD_CONST_STRING '='
    0x22,0x3c, // LOAD_CONST_SMALL_INT 60
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x10,0x23, // LOAD_CONST_STRING '='
    0x22,0x3c, // LOAD_CONST_SMALL_INT 60
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x0c, // LOAD_GLOBAL 'greet'
    0x10,0x24, // LOAD_CONST_STRING 'Test'
    0x34,0x01, // CALL_FUNCTION 1
    0x23,0x04, // LOAD_CONST_OBJ 4
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x0f, // LOAD_GLOBAL 'calculate_checksum'
    0x10,0x26, // LOAD_CONST_STRING 'TEST'
    0x34,0x01, // CALL_FUNCTION 1
    0x22,0x81,0x69, // LOAD_CONST_SMALL_INT 233
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x0f, // LOAD_GLOBAL 'calculate_checksum'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x34,0x01, // CALL_FUNCTION 1
    0x86, // LOAD_CONST_SMALL_INT 6
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x09, // LOAD_GLOBAL 'DataBuffer'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x34,0x01, // CALL_FUNCTION 1
    0xc0, // STORE_FAST 0
    0xb0, // LOAD_FAST 0
    0x14,0x27, // LOAD_METHOD 'write'
    0x10,0x28, // LOAD_CONST_STRING 'Hello'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x29, // LOAD_METHOD 'available'
    0x36,0x00, // CALL_METHOD 0
    0x85, // LOAD_CONST_SMALL_INT 5
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0xb0, // LOAD_FAST 0
    0x14,0x2a, // LOAD_METHOD 'read'
    0x85, // LOAD_CONST_SMALL_INT 5
    0x36,0x01, // CALL_METHOD 1
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x0a, // LOAD_GLOBAL 'RingBuffer'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x34,0x01, // CALL_FUNCTION 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x27, // LOAD_METHOD 'write'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x14,0x2a, // LOAD_METHOD 'read'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x36,0x01, // CALL_METHOD 1
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0x14,0x29, // LOAD_METHOD 'available'
    0x36,0x00, // CALL_METHOD 0
    0x82, // LOAD_CONST_SMALL_INT 2
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x0b, // LOAD_GLOBAL 'MovingAverage'
    0x83, // LOAD_CONST_SMALL_INT 3
    0x34,0x01, // CALL_FUNCTION 1
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'update'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'update'
    0x94, // LOAD_CONST_SMALL_INT 20
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x14,0x2b, // LOAD_METHOD 'update'
    0x9e, // LOAD_CONST_SMALL_INT 30
    0x36,0x01, // CALL_METHOD 1
    0xc3, // STORE_FAST 3
    0x12,0x68, // LOAD_GLOBAL 'abs'
    0xb3, // LOAD_FAST 3
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0xf3, // BINARY_OP 28 __sub__
    0x34,0x01, // CALL_FUNCTION 1
    0x23,0x0f, // LOAD_CONST_OBJ 15
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x12,0x25, // LOAD_GLOBAL 'AssertionError'
    0x65, // RAISE_OBJ
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x10,0x17, // LOAD_CONST_STRING '\n'
    0x10,0x23, // LOAD_CONST_STRING '='
    0x22,0x3c, // LOAD_CONST_SMALL_INT 60
    0xf4, // BINARY_OP 29 __mul__
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x23,0x10, // LOAD_CONST_OBJ 16
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x60, // LOAD_GLOBAL 'print'
    0x10,0x23, // LOAD_CONST_STRING '='
    0x22,0x3c, // LOAD_CONST_SMALL_INT 60
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_myutils_self_test = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils_self_test,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 332,
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
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 34,
        .line_info = fun_data_myutils_self_test + 3,
        .line_info_top = fun_data_myutils_self_test + 38,
        .opcodes = fun_data_myutils_self_test + 38,
    },
    #endif
    #endif
};
#else
#define proto_fun_myutils_self_test fun_data_myutils_self_test[0]
#endif

static const mp_raw_code_t *const children_myutils__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_myutils_greet,
    (const mp_raw_code_t *)&proto_fun_myutils_calculate_checksum,
    (const mp_raw_code_t *)&proto_fun_myutils_hex_dump,
    (const mp_raw_code_t *)&proto_fun_myutils_clamp,
    (const mp_raw_code_t *)&proto_fun_myutils_map_range,
    (const mp_raw_code_t *)&proto_fun_myutils_DataBuffer,
    (const mp_raw_code_t *)&proto_fun_myutils_RingBuffer,
    (const mp_raw_code_t *)&proto_fun_myutils_MovingAverage,
    (const mp_raw_code_t *)&proto_fun_myutils_print_dict,
    (const mp_raw_code_t *)&proto_fun_myutils_sizeof,
    (const mp_raw_code_t *)&proto_fun_myutils_self_test,
};

static const mp_raw_code_truncated_t proto_fun_myutils__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_myutils__lt_module_gt_,
    .children = (void *)&children_myutils__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 177,
    .n_children = 11,
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
        .line_info = fun_data_myutils__lt_module_gt_ + 3,
        .line_info_top = fun_data_myutils__lt_module_gt_ + 43,
        .opcodes = fun_data_myutils__lt_module_gt_ + 43,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_myutils[111] = {
    MP_QSTR_myutils_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_1_dot_0_dot_0,
    MP_QSTR_CaiBo,
    MP_QSTR_2026_hyphen_01_hyphen_28,
    MP_QSTR_baud_rate,
    MP_QSTR_timeout,
    MP_QSTR_debug,
    MP_QSTR_World,
    MP_QSTR_DataBuffer,
    MP_QSTR_RingBuffer,
    MP_QSTR_MovingAverage,
    MP_QSTR_greet,
    MP_QSTR_Hello_comma__space__brace_open__brace_close__bang_,
    MP_QSTR_format,
    MP_QSTR_calculate_checksum,
    MP_QSTR_encode,
    MP_QSTR_hex_dump,
    MP_QSTR__space_,
    MP_QSTR_join,
    MP_QSTR_ljust,
    MP_QSTR_,
    MP_QSTR_append,
    MP_QSTR__0x0a_,
    MP_QSTR_clamp,
    MP_QSTR_map_range,
    MP_QSTR_print_dict,
    MP_QSTR_items,
    MP_QSTR__space__space_,
    MP_QSTR__colon_,
    MP_QSTR_end,
    MP_QSTR_sizeof,
    MP_QSTR_sys,
    MP_QSTR_getsizeof,
    MP_QSTR_self_test,
    MP_QSTR__equals_,
    MP_QSTR_Test,
    MP_QSTR_AssertionError,
    MP_QSTR_TEST,
    MP_QSTR_write,
    MP_QSTR_Hello,
    MP_QSTR_available,
    MP_QSTR_read,
    MP_QSTR_update,
    MP_QSTR__lt_genexpr_gt_,
    MP_QSTR__brace_open__colon_02x_brace_close_,
    MP_QSTR__dot_,
    MP_QSTR___init__,
    MP_QSTR_buffer,
    MP_QSTR_pos,
    MP_QSTR_size,
    MP_QSTR_clear,
    MP_QSTR_free,
    MP_QSTR_is_full,
    MP_QSTR_is_empty,
    MP_QSTR_head,
    MP_QSTR_tail,
    MP_QSTR_count,
    MP_QSTR_peek,
    MP_QSTR_window,
    MP_QSTR_index,
    MP_QSTR_sum,
    MP_QSTR_filled,
    MP_QSTR_reset,
    MP_QSTR___version__,
    MP_QSTR___author__,
    MP_QSTR___date__,
    MP_QSTR_LED_RED,
    MP_QSTR_LED_GREEN,
    MP_QSTR_LED_BLUE,
    MP_QSTR_DEFAULT_CONFIG,
    MP_QSTR_STATUS_OK,
    MP_QSTR_STATUS_ERROR,
    MP_QSTR_STATUS_TIMEOUT,
    MP_QSTR_STATUS_BUSY,
    MP_QSTR_name,
    MP_QSTR_data,
    MP_QSTR_isinstance,
    MP_QSTR_str,
    MP_QSTR_width,
    MP_QSTR_range,
    MP_QSTR_len,
    MP_QSTR_value,
    MP_QSTR_min_val,
    MP_QSTR_max_val,
    MP_QSTR_max,
    MP_QSTR_min,
    MP_QSTR_in_min,
    MP_QSTR_in_max,
    MP_QSTR_out_min,
    MP_QSTR_out_max,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_d,
    MP_QSTR_indent,
    MP_QSTR_print,
    MP_QSTR_dict,
    MP_QSTR_obj,
    MP_QSTR_bytes,
    MP_QSTR_bytearray,
    MP_QSTR_list,
    MP_QSTR_tuple,
    MP_QSTR_hasattr,
    MP_QSTR_abs,
    MP_QSTR__star_,
    MP_QSTR_chr,
    MP_QSTR_self,
    MP_QSTR_length,
    MP_QSTR_offset,
    MP_QSTR_window_size,
};

// constants
static const mp_obj_str_t const_obj_myutils_6 = {{&mp_type_str}, 57550, 31, (const byte*)"\x0a\x32\x2e\x20\xe6\xb5\x8b\xe8\xaf\x95\x20\x63\x61\x6c\x63\x75\x6c\x61\x74\x65\x5f\x63\x68\x65\x63\x6b\x73\x75\x6d\x28\x29"};
static const mp_obj_str_t const_obj_myutils_7 = {{&mp_type_bytes}, 44773, 3, (const byte*)"\x01\x02\x03"};
static const mp_obj_str_t const_obj_myutils_9 = {{&mp_type_bytes}, 11783, 5, (const byte*)"\x48\x65\x6c\x6c\x6f"};
static const mp_obj_str_t const_obj_myutils_11 = {{&mp_type_bytes}, 61268, 5, (const byte*)"\x31\x32\x33\x34\x35"};
static const mp_obj_str_t const_obj_myutils_12 = {{&mp_type_bytes}, 27861, 3, (const byte*)"\x31\x32\x33"};
#if MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_A || MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_B
static const mp_obj_float_t const_obj_myutils_14 = {{&mp_type_float}, (mp_float_t)20};
#define const_obj_myutils_14_macro MP_ROM_PTR(&const_obj_myutils_14)
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_C
#define const_obj_myutils_14_macro ((mp_rom_obj_t)(0xc2200002))
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_D
#define const_obj_myutils_14_macro ((mp_rom_obj_t)(0xc038000000000000))
#endif
#if MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_A || MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_B
static const mp_obj_float_t const_obj_myutils_15 = {{&mp_type_float}, (mp_float_t)0.001};
#define const_obj_myutils_15_macro MP_ROM_PTR(&const_obj_myutils_15)
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_C
#define const_obj_myutils_15_macro ((mp_rom_obj_t)(0xbb03126e))
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_D
#define const_obj_myutils_15_macro ((mp_rom_obj_t)(0xbf54624dd2f1a9fc))
#endif

// constant table
static const mp_rom_obj_t const_obj_table_data_myutils[17] = {
    MP_ROM_QSTR(MP_QSTR_buffer_size),
    MP_ROM_QSTR(MP_QSTR__brace_open__colon_08x_brace_close__colon__space__brace_open__brace_close__space__space__brace_open__brace_close_),
    MP_ROM_QSTR(MP_QSTR_myutils_space__0x6a21__0x5757__0x81ea__0x6d4b__0x8bd5_),
    MP_ROM_QSTR(MP_QSTR__0x0a_1_dot__space__0x6d4b__0x8bd5__space_greet_paren_open__paren_close_),
    MP_ROM_QSTR(MP_QSTR_Hello_comma__space_Test_bang_),
    MP_ROM_QSTR(MP_QSTR__space__space__space__0x2705__space__0x901a__0x8fc7_),
    MP_ROM_PTR(&const_obj_myutils_6),
    MP_ROM_PTR(&const_obj_myutils_7),
    MP_ROM_QSTR(MP_QSTR__0x0a_3_dot__space__0x6d4b__0x8bd5__space_DataBuffer),
    MP_ROM_PTR(&const_obj_myutils_9),
    MP_ROM_QSTR(MP_QSTR__0x0a_4_dot__space__0x6d4b__0x8bd5__space_RingBuffer),
    MP_ROM_PTR(&const_obj_myutils_11),
    MP_ROM_PTR(&const_obj_myutils_12),
    MP_ROM_QSTR(MP_QSTR__0x0a_5_dot__space__0x6d4b__0x8bd5__space_MovingAverage),
    const_obj_myutils_14_macro,
    const_obj_myutils_15_macro,
    MP_ROM_QSTR(MP_QSTR__0x6240__0x6709__0x6d4b__0x8bd5__0x901a__0x8fc7__bang__space__0x2705_),
};

static const mp_frozen_module_t frozen_module_myutils = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_myutils,
        .obj_table = (mp_obj_t *)&const_obj_table_data_myutils,
    },
    .proto_fun = &proto_fun_myutils__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module ymodem
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\ymodem.mpy
// - frozen file name: ymodem.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file ymodem.py, scope ymodem__lt_module_gt_
static const byte fun_data_ymodem__lt_module_gt_[259] = {
    0x30,0x4e, // prelude
    0x01, // names: <module>
    0x80,0x11,0x26,0x26,0x26,0x26,0x26,0x26,0x2c,0x4c,0x24,0x24,0x25,0x25,0x25,0x25,0x45,0x24,0x24,0x24,0x24,0x24,0x44,0x44,0x7b,0x84,0x0a,0x84,0x1b,0x8c,0x27,0xac,0x02,0x8c,0x07,0x8b,0x0a,0x28, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'gc'
    0x16,0x02, // STORE_NAME 'gc'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'uos'
    0x16,0x03, // STORE_NAME 'uos'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x04, // IMPORT_NAME 'sys'
    0x16,0x04, // STORE_NAME 'sys'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x05, // IMPORT_NAME 'ql_fs'
    0x16,0x05, // STORE_NAME 'ql_fs'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x06, // IMPORT_NAME 'osTimer'
    0x16,0x06, // STORE_NAME 'osTimer'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x07, // IMPORT_NAME 'utime'
    0x16,0x7d, // STORE_NAME 'time'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x08, // LOAD_CONST_STRING 'Queue'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x09, // IMPORT_NAME 'queue'
    0x1c,0x08, // IMPORT_FROM 'Queue'
    0x16,0x08, // STORE_NAME 'Queue'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x0a, // LOAD_CONST_STRING 'UART'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x0b, // IMPORT_NAME 'machine'
    0x1c,0x0a, // IMPORT_FROM 'UART'
    0x16,0x0a, // STORE_NAME 'UART'
    0x59, // POP_TOP
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x16,0x7e, // STORE_NAME 'SOH'
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x16,0x7f, // STORE_NAME 'STX'
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x16,0x81,0x00, // STORE_NAME 'EOT'
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x16,0x81,0x01, // STORE_NAME 'ACK'
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x16,0x81,0x02, // STORE_NAME 'NAK'
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x16,0x81,0x03, // STORE_NAME 'CAN'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x16,0x81,0x04, // STORE_NAME 'CRC'
    0xa0, // LOAD_CONST_SMALL_INT 32
    0x16,0x81,0x05, // STORE_NAME 'USE_LENGTH_FIELD'
    0x90, // LOAD_CONST_SMALL_INT 16
    0x16,0x81,0x06, // STORE_NAME 'USE_DATE_FIELD'
    0x88, // LOAD_CONST_SMALL_INT 8
    0x16,0x81,0x07, // STORE_NAME 'USE_MODE_FIELD'
    0x84, // LOAD_CONST_SMALL_INT 4
    0x16,0x81,0x08, // STORE_NAME 'USE_SN_FIELD'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x81,0x09, // STORE_NAME 'ALLOW_1K_BLOCK'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x16,0x81,0x0a, // STORE_NAME 'ALLOW_YMODEM_G'
    0x50, // LOAD_CONST_FALSE
    0x17,0x81,0x0b, // STORE_GLOBAL 'DEBUG'
    0x12,0x81,0x0b, // LOAD_GLOBAL 'DEBUG'
    0x44,0x52, // POP_JUMP_IF_FALSE 18
    0x11,0x0a, // LOAD_NAME 'UART'
    0x11,0x0a, // LOAD_NAME 'UART'
    0x13,0x0c, // LOAD_ATTR 'UART2'
    0x22,0x87,0x84,0x00, // LOAD_CONST_SMALL_INT 115200
    0x88, // LOAD_CONST_SMALL_INT 8
    0x80, // LOAD_CONST_SMALL_INT 0
    0x81, // LOAD_CONST_SMALL_INT 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x34,0x06, // CALL_FUNCTION 6
    0x42,0x41, // JUMP 1
    0x51, // LOAD_CONST_NONE
    0x17,0x81,0x0c, // STORE_GLOBAL '_MAIN_UART_'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x10, // STORE_NAME '_print'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x14, // STORE_NAME 'check_file'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x02, // MAKE_FUNCTION 2
    0x10,0x0d, // LOAD_CONST_STRING 'Serial'
    0x11,0x81,0x0d, // LOAD_NAME 'object'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x0d, // STORE_NAME 'Serial'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x03, // MAKE_FUNCTION 3
    0x10,0x0e, // LOAD_CONST_STRING 'Modem'
    0x11,0x81,0x0d, // LOAD_NAME 'object'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x0e, // STORE_NAME 'Modem'
    0x51, // LOAD_CONST_NONE
    0x22,0x87,0x84,0x00, // LOAD_CONST_SMALL_INT 115200
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x18, // STORE_NAME 'enter_ymodem'
    0x22,0x87,0x84,0x00, // LOAD_CONST_SMALL_INT 115200
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x05, // MAKE_FUNCTION_DEFARGS 5
    0x16,0x20, // STORE_NAME 'send_file'
    0x11,0x81,0x0e, // LOAD_NAME '__name__'
    0x10,0x0f, // LOAD_CONST_STRING '__main__'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0x11,0x18, // LOAD_NAME 'enter_ymodem'
    0x34,0x00, // CALL_FUNCTION 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem__print
static const byte fun_data_ymodem__print[102] = {
    0x29,0x16, // prelude
    0x10,0x81,0x0f, // names: _print, data
    0x80,0x2f,0x20,0x26,0x1f,0x2c,0x32,0x4b, // code info
    0x12,0x81,0x0b, // LOAD_GLOBAL 'DEBUG'
    0x44,0xc8,0x80, // POP_JUMP_IF_FALSE 72
    0x12,0x81,0x10, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x81,0x11, // LOAD_GLOBAL 'bytes'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb0, // LOAD_FAST 0
    0x42,0x5c, // JUMP 28
    0x12,0x81,0x10, // LOAD_GLOBAL 'isinstance'
    0xb0, // LOAD_FAST 0
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0xb0, // LOAD_FAST 0
    0x14,0x11, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0x42,0x4a, // JUMP 10
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x14,0x11, // LOAD_METHOD 'encode'
    0x36,0x00, // CALL_METHOD 0
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0xb1, // LOAD_FAST 1
    0x14,0x12, // LOAD_METHOD 'endswith'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x36,0x01, // CALL_METHOD 1
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x42,0x42, // JUMP 2
    0x23,0x07, // LOAD_CONST_OBJ 7
    0xe5, // BINARY_OP 14 __iadd__
    0xc1, // STORE_FAST 1
    0x12,0x81,0x0c, // LOAD_GLOBAL '_MAIN_UART_'
    0x14,0x13, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x49, // JUMP 9
    0x12,0x81,0x13, // LOAD_GLOBAL 'print'
    0x12,0x81,0x0b, // LOAD_GLOBAL 'DEBUG'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem__print = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem__print,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 102,
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
        .qstr_block_name_idx = 16,
        .line_info = fun_data_ymodem__print + 5,
        .line_info_top = fun_data_ymodem__print + 13,
        .opcodes = fun_data_ymodem__print + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem__print fun_data_ymodem__print[0]
#endif

// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem_check_file
static const byte fun_data_ymodem_check_file[12] = {
    0x08,0x0a, // prelude
    0x14, // names: check_file
    0x80,0x39,0x83,0x17, // code info
    0x32,0x00, // MAKE_FUNCTION 0
    0xc0, // STORE_FAST 0
    0xb0, // LOAD_FAST 0
    0x63, // RETURN_VALUE
};
// child of ymodem_check_file
// frozen bytecode for file ymodem.py, scope ymodem_check_file_wrapper
static const byte fun_data_ymodem_check_file_wrapper[17] = {
    0x11,0x0f, // prelude
    0x22,0x81,0x1a, // names: wrapper, func
    0x80,0x3a,0x85,0x15,0x00, // code info
    0xb0, // LOAD_FAST 0
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x63, // RETURN_VALUE
};
// child of ymodem_check_file_wrapper
// frozen bytecode for file ymodem.py, scope ymodem_check_file_wrapper__wrapper
static const byte fun_data_ymodem_check_file_wrapper__wrapper[185] = {
    0x91,0x90,0xc0,0x40,0x2c, // prelude
    0x74,0x81,0x3f, // names: _wrapper, *
    0x80,0x3b,0x26,0x29,0x24,0x23,0x25,0x31,0x2c,0x29,0x22,0x24,0x2a,0x2a,0x2f,0x46,0x49,0x2f,0x27, // code info
    0x12,0x81,0x40, // LOAD_GLOBAL 'list'
    0x34,0x00, // CALL_FUNCTION 0
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x72, // LOAD_METHOD 'append'
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb1, // LOAD_FAST 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xc4, // STORE_FAST 4
    0x2b,0x00, // BUILD_LIST 0
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0x5f, // GET_ITER_STACK
    0x4b,0x6e, // FOR_ITER 110
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x14,0x75, // LOAD_METHOD 'strip'
    0x10,0x76, // LOAD_CONST_STRING '[]'
    0x36,0x01, // CALL_METHOD 1
    0x14,0x4d, // LOAD_METHOD 'split'
    0x10,0x77, // LOAD_CONST_STRING ','
    0x36,0x01, // CALL_METHOD 1
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc7, // STORE_FAST 7
    0xc8, // STORE_FAST 8
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x2e, // LOAD_CONST_OBJ 46
    0xb7, // LOAD_FAST 7
    0xb8, // LOAD_FAST 8
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x53, // LOAD_METHOD 'path_exists'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x44,0x78, // POP_JUMP_IF_FALSE 56
    0x2c,0x05, // BUILD_MAP 5
    0xb7, // LOAD_FAST 7
    0x10,0x5d, // LOAD_CONST_STRING 'filepath'
    0x62, // STORE_MAP
    0xb8, // LOAD_FAST 8
    0x14,0x75, // LOAD_METHOD 'strip'
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x36,0x01, // CALL_METHOD 1
    0x10,0x65, // LOAD_CONST_STRING 'name'
    0x62, // STORE_MAP
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x78, // LOAD_METHOD 'path_getsize'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x10,0x6a, // LOAD_CONST_STRING 'length'
    0x62, // STORE_MAP
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x79, // LOAD_METHOD 'mktime'
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x7a, // LOAD_METHOD 'localtime'
    0x36,0x00, // CALL_METHOD 0
    0x36,0x01, // CALL_METHOD 1
    0x10,0x6b, // LOAD_CONST_STRING 'mtime'
    0x62, // STORE_MAP
    0x10,0x7b, // LOAD_CONST_STRING 'rtos'
    0x10,0x6e, // LOAD_CONST_STRING 'source'
    0x62, // STORE_MAP
    0xc9, // STORE_FAST 9
    0xb5, // LOAD_FAST 5
    0x14,0x72, // LOAD_METHOD 'append'
    0xb9, // LOAD_FAST 9
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x4c, // JUMP 12
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x2f, // LOAD_CONST_OBJ 47
    0x14,0x68, // LOAD_METHOD 'format'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x90,0x7f, // JUMP -112
    0xb3, // LOAD_FAST 3
    0x14,0x72, // LOAD_METHOD 'append'
    0xb5, // LOAD_FAST 5
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x25,0x00, // LOAD_DEREF 0
    0x12,0x81,0x41, // LOAD_GLOBAL 'tuple'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x53, // LOAD_NULL
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0x35,0x82,0x01, // CALL_FUNCTION_VAR_KW 257
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_check_file_wrapper__wrapper = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_check_file_wrapper__wrapper,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 185,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 19,
        .n_exc_stack = 0,
        .scope_flags = 6,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 116,
        .line_info = fun_data_ymodem_check_file_wrapper__wrapper + 8,
        .line_info_top = fun_data_ymodem_check_file_wrapper__wrapper + 27,
        .opcodes = fun_data_ymodem_check_file_wrapper__wrapper + 27,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_check_file_wrapper__wrapper fun_data_ymodem_check_file_wrapper__wrapper[0]
#endif

static const mp_raw_code_t *const children_ymodem_check_file_wrapper[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_check_file_wrapper__wrapper,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_check_file_wrapper = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_check_file_wrapper,
    .children = (void *)&children_ymodem_check_file_wrapper,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
    .n_children = 1,
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
        .qstr_block_name_idx = 34,
        .line_info = fun_data_ymodem_check_file_wrapper + 5,
        .line_info_top = fun_data_ymodem_check_file_wrapper + 9,
        .opcodes = fun_data_ymodem_check_file_wrapper + 10,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_ymodem_check_file[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_check_file_wrapper,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_check_file = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_check_file,
    .children = (void *)&children_ymodem_check_file,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 12,
    .n_children = 1,
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
        .qstr_block_name_idx = 20,
        .line_info = fun_data_ymodem_check_file + 3,
        .line_info_top = fun_data_ymodem_check_file + 7,
        .opcodes = fun_data_ymodem_check_file + 7,
    },
    #endif
    #endif
};

// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem_Serial
static const byte fun_data_ymodem_Serial[66] = {
    0x20,0x18, // prelude
    0x0d, // names: Serial
    0x8b,0x54,0x8f,0x07,0x64,0x20,0x64,0x20,0x64,0x88,0x10, // code info
    0x11,0x81,0x0e, // LOAD_NAME '__name__'
    0x16,0x81,0x14, // STORE_NAME '__module__'
    0x10,0x0d, // LOAD_CONST_STRING 'Serial'
    0x16,0x81,0x15, // STORE_NAME '__qualname__'
    0x22,0x87,0x84,0x00, // LOAD_CONST_SMALL_INT 115200
    0x88, // LOAD_CONST_SMALL_INT 8
    0x80, // LOAD_CONST_SMALL_INT 0
    0x81, // LOAD_CONST_SMALL_INT 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x05, // BUILD_TUPLE 5
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x23, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x27, // STORE_NAME '_uart_cb'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x2d, // STORE_NAME '_timer_cb'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x13, // STORE_NAME 'write'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x1c, // STORE_NAME 'read'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x1f, // STORE_NAME 'close'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial___init__
static const byte fun_data_ymodem_Serial___init__[71] = {
    0xf3,0x85,0x80,0x01,0x26, // prelude
    0x23,0x81,0x1b,0x81,0x1c,0x1b,0x81,0x1d,0x81,0x1e,0x81,0x1f,0x81,0x20, // names: __init__, self, uart, buadrate, databits, parity, stopbits, flowctl
    0x80,0x56,0x30,0x2b,0x2b, // code info
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0x10,0x24, // LOAD_CONST_STRING 'flow'
    0xb6, // LOAD_FAST 6
    0x34,0x82,0x05, // CALL_FUNCTION 261
    0xb0, // LOAD_FAST 0
    0x18,0x25, // STORE_ATTR '_uart'
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x26, // LOAD_METHOD 'set_callback'
    0xb0, // LOAD_FAST 0
    0x13,0x27, // LOAD_ATTR '_uart_cb'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x08, // LOAD_GLOBAL 'Queue'
    0x10,0x28, // LOAD_CONST_STRING 'maxsize'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x34,0x82,0x00, // CALL_FUNCTION 256
    0xb0, // LOAD_FAST 0
    0x18,0x29, // STORE_ATTR '_queue'
    0x12,0x06, // LOAD_GLOBAL 'osTimer'
    0x34,0x00, // CALL_FUNCTION 0
    0xb0, // LOAD_FAST 0
    0x18,0x2a, // STORE_ATTR '_timer'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 71,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 15,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 7,
        .n_kwonly_args = 0,
        .n_def_pos_args = 5,
        .qstr_block_name_idx = 35,
        .line_info = fun_data_ymodem_Serial___init__ + 19,
        .line_info_top = fun_data_ymodem_Serial___init__ + 24,
        .opcodes = fun_data_ymodem_Serial___init__ + 24,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial___init__ fun_data_ymodem_Serial___init__[0]
#endif

// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial__uart_cb
static const byte fun_data_ymodem_Serial__uart_cb[33] = {
    0xa1,0x80,0x80,0x40,0x0c, // prelude
    0x27,0x81,0x1b, // names: _uart_cb, self
    0x80,0x5c,0x2b, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x2b, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x2c, // LOAD_METHOD 'put'
    0x51, // LOAD_CONST_NONE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial__uart_cb = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial__uart_cb,
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
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data_ymodem_Serial__uart_cb + 8,
        .line_info_top = fun_data_ymodem_Serial__uart_cb + 11,
        .opcodes = fun_data_ymodem_Serial__uart_cb + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial__uart_cb fun_data_ymodem_Serial__uart_cb[0]
#endif

// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial__timer_cb
static const byte fun_data_ymodem_Serial__timer_cb[33] = {
    0xa1,0x80,0x80,0x40,0x0c, // prelude
    0x2d,0x81,0x1b, // names: _timer_cb, self
    0x80,0x60,0x2b, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x2b, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x2c, // LOAD_METHOD 'put'
    0x51, // LOAD_CONST_NONE
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial__timer_cb = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial__timer_cb,
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
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 4,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 45,
        .line_info = fun_data_ymodem_Serial__timer_cb + 8,
        .line_info_top = fun_data_ymodem_Serial__timer_cb + 11,
        .opcodes = fun_data_ymodem_Serial__timer_cb + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial__timer_cb fun_data_ymodem_Serial__timer_cb[0]
#endif

// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial_write
static const byte fun_data_ymodem_Serial_write[18] = {
    0x22,0x0e, // prelude
    0x13,0x81,0x1b,0x81,0x0f, // names: write, self, data
    0x80,0x64, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x13, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial_write = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial_write,
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
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_ymodem_Serial_write + 7,
        .line_info_top = fun_data_ymodem_Serial_write + 9,
        .opcodes = fun_data_ymodem_Serial_write + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial_write fun_data_ymodem_Serial_write[0]
#endif

// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial_read
static const byte fun_data_ymodem_Serial_read[129] = {
    0xd3,0x01,0x2a, // prelude
    0x1c,0x81,0x1b,0x81,0x21,0x60, // names: read, self, nbytes, timeout
    0x80,0x67,0x25,0x23,0x30,0x22,0x25,0x2d,0x22,0x28,0x23,0x28,0x35,0x29,0x28, // code info
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x2e, // LOAD_METHOD 'any'
    0x36,0x00, // CALL_METHOD 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x6e, // POP_JUMP_IF_FALSE 46
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x69, // POP_JUMP_IF_FALSE 41
    0x50, // LOAD_CONST_FALSE
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR '_timer'
    0x14,0x2f, // LOAD_METHOD 'start'
    0xb2, // LOAD_FAST 2
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x13,0x2d, // LOAD_ATTR '_timer_cb'
    0x36,0x03, // CALL_METHOD 3
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x30, // LOAD_METHOD 'get'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x13,0x2a, // LOAD_ATTR '_timer'
    0x14,0x31, // LOAD_METHOD 'stop'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x1c, // LOAD_METHOD 'read'
    0x12,0x81,0x22, // LOAD_GLOBAL 'min'
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x2e, // LOAD_METHOD 'any'
    0x36,0x00, // CALL_METHOD 0
    0x34,0x02, // CALL_FUNCTION 2
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x2b, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x13,0x29, // LOAD_ATTR '_queue'
    0x14,0x30, // LOAD_METHOD 'get'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial_read = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial_read,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 129,
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
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 28,
        .line_info = fun_data_ymodem_Serial_read + 9,
        .line_info_top = fun_data_ymodem_Serial_read + 24,
        .opcodes = fun_data_ymodem_Serial_read + 24,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial_read fun_data_ymodem_Serial_read[0]
#endif

// child of ymodem_Serial
// frozen bytecode for file ymodem.py, scope ymodem_Serial_close
static const byte fun_data_ymodem_Serial_close[17] = {
    0x11,0x0a, // prelude
    0x1f,0x81,0x1b, // names: close, self
    0x80,0x77, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x25, // LOAD_ATTR '_uart'
    0x14,0x1f, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Serial_close = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial_close,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 17,
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
        .qstr_block_name_idx = 31,
        .line_info = fun_data_ymodem_Serial_close + 5,
        .line_info_top = fun_data_ymodem_Serial_close + 7,
        .opcodes = fun_data_ymodem_Serial_close + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Serial_close fun_data_ymodem_Serial_close[0]
#endif

static const mp_raw_code_t *const children_ymodem_Serial[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial___init__,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial__uart_cb,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial__timer_cb,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial_write,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial_read,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial_close,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_Serial = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Serial,
    .children = (void *)&children_ymodem_Serial,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 66,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 13,
        .line_info = fun_data_ymodem_Serial + 3,
        .line_info_top = fun_data_ymodem_Serial + 14,
        .opcodes = fun_data_ymodem_Serial + 14,
    },
    #endif
    #endif
};

// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem_Modem
static const byte fun_data_ymodem_Modem[1296] = {
    0xf8,0xb0,0x30,0x98,0x02, // prelude
    0x0e, // names: Modem
    0x8b,0x7b,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x83,0x23,0x8b,0x16,0x68,0x40,0x8e,0x62,0x8c,0x20,0x8e,0x47,0x69,0x40,0x6e,0x40,0x8b,0x0b,0x84,0x0d,0x6d,0x20,0x68,0x60,0x72,0x80,0x3c,0x8d,0x22,0x88,0x1e,0x89,0x0c,0x84,0x0b,0x8d,0x16,0x84,0x0b,0x8c,0x0f, // code info
    0x11,0x81,0x0e, // LOAD_NAME '__name__'
    0x16,0x81,0x14, // STORE_NAME '__module__'
    0x10,0x0e, // LOAD_CONST_STRING 'Modem'
    0x16,0x81,0x15, // STORE_NAME '__qualname__'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x22,0xa0,0x21, // LOAD_CONST_SMALL_INT 4129
    0x22,0x80,0xc0,0x42, // LOAD_CONST_SMALL_INT 8258
    0x22,0x80,0xe0,0x63, // LOAD_CONST_SMALL_INT 12387
    0x22,0x81,0x81,0x04, // LOAD_CONST_SMALL_INT 16516
    0x22,0x81,0xa1,0x25, // LOAD_CONST_SMALL_INT 20645
    0x22,0x81,0xc1,0x46, // LOAD_CONST_SMALL_INT 24774
    0x22,0x81,0xe1,0x67, // LOAD_CONST_SMALL_INT 28903
    0x22,0x82,0x82,0x08, // LOAD_CONST_SMALL_INT 33032
    0x22,0x82,0xa2,0x29, // LOAD_CONST_SMALL_INT 37161
    0x22,0x82,0xc2,0x4a, // LOAD_CONST_SMALL_INT 41290
    0x22,0x82,0xe2,0x6b, // LOAD_CONST_SMALL_INT 45419
    0x22,0x83,0x83,0x0c, // LOAD_CONST_SMALL_INT 49548
    0x22,0x83,0xa3,0x2d, // LOAD_CONST_SMALL_INT 53677
    0x22,0x83,0xc3,0x4e, // LOAD_CONST_SMALL_INT 57806
    0x22,0x83,0xe3,0x6f, // LOAD_CONST_SMALL_INT 61935
    0x22,0xa4,0x31, // LOAD_CONST_SMALL_INT 4657
    0x22,0x84,0x10, // LOAD_CONST_SMALL_INT 528
    0x22,0x80,0xe4,0x73, // LOAD_CONST_SMALL_INT 12915
    0x22,0x80,0xc4,0x52, // LOAD_CONST_SMALL_INT 8786
    0x22,0x81,0xa5,0x35, // LOAD_CONST_SMALL_INT 21173
    0x22,0x81,0x85,0x14, // LOAD_CONST_SMALL_INT 17044
    0x22,0x81,0xe5,0x77, // LOAD_CONST_SMALL_INT 29431
    0x22,0x81,0xc5,0x56, // LOAD_CONST_SMALL_INT 25302
    0x22,0x82,0xa6,0x39, // LOAD_CONST_SMALL_INT 37689
    0x22,0x82,0x86,0x18, // LOAD_CONST_SMALL_INT 33560
    0x22,0x82,0xe6,0x7b, // LOAD_CONST_SMALL_INT 45947
    0x22,0x82,0xc6,0x5a, // LOAD_CONST_SMALL_INT 41818
    0x22,0x83,0xa7,0x3d, // LOAD_CONST_SMALL_INT 54205
    0x22,0x83,0x87,0x1c, // LOAD_CONST_SMALL_INT 50076
    0x22,0x83,0xe7,0x7f, // LOAD_CONST_SMALL_INT 62463
    0x22,0x83,0xc7,0x5e, // LOAD_CONST_SMALL_INT 58334
    0x22,0x80,0xc8,0x62, // LOAD_CONST_SMALL_INT 9314
    0x22,0x80,0xe8,0x43, // LOAD_CONST_SMALL_INT 13379
    0x22,0x88,0x20, // LOAD_CONST_SMALL_INT 1056
    0x22,0xa8,0x01, // LOAD_CONST_SMALL_INT 5121
    0x22,0x81,0xc9,0x66, // LOAD_CONST_SMALL_INT 25830
    0x22,0x81,0xe9,0x47, // LOAD_CONST_SMALL_INT 29895
    0x22,0x81,0x89,0x24, // LOAD_CONST_SMALL_INT 17572
    0x22,0x81,0xa9,0x05, // LOAD_CONST_SMALL_INT 21637
    0x22,0x82,0xca,0x6a, // LOAD_CONST_SMALL_INT 42346
    0x22,0x82,0xea,0x4b, // LOAD_CONST_SMALL_INT 46411
    0x22,0x82,0x8a,0x28, // LOAD_CONST_SMALL_INT 34088
    0x22,0x82,0xaa,0x09, // LOAD_CONST_SMALL_INT 38153
    0x22,0x83,0xcb,0x6e, // LOAD_CONST_SMALL_INT 58862
    0x22,0x83,0xeb,0x4f, // LOAD_CONST_SMALL_INT 62927
    0x22,0x83,0x8b,0x2c, // LOAD_CONST_SMALL_INT 50604
    0x22,0x83,0xab,0x0d, // LOAD_CONST_SMALL_INT 54669
    0x22,0x80,0xec,0x53, // LOAD_CONST_SMALL_INT 13907
    0x22,0x80,0xcc,0x72, // LOAD_CONST_SMALL_INT 9842
    0x22,0xac,0x11, // LOAD_CONST_SMALL_INT 5649
    0x22,0x8c,0x30, // LOAD_CONST_SMALL_INT 1584
    0x22,0x81,0xed,0x57, // LOAD_CONST_SMALL_INT 30423
    0x22,0x81,0xcd,0x76, // LOAD_CONST_SMALL_INT 26358
    0x22,0x81,0xad,0x15, // LOAD_CONST_SMALL_INT 22165
    0x22,0x81,0x8d,0x34, // LOAD_CONST_SMALL_INT 18100
    0x22,0x82,0xee,0x5b, // LOAD_CONST_SMALL_INT 46939
    0x22,0x82,0xce,0x7a, // LOAD_CONST_SMALL_INT 42874
    0x22,0x82,0xae,0x19, // LOAD_CONST_SMALL_INT 38681
    0x22,0x82,0x8e,0x38, // LOAD_CONST_SMALL_INT 34616
    0x22,0x83,0xef,0x5f, // LOAD_CONST_SMALL_INT 63455
    0x22,0x83,0xcf,0x7e, // LOAD_CONST_SMALL_INT 59390
    0x22,0x83,0xaf,0x1d, // LOAD_CONST_SMALL_INT 55197
    0x22,0x83,0x8f,0x3c, // LOAD_CONST_SMALL_INT 51132
    0x22,0x81,0x91,0x44, // LOAD_CONST_SMALL_INT 18628
    0x22,0x81,0xb1,0x65, // LOAD_CONST_SMALL_INT 22757
    0x22,0x81,0xd1,0x06, // LOAD_CONST_SMALL_INT 26758
    0x22,0x81,0xf1,0x27, // LOAD_CONST_SMALL_INT 30887
    0x22,0x90,0x40, // LOAD_CONST_SMALL_INT 2112
    0x22,0xb0,0x61, // LOAD_CONST_SMALL_INT 6241
    0x22,0x80,0xd0,0x02, // LOAD_CONST_SMALL_INT 10242
    0x22,0x80,0xf0,0x23, // LOAD_CONST_SMALL_INT 14371
    0x22,0x83,0x93,0x4c, // LOAD_CONST_SMALL_INT 51660
    0x22,0x83,0xb3,0x6d, // LOAD_CONST_SMALL_INT 55789
    0x22,0x83,0xd3,0x0e, // LOAD_CONST_SMALL_INT 59790
    0x22,0x83,0xf3,0x2f, // LOAD_CONST_SMALL_INT 63919
    0x22,0x82,0x92,0x48, // LOAD_CONST_SMALL_INT 35144
    0x22,0x82,0xb2,0x69, // LOAD_CONST_SMALL_INT 39273
    0x22,0x82,0xd2,0x0a, // LOAD_CONST_SMALL_INT 43274
    0x22,0x82,0xf2,0x2b, // LOAD_CONST_SMALL_INT 47403
    0x22,0x81,0xb5,0x75, // LOAD_CONST_SMALL_INT 23285
    0x22,0x81,0x95,0x54, // LOAD_CONST_SMALL_INT 19156
    0x22,0x81,0xf5,0x37, // LOAD_CONST_SMALL_INT 31415
    0x22,0x81,0xd5,0x16, // LOAD_CONST_SMALL_INT 27286
    0x22,0xb4,0x71, // LOAD_CONST_SMALL_INT 6769
    0x22,0x94,0x50, // LOAD_CONST_SMALL_INT 2640
    0x22,0x80,0xf4,0x33, // LOAD_CONST_SMALL_INT 14899
    0x22,0x80,0xd4,0x12, // LOAD_CONST_SMALL_INT 10770
    0x22,0x83,0xb7,0x7d, // LOAD_CONST_SMALL_INT 56317
    0x22,0x83,0x97,0x5c, // LOAD_CONST_SMALL_INT 52188
    0x22,0x83,0xf7,0x3f, // LOAD_CONST_SMALL_INT 64447
    0x22,0x83,0xd7,0x1e, // LOAD_CONST_SMALL_INT 60318
    0x22,0x82,0xb6,0x79, // LOAD_CONST_SMALL_INT 39801
    0x22,0x82,0x96,0x58, // LOAD_CONST_SMALL_INT 35672
    0x22,0x82,0xf6,0x3b, // LOAD_CONST_SMALL_INT 47931
    0x22,0x82,0xd6,0x1a, // LOAD_CONST_SMALL_INT 43802
    0x22,0x81,0xd9,0x26, // LOAD_CONST_SMALL_INT 27814
    0x22,0x81,0xf9,0x07, // LOAD_CONST_SMALL_INT 31879
    0x22,0x81,0x99,0x64, // LOAD_CONST_SMALL_INT 19684
    0x22,0x81,0xb9,0x45, // LOAD_CONST_SMALL_INT 23749
    0x22,0x80,0xd8,0x22, // LOAD_CONST_SMALL_INT 11298
    0x22,0x80,0xf8,0x03, // LOAD_CONST_SMALL_INT 15363
    0x22,0x98,0x60, // LOAD_CONST_SMALL_INT 3168
    0x22,0xb8,0x41, // LOAD_CONST_SMALL_INT 7233
    0x22,0x83,0xdb,0x2e, // LOAD_CONST_SMALL_INT 60846
    0x22,0x83,0xfb,0x0f, // LOAD_CONST_SMALL_INT 64911
    0x22,0x83,0x9b,0x6c, // LOAD_CONST_SMALL_INT 52716
    0x22,0x83,0xbb,0x4d, // LOAD_CONST_SMALL_INT 56781
    0x22,0x82,0xda,0x2a, // LOAD_CONST_SMALL_INT 44330
    0x22,0x82,0xfa,0x0b, // LOAD_CONST_SMALL_INT 48395
    0x22,0x82,0x9a,0x68, // LOAD_CONST_SMALL_INT 36200
    0x22,0x82,0xba,0x49, // LOAD_CONST_SMALL_INT 40265
    0x22,0x81,0xfd,0x17, // LOAD_CONST_SMALL_INT 32407
    0x22,0x81,0xdd,0x36, // LOAD_CONST_SMALL_INT 28342
    0x22,0x81,0xbd,0x55, // LOAD_CONST_SMALL_INT 24277
    0x22,0x81,0x9d,0x74, // LOAD_CONST_SMALL_INT 20212
    0x22,0x80,0xfc,0x13, // LOAD_CONST_SMALL_INT 15891
    0x22,0x80,0xdc,0x32, // LOAD_CONST_SMALL_INT 11826
    0x22,0xbc,0x51, // LOAD_CONST_SMALL_INT 7761
    0x22,0x9c,0x70, // LOAD_CONST_SMALL_INT 3696
    0x22,0x83,0xff,0x1f, // LOAD_CONST_SMALL_INT 65439
    0x22,0x83,0xdf,0x3e, // LOAD_CONST_SMALL_INT 61374
    0x22,0x83,0xbf,0x5d, // LOAD_CONST_SMALL_INT 57309
    0x22,0x83,0x9f,0x7c, // LOAD_CONST_SMALL_INT 53244
    0x22,0x82,0xfe,0x1b, // LOAD_CONST_SMALL_INT 48923
    0x22,0x82,0xde,0x3a, // LOAD_CONST_SMALL_INT 44858
    0x22,0x82,0xbe,0x59, // LOAD_CONST_SMALL_INT 40793
    0x22,0x82,0x9e,0x78, // LOAD_CONST_SMALL_INT 36728
    0x22,0x82,0xa3,0x08, // LOAD_CONST_SMALL_INT 37256
    0x22,0x82,0x83,0x29, // LOAD_CONST_SMALL_INT 33193
    0x22,0x82,0xe3,0x4a, // LOAD_CONST_SMALL_INT 45514
    0x22,0x82,0xc3,0x6b, // LOAD_CONST_SMALL_INT 41451
    0x22,0x83,0xa2,0x0c, // LOAD_CONST_SMALL_INT 53516
    0x22,0x83,0x82,0x2d, // LOAD_CONST_SMALL_INT 49453
    0x22,0x83,0xe2,0x4e, // LOAD_CONST_SMALL_INT 61774
    0x22,0x83,0xc2,0x6f, // LOAD_CONST_SMALL_INT 57711
    0x22,0xa1,0x00, // LOAD_CONST_SMALL_INT 4224
    0x22,0x81,0x21, // LOAD_CONST_SMALL_INT 161
    0x22,0x80,0xe1,0x42, // LOAD_CONST_SMALL_INT 12482
    0x22,0x80,0xc1,0x63, // LOAD_CONST_SMALL_INT 8419
    0x22,0x81,0xa0,0x04, // LOAD_CONST_SMALL_INT 20484
    0x22,0x81,0x80,0x25, // LOAD_CONST_SMALL_INT 16421
    0x22,0x81,0xe0,0x46, // LOAD_CONST_SMALL_INT 28742
    0x22,0x81,0xc0,0x67, // LOAD_CONST_SMALL_INT 24679
    0x22,0x82,0x87,0x39, // LOAD_CONST_SMALL_INT 33721
    0x22,0x82,0xa7,0x18, // LOAD_CONST_SMALL_INT 37784
    0x22,0x82,0xc7,0x7b, // LOAD_CONST_SMALL_INT 41979
    0x22,0x82,0xe7,0x5a, // LOAD_CONST_SMALL_INT 46042
    0x22,0x83,0x86,0x3d, // LOAD_CONST_SMALL_INT 49981
    0x22,0x83,0xa6,0x1c, // LOAD_CONST_SMALL_INT 54044
    0x22,0x83,0xc6,0x7f, // LOAD_CONST_SMALL_INT 58239
    0x22,0x83,0xe6,0x5e, // LOAD_CONST_SMALL_INT 62302
    0x22,0x85,0x31, // LOAD_CONST_SMALL_INT 689
    0x22,0xa5,0x10, // LOAD_CONST_SMALL_INT 4752
    0x22,0x80,0xc5,0x73, // LOAD_CONST_SMALL_INT 8947
    0x22,0x80,0xe5,0x52, // LOAD_CONST_SMALL_INT 13010
    0x22,0x81,0x84,0x35, // LOAD_CONST_SMALL_INT 16949
    0x22,0x81,0xa4,0x14, // LOAD_CONST_SMALL_INT 21012
    0x22,0x81,0xc4,0x77, // LOAD_CONST_SMALL_INT 25207
    0x22,0x81,0xe4,0x56, // LOAD_CONST_SMALL_INT 29270
    0x22,0x82,0xeb,0x6a, // LOAD_CONST_SMALL_INT 46570
    0x22,0x82,0xcb,0x4b, // LOAD_CONST_SMALL_INT 42443
    0x22,0x82,0xab,0x28, // LOAD_CONST_SMALL_INT 38312
    0x22,0x82,0x8b,0x09, // LOAD_CONST_SMALL_INT 34185
    0x22,0x83,0xea,0x6e, // LOAD_CONST_SMALL_INT 62830
    0x22,0x83,0xca,0x4f, // LOAD_CONST_SMALL_INT 58703
    0x22,0x83,0xaa,0x2c, // LOAD_CONST_SMALL_INT 54572
    0x22,0x83,0x8a,0x0d, // LOAD_CONST_SMALL_INT 50445
    0x22,0x80,0xe9,0x62, // LOAD_CONST_SMALL_INT 13538
    0x22,0x80,0xc9,0x43, // LOAD_CONST_SMALL_INT 9411
    0x22,0xa9,0x20, // LOAD_CONST_SMALL_INT 5280
    0x22,0x89,0x01, // LOAD_CONST_SMALL_INT 1153
    0x22,0x81,0xe8,0x66, // LOAD_CONST_SMALL_INT 29798
    0x22,0x81,0xc8,0x47, // LOAD_CONST_SMALL_INT 25671
    0x22,0x81,0xa8,0x24, // LOAD_CONST_SMALL_INT 21540
    0x22,0x81,0x88,0x05, // LOAD_CONST_SMALL_INT 17413
    0x22,0x82,0xcf,0x5b, // LOAD_CONST_SMALL_INT 42971
    0x22,0x82,0xef,0x7a, // LOAD_CONST_SMALL_INT 47098
    0x22,0x82,0x8f,0x19, // LOAD_CONST_SMALL_INT 34713
    0x22,0x82,0xaf,0x38, // LOAD_CONST_SMALL_INT 38840
    0x22,0x83,0xce,0x5f, // LOAD_CONST_SMALL_INT 59231
    0x22,0x83,0xee,0x7e, // LOAD_CONST_SMALL_INT 63358
    0x22,0x83,0x8e,0x1d, // LOAD_CONST_SMALL_INT 50973
    0x22,0x83,0xae,0x3c, // LOAD_CONST_SMALL_INT 55100
    0x22,0x80,0xcd,0x53, // LOAD_CONST_SMALL_INT 9939
    0x22,0x80,0xed,0x72, // LOAD_CONST_SMALL_INT 14066
    0x22,0x8d,0x11, // LOAD_CONST_SMALL_INT 1681
    0x22,0xad,0x30, // LOAD_CONST_SMALL_INT 5808
    0x22,0x81,0xcc,0x57, // LOAD_CONST_SMALL_INT 26199
    0x22,0x81,0xec,0x76, // LOAD_CONST_SMALL_INT 30326
    0x22,0x81,0x8c,0x15, // LOAD_CONST_SMALL_INT 17941
    0x22,0x81,0xac,0x34, // LOAD_CONST_SMALL_INT 22068
    0x22,0x83,0xb2,0x4c, // LOAD_CONST_SMALL_INT 55628
    0x22,0x83,0x92,0x6d, // LOAD_CONST_SMALL_INT 51565
    0x22,0x83,0xf2,0x0e, // LOAD_CONST_SMALL_INT 63758
    0x22,0x83,0xd2,0x2f, // LOAD_CONST_SMALL_INT 59695
    0x22,0x82,0xb3,0x48, // LOAD_CONST_SMALL_INT 39368
    0x22,0x82,0x93,0x69, // LOAD_CONST_SMALL_INT 35305
    0x22,0x82,0xf3,0x0a, // LOAD_CONST_SMALL_INT 47498
    0x22,0x82,0xd3,0x2b, // LOAD_CONST_SMALL_INT 43435
    0x22,0x81,0xb0,0x44, // LOAD_CONST_SMALL_INT 22596
    0x22,0x81,0x90,0x65, // LOAD_CONST_SMALL_INT 18533
    0x22,0x81,0xf0,0x06, // LOAD_CONST_SMALL_INT 30726
    0x22,0x81,0xd0,0x27, // LOAD_CONST_SMALL_INT 26663
    0x22,0xb1,0x40, // LOAD_CONST_SMALL_INT 6336
    0x22,0x91,0x61, // LOAD_CONST_SMALL_INT 2273
    0x22,0x80,0xf1,0x02, // LOAD_CONST_SMALL_INT 14466
    0x22,0x80,0xd1,0x23, // LOAD_CONST_SMALL_INT 10403
    0x22,0x83,0x96,0x7d, // LOAD_CONST_SMALL_INT 52093
    0x22,0x83,0xb6,0x5c, // LOAD_CONST_SMALL_INT 56156
    0x22,0x83,0xd6,0x3f, // LOAD_CONST_SMALL_INT 60223
    0x22,0x83,0xf6,0x1e, // LOAD_CONST_SMALL_INT 64286
    0x22,0x82,0x97,0x79, // LOAD_CONST_SMALL_INT 35833
    0x22,0x82,0xb7,0x58, // LOAD_CONST_SMALL_INT 39896
    0x22,0x82,0xd7,0x3b, // LOAD_CONST_SMALL_INT 43963
    0x22,0x82,0xf7,0x1a, // LOAD_CONST_SMALL_INT 48026
    0x22,0x81,0x94,0x75, // LOAD_CONST_SMALL_INT 19061
    0x22,0x81,0xb4,0x54, // LOAD_CONST_SMALL_INT 23124
    0x22,0x81,0xd4,0x37, // LOAD_CONST_SMALL_INT 27191
    0x22,0x81,0xf4,0x16, // LOAD_CONST_SMALL_INT 31254
    0x22,0x95,0x71, // LOAD_CONST_SMALL_INT 2801
    0x22,0xb5,0x50, // LOAD_CONST_SMALL_INT 6864
    0x22,0x80,0xd5,0x33, // LOAD_CONST_SMALL_INT 10931
    0x22,0x80,0xf5,0x12, // LOAD_CONST_SMALL_INT 14994
    0x22,0x83,0xfa,0x2e, // LOAD_CONST_SMALL_INT 64814
    0x22,0x83,0xda,0x0f, // LOAD_CONST_SMALL_INT 60687
    0x22,0x83,0xba,0x6c, // LOAD_CONST_SMALL_INT 56684
    0x22,0x83,0x9a,0x4d, // LOAD_CONST_SMALL_INT 52557
    0x22,0x82,0xfb,0x2a, // LOAD_CONST_SMALL_INT 48554
    0x22,0x82,0xdb,0x0b, // LOAD_CONST_SMALL_INT 44427
    0x22,0x82,0xbb,0x68, // LOAD_CONST_SMALL_INT 40424
    0x22,0x82,0x9b,0x49, // LOAD_CONST_SMALL_INT 36297
    0x22,0x81,0xf8,0x26, // LOAD_CONST_SMALL_INT 31782
    0x22,0x81,0xd8,0x07, // LOAD_CONST_SMALL_INT 27655
    0x22,0x81,0xb8,0x64, // LOAD_CONST_SMALL_INT 23652
    0x22,0x81,0x98,0x45, // LOAD_CONST_SMALL_INT 19525
    0x22,0x80,0xf9,0x22, // LOAD_CONST_SMALL_INT 15522
    0x22,0x80,0xd9,0x03, // LOAD_CONST_SMALL_INT 11395
    0x22,0xb9,0x60, // LOAD_CONST_SMALL_INT 7392
    0x22,0x99,0x41, // LOAD_CONST_SMALL_INT 3265
    0x22,0x83,0xde,0x1f, // LOAD_CONST_SMALL_INT 61215
    0x22,0x83,0xfe,0x3e, // LOAD_CONST_SMALL_INT 65342
    0x22,0x83,0x9e,0x5d, // LOAD_CONST_SMALL_INT 53085
    0x22,0x83,0xbe,0x7c, // LOAD_CONST_SMALL_INT 57212
    0x22,0x82,0xdf,0x1b, // LOAD_CONST_SMALL_INT 44955
    0x22,0x82,0xff,0x3a, // LOAD_CONST_SMALL_INT 49082
    0x22,0x82,0x9f,0x59, // LOAD_CONST_SMALL_INT 36825
    0x22,0x82,0xbf,0x78, // LOAD_CONST_SMALL_INT 40952
    0x22,0x81,0xdc,0x17, // LOAD_CONST_SMALL_INT 28183
    0x22,0x81,0xfc,0x36, // LOAD_CONST_SMALL_INT 32310
    0x22,0x81,0x9c,0x55, // LOAD_CONST_SMALL_INT 20053
    0x22,0x81,0xbc,0x74, // LOAD_CONST_SMALL_INT 24180
    0x22,0x80,0xdd,0x13, // LOAD_CONST_SMALL_INT 11923
    0x22,0x80,0xfd,0x32, // LOAD_CONST_SMALL_INT 16050
    0x22,0x9d,0x51, // LOAD_CONST_SMALL_INT 3793
    0x22,0xbd,0x70, // LOAD_CONST_SMALL_INT 7920
    0x2b,0x82,0x00, // BUILD_LIST 256
    0x16,0x59, // STORE_NAME 'crc_table'
    0x10,0x15, // LOAD_CONST_STRING 'ymodem1k'
    0x10,0x16, // LOAD_CONST_STRING 'rzsz'
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x23, // STORE_NAME '__init__'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x41, // STORE_NAME 'abort'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2a,0x05, // BUILD_TUPLE 5
    0x53, // LOAD_NULL
    0x33,0x02, // MAKE_FUNCTION_DEFARGS 2
    0x16,0x1d, // STORE_NAME 'recv'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x03, // MAKE_FUNCTION_DEFARGS 3
    0x16,0x43, // STORE_NAME '_in_transfer_mode'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x04, // MAKE_FUNCTION_DEFARGS 4
    0x16,0x44, // STORE_NAME '_get_file_header'
    0x11,0x81,0x16, // LOAD_NAME 'staticmethod'
    0x32,0x05, // MAKE_FUNCTION 5
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x4f, // STORE_NAME '_check_path'
    0x11,0x81,0x16, // LOAD_NAME 'staticmethod'
    0x10,0x17, // LOAD_CONST_STRING ''
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x06, // MAKE_FUNCTION_DEFARGS 6
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x42, // STORE_NAME '_delete_failed_file'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x07, // MAKE_FUNCTION_DEFARGS 7
    0x16,0x45, // STORE_NAME '_verify_complement'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x46, // STORE_NAME '_verify_recv_checksum'
    0x11,0x81,0x16, // LOAD_NAME 'staticmethod'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x09, // MAKE_FUNCTION_DEFARGS 9
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x58, // STORE_NAME '_calc_checksum'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0a, // MAKE_FUNCTION_DEFARGS 10
    0x16,0x57, // STORE_NAME '_calc_crc'
    0x11,0x14, // LOAD_NAME 'check_file'
    0x34,0x00, // CALL_FUNCTION 0
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x51, // LOAD_CONST_NONE
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x0b, // MAKE_FUNCTION_DEFARGS 11
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x21, // STORE_NAME 'send'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x22,0x80,0xce,0x10, // LOAD_CONST_SMALL_INT 10000
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x2a,0x03, // BUILD_TUPLE 3
    0x53, // LOAD_NULL
    0x33,0x0c, // MAKE_FUNCTION_DEFARGS 12
    0x16,0x5f, // STORE_NAME '_wait_c'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x0d, // MAKE_FUNCTION_DEFARGS 13
    0x16,0x63, // STORE_NAME '_make_file_header_info'
    0x11,0x81,0x16, // LOAD_NAME 'staticmethod'
    0x32,0x0e, // MAKE_FUNCTION 14
    0x34,0x01, // CALL_FUNCTION 1
    0x16,0x69, // STORE_NAME '_make_send_header'
    0x32,0x0f, // MAKE_FUNCTION 15
    0x16,0x71, // STORE_NAME '_make_send_checksum'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2a,0x04, // BUILD_TUPLE 4
    0x53, // LOAD_NULL
    0x33,0x10, // MAKE_FUNCTION_DEFARGS 16
    0x16,0x62, // STORE_NAME 'serial_trans'
    0x32,0x11, // MAKE_FUNCTION 17
    0x16,0x64, // STORE_NAME '_make_file_body_info'
    0x22,0x80,0xce,0x10, // LOAD_CONST_SMALL_INT 10000
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x12, // MAKE_FUNCTION_DEFARGS 18
    0x16,0x66, // STORE_NAME '_wait_nak_ack'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x13, // MAKE_FUNCTION_DEFARGS 19
    0x16,0x67, // STORE_NAME '_send_end_packet'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem___init__
static const byte fun_data_ymodem_Modem___init__[167] = {
    0xf9,0x84,0x01,0x34, // prelude
    0x23,0x81,0x1b,0x33,0x34,0x35,0x81,0x23, // names: __init__, self, reader, writer, mode, program
    0x80,0xa0,0x2f,0x4f,0x24,0x24,0x24,0x25,0x31,0x29,0x1f,0x61,0x25,0x25,0x24,0x24,0x24,0x24, // code info
    0xb3, // LOAD_FAST 3
    0x10,0x15, // LOAD_CONST_STRING 'ymodem1k'
    0xd9, // BINARY_OP 2 __eq__
    0x43,0x49, // POP_JUMP_IF_TRUE 9
    0x12,0x32, // LOAD_GLOBAL 'AssertionError'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0xb3, // LOAD_FAST 3
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb4, // LOAD_FAST 4
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0xdd, // BINARY_OP 6 <in>
    0x43,0x49, // POP_JUMP_IF_TRUE 9
    0x12,0x32, // LOAD_GLOBAL 'AssertionError'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0xb4, // LOAD_FAST 4
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x33, // STORE_ATTR 'reader'
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0x18,0x34, // STORE_ATTR 'writer'
    0xb3, // LOAD_FAST 3
    0xb0, // LOAD_FAST 0
    0x18,0x35, // STORE_ATTR 'mode'
    0x12,0x81,0x24, // LOAD_GLOBAL 'dict'
    0x10,0x16, // LOAD_CONST_STRING 'rzsz'
    0x12,0x81,0x05, // LOAD_GLOBAL 'USE_LENGTH_FIELD'
    0x12,0x81,0x06, // LOAD_GLOBAL 'USE_DATE_FIELD'
    0xed, // BINARY_OP 22 __or__
    0x12,0x81,0x07, // LOAD_GLOBAL 'USE_MODE_FIELD'
    0xed, // BINARY_OP 22 __or__
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0xed, // BINARY_OP 22 __or__
    0x10,0x36, // LOAD_CONST_STRING 'rbsb'
    0x12,0x81,0x05, // LOAD_GLOBAL 'USE_LENGTH_FIELD'
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0xed, // BINARY_OP 22 __or__
    0x10,0x37, // LOAD_CONST_STRING 'pyam'
    0x12,0x81,0x05, // LOAD_GLOBAL 'USE_LENGTH_FIELD'
    0x12,0x81,0x06, // LOAD_GLOBAL 'USE_DATE_FIELD'
    0xed, // BINARY_OP 22 __or__
    0x12,0x81,0x08, // LOAD_GLOBAL 'USE_SN_FIELD'
    0xed, // BINARY_OP 22 __or__
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0xed, // BINARY_OP 22 __or__
    0x12,0x81,0x0a, // LOAD_GLOBAL 'ALLOW_YMODEM_G'
    0xed, // BINARY_OP 22 __or__
    0x10,0x38, // LOAD_CONST_STRING 'cyam'
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0x10,0x39, // LOAD_CONST_STRING 'kimp'
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0x34,0x8a,0x00, // CALL_FUNCTION 1280
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xb0, // LOAD_FAST 0
    0x18,0x3a, // STORE_ATTR 'program_features'
    0x10,0x17, // LOAD_CONST_STRING ''
    0xb0, // LOAD_FAST 0
    0x18,0x3b, // STORE_ATTR '_recv_file_name'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3c, // STORE_ATTR '_remaining_data_length'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3d, // STORE_ATTR '_recv_file_mtime'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3e, // STORE_ATTR '_recv_mode'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x3f, // STORE_ATTR '_recv_sn'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xb0, // LOAD_FAST 0
    0x18,0x40, // STORE_ATTR 'total_size'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 167,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 16,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 35,
        .line_info = fun_data_ymodem_Modem___init__ + 12,
        .line_info_top = fun_data_ymodem_Modem___init__ + 30,
        .opcodes = fun_data_ymodem_Modem___init__ + 30,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem___init__ fun_data_ymodem_Modem___init__[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem_abort
static const byte fun_data_ymodem_Modem_abort[38] = {
    0xa2,0x01,0x11, // prelude
    0x41,0x81,0x1b,0x81,0x25, // names: abort, self, count
    0x80,0xb5,0x2d,0x00, // code info
    0xb0, // LOAD_FAST 0
    0x20,0x00,0x01, // MAKE_CLOSURE 0
    0x12,0x81,0x26, // LOAD_GLOBAL 'range'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x42, // LOAD_METHOD '_delete_failed_file'
    0x25,0x00, // LOAD_DEREF 0
    0x13,0x3b, // LOAD_ATTR '_recv_file_name'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ymodem_Modem_abort
// frozen bytecode for file ymodem.py, scope ymodem_Modem_abort__lt_listcomp_gt_
static const byte fun_data_ymodem_Modem_abort__lt_listcomp_gt_[30] = {
    0x52,0x0e, // prelude
    0x7c,0x81,0x3f,0x81,0x3f, // names: <listcomp>, *, *
    0x80,0xb5, // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb1, // LOAD_FAST 1
    0x5f, // GET_ITER_STACK
    0x4b,0x0e, // FOR_ITER 14
    0xc2, // STORE_FAST 2
    0x25,0x00, // LOAD_DEREF 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x03, // LOAD_GLOBAL 'CAN'
    0x36,0x01, // CALL_METHOD 1
    0x2f,0x14, // STORE_COMP 20
    0x42,0x30, // JUMP -16
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_abort__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_abort__lt_listcomp_gt_,
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
        .n_state = 11,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 124,
        .line_info = fun_data_ymodem_Modem_abort__lt_listcomp_gt_ + 7,
        .line_info_top = fun_data_ymodem_Modem_abort__lt_listcomp_gt_ + 9,
        .opcodes = fun_data_ymodem_Modem_abort__lt_listcomp_gt_ + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem_abort__lt_listcomp_gt_ fun_data_ymodem_Modem_abort__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_ymodem_Modem_abort[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_abort__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_abort = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_abort,
    .children = (void *)&children_ymodem_Modem_abort,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 38,
    .n_children = 1,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 65,
        .line_info = fun_data_ymodem_Modem_abort + 8,
        .line_info_top = fun_data_ymodem_Modem_abort + 11,
        .opcodes = fun_data_ymodem_Modem_abort + 12,
    },
    #endif
    #endif
};

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem_recv
static const byte fun_data_ymodem_Modem_recv[610] = {
    0xc2,0x97,0x80,0x01,0xbe,0x02, // prelude
    0x1d,0x81,0x1b,0x81,0x27,0x61,0x60,0x81,0x28,0x1e, // names: recv, self, crc_mode, retry, timeout, delay, callback
    0x80,0xba,0x60,0x23,0x22,0x29,0x26,0x28,0x26,0x4b,0x22,0x22,0x22,0x24,0x22,0x22,0x23,0x20,0x22,0x20,0x26,0x27,0x24,0x23,0x26,0x27,0x24,0x23,0x28,0x23,0x29,0x26,0x28,0x28,0x26,0x42,0x22,0x29,0x2a,0x27,0x23,0x29,0x42,0x22,0x4a,0x24,0x28,0x25,0x26,0x25,0x29,0x43,0x2b,0x33,0x4c,0x25,0x24,0x23,0x27,0x2c,0x2a,0x27,0x2a,0x29,0x2c,0x27,0x45,0x27,0x27,0x23,0x29,0x28,0x28,0x28,0x42,0x42,0x20,0x20,0x28,0x25,0x24,0x29,0x28,0x52,0x29, // code info
    0x48,0xd9,0x03, // SETUP_EXCEPT 473
    0x51, // LOAD_CONST_NONE
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x14,0x43, // LOAD_METHOD '_in_transfer_mode'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x36,0x03, // CALL_METHOD 3
    0xc7, // STORE_FAST 7
    0xb7, // LOAD_FAST 7
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x44, // LOAD_METHOD '_get_file_header'
    0xb7, // LOAD_FAST 7
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb0, // LOAD_FAST 0
    0x14,0x43, // LOAD_METHOD '_in_transfer_mode'
    0xb1, // LOAD_FAST 1
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x36,0x03, // CALL_METHOD 3
    0xc7, // STORE_FAST 7
    0x42,0x42, // JUMP 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc8, // STORE_FAST 8
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc9, // STORE_FAST 9
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xca, // STORE_FAST 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0xcb, // STORE_FAST 11
    0x80, // LOAD_CONST_SMALL_INT 0
    0xcc, // STORE_FAST 12
    0x23,0x08, // LOAD_CONST_OBJ 8
    0xcd, // STORE_FAST 13
    0x80, // LOAD_CONST_SMALL_INT 0
    0xce, // STORE_FAST 14
    0xb7, // LOAD_FAST 7
    0x12,0x7e, // LOAD_GLOBAL 'SOH'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0xba, // LOAD_FAST 10
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xca, // STORE_FAST 10
    0x42,0x98,0x81, // JUMP 152
    0xb7, // LOAD_FAST 7
    0x12,0x7f, // LOAD_GLOBAL 'STX'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4e, // POP_JUMP_IF_FALSE 14
    0xba, // LOAD_FAST 10
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0xca, // STORE_FAST 10
    0x42,0x84,0x81, // JUMP 132
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x00, // LOAD_GLOBAL 'EOT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xbf,0x80, // POP_JUMP_IF_FALSE 63
    0xbc, // LOAD_FAST 12
    0x44,0x67, // POP_JUMP_IF_FALSE 39
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0x14,0x1f, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x12,0x81,0x29, // LOAD_GLOBAL 'callable'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb5, // LOAD_FAST 5
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR '_recv_file_name'
    0xb9, // LOAD_FAST 9
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x1d, // LOAD_METHOD 'recv'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xcc, // STORE_FAST 12
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x42,0x7a, // JUMP 58
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x03, // LOAD_GLOBAL 'CAN'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x5a, // POP_JUMP_IF_FALSE 26
    0xbc, // LOAD_FAST 12
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb0, // LOAD_FAST 0
    0x14,0x42, // LOAD_METHOD '_delete_failed_file'
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR '_recv_file_name'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xcc, // STORE_FAST 12
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x42,0x59, // JUMP 25
    0xbe, // LOAD_FAST 14
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xce, // STORE_FAST 14
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0xbe, // LOAD_FAST 14
    0xb2, // LOAD_FAST 2
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x42,0xd4,0x7e, // JUMP -172
    0xb0, // LOAD_FAST 0
    0x14,0x45, // LOAD_METHOD '_verify_complement'
    0xb3, // LOAD_FAST 3
    0xbb, // LOAD_FAST 11
    0x36,0x02, // CALL_METHOD 2
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x42,0xbb,0x81, // JUMP 187
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0xba, // LOAD_FAST 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb1, // LOAD_FAST 1
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0xcf, // STORE_FAST 15
    0xbf, // LOAD_FAST 15
    0x44,0xac,0x81, // POP_JUMP_IF_FALSE 172
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xbf, // LOAD_FAST 15
    0x34,0x01, // CALL_FUNCTION 1
    0xba, // LOAD_FAST 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb1, // LOAD_FAST 1
    0xf2, // BINARY_OP 27 __add__
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x9d,0x81, // POP_JUMP_IF_FALSE 157
    0xb0, // LOAD_FAST 0
    0x14,0x46, // LOAD_METHOD '_verify_recv_checksum'
    0xb1, // LOAD_FAST 1
    0xbf, // LOAD_FAST 15
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0x26,0x10, // STORE_FAST_N 16
    0xcf, // STORE_FAST 15
    0x24,0x10, // LOAD_FAST_N 16
    0x44,0x8a,0x81, // POP_JUMP_IF_FALSE 138
    0xb8, // LOAD_FAST 8
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc8, // STORE_FAST 8
    0xba, // LOAD_FAST 10
    0x26,0x11, // STORE_FAST_N 17
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR '_remaining_data_length'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x12,0x81,0x22, // LOAD_GLOBAL 'min'
    0x24,0x11, // LOAD_FAST_N 17
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR '_remaining_data_length'
    0x34,0x02, // CALL_FUNCTION 2
    0x26,0x11, // STORE_FAST_N 17
    0xb0, // LOAD_FAST 0
    0x57, // DUP_TOP
    0x13,0x3c, // LOAD_ATTR '_remaining_data_length'
    0x24,0x11, // LOAD_FAST_N 17
    0xe6, // BINARY_OP 15 __isub__
    0x5a, // ROT_TWO
    0x18,0x3c, // STORE_ATTR '_remaining_data_length'
    0x12,0x02, // LOAD_GLOBAL 'gc'
    0x14,0x47, // LOAD_METHOD 'collect'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xbd, // LOAD_FAST 13
    0xbf, // LOAD_FAST 15
    0x51, // LOAD_CONST_NONE
    0x24,0x11, // LOAD_FAST_N 17
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xe5, // BINARY_OP 14 __iadd__
    0xcd, // STORE_FAST 13
    0xb9, // LOAD_FAST 9
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xbf, // LOAD_FAST 15
    0x34,0x01, // CALL_FUNCTION 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc9, // STORE_FAST 9
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xbd, // LOAD_FAST 13
    0x34,0x01, // CALL_FUNCTION 1
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0xdd, // BINARY_OP 6 <in>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb6, // LOAD_FAST 6
    0x14,0x13, // LOAD_METHOD 'write'
    0xbd, // LOAD_FAST 13
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x23,0x08, // LOAD_CONST_OBJ 8
    0xcd, // STORE_FAST 13
    0x42,0x51, // JUMP 17
    0xb0, // LOAD_FAST 0
    0x13,0x3c, // LOAD_ATTR '_remaining_data_length'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb6, // LOAD_FAST 6
    0x14,0x13, // LOAD_METHOD 'write'
    0xbd, // LOAD_FAST 13
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x23,0x08, // LOAD_CONST_OBJ 8
    0xcd, // STORE_FAST 13
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x48, // LOAD_METHOD 'sleep_ms'
    0x85, // LOAD_CONST_SMALL_INT 5
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xbb, // LOAD_FAST 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x22,0x82,0x00, // LOAD_CONST_SMALL_INT 256
    0xf8, // BINARY_OP 33 __mod__
    0xcb, // STORE_FAST 11
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x42,0x66, // JUMP 38
    0x42,0x40, // JUMP 0
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xcf, // STORE_FAST 15
    0xbf, // LOAD_FAST 15
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x42, // JUMP 2
    0x42,0x2f, // JUMP -17
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x42,0x40, // JUMP 0
    0x42,0xe4,0x7c, // JUMP -412
    0x4a,0x1f, // POP_EXCEPT_JUMP 31
    0x57, // DUP_TOP
    0x12,0x81,0x19, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0x26,0x12, // STORE_FAST_N 18
    0x49,0x0b, // SETUP_FINALLY 11
    0x12,0x04, // LOAD_GLOBAL 'sys'
    0x14,0x49, // LOAD_METHOD 'print_exception'
    0x24,0x12, // LOAD_FAST_N 18
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x26,0x12, // STORE_FAST_N 18
    0x28,0x12, // DELETE_FAST 18
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_recv = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_recv,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 610,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 25,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 5,
        .qstr_block_name_idx = 29,
        .line_info = fun_data_ymodem_Modem_recv + 16,
        .line_info_top = fun_data_ymodem_Modem_recv + 101,
        .opcodes = fun_data_ymodem_Modem_recv + 101,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem_recv fun_data_ymodem_Modem_recv[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__in_transfer_mode
static const byte fun_data_ymodem_Modem__in_transfer_mode[188] = {
    0xdb,0x85,0x01,0x52, // prelude
    0x43,0x81,0x1b,0x81,0x27,0x61,0x81,0x28,0x60,0x81,0x2b,0x81,0x2c, // names: _in_transfer_mode, self, crc_mode, retry, delay, timeout, cancel, error_count
    0x90,0x1c,0x20,0x25,0x26,0x25,0x27,0x2a,0x28,0x46,0x22,0x2a,0x28,0x24,0x28,0x28,0x24,0x22,0x26,0x22,0x26,0x22,0x27,0x22,0x27,0x23,0x42,0x44, // code info
    0xb6, // LOAD_FAST 6
    0xb2, // LOAD_FAST 2
    0xdb, // BINARY_OP 4 __ge__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x44,0x5f, // POP_JUMP_IF_FALSE 31
    0xb6, // LOAD_FAST 6
    0xb2, // LOAD_FAST 2
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf6, // BINARY_OP 31 __floordiv__
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x58, // POP_JUMP_IF_FALSE 24
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x04, // LOAD_GLOBAL 'CRC'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x4c, // POP_JUMP_IF_TRUE 12
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x4a, // LOAD_METHOD 'sleep'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x42,0x58, // JUMP 24
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc1, // STORE_FAST 1
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x4c, // POP_JUMP_IF_TRUE 12
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x4a, // LOAD_METHOD 'sleep'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb4, // LOAD_FAST 4
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb7, // LOAD_FAST 7
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x42,0x6d, // JUMP 45
    0xb7, // LOAD_FAST 7
    0x12,0x7e, // LOAD_GLOBAL 'SOH'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb7, // LOAD_FAST 7
    0x63, // RETURN_VALUE
    0xb7, // LOAD_FAST 7
    0x12,0x7f, // LOAD_GLOBAL 'STX'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb7, // LOAD_FAST 7
    0x63, // RETURN_VALUE
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x00, // LOAD_GLOBAL 'EOT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0xb7, // LOAD_FAST 7
    0x63, // RETURN_VALUE
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x03, // LOAD_GLOBAL 'CAN'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb5, // LOAD_FAST 5
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc5, // STORE_FAST 5
    0x42,0x44, // JUMP 4
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x42,0xf3,0x7e, // JUMP -141
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__in_transfer_mode = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__in_transfer_mode,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 188,
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
        .n_pos_args = 7,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 67,
        .line_info = fun_data_ymodem_Modem__in_transfer_mode + 17,
        .line_info_top = fun_data_ymodem_Modem__in_transfer_mode + 45,
        .opcodes = fun_data_ymodem_Modem__in_transfer_mode + 45,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__in_transfer_mode fun_data_ymodem_Modem__in_transfer_mode[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__get_file_header
static const byte fun_data_ymodem_Modem__get_file_header[561] = {
    0x8e,0x95,0x01,0x96,0x02, // prelude
    0x44,0x81,0x1b,0x81,0x2d,0x81,0x27,0x60,0x61,0x81,0x2e, // names: _get_file_header, self, char, crc_mode, timeout, retry, packet_size
    0x90,0x3c,0x22,0x22,0x20,0x20,0x26,0x27,0x24,0x22,0x26,0x27,0x24,0x22,0x27,0x23,0x42,0x44,0x24,0x25,0x26,0x25,0x28,0x43,0x2b,0x33,0x2b,0x24,0x28,0x28,0x29,0x22,0x27,0x35,0x29,0x22,0x55,0x23,0x33,0x29,0x28,0x36,0x29,0x29,0x28,0x37,0x29,0x29,0x28,0x36,0x29,0x29,0x28,0x36,0x29,0x42,0x42,0x20,0x20,0x28,0x25,0x24,0x29,0x28, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc6, // STORE_FAST 6
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc7, // STORE_FAST 7
    0xb1, // LOAD_FAST 1
    0x12,0x7e, // LOAD_GLOBAL 'SOH'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb5, // LOAD_FAST 5
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xc5, // STORE_FAST 5
    0x42,0x77, // JUMP 55
    0xb1, // LOAD_FAST 1
    0x12,0x7f, // LOAD_GLOBAL 'STX'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4d, // POP_JUMP_IF_FALSE 13
    0xb5, // LOAD_FAST 5
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0xc5, // STORE_FAST 5
    0x42,0x64, // JUMP 36
    0xb1, // LOAD_FAST 1
    0x12,0x81,0x03, // LOAD_GLOBAL 'CAN'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0xb7, // LOAD_FAST 7
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc7, // STORE_FAST 7
    0x42,0x51, // JUMP 17
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0xb4, // LOAD_FAST 4
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x42,0xb6,0x7f, // JUMP -74
    0xb0, // LOAD_FAST 0
    0x14,0x45, // LOAD_METHOD '_verify_complement'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x42,0xdf,0x82, // JUMP 351
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0xb5, // LOAD_FAST 5
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x44,0xd0,0x82, // POP_JUMP_IF_FALSE 336
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb8, // LOAD_FAST 8
    0x34,0x01, // CALL_FUNCTION 1
    0xb5, // LOAD_FAST 5
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0xd9, // BINARY_OP 2 __eq__
    0x44,0xc1,0x82, // POP_JUMP_IF_FALSE 321
    0xb0, // LOAD_FAST 0
    0x14,0x46, // LOAD_METHOD '_verify_recv_checksum'
    0xb2, // LOAD_FAST 2
    0xb8, // LOAD_FAST 8
    0x36,0x02, // CALL_METHOD 2
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc9, // STORE_FAST 9
    0xc8, // STORE_FAST 8
    0xb9, // LOAD_FAST 9
    0x44,0xb0,0x82, // POP_JUMP_IF_FALSE 304
    0xb8, // LOAD_FAST 8
    0x14,0x4b, // LOAD_METHOD 'lstrip'
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x36,0x01, // CALL_METHOD 1
    0xc8, // STORE_FAST 8
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb8, // LOAD_FAST 8
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x4b, // POP_JUMP_IF_TRUE 11
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x12,0x02, // LOAD_GLOBAL 'gc'
    0x14,0x47, // LOAD_METHOD 'collect'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x12,0x81,0x11, // LOAD_GLOBAL 'bytes'
    0x14,0x4c, // LOAD_METHOD 'decode'
    0xb8, // LOAD_FAST 8
    0x14,0x4d, // LOAD_METHOD 'split'
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x02, // CALL_METHOD 2
    0xb0, // LOAD_FAST 0
    0x18,0x3b, // STORE_ATTR '_recv_file_name'
    0xb0, // LOAD_FAST 0
    0x14,0x4f, // LOAD_METHOD '_check_path'
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR '_recv_file_name'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x48,0x0d, // SETUP_EXCEPT 13
    0x12,0x81,0x2f, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x13,0x3b, // LOAD_ATTR '_recv_file_name'
    0x10,0x50, // LOAD_CONST_STRING 'wb+'
    0x34,0x02, // CALL_FUNCTION 2
    0xca, // STORE_FAST 10
    0x4a,0x0b, // POP_EXCEPT_JUMP 11
    0x57, // DUP_TOP
    0x12,0x81,0x30, // LOAD_GLOBAL 'IOError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x5d, // END_FINALLY
    0x12,0x81,0x11, // LOAD_GLOBAL 'bytes'
    0x14,0x4c, // LOAD_METHOD 'decode'
    0xb8, // LOAD_FAST 8
    0x14,0x4d, // LOAD_METHOD 'split'
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0x36,0x01, // CALL_METHOD 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x02, // CALL_METHOD 2
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x05, // LOAD_GLOBAL 'USE_LENGTH_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x67, // POP_JUMP_IF_FALSE 39
    0xb8, // LOAD_FAST 8
    0x14,0x51, // LOAD_METHOD 'find'
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x36,0x01, // CALL_METHOD 1
    0xcb, // STORE_FAST 11
    0x12,0x81,0x31, // LOAD_GLOBAL 'int'
    0xbb, // LOAD_FAST 11
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb8, // LOAD_FAST 8
    0x42,0x46, // JUMP 6
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0xbb, // LOAD_FAST 11
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x3c, // STORE_ATTR '_remaining_data_length'
    0xb8, // LOAD_FAST 8
    0xbb, // LOAD_FAST 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x06, // LOAD_GLOBAL 'USE_DATE_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x68, // POP_JUMP_IF_FALSE 40
    0xb8, // LOAD_FAST 8
    0x14,0x51, // LOAD_METHOD 'find'
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x36,0x01, // CALL_METHOD 1
    0xcb, // STORE_FAST 11
    0x12,0x81,0x31, // LOAD_GLOBAL 'int'
    0xbb, // LOAD_FAST 11
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb8, // LOAD_FAST 8
    0x42,0x46, // JUMP 6
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0xbb, // LOAD_FAST 11
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0x34,0x02, // CALL_FUNCTION 2
    0xb0, // LOAD_FAST 0
    0x18,0x3d, // STORE_ATTR '_recv_file_mtime'
    0xb8, // LOAD_FAST 8
    0xbb, // LOAD_FAST 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x07, // LOAD_GLOBAL 'USE_MODE_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x67, // POP_JUMP_IF_FALSE 39
    0xb8, // LOAD_FAST 8
    0x14,0x51, // LOAD_METHOD 'find'
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x36,0x01, // CALL_METHOD 1
    0xcb, // STORE_FAST 11
    0x12,0x81,0x31, // LOAD_GLOBAL 'int'
    0xbb, // LOAD_FAST 11
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb8, // LOAD_FAST 8
    0x42,0x46, // JUMP 6
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0xbb, // LOAD_FAST 11
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x3e, // STORE_ATTR '_recv_mode'
    0xb8, // LOAD_FAST 8
    0xbb, // LOAD_FAST 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x08, // LOAD_GLOBAL 'USE_SN_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x5e, // POP_JUMP_IF_FALSE 30
    0xb8, // LOAD_FAST 8
    0x14,0x51, // LOAD_METHOD 'find'
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x36,0x01, // CALL_METHOD 1
    0xcb, // STORE_FAST 11
    0x12,0x81,0x31, // LOAD_GLOBAL 'int'
    0xbb, // LOAD_FAST 11
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0xb8, // LOAD_FAST 8
    0x42,0x46, // JUMP 6
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0xbb, // LOAD_FAST 11
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x3f, // STORE_ATTR '_recv_sn'
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xba, // LOAD_FAST 10
    0x63, // RETURN_VALUE
    0x42,0x40, // JUMP 0
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc8, // STORE_FAST 8
    0xb8, // LOAD_FAST 8
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x42, // JUMP 2
    0x42,0x2f, // JUMP -17
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb3, // LOAD_FAST 3
    0x36,0x02, // CALL_METHOD 2
    0xc1, // STORE_FAST 1
    0x42,0x40, // JUMP 0
    0x42,0xa5,0x7c, // JUMP -475
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__get_file_header = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__get_file_header,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 561,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 18,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 68,
        .line_info = fun_data_ymodem_Modem__get_file_header + 16,
        .line_info_top = fun_data_ymodem_Modem__get_file_header + 80,
        .opcodes = fun_data_ymodem_Modem__get_file_header + 80,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__get_file_header fun_data_ymodem_Modem__get_file_header[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__check_path
static const byte fun_data_ymodem_Modem__check_path[39] = {
    0x29,0x0c, // prelude
    0x4f,0x81,0x32, // names: _check_path, path
    0x90,0x84,0x2f, // code info
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x53, // LOAD_METHOD 'path_exists'
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x54, // LOAD_METHOD 'path_dirname'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x36,0x01, // CALL_METHOD 1
    0x43,0x4e, // POP_JUMP_IF_TRUE 14
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x55, // LOAD_METHOD 'mkdirs'
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x54, // LOAD_METHOD 'path_dirname'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__check_path = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__check_path,
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
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 79,
        .line_info = fun_data_ymodem_Modem__check_path + 5,
        .line_info_top = fun_data_ymodem_Modem__check_path + 8,
        .opcodes = fun_data_ymodem_Modem__check_path + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__check_path fun_data_ymodem_Modem__check_path[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__delete_failed_file
static const byte fun_data_ymodem_Modem__delete_failed_file[31] = {
    0x99,0x01,0x0c, // prelude
    0x42,0x81,0x32, // names: _delete_failed_file, path
    0x90,0x89,0x2c, // code info
    0xb0, // LOAD_FAST 0
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x12,0x05, // LOAD_GLOBAL 'ql_fs'
    0x14,0x53, // LOAD_METHOD 'path_exists'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x03, // LOAD_GLOBAL 'uos'
    0x14,0x56, // LOAD_METHOD 'remove'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__delete_failed_file = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__delete_failed_file,
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
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 66,
        .line_info = fun_data_ymodem_Modem__delete_failed_file + 6,
        .line_info_top = fun_data_ymodem_Modem__delete_failed_file + 9,
        .opcodes = fun_data_ymodem_Modem__delete_failed_file + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__delete_failed_file fun_data_ymodem_Modem__delete_failed_file[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__verify_complement
static const byte fun_data_ymodem_Modem__verify_complement[82] = {
    0xc3,0x80,0x01,0x1e, // prelude
    0x45,0x81,0x1b,0x60,0x81,0x33, // names: _verify_complement, self, timeout, sequence
    0x90,0x8d,0x28,0x25,0x44,0x27,0x28,0x26,0x2b, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x42,0x60, // JUMP 32
    0x12,0x81,0x34, // LOAD_GLOBAL 'ord'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb1, // LOAD_FAST 1
    0x36,0x02, // CALL_METHOD 2
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x51, // LOAD_CONST_NONE
    0xde, // BINARY_OP 7 <is>
    0xd3, // UNARY_OP 3 <not>
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0x12,0x81,0x34, // LOAD_GLOBAL 'ord'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0xf3, // BINARY_OP 28 __sub__
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0x57, // DUP_TOP
    0x5b, // ROT_THREE
    0xd9, // BINARY_OP 2 __eq__
    0x46,0x04, // JUMP_IF_FALSE_OR_POP 4
    0xb2, // LOAD_FAST 2
    0xd9, // BINARY_OP 2 __eq__
    0x42,0x42, // JUMP 2
    0x5a, // ROT_TWO
    0x59, // POP_TOP
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__verify_complement = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__verify_complement,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 82,
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
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 69,
        .line_info = fun_data_ymodem_Modem__verify_complement + 10,
        .line_info_top = fun_data_ymodem_Modem__verify_complement + 19,
        .opcodes = fun_data_ymodem_Modem__verify_complement + 19,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__verify_complement fun_data_ymodem_Modem__verify_complement[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__verify_recv_checksum
static const byte fun_data_ymodem_Modem__verify_recv_checksum[104] = {
    0x5b,0x24, // prelude
    0x46,0x81,0x1b,0x81,0x27,0x81,0x0f, // names: _verify_recv_checksum, self, crc_mode, data
    0x90,0x98,0x23,0x2c,0x2a,0x2c,0x4b,0x2b,0x24,0x2c,0x24, // code info
    0xb1, // LOAD_FAST 1
    0x44,0x6d, // POP_JUMP_IF_FALSE 45
    0x12,0x81,0x35, // LOAD_GLOBAL 'bytearray'
    0xb2, // LOAD_FAST 2
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb3, // LOAD_FAST 3
    0x81, // LOAD_CONST_SMALL_INT 1
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x57, // LOAD_METHOD '_calc_crc'
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0x7e, // LOAD_CONST_SMALL_INT -2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0x12,0x81,0x36, // LOAD_GLOBAL 'bool'
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xd9, // BINARY_OP 2 __eq__
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0x42,0x5f, // JUMP 31
    0x12,0x81,0x35, // LOAD_GLOBAL 'bytearray'
    0xb2, // LOAD_FAST 2
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x55, // LOAD_SUBSCR
    0x2b,0x01, // BUILD_LIST 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x58, // LOAD_METHOD '_calc_checksum'
    0xb2, // LOAD_FAST 2
    0x51, // LOAD_CONST_NONE
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xd9, // BINARY_OP 2 __eq__
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0xb2, // LOAD_FAST 2
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__verify_recv_checksum = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__verify_recv_checksum,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 104,
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
        .qstr_block_name_idx = 70,
        .line_info = fun_data_ymodem_Modem__verify_recv_checksum + 9,
        .line_info_top = fun_data_ymodem_Modem__verify_recv_checksum + 20,
        .opcodes = fun_data_ymodem_Modem__verify_recv_checksum + 20,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__verify_recv_checksum fun_data_ymodem_Modem__verify_recv_checksum[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__calc_checksum
static const byte fun_data_ymodem_Modem__calc_checksum[23] = {
    0x9a,0x01,0x0e, // prelude
    0x58,0x81,0x0f,0x81,0x37, // names: _calc_checksum, data, checksum
    0x90,0xa6, // code info
    0x12,0x81,0x38, // LOAD_GLOBAL 'sum'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0xb1, // LOAD_FAST 1
    0xf2, // BINARY_OP 27 __add__
    0x22,0x82,0x00, // LOAD_CONST_SMALL_INT 256
    0xf8, // BINARY_OP 33 __mod__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__calc_checksum = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__calc_checksum,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 23,
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
        .qstr_block_name_idx = 88,
        .line_info = fun_data_ymodem_Modem__calc_checksum + 8,
        .line_info_top = fun_data_ymodem_Modem__calc_checksum + 10,
        .opcodes = fun_data_ymodem_Modem__calc_checksum + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__calc_checksum fun_data_ymodem_Modem__calc_checksum[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__calc_crc
static const byte fun_data_ymodem_Modem__calc_crc[59] = {
    0xdb,0x01,0x18, // prelude
    0x57,0x81,0x1b,0x81,0x0f,0x81,0x39, // names: _calc_crc, self, data, crc
    0x90,0xa9,0x2a,0x2a,0x31, // code info
    0x12,0x81,0x35, // LOAD_GLOBAL 'bytearray'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x5f, // GET_ITER_STACK
    0x4b,0x1c, // FOR_ITER 28
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb3, // LOAD_FAST 3
    0xee, // BINARY_OP 23 __xor__
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0xc4, // STORE_FAST 4
    0xb2, // LOAD_FAST 2
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf0, // BINARY_OP 25 __lshift__
    0xb0, // LOAD_FAST 0
    0x13,0x59, // LOAD_ATTR 'crc_table'
    0xb4, // LOAD_FAST 4
    0x55, // LOAD_SUBSCR
    0xee, // BINARY_OP 23 __xor__
    0x22,0x83,0xff,0x7f, // LOAD_CONST_SMALL_INT 65535
    0xef, // BINARY_OP 24 __and__
    0xc2, // STORE_FAST 2
    0x42,0x22, // JUMP -30
    0xb2, // LOAD_FAST 2
    0x22,0x83,0xff,0x7f, // LOAD_CONST_SMALL_INT 65535
    0xef, // BINARY_OP 24 __and__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__calc_crc = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__calc_crc,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 59,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 87,
        .line_info = fun_data_ymodem_Modem__calc_crc + 10,
        .line_info_top = fun_data_ymodem_Modem__calc_crc + 15,
        .opcodes = fun_data_ymodem_Modem__calc_crc + 15,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__calc_crc fun_data_ymodem_Modem__calc_crc[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem_send
static const byte fun_data_ymodem_Modem_send[415] = {
    0xb9,0x95,0x01,0x70, // prelude
    0x21,0x81,0x1b,0x81,0x18,0x61,0x60,0x1e, // names: send, self, trans_file, retry, timeout, callback
    0x90,0xb0,0x74,0x40,0x2f,0x25,0x2d,0x22,0x26,0x2e,0x27,0x4c,0x2d,0x23,0x42,0x27,0x33,0x42,0x47,0x2d,0x23,0x42,0x22,0x20,0x27,0x2d,0x27,0x23,0x2c,0x42,0x24,0x28,0x4e,0x22,0x4b,0x29,0x27,0x2a,0x42,0x29,0x27,0x2a,0x42,0x27,0x29,0x29,0x2e,0x28, // code info
    0x12,0x81,0x24, // LOAD_GLOBAL 'dict'
    0x10,0x5a, // LOAD_CONST_STRING 'xmodem'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x10,0x5b, // LOAD_CONST_STRING 'xmodem1k'
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0x10,0x5c, // LOAD_CONST_STRING 'ymodem'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x10,0x15, // LOAD_CONST_STRING 'ymodem1k'
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x09, // LOAD_GLOBAL 'ALLOW_1K_BLOCK'
    0xef, // BINARY_OP 24 __and__
    0x80, // LOAD_CONST_SMALL_INT 0
    0xdc, // BINARY_OP 5 __ne__
    0x55, // LOAD_SUBSCR
    0x34,0x88,0x00, // CALL_FUNCTION 1024
    0xb0, // LOAD_FAST 0
    0x13,0x35, // LOAD_ATTR 'mode'
    0x55, // LOAD_SUBSCR
    0xc5, // STORE_FAST 5
    0x12,0x81,0x38, // LOAD_GLOBAL 'sum'
    0x32,0x00, // MAKE_FUNCTION 0
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xb0, // LOAD_FAST 0
    0x18,0x40, // STORE_ATTR 'total_size'
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc6, // STORE_FAST 6
    0xb1, // LOAD_FAST 1
    0x5f, // GET_ITER_STACK
    0x4b,0x86,0x02, // FOR_ITER 262
    0xc7, // STORE_FAST 7
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x0f, // LOAD_CONST_OBJ 15
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb7, // LOAD_FAST 7
    0x34,0x01, // CALL_FUNCTION 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x10, // LOAD_CONST_OBJ 16
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x81,0x2f, // LOAD_GLOBAL 'open'
    0xb7, // LOAD_FAST 7
    0x10,0x5d, // LOAD_CONST_STRING 'filepath'
    0x55, // LOAD_SUBSCR
    0x10,0x5e, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0xc8, // STORE_FAST 8
    0xb0, // LOAD_FAST 0
    0x14,0x5f, // LOAD_METHOD '_wait_c'
    0x10,0x60, // LOAD_CONST_STRING 'timeout'
    0xb3, // LOAD_FAST 3
    0x10,0x61, // LOAD_CONST_STRING 'retry'
    0xb2, // LOAD_FAST 2
    0x36,0x84,0x00, // CALL_METHOD 512
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x11, // LOAD_CONST_OBJ 17
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x62, // LOAD_METHOD 'serial_trans'
    0xb0, // LOAD_FAST 0
    0x14,0x63, // LOAD_METHOD '_make_file_header_info'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xb9, // LOAD_FAST 9
    0xb7, // LOAD_FAST 7
    0x36,0x03, // CALL_METHOD 3
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0x36,0x03, // CALL_METHOD 3
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x12, // LOAD_CONST_OBJ 18
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x5f, // LOAD_METHOD '_wait_c'
    0x10,0x60, // LOAD_CONST_STRING 'timeout'
    0xb3, // LOAD_FAST 3
    0x10,0x61, // LOAD_CONST_STRING 'retry'
    0xb2, // LOAD_FAST 2
    0x36,0x84,0x00, // CALL_METHOD 512
    0xc9, // STORE_FAST 9
    0xb9, // LOAD_FAST 9
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xca, // STORE_FAST 10
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x13, // LOAD_CONST_OBJ 19
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x64, // LOAD_METHOD '_make_file_body_info'
    0xb8, // LOAD_FAST 8
    0xb5, // LOAD_FAST 5
    0xb9, // LOAD_FAST 9
    0xba, // LOAD_FAST 10
    0x36,0x04, // CALL_METHOD 4
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xcb, // STORE_FAST 11
    0xcc, // STORE_FAST 12
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x14, // LOAD_CONST_OBJ 20
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xbb, // LOAD_FAST 11
    0x44,0x68, // POP_JUMP_IF_FALSE 40
    0xb0, // LOAD_FAST 0
    0x14,0x62, // LOAD_METHOD 'serial_trans'
    0xbb, // LOAD_FAST 11
    0xb3, // LOAD_FAST 3
    0xb2, // LOAD_FAST 2
    0xb6, // LOAD_FAST 6
    0xba, // LOAD_FAST 10
    0x36,0x05, // CALL_METHOD 5
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0xb6, // LOAD_FAST 6
    0xbc, // LOAD_FAST 12
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x12,0x81,0x29, // LOAD_GLOBAL 'callable'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xb4, // LOAD_FAST 4
    0xb0, // LOAD_FAST 0
    0x13,0x40, // LOAD_ATTR 'total_size'
    0xb6, // LOAD_FAST 6
    0xb7, // LOAD_FAST 7
    0x10,0x65, // LOAD_CONST_STRING 'name'
    0x55, // LOAD_SUBSCR
    0x34,0x03, // CALL_FUNCTION 3
    0x59, // POP_TOP
    0x42,0x42, // JUMP 2
    0x42,0x4b, // JUMP 11
    0xba, // LOAD_FAST 10
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x22,0x82,0x00, // LOAD_CONST_SMALL_INT 256
    0xf8, // BINARY_OP 33 __mod__
    0xca, // STORE_FAST 10
    0x42,0xad,0x7f, // JUMP -83
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x00, // LOAD_GLOBAL 'EOT'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x15, // LOAD_CONST_OBJ 21
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x66, // LOAD_METHOD '_wait_nak_ack'
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0x12,0x81,0x00, // LOAD_GLOBAL 'EOT'
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x16, // LOAD_CONST_OBJ 22
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x66, // LOAD_METHOD '_wait_nak_ack'
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0x36,0x01, // CALL_METHOD 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x17, // LOAD_CONST_OBJ 23
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb8, // LOAD_FAST 8
    0x14,0x1f, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x42,0xf7,0x7d, // JUMP -265
    0xb0, // LOAD_FAST 0
    0x14,0x67, // LOAD_METHOD '_send_end_packet'
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x18, // LOAD_CONST_OBJ 24
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x4a, // LOAD_METHOD 'sleep'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
// child of ymodem_Modem_send
// frozen bytecode for file ymodem.py, scope ymodem_Modem_send__lt_listcomp_gt_
static const byte fun_data_ymodem_Modem_send__lt_listcomp_gt_[23] = {
    0x41,0x0a, // prelude
    0x7c,0x81,0x3f, // names: <listcomp>, *
    0x90,0xb7, // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x09, // FOR_ITER 9
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x10,0x6a, // LOAD_CONST_STRING 'length'
    0x55, // LOAD_SUBSCR
    0x2f,0x14, // STORE_COMP 20
    0x42,0x35, // JUMP -11
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_send__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_send__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 23,
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
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 124,
        .line_info = fun_data_ymodem_Modem_send__lt_listcomp_gt_ + 5,
        .line_info_top = fun_data_ymodem_Modem_send__lt_listcomp_gt_ + 7,
        .opcodes = fun_data_ymodem_Modem_send__lt_listcomp_gt_ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem_send__lt_listcomp_gt_ fun_data_ymodem_Modem_send__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children_ymodem_Modem_send[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_send__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_send = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_send,
    .children = (void *)&children_ymodem_Modem_send,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 415,
    .n_children = 1,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 24,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 5,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 33,
        .line_info = fun_data_ymodem_Modem_send + 12,
        .line_info_top = fun_data_ymodem_Modem_send + 60,
        .opcodes = fun_data_ymodem_Modem_send + 60,
    },
    #endif
    #endif
};

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__wait_c
static const byte fun_data_ymodem_Modem__wait_c[192] = {
    0xd0,0x85,0x01,0x48, // prelude
    0x5f,0x81,0x1b,0x81,0x2b,0x60,0x61, // names: _wait_c, self, cancel, timeout, retry
    0x90,0xee,0x26,0x40,0x28,0x24,0x27,0x22,0x27,0x22,0x27,0x22,0x27,0x22,0x27,0x23,0x27,0x42,0x22,0x29,0x27,0x27,0x42,0x4b,0x27,0x24,0x25,0x2c,0x26, // code info
    0x23,0x19, // LOAD_CONST_OBJ 25
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc4, // STORE_FAST 4
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x44,0xdd,0x80, // POP_JUMP_IF_FALSE 93
    0xb6, // LOAD_FAST 6
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc5, // STORE_FAST 5
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1a, // LOAD_CONST_OBJ 26
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x63, // RETURN_VALUE
    0xb6, // LOAD_FAST 6
    0x12,0x81,0x04, // LOAD_GLOBAL 'CRC'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc5, // STORE_FAST 5
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1b, // LOAD_CONST_OBJ 27
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x63, // RETURN_VALUE
    0xb6, // LOAD_FAST 6
    0x12,0x81,0x03, // LOAD_GLOBAL 'CAN'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb1, // LOAD_FAST 1
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1c, // LOAD_CONST_OBJ 28
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x81, // LOAD_CONST_SMALL_INT 1
    0xc1, // STORE_FAST 1
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1d, // LOAD_CONST_OBJ 29
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x59, // JUMP 25
    0xb6, // LOAD_FAST 6
    0x12,0x81,0x00, // LOAD_GLOBAL 'EOT'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x49, // POP_JUMP_IF_FALSE 9
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1e, // LOAD_CONST_OBJ 30
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x1f, // LOAD_CONST_OBJ 31
    0xb6, // LOAD_FAST 6
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x47, // JUMP 7
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x20, // LOAD_CONST_OBJ 32
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0xb3, // LOAD_FAST 3
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x21, // LOAD_CONST_OBJ 33
    0x14,0x68, // LOAD_METHOD 'format'
    0xb3, // LOAD_FAST 3
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0xf0,0x7e, // JUMP -144
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__wait_c = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__wait_c,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 192,
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
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 3,
        .qstr_block_name_idx = 95,
        .line_info = fun_data_ymodem_Modem__wait_c + 11,
        .line_info_top = fun_data_ymodem_Modem__wait_c + 40,
        .opcodes = fun_data_ymodem_Modem__wait_c + 40,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__wait_c fun_data_ymodem_Modem__wait_c[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__make_file_header_info
static const byte fun_data_ymodem_Modem__make_file_header_info[302] = {
    0xe0,0x05,0x40, // prelude
    0x63,0x81,0x1b,0x81,0x2e,0x81,0x27,0x81,0x3a, // names: _make_file_header_info, self, packet_size, crc_mode, info
    0xa0,0x10,0x47,0x28,0x2c,0x2b,0x49,0x29,0x29,0x32,0x29,0x2f,0x29,0x54,0x52,0x29,0x29,0x57,0x4b,0x29,0x2b,0x3b,0x28, // code info
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x10,0x63, // LOAD_CONST_STRING '_make_file_header_info'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x69, // LOAD_METHOD '_make_send_header'
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x02, // CALL_METHOD 2
    0xc4, // STORE_FAST 4
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x22, // LOAD_CONST_OBJ 34
    0xb3, // LOAD_FAST 3
    0x10,0x65, // LOAD_CONST_STRING 'name'
    0x55, // LOAD_SUBSCR
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x10,0x65, // LOAD_CONST_STRING 'name'
    0x55, // LOAD_SUBSCR
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x23, // LOAD_CONST_OBJ 35
    0xb5, // LOAD_FAST 5
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x05, // LOAD_GLOBAL 'USE_LENGTH_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x5b, // POP_JUMP_IF_FALSE 27
    0xb5, // LOAD_FAST 5
    0x12,0x81,0x11, // LOAD_GLOBAL 'bytes'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x34,0x01, // CALL_FUNCTION 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb3, // LOAD_FAST 3
    0x10,0x6a, // LOAD_CONST_STRING 'length'
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x06, // LOAD_GLOBAL 'USE_DATE_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x7e, // POP_JUMP_IF_FALSE 62
    0x12,0x81,0x3b, // LOAD_GLOBAL 'oct'
    0x12,0x81,0x31, // LOAD_GLOBAL 'int'
    0xb3, // LOAD_FAST 3
    0x10,0x6b, // LOAD_CONST_STRING 'mtime'
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0xb6, // LOAD_FAST 6
    0x14,0x6c, // LOAD_METHOD 'startswith'
    0x10,0x6d, // LOAD_CONST_STRING '0o'
    0x36,0x01, // CALL_METHOD 1
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0xb5, // LOAD_FAST 5
    0x10,0x52, // LOAD_CONST_STRING ' '
    0xb6, // LOAD_FAST 6
    0x82, // LOAD_CONST_SMALL_INT 2
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0x42,0x52, // JUMP 18
    0xb5, // LOAD_FAST 5
    0x10,0x52, // LOAD_CONST_STRING ' '
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0x51, // LOAD_CONST_NONE
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x07, // LOAD_GLOBAL 'USE_MODE_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x6b, // POP_JUMP_IF_FALSE 43
    0xb3, // LOAD_FAST 3
    0x10,0x6e, // LOAD_CONST_STRING 'source'
    0x55, // LOAD_SUBSCR
    0x10,0x6f, // LOAD_CONST_STRING 'Unix'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x57, // POP_JUMP_IF_FALSE 23
    0xb5, // LOAD_FAST 5
    0x10,0x52, // LOAD_CONST_STRING ' '
    0x12,0x81,0x3b, // LOAD_GLOBAL 'oct'
    0x22,0x82,0x80,0x00, // LOAD_CONST_SMALL_INT 32768
    0x34,0x01, // CALL_FUNCTION 1
    0xf2, // BINARY_OP 27 __add__
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0x42,0x4b, // JUMP 11
    0xb5, // LOAD_FAST 5
    0x10,0x70, // LOAD_CONST_STRING ' 0'
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x13,0x3a, // LOAD_ATTR 'program_features'
    0x12,0x81,0x07, // LOAD_GLOBAL 'USE_MODE_FIELD'
    0xef, // BINARY_OP 24 __and__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0xb5, // LOAD_FAST 5
    0x10,0x70, // LOAD_CONST_STRING ' 0'
    0x14,0x11, // LOAD_METHOD 'encode'
    0x10,0x4e, // LOAD_CONST_STRING 'utf-8'
    0x36,0x01, // CALL_METHOD 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0xb1, // LOAD_FAST 1
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0xb1, // LOAD_FAST 1
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0xf3, // BINARY_OP 28 __sub__
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xf4, // BINARY_OP 29 __mul__
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x14,0x71, // LOAD_METHOD '_make_send_checksum'
    0xb2, // LOAD_FAST 2
    0xb5, // LOAD_FAST 5
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0xb4, // LOAD_FAST 4
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0xb7, // LOAD_FAST 7
    0xf2, // BINARY_OP 27 __add__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__make_file_header_info = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__make_file_header_info,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 302,
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
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 99,
        .line_info = fun_data_ymodem_Modem__make_file_header_info + 12,
        .line_info_top = fun_data_ymodem_Modem__make_file_header_info + 35,
        .opcodes = fun_data_ymodem_Modem__make_file_header_info + 35,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__make_file_header_info fun_data_ymodem_Modem__make_file_header_info[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__make_send_header
static const byte fun_data_ymodem_Modem__make_send_header[104] = {
    0x3a,0x1e, // prelude
    0x69,0x81,0x2e,0x81,0x33, // names: _make_send_header, packet_size, sequence
    0xa0,0x2f,0x27,0x2c,0x23,0x27,0x2f,0x27,0x2f,0x2e, // code info
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x10,0x69, // LOAD_CONST_STRING '_make_send_header'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x23,0x0e, // LOAD_CONST_OBJ 14
    0xdd, // BINARY_OP 6 <in>
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0x12,0x32, // LOAD_GLOBAL 'AssertionError'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x2b,0x00, // BUILD_LIST 0
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x22,0x81,0x00, // LOAD_CONST_SMALL_INT 128
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb2, // LOAD_FAST 2
    0x14,0x72, // LOAD_METHOD 'append'
    0x12,0x81,0x34, // LOAD_GLOBAL 'ord'
    0x12,0x7e, // LOAD_GLOBAL 'SOH'
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x56, // JUMP 22
    0xb0, // LOAD_FAST 0
    0x22,0x88,0x00, // LOAD_CONST_SMALL_INT 1024
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb2, // LOAD_FAST 2
    0x14,0x72, // LOAD_METHOD 'append'
    0x12,0x81,0x34, // LOAD_GLOBAL 'ord'
    0x12,0x7f, // LOAD_GLOBAL 'STX'
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x40, // JUMP 0
    0xb2, // LOAD_FAST 2
    0x14,0x73, // LOAD_METHOD 'extend'
    0xb1, // LOAD_FAST 1
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xb1, // LOAD_FAST 1
    0xf3, // BINARY_OP 28 __sub__
    0x2b,0x02, // BUILD_LIST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x81,0x35, // LOAD_GLOBAL 'bytearray'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__make_send_header = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__make_send_header,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 104,
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
        .qstr_block_name_idx = 105,
        .line_info = fun_data_ymodem_Modem__make_send_header + 7,
        .line_info_top = fun_data_ymodem_Modem__make_send_header + 17,
        .opcodes = fun_data_ymodem_Modem__make_send_header + 17,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__make_send_header fun_data_ymodem_Modem__make_send_header[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__make_send_checksum
static const byte fun_data_ymodem_Modem__make_send_checksum[77] = {
    0x4b,0x20, // prelude
    0x71,0x81,0x1b,0x81,0x27,0x81,0x0f, // names: _make_send_checksum, self, crc_mode, data
    0xa0,0x3a,0x27,0x23,0x23,0x27,0x52,0x27,0x27, // code info
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x10,0x71, // LOAD_CONST_STRING '_make_send_checksum'
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x2b,0x00, // BUILD_LIST 0
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0x44,0x59, // POP_JUMP_IF_FALSE 25
    0xb0, // LOAD_FAST 0
    0x14,0x57, // LOAD_METHOD '_calc_crc'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x14,0x73, // LOAD_METHOD 'extend'
    0xb4, // LOAD_FAST 4
    0x88, // LOAD_CONST_SMALL_INT 8
    0xf1, // BINARY_OP 26 __rshift__
    0xb4, // LOAD_FAST 4
    0x22,0x81,0x7f, // LOAD_CONST_SMALL_INT 255
    0xef, // BINARY_OP 24 __and__
    0x2b,0x02, // BUILD_LIST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x4e, // JUMP 14
    0xb0, // LOAD_FAST 0
    0x14,0x58, // LOAD_METHOD '_calc_checksum'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x14,0x72, // LOAD_METHOD 'append'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x81,0x35, // LOAD_GLOBAL 'bytearray'
    0xb3, // LOAD_FAST 3
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__make_send_checksum = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__make_send_checksum,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 77,
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
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 113,
        .line_info = fun_data_ymodem_Modem__make_send_checksum + 9,
        .line_info_top = fun_data_ymodem_Modem__make_send_checksum + 18,
        .opcodes = fun_data_ymodem_Modem__make_send_checksum + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__make_send_checksum fun_data_ymodem_Modem__make_send_checksum[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem_serial_trans
static const byte fun_data_ymodem_Modem_serial_trans[172] = {
    0xea,0x84,0x80,0x01,0x3c, // prelude
    0x62,0x81,0x1b,0x81,0x3a,0x60,0x61,0x81,0x3c,0x81,0x33, // names: serial_trans, self, info, timeout, retry, success_count, sequence
    0xa0,0x45,0x42,0x2c,0x27,0x32,0x20,0x28,0x2c,0x27,0x22,0x27,0x42,0x32,0x24,0x28,0x25,0x2c,0x26, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc6, // STORE_FAST 6
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x24, // LOAD_CONST_OBJ 36
    0x14,0x68, // LOAD_METHOD 'format'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x25, // LOAD_CONST_OBJ 37
    0x14,0x68, // LOAD_METHOD 'format'
    0xb4, // LOAD_FAST 4
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x26, // LOAD_CONST_OBJ 38
    0x14,0x68, // LOAD_METHOD 'format'
    0xb7, // LOAD_FAST 7
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x01, // LOAD_GLOBAL 'ACK'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x02, // LOAD_GLOBAL 'NAK'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x27, // LOAD_CONST_OBJ 39
    0x14,0x68, // LOAD_METHOD 'format'
    0xb7, // LOAD_FAST 7
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x02, // CALL_METHOD 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc6, // STORE_FAST 6
    0x12,0x7d, // LOAD_GLOBAL 'time'
    0x14,0x48, // LOAD_METHOD 'sleep_ms'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb6, // LOAD_FAST 6
    0xb3, // LOAD_FAST 3
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x54, // POP_JUMP_IF_FALSE 20
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x28, // LOAD_CONST_OBJ 40
    0x14,0x68, // LOAD_METHOD 'format'
    0xb6, // LOAD_FAST 6
    0x36,0x01, // CALL_METHOD 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0xa0,0x7f, // JUMP -96
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem_serial_trans = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem_serial_trans,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 172,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 14,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 6,
        .n_kwonly_args = 0,
        .n_def_pos_args = 4,
        .qstr_block_name_idx = 98,
        .line_info = fun_data_ymodem_Modem_serial_trans + 16,
        .line_info_top = fun_data_ymodem_Modem_serial_trans + 35,
        .opcodes = fun_data_ymodem_Modem_serial_trans + 35,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem_serial_trans fun_data_ymodem_Modem_serial_trans[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__make_file_body_info
static const byte fun_data_ymodem_Modem__make_file_body_info[93] = {
    0xe1,0x04,0x2a, // prelude
    0x64,0x81,0x1b,0x81,0x3d,0x81,0x2e,0x81,0x27,0x81,0x33, // names: _make_file_body_info, self, stream, packet_size, crc_mode, sequence
    0xa0,0x5b,0x27,0x23,0x27,0x23,0x27,0x28,0x31,0x28, // code info
    0xb1, // LOAD_FAST 1
    0x14,0x1c, // LOAD_METHOD 'read'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0x43,0x4a, // POP_JUMP_IF_TRUE 10
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x29, // LOAD_CONST_OBJ 41
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x23,0x2a, // LOAD_CONST_OBJ 42
    0x63, // RETURN_VALUE
    0x12,0x81,0x2a, // LOAD_GLOBAL 'len'
    0xb5, // LOAD_FAST 5
    0x34,0x01, // CALL_FUNCTION 1
    0xc6, // STORE_FAST 6
    0xb0, // LOAD_FAST 0
    0x14,0x69, // LOAD_METHOD '_make_send_header'
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x36,0x02, // CALL_METHOD 2
    0xc7, // STORE_FAST 7
    0xb5, // LOAD_FAST 5
    0x23,0x2b, // LOAD_CONST_OBJ 43
    0xb2, // LOAD_FAST 2
    0xb6, // LOAD_FAST 6
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x45, // POP_JUMP_IF_FALSE 5
    0xb2, // LOAD_FAST 2
    0xb6, // LOAD_FAST 6
    0xf3, // BINARY_OP 28 __sub__
    0x42,0x41, // JUMP 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xf4, // BINARY_OP 29 __mul__
    0xe5, // BINARY_OP 14 __iadd__
    0xc5, // STORE_FAST 5
    0xb0, // LOAD_FAST 0
    0x14,0x71, // LOAD_METHOD '_make_send_checksum'
    0xb3, // LOAD_FAST 3
    0xb5, // LOAD_FAST 5
    0x36,0x02, // CALL_METHOD 2
    0xc8, // STORE_FAST 8
    0xb7, // LOAD_FAST 7
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0xb8, // LOAD_FAST 8
    0xf2, // BINARY_OP 27 __add__
    0xb6, // LOAD_FAST 6
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__make_file_body_info = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__make_file_body_info,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 93,
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
        .qstr_block_name_idx = 100,
        .line_info = fun_data_ymodem_Modem__make_file_body_info + 14,
        .line_info_top = fun_data_ymodem_Modem__make_file_body_info + 24,
        .opcodes = fun_data_ymodem_Modem__make_file_body_info + 24,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__make_file_body_info fun_data_ymodem_Modem__make_file_body_info[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__wait_nak_ack
static const byte fun_data_ymodem_Modem__wait_nak_ack[92] = {
    0xc8,0x84,0x01,0x28, // prelude
    0x66,0x81,0x1b,0x81,0x3e,0x60,0x61, // names: _wait_nak_ack, self, flags, timeout, retry
    0xa0,0x66,0x22,0x20,0x28,0x25,0x29,0x42,0x2c,0x24,0x25,0x29,0x26, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x33, // LOAD_METHOD 'reader'
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0xc5, // STORE_FAST 5
    0xb5, // LOAD_FAST 5
    0xb1, // LOAD_FAST 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4b, // POP_JUMP_IF_FALSE 11
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x18, // LOAD_CONST_OBJ 24
    0xb1, // LOAD_FAST 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x2c, // LOAD_CONST_OBJ 44
    0xb1, // LOAD_FAST 1
    0xb5, // LOAD_FAST 5
    0x2a,0x02, // BUILD_TUPLE 2
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0xb3, // LOAD_FAST 3
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x51, // POP_JUMP_IF_FALSE 17
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x23,0x2d, // LOAD_CONST_OBJ 45
    0xb1, // LOAD_FAST 1
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x41, // LOAD_METHOD 'abort'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x42,0x00, // JUMP -64
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__wait_nak_ack = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__wait_nak_ack,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 92,
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
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 102,
        .line_info = fun_data_ymodem_Modem__wait_nak_ack + 11,
        .line_info_top = fun_data_ymodem_Modem__wait_nak_ack + 24,
        .opcodes = fun_data_ymodem_Modem__wait_nak_ack + 24,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__wait_nak_ack fun_data_ymodem_Modem__wait_nak_ack[0]
#endif

// child of ymodem_Modem
// frozen bytecode for file ymodem.py, scope ymodem_Modem__send_end_packet
static const byte fun_data_ymodem_Modem__send_end_packet[60] = {
    0xcb,0x01,0x1a, // prelude
    0x67,0x81,0x1b,0x81,0x2e,0x81,0x27, // names: _send_end_packet, self, packet_size, crc_mode
    0xa0,0x75,0x28,0x25,0x28,0x2a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x69, // LOAD_METHOD '_make_send_header'
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x02, // CALL_METHOD 2
    0xc3, // STORE_FAST 3
    0xb1, // LOAD_FAST 1
    0x23,0x0d, // LOAD_CONST_OBJ 13
    0xf4, // BINARY_OP 29 __mul__
    0xc4, // STORE_FAST 4
    0xb0, // LOAD_FAST 0
    0x14,0x71, // LOAD_METHOD '_make_send_checksum'
    0xb2, // LOAD_FAST 2
    0xb4, // LOAD_FAST 4
    0x36,0x02, // CALL_METHOD 2
    0xc5, // STORE_FAST 5
    0x12,0x10, // LOAD_GLOBAL '_print'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xf2, // BINARY_OP 27 __add__
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x34, // LOAD_METHOD 'writer'
    0xb3, // LOAD_FAST 3
    0xb4, // LOAD_FAST 4
    0xf2, // BINARY_OP 27 __add__
    0xb5, // LOAD_FAST 5
    0xf2, // BINARY_OP 27 __add__
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_Modem__send_end_packet = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem__send_end_packet,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 60,
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
        .n_pos_args = 3,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 103,
        .line_info = fun_data_ymodem_Modem__send_end_packet + 10,
        .line_info_top = fun_data_ymodem_Modem__send_end_packet + 16,
        .opcodes = fun_data_ymodem_Modem__send_end_packet + 16,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_Modem__send_end_packet fun_data_ymodem_Modem__send_end_packet[0]
#endif

static const mp_raw_code_t *const children_ymodem_Modem[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem___init__,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_abort,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_recv,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__in_transfer_mode,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__get_file_header,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__check_path,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__delete_failed_file,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__verify_complement,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__verify_recv_checksum,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__calc_checksum,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__calc_crc,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_send,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__wait_c,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__make_file_header_info,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__make_send_header,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__make_send_checksum,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem_serial_trans,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__make_file_body_info,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__wait_nak_ack,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem__send_end_packet,
};

static const mp_raw_code_truncated_t proto_fun_ymodem_Modem = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_Modem,
    .children = (void *)&children_ymodem_Modem,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 1296,
    .n_children = 20,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 256,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_ymodem_Modem + 6,
        .line_info_top = fun_data_ymodem_Modem + 81,
        .opcodes = fun_data_ymodem_Modem + 81,
    },
    #endif
    #endif
};

// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem_enter_ymodem
static const byte fun_data_ymodem_enter_ymodem[71] = {
    0xba,0x80,0x01,0x10, // prelude
    0x18,0x1e,0x1b, // names: enter_ymodem, callback, buadrate
    0xa0,0x7d,0x3e,0x2b,0x2a, // code info
    0x12,0x0d, // LOAD_GLOBAL 'Serial'
    0x12,0x81,0x17, // LOAD_GLOBAL 'hasattr'
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x10,0x19, // LOAD_CONST_STRING 'REPL_UART'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x13,0x19, // LOAD_ATTR 'REPL_UART'
    0x42,0x44, // JUMP 4
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x13,0x1a, // LOAD_ATTR 'UART3'
    0x10,0x1b, // LOAD_CONST_STRING 'buadrate'
    0xb1, // LOAD_FAST 1
    0x34,0x82,0x01, // CALL_FUNCTION 257
    0xc2, // STORE_FAST 2
    0x12,0x0e, // LOAD_GLOBAL 'Modem'
    0xb2, // LOAD_FAST 2
    0x13,0x1c, // LOAD_ATTR 'read'
    0xb2, // LOAD_FAST 2
    0x13,0x13, // LOAD_ATTR 'write'
    0x34,0x02, // CALL_FUNCTION 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x1d, // LOAD_METHOD 'recv'
    0x10,0x1e, // LOAD_CONST_STRING 'callback'
    0xb0, // LOAD_FAST 0
    0x36,0x82,0x00, // CALL_METHOD 256
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x14,0x1f, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_enter_ymodem = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_enter_ymodem,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 71,
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
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 24,
        .line_info = fun_data_ymodem_enter_ymodem + 7,
        .line_info_top = fun_data_ymodem_enter_ymodem + 12,
        .opcodes = fun_data_ymodem_enter_ymodem + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_enter_ymodem fun_data_ymodem_enter_ymodem[0]
#endif

// child of ymodem__lt_module_gt_
// frozen bytecode for file ymodem.py, scope ymodem_send_file
static const byte fun_data_ymodem_send_file[104] = {
    0xd2,0x03,0x16, // prelude
    0x20,0x81,0x18,0x1b, // names: send_file, trans_file, buadrate
    0xa0,0x84,0x3e,0x2b,0x22,0x53,0x34, // code info
    0x12,0x0d, // LOAD_GLOBAL 'Serial'
    0x12,0x81,0x17, // LOAD_GLOBAL 'hasattr'
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x10,0x19, // LOAD_CONST_STRING 'REPL_UART'
    0x34,0x02, // CALL_FUNCTION 2
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x13,0x19, // LOAD_ATTR 'REPL_UART'
    0x42,0x44, // JUMP 4
    0x12,0x0a, // LOAD_GLOBAL 'UART'
    0x13,0x1a, // LOAD_ATTR 'UART3'
    0x10,0x1b, // LOAD_CONST_STRING 'buadrate'
    0xb1, // LOAD_FAST 1
    0x34,0x82,0x01, // CALL_FUNCTION 257
    0xc2, // STORE_FAST 2
    0x12,0x0e, // LOAD_GLOBAL 'Modem'
    0xb2, // LOAD_FAST 2
    0x13,0x1c, // LOAD_ATTR 'read'
    0xb2, // LOAD_FAST 2
    0x13,0x13, // LOAD_ATTR 'write'
    0x34,0x02, // CALL_FUNCTION 2
    0xc3, // STORE_FAST 3
    0x48,0x09, // SETUP_EXCEPT 9
    0xb3, // LOAD_FAST 3
    0x14,0x21, // LOAD_METHOD 'send'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x4a,0x1e, // POP_EXCEPT_JUMP 30
    0x57, // DUP_TOP
    0x12,0x81,0x19, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0xc4, // STORE_FAST 4
    0x49,0x0c, // SETUP_FINALLY 12
    0x12,0x10, // LOAD_GLOBAL '_print'
    0x12,0x81,0x12, // LOAD_GLOBAL 'str'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x51, // LOAD_CONST_NONE
    0xc4, // STORE_FAST 4
    0x28,0x04, // DELETE_FAST 4
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0xb2, // LOAD_FAST 2
    0x14,0x1f, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ymodem_send_file = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem_send_file,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 104,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 11,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 32,
        .line_info = fun_data_ymodem_send_file + 7,
        .line_info_top = fun_data_ymodem_send_file + 14,
        .opcodes = fun_data_ymodem_send_file + 14,
    },
    #endif
    #endif
};
#else
#define proto_fun_ymodem_send_file fun_data_ymodem_send_file[0]
#endif

static const mp_raw_code_t *const children_ymodem__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_ymodem__print,
    (const mp_raw_code_t *)&proto_fun_ymodem_check_file,
    (const mp_raw_code_t *)&proto_fun_ymodem_Serial,
    (const mp_raw_code_t *)&proto_fun_ymodem_Modem,
    (const mp_raw_code_t *)&proto_fun_ymodem_enter_ymodem,
    (const mp_raw_code_t *)&proto_fun_ymodem_send_file,
};

static const mp_raw_code_truncated_t proto_fun_ymodem__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ymodem__lt_module_gt_,
    .children = (void *)&children_ymodem__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 259,
    .n_children = 6,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data_ymodem__lt_module_gt_ + 3,
        .line_info_top = fun_data_ymodem__lt_module_gt_ + 41,
        .opcodes = fun_data_ymodem__lt_module_gt_ + 41,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_ymodem[194] = {
    MP_QSTR_ymodem_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_gc,
    MP_QSTR_uos,
    MP_QSTR_sys,
    MP_QSTR_ql_fs,
    MP_QSTR_osTimer,
    MP_QSTR_utime,
    MP_QSTR_Queue,
    MP_QSTR_queue,
    MP_QSTR_UART,
    MP_QSTR_machine,
    MP_QSTR_UART2,
    MP_QSTR_Serial,
    MP_QSTR_Modem,
    MP_QSTR___main__,
    MP_QSTR__print,
    MP_QSTR_encode,
    MP_QSTR_endswith,
    MP_QSTR_write,
    MP_QSTR_check_file,
    MP_QSTR_ymodem1k,
    MP_QSTR_rzsz,
    MP_QSTR_,
    MP_QSTR_enter_ymodem,
    MP_QSTR_REPL_UART,
    MP_QSTR_UART3,
    MP_QSTR_buadrate,
    MP_QSTR_read,
    MP_QSTR_recv,
    MP_QSTR_callback,
    MP_QSTR_close,
    MP_QSTR_send_file,
    MP_QSTR_send,
    MP_QSTR_wrapper,
    MP_QSTR___init__,
    MP_QSTR_flow,
    MP_QSTR__uart,
    MP_QSTR_set_callback,
    MP_QSTR__uart_cb,
    MP_QSTR_maxsize,
    MP_QSTR__queue,
    MP_QSTR__timer,
    MP_QSTR_size,
    MP_QSTR_put,
    MP_QSTR__timer_cb,
    MP_QSTR_any,
    MP_QSTR_start,
    MP_QSTR_get,
    MP_QSTR_stop,
    MP_QSTR_AssertionError,
    MP_QSTR_reader,
    MP_QSTR_writer,
    MP_QSTR_mode,
    MP_QSTR_rbsb,
    MP_QSTR_pyam,
    MP_QSTR_cyam,
    MP_QSTR_kimp,
    MP_QSTR_program_features,
    MP_QSTR__recv_file_name,
    MP_QSTR__remaining_data_length,
    MP_QSTR__recv_file_mtime,
    MP_QSTR__recv_mode,
    MP_QSTR__recv_sn,
    MP_QSTR_total_size,
    MP_QSTR_abort,
    MP_QSTR__delete_failed_file,
    MP_QSTR__in_transfer_mode,
    MP_QSTR__get_file_header,
    MP_QSTR__verify_complement,
    MP_QSTR__verify_recv_checksum,
    MP_QSTR_collect,
    MP_QSTR_sleep_ms,
    MP_QSTR_print_exception,
    MP_QSTR_sleep,
    MP_QSTR_lstrip,
    MP_QSTR_decode,
    MP_QSTR_split,
    MP_QSTR_utf_hyphen_8,
    MP_QSTR__check_path,
    MP_QSTR_wb_plus_,
    MP_QSTR_find,
    MP_QSTR__space_,
    MP_QSTR_path_exists,
    MP_QSTR_path_dirname,
    MP_QSTR_mkdirs,
    MP_QSTR_remove,
    MP_QSTR__calc_crc,
    MP_QSTR__calc_checksum,
    MP_QSTR_crc_table,
    MP_QSTR_xmodem,
    MP_QSTR_xmodem1k,
    MP_QSTR_ymodem,
    MP_QSTR_filepath,
    MP_QSTR_rb,
    MP_QSTR__wait_c,
    MP_QSTR_timeout,
    MP_QSTR_retry,
    MP_QSTR_serial_trans,
    MP_QSTR__make_file_header_info,
    MP_QSTR__make_file_body_info,
    MP_QSTR_name,
    MP_QSTR__wait_nak_ack,
    MP_QSTR__send_end_packet,
    MP_QSTR_format,
    MP_QSTR__make_send_header,
    MP_QSTR_length,
    MP_QSTR_mtime,
    MP_QSTR_startswith,
    MP_QSTR_0o,
    MP_QSTR_source,
    MP_QSTR_Unix,
    MP_QSTR__space_0,
    MP_QSTR__make_send_checksum,
    MP_QSTR_append,
    MP_QSTR_extend,
    MP_QSTR__wrapper,
    MP_QSTR_strip,
    MP_QSTR__bracket_open__bracket_close_,
    MP_QSTR__comma_,
    MP_QSTR_path_getsize,
    MP_QSTR_mktime,
    MP_QSTR_localtime,
    MP_QSTR_rtos,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR_time,
    MP_QSTR_SOH,
    MP_QSTR_STX,
    MP_QSTR_EOT,
    MP_QSTR_ACK,
    MP_QSTR_NAK,
    MP_QSTR_CAN,
    MP_QSTR_CRC,
    MP_QSTR_USE_LENGTH_FIELD,
    MP_QSTR_USE_DATE_FIELD,
    MP_QSTR_USE_MODE_FIELD,
    MP_QSTR_USE_SN_FIELD,
    MP_QSTR_ALLOW_1K_BLOCK,
    MP_QSTR_ALLOW_YMODEM_G,
    MP_QSTR_DEBUG,
    MP_QSTR__MAIN_UART_,
    MP_QSTR_object,
    MP_QSTR___name__,
    MP_QSTR_data,
    MP_QSTR_isinstance,
    MP_QSTR_bytes,
    MP_QSTR_str,
    MP_QSTR_print,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_staticmethod,
    MP_QSTR_hasattr,
    MP_QSTR_trans_file,
    MP_QSTR_Exception,
    MP_QSTR_func,
    MP_QSTR_self,
    MP_QSTR_uart,
    MP_QSTR_databits,
    MP_QSTR_parity,
    MP_QSTR_stopbits,
    MP_QSTR_flowctl,
    MP_QSTR_nbytes,
    MP_QSTR_min,
    MP_QSTR_program,
    MP_QSTR_dict,
    MP_QSTR_count,
    MP_QSTR_range,
    MP_QSTR_crc_mode,
    MP_QSTR_delay,
    MP_QSTR_callable,
    MP_QSTR_len,
    MP_QSTR_cancel,
    MP_QSTR_error_count,
    MP_QSTR_char,
    MP_QSTR_packet_size,
    MP_QSTR_open,
    MP_QSTR_IOError,
    MP_QSTR_int,
    MP_QSTR_path,
    MP_QSTR_sequence,
    MP_QSTR_ord,
    MP_QSTR_bytearray,
    MP_QSTR_bool,
    MP_QSTR_checksum,
    MP_QSTR_sum,
    MP_QSTR_crc,
    MP_QSTR_info,
    MP_QSTR_oct,
    MP_QSTR_success_count,
    MP_QSTR_stream,
    MP_QSTR_flags,
    MP_QSTR__star_,
    MP_QSTR_list,
    MP_QSTR_tuple,
};

// constants
static const mp_obj_str_t const_obj_ymodem_0 = {{&mp_type_bytes}, 46500, 1, (const byte*)"\x01"};
static const mp_obj_str_t const_obj_ymodem_1 = {{&mp_type_bytes}, 46503, 1, (const byte*)"\x02"};
static const mp_obj_str_t const_obj_ymodem_2 = {{&mp_type_bytes}, 46497, 1, (const byte*)"\x04"};
static const mp_obj_str_t const_obj_ymodem_3 = {{&mp_type_bytes}, 46499, 1, (const byte*)"\x06"};
static const mp_obj_str_t const_obj_ymodem_4 = {{&mp_type_bytes}, 46512, 1, (const byte*)"\x15"};
static const mp_obj_str_t const_obj_ymodem_5 = {{&mp_type_bytes}, 46525, 1, (const byte*)"\x18"};
static const mp_obj_str_t const_obj_ymodem_6 = {{&mp_type_bytes}, 46566, 1, (const byte*)"\x43"};
static const mp_obj_str_t const_obj_ymodem_7 = {{&mp_type_bytes}, 27298, 2, (const byte*)"\x0d\x0a"};
static const mp_obj_str_t const_obj_ymodem_9 = {{&mp_type_str}, 54105, 26, (const byte*)"\x49\x6e\x76\x61\x6c\x69\x64\x20\x6d\x6f\x64\x65\x20\x73\x70\x65\x63\x69\x66\x69\x65\x64\x3a\x20\x25\x73"};
static const mp_rom_obj_tuple_t const_obj_ymodem_10 = {{&mp_type_tuple}, 5, {
    MP_ROM_QSTR(MP_QSTR_rzsz),
    MP_ROM_QSTR(MP_QSTR_rbsb),
    MP_ROM_QSTR(MP_QSTR_pyam),
    MP_ROM_QSTR(MP_QSTR_cyam),
    MP_ROM_QSTR(MP_QSTR_kimp),
}};
static const mp_obj_str_t const_obj_ymodem_11 = {{&mp_type_str}, 7054, 29, (const byte*)"\x49\x6e\x76\x61\x6c\x69\x64\x20\x70\x72\x6f\x67\x72\x61\x6d\x20\x73\x70\x65\x63\x69\x66\x69\x65\x64\x3a\x20\x25\x73"};
static const mp_rom_obj_tuple_t const_obj_ymodem_12 = {{&mp_type_tuple}, 4, {
    MP_ROM_INT(0),
    MP_ROM_INT(1024),
    MP_ROM_INT(2048),
    MP_ROM_INT(3072),
}};
static const mp_obj_str_t const_obj_ymodem_13 = {{&mp_type_bytes}, 46501, 1, (const byte*)"\x00"};
static const mp_rom_obj_tuple_t const_obj_ymodem_14 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(128),
    MP_ROM_INT(1024),
}};
static const mp_obj_str_t const_obj_ymodem_16 = {{&mp_type_str}, 49637, 51, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x57\x61\x69\x74\x69\x6e\x67\x20\x74\x68\x65\x20\x6d\x6f\x64\x65\x20\x72\x65\x71\x75\x65\x73\x74\x20\x61\x6e\x64\x20\x6f\x70\x65\x6e\x20\x66\x69\x6c\x65\x2e\x2e\x2e"};
static const mp_obj_str_t const_obj_ymodem_17 = {{&mp_type_str}, 6097, 30, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x50\x72\x65\x70\x61\x72\x69\x6e\x67\x20\x69\x6e\x66\x6f\x20\x62\x6c\x6f\x63\x6b"};
static const mp_obj_str_t const_obj_ymodem_18 = {{&mp_type_str}, 540, 37, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x57\x61\x69\x74\x69\x6e\x67\x20\x74\x68\x65\x20\x6d\x6f\x64\x65\x20\x72\x65\x71\x75\x65\x73\x74\x2e\x2e\x2e"};
static const mp_obj_str_t const_obj_ymodem_19 = {{&mp_type_str}, 29256, 36, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x73\x74\x61\x72\x74\x20\x5f\x6d\x61\x6b\x65\x5f\x66\x69\x6c\x65\x5f\x62\x6f\x64\x79\x5f\x69\x6e\x66\x6f"};
static const mp_obj_str_t const_obj_ymodem_20 = {{&mp_type_str}, 13479, 34, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x65\x6e\x64\x20\x5f\x6d\x61\x6b\x65\x5f\x66\x69\x6c\x65\x5f\x62\x6f\x64\x79\x5f\x69\x6e\x66\x6f"};
static const mp_obj_str_t const_obj_ymodem_21 = {{&mp_type_str}, 20037, 35, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x4f\x54\x20\x73\x65\x6e\x74\x20\x61\x6e\x64\x20\x61\x77\x61\x69\x74\x69\x6e\x67\x20\x4e\x41\x4b"};
static const mp_obj_str_t const_obj_ymodem_22 = {{&mp_type_str}, 3720, 35, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x4f\x54\x20\x73\x65\x6e\x74\x20\x61\x6e\x64\x20\x61\x77\x61\x69\x74\x69\x6e\x67\x20\x41\x43\x4b"};
static const mp_obj_str_t const_obj_ymodem_23 = {{&mp_type_str}, 54206, 37, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x54\x72\x61\x6e\x73\x6d\x69\x73\x73\x69\x6f\x6e\x20\x66\x69\x6e\x69\x73\x68\x65\x64\x20\x28\x41\x43\x4b\x29"};
static const mp_rom_obj_tuple_t const_obj_ymodem_25 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(0),
    MP_ROM_INT(0),
}};
static const mp_obj_str_t const_obj_ymodem_26 = {{&mp_type_str}, 42692, 41, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x52\x65\x63\x65\x69\x76\x65\x64\x20\x63\x68\x65\x63\x6b\x73\x75\x6d\x20\x72\x65\x71\x75\x65\x73\x74\x20\x28\x4e\x41\x4b\x29"};
static const mp_obj_str_t const_obj_ymodem_27 = {{&mp_type_str}, 52481, 38, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x52\x65\x63\x65\x69\x76\x65\x64\x20\x43\x52\x43\x20\x72\x65\x71\x75\x65\x73\x74\x20\x28\x43\x2f\x43\x52\x43\x29"};
static const mp_obj_str_t const_obj_ymodem_28 = {{&mp_type_str}, 28930, 38, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x54\x72\x61\x6e\x73\x6d\x69\x73\x73\x69\x6f\x6e\x20\x63\x61\x6e\x63\x65\x6c\x6c\x65\x64\x20\x28\x43\x41\x4e\x29"};
static const mp_obj_str_t const_obj_ymodem_29 = {{&mp_type_str}, 34478, 51, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x52\x65\x61\x64\x79\x20\x66\x6f\x72\x20\x74\x72\x61\x6e\x73\x6d\x69\x73\x73\x69\x6f\x6e\x20\x63\x61\x6e\x63\x65\x6c\x6c\x61\x74\x69\x6f\x6e\x20\x28\x43\x41\x4e\x29"};
static const mp_obj_str_t const_obj_ymodem_30 = {{&mp_type_str}, 21136, 38, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x54\x72\x61\x6e\x73\x6d\x69\x73\x73\x69\x6f\x6e\x20\x63\x61\x6e\x63\x65\x6c\x6c\x65\x64\x20\x28\x45\x4f\x54\x29"};
static const mp_obj_str_t const_obj_ymodem_31 = {{&mp_type_str}, 12041, 57, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x72\x72\x6f\x72\x2c\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20\x4e\x41\x4b\x2c\x20\x43\x52\x43\x2c\x20\x45\x4f\x54\x20\x6f\x72\x20\x43\x41\x4e\x20\x62\x75\x74\x20\x67\x6f\x74\x20\x25\x72"};
static const mp_obj_str_t const_obj_ymodem_32 = {{&mp_type_str}, 14306, 32, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x4e\x6f\x20\x76\x61\x6c\x69\x64\x20\x64\x61\x74\x61\x20\x77\x61\x73\x20\x72\x65\x61\x64"};
static const mp_obj_str_t const_obj_ymodem_33 = {{&mp_type_str}, 63024, 52, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x72\x72\x6f\x72\x2c\x20\x65\x72\x72\x6f\x72\x5f\x63\x6f\x75\x6e\x74\x20\x72\x65\x61\x63\x68\x65\x64\x20\x7b\x7d\x2c\x20\x61\x62\x6f\x72\x74\x69\x6e\x67\x2e\x2e\x2e"};
static const mp_obj_str_t const_obj_ymodem_37 = {{&mp_type_str}, 21553, 32, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x42\x6c\x6f\x63\x6b\x20\x7b\x7d\x20\x28\x53\x65\x71\x20\x7b\x7d\x29\x20\x73\x65\x6e\x74"};
static const mp_obj_str_t const_obj_ymodem_38 = {{&mp_type_str}, 41597, 29, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x72\x65\x61\x64\x65\x72\x20\x72\x65\x73\x70\x20\x63\x68\x61\x72\x20\x7b\x7d"};
static const mp_obj_str_t const_obj_ymodem_39 = {{&mp_type_str}, 53212, 53, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x65\x72\x72\x6f\x72\x2c\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20\x41\x43\x4b\x20\x62\x75\x74\x20\x67\x6f\x74\x20\x7b\x7d\x20\x66\x6f\x72\x20\x62\x6c\x6f\x63\x6b\x20\x7b\x7d"};
static const mp_obj_str_t const_obj_ymodem_40 = {{&mp_type_str}, 29637, 51, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x72\x72\x6f\x72\x2c\x20\x4e\x41\x4b\x20\x72\x65\x63\x65\x69\x76\x65\x64\x20\x7b\x7d\x20\x74\x69\x6d\x65\x73\x2c\x20\x61\x62\x6f\x72\x74\x69\x6e\x67\x2e\x2e\x2e"};
static const mp_rom_obj_tuple_t const_obj_ymodem_42 = {{&mp_type_tuple}, 2, {
    MP_ROM_FALSE,
    MP_ROM_INT(0),
}};
static const mp_obj_str_t const_obj_ymodem_43 = {{&mp_type_bytes}, 46527, 1, (const byte*)"\x1a"};
static const mp_obj_str_t const_obj_ymodem_44 = {{&mp_type_str}, 57319, 39, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x45\x72\x72\x6f\x72\x2c\x20\x65\x78\x70\x65\x63\x74\x65\x64\x20\x25\x72\x20\x62\x75\x74\x20\x67\x6f\x74\x20\x25\x72"};
static const mp_obj_str_t const_obj_ymodem_45 = {{&mp_type_str}, 52718, 55, (const byte*)"\x5b\x53\x65\x6e\x64\x65\x72\x5d\x3a\x20\x57\x61\x72\x6e\x69\x6e\x67\x2c\x20\x45\x4f\x54\x20\x77\x61\x73\x20\x6e\x6f\x74\x20\x25\x72\x2c\x20\x61\x62\x6f\x72\x74\x69\x6e\x67\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x2e\x2e\x2e"};

// constant table
static const mp_rom_obj_t const_obj_table_data_ymodem[48] = {
    MP_ROM_PTR(&const_obj_ymodem_0),
    MP_ROM_PTR(&const_obj_ymodem_1),
    MP_ROM_PTR(&const_obj_ymodem_2),
    MP_ROM_PTR(&const_obj_ymodem_3),
    MP_ROM_PTR(&const_obj_ymodem_4),
    MP_ROM_PTR(&const_obj_ymodem_5),
    MP_ROM_PTR(&const_obj_ymodem_6),
    MP_ROM_PTR(&const_obj_ymodem_7),
    MP_ROM_PTR(&mp_const_empty_bytes_obj),
    MP_ROM_PTR(&const_obj_ymodem_9),
    MP_ROM_PTR(&const_obj_ymodem_10),
    MP_ROM_PTR(&const_obj_ymodem_11),
    MP_ROM_PTR(&const_obj_ymodem_12),
    MP_ROM_PTR(&const_obj_ymodem_13),
    MP_ROM_PTR(&const_obj_ymodem_14),
    MP_ROM_QSTR(MP_QSTR_trans_file_colon__space__percent_s),
    MP_ROM_PTR(&const_obj_ymodem_16),
    MP_ROM_PTR(&const_obj_ymodem_17),
    MP_ROM_PTR(&const_obj_ymodem_18),
    MP_ROM_PTR(&const_obj_ymodem_19),
    MP_ROM_PTR(&const_obj_ymodem_20),
    MP_ROM_PTR(&const_obj_ymodem_21),
    MP_ROM_PTR(&const_obj_ymodem_22),
    MP_ROM_PTR(&const_obj_ymodem_23),
    MP_ROM_QSTR(MP_QSTR__bracket_open_Sender_bracket_close__colon__space_Received_space__percent_r),
    MP_ROM_PTR(&const_obj_ymodem_25),
    MP_ROM_PTR(&const_obj_ymodem_26),
    MP_ROM_PTR(&const_obj_ymodem_27),
    MP_ROM_PTR(&const_obj_ymodem_28),
    MP_ROM_PTR(&const_obj_ymodem_29),
    MP_ROM_PTR(&const_obj_ymodem_30),
    MP_ROM_PTR(&const_obj_ymodem_31),
    MP_ROM_PTR(&const_obj_ymodem_32),
    MP_ROM_PTR(&const_obj_ymodem_33),
    MP_ROM_QSTR(MP_QSTR_1_space_target_space_name_space__percent_s),
    MP_ROM_QSTR(MP_QSTR_2_space_target_space_name_space__percent_s),
    MP_ROM_QSTR(MP_QSTR__bracket_open_Sender_bracket_close__colon__space_data_colon__space__brace_open__brace_close_),
    MP_ROM_PTR(&const_obj_ymodem_37),
    MP_ROM_PTR(&const_obj_ymodem_38),
    MP_ROM_PTR(&const_obj_ymodem_39),
    MP_ROM_PTR(&const_obj_ymodem_40),
    MP_ROM_QSTR(MP_QSTR__bracket_open_Sender_bracket_close__colon__space_Reached_space_EOF),
    MP_ROM_PTR(&const_obj_ymodem_42),
    MP_ROM_PTR(&const_obj_ymodem_43),
    MP_ROM_PTR(&const_obj_ymodem_44),
    MP_ROM_PTR(&const_obj_ymodem_45),
    MP_ROM_QSTR(MP_QSTR_source_colon__space__percent_s_comma__space_target_colon__space__percent_s),
    MP_ROM_QSTR(MP_QSTR_File_space__bracket_open__brace_open__brace_close__bracket_close__space_is_space_not_space_exists_dot_),
};

static const mp_frozen_module_t frozen_module_ymodem = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_ymodem,
        .obj_table = (mp_obj_t *)&const_obj_table_data_ymodem,
    },
    .proto_fun = &proto_fun_ymodem__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module ql_fs
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\ql_fs.mpy
// - frozen file name: ql_fs.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file ql_fs.py, scope ql_fs__lt_module_gt_
static const byte fun_data_ql_fs__lt_module_gt_[92] = {
    0x18,0x2e, // prelude
    0x01, // names: <module>
    0x80,0x11,0x26,0x66,0x8b,0x08,0x84,0x0d,0x84,0x0f,0x84,0x12,0x84,0x07,0x84,0x0b,0x84,0x0e,0x8a,0x13,0x64,0x20, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME 'uos'
    0x16,0x02, // STORE_NAME 'uos'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x03, // IMPORT_NAME 'ujson'
    0x16,0x03, // STORE_NAME 'ujson'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x04, // LOAD_CONST_STRING 'FileNotFoundError'
    0x11,0x26, // LOAD_NAME 'Exception'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x04, // STORE_NAME 'FileNotFoundError'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x06, // STORE_NAME 'path_exists'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x08, // STORE_NAME 'file_copy'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x0e, // STORE_NAME 'path_dirname'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x12, // STORE_NAME 'path_getsize'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x13, // STORE_NAME 'mkdirs'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x16, // STORE_NAME 'rmdirs'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x10,0x05, // LOAD_CONST_STRING 'json'
    0x2a,0x02, // BUILD_TUPLE 2
    0x53, // LOAD_NULL
    0x33,0x07, // MAKE_FUNCTION_DEFARGS 7
    0x16,0x19, // STORE_NAME 'touch'
    0x32,0x08, // MAKE_FUNCTION 8
    0x16,0x1f, // STORE_NAME 'write_json'
    0x32,0x09, // MAKE_FUNCTION 9
    0x16,0x20, // STORE_NAME 'read_json'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_FileNotFoundError
static const byte fun_data_ql_fs_FileNotFoundError[24] = {
    0x00,0x08, // prelude
    0x04, // names: FileNotFoundError
    0x88,0x16,0x64, // code info
    0x11,0x27, // LOAD_NAME '__name__'
    0x16,0x28, // STORE_NAME '__module__'
    0x10,0x04, // LOAD_CONST_STRING 'FileNotFoundError'
    0x16,0x29, // STORE_NAME '__qualname__'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x23, // STORE_NAME '__init__'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x25, // STORE_NAME '__str__'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of ql_fs_FileNotFoundError
// frozen bytecode for file ql_fs.py, scope ql_fs_FileNotFoundError___init__
static const byte fun_data_ql_fs_FileNotFoundError___init__[13] = {
    0x1a,0x0a, // prelude
    0x23,0x34,0x24, // names: __init__, self, value
    0x80,0x17, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x24, // STORE_ATTR 'value'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_FileNotFoundError___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_FileNotFoundError___init__,
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
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 35,
        .line_info = fun_data_ql_fs_FileNotFoundError___init__ + 5,
        .line_info_top = fun_data_ql_fs_FileNotFoundError___init__ + 7,
        .opcodes = fun_data_ql_fs_FileNotFoundError___init__ + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_FileNotFoundError___init__ fun_data_ql_fs_FileNotFoundError___init__[0]
#endif

// child of ql_fs_FileNotFoundError
// frozen bytecode for file ql_fs.py, scope ql_fs_FileNotFoundError___str__
static const byte fun_data_ql_fs_FileNotFoundError___str__[14] = {
    0x11,0x08, // prelude
    0x25,0x34, // names: __str__, self
    0x80,0x1a, // code info
    0x12,0x35, // LOAD_GLOBAL 'repr'
    0xb0, // LOAD_FAST 0
    0x13,0x24, // LOAD_ATTR 'value'
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_FileNotFoundError___str__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_FileNotFoundError___str__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
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
        .qstr_block_name_idx = 37,
        .line_info = fun_data_ql_fs_FileNotFoundError___str__ + 4,
        .line_info_top = fun_data_ql_fs_FileNotFoundError___str__ + 6,
        .opcodes = fun_data_ql_fs_FileNotFoundError___str__ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_FileNotFoundError___str__ fun_data_ql_fs_FileNotFoundError___str__[0]
#endif

static const mp_raw_code_t *const children_ql_fs_FileNotFoundError[] = {
    (const mp_raw_code_t *)&proto_fun_ql_fs_FileNotFoundError___init__,
    (const mp_raw_code_t *)&proto_fun_ql_fs_FileNotFoundError___str__,
};

static const mp_raw_code_truncated_t proto_fun_ql_fs_FileNotFoundError = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_FileNotFoundError,
    .children = (void *)&children_ql_fs_FileNotFoundError,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 24,
    .n_children = 2,
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
        .qstr_block_name_idx = 4,
        .line_info = fun_data_ql_fs_FileNotFoundError + 3,
        .line_info_top = fun_data_ql_fs_FileNotFoundError + 6,
        .opcodes = fun_data_ql_fs_FileNotFoundError + 6,
    },
    #endif
    #endif
};

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_path_exists
static const byte fun_data_ql_fs_path_exists[56] = {
    0xb9,0x02,0x14, // prelude
    0x06,0x2a, // names: path_exists, path
    0x80,0x1e,0x23,0x42,0x22,0x29,0x42,0x4d, // code info
    0xb0, // LOAD_FAST 0
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x48,0x0f, // SETUP_EXCEPT 15
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x07, // LOAD_METHOD 'stat'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x4a,0x13, // POP_EXCEPT_JUMP 19
    0x57, // DUP_TOP
    0x12,0x26, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xc1, // STORE_FAST 1
    0x49,0x02, // SETUP_FINALLY 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xc1, // STORE_FAST 1
    0x28,0x01, // DELETE_FAST 1
    0x5d, // END_FINALLY
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_path_exists = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_path_exists,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 56,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 6,
        .line_info = fun_data_ql_fs_path_exists + 5,
        .line_info_top = fun_data_ql_fs_path_exists + 13,
        .opcodes = fun_data_ql_fs_path_exists + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_path_exists fun_data_ql_fs_path_exists[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_file_copy
static const byte fun_data_ql_fs_file_copy[86] = {
    0x3a,0x1e, // prelude
    0x08,0x2b,0x2c, // names: file_copy, dstFile, srcFile
    0x80,0x2b,0x27,0x42,0x28,0x28,0x29,0x22,0x27,0x2c,0x26,0x26, // code info
    0x12,0x06, // LOAD_GLOBAL 'path_exists'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x42, // POP_JUMP_IF_TRUE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0x12,0x2d, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x09, // LOAD_CONST_STRING 'wb+'
    0x34,0x02, // CALL_FUNCTION 2
    0xc2, // STORE_FAST 2
    0x12,0x2d, // LOAD_GLOBAL 'open'
    0xb1, // LOAD_FAST 1
    0x10,0x0a, // LOAD_CONST_STRING 'rb'
    0x34,0x02, // CALL_FUNCTION 2
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0x14,0x0b, // LOAD_METHOD 'read'
    0x22,0xa0,0x00, // LOAD_CONST_SMALL_INT 4096
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0x42,0x50, // JUMP 16
    0xb2, // LOAD_FAST 2
    0x14,0x0c, // LOAD_METHOD 'write'
    0xb4, // LOAD_FAST 4
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x14,0x0b, // LOAD_METHOD 'read'
    0x22,0xa0,0x00, // LOAD_CONST_SMALL_INT 4096
    0x36,0x01, // CALL_METHOD 1
    0xc4, // STORE_FAST 4
    0xb4, // LOAD_FAST 4
    0x43,0x2d, // POP_JUMP_IF_TRUE -19
    0xb2, // LOAD_FAST 2
    0x14,0x0d, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x14,0x0d, // LOAD_METHOD 'close'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_file_copy = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_file_copy,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 86,
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
        .qstr_block_name_idx = 8,
        .line_info = fun_data_ql_fs_file_copy + 5,
        .line_info_top = fun_data_ql_fs_file_copy + 17,
        .opcodes = fun_data_ql_fs_file_copy + 17,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_file_copy fun_data_ql_fs_file_copy[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_path_dirname
static const byte fun_data_ql_fs_path_dirname[85] = {
    0x41,0x20, // prelude
    0x0e,0x2a, // names: path_dirname, path
    0x80,0x3a,0x23,0x43,0x28,0x25,0x23,0x25,0x43,0x23,0x2a,0x25,0x22,0x2f, // code info
    0xb0, // LOAD_FAST 0
    0x43,0x43, // POP_JUMP_IF_TRUE 3
    0x10,0x0f, // LOAD_CONST_STRING ''
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x14,0x10, // LOAD_METHOD 'rfind'
    0x10,0x11, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd7, // BINARY_OP 0 __lt__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x10,0x0f, // LOAD_CONST_STRING ''
    0x63, // RETURN_VALUE
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x10,0x11, // LOAD_CONST_STRING '/'
    0x63, // RETURN_VALUE
    0x10,0x0f, // LOAD_CONST_STRING ''
    0xc2, // STORE_FAST 2
    0x12,0x2e, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x51, // JUMP 17
    0x57, // DUP_TOP
    0xc3, // STORE_FAST 3
    0xb3, // LOAD_FAST 3
    0xb1, // LOAD_FAST 1
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x42,0x4d, // JUMP 13
    0xb2, // LOAD_FAST 2
    0xb0, // LOAD_FAST 0
    0xb3, // LOAD_FAST 3
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0xc2, // STORE_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x2a, // POP_JUMP_IF_TRUE -22
    0x59, // POP_TOP
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_path_dirname = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_path_dirname,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 85,
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
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 14,
        .line_info = fun_data_ql_fs_path_dirname + 4,
        .line_info_top = fun_data_ql_fs_path_dirname + 18,
        .opcodes = fun_data_ql_fs_path_dirname + 18,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_path_dirname fun_data_ql_fs_path_dirname[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_path_getsize
static const byte fun_data_ql_fs_path_getsize[36] = {
    0x19,0x0c, // prelude
    0x12,0x2a, // names: path_getsize, path
    0x80,0x4c,0x27,0x4a, // code info
    0x12,0x06, // LOAD_GLOBAL 'path_exists'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x4a, // POP_JUMP_IF_FALSE 10
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x07, // LOAD_METHOD 'stat'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x7c, // LOAD_CONST_SMALL_INT -4
    0x55, // LOAD_SUBSCR
    0x63, // RETURN_VALUE
    0x12,0x04, // LOAD_GLOBAL 'FileNotFoundError'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0xb0, // LOAD_FAST 0
    0xf8, // BINARY_OP 33 __mod__
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_path_getsize = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_path_getsize,
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
        .n_state = 4,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 18,
        .line_info = fun_data_ql_fs_path_getsize + 4,
        .line_info_top = fun_data_ql_fs_path_getsize + 8,
        .opcodes = fun_data_ql_fs_path_getsize + 8,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_path_getsize fun_data_ql_fs_path_getsize[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_mkdirs
static const byte fun_data_ql_fs_mkdirs[88] = {
    0x59,0x16, // prelude
    0x13,0x2f, // names: mkdirs, dir
    0x80,0x53,0x28,0x24,0x29,0x2a,0x28,0x2d,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x14, // LOAD_METHOD 'split'
    0x10,0x11, // LOAD_CONST_STRING '/'
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0xc2, // STORE_FAST 2
    0x12,0x30, // LOAD_GLOBAL 'enumerate'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x5f, // GET_ITER_STACK
    0x4b,0x35, // FOR_ITER 53
    0xc3, // STORE_FAST 3
    0xb2, // LOAD_FAST 2
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0x12,0x06, // LOAD_GLOBAL 'path_exists'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x15, // LOAD_METHOD 'mkdir'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x12,0x2e, // LOAD_GLOBAL 'len'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf3, // BINARY_OP 28 __sub__
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x46, // POP_JUMP_IF_FALSE 6
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x59, // POP_TOP
    0x42,0x4f, // JUMP 15
    0xb2, // LOAD_FAST 2
    0x10,0x11, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb1, // LOAD_FAST 1
    0xb3, // LOAD_FAST 3
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x55, // LOAD_SUBSCR
    0xf2, // BINARY_OP 27 __add__
    0xc2, // STORE_FAST 2
    0x42,0x09, // JUMP -55
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_mkdirs = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_mkdirs,
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
        .n_state = 12,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 19,
        .line_info = fun_data_ql_fs_mkdirs + 4,
        .line_info_top = fun_data_ql_fs_mkdirs + 13,
        .opcodes = fun_data_ql_fs_mkdirs + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_mkdirs fun_data_ql_fs_mkdirs[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_rmdirs
static const byte fun_data_ql_fs_rmdirs[93] = {
    0x51,0x18, // prelude
    0x16,0x2f, // names: rmdirs, dir
    0x80,0x5e,0x28,0x23,0x4a,0x25,0x27,0x34,0x48,0x2a, // code info
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x17, // LOAD_METHOD 'listdir'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x43,0x4a, // POP_JUMP_IF_TRUE 10
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x18, // LOAD_METHOD 'remove'
    0xb0, // LOAD_FAST 0
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x78, // JUMP 56
    0xb1, // LOAD_FAST 1
    0x5f, // GET_ITER_STACK
    0x4b,0x2e, // FOR_ITER 46
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x10,0x11, // LOAD_CONST_STRING '/'
    0xf2, // BINARY_OP 27 __add__
    0xb2, // LOAD_FAST 2
    0xf2, // BINARY_OP 27 __add__
    0xc2, // STORE_FAST 2
    0x12,0x31, // LOAD_GLOBAL 'int'
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x07, // LOAD_METHOD 'stat'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x80, // LOAD_CONST_SMALL_INT 0
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x22,0x81,0x80,0x00, // LOAD_CONST_SMALL_INT 16384
    0xef, // BINARY_OP 24 __and__
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0x12,0x16, // LOAD_GLOBAL 'rmdirs'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x42,0x48, // JUMP 8
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x18, // LOAD_METHOD 'remove'
    0xb2, // LOAD_FAST 2
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x10, // JUMP -48
    0x12,0x16, // LOAD_GLOBAL 'rmdirs'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_rmdirs = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_rmdirs,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 93,
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
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 22,
        .line_info = fun_data_ql_fs_rmdirs + 4,
        .line_info_top = fun_data_ql_fs_rmdirs + 14,
        .opcodes = fun_data_ql_fs_rmdirs + 14,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_rmdirs fun_data_ql_fs_rmdirs[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_touch
static const byte fun_data_ql_fs_touch[145] = {
    0xe0,0x86,0x01,0x24, // prelude
    0x19,0x32,0x33,0x1b,0x1c, // names: touch, file, data, i, file_type
    0x80,0x6c,0x29,0x25,0x2c,0x2d,0x50,0x22,0x2a,0x26,0x4f,0x55,0x4a, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x1a, // LOAD_METHOD 'find'
    0x10,0x11, // LOAD_CONST_STRING '/'
    0xb2, // LOAD_FAST 2
    0x36,0x02, // CALL_METHOD 2
    0xc2, // STORE_FAST 2
    0xb2, // LOAD_FAST 2
    0x7f, // LOAD_CONST_SMALL_INT -1
    0xdc, // BINARY_OP 5 __ne__
    0x44,0x69, // POP_JUMP_IF_FALSE 41
    0x12,0x06, // LOAD_GLOBAL 'path_exists'
    0xb0, // LOAD_FAST 0
    0x51, // LOAD_CONST_NONE
    0xb2, // LOAD_FAST 2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x34,0x01, // CALL_FUNCTION 1
    0x43,0x4d, // POP_JUMP_IF_TRUE 13
    0x12,0x02, // LOAD_GLOBAL 'uos'
    0x14,0x15, // LOAD_METHOD 'mkdir'
    0xb0, // LOAD_FAST 0
    0x51, // LOAD_CONST_NONE
    0xb2, // LOAD_FAST 2
    0x2e,0x02, // BUILD_SLICE 2
    0x55, // LOAD_SUBSCR
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x12,0x19, // LOAD_GLOBAL 'touch'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x10,0x1b, // LOAD_CONST_STRING 'i'
    0xb2, // LOAD_FAST 2
    0x81, // LOAD_CONST_SMALL_INT 1
    0xf2, // BINARY_OP 27 __add__
    0x10,0x1c, // LOAD_CONST_STRING 'file_type'
    0xb3, // LOAD_FAST 3
    0x34,0x84,0x02, // CALL_FUNCTION 514
    0x63, // RETURN_VALUE
    0x48,0x2b, // SETUP_EXCEPT 43
    0x12,0x2d, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x1d, // LOAD_CONST_STRING 'w'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x1e, // SETUP_WITH 30
    0xc4, // STORE_FAST 4
    0xb3, // LOAD_FAST 3
    0x10,0x05, // LOAD_CONST_STRING 'json'
    0xd9, // BINARY_OP 2 __eq__
    0x44,0x4f, // POP_JUMP_IF_FALSE 15
    0xb4, // LOAD_FAST 4
    0x14,0x0c, // LOAD_METHOD 'write'
    0x12,0x03, // LOAD_GLOBAL 'ujson'
    0x14,0x1e, // LOAD_METHOD 'dumps'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x42,0x47, // JUMP 7
    0xb4, // LOAD_FAST 4
    0x14,0x0c, // LOAD_METHOD 'write'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x4a,0x13, // POP_EXCEPT_JUMP 19
    0x57, // DUP_TOP
    0x12,0x26, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x4c, // POP_JUMP_IF_FALSE 12
    0xc5, // STORE_FAST 5
    0x49,0x02, // SETUP_FINALLY 2
    0x7f, // LOAD_CONST_SMALL_INT -1
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xc5, // STORE_FAST 5
    0x28,0x05, // DELETE_FAST 5
    0x5d, // END_FINALLY
    0x4a,0x03, // POP_EXCEPT_JUMP 3
    0x5d, // END_FINALLY
    0x80, // LOAD_CONST_SMALL_INT 0
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_touch = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_touch,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 145,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 13,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 2,
        .qstr_block_name_idx = 25,
        .line_info = fun_data_ql_fs_touch + 9,
        .line_info_top = fun_data_ql_fs_touch + 22,
        .opcodes = fun_data_ql_fs_touch + 22,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_touch fun_data_ql_fs_touch[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_write_json
static const byte fun_data_ql_fs_write_json[14] = {
    0x22,0x0a, // prelude
    0x1f,0x32,0x33, // names: write_json, file, data
    0x80,0x7f, // code info
    0x12,0x19, // LOAD_GLOBAL 'touch'
    0xb0, // LOAD_FAST 0
    0xb1, // LOAD_FAST 1
    0x34,0x02, // CALL_FUNCTION 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_write_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_write_json,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
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
        .qstr_block_name_idx = 31,
        .line_info = fun_data_ql_fs_write_json + 5,
        .line_info_top = fun_data_ql_fs_write_json + 7,
        .opcodes = fun_data_ql_fs_write_json + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_write_json fun_data_ql_fs_write_json[0]
#endif

// child of ql_fs__lt_module_gt_
// frozen bytecode for file ql_fs.py, scope ql_fs_read_json
static const byte fun_data_ql_fs_read_json[42] = {
    0x35,0x0e, // prelude
    0x20,0x32, // names: read_json, file
    0x80,0x83,0x27,0x2a,0x4c, // code info
    0x12,0x06, // LOAD_GLOBAL 'path_exists'
    0xb0, // LOAD_FAST 0
    0x34,0x01, // CALL_FUNCTION 1
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x12,0x2d, // LOAD_GLOBAL 'open'
    0xb0, // LOAD_FAST 0
    0x10,0x21, // LOAD_CONST_STRING 'r'
    0x34,0x02, // CALL_FUNCTION 2
    0x47,0x09, // SETUP_WITH 9
    0xc1, // STORE_FAST 1
    0x12,0x03, // LOAD_GLOBAL 'ujson'
    0x14,0x22, // LOAD_METHOD 'load'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x63, // RETURN_VALUE
    0x5c, // WITH_CLEANUP
    0x5d, // END_FINALLY
    0x42,0x42, // JUMP 2
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_ql_fs_read_json = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs_read_json,
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
        .n_state = 7,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 32,
        .line_info = fun_data_ql_fs_read_json + 4,
        .line_info_top = fun_data_ql_fs_read_json + 9,
        .opcodes = fun_data_ql_fs_read_json + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun_ql_fs_read_json fun_data_ql_fs_read_json[0]
#endif

static const mp_raw_code_t *const children_ql_fs__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_ql_fs_FileNotFoundError,
    (const mp_raw_code_t *)&proto_fun_ql_fs_path_exists,
    (const mp_raw_code_t *)&proto_fun_ql_fs_file_copy,
    (const mp_raw_code_t *)&proto_fun_ql_fs_path_dirname,
    (const mp_raw_code_t *)&proto_fun_ql_fs_path_getsize,
    (const mp_raw_code_t *)&proto_fun_ql_fs_mkdirs,
    (const mp_raw_code_t *)&proto_fun_ql_fs_rmdirs,
    (const mp_raw_code_t *)&proto_fun_ql_fs_touch,
    (const mp_raw_code_t *)&proto_fun_ql_fs_write_json,
    (const mp_raw_code_t *)&proto_fun_ql_fs_read_json,
};

static const mp_raw_code_truncated_t proto_fun_ql_fs__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_ql_fs__lt_module_gt_,
    .children = (void *)&children_ql_fs__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 92,
    .n_children = 10,
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
        .line_info = fun_data_ql_fs__lt_module_gt_ + 3,
        .line_info_top = fun_data_ql_fs__lt_module_gt_ + 25,
        .opcodes = fun_data_ql_fs__lt_module_gt_ + 25,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_ql_fs[54] = {
    MP_QSTR_ql_fs_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_uos,
    MP_QSTR_ujson,
    MP_QSTR_FileNotFoundError,
    MP_QSTR_json,
    MP_QSTR_path_exists,
    MP_QSTR_stat,
    MP_QSTR_file_copy,
    MP_QSTR_wb_plus_,
    MP_QSTR_rb,
    MP_QSTR_read,
    MP_QSTR_write,
    MP_QSTR_close,
    MP_QSTR_path_dirname,
    MP_QSTR_,
    MP_QSTR_rfind,
    MP_QSTR__slash_,
    MP_QSTR_path_getsize,
    MP_QSTR_mkdirs,
    MP_QSTR_split,
    MP_QSTR_mkdir,
    MP_QSTR_rmdirs,
    MP_QSTR_listdir,
    MP_QSTR_remove,
    MP_QSTR_touch,
    MP_QSTR_find,
    MP_QSTR_i,
    MP_QSTR_file_type,
    MP_QSTR_w,
    MP_QSTR_dumps,
    MP_QSTR_write_json,
    MP_QSTR_read_json,
    MP_QSTR_r,
    MP_QSTR_load,
    MP_QSTR___init__,
    MP_QSTR_value,
    MP_QSTR___str__,
    MP_QSTR_Exception,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_path,
    MP_QSTR_dstFile,
    MP_QSTR_srcFile,
    MP_QSTR_open,
    MP_QSTR_len,
    MP_QSTR_dir,
    MP_QSTR_enumerate,
    MP_QSTR_int,
    MP_QSTR_file,
    MP_QSTR_data,
    MP_QSTR_self,
    MP_QSTR_repr,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data_ql_fs[1] = {
    MP_ROM_QSTR(MP_QSTR_can_space_not_space_find_colon__space__squot__percent_s_squot_),
};

static const mp_frozen_module_t frozen_module_ql_fs = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_ql_fs,
        .obj_table = (mp_obj_t *)&const_obj_table_data_ql_fs,
    },
    .proto_fun = &proto_fun_ql_fs__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module queue
// - original source file: E:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build\queue.mpy
// - frozen file name: queue.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file queue.py, scope queue__lt_module_gt_
static const byte fun_data_queue__lt_module_gt_[23] = {
    0x18,0x04, // prelude
    0x01, // names: <module>
    0x66, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x51, // LOAD_CONST_NONE
    0x1b,0x02, // IMPORT_NAME '_thread'
    0x16,0x02, // STORE_NAME '_thread'
    0x54, // LOAD_BUILD_CLASS
    0x32,0x00, // MAKE_FUNCTION 0
    0x10,0x03, // LOAD_CONST_STRING 'Queue'
    0x11,0x15, // LOAD_NAME 'object'
    0x34,0x03, // CALL_FUNCTION 3
    0x16,0x03, // STORE_NAME 'Queue'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of queue__lt_module_gt_
// frozen bytecode for file queue.py, scope queue_Queue
static const byte fun_data_queue_Queue[64] = {
    0x08,0x1c, // prelude
    0x03, // names: Queue
    0x68,0x20,0x8a,0x07,0x88,0x08,0x84,0x0b,0x84,0x08,0x84,0x07,0x64, // code info
    0x11,0x16, // LOAD_NAME '__name__'
    0x16,0x17, // STORE_NAME '__module__'
    0x10,0x03, // LOAD_CONST_STRING 'Queue'
    0x16,0x18, // STORE_NAME '__qualname__'
    0x22,0x80,0x64, // LOAD_CONST_SMALL_INT 100
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x00, // MAKE_FUNCTION_DEFARGS 0
    0x16,0x04, // STORE_NAME '__init__'
    0x51, // LOAD_CONST_NONE
    0x2a,0x01, // BUILD_TUPLE 1
    0x53, // LOAD_NULL
    0x33,0x01, // MAKE_FUNCTION_DEFARGS 1
    0x16,0x0b, // STORE_NAME 'put'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x0f, // STORE_NAME '__pop'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x11, // STORE_NAME 'get'
    0x32,0x04, // MAKE_FUNCTION 4
    0x16,0x0c, // STORE_NAME '__put'
    0x32,0x05, // MAKE_FUNCTION 5
    0x16,0x14, // STORE_NAME 'empty'
    0x32,0x06, // MAKE_FUNCTION 6
    0x16,0x12, // STORE_NAME 'size'
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue___init__
static const byte fun_data_queue_Queue___init__[49] = {
    0x9a,0x01,0x12, // prelude
    0x04,0x19,0x05, // names: __init__, self, maxsize
    0x60,0x40,0x24,0x25,0x29,0x29, // code info
    0xb1, // LOAD_FAST 1
    0xb0, // LOAD_FAST 0
    0x18,0x05, // STORE_ATTR 'maxsize'
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x18,0x06, // STORE_ATTR '__deque'
    0x12,0x02, // LOAD_GLOBAL '_thread'
    0x14,0x07, // LOAD_METHOD 'allocate_lock'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x08, // STORE_ATTR '__lock_queue'
    0x12,0x02, // LOAD_GLOBAL '_thread'
    0x14,0x07, // LOAD_METHOD 'allocate_lock'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x18,0x09, // STORE_ATTR '__lock_signal'
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '__lock_signal'
    0x14,0x0a, // LOAD_METHOD 'acquire'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue___init__ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue___init__,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 49,
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
        .qstr_block_name_idx = 4,
        .line_info = fun_data_queue_Queue___init__ + 6,
        .line_info_top = fun_data_queue_Queue___init__ + 12,
        .opcodes = fun_data_queue_Queue___init__ + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue___init__ fun_data_queue_Queue___init__[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue_put
static const byte fun_data_queue_Queue_put[55] = {
    0xaa,0x01,0x14, // prelude
    0x0b,0x19,0x1a, // names: put, self, item
    0x80,0x0c,0x28,0x27,0x28,0x29,0x28, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR '__lock_queue'
    0x14,0x0a, // LOAD_METHOD 'acquire'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x0c, // LOAD_METHOD '__put'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0xc2, // STORE_FAST 2
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR '__lock_queue'
    0x14,0x0d, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '__lock_signal'
    0x14,0x0e, // LOAD_METHOD 'locked'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x48, // POP_JUMP_IF_FALSE 8
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '__lock_signal'
    0x14,0x0d, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue_put = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue_put,
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
        .n_state = 6,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 1,
        .qstr_block_name_idx = 11,
        .line_info = fun_data_queue_Queue_put + 6,
        .line_info_top = fun_data_queue_Queue_put + 13,
        .opcodes = fun_data_queue_Queue_put + 13,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue_put fun_data_queue_Queue_put[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue___pop
static const byte fun_data_queue_Queue___pop[63] = {
    0xb9,0x02,0x12, // prelude
    0x0f,0x19, // names: __pop, self
    0x80,0x14,0x28,0x24,0x52,0x44,0x46, // code info
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR '__lock_queue'
    0x14,0x0a, // LOAD_METHOD 'acquire'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x49,0x1e, // SETUP_FINALLY 30
    0x48,0x0b, // SETUP_EXCEPT 11
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR '__deque'
    0x14,0x10, // LOAD_METHOD 'pop'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x36,0x01, // CALL_METHOD 1
    0xc1, // STORE_FAST 1
    0x4a,0x0b, // POP_EXCEPT_JUMP 11
    0x57, // DUP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'Exception'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x44, // POP_JUMP_IF_FALSE 4
    0x59, // POP_TOP
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x63, // RETURN_VALUE
    0x5d, // END_FINALLY
    0x81, // LOAD_CONST_SMALL_INT 1
    0xb1, // LOAD_FAST 1
    0x2a,0x02, // BUILD_TUPLE 2
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0xb0, // LOAD_FAST 0
    0x13,0x08, // LOAD_ATTR '__lock_queue'
    0x14,0x0d, // LOAD_METHOD 'release'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0x5d, // END_FINALLY
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue___pop = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue___pop,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 63,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 8,
        .n_exc_stack = 2,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 15,
        .line_info = fun_data_queue_Queue___pop + 5,
        .line_info_top = fun_data_queue_Queue___pop + 12,
        .opcodes = fun_data_queue_Queue___pop + 12,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue___pop fun_data_queue_Queue___pop[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue_get
static const byte fun_data_queue_Queue_get[46] = {
    0x21,0x12, // prelude
    0x11,0x19, // names: get, self
    0x80,0x1f,0x27,0x28,0x29,0x23,0x26, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x12, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0x43,0x48, // POP_JUMP_IF_TRUE 8
    0xb0, // LOAD_FAST 0
    0x13,0x09, // LOAD_ATTR '__lock_signal'
    0x14,0x0a, // LOAD_METHOD 'acquire'
    0x36,0x00, // CALL_METHOD 0
    0x59, // POP_TOP
    0xb0, // LOAD_FAST 0
    0x14,0x0f, // LOAD_METHOD '__pop'
    0x36,0x00, // CALL_METHOD 0
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xc1, // STORE_FAST 1
    0xc2, // STORE_FAST 2
    0xb1, // LOAD_FAST 1
    0x43,0x46, // POP_JUMP_IF_TRUE 6
    0xb0, // LOAD_FAST 0
    0x14,0x11, // LOAD_METHOD 'get'
    0x36,0x00, // CALL_METHOD 0
    0x63, // RETURN_VALUE
    0xb2, // LOAD_FAST 2
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue_get = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue_get,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 46,
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
        .qstr_block_name_idx = 17,
        .line_info = fun_data_queue_Queue_get + 4,
        .line_info_top = fun_data_queue_Queue_get + 11,
        .opcodes = fun_data_queue_Queue_get + 11,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue_get fun_data_queue_Queue_get[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue___put
static const byte fun_data_queue_Queue___put[36] = {
    0x22,0x10, // prelude
    0x0c,0x19,0x1a, // names: __put, self, item
    0x80,0x27,0x2b,0x42,0x29, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x12, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0x13,0x05, // LOAD_ATTR 'maxsize'
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x42, // POP_JUMP_IF_FALSE 2
    0x50, // LOAD_CONST_FALSE
    0x63, // RETURN_VALUE
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR '__deque'
    0x14,0x13, // LOAD_METHOD 'append'
    0xb1, // LOAD_FAST 1
    0x36,0x01, // CALL_METHOD 1
    0x59, // POP_TOP
    0x52, // LOAD_CONST_TRUE
    0x63, // RETURN_VALUE
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue___put = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue___put,
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
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 12,
        .line_info = fun_data_queue_Queue___put + 5,
        .line_info_top = fun_data_queue_Queue___put + 10,
        .opcodes = fun_data_queue_Queue___put + 10,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue___put fun_data_queue_Queue___put[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue_empty
static const byte fun_data_queue_Queue_empty[13] = {
    0x11,0x08, // prelude
    0x14,0x19, // names: empty, self
    0x80,0x2e, // code info
    0xb0, // LOAD_FAST 0
    0x14,0x12, // LOAD_METHOD 'size'
    0x36,0x00, // CALL_METHOD 0
    0xd3, // UNARY_OP 3 <not>
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue_empty = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue_empty,
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
        .n_state = 3,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 20,
        .line_info = fun_data_queue_Queue_empty + 4,
        .line_info_top = fun_data_queue_Queue_empty + 6,
        .opcodes = fun_data_queue_Queue_empty + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue_empty fun_data_queue_Queue_empty[0]
#endif

// child of queue_Queue
// frozen bytecode for file queue.py, scope queue_Queue_size
static const byte fun_data_queue_Queue_size[14] = {
    0x11,0x08, // prelude
    0x12,0x19, // names: size, self
    0x80,0x31, // code info
    0x12,0x1c, // LOAD_GLOBAL 'len'
    0xb0, // LOAD_FAST 0
    0x13,0x06, // LOAD_ATTR '__deque'
    0x34,0x01, // CALL_FUNCTION 1
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun_queue_Queue_size = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue_size,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 14,
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
        .qstr_block_name_idx = 18,
        .line_info = fun_data_queue_Queue_size + 4,
        .line_info_top = fun_data_queue_Queue_size + 6,
        .opcodes = fun_data_queue_Queue_size + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun_queue_Queue_size fun_data_queue_Queue_size[0]
#endif

static const mp_raw_code_t *const children_queue_Queue[] = {
    (const mp_raw_code_t *)&proto_fun_queue_Queue___init__,
    (const mp_raw_code_t *)&proto_fun_queue_Queue_put,
    (const mp_raw_code_t *)&proto_fun_queue_Queue___pop,
    (const mp_raw_code_t *)&proto_fun_queue_Queue_get,
    (const mp_raw_code_t *)&proto_fun_queue_Queue___put,
    (const mp_raw_code_t *)&proto_fun_queue_Queue_empty,
    (const mp_raw_code_t *)&proto_fun_queue_Queue_size,
};

static const mp_raw_code_truncated_t proto_fun_queue_Queue = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue_Queue,
    .children = (void *)&children_queue_Queue,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 64,
    .n_children = 7,
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
        .qstr_block_name_idx = 3,
        .line_info = fun_data_queue_Queue + 3,
        .line_info_top = fun_data_queue_Queue + 16,
        .opcodes = fun_data_queue_Queue + 16,
    },
    #endif
    #endif
};

static const mp_raw_code_t *const children_queue__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun_queue_Queue,
};

static const mp_raw_code_truncated_t proto_fun_queue__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data_queue__lt_module_gt_,
    .children = (void *)&children_queue__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 23,
    .n_children = 1,
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
        .line_info = fun_data_queue__lt_module_gt_ + 3,
        .line_info_top = fun_data_queue__lt_module_gt_ + 4,
        .opcodes = fun_data_queue__lt_module_gt_ + 4,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data_queue[29] = {
    MP_QSTR_queue_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR__thread,
    MP_QSTR_Queue,
    MP_QSTR___init__,
    MP_QSTR_maxsize,
    MP_QSTR___deque,
    MP_QSTR_allocate_lock,
    MP_QSTR___lock_queue,
    MP_QSTR___lock_signal,
    MP_QSTR_acquire,
    MP_QSTR_put,
    MP_QSTR___put,
    MP_QSTR_release,
    MP_QSTR_locked,
    MP_QSTR___pop,
    MP_QSTR_pop,
    MP_QSTR_get,
    MP_QSTR_size,
    MP_QSTR_append,
    MP_QSTR_empty,
    MP_QSTR_object,
    MP_QSTR___name__,
    MP_QSTR___module__,
    MP_QSTR___qualname__,
    MP_QSTR_self,
    MP_QSTR_item,
    MP_QSTR_Exception,
    MP_QSTR_len,
};

// constants
static const mp_rom_obj_tuple_t const_obj_queue_0 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(0),
    MP_ROM_NONE,
}};

// constant table
static const mp_rom_obj_t const_obj_table_data_queue[1] = {
    MP_ROM_PTR(&const_obj_queue_0),
};

static const mp_frozen_module_t frozen_module_queue = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data_queue,
        .obj_table = (mp_obj_t *)&const_obj_table_data_queue,
    },
    .proto_fun = &proto_fun_queue__lt_module_gt_,
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
    "myutils.py\0"
    "ymodem.py\0"
    "ql_fs.py\0"
    "queue.py\0"
    "\0"
};

const mp_frozen_module_t *const mp_frozen_mpy_content[] = {
    &frozen_module_zlib,
    &frozen_module_gzip,
    &frozen_module__thread,
    &frozen_module_ssl,
    &frozen_module_lcd160cr,
    &frozen_module_myutils,
    &frozen_module_ymodem,
    &frozen_module_ql_fs,
    &frozen_module_queue,
};

#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("zlib", "zlib.py")
MICROPY_FROZEN_LIST_ITEM("gzip", "gzip.py")
MICROPY_FROZEN_LIST_ITEM("_thread", "_thread.py")
MICROPY_FROZEN_LIST_ITEM("ssl", "ssl.py")
MICROPY_FROZEN_LIST_ITEM("lcd160cr", "lcd160cr.py")
MICROPY_FROZEN_LIST_ITEM("myutils", "myutils.py")
MICROPY_FROZEN_LIST_ITEM("ymodem", "ymodem.py")
MICROPY_FROZEN_LIST_ITEM("ql_fs", "ql_fs.py")
MICROPY_FROZEN_LIST_ITEM("queue", "queue.py")
#endif

/*
byte sizes:
qstr content: 300 unique, 3848 bytes
bc content: 13154
const str content: 1187
const int content: 4
const obj content: 744
const table qstr content: 0 entries, 0 bytes
const table ptr content: 79 entries, 316 bytes
raw code content: 167 * 4 = 2672
mp_frozen_mpy_names_content: 86
mp_frozen_mpy_content_size: 36
total: 22047
*/
