#ifndef QUEUEVISUALIZER_H
#define QUEUEVISUALIZER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include "../ds/Queue.h"

class QueueVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit QueueVisualizer(QWidget *parent = nullptr);

private slots:
    void onEnqueue();
    void onDequeue();
    void onFront();
    void onRear();
    void onSearch();
    void onClear();
    void onReload();

private:
    void paintEvent(QPaintEvent *event) override;
    void drawQueue();
    void updateStatus(const QString &message, const QString &color);
    
    Queue<int> queue;
    int highlightIndex;
    QString lastOperation;
    
    // UI Components
    QLineEdit *valueInput;
    QPushButton *enqueueBtn;
    QPushButton *dequeueBtn;
    QPushButton *frontBtn;
    QPushButton *rearBtn;
    QPushButton *searchBtn;
    QPushButton *clearBtn;
    QPushButton *reloadBtn;
    QLabel *statusLabel;
    QLabel *infoLabel;
    QLabel *sizeLabel;
    QLabel *frontRearLabel;
};

#endif // QUEUEVISUALIZER_H
