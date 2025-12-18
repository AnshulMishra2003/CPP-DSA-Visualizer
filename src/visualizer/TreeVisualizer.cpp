#include "TreeVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <limits>

TreeVisualizer::TreeVisualizer(QWidget* parent)
    : QWidget(parent), highlightValue(std::numeric_limits<int>::min()) {
    // Seed with some values
    int seedVals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : seedVals) tree.insert(v);

    QVBoxLayout* main = new QVBoxLayout(this);
    main->setSpacing(15);
    main->setContentsMargins(20, 20, 20, 20);

    // Title
    infoLabel = new QLabel("\xF0\x9F\x8C\xB3 Binary Search Tree Visualizer"); // 🌳
    infoLabel->setStyleSheet(
        "font-size: 22px; font-weight: bold; padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #2ecc71, stop:1 #27ae60); "
        "border-radius: 8px; color: white;");
    infoLabel->setAlignment(Qt::AlignCenter);
    main->addWidget(infoLabel);

    // Stats row
    QHBoxLayout* stats = new QHBoxLayout();
    sizeLabel = new QLabel("Size: " + QString::number(tree.size()));
    sizeLabel->setStyleSheet("font-size: 13px; color: #2c3e50; padding: 6px; background:#ecf0f1; border-radius:5px;");
    sizeLabel->setAlignment(Qt::AlignCenter);

    heightLabel = new QLabel("Height: " + QString::number(tree.height()));
    heightLabel->setStyleSheet("font-size: 13px; color: #2c3e50; padding: 6px; background:#ecf0f1; border-radius:5px;");
    heightLabel->setAlignment(Qt::AlignCenter);

    // Min/Max label
    QString minMaxText = tree.size() > 0
        ? (QString("Min: ") + QString::number(tree.min()) + " | Max: " + QString::number(tree.max()))
        : QString("Min: - | Max: -");
    minMaxLabel = new QLabel(minMaxText);
    minMaxLabel->setStyleSheet("font-size: 13px; color: #2c3e50; padding: 6px; background:#ecf0f1; border-radius:5px;");
    minMaxLabel->setAlignment(Qt::AlignCenter);

    stats->addWidget(sizeLabel);
    stats->addWidget(heightLabel);
    stats->addWidget(minMaxLabel);
    main->addLayout(stats);

    // Controls
    controlGroup = new QGroupBox("Control Panel");
    controlGroup->setStyleSheet(
        "QGroupBox { font-size:14px; font-weight:bold; border:2px solid #2ecc71; border-radius:8px; margin-top:10px; padding-top:10px; }"
        "QGroupBox::title { left: 15px; padding: 0 5px; color:#2ecc71; }");
    QVBoxLayout* gl = new QVBoxLayout();

    QHBoxLayout* inputs = new QHBoxLayout();
    QLabel* valueLbl = new QLabel("Value:");
    valueLbl->setStyleSheet("font-size:12px; font-weight:bold; color:#2c3e50;");
    valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Enter integer value");
    valueInput->setMaximumWidth(180);
    valueInput->setStyleSheet("padding:8px; border:2px solid #bdc3c7; border-radius:5px; font-size:12px;");
    inputs->addWidget(valueLbl);
    inputs->addWidget(valueInput);
    inputs->addStretch();
    gl->addLayout(inputs);

    QString btnStyle =
        "QPushButton { padding:10px 20px; font-size:13px; font-weight:bold; border:none; border-radius:6px; color:white; background-color:%1; }"
        "QPushButton:hover { background-color:%2; }"
        "QPushButton:pressed { background-color:%3; }";

    QHBoxLayout* row1 = new QHBoxLayout();
    insertBtn = new QPushButton("➕ Insert"); insertBtn->setStyleSheet(btnStyle.arg("#27ae60", "#229954", "#1e8449"));
    deleteBtn = new QPushButton("❌ Delete"); deleteBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    searchBtn = new QPushButton("🔍 Search"); searchBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    clearBtn = new QPushButton("🗑 Clear"); clearBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    reloadBtn = new QPushButton("🔄 Reload"); reloadBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    row1->addWidget(insertBtn); row1->addWidget(deleteBtn); row1->addWidget(searchBtn); row1->addWidget(clearBtn); row1->addWidget(reloadBtn);
    gl->addLayout(row1);

    QHBoxLayout* row2 = new QHBoxLayout();
    inorderBtn = new QPushButton("Inorder"); inorderBtn->setStyleSheet(btnStyle.arg("#1abc9c", "#16a085", "#138d75"));
    preorderBtn = new QPushButton("Preorder"); preorderBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    postorderBtn = new QPushButton("Postorder"); postorderBtn->setStyleSheet(btnStyle.arg("#f39c12", "#e67e22", "#d68910"));
    levelorderBtn = new QPushButton("BFS (Levelorder)"); levelorderBtn->setStyleSheet(btnStyle.arg("#e67e22", "#d35400", "#ba4a00"));
    row2->addWidget(inorderBtn); row2->addWidget(preorderBtn); row2->addWidget(postorderBtn); row2->addWidget(levelorderBtn); row2->addStretch();
    gl->addLayout(row2);

    QHBoxLayout* row3 = new QHBoxLayout();
    playDFSBtn = new QPushButton("▶ Play DFS (Preorder)"); playDFSBtn->setStyleSheet(btnStyle.arg("#2ecc71", "#27ae60", "#1e8449"));
    playBFSBtn = new QPushButton("▶ Play BFS"); playBFSBtn->setStyleSheet(btnStyle.arg("#2980b9", "#2471a3", "#1f618d"));
    row3->addWidget(playDFSBtn); row3->addWidget(playBFSBtn); row3->addStretch();
    gl->addLayout(row3);

    controlGroup->setLayout(gl);
    main->addWidget(controlGroup);

    statusLabel = new QLabel("✅ Ready - BST initialized with sample data");
    statusLabel->setStyleSheet("font-size:13px; color:#27ae60; padding:10px; background:#d5f4e6; border-left:4px solid #27ae60; border-radius:5px;");
    main->addWidget(statusLabel);
    main->addStretch();

    connect(insertBtn, &QPushButton::clicked, this, &TreeVisualizer::onInsert);
    connect(deleteBtn, &QPushButton::clicked, this, &TreeVisualizer::onDelete);
    connect(searchBtn, &QPushButton::clicked, this, &TreeVisualizer::onSearch);
    connect(clearBtn, &QPushButton::clicked, this, &TreeVisualizer::onClear);
    connect(reloadBtn, &QPushButton::clicked, this, &TreeVisualizer::onReload);
    connect(inorderBtn, &QPushButton::clicked, this, &TreeVisualizer::onInorder);
    connect(preorderBtn, &QPushButton::clicked, this, &TreeVisualizer::onPreorder);
    connect(postorderBtn, &QPushButton::clicked, this, &TreeVisualizer::onPostorder);
    connect(levelorderBtn, &QPushButton::clicked, this, &TreeVisualizer::onLevelorder);
    connect(playDFSBtn, &QPushButton::clicked, this, &TreeVisualizer::onPlayDFS);
    connect(playBFSBtn, &QPushButton::clicked, this, &TreeVisualizer::onPlayBFS);
}

void TreeVisualizer::paintEvent(QPaintEvent* e) { QWidget::paintEvent(e); drawTree(); }

void TreeVisualizer::drawTree() {
    QPainter p(this); p.setRenderHint(QPainter::Antialiasing);
    // Compute a top offset so drawing stays below controls (raised slightly to show deeper leaves)
    int controlsBottom = 0;
    if (statusLabel && statusLabel->isVisible()) {
        controlsBottom = statusLabel->geometry().bottom();
    }
    if (controlGroup && controlGroup->isVisible() && controlGroup->geometry().bottom() > controlsBottom) {
        controlsBottom = controlGroup->geometry().bottom();
    }
    int topOffset = controlsBottom + 20; // slimmer padding below controls
    topOffset = std::max(topOffset, 140); // lowered minimum to pull tree upward
    
    int bottomMargin = 30;
    int sideMargin = 40;
    int drawHeight = height() - topOffset - bottomMargin;
    int drawWidth = width() - 2 * sideMargin;
    if (drawHeight < 80) drawHeight = 80;
    if (drawWidth < 100) drawWidth = 100;

    if (!tree.getRoot()) {
        p.setPen(QPen(QColor("#95a5a6"), 2)); p.setFont(QFont("Arial", 16, QFont::Bold));
        QRect emptyRect(sideMargin, topOffset, drawWidth, drawHeight);
        p.drawText(emptyRect, Qt::AlignCenter,
                   "⚠️ Tree is empty\n\nInsert values to build the BST");
        return;
    }
    
    // Compute scaling based on tree dimensions
    int treeHeight = tree.height();
    int treeSize = tree.size();
    
    // Estimate tree width based on size
    int estimatedWidth = std::max(200, treeSize * 60);
    int estimatedHeight = 60 + (treeHeight * 100);
    
    double scaleX = 1.0;
    double scaleY = 1.0;
    
    if (estimatedWidth > drawWidth) {
        scaleX = (double)drawWidth / (double)estimatedWidth;
        scaleX = std::max(0.2, std::min(1.0, scaleX));
    }
    
    if (estimatedHeight > drawHeight) {
        scaleY = (double)drawHeight / (double)estimatedHeight;
        scaleY = std::max(0.3, std::min(1.0, scaleY));
    }
    
    // Use minimum scale to maintain aspect ratio
    double scale = std::min(scaleX, scaleY);
    
    // Set clipping region to prevent drawing outside bounds
    p.setClipRect(sideMargin, topOffset, drawWidth, drawHeight);
    
    p.save();
    p.translate(sideMargin, topOffset);
    p.scale(scale, scale);
    
    int startY = 30; // start higher to keep bottom leaves visible
    int centerX = (int)(drawWidth / scale) / 2;
    int hGap = std::max(80, (int)(drawWidth / scale) / 5);
    drawNode(p, tree.getRoot(), centerX, startY, hGap, 0);
    
    p.restore();
}

void TreeVisualizer::drawNode(QPainter& p, BSTree::Node* n, int x, int y, int hGap, int depth) {
    if (!n) return;
    int childY = y + 100;
    int nextGap = std::max(40, hGap / 2);

    // Edges first
    if (n->left) {
        int lx = x - hGap; int ly = childY;
        p.setPen(QPen(QColor("#34495e"), 2));
        p.drawLine(x, y, lx, ly);
        drawNode(p, n->left, lx, ly, nextGap, depth + 1);
    }
    if (n->right) {
        int rx = x + hGap; int ry = childY;
        p.setPen(QPen(QColor("#34495e"), 2));
        p.drawLine(x, y, rx, ry);
        drawNode(p, n->right, rx, ry, nextGap, depth + 1);
    }

    // Node circle
    int r = 26;
    bool hi = (n->value == highlightValue);
    QColor fill = hi ? QColor("#e74c3c") : QColor("#2ecc71");
    QColor border = hi ? QColor("#c0392b") : QColor("#27ae60");

    // Shadow
    p.setBrush(QColor(0,0,0,35)); p.setPen(Qt::NoPen);
    p.drawEllipse(QPoint(x+3,y+3), r, r);

    // Circle
    p.setBrush(fill); p.setPen(QPen(border, 3));
    p.drawEllipse(QPoint(x,y), r, r);

    // Value text
    p.setPen(Qt::white); p.setFont(QFont("Arial", 12, QFont::Bold));
    p.drawText(x - r, y - r, 2*r, 2*r, Qt::AlignCenter, QString::number(n->value));
}

void TreeVisualizer::updateStatus(const QString& m, const QString& kind) {
    if (kind == "success") {
        statusLabel->setStyleSheet("font-size:13px; color:#27ae60; padding:10px; background:#d5f4e6; border-left:4px solid #27ae60; border-radius:5px;");
    } else if (kind == "error") {
        statusLabel->setStyleSheet("font-size:13px; color:#e74c3c; padding:10px; background:#fadbd8; border-left:4px solid #e74c3c; border-radius:5px;");
    } else {
        statusLabel->setStyleSheet("font-size:13px; color:#3498db; padding:10px; background:#d6eaf8; border-left:4px solid #3498db; border-radius:5px;");
    }
    statusLabel->setText(m);
    sizeLabel->setText("Size: " + QString::number(tree.size()));
    heightLabel->setText("Height: " + QString::number(tree.height()));
    if (tree.size() > 0) {
        minMaxLabel->setText("Min: " + QString::number(tree.min()) + " | Max: " + QString::number(tree.max()));
    } else {
        minMaxLabel->setText("Min: - | Max: -");
    }
}

void TreeVisualizer::onInsert() {
    bool ok; int v = valueInput->text().toInt(&ok);
    if (!ok || valueInput->text().isEmpty()) { updateStatus("Please enter a valid integer value", "error"); return; }
    if (tree.height() >= 7) { updateStatus("❌ Tree height limit reached (max 7). Cannot insert more values.", "error"); return; }
    if (!tree.insert(v)) { updateStatus("Value already exists in tree", "error"); return; }
    highlightValue = v; valueInput->clear(); updateStatus("Inserted " + QString::number(v), "success"); update();
}

void TreeVisualizer::onDelete() {
    bool ok; int v = valueInput->text().toInt(&ok);
    if (!ok || valueInput->text().isEmpty()) { updateStatus("Please enter a valid integer value", "error"); return; }
    if (!tree.remove(v)) { updateStatus("Value not found in tree", "error"); return; }
    highlightValue = std::numeric_limits<int>::min(); updateStatus("Deleted " + QString::number(v), "success"); update();
}

void TreeVisualizer::onSearch() {
    bool ok; int v = valueInput->text().toInt(&ok);
    if (!ok || valueInput->text().isEmpty()) { updateStatus("Please enter a valid integer to search", "error"); return; }
    if (tree.contains(v)) { highlightValue = v; updateStatus("Found value " + QString::number(v), "success"); }
    else { highlightValue = std::numeric_limits<int>::min(); updateStatus("Value not found", "error"); }
    update();
}

void TreeVisualizer::onClear() {
    if (tree.size() == 0) { updateStatus("Tree is already empty", "info"); return; }
    tree.clear(); highlightValue = std::numeric_limits<int>::min(); updateStatus("Cleared all nodes", "success"); update();
}

void TreeVisualizer::onReload() {
    tree.clear();
    int seedVals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : seedVals) tree.insert(v);
    highlightValue = std::numeric_limits<int>::min();
    updateStatus("BST reloaded with sample data", "success");
    update();
}

static QString joinVec(const std::vector<int>& v) {
    QString s; for (size_t i=0;i<v.size();++i){ if(i) s += ", "; s += QString::number(v[i]); } return s;
}

void TreeVisualizer::onInorder()  { startTraversalAnimation(tree.inorder(), "Inorder"); }
void TreeVisualizer::onPreorder() { startTraversalAnimation(tree.preorder(), "Preorder"); }
void TreeVisualizer::onPostorder(){ startTraversalAnimation(tree.postorder(), "Postorder"); }
void TreeVisualizer::onLevelorder(){ startTraversalAnimation(tree.levelorder(), "BFS (Levelorder)"); }

void TreeVisualizer::startTraversalAnimation(const std::vector<int>& seq, const QString& label) {
    if (traversalTimer) { traversalTimer->stop(); traversalTimer->deleteLater(); traversalTimer = nullptr; }
    traversalSeq = seq; traversalIndex = 0;
    if (traversalSeq.empty()) { updateStatus(label + ": [empty]", "info"); highlightValue = std::numeric_limits<int>::min(); update(); return; }
    updateStatus("Animating " + label + "...", "info");
    if (!traversalTimer) traversalTimer = new QTimer(this);
    traversalTimer->setInterval(600);
    connect(traversalTimer, &QTimer::timeout, this, [this, label]() mutable {
        if (traversalIndex >= (int)traversalSeq.size()) {
            traversalTimer->stop();
            statusLabel->setText(label + ": [" + joinVec(traversalSeq) + "]");
            highlightValue = std::numeric_limits<int>::min();
            update();
            return;
        }
        highlightValue = traversalSeq[traversalIndex++];
        update();
    });
    traversalTimer->start();
}

void TreeVisualizer::onPlayDFS(){ startTraversalAnimation(tree.preorder(), "DFS (Preorder)"); }
void TreeVisualizer::onPlayBFS(){ startTraversalAnimation(tree.levelorder(), "BFS (Levelorder)"); }
