# KEIL 项目配置指南 - 添加 pyb 和 stm 模块

## 问题诊断

如果 `help('modules')` 没有显示 `pyb` 和 `stm` 模块，原因是：

**modpyb.c 和 modstm.c 没有被添加到 KEIL 项目中进行编译。**

## 解决步骤

### 步骤 1: 在 KEIL 中添加源文件

1. **打开 KEIL MDK-ARM 项目**
   - 文件位置: `MDK-ARM/mp_threadx.uvprojx`

2. **在项目浏览器中找到 MicroPython 源文件组**
   - 展开项目树
   - 找到包含其他 MicroPython 模块的组 (如 `py_port` 或 `Middlewares`)

3. **添加 modpyb.c**
   - 右键点击该组 → **Add Existing Files to Group...**
   - 浏览到: `Middlewares\micropython\py_port\modpyb.c`
   - 点击 **Add** 然后 **Close**

4. **添加 modstm.c (如果还没有)**
   - 同样的方式添加: `Middlewares\micropython\py_port\modstm.c`

### 步骤 2: 验证文件已添加

在 KEIL 项目树中，你应该能看到:

```
Project
  └─ mp_threadx
      └─ [某个组名]
          ├─ modpyb.c      ← 新添加
          ├─ modstm.c      ← 应该已存在或新添加
          ├─ modneopixel.c ← 已存在的其他模块
          └─ ...
```

### 步骤 3: 清理并重新编译

1. **清理项目**
   - 菜单: `Project` → `Clean Targets` (或按 Alt+F7)

2. **重新编译**
   - 菜单: `Project` → `Build Target` (或按 F7)
   - 等待编译完成，确保没有错误

3. **检查编译输出**
   - 在 Build Output 窗口中，应该能看到类似:
     ```
     compiling modpyb.c...
     compiling modstm.c...
     ```

### 步骤 4: 烧录新固件

1. **烧录固件**
   - 菜单: `Flash` → `Download` (或按 F8)
   - 或使用你常用的烧录工具

2. **复位板子**
   - 按复位按钮或重新上电

### 步骤 5: 测试验证

在 MicroPython REPL 中运行:

```python
# 运行诊断脚本
import check_modules

# 或者手动测试
help('modules')  # 应该能看到 pyb 和 stm

# 测试 pyb 模块
import pyb
pyb.info()
pyb.delay(100)
print("pyb 模块正常!")

# 测试 stm 模块
import stm
print(f"GPIOA 基址: 0x{stm.GPIOA:08X}")
chip_id = stm.mem32[0xE0042000]
print(f"芯片ID: 0x{chip_id:08X}")
print("stm 模块正常!")
```

## 常见问题

### Q1: 找不到 modpyb.c 文件
**A:** 确认文件路径是 `Middlewares\micropython\py_port\modpyb.c`

### Q2: 编译时出现 "undefined reference" 错误
**A:** 确保在 `mpconfigport.h` 中有:
```c
#define MICROPY_PY_PYB (1)
#define MICROPY_PY_STM (1)
```

### Q3: 编译成功但模块仍然找不到
**A:** 
1. 确认固件确实被烧录了 (检查文件时间戳)
2. 确认板子被复位了
3. 尝试运行 `import sys; sys.modules` 查看所有已注册的模块

### Q4: lcd160cr 模块找不到
**A:** 这是 Python 模块，需要正确配置冻结模块系统。检查:
1. `Middlewares\micropython\lib\lcd160cr\lcd160cr.py` 存在
2. `Middlewares\micropython\lib\lcd160cr\manifest.py` 存在
3. 构建系统支持 frozen modules

## 快速验证清单

- [ ] modpyb.c 已添加到 KEIL 项目
- [ ] modstm.c 已添加到 KEIL 项目
- [ ] MICROPY_PY_PYB 在 mpconfigport.h 中定义为 1
- [ ] MICROPY_PY_STM 在 mpconfigport.h 中定义为 1
- [ ] 项目已清理并重新编译
- [ ] 新固件已烧录到板子
- [ ] 板子已复位
- [ ] 运行 check_modules.py 验证

## 预期结果

成功后，`help('modules')` 应该显示:

```
__main__          errno             socket            umachine
_asyncio          framebuf          ssl               ure
_thread           gc                stm               uselect
asyncio           json              struct            usocket
binascii          lcd160cr          sys               ussl
bluetooth         machine           time              ustruct
btree             math              ubinascii         uzlib
builtins          micropython       ucryptolib        zlib
cmath             neopixel          uctypes
collections       openamp           uhashlib
cryptolib         pyb               uheapq
                  ...
```

注意 `pyb`, `stm`, `lcd160cr` 应该在列表中。
