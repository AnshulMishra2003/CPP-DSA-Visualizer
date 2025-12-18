#include "ArrayVisualizer.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <algorithm>

ArrayVisualizer::ArrayVisualizer(QWidget *parent)
    : QWidget(parent), highlightIndex(-1)
{
    // Initialize with sample data
    array = {15, 42, 8, 23, 56, 31, 19, 67};
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title Section
    infoLabel = new QLabel("\U0001F4CA Array Data Structure Visualizer");
    infoLabel->setStyleSheet(
        "font-size: 22px; "
        "font-weight: bold; "
        "color: #2c3e50; "
        "padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2ecc71); "
        "border-radius: 8px; "
        "color: white;"
    );
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Size Label
    sizeLabel = new QLabel("Array Size: " + QString::number(array.size()) + " | Capacity: Dynamic");
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
        "   border: 2px solid #3498db; "
        "   border-radius: 8px; "
        "   margin-top: 10px; "
        "   padding-top: 10px; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 15px; "
        "   padding: 0 5px; "
        "   color: #3498db; "
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
    
    QLabel *indexLabel = new QLabel("Index:");
    indexLabel->setStyleSheet("font-size: 12px; font-weight: bold; color: #2c3e50;");
    indexInput = new QSpinBox();
    indexInput->setMinimum(0);
    indexInput->setMaximum(99);
    indexInput->setValue(0);
    indexInput->setMaximumWidth(100);
    indexInput->setStyleSheet(
        "padding: 8px; "
        "border: 2px solid #bdc3c7; "
        "border-radius: 5px; "
        "font-size: 12px;"
    );
    
    inputLayout->addWidget(valueLabel);
    inputLayout->addWidget(valueInput);
    inputLayout->addSpacing(20);
    inputLayout->addWidget(indexLabel);
    inputLayout->addWidget(indexInput);
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
    
    // Row 1: Basic Operations
    QHBoxLayout *buttonRow1 = new QHBoxLayout();
    
    insertBtn = new QPushButton("\u2795 Insert");
    insertBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    deleteBtn = new QPushButton("\u274C Delete");
    deleteBtn->setStyleSheet(btnStyle.arg("#e74c3c", "#c0392b", "#a93226"));
    
    searchBtn = new QPushButton("\U0001F50D Search");
    searchBtn->setStyleSheet(btnStyle.arg("#9b59b6", "#8e44ad", "#7d3c98"));
    
    updateBtn = new QPushButton("\u270F\uFE0F Update");
    updateBtn->setStyleSheet(btnStyle.arg("#f39c12", "#e67e22", "#d68910"));
    
    buttonRow1->addWidget(insertBtn);
    buttonRow1->addWidget(deleteBtn);
    buttonRow1->addWidget(searchBtn);
    buttonRow1->addWidget(updateBtn);
    
    controlLayout->addLayout(buttonRow1);
    
    // Row 2: Array Operations
    QHBoxLayout *buttonRow2 = new QHBoxLayout();
    
    pushBackBtn = new QPushButton("\u2B07\uFE0F Push Back");
    pushBackBtn->setStyleSheet(btnStyle.arg("#1abc9c", "#16a085", "#138d75"));
    
    popBackBtn = new QPushButton("\u2B06\uFE0F Pop Back");
    popBackBtn->setStyleSheet(btnStyle.arg("#e67e22", "#d35400", "#ba4a00"));
    
    sortBtn = new QPushButton("\u2195\uFE0F Sort");
    sortBtn->setStyleSheet(btnStyle.arg("#2ecc71", "#27ae60", "#229954"));
    
    reverseBtn = new QPushButton("\U0001F504 Reverse");
    reverseBtn->setStyleSheet(btnStyle.arg("#34495e", "#2c3e50", "#1c2833"));
    
    buttonRow2->addWidget(pushBackBtn);
    buttonRow2->addWidget(popBackBtn);
    buttonRow2->addWidget(sortBtn);
    buttonRow2->addWidget(reverseBtn);
    
    controlLayout->addLayout(buttonRow2);
    
    // Row 3: Utility
    QHBoxLayout *buttonRow3 = new QHBoxLayout();
    
    clearBtn = new QPushButton("\U0001F5D1\uFE0F Clear All");
    clearBtn->setStyleSheet(btnStyle.arg("#95a5a6", "#7f8c8d", "#5d6d7e"));
    
    reloadBtn = new QPushButton("\U0001F504 Reload");
    reloadBtn->setStyleSheet(btnStyle.arg("#3498db", "#2980b9", "#21618c"));
    
    buttonRow3->addWidget(clearBtn);
    buttonRow3->addWidget(reloadBtn);
    buttonRow3->addStretch();
    
    controlLayout->addLayout(buttonRow3);
    
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);
    
    // Status Label
    statusLabel = new QLabel("\u2705 Ready - Array initialized with sample data");
    statusLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #27ae60; "
        "padding: 10px; "
        "background-color: #d5f4e6; "
        "border-left: 4px solid #27ae60; "
        "border-radius: 5px;"
    );
    mainLayout->addWidget(statusLabel);
    
    // Visualization Area (spacer)
    mainLayout->addStretch();
    
    // Connect signals
    connect(insertBtn, &QPushButton::clicked, this, &ArrayVisualizer::onInsert);
    connect(deleteBtn, &QPushButton::clicked, this, &ArrayVisualizer::onDelete);
    connect(searchBtn, &QPushButton::clicked, this, &ArrayVisualizer::onSearch);
    connect(updateBtn, &QPushButton::clicked, this, &ArrayVisualizer::onUpdate);
    connect(sortBtn, &QPushButton::clicked, this, &ArrayVisualizer::onSort);
    connect(reverseBtn, &QPushButton::clicked, this, &ArrayVisualizer::onReverse);
    connect(clearBtn, &QPushButton::clicked, this, &ArrayVisualizer::onClear);
    connect(reloadBtn, &QPushButton::clicked, this, &ArrayVisualizer::onReload);
    connect(pushBackBtn, &QPushButton::clicked, this, &ArrayVisualizer::onPushBack);
    connect(popBackBtn, &QPushButton::clicked, this, &ArrayVisualizer::onPopBack);
}

void ArrayVisualizer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    drawArray();
}

void ArrayVisualizer::drawArray()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    if (array.isEmpty()) {
        painter.setPen(QPen(QColor("#95a5a6"), 2));
        painter.setFont(QFont("Arial", 16, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "\u26A0\uFE0F Array is Empty\n\nAdd elements using Insert or Push Back");
        return;
    }
    
    // Base geometry
    int boxWidth = 70;
    int boxHeight = 70;
    int spacing = 5;
    int marginLeft = 40;
    int marginRight = 40;
    // Compute a startY that stays below controls/status
    int topOffset = statusLabel ? statusLabel->geometry().bottom() + 12 : 120;
    int desiredStartY = height() - 200;
    int startY = desiredStartY; // adjust after scale known

    // Compute content width and scale uniformly to fit horizontally
    const int count = array.size();
    int contentWidth = count > 0 ? (count * (boxWidth + spacing) - spacing) : 0;
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
    int minStartY = static_cast<int>(topOffset / scale + 60);
    if (startY < minStartY) startY = minStartY;
    
    int logicalViewportHeight = static_cast<int>(height() / scale);
    
    // Draw array elements
    for (int i = 0; i < array.size(); ++i) {
        int x = startX + i * (boxWidth + spacing);
        
        // Color based on state
        QColor fillColor;
        QColor borderColor;
        
        if (i == highlightIndex) {
            fillColor = QColor("#2ecc71");  // Green for highlighted
            borderColor = QColor("#27ae60");
        } else {
            fillColor = QColor("#3498db");  // Blue for normal
            borderColor = QColor("#2980b9");
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
                        Qt::AlignCenter, QString::number(array[i]));
        
        // Draw index below (clamp y to avoid bottom overflow)
        painter.setPen(QColor("#2c3e50"));
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        int indexY = qMin(logicalViewportHeight - 30, startY + boxHeight + 5);
        painter.drawText(x, indexY, boxWidth, 25, 
                        Qt::AlignCenter, "[" + QString::number(i) + "]");
    }

    painter.restore();
}

void ArrayVisualizer::updateStatus(const QString &message, const QString &color)
{
    QString icon;
    QString bgColor;
    
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
    sizeLabel->setText("Array Size: " + QString::number(array.size()) + " | Capacity: Dynamic");
}

void ArrayVisualizer::onInsert()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    int index = indexInput->value();
    
    if (index < 0 || index > array.size()) {
        updateStatus("Index out of range! Valid range: 0 to " + QString::number(array.size()), "error");
        return;
    }
    
    array.insert(index, value);
    highlightIndex = index;
    updateStatus("Inserted " + QString::number(value) + " at index " + QString::number(index), "success");
    
    valueInput->clear();
    update();
}

void ArrayVisualizer::onDelete()
{
    if (array.isEmpty()) {
        updateStatus("Cannot delete from empty array", "error");
        return;
    }
    
    int index = indexInput->value();
    
    if (index < 0 || index >= array.size()) {
        updateStatus("Index out of range! Valid range: 0 to " + QString::number(array.size() - 1), "error");
        return;
    }
    
    int deletedValue = array[index];
    array.remove(index);
    highlightIndex = -1;
    updateStatus("Deleted value " + QString::number(deletedValue) + " from index " + QString::number(index), "success");
    
    update();
}

void ArrayVisualizer::onSearch()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value to search", "error");
        return;
    }
    
    int foundIndex = -1;
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] == value) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex != -1) {
        highlightIndex = foundIndex;
        updateStatus("Found value " + QString::number(value) + " at index " + QString::number(foundIndex), "success");
    } else {
        highlightIndex = -1;
        updateStatus("Value " + QString::number(value) + " not found in array", "error");
    }
    
    update();
}

void ArrayVisualizer::onUpdate()
{
    if (array.isEmpty()) {
        updateStatus("Cannot update empty array", "error");
        return;
    }
    
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    int index = indexInput->value();
    
    if (index < 0 || index >= array.size()) {
        updateStatus("Index out of range! Valid range: 0 to " + QString::number(array.size() - 1), "error");
        return;
    }
    
    int oldValue = array[index];
    array[index] = value;
    highlightIndex = index;
    updateStatus("Updated index [" + QString::number(index) + "] from " + 
                QString::number(oldValue) + " \u2192 " + QString::number(value), "success");
    
    valueInput->clear();
    update();
}

void ArrayVisualizer::onSort()
{
    if (array.isEmpty()) {
        updateStatus("Cannot sort empty array", "error");
        return;
    }
    
    if (array.size() == 1) {
        updateStatus("Array has only one element, already sorted", "info");
        return;
    }
    
    std::sort(array.begin(), array.end());
    highlightIndex = -1;
    updateStatus("Array sorted in ascending order using Quick Sort", "success");
    
    update();
}

void ArrayVisualizer::onReverse()
{
    if (array.isEmpty()) {
        updateStatus("Cannot reverse empty array", "error");
        return;
    }
    
    if (array.size() == 1) {
        updateStatus("Array has only one element, reverse has no effect", "info");
        return;
    }
    
    std::reverse(array.begin(), array.end());
    highlightIndex = -1;
    updateStatus("Array reversed successfully", "success");
    
    update();
}

void ArrayVisualizer::onClear()
{
    if (array.isEmpty()) {
        updateStatus("Array is already empty", "info");
        return;
    }
    
    array.clear();
    highlightIndex = -1;
    updateStatus("All elements cleared from array", "success");
    
    update();
}

void ArrayVisualizer::onReload()
{
    array.clear();
    array = {15, 42, 8, 23, 56, 31, 19, 67};
    highlightIndex = -1;
    updateStatus("Array reloaded with sample data", "success");
    update();
}

void ArrayVisualizer::onPushBack()
{
    bool ok;
    int value = valueInput->text().toInt(&ok);
    
    if (!ok || valueInput->text().isEmpty()) {
        updateStatus("Please enter a valid integer value", "error");
        return;
    }
    
    array.push_back(value);
    highlightIndex = array.size() - 1;
    updateStatus("Pushed " + QString::number(value) + " to the end of array", "success");
    
    valueInput->clear();
    update();
}

void ArrayVisualizer::onPopBack()
{
    if (array.isEmpty()) {
        updateStatus("Cannot pop from empty array", "error");
        return;
    }
    
    int poppedValue = array.last();
    array.pop_back();
    highlightIndex = -1;
    updateStatus("Popped value " + QString::number(poppedValue) + " from the end", "success");
    
    update();
}
