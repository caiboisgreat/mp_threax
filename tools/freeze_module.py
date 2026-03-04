#!/usr/bin/env python3
"""
通用的冻结模块编译脚本
用法: python freeze_module.py <module_name>

示例:
    python freeze_module.py myutils
    python freeze_module.py sensor_driver
"""

import os
import subprocess
import sys
from pathlib import Path

# 项目路径配置
PROJECT_ROOT = Path(__file__).parent.parent.absolute()
MPY_CROSS = PROJECT_ROOT / "Middlewares" / "micropython" / "mpy-cross" / "build" / "mpy-cross.exe"
FROZEN_DIR = PROJECT_ROOT / "Middlewares" / "micropython" / "py_port" / "frozen_build"
REGENERATE_SCRIPT = PROJECT_ROOT / "tools" / "regenerate_micropython_genhdr.py"

def check_prerequisites():
    """检查必要的工具和文件"""
    errors = []
    
    if not MPY_CROSS.exists():
        errors.append(f"❌ mpy-cross 未找到: {MPY_CROSS}")
        errors.append("   需要先编译 mpy-cross 或下载预编译版本")
    
    if not FROZEN_DIR.exists():
        errors.append(f"❌ frozen_build 目录不存在: {FROZEN_DIR}")
    
    if not REGENERATE_SCRIPT.exists():
        errors.append(f"❌ 重新生成脚本未找到: {REGENERATE_SCRIPT}")
    
    if errors:
        for err in errors:
            print(err)
        return False
    
    return True

def compile_py_to_mpy(module_name):
    """编译 .py 文件为 .mpy"""
    source_py = FROZEN_DIR / f"{module_name}.py"
    output_mpy = FROZEN_DIR / f"{module_name}.mpy"
    
    if not source_py.exists():
        print(f"❌ 错误: 源文件未找到: {source_py}")
        print(f"\n请先创建该文件，例如:")
        print(f"   notepad {source_py}")
        return False
    
    print(f"\n📦 步骤 1: 编译 Python 模块")
    print(f"   源文件: {source_py.name}")
    print(f"   输出: {output_mpy.name}")
    
    try:
        result = subprocess.run(
            [
                str(MPY_CROSS),
                '-o', str(output_mpy),
                '-s', f'{module_name}.py',
                f'{module_name}.py'
            ],
            cwd=str(FROZEN_DIR),
            capture_output=True,
            text=True,
            timeout=30
        )
        
        if result.returncode != 0:
            print(f"   ❌ 编译失败!")
            if result.stderr:
                print(f"   错误信息:\n{result.stderr}")
            return False
        
        # 检查输出文件大小
        size = output_mpy.stat().st_size
        print(f"   ✅ 编译成功! (大小: {size} 字节)")
        
        return True
        
    except subprocess.TimeoutExpired:
        print(f"   ❌ 编译超时")
        return False
    except Exception as e:
        print(f"   ❌ 异常: {e}")
        return False

def regenerate_frozen_c():
    """重新生成 frozen_mpy.c"""
    print(f"\n🔄 步骤 2: 重新生成 frozen_mpy.c")
    print(f"   运行: {REGENERATE_SCRIPT.name}")
    
    try:
        result = subprocess.run(
            [sys.executable, str(REGENERATE_SCRIPT)],
            cwd=str(PROJECT_ROOT),
            capture_output=True,
            text=True,
            timeout=60
        )
        
        if result.returncode != 0:
            print(f"   ❌ 生成失败!")
            print(f"   错误信息:\n{result.stderr}")
            return False
        
        # 显示输出
        if result.stdout:
            print(result.stdout)
        
        print(f"   ✅ frozen_mpy.c 已更新")
        return True
        
    except subprocess.TimeoutExpired:
        print(f"   ❌ 生成超时")
        return False
    except Exception as e:
        print(f"   ❌ 异常: {e}")
        return False

def check_if_in_allowlist(module_name):
    """检查模块是否在 frozen_allowlist 中"""
    try:
        with open(REGENERATE_SCRIPT, 'r', encoding='utf-8') as f:
            content = f.read()
            return f'"{module_name}.mpy"' in content
    except:
        return False

def freeze_module(module_name):
    """冻结指定的模块"""
    
    print("=" * 80)
    print(f"🔥 冻结模块: {module_name}")
    print("=" * 80)
    
    # 检查前置条件
    if not check_prerequisites():
        return 1
    
    # 编译 .py -> .mpy
    if not compile_py_to_mpy(module_name):
        return 1
    
    # 检查是否在允许列表中
    if not check_if_in_allowlist(module_name):
        print(f"\n⚠️  警告: '{module_name}.mpy' 未在 frozen_allowlist 中")
        print(f"   请手动编辑: {REGENERATE_SCRIPT}")
        print(f"   在 frozen_allowlist 中添加: \"{module_name}.mpy\",")
        print(f"\n   例如:")
        print(f"   frozen_allowlist = [")
        print(f"       \"zlib.mpy\",")
        print(f"       \"gzip.mpy\",")
        print(f"       \"{module_name}.mpy\",  # 👈 添加这一行")
        print(f"   ]")
        
        response = input(f"\n是否继续重新生成 frozen_mpy.c? (y/n): ")
        if response.lower() != 'y':
            print("\n已取消")
            return 0
    
    # 重新生成 frozen_mpy.c
    if not regenerate_frozen_c():
        return 1
    
    # 成功提示
    print("\n" + "=" * 80)
    print(f"✅ 模块 '{module_name}' 已成功冻结!")
    print("=" * 80)
    print("\n📋 下一步操作:")
    
    if not check_if_in_allowlist(module_name):
        print(f"   1. ⚠️  在 {REGENERATE_SCRIPT.name} 的 frozen_allowlist 中添加此模块")
        print(f"   2. 重新运行: python {REGENERATE_SCRIPT.name}")
        print(f"   3. 在 Keil MDK 中重新编译项目 (Project -> Rebuild)")
    else:
        print(f"   1. 在 Keil MDK 中重新编译项目 (Project -> Rebuild)")
    
    print(f"   2. 烧录固件到 STM32")
    print(f"   3. 在 REPL 中测试:")
    print(f"      >>> import {module_name}")
    print(f"      >>> dir({module_name})")
    print()
    
    return 0

def list_frozen_modules():
    """列出所有已编译的 .mpy 模块"""
    print("\n📦 frozen_build 目录中的模块:")
    print("=" * 80)
    
    mpy_files = sorted(FROZEN_DIR.glob("*.mpy"))
    py_files = sorted(FROZEN_DIR.glob("*.py"))
    
    if mpy_files:
        print("\n已编译的 .mpy 文件:")
        for f in mpy_files:
            size = f.stat().st_size
            in_list = "✅" if check_if_in_allowlist(f.stem) else "❌"
            print(f"   {in_list} {f.name:20s} {size:8d} bytes")
    
    if py_files:
        print("\n未编译的 .py 文件:")
        for f in py_files:
            size = f.stat().st_size
            print(f"   ⏳ {f.name:20s} {size:8d} bytes")
    
    if not mpy_files and not py_files:
        print("   (空)")
    
    print()

def show_usage():
    """显示使用说明"""
    print("=" * 80)
    print("MicroPython 冻结模块编译工具")
    print("=" * 80)
    print("\n用法:")
    print(f"   python {Path(__file__).name} <module_name>     # 编译指定模块")
    print(f"   python {Path(__file__).name} --list            # 列出所有模块")
    print(f"   python {Path(__file__).name} --help            # 显示帮助")
    print("\n示例:")
    print(f"   python {Path(__file__).name} myutils")
    print(f"   python {Path(__file__).name} sensor_driver")
    print(f"   python {Path(__file__).name} config_manager")
    print("\n说明:")
    print("   1. 首先在 frozen_build/ 目录创建 .py 文件")
    print("   2. 运行此脚本编译为 .mpy")
    print("   3. 在 Keil 中重新编译固件")
    print("   4. 烧录后即可 import 使用")
    print()

def main():
    """主函数"""
    
    if len(sys.argv) < 2:
        show_usage()
        return 1
    
    arg = sys.argv[1]
    
    if arg in ['--help', '-h', 'help']:
        show_usage()
        return 0
    
    if arg in ['--list', '-l', 'list']:
        list_frozen_modules()
        return 0
    
    # 冻结指定模块
    module_name = arg
    
    # 验证模块名（仅允许字母、数字、下划线）
    if not module_name.replace('_', '').isalnum():
        print(f"❌ 错误: 无效的模块名 '{module_name}'")
        print("   模块名只能包含字母、数字和下划线")
        return 1
    
    return freeze_module(module_name)

if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        print("\n\n用户中断")
        sys.exit(1)
    except Exception as e:
        print(f"\n❌ 未预期的错误: {e}")
        import traceback
        traceback.print_exc()
        sys.exit(1)
