#ifndef ARRAYVISUALIZER_H
#define ARRAYVISUALIZER_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QGroupBox>

class ArrayVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit ArrayVisualizer(QWidget *parent = nullptr);

private slots:
    void onInsert();
    void onDelete();
    void onSearch();
    void onUpdate();
    void onSort();
    void onReverse();
    void onClear();
    void onReload();
    void onPushBack();
    void onPopBack();

private:
    void paintEvent(QPaintEvent *event) override;
    void drawArray();
    void updateStatus(const QString &message, const QString &color);
    
    QVector<int> array;
    int highlightIndex;
    
    // UI Components
    QLineEdit *valueInput;
    QSpinBox *indexInput;
    QPushButton *insertBtn;
    QPushButton *deleteBtn;
    QPushButton *searchBtn;
    QPushButton *updateBtn;
    QPushButton *sortBtn;
    QPushButton *reverseBtn;
    QPushButton *clearBtn;
    QPushButton *reloadBtn;
    QPushButton *pushBackBtn;
    QPushButton *popBackBtn;
    QLabel *statusLabel;
    QLabel *infoLabel;
    QLabel *sizeLabel;
};

#endif // ARRAYVISUALIZER_H
