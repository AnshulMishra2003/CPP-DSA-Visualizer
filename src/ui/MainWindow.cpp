#include "MainWindow.h"
#include "../visualizer/ArrayVisualizer.h"
#include "../visualizer/LinkedListVisualizer.h"
#include "../visualizer/StackVisualizer.h"
#include "../visualizer/QueueVisualizer.h"
#include "../visualizer/TreeVisualizer.h"
#include "../visualizer/GraphVisualizer.h"
#include <QTabWidget>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("C++ Data Structure Visualizer");
    resize(1200, 750);
    
    // Set window style
    setStyleSheet("QMainWindow { background-color: #f5f6fa; }");
    
    // Create tab widget
    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet(
        "QTabWidget::pane { "
        "   border: 2px solid #dfe6e9; "
        "   border-radius: 8px; "
        "   background-color: white; "
        "} "
        "QTabBar::tab { "
        "   background-color: #b2bec3; "
        "   color: #2d3436; "
        "   padding: 12px 25px; "
        "   margin-right: 5px; "
        "   border-top-left-radius: 8px; "
        "   border-top-right-radius: 8px; "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "} "
        "QTabBar::tab:selected { "
        "   background-color: #0984e3; "
        "   color: white; "
        "} "
        "QTabBar::tab:hover { "
        "   background-color: #74b9ff; "
        "   color: white; "
        "}"
    );
    
    // Create visualizers
    ArrayVisualizer *arrayVis = new ArrayVisualizer(this);
    LinkedListVisualizer *listVis = new LinkedListVisualizer(this);
    StackVisualizer *stackVis = new StackVisualizer(this);
    QueueVisualizer *queueVis = new QueueVisualizer(this);
    TreeVisualizer *treeVis = new TreeVisualizer(this);
    GraphVisualizer *graphVis = new GraphVisualizer(this);
    
    // Add tabs
    tabWidget->addTab(arrayVis, "\U0001F4CA Array");
    tabWidget->addTab(listVis, "\U0001F517 Linked List");
    tabWidget->addTab(stackVis, "\U0001F4DA Stack");
    tabWidget->addTab(queueVis, "\U0001F500 Queue");
    tabWidget->addTab(treeVis, "\U0001F333 Tree");
    tabWidget->addTab(graphVis, "\U0001F30F Graph");
    
    setCentralWidget(tabWidget);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
}
