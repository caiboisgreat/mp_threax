# MicroPython 官方冻结模块工作流程完整指南

本文档详细介绍 MicroPython 官方的 **manifest.py** 方式冻结模块的完整流程。

---

## 📋 目录

1. [官方工作流程概述](#官方工作流程概述)
2. [核心工具介绍](#核心工具介绍)
3. [manifest.py 语法详解](#manifestpy-语法详解)
4. [完整实现步骤](#完整实现步骤)
5. [与当前项目的对比](#与当前项目的对比)
6. [迁移到官方方式](#迁移到官方方式)

---

## 🎯 官方工作流程概述

### 标准流程图

```
┌─────────────────────┐
│  创建 manifest.py   │  定义要冻结的模块
│  (描述文件)         │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  makemanifest.py    │  解析 manifest，编译 .py → .mpy
│  (官方脚本)         │
└──────────┬──────────┘
           │
           ├─→ 调用 mpy-cross 编译 Python 文件
           │
           ▼
┌─────────────────────┐
│  frozen_mpy/*.mpy   │  临时构建目录
│  (中间产物)         │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  mpy-tool.py        │  将 .mpy 文件打包为 C 代码
│  --freeze           │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  frozen_mpy.c       │  最终的 C 文件（在 Keil 中编译）
│  (输出)             │
└─────────────────────┘
```

---

## 🛠️ 核心工具介绍

### 1. manifestfile.py ⭐ 核心引擎

**作用**: 
- 提供 `manifest.py` 中可用的 API 函数（freeze、include 等）
- 解析和执行 `manifest.py` 文件
- 管理要冻结的文件列表
- 处理路径变量替换（如 `$(MPY_DIR)`）

**调用关系**:
```
makemanifest.py
    ↓ import manifestfile
    ↓ 创建 ManifestFile 对象
    ↓ manifest.execute("manifest.py")  
    ↓ 执行 manifest.py 中的代码
    ↓ manifest.py 调用 freeze()、include() 等
    ↓ manifestfile 记录所有文件信息
    ↓ manifest.files() 返回文件列表
    ↓ makemanifest 遍历并编译这些文件
```

**核心 API 函数**:
```python
# 冻结单个 Python 文件
freeze(path, script, opt=0)
# 实际调用：manifestfile.ManifestFile.freeze()

# 包含另一个 manifest 文件
include(manifest_path, **kwargs)
# 实际调用：manifestfile.ManifestFile.include()

# 引入外部包（从 micropython-lib）
require(name, **kwargs)
# 实际调用：manifestfile.ManifestFile.require()

# 定义包元数据
metadata(
    version="1.0.0",
    description="My package",
    license="MIT",
    author="Your Name"
)

# 冻结整个模块文件
module(name, base_path=".", opt=0)

# 冻结整个包目录（带 __init__.py）
package(package_dir, files=None, base_path=".", opt=0)
```

**工作原理**:

1. **创建执行环境**:
   ```python
   # makemanifest.py 中
   manifest = manifestfile.ManifestFile(manifestfile.MODE_FREEZE, VARS)
   ```

2. **执行 manifest.py**:
   ```python
   # 读取并执行 manifest.py 文件
   manifest.execute("manifest.py")
   # 内部会：
   # 1. 读取 manifest.py 内容
   # 2. 设置全局函数（freeze、include 等）
   # 3. 执行 exec(manifest_content, globals)
   ```

3. **收集文件列表**:
   ```python
   # manifest.py 中每次调用 freeze() 时
   # manifestfile 会将文件信息保存到内部列表
   for result in manifest.files():
       # 处理每个要冻结的文件
       if result.kind == KIND_FREEZE_AS_MPY:
           # 编译 .py -> .mpy
   ```

### 2. makemanifest.py

**作用**: 主执行脚本，解析 manifest 并生成冻结代码

**命令行语法**:
```bash
python makemanifest.py \
    --output frozen_mpy.c \               # 输出文件
    --build-dir build \                    # 构建目录
    --mpy-cross-flags "-march=armv7m" \   # mpy-cross 参数
    --var MPY_DIR=/path/to/micropython \  # 变量替换
    --var PORT_DIR=/path/to/port \
    manifest.py                            # 输入的 manifest 文件
```

### 3. mpy-cross

**作用**: Python 到 .mpy 字节码编译器

**用法**:
```bash
mpy-cross module.py -o module.mpy -march=armv7m
```

### 4. mpy-tool.py

**作用**: 将 .mpy 文件打包为 C 代码

**用法**:
```bash
python mpy-tool.py \
    -f \                                  # freeze 模式
    -q qstrdefs.preprocessed.h \          # QSTR 头文件
    module1.mpy module2.mpy > frozen.c    # 输入文件
```

---

## 📝 manifest.py 语法详解

### 基本结构

```python
# manifest.py - 冻结模块描述文件

# 1. 定义包元数据（可选，但推荐）
metadata(
    version="1.0.0",
    description="My frozen modules",
    author="CaiBo"
)

# 2. 冻结单个 Python 文件
# freeze(base_path, script_name, opt=optimization_level)
freeze(".", "mymodule.py")

# 3. 冻结整个目录
freeze("libs", ["utils.py", "config.py"])

# 4. 冻结包（带 __init__.py 的目录）
package("mypackage")

# 5. 包含其他 manifest
include("$(MPY_DIR)/lib/micropython-lib/manifest.py")

# 6. 引入外部库
require("aiohttp")
```

### 详细示例

```python
# ========================================
# 示例 1: 简单的单文件冻结
# ========================================
metadata(version="1.0.0")
freeze(".", "myutils.py")

# ========================================
# 示例 2: 冻结多个文件
# ========================================
freeze("modules", [
    "config.py",
    "helpers.py",
    "protocol.py"
])

# ========================================
# 示例 3: 冻结包结构
# ========================================
# 目录结构:
#   mypackage/
#   ├── __init__.py
#   ├── core.py
#   └── utils.py
package("mypackage")

# ========================================
# 示例 4: 使用优化级别
# ========================================
freeze(".", "production.py", opt=2)  # -O2 优化

# ========================================
# 示例 5: 条件冻结
# ========================================
if options.ENABLE_NETWORKING:
    freeze(".", "network_utils.py")

# ========================================
# 示例 6: 包含标准库
# ========================================
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")

# ========================================
# 示例 7: 冻结子目录
# ========================================
freeze("drivers", [
    "sensor.py",
    "lcd.py",
    "led.py"
])

# ========================================
# 示例 8: 使用变量
# ========================================
freeze("$(PORT_DIR)/modules", "board_config.py")
```

### 高级用法

```python
# ========================================
# 使用 module() 函数
# ========================================
# 冻结单个模块（不包含子包）
module("bluetooth/ble_advertising.py")

# ========================================
# 递归冻结整个目录树
# ========================================
freeze("libs", glob="**/*.py")

# ========================================
# 排除特定文件
# ========================================
package("mypackage", exclude=["test_*.py"])
```

---

## 🚀 完整实现步骤

### 方法一：标准官方流程（推荐用于新项目）

#### 步骤 1: 创建目录结构

```
my_port/
├── manifest.py          # 主 manifest 文件
├── modules/             # 自定义模块目录
│   ├── myutils.py
│   └── config.py
├── build/               # 构建输出目录
│   └── frozen_mpy/      # .mpy 临时文件
└── Makefile            # 或其他构建系统
```

#### 步骤 2: 创建 manifest.py

`manifest.py`:
```python
"""
主 manifest 文件 - 定义所有要冻结的模块
"""

# 包元数据
metadata(
    version="1.0.0",
    description="STM32F405 MicroPython Port",
    author="CaiBo"
)

# 1. 冻结自定义模块
freeze("modules", [
    "myutils.py",
    "config.py",
])

# 2. 包含标准库的 manifest
# 注意：使用 $(MPY_DIR) 变量
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/zlib/manifest.py")

# 3. 包含第三方库
include("$(MPY_DIR)/lib/lcd160cr/manifest.py")

# 4. 条件编译（可选）
# if options.ENABLE_NETWORK:
#     freeze("modules", "network_driver.py")
```

#### 步骤 3: 运行 makemanifest.py

**方法 A: 手动命令行**

```bash
# 设置变量
export MPY_DIR=/path/to/micropython
export PORT_DIR=/path/to/your_port
export BUILD_DIR=/path/to/build

# 运行 makemanifest
python $MPY_DIR/tools/makemanifest.py \
    --output $BUILD_DIR/frozen_mpy.c \
    --build-dir $BUILD_DIR \
    --mpy-cross-flags "-march=armv7m" \
    --var MPY_DIR=$MPY_DIR \
    --var PORT_DIR=$PORT_DIR \
    manifest.py
```

**方法 B: Makefile 集成**

`Makefile`:
```makefile
MPY_DIR = ../Middlewares/micropython
PORT_DIR = .
BUILD_DIR = build

FROZEN_MANIFEST ?= manifest.py

# 调用 makemanifest
$(BUILD_DIR)/frozen_mpy.c: $(FROZEN_MANIFEST)
	$(Q)$(PYTHON) $(MPY_DIR)/tools/makemanifest.py \
		--output $@ \
		--build-dir $(BUILD_DIR) \
		--mpy-cross-flags "$(MPY_CROSS_FLAGS)" \
		--var MPY_DIR=$(MPY_DIR) \
		--var PORT_DIR=$(PORT_DIR) \
		$(FROZEN_MANIFEST)

# 包含到主构建
all: $(BUILD_DIR)/frozen_mpy.c
	# 编译固件...
```

#### 步骤 4: 在 Keil 中集成（手动）

**Pre-Build 事件**:

在 Keil 项目的 `Options for Target` → `User` → `Before Build/Rebuild` 添加：

```batch
python %MPY_DIR%\tools\makemanifest.py ^
    --output frozen_mpy.c ^
    --build-dir build ^
    --mpy-cross-flags "-march=armv7m" ^
    --var MPY_DIR=%MPY_DIR% ^
    --var PORT_DIR=%PORT_DIR% ^
    manifest.py
```

---

### 方法二：在你的项目中使用官方工具

#### 创建适配脚本

创建 `tools/freeze_official.py`:

```python
#!/usr/bin/env python3
"""
使用官方 makemanifest.py 的包装脚本
适配到当前项目结构
"""

import sys
import os
import subprocess
from pathlib import Path

# 项目路径
PROJECT_ROOT = Path(__file__).parent.parent.absolute()
MPY_DIR = PROJECT_ROOT / "Middlewares" / "micropython"
PORT_DIR = PROJECT_ROOT / "Middlewares" / "micropython" / "py_port"
BUILD_DIR = PROJECT_ROOT / "build"
MANIFEST = PROJECT_ROOT / "manifest.py"

# 工具路径
MAKEMANIFEST = MPY_DIR / "tools" / "makemanifest.py"
OUTPUT = PORT_DIR / "frozen_mpy.c"

def main():
    print("=" * 80)
    print("使用官方 makemanifest.py 生成冻结模块")
    print("=" * 80)
    
    # 检查工具
    if not MAKEMANIFEST.exists():
        print(f"❌ makemanifest.py 未找到: {MAKEMANIFEST}")
        return 1
    
    if not MANIFEST.exists():
        print(f"❌ manifest.py 未找到: {MANIFEST}")
        print(f"   请先创建 manifest.py 文件")
        return 1
    
    # 创建构建目录
    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "frozen_mpy").mkdir(exist_ok=True)
    
    # 运行 makemanifest
    cmd = [
        sys.executable,
        str(MAKEMANIFEST),
        "--output", str(OUTPUT),
        "--build-dir", str(BUILD_DIR),
        "--mpy-cross-flags", "-march=armv7m",
        "--var", f"MPY_DIR={MPY_DIR}",
        "--var", f"PORT_DIR={PORT_DIR}",
        str(MANIFEST)
    ]
    
    print(f"\n📝 运行命令:")
    print(f"   {' '.join(cmd)}\n")
    
    try:
        result = subprocess.run(
            cmd,
            cwd=str(PROJECT_ROOT),
            capture_output=True,
            text=True
        )
        
        # 显示输出
        if result.stdout:
            print(result.stdout)
        
        if result.returncode != 0:
            print(f"❌ 失败!")
            if result.stderr:
                print(result.stderr)
            return 1
        
        print("\n" + "=" * 80)
        print(f"✅ 成功生成: {OUTPUT}")
        print("=" * 80)
        print("\n下一步:")
        print("   1. 在 Keil 中重新编译项目")
        print("   2. 烧录固件")
        print("   3. 测试模块导入")
        
        return 0
        
    except Exception as e:
        print(f"❌ 异常: {e}")
        return 1

if __name__ == '__main__':
    sys.exit(main())
```

---

## 🔄 与当前项目的对比

### 当前项目方式 vs 官方方式

| 方面 | 当前项目方式 | 官方方式 |
|------|-------------|---------|
| **配置方式** | `frozen_allowlist` 列表 | `manifest.py` 文件 |
| **编译脚本** | 自定义 `regenerate_micropython_genhdr.py` | 官方 `makemanifest.py` |
| **灵活性** | 低（需手动维护列表） | 高（声明式配置） |
| **包管理** | 不支持 | 支持（require, include） |
| **条件编译** | 不支持 | 支持 |
| **标准库集成** | 手动添加 | 一行 include |
| **可维护性** | 中 | 高 |

### 当前项目的工作流程

```python
# tools/regenerate_micropython_genhdr.py

frozen_allowlist = [
    "zlib.mpy",
    "gzip.mpy",
    "_thread.mpy",
    "ssl.mpy",
    "lcd160cr.mpy",
    "myutils.mpy",  # 手动添加
]

# 手动调用 mpy-tool.py
```

### 官方推荐的工作流程

```python
# manifest.py

metadata(version="1.0.0")

# 自动处理依赖
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")

# 自动编译和冻结
freeze("modules", "myutils.py")
```

---

## 🎯 迁移到官方方式

### 步骤 1: 创建 manifest.py

在项目根目录创建 `manifest.py`:

```python
"""
mp_threadx 项目的 manifest 文件
"""

metadata(
    version="1.0.0",
    description="STM32F405 + ThreadX MicroPython Port",
    author="CaiBo"
)

# ========================================
# 1. 标准库模块
# ========================================
# 这些是之前在 frozen_allowlist 中的模块

# SSL/TLS 支持
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")

# 压缩支持
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/zlib", "zlib.py")
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/gzip", "gzip.py")

# 线程支持
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/_thread", "_thread.py")

# LCD 驱动
include("$(MPY_DIR)/lib/lcd160cr/manifest.py")

# ========================================
# 2. 自定义模块
# ========================================
# 之前在 frozen_build 目录的自定义模块

freeze("$(PORT_DIR)/frozen_build", [
    "myutils.py",
    # 添加更多自定义模块...
])

# ========================================
# 3. 驱动和库（如果有）
# ========================================
# freeze("$(PORT_DIR)/drivers", [
#     "sensor.py",
#     "lcd.py",
# ])
```

### 步骤 2: 创建包装脚本

使用上面的 `tools/freeze_official.py`

### 步骤 3: 测试

```bash
# 运行官方工作流程
python tools/freeze_official.py

# 检查输出
dir Middlewares\micropython\py_port\frozen_mpy.c
```

### 步骤 4: 更新构建流程

**选项 A**: 替换现有脚本
```bash
# 用官方方式替代
python tools/freeze_official.py  # 代替 regenerate_micropython_genhdr.py
```

**选项 B**: 保留两种方式
```bash
# 兼容模式：保留现有方式，添加官方方式
python tools/regenerate_micropython_genhdr.py  # 现有方式
# 或
python tools/freeze_official.py                 # 官方方式
```

---

## 📊 实际示例对比

### 示例：添加新的冻结模块

#### 当前方式

```bash
# 1. 创建模块
notepad frozen_build/sensor.py

# 2. 编译
mpy-cross sensor.py

# 3. 手动编辑 regenerate_micropython_genhdr.py
# frozen_allowlist = [..., "sensor.mpy"]

# 4. 重新生成
python regenerate_micropython_genhdr.py
```

#### 官方方式

```bash
# 1. 创建模块
notepad modules/sensor.py

# 2. 编辑 manifest.py，添加一行
# freeze("modules", "sensor.py")

# 3. 运行一个命令
python freeze_official.py
```

---

## 🎓 最佳实践

### 1. 项目结构

```
my_project/
├── manifest.py              # 主 manifest
├── modules/                 # 自定义模块
│   ├── manifest.py          # 可选：模块子 manifest
│   ├── myutils.py
│   └── config.py
├── build/
│   └── frozen_mpy/          # 临时 .mpy 文件
└── tools/
    └── freeze_official.py   # 包装脚本
```

### 2. 模块化 manifest

`manifest.py`:
```python
# 主 manifest
metadata(version="1.0.0")

# 包含子 manifest
include("modules/manifest.py")
include("drivers/manifest.py")
```

`modules/manifest.py`:
```python
# 子 manifest - 只管理本目录的模块
freeze(".", [
    "myutils.py",
    "config.py",
])
```

### 3. 使用变量

```python
# 支持不同平台
if options.BOARD == "STM32F405":
    freeze("boards/stm32f405", "board_config.py")
elif options.BOARD == "ESP32":
    freeze("boards/esp32", "board_config.py")
```

---

## 📚 参考资源

### 官方文档
- [MicroPython Manifest Files](https://docs.micropython.org/en/latest/reference/manifest.html)
- [makemanifest.py 源码](Middlewares/micropython/tools/makemanifest.py)
- [manifestfile.py 源码](Middlewares/micropython/tools/manifestfile.py)

### 示例 Manifest
- [lcd160cr manifest](Middlewares/micropython/lib/lcd160cr/manifest.py)
- 官方 ports 中的 manifest.py（如果有的话）

### 相关工具
- [mpy-cross](Middlewares/micropython/mpy-cross/)
- [mpy-tool.py](Middlewares/micropython/tools/mpy-tool.py)

---

## 🔧 故障排查

### 问题 1: makemanifest.py 找不到 MPY_DIR

**解决**:
```bash
# 确保传递了正确的变量
--var MPY_DIR=/absolute/path/to/micropython
--var PORT_DIR=/absolute/path/to/port
```

### 问题 2: mpy-cross 未找到

**解决**:
```bash
# 检查 mpy-cross 是否存在
dir Middlewares\micropython\mpy-cross\build\mpy-cross.exe

# 或设置环境变量
set MICROPY_MPYCROSS=C:\path\to\mpy-cross.exe
```

### 问题 3: 找不到模块

**解决**:
```python
# 在 manifest.py 中使用绝对路径
freeze("$(PORT_DIR)/modules", "myutils.py")

# 或使用相对路径（相对于 manifest.py）
freeze("modules", "myutils.py")
```

---

## ✅ 总结

### 官方方式的优势

1. ✅ **标准化** - 遵循 MicroPython 官方规范
2. ✅ **灵活性** - 声明式配置，易于维护
3. ✅ **可扩展** - 支持条件编译、包管理
4. ✅ **自动化** - 自动处理依赖和编译
5. ✅ **可移植** - 更容易移植到其他平台

### 建议

- **新项目**: 直接使用官方 manifest.py 方式
- **现有项目**: 可以逐步迁移，或保持现有方式
- **大型项目**: 使用模块化 manifest 结构

---

**创建日期**: 2026-01-28  
**适用版本**: MicroPython 1.20+  
**项目**: mp_threadx
