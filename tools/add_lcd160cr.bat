@echo off
REM 添加 lcd160cr 模块到冻结模块
echo ============================================================
echo  添加 lcd160cr 到冻结模块 / Add lcd160cr to frozen modules
echo ============================================================

echo.
echo [1/3] 编译 lcd160cr.py 到 lcd160cr.mpy...
Middlewares\micropython\mpy-cross\build\mpy-cross.exe ^
  -o Middlewares\micropython\py_port\frozen_build\lcd160cr.mpy ^
  Middlewares\micropython\lib\lcd160cr\lcd160cr.py

if errorlevel 1 (
  echo ❌ 编译失败
  pause
  exit /b 1
)
echo ✅ 编译成功

echo.
echo [2/3] 重新生成 frozen_mpy.c...
python tools\regenerate_micropython_genhdr.py

if errorlevel 1 (
  echo ❌ 生成失败
  pause
  exit /b 1
)

echo.
echo ============================================================
echo ✅ 完成！lcd160cr 已添加到冻结模块
echo ============================================================
echo.
echo 下一步:
echo 1. 在 Keil MDK 中重新编译项目
echo 2. 烧录固件到板子
echo 3. 在 MicroPython REPL 中测试: import lcd160cr
echo.
pause
