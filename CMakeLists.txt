cmake_minimum_required(VERSION 3.16)

project(DataStructureVisualizer
    VERSION 1.0
    LANGUAGES CXX
)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt6 Widgets module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Standard Qt project setup
qt_standard_project_setup()

# Create executable
add_executable(ds_visualizer
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    src/visualizer/ArrayVisualizer.cpp
    src/visualizer/ArrayVisualizer.h
    src/visualizer/LinkedListVisualizer.cpp
    src/visualizer/LinkedListVisualizer.h
    src/visualizer/StackVisualizer.cpp
    src/visualizer/StackVisualizer.h
    src/visualizer/QueueVisualizer.cpp
    src/visualizer/QueueVisualizer.h
    src/visualizer/TreeVisualizer.cpp
    src/visualizer/TreeVisualizer.h
    src/visualizer/GraphVisualizer.cpp
    src/visualizer/GraphVisualizer.h
    src/ds/LinkedList.h
    src/ds/Stack.h
    src/ds/Queue.h
    src/ds/Tree.h
    src/ds/DirectedUnweightedGraph.h
    src/ds/DirectedWeightedGraph.h
    src/ds/UndirectedUnweightedGraph.h
    src/ds/UndirectedWeightedGraph.h
)

# Link Qt Widgets
target_link_libraries(ds_visualizer PRIVATE Qt6::Widgets)
