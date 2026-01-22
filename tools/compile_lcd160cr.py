#!/usr/bin/env python3
"""
Compile lcd160cr.py to .mpy format and regenerate frozen module files
"""

import os
import subprocess
import sys

# Project paths
PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
MPY_CROSS_EXE = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'mpy-cross', 'build', 'mpy-cross.exe')
LCD160CR_PY = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'lib', 'lcd160cr', 'lcd160cr.py')
OUTPUT_MPY = os.path.join(PROJECT_ROOT, 'Middlewares', 'micropython', 'py_port', 'frozen_build', 'lcd160cr.mpy')
REGENERATE_SCRIPT = os.path.join(PROJECT_ROOT, 'tools', 'regenerate_micropython_genhdr.py')

def main():
    print("=" * 60)
    print("Compiling lcd160cr module")
    print("=" * 60)
    
    # Check if mpy-cross exists
    if not os.path.exists(MPY_CROSS_EXE):
        print(f"ERROR: mpy-cross not found at: {MPY_CROSS_EXE}")
        return 1
    
    # Check if lcd160cr.py exists
    if not os.path.exists(LCD160CR_PY):
        print(f"ERROR: lcd160cr.py not found at: {LCD160CR_PY}")
        return 1
    
    print(f"\n1. Source file: {LCD160CR_PY}")
    print(f"   Output file: {OUTPUT_MPY}")
    
    # Compile lcd160cr.py to .mpy
    print("\n2. Running mpy-cross...")
    try:
        result = subprocess.run(
            [MPY_CROSS_EXE, '-o', OUTPUT_MPY, '-s', 'lcd160cr.py', os.path.basename(LCD160CR_PY)],
            cwd=os.path.dirname(LCD160CR_PY),
            capture_output=True,
            text=True,
            check=False
        )
        
        if result.returncode != 0:
            print(f"   ERROR: Compilation failed!")
            print(f"   stdout: {result.stdout}")
            print(f"   stderr: {result.stderr}")
            return 1
        else:
            print(f"   SUCCESS: lcd160cr.mpy compiled successfully!")
            
    except Exception as e:
        print(f"   ERROR: Failed to run mpy-cross: {e}")
        return 1
    
    # Verify the output file exists
    if not os.path.exists(OUTPUT_MPY):
        print(f"\n   ERROR: Output file not created: {OUTPUT_MPY}")
        return 1
    
    file_size = os.path.getsize(OUTPUT_MPY)
    print(f"   File size: {file_size} bytes")
    
    # Run regenerate script
    print("\n3. Regenerating frozen module C code...")
    print(f"   Running: {REGENERATE_SCRIPT}")
    
    try:
        result = subprocess.run(
            [sys.executable, REGENERATE_SCRIPT],
            cwd=PROJECT_ROOT,
            capture_output=True,
            text=True,
            check=False
        )
        
        if result.returncode != 0:
            print(f"   WARNING: Regenerate script returned {result.returncode}")
            print(f"   stdout: {result.stdout}")
            print(f"   stderr: {result.stderr}")
        else:
            print(f"   SUCCESS: Frozen module code regenerated!")
            if result.stdout:
                print(f"   Output: {result.stdout}")
                
    except Exception as e:
        print(f"   ERROR: Failed to run regenerate script: {e}")
        return 1
    
    print("\n" + "=" * 60)
    print("COMPLETED SUCCESSFULLY!")
    print("=" * 60)
    print("\nNext steps:")
    print("1. Rebuild the Keil project")
    print("2. Flash the new firmware")
    print("3. Test in REPL: help('modules')")
    print("4. Import test: import lcd160cr")
    print()
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
