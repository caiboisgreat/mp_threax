#!/usr/bin/env python3
"""
使用官方 makemanifest.py 的包装脚本
适配到 mp_threadx 项目结构

用法:
    python freeze_official.py

说明:
    此脚本调用 MicroPython 官方的 makemanifest.py 工具，
    使用 manifest.py 文件定义的模块列表生成 frozen_mpy.c
"""

import sys
import os
import subprocess
from pathlib import Path

# ============================================================================
# 项目路径配置
# ============================================================================

PROJECT_ROOT = Path(__file__).parent.parent.absolute()
MPY_DIR = PROJECT_ROOT / "Middlewares" / "micropython"
PORT_DIR = PROJECT_ROOT / "Middlewares" / "micropython" / "py_port"
BUILD_DIR = PROJECT_ROOT / "build"
GENHDR_DIR = MPY_DIR / "genhdr"

# 工具路径
MAKEMANIFEST = MPY_DIR / "tools" / "makemanifest.py"
MPY_CROSS = MPY_DIR / "mpy-cross" / "build" / "mpy-cross.exe"

# 输入/输出
MANIFEST = PROJECT_ROOT / "manifest.py"
OUTPUT = PORT_DIR / "frozen_mpy.c"
QSTR_HEADER = GENHDR_DIR / "qstrdefs.preprocessed.h"

# ============================================================================
# 辅助函数
# ============================================================================

def check_prerequisites():
    """检查必要的工具和文件"""
    errors = []
    
    if not MAKEMANIFEST.exists():
        errors.append(f"❌ makemanifest.py 未找到: {MAKEMANIFEST}")
        errors.append(f"   这是 MicroPython 官方工具，应该在源码树中")
    
    if not MPY_CROSS.exists():
        errors.append(f"❌ mpy-cross 未找到: {MPY_CROSS}")
        errors.append(f"   需要先编译 mpy-cross 或下载预编译版本")
    
    if not MANIFEST.exists():
        errors.append(f"❌ manifest.py 未找到: {MANIFEST}")
        errors.append(f"   请先创建 manifest.py 文件（参考 OFFICIAL_FREEZE_WORKFLOW_GUIDE.md）")
    
    if not QSTR_HEADER.exists():
        errors.append(f"⚠️  警告: QSTR 头文件未找到: {QSTR_HEADER}")
        errors.append(f"   如果是首次运行，可能需要先运行 regenerate_micropython_genhdr.py")
    
    if errors:
        for err in errors:
            print(err)
        return False
    
    return True

def create_build_dirs():
    """创建必要的构建目录"""
    BUILD_DIR.mkdir(exist_ok=True)
    (BUILD_DIR / "frozen_mpy").mkdir(exist_ok=True)
    print(f"✅ 构建目录已准备: {BUILD_DIR}")

def run_makemanifest():
    """运行官方的 makemanifest.py"""
    
    # 构建命令
    cmd = [
        sys.executable,
        str(MAKEMANIFEST),
        "--output", str(OUTPUT),
        "--build-dir", str(BUILD_DIR),
        "--mpy-cross-flags", "-march=armv7m",  # STM32F4 使用 ARM Cortex-M4
        "--mpy-tool-flags", "-f",               # freeze 模式
        "--var", f"MPY_DIR={MPY_DIR}",
        "--var", f"PORT_DIR={PORT_DIR}",
        str(MANIFEST)
    ]
    
    print(f"\n📝 运行官方 makemanifest.py:")
    print(f"   命令: {' '.join(str(c) for c in cmd)}")
    print()
    
    try:
        result = subprocess.run(
            cmd,
            cwd=str(PROJECT_ROOT),
            capture_output=True,
            text=True,
            timeout=120
        )
        
        # 显示输出
        if result.stdout:
            # makemanifest 会输出正在处理的文件
            for line in result.stdout.splitlines():
                if line.strip():
                    print(f"   {line}")
        
        if result.returncode != 0:
            print(f"\n❌ makemanifest.py 执行失败!")
            if result.stderr:
                print(f"\n错误信息:")
                print(result.stderr)
            return False
        
        return True
        
    except subprocess.TimeoutExpired:
        print(f"\n❌ 执行超时")
        return False
    except Exception as e:
        print(f"\n❌ 异常: {e}")
        import traceback
        traceback.print_exc()
        return False

def verify_output():
    """验证输出文件"""
    if not OUTPUT.exists():
        print(f"❌ 输出文件未生成: {OUTPUT}")
        return False
    
    size = OUTPUT.stat().st_size
    if size == 0:
        print(f"❌ 输出文件为空")
        return False
    
    print(f"\n✅ frozen_mpy.c 已生成")
    print(f"   路径: {OUTPUT}")
    print(f"   大小: {size:,} 字节 ({size/1024:.1f} KB)")
    
    return True

def show_next_steps():
    """显示下一步操作"""
    print("\n" + "=" * 80)
    print("🎉 成功！官方工作流程已完成")
    print("=" * 80)
    print("\n📋 下一步操作:")
    print("   1. 在 Keil MDK 中重新编译项目")
    print("      Project -> Rebuild all target files (F7)")
    print("   2. 烧录固件到 STM32F405")
    print("   3. 在 REPL 中测试冻结的模块:")
    print("      >>> import myutils")
    print("      >>> help('modules')")
    print()
    print("💡 提示:")
    print("   - 修改 manifest.py 后重新运行此脚本")
    print("   - 查看详细文档: OFFICIAL_FREEZE_WORKFLOW_GUIDE.md")
    print()

def compare_with_old_way():
    """对比新旧方式"""
    print("\n" + "=" * 80)
    print("📊 与原有方式对比")
    print("=" * 80)
    print("\n原有方式:")
    print("   1. 手动编辑 frozen_allowlist")
    print("   2. 运行 regenerate_micropython_genhdr.py")
    print("\n官方方式:")
    print("   1. 编辑 manifest.py（声明式配置）")
    print("   2. 运行 freeze_official.py")
    print("\n优势:")
    print("   ✅ 更灵活的模块管理")
    print("   ✅ 支持条件编译")
    print("   ✅ 自动处理依赖")
    print("   ✅ 符合 MicroPython 官方规范")
    print()

# ============================================================================
# 主函数
# ============================================================================

def main():
    """主执行流程"""
    
    print("=" * 80)
    print("MicroPython 官方冻结模块工作流程")
    print("使用 makemanifest.py + manifest.py")
    print("=" * 80)
    print()
    
    # 1. 检查前置条件
    print("🔍 步骤 1: 检查前置条件")
    if not check_prerequisites():
        print("\n⚠️  请解决上述问题后重试")
        return 1
    print("   ✅ 所有前置条件满足\n")
    
    # 2. 创建构建目录
    print("📁 步骤 2: 准备构建目录")
    create_build_dirs()
    print()
    
    # 3. 运行 makemanifest
    print("🔧 步骤 3: 运行 makemanifest.py")
    if not run_makemanifest():
        print("\n❌ 生成失败")
        return 1
    print()
    
    # 4. 验证输出
    print("✔️  步骤 4: 验证输出文件")
    if not verify_output():
        return 1
    
    # 5. 显示下一步
    show_next_steps()
    
    # 6. 对比说明
    compare_with_old_way()
    
    return 0

if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print("\n\n⚠️  用户中断")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ 未预期的错误: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
