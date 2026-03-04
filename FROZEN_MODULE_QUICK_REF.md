# 🚀 冻结 Python 模块快速参考

## 一分钟快速开始

```powershell
# 1. 创建模块
notepad Middlewares\micropython\py_port\frozen_build\mymodule.py

# 2. 编译冻结
python tools\freeze_module.py mymodule

# 3. 添加到允许列表（编辑 tools/regenerate_micropython_genhdr.py）
# frozen_allowlist = [..., "mymodule.mpy"]

# 4. 重新生成
python tools\regenerate_micropython_genhdr.py

# 5. Keil 编译
# Project -> Rebuild (F7)

# 6. 烧录测试
# >>> import mymodule
```

---

## 项目已有工具 ✅

| 工具 | 路径 | 说明 |
|------|------|------|
| **编译脚本** | `tools/freeze_module.py` | 自动化编译单个模块 |
| **重新生成** | `tools/regenerate_micropython_genhdr.py` | 生成 frozen_mpy.c |
| **示例模块** | `Middlewares/.../frozen_build/myutils.py` | 完整示例 |
| **mpy-cross** | `Middlewares/.../mpy-cross/build/mpy-cross.exe` | 编译器 |

---

## 工具使用

### freeze_module.py

```powershell
# 编译指定模块
python tools\freeze_module.py myutils

# 列出所有模块
python tools\freeze_module.py --list

# 显示帮助
python tools\freeze_module.py --help
```

### 查看当前已冻结模块

```powershell
# 查看 frozen_build 目录
dir Middlewares\micropython\py_port\frozen_build\*.mpy

# 输出示例:
# zlib.mpy
# gzip.mpy
# ssl.mpy
# _thread.mpy
# lcd160cr.mpy
# myutils.mpy  ← 你的模块
```

---

## 示例模块结构

```python
"""模块文档字符串"""

__version__ = "1.0.0"

# 常量
LED_PIN = 13

# 函数
def hello():
    return "Hello"

# 类
class MyClass:
    def __init__(self):
        pass
```

---

## 常见问题速查

| 问题 | 解决方案 |
|------|---------|
| `import mymodule` 找不到 | 1. 检查是否在 frozen_allowlist 中<br>2. 确认 Keil 已重新编译<br>3. 确认固件已烧录 |
| mpy-cross 未找到 | 检查路径或下载预编译版本 |
| 编译失败 | 检查 Python 语法错误 |
| 模块太大 | 使用 `-O2` 优化编译 |

---

## 目录结构

```
mp_threadx/
├── tools/
│   ├── freeze_module.py              ← 编译工具
│   └── regenerate_micropython_genhdr.py  ← 重新生成工具
└── Middlewares/micropython/
    ├── mpy-cross/build/
    │   └── mpy-cross.exe             ← 编译器
    └── py_port/
        ├── frozen_build/             ← 模块源码目录
        │   ├── myutils.py            ← 你的模块（示例）
        │   ├── myutils.mpy           ← 编译后
        │   ├── zlib.mpy
        │   └── ...
        └── frozen_mpy.c              ← 生成的 C 文件（在 Keil 中编译）
```

---

## 完整文档

- 📖 [完整指南](FROZEN_MODULE_KEIL_GUIDE.md) - MDK-ARM 详细步骤
- 📖 [扩展方法总览](MICROPYTHON_EXTENSION_GUIDE.md) - 所有扩展方法对比
- 💻 [示例模块](Middlewares/micropython/py_port/frozen_build/myutils.py) - 完整代码示例

---

**创建日期**: 2026-01-28  
**项目**: mp_threadx  
**平台**: STM32F405 + Keil MDK
