"""
检查模块是否正确编译和注册
Check if modules are properly compiled and registered
"""

import sys
import gc

print("="*60)
print("模块检查诊断脚本 / Module Check Diagnostic Script")
print("="*60)
print()

# 1. 检查 sys.modules
print("[1] 检查已注册的模块 / Checking registered modules:")
print("-"*60)
try:
    import sys
    all_modules = sys.modules
    print(f"总模块数 / Total modules: {len(all_modules)}")
    
    # 查找pyb、stm、lcd160cr
    pyb_found = 'pyb' in all_modules
    stm_found = 'stm' in all_modules
    lcd_found = 'lcd160cr' in all_modules
    
    print(f"\npyb 模块:      {'✅ 已注册' if pyb_found else '❌ 未注册'}")
    print(f"stm 模块:      {'✅ 已注册' if stm_found else '❌ 未注册'}")
    print(f"lcd160cr 模块: {'✅ 已注册' if lcd_found else '❌ 未注册'}")
    
except Exception as e:
    print(f"错误: {e}")

print()

# 2. 尝试导入模块
print("[2] 尝试导入模块 / Attempting to import modules:")
print("-"*60)

# 尝试导入 pyb
print("\n2.1 导入 pyb 模块:")
try:
    import pyb
    print("✅ 成功导入 pyb 模块")
    print(f"   pyb 模块内容: {dir(pyb)}")
except ImportError as e:
    print(f"❌ 无法导入 pyb 模块: {e}")
    print("\n可能的原因:")
    print("  1. modpyb.c 没有被添加到 KEIL 项目中")
    print("  2. MICROPY_PY_PYB 宏没有定义为 1")
    print("  3. 项目没有重新编译")
except Exception as e:
    print(f"❌ 导入时发生错误: {e}")

# 尝试导入 stm
print("\n2.2 导入 stm 模块:")
try:
    import stm
    print("✅ 成功导入 stm 模块")
    print(f"   stm 模块内容: {dir(stm)}")
except ImportError as e:
    print(f"❌ 无法导入 stm 模块: {e}")
    print("\n可能的原因:")
    print("  1. modstm.c 没有被添加到 KEIL 项目中")
    print("  2. MICROPY_PY_STM 宏没有定义为 1")
    print("  3. 项目没有重新编译")
except Exception as e:
    print(f"❌ 导入时发生错误: {e}")

# 尝试导入 lcd160cr
print("\n2.3 导入 lcd160cr 模块:")
try:
    import lcd160cr
    print("✅ 成功导入 lcd160cr 模块")
    print(f"   lcd160cr 模块内容: {dir(lcd160cr)[:10]}...")  # 只显示前10个
except ImportError as e:
    print(f"❌ 无法导入 lcd160cr 模块: {e}")
    print("\n可能的原因:")
    print("  1. lcd160cr.py 没有被冻结到固件中")
    print("  2. manifest.py 配置不正确")
    print("  3. 冻结模块的构建步骤没有执行")
except Exception as e:
    print(f"❌ 导入时发生错误: {e}")

print()

# 3. 检查配置宏
print("[3] 检查编译配置 / Checking compile configuration:")
print("-"*60)
try:
    # 尝试通过特征函数来推断配置
    test_passed = 0
    test_total = 0
    
    # 测试 gc 模块 (基础功能)
    test_total += 1
    try:
        import gc
        gc.collect()
        test_passed += 1
        print("✅ gc 模块正常")
    except:
        print("❌ gc 模块异常")
    
    # 测试 sys 模块
    test_total += 1
    try:
        import sys
        print(f"✅ sys 模块正常 (platform: {sys.platform})")
        test_passed += 1
    except:
        print("❌ sys 模块异常")
    
    # 测试 math 模块
    test_total += 1
    try:
        import math
        test_passed += 1
        print("✅ math 模块正常")
    except:
        print("❌ math 模块异常")
    
    print(f"\n基础模块测试: {test_passed}/{test_total} 通过")
    
except Exception as e:
    print(f"错误: {e}")

print()

# 4. 提供解决方案
print("[4] 解决方案建议 / Suggested Solutions:")
print("-"*60)
print("""
如果 pyb 或 stm 模块未找到，请执行以下步骤:

步骤 1: 在 KEIL 项目中添加源文件
  1. 打开 KEIL MDK 项目
  2. 在项目树中找到 MicroPython 相关的组
  3. 右键 → Add Existing Files to Group
  4. 添加以下文件:
     - Middlewares/micropython/py_port/modpyb.c
     - Middlewares/micropython/py_port/modstm.c

步骤 2: 验证配置宏
  1. 打开 mpconfigport.h 文件
  2. 确认以下定义存在且为 1:
     #define MICROPY_PY_PYB (1)
     #define MICROPY_PY_STM (1)

步骤 3: 清理并重新编译
  1. 在 KEIL 中: Project → Clean Targets
  2. 删除 build 目录中的 .o 文件
  3. 重新编译: Project → Build Target (F7)

步骤 4: 重新烧录固件
  1. 使用 KEIL 或其他工具烧录新的固件
  2. 复位板子
  3. 重新运行此诊断脚本

如果 lcd160cr 模块未找到，请检查:
  1. Middlewares/micropython/lib/lcd160cr/manifest.py 是否存在
  2. 构建系统是否正确处理冻结模块
  3. 查看编译输出中是否有 "Freezing" 相关信息
""")

print()
print("="*60)
print("诊断完成 / Diagnostic Completed")
print("="*60)
