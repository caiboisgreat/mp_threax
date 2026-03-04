# 在 MDK-ARM (Keil) 中冻结 Python 模块完整指南

> 本指南针对你的 mp_threadx 项目，提供在 Keil MDK-ARM 环境下实现冻结 Python 模块的完整方案。

---

## 📋 目录

1. [什么是冻结模块](#什么是冻结模块)
2. [你的项目现状](#你的项目现状)
3. [实现方法](#实现方法)
4. [完整示例流程](#完整示例流程)
5. [常见问题](#常见问题)

---

## 🎯 什么是冻结模块

### 原理
- 将 `.py` 文件预编译为 `.mpy` 字节码
- 使用 `mpy-tool.py` 将多个 `.mpy` 打包成一个 `frozen_mpy.c` 文件
- 在固件编译时将 `frozen_mpy.c` 链接进去
- 运行时可直接 `import`，无需从文件系统加载

### 优势
- **节省 RAM**：字节码存储在 Flash 中
- **启动快速**：无需运行时编译
- **可靠性高**：不依赖文件系统

---

## 📊 你的项目现状

### ✅ 已有基础设施

你的项目**已经配置好**冻结模块框架：

1. **配置已启用** ([mpconfigport.h](Middlewares/micropython/py_port/mpconfigport.h#L101))
   ```c
   #define MICROPY_MODULE_FROZEN_MPY         (1)
   #define MICROPY_QSTR_EXTRA_POOL           mp_qstr_frozen_const_pool
   ```

2. **已有冻结模块目录**
   ```
   Middlewares/micropython/py_port/frozen_build/
   ├── zlib.mpy      ✅ 已冻结
   ├── gzip.mpy      ✅ 已冻结
   ├── ssl.mpy       ✅ 已冻结
   ├── _thread.mpy   ✅ 已冻结
   └── lcd160cr.mpy  ✅ 已冻结
   ```

3. **生成的 C 文件**
   ```
   Middlewares/micropython/py_port/frozen_mpy.c  (6041 行)
   ```

4. **自动化工具**
   - `tools/compile_lcd160cr.py` - 编译单个模块
   - `tools/regenerate_micropython_genhdr.py` - 重新生成所有头文件

### 🔧 工具链

你的项目使用：
- **mpy-cross**：位于 `Middlewares/micropython/mpy-cross/build/mpy-cross.exe`
- **mpy-tool.py**：位于 `Middlewares/micropython/tools/mpy-tool.py`

---

## 🚀 实现方法

在 Keil 中添加冻结 Python 模块有**两种方法**：

### 方法 A：使用现有脚本（推荐）⭐

利用项目现有的 Python 脚本，自动完成编译和生成。

### 方法 B：手动编译（适合调试）

逐步手动执行每个步骤，便于理解和调试。

---

## 📝 完整示例流程

### 示例：添加自定义 `myutils.py` 模块

假设我们要冻结一个自定义的工具模块。

---

### 🔸 步骤 1：创建 Python 模块文件

在 `Middlewares/micropython/py_port/frozen_build/` 创建 `myutils.py`：

```python
"""
自定义工具模块 - 将被冻结到固件中
"""

# 版本信息
__version__ = "1.0.0"
__author__ = "CaiBo"

# 简单函数
def greet(name="World"):
    """问候函数"""
    return f"Hello, {name}!"

def calculate_checksum(data):
    """计算简单校验和"""
    if isinstance(data, str):
        data = data.encode()
    return sum(data) & 0xFF

# 实用类
class DataBuffer:
    """简单的数据缓冲区"""
    def __init__(self, size=128):
        self.buffer = bytearray(size)
        self.pos = 0
    
    def write(self, data):
        if isinstance(data, str):
            data = data.encode()
        for b in data:
            if self.pos < len(self.buffer):
                self.buffer[self.pos] = b
                self.pos += 1
    
    def read(self):
        return bytes(self.buffer[:self.pos])
    
    def clear(self):
        self.pos = 0
        for i in range(len(self.buffer)):
            self.buffer[i] = 0

# 常量定义
LED_RED = 0
LED_GREEN = 1
LED_BLUE = 2

# 配置字典
DEFAULT_CONFIG = {
    'baud_rate': 115200,
    'timeout': 1000,
    'buffer_size': 256,
}
```

---

### 🔸 步骤 2：编译为 .mpy 文件

#### 方法 A1：创建自动化脚本（推荐）

创建 `tools/compile_myutils.py`：

```python
#!/usr/bin/env python3
"""
编译 myutils.py 并重新生成冻结模块
"""

import os
import subprocess
import sys

# 项目路径
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
MPY_CROSS = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'mpy-cross', 'build', 'mpy-cross.exe')
SOURCE_PY = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'py_port', 'frozen_build', 'myutils.py')
OUTPUT_MPY = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'py_port', 'frozen_build', 'myutils.mpy')
REGENERATE_SCRIPT = os.path.join(PROJECT_ROOT, 'tools', 'regenerate_micropython_genhdr.py')

def main():
    print("=" * 70)
    print("编译 myutils 模块并重新生成冻结文件")
    print("=" * 70)
    
    # 1. 检查工具
    if not os.path.exists(MPY_CROSS):
        print(f"❌ 错误：mpy-cross 未找到: {MPY_CROSS}")
        return 1
    
    if not os.path.exists(SOURCE_PY):
        print(f"❌ 错误：源文件未找到: {SOURCE_PY}")
        return 1
    
    # 2. 编译 .py -> .mpy
    print(f"\n📝 步骤 1: 编译 Python 模块")
    print(f"   源文件: {SOURCE_PY}")
    print(f"   输出: {OUTPUT_MPY}")
    
    try:
        result = subprocess.run(
            [MPY_CROSS, '-o', OUTPUT_MPY, '-s', 'myutils.py', 'myutils.py'],
            cwd=os.path.dirname(SOURCE_PY),
            capture_output=True,
            text=True,
            check=False
        )
        
        if result.returncode != 0:
            print(f"   ❌ 编译失败!")
            print(f"   错误: {result.stderr}")
            return 1
        
        print(f"   ✅ 编译成功: {OUTPUT_MPY}")
        
    except Exception as e:
        print(f"   ❌ 异常: {e}")
        return 1
    
    # 3. 重新生成 frozen_mpy.c
    print(f"\n📝 步骤 2: 重新生成 frozen_mpy.c")
    print(f"   运行: {REGENERATE_SCRIPT}")
    
    try:
        result = subprocess.run(
            [sys.executable, REGENERATE_SCRIPT],
            cwd=PROJECT_ROOT,
            capture_output=True,
            text=True,
            check=False
        )
        
        if result.returncode != 0:
            print(f"   ❌ 生成失败!")
            print(f"   输出: {result.stdout}")
            print(f"   错误: {result.stderr}")
            return 1
        
        print(result.stdout)
        print(f"   ✅ frozen_mpy.c 已更新")
        
    except Exception as e:
        print(f"   ❌ 异常: {e}")
        return 1
    
    print("\n" + "=" * 70)
    print("✅ 完成！现在可以在 Keil 中重新编译项目")
    print("=" * 70)
    print("\n使用方法:")
    print("  >>> import myutils")
    print("  >>> myutils.greet('MicroPython')")
    print("  'Hello, MicroPython!'")
    print()
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

**运行脚本**：
```powershell
cd tools
python compile_myutils.py
```

#### 方法 A2：修改现有的 regenerate_micropython_genhdr.py

编辑 `tools/regenerate_micropython_genhdr.py`，在 `frozen_allowlist` 中添加：

```python
frozen_allowlist = [
    "zlib.mpy",
    "gzip.mpy",
    "_thread.mpy",
    "ssl.mpy",
    "lcd160cr.mpy",
    "myutils.mpy",      # 👈 添加这一行
]
```

然后手动编译 `.py` -> `.mpy`：
```powershell
cd Middlewares\micropython\py_port\frozen_build

# 编译
..\..\mpy-cross\build\mpy-cross.exe -o myutils.mpy -s myutils.py myutils.py

# 重新生成
cd ..\..\..\..\tools
python regenerate_micropython_genhdr.py
```

#### 方法 B：手动逐步编译

```powershell
# 1. 编译 Python 到 .mpy
cd e:\Work\code\study\mp_threadx\Middlewares\micropython\py_port\frozen_build
..\..\..\micropython\mpy-cross\build\mpy-cross.exe myutils.py

# 验证生成
dir myutils.mpy

# 2. 使用 mpy-tool 生成 C 代码
cd e:\Work\code\study\mp_threadx
python Middlewares\micropython\tools\mpy-tool.py --freeze --qstr-header Middlewares\micropython\genhdr\qstrdefs.preprocessed.h Middlewares\micropython\py_port\frozen_build\myutils.mpy > temp_frozen.c

# 3. 合并到现有的 frozen_mpy.c
# 建议使用 regenerate_micropython_genhdr.py 脚本自动化这个过程
```

---

### 🔸 步骤 3：更新 Keil 项目（自动完成）

如果 `frozen_mpy.c` 已经在 Keil 项目中，它会自动被更新。验证：

1. 打开 Keil 项目
2. 在 Project 窗口找到 `frozen_mpy.c`（通常在 `MicroPython/py_port` 组）
3. 右键 -> Options for File -> 查看路径是否为：
   ```
   ..\Middlewares\micropython\py_port\frozen_mpy.c
   ```

如果不存在，手动添加：
- 右键 `MicroPython/py_port` 组 -> Add Existing Files...
- 选择 `Middlewares\micropython\py_port\frozen_mpy.c`

---

### 🔸 步骤 4：编译 Keil 项目

在 Keil 中：
1. **Project** -> **Rebuild all target files** (F7)
2. 等待编译完成

---

### 🔸 步骤 5：烧录和测试

烧录固件后，在 REPL 中测试：

```python
>>> import myutils
>>> myutils.__version__
'1.0.0'
>>> myutils.greet("STM32")
'Hello, STM32!'
>>> myutils.calculate_checksum("TEST")
233
>>> buf = myutils.DataBuffer(16)
>>> buf.write("Hello")
>>> buf.read()
b'Hello\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
>>> myutils.LED_RED
0
>>> myutils.DEFAULT_CONFIG
{'baud_rate': 115200, 'timeout': 1000, 'buffer_size': 256}
```

---

## 🔄 完整自动化流程

### 创建统一的编译脚本

创建 `tools/freeze_module.py`：

```python
#!/usr/bin/env python3
"""
通用的冻结模块编译脚本
用法: python freeze_module.py <module_name>
"""

import os
import subprocess
import sys

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
MPY_CROSS = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'mpy-cross', 'build', 'mpy-cross.exe')
FROZEN_DIR = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'py_port', 'frozen_build')
REGENERATE_SCRIPT = os.path.join(PROJECT_ROOT, 'tools', 'regenerate_micropython_genhdr.py')

def freeze_module(module_name):
    """冻结指定的模块"""
    
    source_py = os.path.join(FROZEN_DIR, f"{module_name}.py")
    output_mpy = os.path.join(FROZEN_DIR, f"{module_name}.mpy")
    
    print(f"🔥 冻结模块: {module_name}")
    print("=" * 70)
    
    # 检查源文件
    if not os.path.exists(source_py):
        print(f"❌ 错误: 未找到 {source_py}")
        print(f"   请先创建该文件")
        return 1
    
    # 编译
    print(f"\n📦 编译 {module_name}.py -> {module_name}.mpy")
    result = subprocess.run(
        [MPY_CROSS, '-o', output_mpy, '-s', f'{module_name}.py', f'{module_name}.py'],
        cwd=FROZEN_DIR,
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"❌ 编译失败: {result.stderr}")
        return 1
    
    print(f"✅ 生成: {output_mpy}")
    
    # 重新生成 frozen_mpy.c
    print(f"\n🔄 重新生成 frozen_mpy.c...")
    result = subprocess.run(
        [sys.executable, REGENERATE_SCRIPT],
        cwd=PROJECT_ROOT,
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"❌ 生成失败:\n{result.stderr}")
        return 1
    
    print(result.stdout)
    print("\n" + "=" * 70)
    print(f"✅ 模块 '{module_name}' 已冻结到固件中")
    print("=" * 70)
    print("\n下一步:")
    print(f"  1. 在 tools/regenerate_micropython_genhdr.py 的 frozen_allowlist 中添加 '{module_name}.mpy'")
    print(f"  2. 在 Keil 中重新编译项目")
    print(f"  3. 烧录固件")
    print(f"  4. 测试: import {module_name}")
    
    return 0

def main():
    if len(sys.argv) < 2:
        print("用法: python freeze_module.py <module_name>")
        print("\n示例:")
        print("  python freeze_module.py myutils")
        print("  python freeze_module.py sensor_driver")
        return 1
    
    module_name = sys.argv[1]
    return freeze_module(module_name)

if __name__ == '__main__':
    sys.exit(main())
```

**使用方法**：
```powershell
# 冻结任意模块
python tools\freeze_module.py myutils
python tools\freeze_module.py sensor_config
```

---

## 📦 批量冻结多个模块

### 创建模块清单

创建 `Middlewares/micropython/py_port/frozen_build/my_modules_manifest.txt`：

```
# 我的自定义冻结模块列表
myutils
sensor_driver
config_manager
protocol_handler
```

### 批量编译脚本

创建 `tools/freeze_all_custom.py`：

```python
#!/usr/bin/env python3
"""
批量冻结自定义模块
"""

import os
import subprocess
import sys

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
FROZEN_DIR = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'py_port', 'frozen_build')
MANIFEST = os.path.join(FROZEN_DIR, 'my_modules_manifest.txt')
FREEZE_SCRIPT = os.path.join(PROJECT_ROOT, 'tools', 'freeze_module.py')

def main():
    if not os.path.exists(MANIFEST):
        print(f"❌ 未找到清单文件: {MANIFEST}")
        return 1
    
    # 读取模块列表
    with open(MANIFEST, 'r') as f:
        modules = [line.strip() for line in f if line.strip() and not line.startswith('#')]
    
    print(f"📋 找到 {len(modules)} 个模块需要冻结")
    print("=" * 70)
    
    for i, module in enumerate(modules, 1):
        print(f"\n[{i}/{len(modules)}] 处理: {module}")
        result = subprocess.run(
            [sys.executable, FREEZE_SCRIPT, module],
            cwd=PROJECT_ROOT
        )
        if result.returncode != 0:
            print(f"❌ 模块 {module} 冻结失败")
            return 1
    
    print("\n" + "=" * 70)
    print("✅ 所有模块冻结完成！")
    print("=" * 70)
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
```

---

## ⚙️ Keil Pre-Build 集成（高级）

### 在 Keil 中自动化冻结流程

1. 打开 Keil 项目
2. **Project** -> **Options for Target** -> **User** 标签
3. 在 **Before Build/Rebuild** 添加：

```batch
cmd /c "python tools\freeze_all_custom.py"
```

这样每次编译前会自动重新冻结所有模块。

⚠️ **注意**：这会增加编译时间，建议仅在模块有更新时使用。

---

## 🛠️ 常见问题

### Q1: mpy-cross 编译失败

**错误**: `mpy-cross.exe 不是内部或外部命令`

**解决**:
```powershell
# 检查 mpy-cross 是否存在
dir Middlewares\micropython\mpy-cross\build\mpy-cross.exe

# 如果不存在，需要编译 mpy-cross（需要 MinGW 或 WSL）
cd Middlewares\micropython\mpy-cross
make
```

或从官方下载预编译版本。

---

### Q2: 模块未出现在 frozen_mpy.c 中

**原因**: 没有在 `frozen_allowlist` 中添加

**解决**: 编辑 `tools/regenerate_micropython_genhdr.py`：

```python
frozen_allowlist = [
    "zlib.mpy",
    "gzip.mpy",
    "_thread.mpy",
    "ssl.mpy",
    "lcd160cr.mpy",
    "myutils.mpy",      # 👈 确保添加了
]
```

---

### Q3: import 时找不到模块

**检查清单**:
1. ✅ `.mpy` 文件已生成
2. ✅ `frozen_mpy.c` 已更新
3. ✅ Keil 项目已重新编译
4. ✅ 固件已烧录

**调试**:
```python
>>> import sys
>>> sys.modules
# 查看所有已加载模块

>>> import gc
>>> gc.mem_free()
# 检查内存是否充足
```

---

### Q4: 冻结后模块太大，编译失败

**症状**: 
```
Error: L6407E: Sections of aggregate size 0x12345 bytes could not fit into region
```

**解决**:
1. 减少冻结模块数量
2. 优化 Python 代码（删除注释、文档字符串）
3. 增加 Flash 容量配置

---

### Q5: 如何查看冻结了哪些模块？

在 REPL 中：
```python
>>> help('modules')
```

或查看 `frozen_mpy.c` 文件开头的 QSTR 枚举。

---

## 📚 最佳实践

### 1. 模块组织

```
frozen_build/
├── stdlib/          # 标准库替代品
│   ├── zlib.mpy
│   ├── gzip.mpy
│   └── ssl.mpy
├── drivers/         # 硬件驱动
│   ├── sensor.mpy
│   └── lcd.mpy
└── app/             # 应用层
    ├── config.mpy
    └── protocol.mpy
```

### 2. 版本管理

在每个模块中添加版本信息：
```python
__version__ = "1.0.0"
__author__ = "CaiBo"
__date__ = "2026-01-28"
```

### 3. 文档字符串

在开发时保留，发布时可用 `-O` 优化删除：
```powershell
mpy-cross -O2 myutils.py  # 删除文档字符串和断言
```

### 4. 模块大小监控

创建 `tools/check_frozen_size.py`：
```python
import os

FROZEN_DIR = "Middlewares/micropython/py_port/frozen_build"

for f in os.listdir(FROZEN_DIR):
    if f.endswith('.mpy'):
        size = os.path.getsize(os.path.join(FROZEN_DIR, f))
        print(f"{f:20s} {size:8d} bytes")
```

---

## 🎯 快速参考

### 完整工作流程

```powershell
# 1. 创建 Python 模块
notepad Middlewares\micropython\py_port\frozen_build\myutils.py

# 2. 编译并冻结
python tools\freeze_module.py myutils

# 3. 更新允许列表
notepad tools\regenerate_micropython_genhdr.py
# 添加 "myutils.mpy" 到 frozen_allowlist

# 4. 重新生成
python tools\regenerate_micropython_genhdr.py

# 5. Keil 编译
# Project -> Rebuild

# 6. 烧录测试
# 烧录固件后在 REPL 中: import myutils
```

---

## 📖 相关文件

- 配置文件：[mpconfigport.h](Middlewares/micropython/py_port/mpconfigport.h)
- 冻结模块目录：[frozen_build/](Middlewares/micropython/py_port/frozen_build/)
- 生成的 C 文件：[frozen_mpy.c](Middlewares/micropython/py_port/frozen_mpy.c)
- 自动化脚本：[regenerate_micropython_genhdr.py](tools/regenerate_micropython_genhdr.py)
- 示例脚本：[compile_lcd160cr.py](tools/compile_lcd160cr.py)

---

**创建日期**: 2026-01-28  
**项目**: mp_threadx  
**平台**: STM32F405 + MDK-ARM + ThreadX
