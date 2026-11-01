@echo off
rem ============================================================
rem  p1.2 command line build (Debug configuration)
rem  Double click to build. Independent from the IDE.
rem  Usage:
rem    build_debug.cmd          incremental build
rem    build_debug.cmd clean    clean + full rebuild
rem  Output: Debug\p1.2.elf
rem ============================================================
setlocal

set "TC=D:\SoftWare\stm32cubeIDE\STM32CubeIDE_1.19.0\STM32CubeIDE\plugins"
set "MAKEBIN=%TC%\com.st.stm32cube.ide.mcu.externaltools.make.win32_2.2.0.202409170845\tools\bin"
set "GCCBIN=%TC%\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.13.3.rel1.win32_1.0.0.202411081344\tools\bin"

if not exist "%MAKEBIN%\make.exe" (
    echo [ERROR] make.exe not found:
    echo         %MAKEBIN%
    pause
    exit /b 1
)
if not exist "%GCCBIN%\arm-none-eabi-gcc.exe" (
    echo [ERROR] arm-none-eabi-gcc.exe not found:
    echo         %GCCBIN%
    pause
    exit /b 1
)

set "PATH=%GCCBIN%;%MAKEBIN%;%PATH%"
cd /d "%~dp0Debug"

if /i "%~1"=="clean" (
    echo === clean ===
    "%MAKEBIN%\make.exe" clean
)

echo === build ===
"%MAKEBIN%\make.exe" all
set "RC=%ERRORLEVEL%"

echo.
if "%RC%"=="0" (
    echo [OK] build succeeded, artifact in %~dp0Debug
    for %%F in ("%~dp0Debug\*.elf") do echo      %%~nxF
) else (
    echo [FAIL] build failed, exit code %RC%
)
pause
exit /b %RC%
