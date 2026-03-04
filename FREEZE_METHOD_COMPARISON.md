# 🔄 冻结模块方式对比：官方 vs 当前项目

## 快速对比表

| 特性 | 当前项目方式 | 官方 manifest.py 方式 |
|------|-------------|----------------------|
| **配置文件** | `regenerate_micropython_genhdr.py` | `manifest.py` ⭐ |
| **配置方式** | Python 列表 `frozen_allowlist` | 声明式 API |
| **主工具** | 自定义脚本 | 官方 `makemanifest.py` |
| **灵活性** | 低 | 高 ⭐ |
| **条件编译** | ❌ 不支持 | ✅ 支持 |
| **依赖管理** | ❌ 手动 | ✅ 自动 |
| **标准库集成** | ❌ 手动添加 | ✅ 一行 include |
| **学习曲线** | 低 | 中 |
| **官方支持** | ❌ 自定义 | ✅ 官方标准 ⭐ |
| **可维护性** | 中 | 高 ⭐ |

---

## 实际示例对比

### 示例：添加新模块 `sensor.py`

#### 当前方式

```bash
# 1. 创建模块
notepad frozen_build\sensor.py

# 2. 手动编译
cd frozen_build
..\..\mpy-cross\build\mpy-cross.exe sensor.py

# 3. 编辑 Python 列表
notepad tools\regenerate_micropython_genhdr.py
# 找到 frozen_allowlist，添加 "sensor.mpy"

# 4. 重新生成
python tools\regenerate_micropython_genhdr.py

# 5. Keil 编译
```

#### 官方方式 ⭐

```bash
# 1. 创建模块
notepad frozen_build\sensor.py

# 2. 编辑配置文件（声明式）
notepad manifest.py
# 添加一行: freeze("$(PORT_DIR)/frozen_build", "sensor.py")

# 3. 一键生成
python tools\freeze_official.py

# 4. Keil 编译
```

**节省步骤**: 2个 → 官方方式更简洁

---

## 代码对比

### 当前项目方式

**配置文件**: `tools/regenerate_micropython_genhdr.py`

```python
# 手动维护的列表
frozen_allowlist = [
    "zlib.mpy",
    "gzip.mpy",
    "_thread.mpy",
    "ssl.mpy",
    "lcd160cr.mpy",
    "myutils.mpy",
    "sensor.mpy",  # 每次手动添加
]

# 手动遍历和检查
mpy_files: list[Path] = []
for name in frozen_allowlist:
    p = frozen_build_dir / name
    if not p.exists():
        raise RuntimeError(f"Missing frozen module: {p}")
    mpy_files.append(p)

# 手动调用 mpy-tool
frozen_c = run([...], mpy_files)
```

### 官方方式 ⭐

**配置文件**: `manifest.py`

```python
# 声明式配置
metadata(version="1.0.0")

# 自动处理依赖
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")

# 简单声明
freeze("$(PORT_DIR)/frozen_build", [
    "myutils.py",
    "sensor.py",  # 添加即可
])

# 条件编译（当前方式不支持）
if options.ENABLE_SENSOR:
    freeze("$(PORT_DIR)/frozen_build", "sensor.py")
```

**优势**:
- ✅ 更清晰、更简洁
- ✅ 自动处理编译
- ✅ 支持高级功能

---

## 工具对比

### 当前项目工具链

```
你的脚本:
  freeze_module.py (自定义)
      ↓
  regenerate_micropython_genhdr.py (自定义)
      ↓
  手动调用 mpy-cross
      ↓
  手动调用 mpy-tool.py
      ↓
  frozen_mpy.c
```

### 官方工具链 ⭐

```
官方标准:
  manifest.py (配置)
      ↓
  makemanifest.py (官方)
      ↓ 自动调用
  mpy-cross (自动)
      ↓ 自动调用
  mpy-tool.py (自动)
      ↓
  frozen_mpy.c
```

**优势**: 自动化程度更高，减少手动干预

---

## 功能对比

### 1. 标准库集成

#### 当前方式
```python
# 需要手动找到 .mpy 文件并添加
frozen_allowlist = [
    "ssl.mpy",    # 从哪里来？怎么编译的？
    "zlib.mpy",   # 需要手动维护
]
```

#### 官方方式 ⭐
```python
# 一行搞定，自动处理依赖
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")
```

### 2. 条件编译

#### 当前方式
```python
# ❌ 不支持
# 所有模块都会被冻结，无法根据配置选择
```

#### 官方方式 ⭐
```python
# ✅ 完全支持
if options.BOARD == "STM32F405":
    freeze("boards/stm32f405", "board_config.py")

if options.ENABLE_NETWORKING:
    freeze("modules", "network_utils.py")
```

### 3. 优化级别

#### 当前方式
```python
# ❌ 统一优化，无法细化
mpy_cross.exe module.py
```

#### 官方方式 ⭐
```python
# ✅ 可以为每个模块指定
freeze("modules", "debug.py", opt=0)      # 保留所有信息
freeze("modules", "production.py", opt=2)  # 最大优化
```

### 4. 包管理

#### 当前方式
```python
# ❌ 手动处理每个文件
frozen_allowlist = [
    "mypackage/__init__.mpy",
    "mypackage/core.mpy",
    "mypackage/utils.mpy",
]
```

#### 官方方式 ⭐
```python
# ✅ 一行搞定整个包
package("mypackage")
```

---

## 使用建议

### 🟢 继续使用当前方式，如果：
- 项目简单，模块少
- 不需要条件编译
- 已经熟悉现有流程
- 不想改变现有构建系统

### 🟢 切换到官方方式，如果：⭐ 推荐
- 希望更灵活的配置
- 需要条件编译
- 模块数量较多
- 希望符合官方标准
- 便于与社区分享代码

### 🟢 两者并用
- 保留现有方式作为备份
- 逐步迁移到官方方式
- 学习和实验

---

## 迁移指南

### 快速迁移（5 分钟）

```bash
# 1. 创建 manifest.py（已提供）
# 文件已存在: manifest.py

# 2. 运行官方工具
python tools\freeze_official.py

# 3. 对比输出
# 检查生成的 frozen_mpy.c 是否相同

# 4. Keil 编译测试
# 确保所有模块正常工作

# 5. 切换（可选）
# 如果一切正常，可以完全切换到官方方式
```

### 兼容模式

```bash
# 保留两个脚本
python tools\regenerate_micropython_genhdr.py  # 原有方式
python tools\freeze_official.py                 # 官方方式

# 根据需要选择使用
```

---

## 文件清单

### 当前项目方式需要的文件
- ✅ `tools/regenerate_micropython_genhdr.py` (已有)
- ✅ `tools/freeze_module.py` (已有)
- ✅ `frozen_build/*.mpy` (已有)

### 官方方式需要的文件 ⭐
- ✅ `manifest.py` (已创建)
- ✅ `tools/freeze_official.py` (已创建)
- ✅ `Middlewares/micropython/tools/makemanifest.py` (官方提供)

---

## 常见问题

### Q: 必须切换到官方方式吗？
A: 不必须。当前方式完全可用。官方方式提供更多功能和灵活性。

### Q: 两种方式可以共存吗？
A: 可以。它们生成相同的 `frozen_mpy.c`，可以根据需要选择使用。

### Q: 官方方式难学吗？
A: 不难。`manifest.py` 语法简单，本质上就是声明要冻结哪些文件。

### Q: 性能有区别吗？
A: 没有。最终生成的 `frozen_mpy.c` 内容相同，性能一致。

### Q: 哪个更适合初学者？
A: 当前方式更直观（直接看到列表）。但官方方式更符合规范。

---

## 下一步

### 如果选择当前方式
1. 继续使用 `freeze_module.py`
2. 查看 [FROZEN_MODULE_KEIL_GUIDE.md](FROZEN_MODULE_KEIL_GUIDE.md)

### 如果选择官方方式 ⭐
1. 查看 [OFFICIAL_FREEZE_WORKFLOW_GUIDE.md](OFFICIAL_FREEZE_WORKFLOW_GUIDE.md)
2. 运行 `python tools\freeze_official.py`
3. 编辑 `manifest.py` 添加新模块

### 如果两者都想了解
1. 查看 [MICROPYTHON_DOCS_INDEX.md](MICROPYTHON_DOCS_INDEX.md)
2. 对比两种方式的输出
3. 选择最适合你的方式

---

**总结**: 两种方式都可行，官方方式更强大、更标准，建议新功能使用官方方式。

**创建日期**: 2026-01-28  
**项目**: mp_threadx
