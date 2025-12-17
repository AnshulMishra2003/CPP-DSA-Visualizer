# C++ DSA Visualizer

An interactive Data Structures and Algorithms visualizer built with C++ and Qt6.

## ⚡ Quick Start - Download & Run

### Windows Users
**[Download Latest Release](https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases)**

1. Download `ds_visualizer-windows.zip` from releases
2. Extract the folder
3. Run `ds_visualizer.exe`
4. No installation needed!

### Linux Users
**[Download Latest Release](https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases)**

1. Download `ds_visualizer.AppImage`
2. Make it executable: `chmod +x ds_visualizer.AppImage`
3. Run: `./ds_visualizer.AppImage`

### macOS Users
**[Download Latest Release](https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases)**

1. Download `ds_visualizer-macos.dmg`
2. Open and drag to Applications
3. Run from Applications folder

---

## Features

### Data Structures Visualization
- **Array**: Dynamic array with insert, delete, and search operations
- **Linked List**: Singly linked list with node operations and traversal
- **Stack**: LIFO stack with push, pop, and peek operations
- **Queue**: FIFO queue with enqueue and dequeue operations
- **Binary Search Tree**: BST with insert, delete, and traversal (Inorder, Preorder, Postorder)
- **Graph**: Unified graph supporting:
  - Directed/Undirected
  - Weighted/Unweighted
  - BFS and DFS traversal animations
  - Multiple layout modes (Radial, Grid, Force-directed)

### Key Features
- 🎨 Modern UI with gradient styling and smooth animations
- 🔄 Real-time visualization of operations
- 📊 Multiple layout algorithms for graph visualization
- 🎯 Interactive controls for each data structure
- 📈 Step-by-step algorithm animations
- 🖱️ Scrollable viewport for large data structures

---

## Building from Source (For Developers)

If you want to build from source instead of using pre-built executables:

### Requirements

- CMake 3.16 or higher
- Qt 6.10.1 or higher
- C++17 compatible compiler
  - MinGW 13.1.0 (Windows)
  - GCC/Clang (Linux/macOS)

## Building the Project

### Windows (MinGW)
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### Linux/macOS
```bash
mkdir build
cd build
cmake ..
make
```

## Running the Application

After building, run the executable:
```bash
# Windows
./ds_visualizer.exe

# Linux/macOS
./ds_visualizer
```

## Deployment & Distribution

### Creating Release Builds

For deployment, create an optimized release build:

#### Windows (MinGW)
```bash
mkdir build-release
cd build-release
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

#### Linux/macOS
```bash
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Creating Executable Packages

#### Windows Standalone EXE with Dependencies
1. Build in Release mode (see above)
2. Copy required DLLs to the executable directory:
   - From Qt installation: `bin/Qt6Core.dll`, `bin/Qt6Gui.dll`, `bin/Qt6Widgets.dll`
   - Platform plugin: `plugins/platforms/qwindows.dll`
   
Example directory structure:
```
ds_visualizer/
├── ds_visualizer.exe
├── Qt6Core.dll
├── Qt6Gui.dll
├── Qt6Widgets.dll
└── plugins/
    └── platforms/
        └── qwindows.dll
```

3. Zip the folder for distribution

#### Creating Installer (Windows)
- Use NSIS (Nullsoft Scriptable Install System) or WiX Toolset
- Or use Qt's deployment tools: `windeployqt ds_visualizer.exe`

#### Linux AppImage
```bash
# Install linuxdeploy and linuxdeploy-plugin-qt
./linuxdeploy-x86_64.AppImage --appdir AppDir --executable build/ds_visualizer
./linuxdeploy-plugin-qt-x86_64.AppImage --appdir AppDir
./appimagetool-x86_64.AppImage AppDir ds_visualizer.AppImage
```

#### macOS App Bundle
```bash
mkdir -p ds_visualizer.app/Contents/MacOS
mkdir -p ds_visualizer.app/Contents/Resources
cp build/ds_visualizer ds_visualizer.app/Contents/MacOS/
macdeployqt ds_visualizer.app -dmg
```

### Qt Deployment Tools

#### Automatic Deployment (Windows)
```bash
# From Qt bin directory or command line
windeployqt <path-to-executable>
```

This automatically copies all required Qt libraries and plugins.

#### Automatic Deployment (Linux)
```bash
linuxdeployqt <path-to-executable> -appimage
```

### Release Checklist

- [ ] Build in Release mode with optimizations
- [ ] Test all features on target platform
- [ ] Copy all required dependencies
- [ ] Test on clean machine without development tools
- [ ] Create version file/release notes
- [ ] Sign executable (recommended for Windows)
- [ ] Create installer or package
- [ ] Test installer/package on clean system
- [ ] Upload to GitHub Releases

### GitHub Releases

To create a release on GitHub:

1. Build release executables for all platforms
2. Go to your GitHub repository → Releases → Draft a new release
3. Create a new tag (e.g., `v1.0.0`)
4. Add release notes
5. Upload compiled executables and installers
6. Publish the release

Example:
```bash
# After building, create release folder
mkdir releases
cp build-release/ds_visualizer.exe releases/ds_visualizer-windows.exe
cp build-release/ds_visualizer releases/ds_visualizer-linux
```

## Project Structure

```
cpp-ds-visualizer/
├── src/
│   ├── main.cpp                 # Application entry point
│   ├── ds/                      # Data structure implementations
│   │   ├── LinkedList.h
│   │   ├── Queue.h
│   │   ├── Stack.h
│   │   ├── Tree.h
│   │   ├── DirectedWeightedGraph.h
│   │   ├── DirectedUnweightedGraph.h
│   │   ├── UndirectedWeightedGraph.h
│   │   └── UndirectedUnweightedGraph.h
│   ├── ui/                      # User interface
│   │   ├── MainWindow.h
│   │   └── MainWindow.cpp
│   └── visualizer/              # Visualization components
│       ├── ArrayVisualizer.h/cpp
│       ├── LinkedListVisualizer.h/cpp
│       ├── QueueVisualizer.h/cpp
│       ├── StackVisualizer.h/cpp
│       ├── TreeVisualizer.h/cpp
│       └── GraphVisualizer.h/cpp
├── CMakeLists.txt
└── README.md
```

## Usage

### Array Visualizer
- Insert elements at specific indices
- Delete elements
- Search for values with visual feedback

### Linked List Visualizer
- Insert nodes at head, tail, or specific positions
- Delete nodes
- Visual traversal with arrows

### Stack Visualizer
- Push elements onto the stack
- Pop elements with animation
- Peek at top element

### Queue Visualizer
- Enqueue elements
- Dequeue with visual flow
- Full-bodied arrow indicators

### Tree Visualizer
- Insert nodes (BST property maintained)
- Delete nodes
- Animated traversals (Inorder, Preorder, Postorder)

### Graph Visualizer
- Switch between graph types
- Add vertices and edges (with weights for weighted graphs)
- BFS and DFS with step-by-step animation
- Toggle between radial and force-directed layouts
- Scrollable viewport for large graphs

## Technologies Used

- **C++17**: Core programming language
- **Qt 6**: GUI framework
- **CMake**: Build system
- **QPainter**: Custom graphics rendering

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## License

This project is open source and available for educational purposes.

## Author

Anshul Mishra

## Acknowledgments

Built with modern C++ and Qt6 for educational purposes to help students understand data structures and algorithms through visualization.
