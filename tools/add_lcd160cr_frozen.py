#!/usr/bin/env python3
"""
Add lcd160cr module to frozen modules
将 lcd160cr 模块添加到冻结模块列表
"""

import subprocess
import sys
from pathlib import Path

def main():
    # 路径配置
    workspace = Path(__file__).parent.parent
    mpy_cross = workspace / "Middlewares/micropython/mpy-cross/build/mpy-cross.exe"
    lcd_py = workspace / "Middlewares/micropython/lib/lcd160cr/lcd160cr.py"
    out_mpy = workspace / "Middlewares/micropython/py_port/frozen_build/lcd160cr.mpy"
    
    print("=" * 60)
    print("添加 lcd160cr 冻结模块 / Add lcd160cr frozen module")
    print("=" * 60)
    
    # 步骤 1: 编译 .py 到 .mpy
    print(f"\n[1/3] 编译 lcd160cr.py → lcd160cr.mpy...")
    print(f"  源文件: {lcd_py}")
    print(f"  输出文件: {out_mpy}")
    
    if not mpy_cross.exists():
        print(f"❌ 错误: mpy-cross.exe 不存在: {mpy_cross}")
        return 1
    
    if not lcd_py.exists():
        print(f"❌ 错误: lcd160cr.py 不存在: {lcd_py}")
        return 1
    
    # 编译
    result = subprocess.run(
        [str(mpy_cross), "-o", str(out_mpy), "-s", "lcd160cr.py", lcd_py.name],
        cwd=str(lcd_py.parent),
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"❌ 编译失败:")
        print(result.stderr)
        return 1
    
    print(f"✅ 编译成功: {out_mpy.name}")
    
    # 步骤 2: 更新 regenerate_micropython_genhdr.py
    print(f"\n[2/3] 更新 regenerate_micropython_genhdr.py...")
    
    regen_script = workspace / "tools/regenerate_micropython_genhdr.py"
    content = regen_script.read_text(encoding="utf-8")
    
    # 查找 frozen_allowlist
    needle = '    frozen_allowlist = [\n        "zlib.mpy",\n        "gzip.mpy",\n        "_thread.mpy",\n        "ssl.mpy",\n    ]'
    replacement = '    frozen_allowlist = [\n        "zlib.mpy",\n        "gzip.mpy",\n        "_thread.mpy",\n        "ssl.mpy",\n        "lcd160cr.mpy",\n    ]'
    
    if "lcd160cr.mpy" in content:
        print("  ⚠️  lcd160cr.mpy 已经在列表中")
    else:
        if needle in content:
            new_content = content.replace(needle, replacement)
            regen_script.write_text(new_content, encoding="utf-8")
            print("✅ frozen_allowlist 已更新")
        else:
            print("  ⚠️  无法自动更新，请手动添加 'lcd160cr.mpy' 到 frozen_allowlist")
    
    # 步骤 3: 重新生成 frozen_mpy.c
    print(f"\n[3/3] 运行 regenerate_micropython_genhdr.py...")
    
    result = subprocess.run(
        [sys.executable, str(regen_script)],
        cwd=str(workspace),
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"❌ 重新生成失败:")
        print(result.stderr)
        return 1
    
    print(result.stdout)
    print("\n✅ frozen_mpy.c 已重新生成")
    
    print("\n" + "=" * 60)
    print("✅ 完成！lcd160cr 模块已添加到冻结模块")
    print("=" * 60)
    print("\n下一步:")
    print("1. 在 Keil MDK 中重新编译项目")
    print("2. 烧录固件到板子")
    print("3. 在 MicroPython REPL 中测试: import lcd160cr")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())
