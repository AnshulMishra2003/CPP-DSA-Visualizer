#!/bin/bash
# Build Script for C++ DSA Visualizer (Linux/macOS)
# This script builds the project in Release mode with all dependencies

BUILD_TYPE="Release"
BUILD_DIR="build-release"

# Parse arguments
if [ "$1" = "debug" ]; then
    BUILD_TYPE="Debug"
    BUILD_DIR="build-debug"
    echo "Building in DEBUG mode..."
else
    echo "Building in RELEASE mode..."
fi

echo ""
echo "======================================"
echo "C++ DSA Visualizer Build Script"
echo "======================================"
echo ""

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory: $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

echo ""
echo "Step 1: Running CMake configuration..."
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

echo ""
echo "Step 2: Building project..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "======================================"
echo "Build completed successfully!"
echo "======================================"
echo ""

if [ "$BUILD_TYPE" = "Release" ]; then
    echo "Executable location: $BUILD_DIR/ds_visualizer"
    echo ""
    echo "To run:"
    echo "  ./$BUILD_DIR/ds_visualizer"
    echo ""
    echo "To create AppImage:"
    echo "  linuxdeploy-x86_64.AppImage --appdir AppDir --executable $BUILD_DIR/ds_visualizer"
else
    echo "Debug executable: $BUILD_DIR/ds_visualizer"
fi

echo ""
