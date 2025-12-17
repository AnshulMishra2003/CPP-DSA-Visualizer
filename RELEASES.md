# Release Distribution Guide

This guide explains how to create and distribute pre-built executable files on GitHub for end users.

## Why Pre-built Executables?

✅ **Users don't need to compile** - Faster setup  
✅ **No development tools required** - No CMake, Qt, compiler needed  
✅ **Just download and run** - Better user experience  
✅ **Professional distribution** - Like real software  

---

## Preparing Release Files

### Step 1: Build Release Executables

#### Windows
```bash
cd "C++ Project\cpp-ds-visualizer"
mkdir build-release
cd build-release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

#### Linux
```bash
cd cpp-ds-visualizer
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

#### macOS
```bash
cd cpp-ds-visualizer
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Step 2: Deploy with Dependencies

#### Windows - Prepare with Qt Libraries

```bash
# Navigate to build-release folder
cd build-release

# Create a distribution folder
mkdir ds_visualizer-windows

# Copy executable
copy ds_visualizer.exe ds_visualizer-windows\

# Method 1: Use Qt deployment tool (if installed)
windeployqt ds_visualizer-windows\ds_visualizer.exe

# Method 2: Manual copy (if windeployqt not available)
# Copy these DLLs from Qt\6.10.1\mingw_64\bin to ds_visualizer-windows\
# - Qt6Core.dll
# - Qt6Gui.dll  
# - Qt6Widgets.dll
#
# Create plugins/platforms folder:
# mkdir ds_visualizer-windows\plugins\platforms
# Copy qwindows.dll to plugins\platforms\

# Create zip
powershell Compress-Archive -Path ds_visualizer-windows -DestinationPath ds_visualizer-windows.zip
```

**Final structure:**
```
ds_visualizer-windows/
├── ds_visualizer.exe
├── Qt6Core.dll
├── Qt6Gui.dll
├── Qt6Widgets.dll
├── plugins/
│   └── platforms/
│       └── qwindows.dll
└── [other Qt dependencies]
```

#### Linux - Create AppImage

```bash
# Install linuxdeploy if needed
# https://github.com/linuxdeploy/linuxdeploy/releases

# Create AppImage
linuxdeploy-x86_64.AppImage --appdir AppDir --executable build-release/ds_visualizer
linuxdeploy-plugin-qt-x86_64.AppImage --appdir AppDir
appimagetool-x86_64.AppImage AppDir ds_visualizer-linux.AppImage

chmod +x ds_visualizer-linux.AppImage
```

#### macOS - Create DMG

```bash
# Create app bundle
mkdir -p ds_visualizer.app/Contents/MacOS
mkdir -p ds_visualizer.app/Contents/Resources
cp build-release/ds_visualizer ds_visualizer.app/Contents/MacOS/

# Deploy Qt libraries
macdeployqt ds_visualizer.app -dmg

# This creates ds_visualizer.dmg
```

---

## Uploading to GitHub Releases

### Method 1: Using GitHub Web Interface (Easiest)

1. **Go to Releases**
   - Navigate to: https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases

2. **Click "Draft a new release"**

3. **Fill in the form:**
   - **Tag version**: `v1.0.0` (format: vX.Y.Z)
   - **Release title**: `C++ DSA Visualizer v1.0.0`
   - **Description**: Add release notes
     ```
     ## What's New
     - Initial release
     - Complete visualization for 6 data structures
     - Force-directed graph layout
     - Cross-platform support (Windows, Linux, macOS)
     
     ## How to Use
     1. Download the appropriate file for your OS
     2. Extract/Install
     3. Run the application
     
     ## Files Included
     - Windows: Standalone executable with all dependencies
     - Linux: AppImage - extract and run
     - macOS: DMG - extract and install
     ```

4. **Upload Files** (drag and drop or click to select)
   - `ds_visualizer-windows.zip`
   - `ds_visualizer-linux.AppImage`
   - `ds_visualizer-macos.dmg`

5. **Click "Publish release"**

### Method 2: Using GitHub CLI

```bash
# Install GitHub CLI first
# https://cli.github.com/

# Create a release with files
gh release create v1.0.0 \
  ds_visualizer-windows.zip \
  ds_visualizer-linux.AppImage \
  ds_visualizer-macos.dmg \
  --title "C++ DSA Visualizer v1.0.0" \
  --notes "Initial release with complete DSA visualization"
```

### Method 3: Using Git Commands

```bash
# Tag the commit
git tag -a v1.0.0 -m "C++ DSA Visualizer v1.0.0"

# Push tag to GitHub
git push origin v1.0.0

# Then manually upload files on GitHub web interface
```

---

## User Experience Flow

### For Windows Users

1. User goes to GitHub Releases page
2. Clicks download: `ds_visualizer-windows.zip`
3. Extracts the folder
4. Double-clicks `ds_visualizer.exe`
5. ✅ Application runs immediately!

### For Linux Users

1. User downloads `ds_visualizer-linux.AppImage`
2. Right-click → Properties → Make executable
3. Double-click to run
4. ✅ Application runs immediately!

Alternative:
```bash
chmod +x ds_visualizer-linux.AppImage
./ds_visualizer-linux.AppImage
```

### For macOS Users

1. User downloads `ds_visualizer-macos.dmg`
2. Opens the DMG file
3. Drags app to Applications
4. Double-clicks from Applications
5. ✅ Application runs immediately!

---

## GitHub Release Features

After creating a release, users will see:

✅ Download links for all files  
✅ Release notes/description  
✅ Automatic zip creation for source code  
✅ Version information  
✅ Pre-release option (if needed)  

### Release Badge (Optional)

Add to your README:
```markdown
[![Latest Release](https://img.shields.io/github/v/release/AnshulMishra2003/CPP-DSA-Visualizer?style=flat-square)](https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases/latest)
```

---

## Update Process

For future versions (e.g., v1.1.0):

1. Make code changes locally
2. Build new release executables
3. Commit and push code: `git push`
4. Create new release on GitHub with new executables
5. Users download new version

---

## File Size Considerations

| Platform | Size | Notes |
|----------|------|-------|
| Windows ZIP | 80-120 MB | Includes all Qt DLLs |
| Linux AppImage | 150-200 MB | Self-contained |
| macOS DMG | 120-160 MB | Includes Qt frameworks |

**Optimization tips:**
- Use Release build (not Debug) - 3-5x smaller
- Strip debug symbols: `strip ds_visualizer`
- Compress when possible

---

## Distribution Checklist

- [ ] Build Release executables for all platforms
- [ ] Test each executable on a clean machine
- [ ] Verify all dependencies included
- [ ] Create release notes
- [ ] Test downloaded files work correctly
- [ ] Create GitHub Release (v1.0.0 or your version)
- [ ] Upload all platform executables
- [ ] Update README with download links
- [ ] Test download links work
- [ ] Announce release (optional)

---

## Example Release Page

Your release page will look like:

```
C++ DSA Visualizer v1.0.0
Latest · 2024-12-17

Complete Data Structures and Algorithms Visualizer

Features:
✨ Array, Linked List, Stack, Queue, Tree, Graph
🎨 Modern UI with animations
📊 Multiple graph layouts
🎯 Interactive controls

Download:
↓ ds_visualizer-windows.zip (95 MB)
↓ ds_visualizer-linux.AppImage (175 MB)
↓ ds_visualizer-macos.dmg (140 MB)
```

---

## Troubleshooting

**"DLL not found" on Windows:**
- Re-run windeployqt or manually add missing DLLs

**"Cannot execute" on Linux:**
- Make file executable: `chmod +x ds_visualizer-linux.AppImage`

**macOS asks to verify:**
- Go to Settings → Security & Privacy
- Allow the app to run

---

## Next Steps

1. **Build your release executables** (see instructions above)
2. **Create GitHub Release** with the files
3. **Test download and run** on each platform
4. **Update README** with download links
5. **Share with users!**

Your users can now get your app in just 30 seconds! 🚀
