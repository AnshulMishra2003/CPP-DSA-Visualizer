@echo off
REM Build Script for C++ DSA Visualizer (Windows)
REM This script builds the project in Release mode with all dependencies

setlocal enabledelayedexpansion

echo.
echo ======================================
echo C++ DSA Visualizer Build Script
echo ======================================
echo.

set BUILD_TYPE=Release
set BUILD_DIR=build-release

if "%1"=="debug" (
    set BUILD_TYPE=Debug
    set BUILD_DIR=build-debug
    echo Building in DEBUG mode...
) else (
    echo Building in RELEASE mode...
)

REM Create build directory
if not exist "%BUILD_DIR%" (
    echo Creating build directory: %BUILD_DIR%
    mkdir "%BUILD_DIR%"
)

cd /d "%BUILD_DIR%"

echo.
echo Step 1: Running CMake configuration...
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

if errorlevel 1 (
    echo CMake configuration failed!
    exit /b 1
)

echo.
echo Step 2: Building project...
cmake --build .

if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo.
echo ======================================
echo Build completed successfully!
echo ======================================
echo.

if "%BUILD_TYPE%"=="Release" (
    echo Executable location: %BUILD_DIR%\ds_visualizer.exe
    echo.
    echo To deploy:
    echo   1. Copy ds_visualizer.exe to a folder
    echo   2. Run: windeployqt ds_visualizer.exe
    echo   3. Zip the folder for distribution
) else (
    echo Debug executable: %BUILD_DIR%\ds_visualizer.exe
)

echo.
pause
