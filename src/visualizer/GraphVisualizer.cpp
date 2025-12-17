#include "GraphVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <limits>
#include <QRandomGenerator>

GraphVisualizer::GraphVisualizer(QWidget* parent)
    : QWidget(parent), graph(UnifiedGraph::DirectedUnweighted) {
    // Initialize with sample data
    for (int i = 0; i < 6; i++) graph.addVertex();
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 6);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 5, 1);
    graph.addEdge(4, 5, 7);
    
    QVBoxLayout* main = new QVBoxLayout(this);
    main->setSpacing(15);
    main->setContentsMargins(20, 20, 20, 20);

    // Title
    infoLabel = new QLabel("🌐 Graph Visualizer - All Types (BFS & DFS)");
    infoLabel->setStyleSheet(
        "font-size: 22px; font-weight: bold; padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2980b9); "
        "border-radius: 8px; color: white;");
    infoLabel->setAlignment(Qt::AlignCenter);
    main->addWidget(infoLabel);

    // Stats row
    statsLabel = new QLabel("Vertices: 0 | Edges: 0 | Type: Directed Unweighted");
    statsLabel->setStyleSheet("font-size: 13px; color: #2c3e50; padding: 6px; background:#ecf0f1; border-radius:5px;");
    statsLabel->setAlignment(Qt::AlignCenter);
    main->addWidget(statsLabel);

    // Vertical scroll (used only for force layout)
    vScroll = new QScrollBar(Qt::Vertical, this);
    vScroll->hide();
    connect(vScroll, &QScrollBar::valueChanged, this, [this](int v){ scrollOffsetY = v; update(); });

    // Controls - Compact 3-line layout
    controlGroup = new QGroupBox("Control Panel");
    controlGroup->setStyleSheet(
        "QGroupBox { font-size:14px; font-weight:bold; border:2px solid #3498db; border-radius:8px; margin-top:10px; padding-top:5px; }"
        "QGroupBox::title { left: 15px; padding: 0 5px; color:#3498db; }");
    QVBoxLayout* gl = new QVBoxLayout();
    gl->setSpacing(5);

    // Button style for all buttons
    QString btnStyle =
        "QPushButton { padding:6px 12px; font-size:11px; font-weight:bold; border:none; border-radius:5px; color:white; background-color:%1; }"
        "QPushButton:hover { background-color:%2; }"
        "QPushButton:pressed { background-color:%3; }";

    // LINE 1: Graph Type + Layout Controls + Vertex Operations
    QHBoxLayout* line1 = new QHBoxLayout();
    QLabel* typeLbl = new QLabel("Type:");
    typeLbl->setStyleSheet("font-size:11px; font-weight:bold; color:#2c3e50;");
    typeCombo = new QComboBox();
    typeCombo->addItem("Directed Unweighted");
    typeCombo->addItem("Directed Weighted");
    typeCombo->addItem("Undirected Unweighted");
    typeCombo->addItem("Undirected Weighted");
    typeCombo->setMinimumWidth(150);
    typeCombo->setMaximumWidth(180);
    typeCombo->setStyleSheet(
        "QComboBox { padding: 6px 10px; border: 2px solid #3498db; border-radius: 5px; "
        "font-size: 11px; font-weight: bold; color: #2c3e50; background: white; }"
        "QComboBox:hover { border-color: #2980b9; background: #ecf0f1; }"
        "QComboBox::drop-down { border: none; width: 25px; }"
        "QComboBox::down-arrow { image: url(none); width: 0px; height: 0px; "
        "border-left: 4px solid transparent; border-right: 4px solid transparent; "
        "border-top: 5px solid #2c3e50; margin-right: 6px; }"
        "QComboBox QAbstractItemView { border: 2px solid #3498db; border-radius: 5px; "
        "background: white; selection-background-color: #3498db; selection-color: white; "
        "font-size: 11px; padding: 4px; }");
    
    toggleLayoutBtn = new QPushButton("Force: Off");
    toggleLayoutBtn->setCheckable(true);
    toggleLayoutBtn->setStyleSheet(
        "QPushButton { padding: 6px 12px; font-size: 11px; font-weight: bold; border: 2px solid #3498db; border-radius: 5px; color: #2c3e50; background: #ecf6fd; }"
        "QPushButton:checked { background: #3498db; color: white; border-color: #2980b9; }"
    );
    fitViewBtn = new QPushButton("Fit");
    fitViewBtn->setStyleSheet(
        "QPushButton { padding: 6px 12px; font-size: 11px; font-weight: bold; border: 2px solid #16a085; border-radius: 5px; color: #2c3e50; background: #e8f8f5; }"
        "QPushButton:hover { background: #d0f2eb; }"
    );
    
    QLabel* vLbl = new QLabel("Vertex:");
    vLbl->setStyleSheet("font-size:11px; font-weight:bold; color:#2c3e50;");
    vertexInput = new QLineEdit();
    vertexInput->setPlaceholderText("Count");
    vertexInput->setMaximumWidth(60);
    vertexInput->setText("5");
    vertexInput->setStyleSheet("padding:6px; border:2px solid #bdc3c7; border-radius:4px; font-size:11px;");
    addVertexBtn = new QPushButton("➕ Add");
    addVertexBtn->setStyleSheet(btnStyle.arg("#27ae60", "#229954", "#1e8449"));
    
    line1->addWidget(typeLbl);
    line1->addWidget(typeCombo);
    line1->addSpacing(10);
    line1->addWidget(toggleLayoutBtn);
    line1->addWidget(fitViewBtn);
    line1->addSpacing(10);
    line1->addWidget(vLbl);
    line1->addWidget(vertexInput);
    line1->addWidget(addVertexBtn);
    line1->addStretch();
    gl->addLayout(line1);

    // LINE 2: Edge Operations + Search
    QHBoxLayout* line2 = new QHBoxLayout();
    QLabel* eLbl = new QLabel("Edge:");
    eLbl->setStyleSheet("font-size:11px; font-weight:bold; color:#2c3e50;");
    edgeU = new QLineEdit();
    edgeU->setPlaceholderText("From");
    edgeU->setMaximumWidth(50);
    edgeU->setStyleSheet("padding:6px; border:2px solid #bdc3c7; border-radius:4px; font-size:11px;");
    edgeV = new QLineEdit();
    edgeV->setPlaceholderText("To");
    edgeV->setMaximumWidth(50);
    edgeV->setStyleSheet("padding:6px; border:2px solid #bdc3c7; border-radius:4px; font-size:11px;");
    edgeW = new QLineEdit();
    edgeW->setPlaceholderText("Weight");
    edgeW->setMaximumWidth(50);
    edgeW->setText("1");
    edgeW->setStyleSheet("padding:6px; border:2px solid #bdc3c7; border-radius:4px; font-size:11px;");
    addEdgeBtn = new QPushButton("➕ Add");
    addEdgeBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    QLabel* searchLbl = new QLabel("Search:");
    searchLbl->setStyleSheet("font-size:11px; font-weight:bold; color:#2c3e50;");
    searchVertexInput = new QLineEdit();
    searchVertexInput->setPlaceholderText("Vertex ID");
    searchVertexInput->setMaximumWidth(70);
    searchVertexInput->setStyleSheet("padding:6px; border:2px solid #bdc3c7; border-radius:4px; font-size:11px;");
    searchVertexBtn = new QPushButton("🔍");
    searchVertexBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    line2->addWidget(eLbl);
    line2->addWidget(edgeU);
    line2->addWidget(edgeV);
    line2->addWidget(edgeW);
    line2->addWidget(addEdgeBtn);
    line2->addSpacing(10);
    line2->addWidget(searchLbl);
    line2->addWidget(searchVertexInput);
    line2->addWidget(searchVertexBtn);
    line2->addStretch();
    gl->addLayout(line2);
    
    // Hide weight field initially for unweighted graph (default is DirectedUnweighted)
    edgeW->setVisible(false);

    // LINE 3: Action Buttons
    QHBoxLayout* line3 = new QHBoxLayout();
    clearBtn = new QPushButton("🗑 Clear");
    clearBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    bfsBtn = new QPushButton("📊 BFS");
    bfsBtn->setStyleSheet(btnStyle.arg("#f39c12", "#e67e22", "#d68910"));
    dfsBtn = new QPushButton("📈 DFS");
    dfsBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    playBFSBtn = new QPushButton("▶ Play BFS");
    playBFSBtn->setStyleSheet(btnStyle.arg("#2ecc71", "#27ae60", "#1e8449"));
    playDFSBtn = new QPushButton("▶ Play DFS");
    playDFSBtn->setStyleSheet(btnStyle.arg("#1abc9c", "#16a085", "#138d75"));
    line3->addWidget(clearBtn);
    line3->addWidget(bfsBtn);
    line3->addWidget(dfsBtn);
    line3->addWidget(playBFSBtn);
    line3->addWidget(playDFSBtn);
    line3->addStretch();
    gl->addLayout(line3);

    controlGroup->setLayout(gl);
    main->addWidget(controlGroup);

    statusLabel = new QLabel("✅ Ready - Graph initialized with sample data!");
    statusLabel->setStyleSheet("font-size:13px; color:#27ae60; padding:10px; background:#d5f4e6; border-left:4px solid #27ae60; border-radius:5px;");
    main->addWidget(statusLabel);
    main->addStretch();

    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GraphVisualizer::onTypeChanged);
    connect(addVertexBtn, &QPushButton::clicked, this, &GraphVisualizer::onAddVertex);
    connect(addEdgeBtn, &QPushButton::clicked, this, &GraphVisualizer::onAddEdge);
    connect(clearBtn, &QPushButton::clicked, this, &GraphVisualizer::onClear);
    connect(searchVertexBtn, &QPushButton::clicked, this, &GraphVisualizer::onSearchVertex);
    connect(bfsBtn, &QPushButton::clicked, this, &GraphVisualizer::onBFS);
    connect(dfsBtn, &QPushButton::clicked, this, &GraphVisualizer::onDFS);
    connect(playBFSBtn, &QPushButton::clicked, this, &GraphVisualizer::onPlayBFS);
    connect(playDFSBtn, &QPushButton::clicked, this, &GraphVisualizer::onPlayDFS);
    connect(toggleLayoutBtn, &QPushButton::clicked, this, &GraphVisualizer::onToggleLayoutMode);
    connect(fitViewBtn, &QPushButton::clicked, this, &GraphVisualizer::onFitView);
}

void GraphVisualizer::onTypeChanged(int idx) {
    UnifiedGraph::Type newType = (UnifiedGraph::Type)idx;
    if (newType != graph.getType()) {
        graph = UnifiedGraph(newType);
        nodePositions.clear();
        selectedStart = -1;
        
        // Show/hide weight field based on graph type
        bool isWeighted = (newType == UnifiedGraph::DirectedWeighted || newType == UnifiedGraph::UndirectedWeighted);
        edgeW->setVisible(isWeighted);
        
        // Add sample data for each graph type
        if (newType == UnifiedGraph::DirectedUnweighted) {
            for (int i = 0; i < 6; i++) graph.addVertex();
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(1, 3);
            graph.addEdge(2, 3);
            graph.addEdge(2, 4);
            graph.addEdge(3, 5);
            graph.addEdge(4, 5);
            updateStatus("Directed Unweighted graph with sample data", "success");
        } else if (newType == UnifiedGraph::DirectedWeighted) {
            for (int i = 0; i < 6; i++) graph.addVertex();
            graph.addEdge(0, 1, 5);
            graph.addEdge(0, 2, 3);
            graph.addEdge(1, 3, 6);
            graph.addEdge(2, 3, 2);
            graph.addEdge(2, 4, 4);
            graph.addEdge(3, 5, 1);
            graph.addEdge(4, 5, 7);
            updateStatus("Directed Weighted graph with sample data", "success");
        } else if (newType == UnifiedGraph::UndirectedUnweighted) {
            for (int i = 0; i < 5; i++) graph.addVertex();
            graph.addEdge(0, 1);
            graph.addEdge(0, 2);
            graph.addEdge(1, 2);
            graph.addEdge(1, 3);
            graph.addEdge(2, 4);
            graph.addEdge(3, 4);
            updateStatus("Undirected Unweighted graph with sample data", "success");
        } else if (newType == UnifiedGraph::UndirectedWeighted) {
            for (int i = 0; i < 5; i++) graph.addVertex();
            graph.addEdge(0, 1, 8);
            graph.addEdge(0, 2, 4);
            graph.addEdge(1, 2, 2);
            graph.addEdge(1, 3, 5);
            graph.addEdge(2, 4, 3);
            graph.addEdge(3, 4, 6);
            updateStatus("Undirected Weighted graph with sample data", "success");
        }
        
            computeLayout(); // Ensure layout is updated
        update();
    }
}

void GraphVisualizer::onAddVertex() {
    bool ok;
    int count = vertexInput->text().toInt(&ok);
    if (!ok || count <= 0) {
        updateStatus("Enter a positive integer for vertex count.", "error");
        return;
    }
    int currentCount = graph.vertexCount();
    if (currentCount + count > 30) {
        int allowedCount = 30 - currentCount;
        updateStatus("❌ Graph node limit reached (max 30). Can only add " + QString::number(allowedCount) + " more node(s).", "error");
        return;
    }
    int startIdx = currentCount;
    for (int i = 0; i < count; i++) {
        graph.addVertex();
    }
    computeLayout();
    updateStatus("Added " + QString::number(count) + " vertices (IDs " + QString::number(startIdx) + "-" + QString::number(startIdx + count - 1) + ")", "success");
    update();
}

void GraphVisualizer::onAddEdge() {
    bool okU, okV;
    int u = edgeU->text().toInt(&okU);
    int v = edgeV->text().toInt(&okV);
    
    if (!okU || !okV || u < 0 || v < 0 || u >= graph.vertexCount() || v >= graph.vertexCount()) {
        updateStatus("Invalid edge: check vertex IDs.", "error");
        return;
    }
    
    // Check if graph is weighted
    bool isWeighted = (graph.getType() == UnifiedGraph::DirectedWeighted || graph.getType() == UnifiedGraph::UndirectedWeighted);
    int w = 1; // Default weight for unweighted graphs
    
    if (isWeighted) {
        bool okW;
        w = edgeW->text().toInt(&okW);
        if (!okW) {
            updateStatus("Invalid weight value.", "error");
            return;
        }
    }
    
    graph.addEdge(u, v, w);
    
    if (isWeighted) {
        updateStatus("Edge added: " + QString::number(u) + " → " + QString::number(v) + " (w=" + QString::number(w) + ")", "success");
    } else {
        updateStatus("Edge added: " + QString::number(u) + " → " + QString::number(v), "success");
    }
    
    edgeU->clear();
    edgeV->clear();
    if (isWeighted) {
        edgeW->setText("1");
    }
    computeLayout(); // Ensure layout is updated
    update();
}

void GraphVisualizer::onClear() {
    if (graph.vertexCount() == 0) {
        updateStatus("Graph is already empty.", "info");
        return;
    }
    graph.clear();
    nodePositions.clear();
    selectedStart = -1;
    updateStatus("Graph cleared.", "success");
    update();
}

void GraphVisualizer::onBFS() {
    if (graph.vertexCount() == 0) {
        updateStatus("Graph is empty.", "error");
        return;
    }
    int start = (selectedStart >= 0 && selectedStart < graph.vertexCount()) ? selectedStart : 0;
    auto seq = graph.bfs(start);
    QString result = "BFS from " + QString::number(start) + ": [";
    for (size_t i = 0; i < seq.size(); i++) {
        if (i > 0) result += ", ";
        result += QString::number(seq[i]);
    }
    result += "]";
    updateStatus(result, "info");
    update();
}

void GraphVisualizer::onDFS() {
    if (graph.vertexCount() == 0) {
        updateStatus("Graph is empty.", "error");
        return;
    }
    int start = (selectedStart >= 0 && selectedStart < graph.vertexCount()) ? selectedStart : 0;
    auto seq = graph.dfs(start);
    QString result = "DFS from " + QString::number(start) + ": [";
    for (size_t i = 0; i < seq.size(); i++) {
        if (i > 0) result += ", ";
        result += QString::number(seq[i]);
    }
    result += "]";
    updateStatus(result, "info");
    update();
}

void GraphVisualizer::startTraversalAnimation(const std::vector<int>& seq, const QString& label) {
    if (traversalTimer) {
        traversalTimer->stop();
        traversalTimer->deleteLater();
        traversalTimer = nullptr;
    }
    traversalSeq = seq;
    traversalIndex = 0;
    if (traversalSeq.empty()) {
        updateStatus(label + ": [empty]", "info");
        selectedStart = -1;
        update();
        return;
    }
    updateStatus("Animating " + label + "...", "info");
    traversalTimer = new QTimer(this);
    traversalTimer->setInterval(600);
    connect(traversalTimer, &QTimer::timeout, this, [this, label]() {
        if (traversalIndex >= (int)traversalSeq.size()) {
            traversalTimer->stop();
            QString result = label + ": [";
            for (size_t i = 0; i < traversalSeq.size(); i++) {
                if (i > 0) result += ", ";
                result += QString::number(traversalSeq[i]);
            }
            result += "]";
            statusLabel->setText(result);
            selectedStart = -1;
            update();
            return;
        }
        selectedStart = traversalSeq[traversalIndex++];
        update();
    });
    traversalTimer->start();
}

void GraphVisualizer::onPlayBFS() {
    if (graph.vertexCount() == 0) {
        updateStatus("Graph is empty.", "error");
        return;
    }
    int start = 0;
    auto seq = graph.bfs(start);
    startTraversalAnimation(seq, "BFS from " + QString::number(start));
}

void GraphVisualizer::onPlayDFS() {
    if (graph.vertexCount() == 0) {
        updateStatus("Graph is empty.", "error");
        return;
    }
    int start = 0;
    auto seq = graph.dfs(start);
    startTraversalAnimation(seq, "DFS from " + QString::number(start));
}

void GraphVisualizer::onSearchVertex() {
    bool ok;
    int vertexId = searchVertexInput->text().toInt(&ok);
    
    if (!ok || searchVertexInput->text().isEmpty()) {
        updateStatus("Please enter a valid vertex ID to search", "error");
        highlightedVertex = -1;
        update();
        return;
    }
    
    if (vertexId < 0 || vertexId >= graph.vertexCount()) {
        updateStatus("Vertex ID " + QString::number(vertexId) + " not found (valid range: 0-" + 
                    QString::number(graph.vertexCount() - 1) + ")", "error");
        highlightedVertex = -1;
        update();
        return;
    }
    
    highlightedVertex = vertexId;
    searchVertexInput->clear();
    updateStatus("Found vertex " + QString::number(vertexId), "success");
    update();
}

void GraphVisualizer::onToggleLayoutMode() {
    useForceLayout = !useForceLayout;
    toggleLayoutBtn->setChecked(useForceLayout);
    toggleLayoutBtn->setText(useForceLayout ? "Force: On" : "Force: Off");
    nodePositions.clear();
    computeLayout();
    updateStatus(useForceLayout ? "Force-directed layout enabled" : "Radial/grid layout enabled", "info");
    update();
}

void GraphVisualizer::onFitView() {
    nodePositions.clear();
    computeLayout();
    updateStatus("Layout recomputed to fit view", "info");
    update();
}

void GraphVisualizer::computeCircularLayout() {
    nodePositions.clear();
    int n = graph.vertexCount();
    if (n == 0) return;

    // Calculate control panel bottom with extra buffer
    int controlsBottom = 0;
    if (controlGroup && controlGroup->isVisible()) {
        controlsBottom = controlGroup->geometry().bottom();
    }
    if (statusLabel && statusLabel->isVisible() && statusLabel->geometry().bottom() > controlsBottom) {
        controlsBottom = statusLabel->geometry().bottom();
    }
    
    // Add substantial top offset to ensure drawing area starts well below controls
    int topOffset = controlsBottom + 50;
    if (topOffset < 200) topOffset = 200; // Minimum offset from top
    
    int bottomMargin = 40;
    int sideMargin = 60;
    
    int drawHeight = height() - topOffset - bottomMargin;
    int drawWidth = width() - 2 * sideMargin;
    
    // Ensure minimum draw area
    if (drawHeight < 150) drawHeight = 150;
    if (drawWidth < 150) drawWidth = 150;

    // For graphs up to 30 nodes, use scattered grid layout for better edge visibility
    if (n <= 30) {
        int cols = (n <= 4) ? 2 : (n <= 9) ? 3 : (n <= 16) ? 4 : (n <= 25) ? 5 : 6;
        int rows = (n + cols - 1) / cols;
        
        double cellWidth = drawWidth / (double)cols;
        double cellHeight = drawHeight / (double)rows;
        
        // Add randomness variation that decreases with node count
        double randomFactor = std::max(0.15, 0.35 - (n / 100.0));
        
        int idx = 0;
        for (int row = 0; row < rows && idx < n; row++) {
            for (int col = 0; col < cols && idx < n; col++) {
                // Stagger positions for organic look
                double offsetX = (col % 2 == 0) ? cellWidth * randomFactor : cellWidth * (randomFactor + 0.1);
                double offsetY = (row % 2 == 0) ? cellHeight * (randomFactor + 0.1) : cellHeight * randomFactor;
                
                double x = sideMargin + col * cellWidth + cellWidth / 2 + offsetX;
                double y = topOffset + row * cellHeight + cellHeight / 2 + offsetY;
                
                // Clamp to drawing area with tighter margins
                x = std::max(sideMargin + 25.0, std::min(x, (double)(width() - sideMargin - 25)));
                y = std::max(topOffset + 25.0, std::min(y, (double)(topOffset + drawHeight - 25)));
                
                nodePositions.emplace_back(x, y);
                idx++;
            }
        }
        return;
    }

    // For larger graphs, use multi-ring radial layout to avoid overlap
    double centerX = drawWidth / 2.0 + sideMargin;
    double centerY = topOffset + drawHeight / 2.0;

    int maxPerRing = 22; // spread nodes across rings
    int ringCount = (n + maxPerRing - 1) / maxPerRing;
    double baseRadius = std::min(drawWidth, drawHeight) / 2.0 - 90;
    if (baseRadius < 120) baseRadius = 120;
    double ringSpacing = std::max(70.0, baseRadius / std::max(1, ringCount));

    int placed = 0;
    for (int ring = 0; ring < ringCount && placed < n; ++ring) {
        int nodesThisRing = std::min(maxPerRing, n - placed);
        double radius = (ring + 1) * ringSpacing;
        double jitter = std::max(0.0, 12.0 - ring * 2.0); // less jitter on outer rings
        for (int j = 0; j < nodesThisRing; ++j) {
            double angle = 2.0 * M_PI * j / nodesThisRing - M_PI / 2;
            double x = centerX + radius * cos(angle) + ((j % 2 == 0) ? jitter : -jitter);
            double y = centerY + radius * sin(angle) + ((j % 3 == 0) ? jitter * 0.6 : -jitter * 0.4);
            nodePositions.emplace_back(x, y);
            ++placed;
        }
    }
}

void GraphVisualizer::computeForceLayout() {
    nodePositions.clear();
    int n = graph.vertexCount();
    if (n == 0) return;

    int controlsBottom = 0;
    if (controlGroup && controlGroup->isVisible()) controlsBottom = controlGroup->geometry().bottom();
    if (statusLabel && statusLabel->isVisible() && statusLabel->geometry().bottom() > controlsBottom) controlsBottom = statusLabel->geometry().bottom();

    int topOffset = std::max(200, controlsBottom + 50);
    int bottomMargin = 40;
    int sideMargin = 60;
    int drawHeight = std::max(200, height() - topOffset - bottomMargin);
    int drawWidth = std::max(200, width() - 2 * sideMargin);

    // Init positions roughly on a circle with slight jitter
    double cx = drawWidth / 2.0 + sideMargin;
    double cy = topOffset + drawHeight / 2.0;
    double radius = std::min(drawWidth, drawHeight) * 0.35;
    if (radius < 120) radius = 120;
    nodePositions.reserve(n);
    for (int i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * i / n;
        int jitterX = QRandomGenerator::global()->bounded(-20, 21);
        int jitterY = QRandomGenerator::global()->bounded(-20, 21);
        double rx = static_cast<double>(jitterX);
        double ry = static_cast<double>(jitterY);
        nodePositions.emplace_back(cx + radius * cos(angle) + rx, cy + radius * sin(angle) + ry);
    }

    // Fruchterman-Reingold style relaxation
    double area = (double)drawWidth * (double)drawHeight;
    double k = std::sqrt(area / std::max(1, n));
    int iterations = std::clamp(80 + n * 2, 80, 220);
    double cooling = std::max(drawWidth, drawHeight) * 0.06;

    std::vector<NodePos> disp(n, NodePos(0, 0));

    for (int it = 0; it < iterations; ++it) {
        std::fill(disp.begin(), disp.end(), NodePos(0, 0));

        // Repulsive forces
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dx = nodePositions[i].x - nodePositions[j].x;
                double dy = nodePositions[i].y - nodePositions[j].y;
                double dist = std::sqrt(dx * dx + dy * dy) + 0.01;
                double force = (k * k) / dist;
                double fx = force * dx / dist;
                double fy = force * dy / dist;
                disp[i].x += fx; disp[i].y += fy;
                disp[j].x -= fx; disp[j].y -= fy;
            }
        }

        // Attractive forces along edges
        for (int u = 0; u < graph.vertexCount(); ++u) {
            for (const auto& e : graph.neighbors(u)) {
                int v = e.to;
                if (v == u || v >= n) continue;
                double dx = nodePositions[u].x - nodePositions[v].x;
                double dy = nodePositions[u].y - nodePositions[v].y;
                double dist = std::sqrt(dx * dx + dy * dy) + 0.01;
                double force = (dist * dist) / k;
                double fx = force * dx / dist;
                double fy = force * dy / dist;
                disp[u].x -= fx; disp[u].y -= fy;
                disp[v].x += fx; disp[v].y += fy;
            }
        }

        // Apply displacement with cooling and clamp
        double temp = cooling * (1.0 - (double)it / iterations);
        for (int i = 0; i < n; ++i) {
            double dx = disp[i].x;
            double dy = disp[i].y;
            double len = std::sqrt(dx * dx + dy * dy);
            if (len > 0) {
                double limit = std::min(temp, len);
                dx = dx / len * limit;
                dy = dy / len * limit;
            }
            nodePositions[i].x = std::clamp(nodePositions[i].x + dx, (double)sideMargin + 25.0, (double)(width() - sideMargin - 25));
            nodePositions[i].y = std::clamp(nodePositions[i].y + dy, (double)topOffset + 25.0, (double)(topOffset + drawHeight - 25));
        }
    }
}

void GraphVisualizer::computeLayout() {
    if (useForceLayout) computeForceLayout();
    else computeCircularLayout();
}

void GraphVisualizer::paintEvent(QPaintEvent* e) {
    QWidget::paintEvent(e);
    drawGraph();
}

void GraphVisualizer::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    // Compute layout when widget is first shown with correct dimensions
    if (nodePositions.empty() || (int)nodePositions.size() != graph.vertexCount()) {
        QTimer::singleShot(10, this, [this]() {
            computeLayout();
            update();
        });
    }
}

void GraphVisualizer::drawGraph() {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Calculate control panel bottom
    int controlsBottom = 0;
    if (controlGroup && controlGroup->isVisible()) {
        controlsBottom = controlGroup->geometry().bottom();
    }
    if (statusLabel && statusLabel->isVisible() && statusLabel->geometry().bottom() > controlsBottom) {
        controlsBottom = statusLabel->geometry().bottom();
    }
    
    int topOffset = controlsBottom + 50;
    if (topOffset < 200) topOffset = 200;
    
    int bottomMargin = 40;
    int drawHeight = height() - topOffset - bottomMargin;
    if (drawHeight < 150) drawHeight = 150;
    int extraHeight = 0;
    if (useForceLayout) {
        // allow vertical scrolling space proportional to node count
        extraHeight = std::max(0, graph.vertexCount() * 18 - drawHeight / 2);
    }
    int totalHeight = drawHeight + extraHeight;

    // Configure scrollbar for force layout only
    if (useForceLayout) {
        vScroll->setGeometry(width() - 18, topOffset, 16, drawHeight);
        vScroll->setRange(0, std::max(0, totalHeight - drawHeight));
        vScroll->setPageStep(drawHeight);
        vScroll->setSingleStep(40);
        vScroll->show();
        scrollOffsetY = vScroll->value();
    } else {
        vScroll->hide();
        scrollOffsetY = 0;
    }

    // Clip to drawing viewport so controls are never overdrawn
    p.save();
    p.setClipRect(0, topOffset, width(), drawHeight);
    p.translate(0, -scrollOffsetY);

    // Draw background within content space; clip keeps it inside viewport
    p.fillRect(0, topOffset, width(), totalHeight, QColor("#f8f9fa"));
    p.setPen(QPen(QColor("#dfe6e9"), 1));
    p.drawRect(0, topOffset, width() - 1, totalHeight);

    if (graph.vertexCount() == 0) {
        p.setPen(QPen(QColor("#95a5a6"), 2));
        p.setFont(QFont("Arial", 16, QFont::Bold));
        QRect emptyRect(0, topOffset, width(), totalHeight);
        p.drawText(emptyRect, Qt::AlignCenter, "⚠️ Graph is empty\n\nAdd vertices and edges to begin");
        p.restore();
        return;
    }

    if (nodePositions.empty() || (int)nodePositions.size() != graph.vertexCount()) {
        computeLayout();
    }

    // Draw edges with better visibility
    bool isWeighted = (graph.getType() == UnifiedGraph::DirectedWeighted || graph.getType() == UnifiedGraph::UndirectedWeighted);
    bool isDirected = (graph.getType() == UnifiedGraph::DirectedUnweighted || graph.getType() == UnifiedGraph::DirectedWeighted);

    // Draw edges with thicker lines for better visibility
    p.setPen(QPen(QColor("#2c3e50"), 3, Qt::SolidLine));
    p.setRenderHint(QPainter::Antialiasing);
    
    for (int u = 0; u < graph.vertexCount(); u++) {
        for (const auto& e : graph.neighbors(u)) {
            int v = e.to;
            if (!isDirected && u > v) continue; // Avoid drawing undirected edges twice
            if ((int)nodePositions.size() <= std::max(u, v)) continue;

            double x1 = nodePositions[u].x;
            double y1 = nodePositions[u].y;
            double x2 = nodePositions[v].x;
            double y2 = nodePositions[v].y;

            // Draw shadow for edge
            p.setPen(QPen(QColor(0, 0, 0, 40), 4, Qt::SolidLine));
            p.drawLine((int)x1 + 1, (int)y1 + 1, (int)x2 + 1, (int)y2 + 1);
            
            // Draw main edge line
            p.setPen(QPen(QColor("#2c3e50"), 3, Qt::SolidLine));
            p.drawLine((int)x1, (int)y1, (int)x2, (int)y2);

            // Draw arrow for directed edges
            if (isDirected && u != v) {
                double dx = x2 - x1;
                double dy = y2 - y1;
                double len = sqrt(dx * dx + dy * dy);
                if (len > 0) {
                    dx /= len;
                    dy /= len;
                    // Shorten arrow to stop at node edge
                    double arrowX = x2 - 20 * dx;
                    double arrowY = y2 - 20 * dy;
                    double angle = atan2(dy, dx);
                    int arrowSize = 10;
                    int x_end = (int)arrowX;
                    int y_end = (int)arrowY;
                    int x_left = x_end - (int)(arrowSize * cos(angle - 0.5));
                    int y_left = y_end - (int)(arrowSize * sin(angle - 0.5));
                    int x_right = x_end - (int)(arrowSize * cos(angle + 0.5));
                    int y_right = y_end - (int)(arrowSize * sin(angle + 0.5));
                    
                    QPolygon arrowPoly;
                    arrowPoly << QPoint(x_end, y_end) << QPoint(x_left, y_left) << QPoint(x_right, y_right);
                    p.setBrush(QColor("#2c3e50"));
                    p.setPen(QPen(QColor("#2c3e50"), 2));
                    p.drawPolygon(arrowPoly);
                }
            }

            // Draw weight if weighted
            if (isWeighted) {
                double midX = (x1 + x2) / 2;
                double midY = (y1 + y2) / 2;
                
                // Draw background circle for weight
                p.setBrush(QColor(255, 255, 255, 220));
                p.setPen(QPen(QColor("#e74c3c"), 2));
                p.drawEllipse(QPoint((int)midX, (int)midY), 15, 15);
                
                // Draw weight text
                p.setPen(QPen(QColor("#e74c3c")));
                p.setFont(QFont("Arial", 9, QFont::Bold));
                p.drawText((int)midX - 15, (int)midY - 15, 30, 30, Qt::AlignCenter, QString::number(e.weight));
            }
        }
    }

    // Draw nodes with smaller dynamic size based on vertex count
    int n = graph.vertexCount();
    int r = 16; // Reduced base size
    int fontSize = 9;
    
    if (n > 6) { r = 14; fontSize = 8; }
    if (n > 12) { r = 12; fontSize = 7; }
    if (n > 20) { r = 10; fontSize = 7; }
    if (n > 30) { r = 9; fontSize = 6; }
    if (n > 40) { r = 8; fontSize = 6; }
    if (n > 60) { r = 7; fontSize = 5; }
    
    for (int i = 0; i < n; i++) {
        if ((int)nodePositions.size() <= i) continue;
        int x = (int)nodePositions[i].x;
        int y = (int)nodePositions[i].y;

        bool isHighlighted = (i == selectedStart || i == highlightedVertex);
        QColor fill = isHighlighted ? QColor("#e74c3c") : QColor("#3498db");
        QColor border = isHighlighted ? QColor("#c0392b") : QColor("#2980b9");

        // Shadow
        p.setBrush(QColor(0, 0, 0, 35));
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPoint(x + 2, y + 2), r, r);

        // Circle
        p.setBrush(fill);
        p.setPen(QPen(border, 2));
        p.drawEllipse(QPoint(x, y), r, r);

        // Text
        p.setPen(Qt::white);
        p.setFont(QFont("Arial", fontSize, QFont::Bold));
        p.drawText(x - r, y - r, 2 * r, 2 * r, Qt::AlignCenter, QString::number(i));
    }

    p.restore();
}

void GraphVisualizer::updateStatus(const QString& msg, const QString& kind) {
    if (kind == "success") {
        statusLabel->setStyleSheet("font-size:13px; color:#27ae60; padding:10px; background:#d5f4e6; border-left:4px solid #27ae60; border-radius:5px;");
    } else if (kind == "error") {
        statusLabel->setStyleSheet("font-size:13px; color:#e74c3c; padding:10px; background:#fadbd8; border-left:4px solid #e74c3c; border-radius:5px;");
    } else {
        statusLabel->setStyleSheet("font-size:13px; color:#3498db; padding:10px; background:#d6eaf8; border-left:4px solid #3498db; border-radius:5px;");
    }
    statusLabel->setText(msg);
    
    QString typeStr;
    switch (graph.getType()) {
        case UnifiedGraph::DirectedUnweighted: typeStr = "Directed Unweighted"; break;
        case UnifiedGraph::DirectedWeighted: typeStr = "Directed Weighted"; break;
        case UnifiedGraph::UndirectedUnweighted: typeStr = "Undirected Unweighted"; break;
        case UnifiedGraph::UndirectedWeighted: typeStr = "Undirected Weighted"; break;
    }
    statsLabel->setText("Vertices: " + QString::number(graph.vertexCount()) + " | Type: " + typeStr);
}
