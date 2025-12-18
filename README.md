# C++ DSA Visualizer

An interactive Data Structures and Algorithms visualizer built with C++ and Qt6.

## ⚡ Quick Start - Download & Run

### Windows (prebuilt)
**[Download Latest Release](https://github.com/AnshulMishra2003/CPP-DSA-Visualizer/releases)**

1) Grab `CPP-DSA-Visualizer-v1.0.0-windows.zip`
2) Extract it
3) Run `ds_visualizer.exe` inside the extracted folder (do **not** move the `platforms/` subfolder)
4) Works on Windows 10/11 (64-bit) without installing Qt

### macOS (build locally on a Mac)
No macOS binary is shipped. Build on a Mac with Qt 6:
```bash
cmake -B build-macos -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$HOME/Qt/6.10.1/macos/lib/cmake"
cmake --build build-macos --config Release
$HOME/Qt/6.10.1/macos/bin/macdeployqt build-macos/ds_visualizer.app -dmg
```
Distribute the generated `build-macos/ds_visualizer.dmg` to Mac users.

### Linux
Build from source with your distro’s Qt 6:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/ds_visualizer
```


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

## Building from Source (developers)

Requirements:
- CMake ≥ 3.16
- Qt 6.10.1 (or newer) matching your compiler
- C++17 toolchain (MinGW 13.1 on Windows, clang/gcc on macOS/Linux)

Windows (MinGW):
```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build --config Release
```

Linux/macOS:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Run after build:
```bash
# Windows
./build/ds_visualizer.exe
# Linux/macOS
./build/ds_visualizer
```

## Packaging for distribution

### Windows (already provided as ZIP)
If you rebuild locally and need a fresh ZIP:
```bash
cmake -B build-release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --config Release
& "C:/Qt/6.10.1/mingw_64/bin/windeployqt.exe" --release --compiler-runtime build-release/ds_visualizer.exe
```
Ensure `ds_visualizer.exe`, Qt6*.dll, and `platforms/qwindows.dll` stay together; then zip the folder.

### macOS bundle (local build on Mac)
```bash
cmake -B build-macos -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$HOME/Qt/6.10.1/macos/lib/cmake"
cmake --build build-macos --config Release
$HOME/Qt/6.10.1/macos/bin/macdeployqt build-macos/ds_visualizer.app -dmg
```
Ship `ds_visualizer.dmg` to Mac users.

### Linux
Build from source with your distro’s Qt; optionally create an AppImage using linuxdeployqt.

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
