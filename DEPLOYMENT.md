# Deployment Guide - C++ DSA Visualizer

This guide covers building, packaging, and distributing the C++ DSA Visualizer application.

## Quick Start - Build & Run

### Windows (MinGW)
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
./ds_visualizer.exe
```

### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
./ds_visualizer
```

---

## Release Build (Optimized)

### Windows Release
```bash
mkdir build-release
cd build-release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Linux Release
```bash
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

**Size comparison:**
- Debug: ~15-20 MB
- Release: ~3-5 MB (with optimizations)

---

## Windows Distribution

### Method 1: Simple Folder Distribution (Recommended for Testing)

1. **Create Release Build**
   ```bash
   cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
   cmake --build .
   ```

2. **Copy Executable**
   ```bash
   mkdir ds_visualizer-windows
   copy build\ds_visualizer.exe ds_visualizer-windows\
   ```

3. **Deploy Qt Libraries**
   ```bash
   # Option A: Using windeployqt (if Qt is in PATH)
   windeployqt ds_visualizer-windows\ds_visualizer.exe
   
   # Option B: Manual copy
   # Copy from Qt installation (e.g., C:\Qt\6.10.1\mingw_64\bin)
   copy Qt6Core.dll ds_visualizer-windows\
   copy Qt6Gui.dll ds_visualizer-windows\
   copy Qt6Widgets.dll ds_visualizer-windows\
   
   # Create platforms folder and copy plugin
   mkdir ds_visualizer-windows\plugins\platforms
   copy qwindows.dll ds_visualizer-windows\plugins\platforms\
   ```

4. **Create Zip for Distribution**
   ```bash
   # Compress the folder
   powershell Compress-Archive -Path ds_visualizer-windows -DestinationPath ds_visualizer-windows.zip
   ```

5. **Test on Clean Machine**
   - Unzip on different computer
   - Run `ds_visualizer.exe` to verify all dependencies are included

### Method 2: NSIS Installer

1. **Install NSIS** from https://nsis.sourceforge.io/

2. **Create installer script** (`installer.nsi`):
   ```nsis
   !include "MUI2.nsh"
   !include "x64.nsh"
   
   Name "C++ DSA Visualizer v1.0.0"
   OutFile "CPP-DSA-Visualizer-Setup.exe"
   InstallDir "$PROGRAMFILES\CPP-DSA-Visualizer"
   RequestExecutionLevel admin
   
   !insertmacro MUI_PAGE_DIRECTORY
   !insertmacro MUI_PAGE_INSTFILES
   !insertmacro MUI_LANGUAGE "English"
   
   Section "Install"
     SetOutPath "$INSTDIR"
     File "ds_visualizer-windows\*.*"
     CreateDirectory "$SMPROGRAMS\CPP-DSA-Visualizer"
     CreateShortCut "$SMPROGRAMS\CPP-DSA-Visualizer\C++ DSA Visualizer.lnk" "$INSTDIR\ds_visualizer.exe"
     CreateShortCut "$SMPROGRAMS\CPP-DSA-Visualizer\Uninstall.lnk" "$INSTDIR\uninstall.exe"
   SectionEnd
   ```

3. **Build Installer**
   ```bash
   # From NSIS installation directory
   makensis installer.nsi
   ```

### Method 3: Portable Executable with Dependencies

Use **Inno Setup** for a more user-friendly installer:

1. Download Inno Setup
2. Create setup script (`.iss` file)
3. Compile to create installer

---

## Linux Distribution

### Method 1: AppImage (Single File Distribution)

```bash
# Install tools
sudo apt install python3-pip
pip3 install linuxdeploy

# Build release
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# Create AppImage
linuxdeploy-x86_64.AppImage --appdir AppDir --executable ds_visualizer
linuxdeploy-plugin-qt-x86_64.AppImage --appdir AppDir
appimagetool-x86_64.AppImage AppDir ds_visualizer.AppImage

chmod +x ds_visualizer.AppImage
```

### Method 2: Debian Package

```bash
# Create package structure
mkdir -p deb/DEBIAN
mkdir -p deb/usr/bin
mkdir -p deb/usr/share/applications

# Copy executable
cp build-release/ds_visualizer deb/usr/bin/

# Create desktop entry
cat > deb/usr/share/applications/ds_visualizer.desktop << EOF
[Desktop Entry]
Name=C++ DSA Visualizer
Exec=/usr/bin/ds_visualizer
Type=Application
Categories=Education;Science;
Icon=application-x-executable
EOF

# Create control file
cat > deb/DEBIAN/control << EOF
Package: cpp-dsa-visualizer
Version: 1.0.0
Architecture: amd64
Maintainer: Anshul Mishra <anshul.mishra@example.com>
Description: Interactive Data Structures and Algorithms Visualizer
Depends: libqt6core6, libqt6gui6, libqt6widgets6
EOF

# Build package
dpkg-deb --build deb/ cpp-dsa-visualizer-1.0.0.deb
```

### Method 3: Snap

```bash
# Create snapcraft.yaml
cat > snap/snapcraft.yaml << EOF
name: cpp-dsa-visualizer
version: '1.0'
summary: C++ Data Structures Visualizer
description: |
  Interactive visualization tool for learning data structures and algorithms

grade: stable
confinement: strict

parts:
  cpp-dsa-visualizer:
    plugin: cmake
    source: .
    build-packages:
      - cmake
      - qt6-base-dev
      - g++

apps:
  cpp-dsa-visualizer:
    command: bin/ds_visualizer
    plugs:
      - opengl
EOF

# Build snap
snapcraft
```

---

## macOS Distribution

### Method 1: DMG (Disk Image)

```bash
# Build release
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# Create app bundle
mkdir -p ds_visualizer.app/Contents/MacOS
mkdir -p ds_visualizer.app/Contents/Resources
cp ds_visualizer ds_visualizer.app/Contents/MacOS/

# Create Info.plist
cat > ds_visualizer.app/Contents/Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>ds_visualizer</string>
    <key>CFBundleIdentifier</key>
    <string>com.anshul.dsa-visualizer</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>C++ DSA Visualizer</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0.0</string>
    <key>CFBundleVersion</key>
    <string>1</string>
</dict>
</plist>
EOF

# Deploy Qt frameworks
macdeployqt ds_visualizer.app -dmg

# Create DMG
hdiutil create -volname "C++ DSA Visualizer" -srcfolder ds_visualizer.app -ov -format UDZO ds_visualizer.dmg
```

---

## GitHub Releases Setup

### Step 1: Prepare Release Artifacts

```bash
# Create releases directory
mkdir releases

# Windows
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
windeployqt build\ds_visualizer.exe
# Zip and copy to releases/
powershell Compress-Archive -Path build -DestinationPath releases/ds_visualizer-windows.zip

# Linux
cmake -DCMAKE_BUILD_TYPE=Release ..
make
# Create AppImage or zip and copy to releases/
```

### Step 2: Create GitHub Release

```bash
# Install GitHub CLI
# Then run:
gh release create v1.0.0 \
  releases/ds_visualizer-windows.zip \
  releases/ds_visualizer-linux \
  --title "C++ DSA Visualizer v1.0.0" \
  --notes "Initial release with complete DSA visualization"
```

### Step 3: Manual Release on GitHub

1. Go to: https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases
2. Click "Draft a new release"
3. Create new tag: `v1.0.0`
4. Title: "C++ DSA Visualizer v1.0.0"
5. Description: Add release notes
6. Upload files (drag & drop)
7. Click "Publish release"

---

## Troubleshooting

### Windows Issues

**"DLL not found" errors:**
- Ensure all Qt DLLs are in the same folder or `plugins/` subdirectory
- Use `windeployqt` to automatically copy dependencies

**"Cannot find platform plugin" error:**
- Verify `plugins/platforms/qwindows.dll` exists
- Check path structure is: `./plugins/platforms/`

### Linux Issues

**Missing Qt libraries:**
```bash
# Check dependencies
ldd ./ds_visualizer

# Install missing libraries
sudo apt-get install libqt6core6 libqt6gui6 libqt6widgets6
```

**AppImage permission denied:**
```bash
chmod +x ds_visualizer.AppImage
```

### macOS Issues

**Code signing requirement:**
```bash
codesign -s - ds_visualizer.app
```

---

## Performance Tips

- **Release builds are 3-5x faster** than debug builds
- **Enable compiler optimizations**: `-DCMAKE_BUILD_TYPE=Release`
- **Strip debug symbols**: reduces binary size by 60-70%
- **Use link-time optimization (LTO)**: add `-flto` to CMake

---

## Version Management

Update version in:
1. `CMakeLists.txt`: `project(ds_visualizer VERSION 1.0.0)`
2. GitHub release tag
3. README.md version references

---

## Distribution Checklist

- [ ] Build release executable with optimizations
- [ ] Test all features on target platform
- [ ] Copy/verify all dependencies included
- [ ] Test on clean machine without dev tools
- [ ] Create installer or packaged archive
- [ ] Test installer/package
- [ ] Create release notes
- [ ] Upload to GitHub Releases
- [ ] Update README with download links
- [ ] Tag git repository with version

---

For questions or issues, open an issue on GitHub: https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/issues
