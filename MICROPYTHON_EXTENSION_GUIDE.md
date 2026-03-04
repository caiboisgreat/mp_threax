# MicroPython 组件扩展方法完整指南

本文档整理了 MicroPython 的所有组件扩展方法，并提供详细的示范流程。

---

## 📋 目录

1. [扩展方法概览](#扩展方法概览)
2. [方法一：C 模块扩展（extmod）](#方法一c-模块扩展extmod)
3. [方法二：用户 C 模块（User C Module）](#方法二用户-c-模块user-c-module)
4. [方法三：冻结 Python 模块](#方法三冻结-python-模块)
5. [方法四：动态原生模块](#方法四动态原生模块)
6. [方法五：移植层扩展（Port-specific）](#方法五移植层扩展portspecific)
7. [选择建议](#选择建议)

---

## 🎯 扩展方法概览

| 方法 | 实现语言 | 编译方式 | 灵活性 | 性能 | 适用场景 |
|------|---------|---------|--------|------|---------|
| **C 模块扩展** | C | 内置编译 | 中 | 最高 | 核心功能、硬件驱动 |
| **用户 C 模块** | C | 独立编译 | 高 | 最高 | 第三方库、可移植模块 |
| **冻结 Python** | Python | 预编译 | 最高 | 中 | 业务逻辑、库封装 |
| **动态原生模块** | C/Asm | 运行时加载 | 高 | 高 | 可更新功能 |
| **移植层扩展** | C | 内置编译 | 低 | 最高 | 平台特定功能 |

---

## 方法一：C 模块扩展（extmod）

### 📝 概述
在 `extmod/` 目录下添加 C 模块，适合添加通用的、可跨平台的模块。

### ✅ 优点
- 性能最优
- 完全控制硬件
- 可访问所有 MicroPython 内部 API

### ❌ 缺点
- 需要重新编译固件
- 修改后需要刷写整个固件

### 🚀 实现流程

#### 步骤 1：创建模块文件

在 `Middlewares/micropython/extmod/` 下创建 `modsubsystem.c`（已存在）：

```c
/*
 * 自定义子系统模块示例
 */

#include "py/obj.h"
#include "py/runtime.h"
#include <string.h>

#if MICROPY_PY_SUBSYSTEM

// ========== 函数定义 ==========

// 无参数函数
static mp_obj_t py_subsystem_info(void) {
    return MP_OBJ_NEW_SMALL_INT(42);
}

// 返回字符串
static mp_obj_t hello(void) {
    char str[] = "My name is CaiBo!";
    return mp_obj_new_str(str, strlen(str));
}

// 带参数函数示例
static mp_obj_t py_subsystem_add(mp_obj_t a_obj, mp_obj_t b_obj) {
    int a = mp_obj_get_int(a_obj);
    int b = mp_obj_get_int(b_obj);
    return mp_obj_new_int(a + b);
}

// 可变参数函数
static mp_obj_t py_subsystem_sum(size_t n_args, const mp_obj_t *args) {
    int sum = 0;
    for (size_t i = 0; i < n_args; i++) {
        sum += mp_obj_get_int(args[i]);
    }
    return mp_obj_new_int(sum);
}

// ========== 函数对象定义 ==========

static MP_DEFINE_CONST_FUN_OBJ_0(subsystem_info_obj, py_subsystem_info);
static MP_DEFINE_CONST_FUN_OBJ_0(hello_obj, hello);
static MP_DEFINE_CONST_FUN_OBJ_2(subsystem_add_obj, py_subsystem_add);
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(subsystem_sum_obj, 0, MP_OBJ_FUN_ARGS_MAX, py_subsystem_sum);

// ========== 模块全局表 ==========

static const mp_rom_map_elem_t mp_module_subsystem_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_subsystem) },
    { MP_ROM_QSTR(MP_QSTR_info), MP_ROM_PTR(&subsystem_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_hello), MP_ROM_PTR(&hello_obj) },
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&subsystem_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_sum), MP_ROM_PTR(&subsystem_sum_obj) },
};

static MP_DEFINE_CONST_DICT(mp_module_subsystem_globals, mp_module_subsystem_globals_table);

// ========== 模块定义 ==========

const mp_obj_module_t mp_module_subsystem = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mp_module_subsystem_globals,
};

// ========== 模块注册 ==========

MP_REGISTER_MODULE(MP_QSTR_subsystem, mp_module_subsystem);

#endif // MICROPY_PY_SUBSYSTEM
```

#### 步骤 2：在 mpconfigport.h 中启用模块

编辑 `Middlewares/micropython/py_port/mpconfigport.h`，添加：

```c
// 自定义模块开关
#define MICROPY_PY_SUBSYSTEM              (1)
```

#### 步骤 3：添加到编译系统

**Keil 项目**：将 `modsubsystem.c` 添加到项目中

**Makefile 项目**：编辑 `extmod/extmod.mk`，添加：
```makefile
SRC_EXTMOD_C += extmod/modsubsystem.c
```

#### 步骤 4：编译和测试

```bash
# 编译固件
# 在 Keil 中：Project -> Build Target

# 烧录固件后测试
>>> import subsystem
>>> subsystem.hello()
'My name is CaiBo!'
>>> subsystem.add(10, 20)
30
>>> subsystem.sum(1, 2, 3, 4, 5)
15
```

---

## 方法二：用户 C 模块（User C Module）

### 📝 概述
独立于 MicroPython 源码树的 C 模块，通过 `USER_C_MODULES` 变量指定。

### ✅ 优点
- 代码独立，易于维护
- 可跨项目复用
- 支持版本控制

### ❌ 缺点
- 需要配置编译脚本
- 在 Keil 中集成稍复杂

### 🚀 实现流程

#### 步骤 1：创建模块目录结构

```
mp_threadx/
└── user_modules/
    └── mymodule/
        ├── micropython.mk
        ├── mymodule.c
        └── mymodule.h
```

#### 步骤 2：创建 micropython.mk

`user_modules/mymodule/micropython.mk`：
```makefile
MYMODULE_MOD_DIR := $(USERMOD_DIR)

# 添加源文件
SRC_USERMOD += $(MYMODULE_MOD_DIR)/mymodule.c

# 添加头文件路径
CFLAGS_USERMOD += -I$(MYMODULE_MOD_DIR)
```

#### 步骤 3：实现模块

`user_modules/mymodule/mymodule.c`：
```c
#include "py/obj.h"
#include "py/runtime.h"

static mp_obj_t mymodule_hello(void) {
    mp_printf(&mp_plat_print, "Hello from User C Module!\n");
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(mymodule_hello_obj, mymodule_hello);

static const mp_rom_map_elem_t mymodule_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_mymodule) },
    { MP_ROM_QSTR(MP_QSTR_hello), MP_ROM_PTR(&mymodule_hello_obj) },
};
static MP_DEFINE_CONST_DICT(mymodule_module_globals, mymodule_module_globals_table);

const mp_obj_module_t mymodule_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&mymodule_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_mymodule, mymodule_user_cmodule);
```

#### 步骤 4：配置编译

**Makefile 方式**：
```bash
make USER_C_MODULES=../user_modules
```

**Keil 方式**：
- 将 `mymodule.c` 添加到项目
- 添加 `user_modules/mymodule` 到 Include Paths

---

## 方法三：冻结 Python 模块

### 📝 概述
将 Python 代码预编译为 `.mpy` 字节码，嵌入固件中。

### ✅ 优点
- 使用 Python 开发，简单快速
- 占用 Flash，不占用 RAM
- 启动时无需编译

### ❌ 缺点
- 性能不如 C 模块
- 修改需要重新编译固件
- 不能访问底层硬件

### 🚀 实现流程

> ⚠️ **重要**: 你的项目已经配置好冻结模块基础设施！详细步骤请查看：[FROZEN_MODULE_KEIL_GUIDE.md](FROZEN_MODULE_KEIL_GUIDE.md)

#### 快速开始（针对你的项目）

**步骤 1**：创建 Python 模块

在 `Middlewares/micropython/py_port/frozen_build/` 创建 `mylib.py`：
```python
# Frozen module example

def greet(name):
    return f"Hello, {name}!"

class Calculator:
    def __init__(self):
        self.result = 0
    
    def add(self, x):
        self.result += x
        return self.result
    
    def reset(self):
        self.result = 0

# 模块常量
VERSION = "1.0.0"
```

**步骤 2**：使用自动化脚本编译

```powershell
# 编译模块
python tools\freeze_module.py mylib
```

**步骤 3**：添加到允许列表

编辑 `tools/regenerate_micropython_genhdr.py`，添加：
```python
frozen_allowlist = [
    "zlib.mpy",
    "gzip.mpy",
    "_thread.mpy",
    "ssl.mpy",
    "lcd160cr.mpy",
    "mylib.mpy",      # 👈 添加这一行
]
```

重新生成：
```powershell
python tools\regenerate_micropython_genhdr.py
```

**步骤 4**：在 Keil 中编译

- Project -> Rebuild all target files (F7)

**步骤 5**：烧录和测试

```python
>>> import mylib
>>> mylib.greet("MicroPython")
'Hello, MicroPython!'
>>> calc = mylib.Calculator()
>>> calc.add(10)
10
>>> calc.add(5)
15
```

#### 完整文档

详细的 MDK-ARM 冻结模块指南请参考：
- [在 MDK-ARM 中实现冻结 Python 模块完整指南](FROZEN_MODULE_KEIL_GUIDE.md)
- 示例模块：[myutils.py](Middlewares/micropython/py_port/frozen_build/myutils.py)
- 自动化脚本：[freeze_module.py](tools/freeze_module.py)

---

## 方法四：动态原生模块

### 📝 概述
编译为 `.mpy` 原生代码模块，可在运行时从文件系统加载。

### ✅ 优点
- 可在不刷固件的情况下更新
- 性能接近 C 模块
- 支持热更新

### ❌ 缺点
- 需要启用原生代码支持
- 架构相关（ARM/x86）
- 占用文件系统空间

### 🚀 实现流程

#### 步骤 1：启用原生代码支持

在 `mpconfigport.h` 中：
```c
#define MICROPY_EMIT_NATIVE               (1)
#define MICROPY_EMIT_INLINE_THUMB         (1)  // ARM Thumb2
```

#### 步骤 2：编写原生模块

`myfast.py`：
```python
# 使用 @micropython.native 装饰器
import micropython

@micropython.native
def fast_sum(n: int) -> int:
    total = 0
    for i in range(n):
        total += i
    return total

@micropython.viper
def viper_sum(n: int) -> int:
    total = 0
    for i in range(n):
        total += i
    return total
```

#### 步骤 3：编译为 .mpy

```bash
# 编译为原生代码
mpy-cross -march=armv7m myfast.py

# 生成 myfast.mpy
```

#### 步骤 4：部署和使用

```python
# 将 myfast.mpy 复制到设备文件系统
# 然后导入使用
>>> import myfast
>>> myfast.fast_sum(1000)
499500
```

---

## 方法五：移植层扩展（Port-specific）

### 📝 概述
在 `py_port/` 目录下添加特定于硬件平台的模块。

### ✅ 优点
- 完全访问硬件资源
- 与平台深度集成
- 性能最优

### ❌ 缺点
- 不可移植
- 与固件紧密耦合

### 🚀 实现流程

#### 步骤 1：创建移植层模块

`py_port/modboard.c`：
```c
#include "py/obj.h"
#include "py/runtime.h"
#include "stm32f4xx_hal.h"

// 读取芯片 ID
static mp_obj_t board_chip_id(void) {
    uint32_t id[3];
    id[0] = HAL_GetUIDw0();
    id[1] = HAL_GetUIDw1();
    id[2] = HAL_GetUIDw2();
    
    char buf[32];
    snprintf(buf, sizeof(buf), "%08X%08X%08X", 
             (unsigned)id[0], (unsigned)id[1], (unsigned)id[2]);
    return mp_obj_new_str(buf, strlen(buf));
}
static MP_DEFINE_CONST_FUN_OBJ_0(board_chip_id_obj, board_chip_id);

// 获取系统时钟频率
static mp_obj_t board_sys_clock(void) {
    return mp_obj_new_int(HAL_RCC_GetSysClockFreq());
}
static MP_DEFINE_CONST_FUN_OBJ_0(board_sys_clock_obj, board_sys_clock);

static const mp_rom_map_elem_t board_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_board) },
    { MP_ROM_QSTR(MP_QSTR_chip_id), MP_ROM_PTR(&board_chip_id_obj) },
    { MP_ROM_QSTR(MP_QSTR_sys_clock), MP_ROM_PTR(&board_sys_clock_obj) },
};
static MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);

const mp_obj_module_t board_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&board_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_board, board_module);
```

#### 步骤 2：添加到 Keil 项目

将 `modboard.c` 添加到项目的 `py_port` 组中。

#### 步骤 3：使用

```python
>>> import board
>>> board.chip_id()
'2F003A001234567890ABCDEF'
>>> board.sys_clock()
168000000
```

---

## 🎯 选择建议

### 场景 1：硬件驱动（GPIO、I2C、SPI）
**推荐**：移植层扩展（方法五）
- 直接访问 HAL 库
- 性能最优

### 场景 2：通用算法库（加密、压缩）
**推荐**：用户 C 模块（方法二）或 extmod（方法一）
- 可跨项目复用
- 性能好

### 场景 3：业务逻辑、协议处理
**推荐**：冻结 Python 模块（方法三）
- 开发快速
- 易于维护

### 场景 4：需要热更新的功能
**推荐**：动态原生模块（方法四）
- 无需刷固件
- 保持较高性能

### 场景 5：快速原型验证
**推荐**：纯 Python（不冻结）
- 实时修改测试
- 确认后再冻结

---

## 📚 进阶技巧

### 1. 类型定义

```c
// 定义一个类类型
typedef struct _myclass_obj_t {
    mp_obj_base_t base;
    int value;
} myclass_obj_t;

static mp_obj_t myclass_make_new(const mp_obj_type_t *type, size_t n_args, 
                                   size_t n_kw, const mp_obj_t *args) {
    myclass_obj_t *self = mp_obj_malloc(myclass_obj_t, type);
    self->value = 0;
    return MP_OBJ_FROM_PTR(self);
}

static void myclass_print(const mp_print_t *print, mp_obj_t self_in, 
                          mp_print_kind_t kind) {
    myclass_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "<MyClass value=%d>", self->value);
}

MP_DEFINE_CONST_OBJ_TYPE(
    myclass_type,
    MP_QSTR_MyClass,
    MP_TYPE_FLAG_NONE,
    make_new, myclass_make_new,
    print, myclass_print
);
```

### 2. 异常处理

```c
static mp_obj_t risky_function(mp_obj_t arg) {
    if (!mp_obj_is_int(arg)) {
        mp_raise_TypeError(MP_ERROR_TEXT("expected int"));
    }
    
    int val = mp_obj_get_int(arg);
    if (val < 0) {
        mp_raise_ValueError(MP_ERROR_TEXT("value must be positive"));
    }
    
    return mp_obj_new_int(val * 2);
}
```

### 3. 回调函数

```c
// 保存 Python 回调
static mp_obj_t callback = mp_const_none;

static mp_obj_t set_callback(mp_obj_t func) {
    callback = func;
    return mp_const_none;
}

// 在 C 代码中调用
void hardware_interrupt_handler(void) {
    if (callback != mp_const_none) {
        mp_call_function_0(callback);
    }
}
```

---

## 🔧 调试技巧

### 1. 打印调试

```c
#include "py/runtime.h"

mp_printf(&mp_plat_print, "Debug: value=%d\n", value);
```

### 2. 查看对象类型

```python
>>> import subsystem
>>> type(subsystem.hello)
<class 'function'>
>>> dir(subsystem)
['__name__', 'hello', 'info', 'add', 'sum']
```

### 3. 内存调试

```c
// 在 mpconfigport.h 启用
#define MICROPY_DEBUG_PRINTERS            (1)
#define MICROPY_MEM_STATS                 (1)
```

---

## 📖 参考资源

- [MicroPython 官方文档](https://docs.micropython.org/)
- [扩展 MicroPython](https://docs.micropython.org/en/latest/develop/cmodules.html)
- [MicroPython GitHub](https://github.com/micropython/micropython)
- 当前项目示例：[modsubsystem.c](Middlewares/micropython/extmod/modsubsystem.c)

---

**创建日期**：2026-01-28  
**适用版本**：MicroPython 1.20+  
**测试平台**：STM32F405 + ThreadX
