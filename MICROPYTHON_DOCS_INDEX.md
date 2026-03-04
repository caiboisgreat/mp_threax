# 📚 MicroPython 扩展开发文档索引

本项目包含了完整的 MicroPython 组件扩展文档和工具。

---

## 🎯 快速导航

### 新手入门

1. **[扩展方法总览](MICROPYTHON_EXTENSION_GUIDE.md)** ⭐
   - 5 种扩展方法完整对比
   - 每种方法的详细示例
   - 选择建议和最佳实践

### 冻结 Python 模块（方法三）

2. **[MDK-ARM 冻结模块完整指南](FROZEN_MODULE_KEIL_GUIDE.md)** 📘
   - 针对 Keil MDK-ARM 的详细步骤
   - 自动化工具使用说明
   - 完整的示例流程

3. **[官方冻结工作流程指南](OFFICIAL_FREEZE_WORKFLOW_GUIDE.md)** ⭐ 官方标准
   - MicroPython 官方 manifest.py 方式
   - makemanifest.py 完整说明
   - 官方工具链详解
   - 与当前项目的对比

4. **[快速参考卡](FROZEN_MODULE_QUICK_REF.md)** 🚀
   - 一分钟快速开始
   - 常用命令速查
   - 故障排查清单

5. **[就绪清单](FROZEN_MODULE_READY.md)** ✅
   - 已完成工作总结
   - 接下来要做的步骤
   - 验证清单

---

## 🛠️ 工具和示例

### 自动化脚本

| 脚本 | 功能 | 位置 |
|------|------|------|
| **freeze_module.py** | 编译单个冻结模块（自定义） | [tools/freeze_module.py](tools/freeze_module.py) |
| **freeze_official.py** | 使用官方工具冻结（推荐） | [tools/freeze_official.py](tools/freeze_official.py) |
| **regenerate_micropython_genhdr.py** | 重新生成所有头文件 | [tools/regenerate_micropython_genhdr.py](tools/regenerate_micropython_genhdr.py) |

### 配置文件

| 文件 | 说明 | 位置 |
|------|------|------|
| **manifest.py** | 官方冻结模块配置（推荐） | [manifest.py](manifest.py) |

### 示例模块

| 模块 | 说明 | 位置 |
|------|------|------|
| **myutils** | 完整的工具模块示例 | [frozen_build/myutils.py](Middlewares/micropython/py_port/frozen_build/myutils.py) |
| **subsystem** | C 模块扩展示例 | [extmod/modsubsystem.c](Middlewares/micropython/extmod/modsubsystem.c) |

---

## 📖 按扩展方法分类

### 方法一：C 模块扩展（extmod）

- **文档**: [MICROPYTHON_EXTENSION_GUIDE.md - 方法一](MICROPYTHON_EXTENSION_GUIDE.md#方法一c-模块扩展extmod)
- **示例**: [modsubsystem.c](Middlewares/micropython/extmod/modsubsystem.c)
- **适用**: 核心功能、硬件驱动

### 方法二：用户 C 模块

- **文档**: [MICROPYTHON_EXTENSION_GUIDE.md - 方法二](MICROPYTHON_EXTENSION_GUIDE.md#方法二用户-c-模块user-c-module)
- **适用**: 第三方库、可移植模块

### 方法三：冻结 Python 模块 ⭐ 重点

- **完整指南**: [FROZEN_MODULE_KEIL_GUIDE.md](FROZEN_MODULE_KEIL_GUIDE.md)
- **官方工作流程**: [OFFICIAL_FREEZE_WORKFLOW_GUIDE.md](OFFICIAL_FREEZE_WORKFLOW_GUIDE.md) ⭐ 官方标准
- **快速参考**: [FROZEN_MODULE_QUICK_REF.md](FROZEN_MODULE_QUICK_REF.md)
- **就绪清单**: [FROZEN_MODULE_READY.md](FROZEN_MODULE_READY.md)
- **示例**: [myutils.py](Middlewares/micropython/py_port/frozen_build/myutils.py)
- **配置**: [manifest.py](manifest.py)
- **适用**: 业务逻辑、快速开发

### 方法四：动态原生模块

- **文档**: [MICROPYTHON_EXTENSION_GUIDE.md - 方法四](MICROPYTHON_EXTENSION_GUIDE.md#方法四动态原生模块)
- **适用**: 需要热更新的功能

### 方法五：移植层扩展

- **文档**: [MICROPYTHON_EXTENSION_GUIDE.md - 方法五](MICROPYTHON_EXTENSION_GUIDE.md#方法五移植层扩展portspecific)
- **适用**: STM32 特定功能

---

## 🚀 快速开始

### 添加冻结 Python 模块（推荐）

```powershell
# 1. 创建模块
notepad Middlewares\micropython\py_port\frozen_build\my_module.py

# 2. 编译
python tools\freeze_module.py my_module

# 3. 添加到允许列表（如果需要）
notepad tools\regenerate_micropython_genhdr.py

# 4. 重新生成
python tools\regenerate_micropython_genhdr.py

# 5. Keil 编译 → 烧录 → 测试
```

详细步骤见：[FROZEN_MODULE_QUICK_REF.md](FROZEN_MODULE_QUICK_REF.md)

### 添加 C 模块扩展

1. 在 `Middlewares/micropython/extmod/` 创建 `modxxx.c`
2. 在 `mpconfigport.h` 启用：`#define MICROPY_PY_XXX (1)`
3. 在 Keil 项目中添加该文件
4. 编译 → 烧录 → 测试

详细步骤见：[MICROPYTHON_EXTENSION_GUIDE.md](MICROPYTHON_EXTENSION_GUIDE.md#方法一c-模块扩展extmod)

---

## 📂 项目结构

```
mp_threadx/
├── 📚 文档
│   ├── MICROPYTHON_EXTENSION_GUIDE.md    ← 所有扩展方法总览
│   ├── FROZEN_MODULE_KEIL_GUIDE.md       ← MDK-ARM 冻结模块完整指南
│   ├── FROZEN_MODULE_QUICK_REF.md        ← 快速参考卡
│   └── FROZEN_MODULE_READY.md            ← 就绪清单
│
├── 🛠️ 工具
│   └── tools/
│       ├── freeze_module.py                  ← 编译冻结模块
│       └── regenerate_micropython_genhdr.py  ← 重新生成头文件
│
├── 📦 MicroPython
│   └── Middlewares/micropython/
│       ├── extmod/
│       │   └── modsubsystem.c            ← C 模块示例
│       ├── py_port/
│       │   ├── frozen_build/             ← 冻结模块源码
│       │   │   └── myutils.py            ← Python 模块示例
│       │   └── frozen_mpy.c              ← 生成的冻结代码
│       └── mpy-cross/
│           └── build/
│               └── mpy-cross.exe         ← Python 到 .mpy 编译器
│
└── 🔧 Keil 项目
    └── MDK-ARM/
        └── mp_threadx.uvprojx
```

---

## 💡 使用建议

### 选择扩展方法

| 场景 | 推荐方法 | 原因 |
|------|----------|------|
| 硬件驱动 (GPIO, I2C) | 方法五（移植层） | 直接访问 HAL，性能最优 |
| 业务逻辑 | 方法三（冻结 Python） | 开发快速，易维护 |
| 算法库 | 方法一/二（C 模块） | 性能好，可复用 |
| 需要热更新 | 方法四（动态原生） | 无需刷固件 |
| 快速原型 | 不冻结的 Python | 实时修改测试 |

---

## ✅ 已完成的配置

你的项目已经配置好：

- ✅ 冻结模块基础设施（`MICROPY_MODULE_FROZEN_MPY`）
- ✅ 5 个标准库冻结模块（zlib, gzip, ssl, _thread, lcd160cr）
- ✅ 1 个自定义模块示例（myutils）
- ✅ 自动化编译脚本
- ✅ 完整文档

**下一步**：在 Keil 中编译 → 烧录 → 测试！

---

## 🔍 常见操作

### 查看当前冻结模块

```powershell
python tools\freeze_module.py --list
```

### 测试冻结模块

```python
>>> import myutils
>>> myutils.self_test()
```

### 添加新的冻结模块

```powershell
python tools\freeze_module.py my_new_module
```

### 查看所有可用模块

```python
>>> help('modules')
```

---

## 📞 需要帮助？

1. 查看对应文档的"常见问题"章节
2. 查看示例代码
3. 运行 `python tools\freeze_module.py --help`

---

## 📋 文档版本

- **创建日期**: 2026-01-28
- **项目**: mp_threadx
- **平台**: STM32F405 + Keil MDK + ThreadX
- **MicroPython**: v1.20+

---

## 🎓 学习路径

### 初学者

1. 阅读 [扩展方法总览](MICROPYTHON_EXTENSION_GUIDE.md)
2. 尝试 [冻结 Python 模块](FROZEN_MODULE_QUICK_REF.md)
3. 查看 [myutils.py](Middlewares/micropython/py_port/frozen_build/myutils.py) 示例

### 进阶

1. 学习 [C 模块扩展](MICROPYTHON_EXTENSION_GUIDE.md#方法一c-模块扩展extmod)
2. 查看 [modsubsystem.c](Middlewares/micropython/extmod/modsubsystem.c)
3. 实现自定义硬件驱动

### 高级

1. 研究移植层扩展
2. 优化性能（原生代码、viper）
3. 集成第三方库

---

**祝你使用愉快！🚀**
