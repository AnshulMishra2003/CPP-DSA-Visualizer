#ifndef LINKEDLISTVISUALIZER_H
#define LINKEDLISTVISUALIZER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include "../ds/LinkedList.h"

class LinkedListVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit LinkedListVisualizer(QWidget *parent = nullptr);

private slots:
    void onInsertBeginning();
    void onInsertEnd();
    void onInsertPosition();
    void onDeleteBeginning();
    void onDeleteEnd();
    void onDeletePosition();
    void onSearch();
    void onReverse();
    void onClear();

private:
    void paintEvent(QPaintEvent *event) override;
    void drawLinkedList();
    void updateStatus(const QString &message, const QString &color);
    
    LinkedList<int> list;
    int highlightIndex;
    
    // UI Components
    QLineEdit *valueInput;
    QSpinBox *positionInput;
    QPushButton *insertBeginBtn;
    QPushButton *insertEndBtn;
    QPushButton *insertPosBtn;
    QPushButton *deleteBeginBtn;
    QPushButton *deleteEndBtn;
    QPushButton *deletePosBtn;
    QPushButton *searchBtn;
    QPushButton *reverseBtn;
    QPushButton *clearBtn;
    QLabel *statusLabel;
    QLabel *infoLabel;
    QLabel *sizeLabel;
};

#endif // LINKEDLISTVISUALIZER_H
