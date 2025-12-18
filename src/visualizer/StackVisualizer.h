#ifndef STACKVISUALIZER_H
#define STACKVISUALIZER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>
#include "../ds/Stack.h"

class StackVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit StackVisualizer(QWidget *parent = nullptr);

private slots:
    void onPush();
    void onPop();
    void onPeek();
    void onSearch();
    void onClear();
    void onReload();

private:
    void paintEvent(QPaintEvent *event) override;
    void drawStack();
    void updateStatus(const QString &message, const QString &color);
    
    Stack<int> stack;
    int highlightIndex;
    QString lastOperation;
    
    // UI Components
    QLineEdit *valueInput;
    QPushButton *pushBtn;
    QPushButton *popBtn;
    QPushButton *peekBtn;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QPushButton *reloadBtn;
    QLabel *statusLabel;
    QLabel *infoLabel;
    QLabel *sizeLabel;
    QLabel *topLabel;
};

#endif // STACKVISUALIZER_H
