#include "LinkedListVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

LinkedListVisualizer::LinkedListVisualizer(QWidget *parent)
    : QWidget(parent), highlightIndex(-1)
{
    // Initialize with sample data
    list.insertAtEnd(10);
    list.insertAtEnd(25);
    list.insertAtEnd(40);
    list.insertAtEnd(55);
    list.insertAtEnd(70);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title Section
    infoLabel = new QLabel("\U0001F517 Linked List Data Structure Visualizer");
    infoLabel->setStyleSheet(
        "font-size: 22px; "
        "font-weight: bold; "
        "color: #2c3e50; "
        "padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #e74c3c, stop:1 #9b59b6); "
        "border-radius: 8px; "
        "color: white;"
    );
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Size Label
    sizeLabel = new QLabel("List Size: " + QString::number(list.size()) + " | Type: Singly Linked List");
    sizeLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #34495e; "
        "padding: 5px; "
        "background-color: #ecf0f1; "
        "border-radius: 5px;"
    );
    sizeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(sizeLabel);
    
    // Control Panel Group
    QGroupBox *controlGroup = new QGroupBox("Control Panel");
    controlGroup->setStyleSheet(
        "QGroupBox { "
        "   font-size: 14px; "
        "   font-weight: bold; "
        "   border: 2px solid #e74c3c; "
        "   border-radius: 8px; "
        "   margin-top: 10px; "
        "   padding-top: 10px; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 15px; "
        "   padding: 0 5px; "
        "   color: #e74c3c; "
        "}"
    );
    
    QVBoxLayout *controlLayout = new QVBoxLayout();
    
    // Input Section
    QHBoxLayout *inputLayout = new QHBoxLayout();
    
    QLabel *valueLabel = new QLabel("Value:");
    valueLabel->setStyleSheet("font-size: 12px; font-weight: bold; color: #2c3e50;");
    valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Enter integer value");
    valueInput->setMaximumWidth(120);
    valueInput->setStyleSheet(
        "padding: 8px; "
        "border: 2px solid #bdc3c7; "
        "border-radius: 5px; "
        "font-size: 12px;"
    );
    
    QLabel *positionLabel = new QLabel("Position:");
    positionLabel->setStyleSheet("font-size: 12px; font-weight: bold; color: #2c3e50;");
    positionInput = new QSpinBox();
    positionInput->setMinimum(0);
    positionInput->setMaximum(99);
    positionInput->setValue(0);
    positionInput->setMaximumWidth(100);
    positionInput->setStyleSheet(
        "padding: 8px; "
        "border: 2px solid #bdc3c7; "
        "border-radius: 5px; "
        "font-size: 12px;"
    );
    
    inputLayout->addWidget(valueLabel);
    inputLayout->addWidget(valueInput);
    inputLayout->addSpacing(20);
    inputLayout->addWidget(positionLabel);
    inputLayout->addWidget(positionInput);
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
    
    // Row 1: Insert Operations
    QHBoxLayout *buttonRow1 = new QHBoxLayout();
    
    insertBeginBtn = new QPushButton("\u25C0 Insert Head");
    insertBeginBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    insertEndBtn = new QPushButton("Insert Tail \u25B6");
    insertEndBtn->setStyleSheet(btnStyle.arg("#1abc9c", "#16a085", "#138d75"));
    
    insertPosBtn = new QPushButton("\u2795 Insert at Position");
    insertPosBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    
    buttonRow1->addWidget(insertBeginBtn);
    buttonRow1->addWidget(insertEndBtn);
    buttonRow1->addWidget(insertPosBtn);
    
    controlLayout->addLayout(buttonRow1);
    
    // Row 2: Delete Operations
    QHBoxLayout *buttonRow2 = new QHBoxLayout();
    
    deleteBeginBtn = new QPushButton("\u274C Delete Head");
    deleteBeginBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    deleteEndBtn = new QPushButton("Delete Tail \u274C");
    deleteEndBtn->setStyleSheet(btnStyle.arg("#e67e22", "#d35400", "#ba4a00"));
    
    deletePosBtn = new QPushButton("\U0001F5D1 Delete at Position");
    deletePosBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    
    buttonRow2->addWidget(deleteBeginBtn);
    buttonRow2->addWidget(deleteEndBtn);
    buttonRow2->addWidget(deletePosBtn);
    
    controlLayout->addLayout(buttonRow2);
    
    // Row 3: Utility Operations
    QHBoxLayout *buttonRow3 = new QHBoxLayout();
    
    searchBtn = new QPushButton("\U0001F50D Search");
    searchBtn->setStyleSheet(btnStyle.arg("#f39c12", "#e67e22", "#d68910"));
    
    reverseBtn = new QPushButton("\U0001F504 Reverse");
    reverseBtn->setStyleSheet(btnStyle.arg("#34495e", "#2c3e50", "#1c2833"));
    
    clearBtn = new QPushButton("\U0001F6AE Clear All");
    clearBtn->setStyleSheet(btnStyle.arg("#c0392b", "#a93226", "#922b21"));
    
    reloadBtn = new QPushButton("\U0001F504 Reload");
    reloadBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    buttonRow3->addWidget(searchBtn);
    buttonRow3->addWidget(reverseBtn);
    buttonRow3->addWidget(clearBtn);
    buttonRow3->addWidget(reloadBtn);
    buttonRow3->addStretch();
    
    controlLayout->addLayout(buttonRow3);
    
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);
    
    // Status Label
    statusLabel = new QLabel("\u2705 Ready - Linked List initialized with sample data");
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
    connect(insertBeginBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onInsertBeginning);
    connect(insertEndBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onInsertEnd);
    connect(insertPosBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onInsertPosition);
    connect(deleteBeginBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onDeleteBeginning);
    connect(deleteEndBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onDeleteEnd);
    connect(deletePosBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onDeletePosition);
    connect(searchBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onSearch);
    connect(reverseBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onReverse);
    connect(clearBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onClear);
    connect(reloadBtn, &QPushButton::clicked, this, &LinkedListVisualizer::onReload);
}

void LinkedListVisualizer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    drawLinkedList();
}

void LinkedListVisualizer::drawLinkedList()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    if (list.isEmpty()) {
        painter.setPen(QPen(QColor("#95a5a6"), 2));
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "\u26A0\uFE0F Linked List is Empty\n\nAdd nodes using Insert operations");
        return;
    }
    
    auto nodes = list.toVector();
    
    // Base geometry
    int nodeWidth = 80;
    int nodeHeight = 60;
    int arrowLength = 40;
    int spacing = arrowLength + 10;
    int marginLeft = 40;
    int marginRight = 40;
    // Compute a startY that stays below controls/status
    int topOffset = statusLabel ? statusLabel->geometry().bottom() + 12 : 120;
    int desiredStartY = height() - 220;
    int startY = desiredStartY; // adjusted after scale known

    // Compute content width and scale uniformly to fit horizontally
    const int count = static_cast<int>(nodes.size());
    int contentWidth = count > 0 ? (count * (nodeWidth + spacing) - spacing) : 0;
    int availableWidth = qMax(100, width() - marginLeft - marginRight);
    double scale = contentWidth > 0 ? qMin(1.0, static_cast<double>(availableWidth) / static_cast<double>(contentWidth)) : 1.0;

    // Center scaled content horizontally
    double scaledContentWidth = contentWidth * scale;
    double offsetX = marginLeft + qMax(0.0, (availableWidth - scaledContentWidth) / 2.0);

    painter.save();
    painter.translate(offsetX, 0);
    painter.scale(scale, scale);

    int startX = 0;
    
    // Ensure startY (in logical coords) is not above the topOffset
    int minStartY = static_cast<int>(topOffset / scale + 70); // allow HEAD label above node
    if (startY < minStartY) startY = minStartY;
    
    int logicalViewportWidth = static_cast<int>(width() / scale);
    int logicalViewportHeight = static_cast<int>(height() / scale);
    
    // Draw HEAD label (clamp y to stay within bounds)
    painter.setPen(QColor("#e74c3c"));
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    int headLabelY = qMax(5, startY - 30);
    painter.drawText(startX, headLabelY, nodeWidth, 20, Qt::AlignCenter, "HEAD");
    
    // Draw nodes
    for (size_t i = 0; i < nodes.size(); ++i) {
        int x = startX + i * (nodeWidth + spacing);
        
        // Color based on state
        QColor fillColor;
        QColor borderColor;
        
        if (i == static_cast<size_t>(highlightIndex)) {
            fillColor = QColor("#e74c3c");  // Red for highlighted
            borderColor = QColor("#c0392b");
        } else if (i == 0) {
            fillColor = QColor("#3498db");  // Blue for head
            borderColor = QColor("#2980b9");
        } else if (i == nodes.size() - 1) {
            fillColor = QColor("#1abc9c");  // Green for tail
            borderColor = QColor("#16a085");
        } else {
            fillColor = QColor("#9b59b6");  // Purple for middle
            borderColor = QColor("#8e44ad");
        }
        
        // Draw shadow
        painter.setBrush(QColor(0, 0, 0, 30));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(x + 3, startY + 3, nodeWidth, nodeHeight, 8, 8);
        
        // Draw node box
        painter.setBrush(fillColor);
        painter.setPen(QPen(borderColor, 3));
        painter.drawRoundedRect(x, startY, nodeWidth, nodeHeight, 8, 8);
        
        // Draw value
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(x, startY, nodeWidth, nodeHeight, 
                        Qt::AlignCenter, QString::number(nodes[i]));
        
        // Draw position below
        painter.setPen(QColor("#2c3e50"));
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        painter.drawText(x, startY + nodeHeight + 5, nodeWidth, 25, 
                        Qt::AlignCenter, "pos[" + QString::number(i) + "]");
        
        // Draw arrow to next node
        if (i < nodes.size() - 1) {
            int arrowStartX = x + nodeWidth;
            int arrowStartY = startY + nodeHeight / 2;
            int arrowEndX = arrowStartX + spacing;
            int arrowEndY = arrowStartY;
            
            // Arrow line
            painter.setPen(QPen(QColor("#34495e"), 3));
            painter.drawLine(arrowStartX, arrowStartY, arrowEndX, arrowEndY);
            
            // Arrow head
            QPolygon arrowHead;
            arrowHead << QPoint(arrowEndX, arrowEndY)
                     << QPoint(arrowEndX - 10, arrowEndY - 5)
                     << QPoint(arrowEndX - 10, arrowEndY + 5);
            painter.setBrush(QColor("#34495e"));
            painter.drawPolygon(arrowHead);
        } else {
            // Draw NULL at the end (clamp x to avoid right overflow)
            painter.setPen(QColor("#95a5a6"));
            painter.setFont(QFont("Arial", 11, QFont::Bold));
            int nullX = qMin(logicalViewportWidth - 60, x + nodeWidth + 10);
            painter.drawText(nullX, startY + nodeHeight / 2 - 10, 50, 20, 
                           Qt::AlignLeft, "NULL");
        }
    }
    
    // Draw TAIL label (clamp y to avoid bottom overflow)
    if (!nodes.empty()) {
        int lastX = startX + (nodes.size() - 1) * (nodeWidth + spacing);
        painter.setPen(QColor("#1abc9c"));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        int tailLabelY = qMin(logicalViewportHeight - 25, startY + nodeHeight + 35);
        painter.drawText(lastX, tailLabelY, nodeWidth, 20, Qt::AlignCenter, "TAIL");
    }

    painter.restore();
}

void LinkedListVisualizer::updateStatus(const QString &message, const QString &color)
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
    sizeLabel->setText("List Size: " + QString::number(list.size()) + " | Type: Singly Linked List");
}

void LinkedListVisualizer::onInsertBeginning()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    list.insertAtBeginning(value);
    highlightIndex = 0;
    updateStatus("Inserted " + QString::number(value) + " at the beginning (HEAD)", "success");
    
    valueInput->clear();
    update();
}

void LinkedListVisualizer::onInsertEnd()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    list.insertAtEnd(value);
    highlightIndex = list.size() - 1;
    updateStatus("Inserted " + QString::number(value) + " at the end (TAIL)", "success");
    
    valueInput->clear();
    update();
}

void LinkedListVisualizer::onInsertPosition()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    int position = positionInput->value();
    
    if (!list.insertAtPosition(value, position)) {
        updateStatus("Position out of range! Valid range: 0 to " + QString::number(list.size()), "error");
        return;
    }
    
    highlightIndex = position;
    updateStatus("Inserted " + QString::number(value) + " at position " + QString::number(position), "success");
    
    valueInput->clear();
    update();
}

void LinkedListVisualizer::onDeleteBeginning()
{
    if (list.isEmpty()) {
        updateStatus("Cannot delete from empty list", "error");
        return;
    }
    
    int deletedValue = list.toVector()[0];
    list.deleteFromBeginning();
    highlightIndex = -1;
    updateStatus("Deleted value " + QString::number(deletedValue) + " from the beginning (HEAD)", "success");
    
    update();
}

void LinkedListVisualizer::onDeleteEnd()
{
    if (list.isEmpty()) {
        updateStatus("Cannot delete from empty list", "error");
        return;
    }
    
    auto nodes = list.toVector();
    int deletedValue = nodes.back();
    list.deleteFromEnd();
    highlightIndex = -1;
    updateStatus("Deleted value " + QString::number(deletedValue) + " from the end (TAIL)", "success");
    
    update();
}

void LinkedListVisualizer::onDeletePosition()
{
    if (list.isEmpty()) {
        updateStatus("Cannot delete from empty list", "error");
        return;
    }
    
    int position = positionInput->value();
    
    if (position < 0 || position >= list.size()) {
        updateStatus("Position out of range! Valid range: 0 to " + QString::number(list.size() - 1), "error");
        return;
    }
    
    int deletedValue = list.toVector()[position];
    list.deleteAtPosition(position);
    highlightIndex = -1;
    updateStatus("Deleted value " + QString::number(deletedValue) + " from position " + QString::number(position), "success");
    
    update();
}

void LinkedListVisualizer::onSearch()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value to search", "error");
        return;
    }
    
    int position = list.search(value);
    
    if (position != -1) {
        highlightIndex = position;
        updateStatus("Found value " + QString::number(value) + " at position " + QString::number(position), "success");
    } else {
        highlightIndex = -1;
        updateStatus("Value " + QString::number(value) + " not found in list", "error");
    }
    
    update();
}

void LinkedListVisualizer::onReverse()
{
    if (list.isEmpty()) {
        updateStatus("Cannot reverse empty list", "error");
        return;
    }
    
    if (list.size() == 1) {
        updateStatus("List has only one node, reverse has no effect", "info");
        return;
    }
    
    list.reverse();
    highlightIndex = -1;
    updateStatus("Linked list reversed successfully", "success");
    
    update();
}

void LinkedListVisualizer::onClear()
{
    if (list.isEmpty()) {
        updateStatus("List is already empty", "info");
        return;
    }
    
    list.clear();
    highlightIndex = -1;
    updateStatus("All nodes cleared from linked list", "success");
    
    update();
}

void LinkedListVisualizer::onReload()
{
    list.clear();
    list.insertAtEnd(10);
    list.insertAtEnd(25);
    list.insertAtEnd(40);
    list.insertAtEnd(55);
    list.insertAtEnd(70);
    highlightIndex = -1;
    updateStatus("Linked list reloaded with sample data", "success");
    update();
}
