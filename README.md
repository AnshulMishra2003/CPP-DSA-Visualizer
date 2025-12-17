# C++ DSA Visualizer

An interactive Data Structures and Algorithms visualizer built with C++ and Qt6.

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

## Requirements

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
