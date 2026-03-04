# manifestfile.py 详解 - MicroPython 冻结模块的核心引擎

## 🎯 什么是 manifestfile.py

`manifestfile.py` 是 MicroPython 官方工具链的**核心引擎**，它不是一个独立运行的脚本，而是一个被 `makemanifest.py` 导入和使用的**模块库**。

---

## 📊 调用关系图

```
用户操作:
    创建 manifest.py
        ↓
    运行 makemanifest.py
        ↓
        ├─ import manifestfile  ← 导入模块
        ├─ manifest = ManifestFile(MODE_FREEZE, VARS)  ← 创建对象
        ├─ manifest.execute("manifest.py")  ← 执行你的 manifest.py
        │   ↓
        │   执行 manifest.py 中的代码：
        │   ├─ freeze("modules", "myutils.py")  ← 调用 manifestfile 提供的函数
        │   ├─ include("$(MPY_DIR)/lib/ssl/manifest.py")
        │   └─ package("mypackage")
        │       ↓
        │       manifestfile 内部记录所有文件
        │       ↓
        ├─ for result in manifest.files():  ← 获取文件列表
        │   ├─ 编译 .py -> .mpy (调用 mpy-cross)
        │   └─ 收集 .mpy 文件
        │       ↓
        └─ 调用 mpy-tool.py 打包所有 .mpy -> frozen_mpy.c
```

---

## 🔧 核心作用

### 1️⃣ 提供 API 给 manifest.py

`manifestfile.py` 定义了在 `manifest.py` 中可以使用的所有函数：

```python
# 这些函数都是 manifestfile.py 提供的
freeze()      # manifestfile.ManifestFile.freeze()
include()     # manifestfile.ManifestFile.include()
require()     # manifestfile.ManifestFile.require()
metadata()    # manifestfile.ManifestFile.metadata()
package()     # manifestfile.ManifestFile.package()
module()      # manifestfile.ManifestFile.module()
```

### 2️⃣ 执行和解析 manifest.py

**makemanifest.py 调用**:
```python
# makemanifest.py 第 165 行
manifest = manifestfile.ManifestFile(manifestfile.MODE_FREEZE, VARS)

# 第 170 行
manifest.execute("manifest.py")
```

**manifestfile.py 执行过程**:
```python
# manifestfile.py execute() 方法
def execute(self, manifest_file):
    if manifest_file.endswith(".py"):
        # 执行 manifest.py 文件
        self.include(manifest_file)
    # ...

def include(self, manifest_path, **kwargs):
    # 读取 manifest.py
    with open(manifest_path) as f:
        # 执行其中的代码
        # 重点：_manifest_globals() 提供了可用的函数
        exec(f.read(), self._manifest_globals(kwargs))
```

**_manifest_globals() 设置可用函数**:
```python
# manifestfile.py 第 217 行
def _manifest_globals(self, kwargs):
    # 这是 manifest.py 中可用的 "API"
    g = {
        "metadata": self.metadata,        # 你在 manifest.py 调用的
        "include": self.include,          # 实际是这些方法
        "require": self.require,
        "add_library": self.add_library,
        "package": self.package,
        "module": self.module,
        "options": IncludeOptions(**kwargs),
    }
    
    # Freeze 模式额外函数
    if self._mode == MODE_FREEZE:
        g.update({
            "freeze": self.freeze,        # 你最常用的
            "freeze_as_str": self.freeze_as_str,
            "freeze_as_mpy": self.freeze_as_mpy,
            "freeze_mpy": self.freeze_mpy,
        })
    
    return g
```

### 3️⃣ 管理文件列表

每次在 `manifest.py` 中调用 `freeze()`，`manifestfile.py` 都会记录：

```python
# manifestfile.py 内部维护文件列表
self._manifest_files = []  # 存储所有要冻结的文件

def freeze(self, path, script=None, opt=None):
    # 解析路径和文件
    # 调用内部方法添加文件
    self._add_file(full_path, target_path, kind, opt)

def _add_file(self, full_path, target_path, kind, opt):
    # 获取文件时间戳
    stat = os.stat(full_path)
    timestamp = stat.st_mtime
    
    # 添加到列表
    self._manifest_files.append(
        ManifestOutput(
            FILE_TYPE_LOCAL,
            full_path,     # 完整路径
            target_path,   # 目标路径
            timestamp,     # 时间戳
            kind,          # 类型（STR/MPY）
            metadata,      # 元数据
            opt            # 优化级别
        )
    )

def files(self):
    # makemanifest.py 调用这个获取所有文件
    return self._manifest_files
```

### 4️⃣ 处理路径变量

```python
# manifest.py 中写
freeze("$(PORT_DIR)/modules", "myutils.py")

# manifestfile.py 自动替换
def _resolve_path(self, path):
    for name, value in self._path_vars.items():
        if value is not None:
            # 替换 $(PORT_DIR) 为实际路径
            path = path.replace("$({})".format(name), value)
    return os.path.abspath(path)
```

---

## 💡 实际执行流程示例

### 你的 manifest.py:
```python
metadata(version="1.0.0")
freeze("$(PORT_DIR)/frozen_build", "myutils.py")
include("$(MPY_DIR)/lib/ssl/manifest.py")
```

### manifestfile.py 执行过程:

```python
# 步骤 1: makemanifest.py 创建对象
manifest = ManifestFile(MODE_FREEZE, {
    "MPY_DIR": "/path/to/micropython",
    "PORT_DIR": "/path/to/port"
})

# 步骤 2: 执行 manifest.py
manifest.execute("manifest.py")
    ↓
    # 读取并执行 manifest.py 内容
    exec("""
metadata(version="1.0.0")
freeze("$(PORT_DIR)/frozen_build", "myutils.py")
include("$(MPY_DIR)/lib/ssl/manifest.py")
    """, globals_dict)
    
    # globals_dict 包含：
    # {
    #     "metadata": manifest.metadata,
    #     "freeze": manifest.freeze,
    #     "include": manifest.include,
    # }

# 步骤 3: 执行 metadata(version="1.0.0")
    ↓ 调用 manifest.metadata()
    ↓ 设置元数据

# 步骤 4: 执行 freeze("$(PORT_DIR)/frozen_build", "myutils.py")
    ↓ 调用 manifest.freeze()
    ↓ _resolve_path() 替换变量
        "$(PORT_DIR)/frozen_build" → "/path/to/port/frozen_build"
    ↓ _add_file() 添加到列表
        self._manifest_files.append(ManifestOutput(
            full_path="/path/to/port/frozen_build/myutils.py",
            target_path="myutils.py",
            kind=KIND_FREEZE_AS_MPY,
            ...
        ))

# 步骤 5: 执行 include("$(MPY_DIR)/lib/ssl/manifest.py")
    ↓ 调用 manifest.include()
    ↓ 递归执行 ssl/manifest.py
    ↓ ssl/manifest.py 中的 freeze() 也会添加到列表

# 步骤 6: makemanifest.py 获取结果
for result in manifest.files():
    # result 是每个 ManifestOutput 对象
    # 包含了所有需要冻结的文件信息
    print(result.full_path)    # 源文件路径
    print(result.target_path)  # 目标路径
    print(result.kind)         # 冻结类型
    
    # makemanifest 根据这些信息编译文件
```

---

## 🔑 关键类和方法

### ManifestFile 类

```python
class ManifestFile:
    def __init__(self, mode, path_vars):
        """
        mode: MODE_FREEZE（冻结模式）
        path_vars: 路径变量字典，如 {"MPY_DIR": "...", "PORT_DIR": "..."}
        """
        self._mode = mode
        self._path_vars = path_vars
        self._manifest_files = []  # 存储文件
        self._metadata = []         # 元数据栈
        self._visited = set()       # 已访问的 manifest
    
    def execute(self, manifest_file):
        """执行 manifest.py 文件"""
    
    def freeze(self, path, script, opt):
        """冻结文件（最常用的方法）"""
    
    def include(self, manifest_path, **kwargs):
        """包含另一个 manifest.py"""
    
    def require(self, name, **kwargs):
        """引入外部包"""
    
    def files(self):
        """返回所有要冻结的文件"""
        return self._manifest_files
```

### ManifestOutput 命名元组

```python
ManifestOutput = namedtuple(
    "ManifestOutput",
    [
        "file_type",   # FILE_TYPE_LOCAL
        "full_path",   # 完整文件路径
        "target_path", # 目标路径（模块名）
        "timestamp",   # 文件修改时间
        "kind",        # KIND_FREEZE_AS_MPY / KIND_FREEZE_MPY
        "metadata",    # 包元数据
        "opt",         # 优化级别 (0/1/2)
    ],
)
```

---

## 📋 完整调用示例

### makemanifest.py 使用 manifestfile:

```python
#!/usr/bin/env python3
import manifestfile

# 1. 创建 ManifestFile 对象
manifest = manifestfile.ManifestFile(
    manifestfile.MODE_FREEZE,
    {"MPY_DIR": "...", "PORT_DIR": "..."}
)

# 2. 执行 manifest.py
try:
    manifest.execute("manifest.py")
except manifestfile.ManifestFileError as er:
    print(f"Error: {er}")
    exit(1)

# 3. 获取所有文件
for result in manifest.files():
    # result 是 ManifestOutput 对象
    
    if result.kind == manifestfile.KIND_FREEZE_AS_MPY:
        # 需要编译 .py -> .mpy
        print(f"Compiling: {result.full_path}")
        mpy_cross.compile(
            result.full_path,
            dest=f"build/{result.target_path}.mpy",
            opt=result.opt
        )
    
    elif result.kind == manifestfile.KIND_FREEZE_MPY:
        # 直接使用 .mpy 文件
        print(f"Using: {result.full_path}")
```

---

## 🎓 总结

### manifestfile.py 的角色

1. **不是独立脚本** - 是一个被导入的模块
2. **API 提供者** - 提供 `freeze()`、`include()` 等函数
3. **执行引擎** - 解析和执行 `manifest.py`
4. **文件管理器** - 收集和管理所有要冻结的文件
5. **桥梁** - 连接 `manifest.py`（配置）和 `makemanifest.py`（执行）

### 为什么需要 manifestfile.py

❌ **没有 manifestfile.py**:
- 需要手动编写复杂的列表
- 难以处理依赖关系
- 缺乏灵活性

✅ **有了 manifestfile.py**:
- 提供友好的 API（freeze、include）
- 自动处理依赖和递归
- 支持条件编译和变量替换
- 统一的配置格式

---

## 🔗 相关文件

- **manifestfile.py** - 本文档介绍的核心引擎
- **makemanifest.py** - 使用 manifestfile 的主脚本
- **manifest.py** - 你编写的配置文件（使用 manifestfile 提供的 API）

---

**创建日期**: 2026-01-28  
**文件位置**: `Middlewares/micropython/tools/manifestfile.py`  
**主要调用者**: `makemanifest.py`
