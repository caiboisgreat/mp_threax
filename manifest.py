"""
MicroPython 冻结模块 Manifest 文件

此文件使用 MicroPython 官方的 manifest.py 语法定义要冻结的模块。
相比手动维护 frozen_allowlist 列表，这种方式更灵活、更易维护。

官方文档: https://docs.micropython.org/en/latest/reference/manifest.html

使用方法:
    python tools/freeze_official.py

文件结构:
    1. 项目元数据
    2. 标准库模块（从 micropython-lib 引入）
    3. 自定义模块（frozen_build 目录）
    4. 驱动和库（可选）
"""

# ============================================================================
# 1. 项目元数据
# ============================================================================

metadata(
    version="1.0.0",
    description="STM32F405 + ThreadX MicroPython Port",
    author="CaiBo",
    license="MIT"
)

# ============================================================================
# 2. 标准库模块
# ============================================================================
# 这些是原来在 frozen_allowlist 中的标准库模块
# 使用官方 manifest 可以直接 include，自动处理依赖

# SSL/TLS 支持
# 原来: "ssl.mpy" in frozen_allowlist
# 现在: 直接包含官方 manifest
include("$(MPY_DIR)/lib/micropython-lib/python-stdlib/ssl/manifest.py")

# 压缩库 - zlib
# 原来: "zlib.mpy" in frozen_allowlist
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/zlib", "zlib.py")

# 压缩库 - gzip
# 原来: "gzip.mpy" in frozen_allowlist  
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/gzip", "gzip.py")

# 线程支持
# 原来: "_thread.mpy" in frozen_allowlist
freeze("$(MPY_DIR)/lib/micropython-lib/python-stdlib/_thread", "_thread.py")

# LCD160CR 驱动
# 原来: "lcd160cr.mpy" in frozen_allowlist
include("$(MPY_DIR)/lib/lcd160cr/manifest.py")

# ============================================================================
# 3. 自定义模块
# ============================================================================
# 这些是项目特定的自定义模块，位于 py_port/frozen_build 目录

# myutils - 工具模块示例
# 原来: "myutils.mpy" in frozen_allowlist
# 现在: 直接声明冻结
freeze("$(PORT_DIR)/frozen_build", "myutils.py")

# 如果有更多自定义模块，在这里添加
# freeze("$(PORT_DIR)/frozen_build", [
#     "myutils.py",
#     "config.py",
#     "helpers.py",
# ])

# ============================================================================
# 4. 可选：驱动和库
# ============================================================================
# 如果你有额外的驱动或库目录，在这里添加

# 示例：冻结 drivers 目录
# freeze("$(PORT_DIR)/drivers", [
#     "sensor.py",
#     "lcd_driver.py",
#     "led.py",
# ])

# 示例：冻结整个包（带 __init__.py 的目录）
# package("$(PORT_DIR)/mypackage")

# ============================================================================
# 5. 条件编译示例（可选）
# ============================================================================
# manifest.py 支持条件编译，可以根据不同配置冻结不同模块

# 示例 1: 根据选项启用
# if options.ENABLE_NETWORKING:
#     freeze("$(PORT_DIR)/modules", "network_utils.py")

# 示例 2: 根据板子类型
# if options.BOARD == "STM32F405":
#     freeze("$(PORT_DIR)/boards/stm32f405", "board_config.py")

# ============================================================================
# 6. 优化级别示例（可选）
# ============================================================================
# 可以为不同模块指定不同的优化级别

# opt=0: 无优化，保留所有信息（默认）
# freeze("$(PORT_DIR)/modules", "debug_module.py", opt=0)

# opt=1: 基本优化
# freeze("$(PORT_DIR)/modules", "normal_module.py", opt=1)

# opt=2: 最大优化，移除文档字符串和断言
# freeze("$(PORT_DIR)/modules", "production_module.py", opt=2)

# ============================================================================
# 使用说明
# ============================================================================
"""
添加新的冻结模块:

1. 在 frozen_build 目录创建 .py 文件
   例如: Middlewares/micropython/py_port/frozen_build/my_sensor.py

2. 在此文件中添加一行:
   freeze("$(PORT_DIR)/frozen_build", "my_sensor.py")

3. 运行官方冻结脚本:
   python tools/freeze_official.py

4. 在 Keil 中重新编译项目

5. 测试:
   >>> import my_sensor
   >>> my_sensor.read()

对比原有方式:
   原来: 需要手动编辑 regenerate_micropython_genhdr.py 的 frozen_allowlist
   现在: 只需在此文件添加一行 freeze() 声明

优势:
   ✅ 更清晰的模块组织
   ✅ 支持条件编译
   ✅ 自动处理依赖
   ✅ 符合官方规范
   ✅ 易于维护和版本控制
"""
