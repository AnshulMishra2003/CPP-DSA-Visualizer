#ifndef TREEVISUALIZER_H
#define TREEVISUALIZER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QTimer>
#include "../ds/Tree.h"

class TreeVisualizer : public QWidget {
    Q_OBJECT
public:
    explicit TreeVisualizer(QWidget* parent = nullptr);

private slots:
    void onInsert();
    void onDelete();
    void onSearch();
    void onClear();
    void onInorder();
    void onPreorder();
    void onPostorder();
    void onLevelorder();
    void onPlayDFS();
    void onPlayBFS();

private:
    void paintEvent(QPaintEvent* event) override;
    void drawTree();
    void drawNode(class QPainter& p, BSTree::Node* node, int x, int y, int hGap, int depth);
    void updateStatus(const QString& message, const QString& kind);
    void startTraversalAnimation(const std::vector<int>& sequence, const QString& label);

    BSTree tree;
    int highlightValue;

    // UI
    QLineEdit* valueInput;
    QPushButton* insertBtn;
    QPushButton* deleteBtn;
    QPushButton* searchBtn;
    QPushButton* clearBtn;
    QPushButton* inorderBtn;
    QPushButton* preorderBtn;
    QPushButton* postorderBtn;
    QPushButton* levelorderBtn;
    QPushButton* playDFSBtn;
    QPushButton* playBFSBtn;
    QLabel* statusLabel;
    QLabel* infoLabel;
    QLabel* sizeLabel;
    QLabel* heightLabel;
    QLabel* minMaxLabel;
    QGroupBox* controlGroup;

    // Traversal animation
    QTimer* traversalTimer{nullptr};
    std::vector<int> traversalSeq;
    int traversalIndex{0};
};

#endif // TREEVISUALIZER_H
