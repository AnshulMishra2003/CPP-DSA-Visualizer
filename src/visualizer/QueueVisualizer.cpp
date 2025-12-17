#include "QueueVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

QueueVisualizer::QueueVisualizer(QWidget *parent)
    : QWidget(parent), queue(15), highlightIndex(-1), lastOperation("")
{
    // Initialize with sample data
    queue.enqueue(20);
    queue.enqueue(35);
    queue.enqueue(50);
    queue.enqueue(65);
    queue.enqueue(80);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title Section
    infoLabel = new QLabel("\U0001F500 Queue Data Structure Visualizer (FIFO)");
    infoLabel->setStyleSheet(
        "font-size: 22px; "
        "font-weight: bold; "
        "padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1abc9c, stop:1 #3498db); "
        "border-radius: 8px; "
        "color: white;"
    );
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Size and Front/Rear Labels
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    sizeLabel = new QLabel("Size: " + QString::number(queue.size()) + " / " + QString::number(queue.capacity()));
    sizeLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #34495e; "
        "padding: 5px; "
        "background-color: #ecf0f1; "
        "border-radius: 5px;"
    );
    sizeLabel->setAlignment(Qt::AlignCenter);
    
    QString frontRearText = queue.isEmpty() ? "Front: - | Rear: -" : 
                           "Front: " + QString::number(queue.front()) + " | Rear: " + QString::number(queue.rear());
    frontRearLabel = new QLabel(frontRearText);
    frontRearLabel->setStyleSheet(
        "font-size: 13px; "
        "color: white; "
        "padding: 5px; "
        "background-color: #1abc9c; "
        "border-radius: 5px; "
        "font-weight: bold;"
    );
    frontRearLabel->setAlignment(Qt::AlignCenter);
    
    statsLayout->addWidget(sizeLabel);
    statsLayout->addWidget(frontRearLabel);
    mainLayout->addLayout(statsLayout);
    
    // Control Panel Group
    QGroupBox *controlGroup = new QGroupBox("Control Panel");
    controlGroup->setStyleSheet(
        "QGroupBox { "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "   border: 2px solid #1abc9c; "
        "   border-radius: 8px; "
        "   margin-top: 10px; "
        "   padding-top: 10px; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 15px; "
        "   padding: 0 5px; "
        "   color: #1abc9c; "
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
    
    enqueueBtn = new QPushButton("\u2795 Enqueue (Rear)");
    enqueueBtn->setStyleSheet(btnStyle.arg("#27ae60", "#229954", "#1e8449"));
    
    dequeueBtn = new QPushButton("\u2796 Dequeue (Front)");
    dequeueBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    frontBtn = new QPushButton("\u25C0 Front");
    frontBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    rearBtn = new QPushButton("Rear \u25B6");
    rearBtn->setStyleSheet(btnStyle.arg("#1abc9c", "#16a085", "#138d75"));
    
    buttonRow1->addWidget(enqueueBtn);
    buttonRow1->addWidget(dequeueBtn);
    buttonRow1->addWidget(frontBtn);
    buttonRow1->addWidget(rearBtn);
    
    controlLayout->addLayout(buttonRow1);
    
    QHBoxLayout *buttonRow2 = new QHBoxLayout();
    
    searchBtn = new QPushButton("\U0001F50D Search");
    searchBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    
    clearBtn = new QPushButton("\U0001F5D1 Clear");
    clearBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    
    buttonRow2->addWidget(searchBtn);
    buttonRow2->addWidget(clearBtn);
    buttonRow2->addStretch();
    
    controlLayout->addLayout(buttonRow2);
    
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);
    
    // Status Label
    statusLabel = new QLabel("\u2705 Ready - Queue initialized with sample data (FIFO - First In First Out)");
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
    connect(enqueueBtn, &QPushButton::clicked, this, &QueueVisualizer::onEnqueue);
    connect(dequeueBtn, &QPushButton::clicked, this, &QueueVisualizer::onDequeue);
    connect(frontBtn, &QPushButton::clicked, this, &QueueVisualizer::onFront);
    connect(rearBtn, &QPushButton::clicked, this, &QueueVisualizer::onRear);
    connect(searchBtn, &QPushButton::clicked, this, &QueueVisualizer::onSearch);
    connect(clearBtn, &QPushButton::clicked, this, &QueueVisualizer::onClear);
}

void QueueVisualizer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    drawQueue();
}

void QueueVisualizer::drawQueue()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    if (queue.isEmpty()) {
        painter.setPen(QPen(QColor("#95a5a6"), 2));
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "\u26A0\uFE0F Queue is Empty\n\nUse Enqueue to add elements at rear");
        return;
    }
    
    auto elements = queue.getData();
    
    // Base geometry
    int boxWidth = 80;
    int boxHeight = 70;
    int spacing = 18; // give arrows room for a visible shaft
    int marginLeft = 40;
    int marginRight = 40;
    // Compute a startY that stays below controls/status
    int topOffset = statusLabel ? statusLabel->geometry().bottom() + 12 : 120;
    int desiredStartY = height() - 250;
    int startY = desiredStartY; // will be adjusted after scale is known

    // Compute content width and scale to fit available width
    const int count = static_cast<int>(elements.size());
    int contentWidth = count > 0 ? (count * (boxWidth + spacing) - spacing) : 0;
    int availableWidth = qMax(100, width() - marginLeft - marginRight);
    double scale = contentWidth > 0 ? qMin(1.0, static_cast<double>(availableWidth) / static_cast<double>(contentWidth)) : 1.0;

    // Center scaled content horizontally within available area
    double scaledContentWidth = contentWidth * scale;
    double offsetX = marginLeft + qMax(0.0, (availableWidth - scaledContentWidth) / 2.0);

    painter.save();
    painter.translate(offsetX, 0);
    painter.scale(scale, scale);

    // After scaling, start drawing from x=0 for simplicity
    int startX = 0;

    // Ensure startY (in logical coords) is not above the topOffset
    int minStartY = static_cast<int>(topOffset / scale + 60);
    if (startY < minStartY) startY = minStartY;
    
    int logicalViewportWidth = static_cast<int>(width() / scale);
    int logicalViewportHeight = static_cast<int>(height() / scale);
    
    // Draw FRONT label (clamp x to avoid left overflow)
    painter.setPen(QColor("#3498db"));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    int frontLabelX = qMax(5, startX - 80);
    painter.drawText(frontLabelX, startY, 70, boxHeight, Qt::AlignRight | Qt::AlignVCenter, "FRONT \u25B6");
    
    // Draw elements
    for (size_t i = 0; i < elements.size(); ++i) {
        int x = startX + i * (boxWidth + spacing);
        
        // Color based on position
        QColor fillColor;
        QColor borderColor;
        
        if (i == static_cast<size_t>(highlightIndex)) {
            fillColor = QColor("#f39c12");  // Orange for highlighted
            borderColor = QColor("#e67e22");
        } else if (i == 0) {
            fillColor = QColor("#3498db");  // Blue for front
            borderColor = QColor("#2980b9");
        } else if (i == elements.size() - 1) {
            fillColor = QColor("#1abc9c");  // Green for rear
            borderColor = QColor("#16a085");
        } else {
            fillColor = QColor("#9b59b6");  // Purple for middle
            borderColor = QColor("#8e44ad");
        }
        
        // Draw shadow
        painter.setBrush(QColor(0, 0, 0, 30));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(x + 3, startY + 3, boxWidth, boxHeight, 8, 8);
        
        // Draw box
        painter.setBrush(fillColor);
        painter.setPen(QPen(borderColor, 3));
        painter.drawRoundedRect(x, startY, boxWidth, boxHeight, 8, 8);
        
        // Draw value
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(x, startY, boxWidth, boxHeight, 
                        Qt::AlignCenter, QString::number(elements[i]));
        
        // Draw position below
        painter.setPen(QColor("#2c3e50"));
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        painter.drawText(x, startY + boxHeight + 5, boxWidth, 25, 
                        Qt::AlignCenter, "pos[" + QString::number(i) + "]");
        
        // Draw arrow between elements with a visible shaft and head
        if (i < elements.size() - 1) {
            int arrowY = startY + boxHeight / 2;
            int gap = spacing;
            int headW = qMin(18, gap - 4);   // head width fits within gap
            int headH = 10;                  // head height
            int shaftEndX = x + boxWidth + gap - headW;
            painter.setPen(QPen(QColor("#34495e"), 4, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(x + boxWidth, arrowY, shaftEndX, arrowY);
            
            // Arrow head
            painter.setBrush(QColor("#34495e"));
            painter.setPen(Qt::NoPen);
            int tipX = x + boxWidth + gap;
            QPolygon arrowHead;
            arrowHead << QPoint(tipX, arrowY)
                     << QPoint(tipX - headW, arrowY - headH / 2)
                     << QPoint(tipX - headW, arrowY + headH / 2);
            painter.drawPolygon(arrowHead);
        }
        
        // Draw FRONT indicator
        if (i == 0) {
            painter.setPen(QColor("#3498db"));
            painter.setFont(QFont("Arial", 10, QFont::Bold));
            painter.drawText(x, startY - 25, boxWidth, 20, Qt::AlignCenter, "\u25BC FRONT");
        }
        
        // Draw REAR indicator
        if (i == elements.size() - 1) {
            painter.setPen(QColor("#1abc9c"));
            painter.setFont(QFont("Arial", 10, QFont::Bold));
            painter.drawText(x, startY - 25, boxWidth, 20, Qt::AlignCenter, "REAR \u25BC");
        }
    }
    
    // Removed extra REAR label on the right to avoid duplication
    
    // Draw flow direction text with dynamic width and clamping to avoid clipping
    painter.setPen(QColor("#7f8c8d"));
    QFont flowFont("Arial", 11);
    painter.setFont(flowFont);
    QString flowText = "Dequeue \u2190 FIFO Flow \u2192 Enqueue";
    QFontMetrics fm(flowFont);
    int textW = fm.horizontalAdvance(flowText) + 20; // padding
    int textH = fm.height() + 6;
    int contentCenterX = startX + (contentWidth / 2);
    int flowY = qMin(logicalViewportHeight - textH - 10, startY + boxHeight + 40);
    int flowX = qMax(0, qMin(logicalViewportWidth - textW, contentCenterX - textW / 2));
    painter.drawText(flowX, flowY, textW, textH, Qt::AlignCenter, flowText);

    painter.restore();
}

void QueueVisualizer::updateStatus(const QString &message, const QString &color)
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
    sizeLabel->setText("Size: " + QString::number(queue.size()) + " / " + QString::number(queue.capacity()));
    
    QString frontRearText = queue.isEmpty() ? "Front: - | Rear: -" : 
                           "Front: " + QString::number(queue.front()) + " | Rear: " + QString::number(queue.rear());
    frontRearLabel->setText(frontRearText);
}

void QueueVisualizer::onEnqueue()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    if (queue.isFull()) {
        updateStatus("Queue overflow! Cannot enqueue to full queue (max capacity: " + 
                    QString::number(queue.capacity()) + ")", "error");
        return;
    }
    
    queue.enqueue(value);
    highlightIndex = queue.size() - 1;
    lastOperation = "enqueue";
    updateStatus("Enqueued " + QString::number(value) + " at the rear", "success");
    
    valueInput->clear();
    update();
}

void QueueVisualizer::onDequeue()
{
    if (queue.isEmpty()) {
        updateStatus("Queue underflow! Cannot dequeue from empty queue", "error");
        return;
    }
    
    int dequeuedValue = queue.dequeue();
    highlightIndex = -1;
    lastOperation = "dequeue";
    updateStatus("Dequeued " + QString::number(dequeuedValue) + " from the front", "success");
    
    update();
}

void QueueVisualizer::onFront()
{
    if (queue.isEmpty()) {
        updateStatus("Queue is empty! Cannot get front element", "error");
        return;
    }
    
    int frontValue = queue.front();
    highlightIndex = 0;
    lastOperation = "front";
    updateStatus("Front element: " + QString::number(frontValue) + " (element not removed)", "info");
    
    update();
}

void QueueVisualizer::onRear()
{
    if (queue.isEmpty()) {
        updateStatus("Queue is empty! Cannot get rear element", "error");
        return;
    }
    
    int rearValue = queue.rear();
    highlightIndex = queue.size() - 1;
    lastOperation = "rear";
    updateStatus("Rear element: " + QString::number(rearValue) + " (element not removed)", "info");
    
    update();
}

void QueueVisualizer::onSearch()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value to search", "error");
        return;
    }
    
    int position = queue.search(value);
    
    if (position != -1) {
        highlightIndex = position;
        updateStatus("Found value " + QString::number(value) + " at position " + 
                    QString::number(position) + " from front", "success");
    } else {
        highlightIndex = -1;
        updateStatus("Value " + QString::number(value) + " not found in queue", "error");
    }
    
    update();
}

void QueueVisualizer::onClear()
{
    if (queue.isEmpty()) {
        updateStatus("Queue is already empty", "info");
        return;
    }
    
    queue.clear();
    highlightIndex = -1;
    lastOperation = "clear";
    updateStatus("All elements cleared from queue", "success");
    
    update();
}
