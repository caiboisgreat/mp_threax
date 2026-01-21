# Pyboard板载库移植摘要 / Pyboard Port Modules Summary

## 概述 / Overview

本项目已成功移植了MicroPython官方pyboard的三个板载库，使STM32F405RGT6 + ThreadX平台能够使用pyboard特有的API和功能。

The project has successfully ported three board-specific modules from the official MicroPython pyboard, enabling STM32F405RGT6 + ThreadX platform to use pyboard-specific APIs and features.

## 已移植的模块 / Ported Modules

### 1. `pyb` 模块 (C实现 / C Implementation)

**文件位置 / File Location:** `Middlewares/micropython/py_port/modpyb.c`

**功能 / Features:**
- `pyb.info()` - 显示系统信息
- `pyb.delay(ms)` - 毫秒延时
- `pyb.udelay(us)` - 微秒延时
- `pyb.millis()` - 获取毫秒计数
- `pyb.micros()` - 获取微秒计数
- `pyb.elapsed_millis(start)` - 计算经过的毫秒数
- `pyb.elapsed_micros(start)` - 计算经过的微秒数

**使用示例 / Usage Example:**
```python
import pyb

pyb.info()                  # 打印系统信息
start = pyb.millis()        # 记录开始时间
pyb.delay(1000)             # 延时1秒
elapsed = pyb.elapsed_millis(start)  # 计算经过时间
print(f"用时: {elapsed}ms")
```

### 2. `stm` 模块 (C实现 / C Implementation)

**文件位置 / File Location:** `Middlewares/micropython/py_port/modstm.c`

**功能 / Features:**
- 内存访问对象: `stm.mem8`, `stm.mem16`, `stm.mem32`
- STM32F405外设基地址常量 (GPIO, UART, SPI, I2C, Timer等)

**使用示例 / Usage Example:**
```python
import stm

# 读取芯片ID
chip_id = stm.mem32[0xE0042000]
print(f"芯片ID: 0x{chip_id:08X}")

# 访问GPIOA寄存器
gpioa_idr = stm.mem32[stm.GPIOA + 0x10]  # 读取输入数据寄存器
stm.mem32[stm.GPIOA + 0x18] = (1 << 5)   # 设置PA5引脚
```

### 3. `lcd160cr` 模块 (Python实现 / Python Implementation)

**文件位置 / File Location:** `Middlewares/micropython/lib/lcd160cr/lcd160cr.py`

**功能 / Features:**
- 官方LCD160CR显示屏驱动
- 图形绘制 (点、线、矩形等)
- 文本显示
- 触摸屏支持
- 帧缓冲和SPI快速刷新

**使用示例 / Usage Example:**
```python
import lcd160cr

# 初始化显示屏
lcd = lcd160cr.LCD160CR('X')

# 设置方向和颜色
lcd.set_orient(lcd160cr.PORTRAIT)
lcd.set_pen(lcd.rgb(255, 0, 0), lcd.rgb(0, 0, 0))

# 绘制图形
lcd.erase()
lcd.rect(10, 10, 50, 50)
lcd.line(0, 0, 160, 128)

# 显示文本
lcd.set_text_color(lcd.rgb(255, 255, 255), lcd.rgb(0, 0, 0))
lcd.set_font(1)
lcd.set_pos(0, 0)
lcd.write('你好 MicroPython!')

# 读取触摸
if lcd.is_touched():
    touching, x, y = lcd.get_touch()
    print(f"触摸位置: ({x}, {y})")
```

## 文件结构 / File Structure

```
Middlewares/micropython/
├── py_port/
│   ├── modpyb.c                    # pyb模块C源码
│   ├── modstm.c                    # stm模块C源码
│   ├── mpconfigport.h              # 端口配置(已更新)
│   ├── qstrdefsport.h              # QSTR定义(已更新)
│   ├── PYBOARD_MODULES.md          # 详细使用文档
│   └── PYBOARD_MODULES_README.md   # 本文件
└── lib/
    └── lcd160cr/
        ├── lcd160cr.py             # LCD160CR驱动(Python)
        └── manifest.py             # 冻结配置
```

## 编译说明 / Build Instructions

### 1. KEIL项目配置

需要将以下源文件添加到KEIL项目中：
- ✅ `Middlewares/micropython/py_port/modpyb.c` (新增)
- ✅ `Middlewares/micropython/py_port/modstm.c` (已存在)

`lcd160cr.py` 是Python模块，会被自动冻结到固件中，无需手动添加。

### 2. 配置文件修改

已自动更新以下配置：
- ✅ `mpconfigport.h` - 启用 MICROPY_PY_PYB 和 MICROPY_PY_STM
- ✅ `qstrdefsport.h` - 添加所有模块的QSTR定义

### 3. 重新编译

1. 清理项目
2. 重新生成QSTR (QSTR会自动从qstrdefsport.h读取)
3. 编译整个项目

## 测试代码 / Test Code

创建测试文件 `test_pyboard.py`：

```python
# 基础功能测试
import pyb
import stm

print("=== Pyboard模块测试 ===")
pyb.info()
print()

# 延时测试
print("延时测试...")
start = pyb.millis()
pyb.delay(100)
elapsed = pyb.elapsed_millis(start)
print(f"pyb.delay(100): 实际用时 {elapsed}ms")
print()

# stm模块测试
print("=== STM模块测试 ===")
chip_id = stm.mem32[0xE0042000]
print(f"芯片ID: 0x{chip_id:08X}")
print(f"GPIOA基址: 0x{stm.GPIOA:08X}")
print(f"RCC基址: 0x{stm.RCC:08X}")
print()

# LCD160CR测试(如果有硬件)
try:
    import lcd160cr
    print("=== LCD160CR模块测试 ===")
    print("lcd160cr模块已成功导入")
    print("如需测试显示功能，请确保LCD160CR硬件已连接")
except ImportError:
    print("lcd160cr模块未冻结或硬件未连接")
```

## 参考文档 / Documentation

详细的使用文档请参考：
- [PYBOARD_MODULES.md](PYBOARD_MODULES.md) - 完整的API文档和示例

官方参考：
- [MicroPython官方文档](https://docs.micropython.org/)
- [Pyboard库参考](https://docs.micropython.org/en/latest/library/index.html#port-specific-libraries)

---

✅ 移植完成！/ Port completed!
