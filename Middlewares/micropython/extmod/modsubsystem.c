
/*
	测试添加一个子系统模块  by caibo 2026-01-27
*/

#include "py/obj.h"
#include "py/runtime.h"
#include <string.h>

#if MICROPY_PY_SUBSYSTEM

// info()
static mp_obj_t py_subsystem_info(void) {
    return MP_OBJ_NEW_SMALL_INT(42);
}

static mp_obj_t hello(void) {
   char str[] = "My name is CaiBo!";
   return mp_obj_new_str(str, strlen(str));
}

static MP_DEFINE_CONST_FUN_OBJ_0(subsystem_info_obj, py_subsystem_info);
static MP_DEFINE_CONST_FUN_OBJ_0(hello_obj, hello);

static const mp_rom_map_elem_t mp_module_subsystem_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_subsystem) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&subsystem_info_obj) },
		{ MP_ROM_QSTR(MP_QSTR_hello), MP_ROM_PTR(&hello_obj) },
};

static MP_DEFINE_CONST_DICT(mp_module_subsystem_globals, mp_module_subsystem_globals_table);

const mp_obj_module_t mp_module_subsystem = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_subsystem_globals,
};

MP_REGISTER_MODULE(MP_QSTR_subsystem, mp_module_subsystem);

#endif // MICROPY_PY_SUBSYSTEM