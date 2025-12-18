#include "StackVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

StackVisualizer::StackVisualizer(QWidget *parent)
    : QWidget(parent), stack(20), highlightIndex(-1), lastOperation("")
{
    // Initialize with sample data
    stack.push(15);
    stack.push(30);
    stack.push(45);
    stack.push(60);
    stack.push(75);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title Section
    infoLabel = new QLabel("\U0001F4DA Stack Data Structure Visualizer (LIFO)");
    infoLabel->setStyleSheet(
        "font-size: 22px; "
        "font-weight: bold; "
        "padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #f39c12, stop:1 #e74c3c); "
        "border-radius: 8px; "
        "color: white;"
    );
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Size and Top Labels
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    sizeLabel = new QLabel("Size: " + QString::number(stack.size()) + " / " + QString::number(stack.capacity()));
    sizeLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #34495e; "
        "padding: 5px; "
        "background-color: #ecf0f1; "
        "border-radius: 5px;"
    );
    sizeLabel->setAlignment(Qt::AlignCenter);
    
    topLabel = new QLabel("Top: " + (stack.isEmpty() ? "Empty" : QString::number(stack.peek())));
    topLabel->setStyleSheet(
        "font-size: 13px; "
        "color: white; "
        "padding: 5px; "
        "background-color: #e74c3c; "
        "border-radius: 5px; "
        "font-weight: bold;"
    );
    topLabel->setAlignment(Qt::AlignCenter);
    
    statsLayout->addWidget(sizeLabel);
    statsLayout->addWidget(topLabel);
    mainLayout->addLayout(statsLayout);
    
    // Control Panel Group
    QGroupBox *controlGroup = new QGroupBox("Control Panel");
    controlGroup->setStyleSheet(
        "QGroupBox { "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "   border: 2px solid #f39c12; "
        "   border-radius: 8px; "
        "   margin-top: 10px; "
        "   padding-top: 10px; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 15px; "
        "   padding: 0 5px; "
        "   color: #f39c12; "
        "}"
    );
    
    QVBoxLayout *controlLayout = new QVBoxLayout();
    
    // Input Section
    QHBoxLayout *inputLayout = new QHBoxLayout();
    
    QLabel *valueLabel = new QLabel("Value:");
    valueLabel->setStyleSheet("font-size: 12px; font-weight: bold; color: #2c3e50;");
    valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Enter integer value");
    valueInput->setMaximumWidth(150);
    valueInput->setStyleSheet(
        "padding: 8px; "
        "border: 2px solid #bdc3c7; "
        "border-radius: 5px; "
        "font-size: 12px;"
    );
    
    inputLayout->addWidget(valueLabel);
    inputLayout->addWidget(valueInput);
    inputLayout->addStretch();
    
    controlLayout->addLayout(inputLayout);
    
    // Buttons Section
    QString btnStyle = 
        "QPushButton { "
        "   padding: 10px 20px; "
        "   font-size: 13px; "
        "   font-weight: bold; "
        "   border: none; "
        "   border-radius: 6px; "
        "   color: white; "
        "   background-color: %1; "
        "} "
        "QPushButton:hover { "
        "   background-color: %2; "
        "} "
        "QPushButton:pressed { "
        "   background-color: %3; "
        "}";
    
    QHBoxLayout *buttonRow1 = new QHBoxLayout();
    
    pushBtn = new QPushButton("\u2B06 Push");
    pushBtn->setStyleSheet(btnStyle.arg("#27ae60", "#229954", "#1e8449"));
    
    popBtn = new QPushButton("\u2B07 Pop");
    popBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    peekBtn = new QPushButton("\U0001F441 Peek");
    peekBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    searchBtn = new QPushButton("\U0001F50D Search");
    searchBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    
    clearBtn = new QPushButton("\U0001F5D1 Clear");
    clearBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    
    reloadBtn = new QPushButton("\U0001F504 Reload");
    reloadBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    buttonRow1->addWidget(pushBtn);
    buttonRow1->addWidget(popBtn);
    buttonRow1->addWidget(peekBtn);
    buttonRow1->addWidget(searchBtn);
    buttonRow1->addWidget(clearBtn);
    buttonRow1->addWidget(reloadBtn);
    
    controlLayout->addLayout(buttonRow1);
    
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);
    
    // Status Label
    statusLabel = new QLabel("\u2705 Ready - Stack initialized with sample data (LIFO - Last In First Out)");
    statusLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #27ae60; "
        "padding: 10px; "
        "background-color: #d5f4e6; "
        "border-left: 4px solid #27ae60; "
        "border-radius: 5px;"
    );
    mainLayout->addWidget(statusLabel);
    
    // Visualization Area
    mainLayout->addStretch();
    
    // Connect signals
    connect(pushBtn, &QPushButton::clicked, this, &StackVisualizer::onPush);
    connect(popBtn, &QPushButton::clicked, this, &StackVisualizer::onPop);
    connect(peekBtn, &QPushButton::clicked, this, &StackVisualizer::onPeek);
    connect(searchBtn, &QPushButton::clicked, this, &StackVisualizer::onSearch);
    connect(clearBtn, &QPushButton::clicked, this, &StackVisualizer::onClear);
    connect(reloadBtn, &QPushButton::clicked, this, &StackVisualizer::onReload);
}

void StackVisualizer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    drawStack();
}

void StackVisualizer::drawStack()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Compute drawing area below controls/status to avoid overlap
    int topOffset = statusLabel ? statusLabel->geometry().bottom() + 12 : 120;
    int bottomMargin = 24;
    int drawAreaTop = topOffset;
    int drawAreaBottom = height() - bottomMargin;
    int drawAreaHeight = qMax(50, drawAreaBottom - drawAreaTop);
    
    int containerWidth = 200;
    int containerX = width() / 2 - containerWidth / 2;
    int elementHeight = 50;
    
    if (stack.isEmpty()) {
        // Draw empty container centered within draw area
        int emptyHeight = qMin(300, drawAreaHeight - 40);
        int emptyTop = drawAreaTop + (drawAreaHeight - emptyHeight) / 2;
        painter.setPen(QPen(QColor("#bdc3c7"), 3));
        painter.setBrush(QColor(255, 255, 255, 50));
        painter.drawRect(containerX, emptyTop, containerWidth, emptyHeight);
        
        painter.setPen(QColor("#95a5a6"));
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(containerX, emptyTop, containerWidth, emptyHeight, 
                        Qt::AlignCenter, "\u26A0\uFE0F Stack is Empty\n\nUse Push to add elements");
        
        // Draw base just above the bottom of draw area
        int baseY = drawAreaBottom - 10;
        painter.setPen(QPen(QColor("#34495e"), 5));
        painter.drawLine(containerX - 20, baseY, containerX + containerWidth + 20, baseY);
        return;
    }
    
    auto elements = stack.getData();
    int maxVisible = 10;
    int visibleCount = qMin(static_cast<int>(elements.size()), maxVisible);
    
    // Compute container and vertical scaling to stay within draw area
    int containerHeight = visibleCount * elementHeight + 20;
    double scaleY = 1.0;
    if (containerHeight + 30 > drawAreaHeight) {
        scaleY = static_cast<double>(drawAreaHeight - 30) / static_cast<double>(containerHeight);
        scaleY = qMax(0.3, qMin(1.0, scaleY));
    }
    painter.save();
    painter.scale(1.0, scaleY);
    int logicalBottom = static_cast<int>(drawAreaBottom / scaleY);
    int containerY = logicalBottom - 20; // leave room for bottom label/base
    
    // Draw container outline
    painter.setPen(QPen(QColor("#34495e"), 3));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(containerX, containerY - containerHeight, containerWidth, containerHeight);
    
    // Draw elements from bottom to top
    int startIdx = qMax(0, static_cast<int>(elements.size()) - maxVisible);
    for (int i = startIdx; i < static_cast<int>(elements.size()); ++i) {
        int displayIdx = i - startIdx;
        int y = containerY - (displayIdx + 1) * elementHeight - 10;
        
        // Determine color
        QColor fillColor;
        QColor borderColor;
        
        if (i == static_cast<int>(elements.size()) - 1) {
            // Top element (most recently pushed)
            fillColor = QColor("#e74c3c");
            borderColor = QColor("#c0392b");
        } else if (i == highlightIndex) {
            fillColor = QColor("#f39c12");
            borderColor = QColor("#e67e22");
        } else {
            // Gradient from bottom (old) to top (new)
            int intensity = 100 + (displayIdx * 155 / visibleCount);
            fillColor = QColor(52, 152, intensity);
            borderColor = QColor(41, 128, intensity - 30);
        }
        
        // Draw shadow
        painter.setBrush(QColor(0, 0, 0, 30));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(containerX + 8, y + 3, containerWidth - 16, elementHeight - 6, 6, 6);
        
        // Draw element
        painter.setBrush(fillColor);
        painter.setPen(QPen(borderColor, 2));
        painter.drawRoundedRect(containerX + 5, y, containerWidth - 10, elementHeight - 6, 6, 6);
        
        // Draw value
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(containerX + 5, y, containerWidth - 10, elementHeight - 6, 
                        Qt::AlignCenter, QString::number(elements[i]));
        
        // Draw index (clamp x to avoid left overflow)
        painter.setPen(QColor("#2c3e50"));
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        int indexX = qMax(5, containerX - 45);
        painter.drawText(indexX, y, 40, elementHeight - 6, 
                        Qt::AlignRight | Qt::AlignVCenter, QString::number(i));
        
        // Draw TOP indicator for top element (clamp x to avoid right overflow)
        if (i == static_cast<int>(elements.size()) - 1) {
            painter.setPen(QColor("#e74c3c"));
            painter.setFont(QFont("Arial", 12, QFont::Bold));
            int logicalViewportWidth = static_cast<int>(width() / 1.0); // no horizontal scale in Stack
            int topIndicatorX = qMin(logicalViewportWidth - 60, containerX + containerWidth + 10);
            painter.drawText(topIndicatorX, y, 50, elementHeight - 6, 
                           Qt::AlignLeft | Qt::AlignVCenter, "TOP \u25C0");
        }
    }
    
    // Draw base
    painter.setPen(QPen(QColor("#34495e"), 5));
    painter.drawLine(containerX - 20, containerY, containerX + containerWidth + 20, containerY);
    
    // Draw BOTTOM label (positioned just below the base line)
    painter.setPen(QColor("#34495e"));
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.drawText(containerX, containerY + 8, containerWidth, 20, Qt::AlignCenter, "BOTTOM");
    
    // Show if there are more elements
    if (elements.size() > maxVisible) {
        painter.setPen(QColor("#7f8c8d"));
        painter.setFont(QFont("Arial", 10));
        int hiddenCount = elements.size() - maxVisible;
        painter.drawText(containerX, containerY - containerHeight - 25, containerWidth, 20, 
                        Qt::AlignCenter, "..." + QString::number(hiddenCount) + " more below");
    }

    painter.restore();
}

void StackVisualizer::updateStatus(const QString &message, const QString &color)
{
    QString icon;
    
    if (color == "success") {
        icon = "\u2705";
        statusLabel->setStyleSheet(
            "font-size: 13px; "
            "color: #27ae60; "
            "padding: 10px; "
            "background-color: #d5f4e6; "
            "border-left: 4px solid #27ae60; "
            "border-radius: 5px;"
        );
    } else if (color == "error") {
        icon = "\u274C";
        statusLabel->setStyleSheet(
            "font-size: 13px; "
            "color: #e74c3c; "
            "padding: 10px; "
            "background-color: #fadbd8; "
            "border-left: 4px solid #e74c3c; "
            "border-radius: 5px;"
        );
    } else if (color == "info") {
        icon = "\u2139\uFE0F";
        statusLabel->setStyleSheet(
            "font-size: 13px; "
            "color: #3498db; "
            "padding: 10px; "
            "background-color: #d6eaf8; "
            "border-left: 4px solid #3498db; "
            "border-radius: 5px;"
        );
    }
    
    statusLabel->setText(icon + " " + message);
    sizeLabel->setText("Size: " + QString::number(stack.size()) + " / " + QString::number(stack.capacity()));
    topLabel->setText("Top: " + (stack.isEmpty() ? "Empty" : QString::number(stack.peek())));
}

void StackVisualizer::onPush()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    if (stack.isFull()) {
        updateStatus("Stack overflow! Cannot push to full stack (max capacity: " + 
                    QString::number(stack.capacity()) + ")", "error");
        return;
    }
    
    stack.push(value);
    highlightIndex = stack.size() - 1;
    lastOperation = "push";
    updateStatus("Pushed " + QString::number(value) + " onto the stack (TOP)", "success");
    
    valueInput->clear();
    update();
}

void StackVisualizer::onPop()
{
    if (stack.isEmpty()) {
        updateStatus("Stack underflow! Cannot pop from empty stack", "error");
        return;
    }
    
    int poppedValue = stack.pop();
    highlightIndex = -1;
    lastOperation = "pop";
    updateStatus("Popped " + QString::number(poppedValue) + " from the stack", "success");
    
    update();
}

void StackVisualizer::onPeek()
{
    if (stack.isEmpty()) {
        updateStatus("Stack is empty! Cannot peek", "error");
        return;
    }
    
    int topValue = stack.peek();
    highlightIndex = stack.size() - 1;
    lastOperation = "peek";
    updateStatus("Top element: " + QString::number(topValue) + " (element not removed)", "info");
    
    update();
}

void StackVisualizer::onSearch()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value to search", "error");
        return;
    }
    
    int distance = stack.search(value);
    
    if (distance != -1) {
        highlightIndex = stack.size() - 1 - distance;
        updateStatus("Found value " + QString::number(value) + " at distance " + 
                    QString::number(distance) + " from top", "success");
    } else {
        highlightIndex = -1;
        updateStatus("Value " + QString::number(value) + " not found in stack", "error");
    }
    
    update();
}

void StackVisualizer::onClear()
{
    if (stack.isEmpty()) {
        updateStatus("Stack is already empty", "info");
        return;
    }
    
    stack.clear();
    highlightIndex = -1;
    lastOperation = "clear";
    updateStatus("All elements cleared from stack", "success");
    
    update();
}

void StackVisualizer::onReload()
{
    stack.clear();
    stack.push(15);
    stack.push(30);
    stack.push(45);
    stack.push(60);
    stack.push(75);
    highlightIndex = -1;
    lastOperation = "reload";
    updateStatus("Stack reloaded with sample data", "success");
    update();
}
