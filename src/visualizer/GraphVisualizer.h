#ifndef GRAPHVISUALIZER_H
#define GRAPHVISUALIZER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QTimer>
#include <QCheckBox>
#include <QPushButton>
#include <QRandomGenerator>
#include <QScrollBar>
#include <vector>
#include <queue>
#include <stack>
#include <map>

// Unified graph interface supporting 4 types
class UnifiedGraph {
public:
    enum Type { DirectedUnweighted, DirectedWeighted, UndirectedUnweighted, UndirectedWeighted };
    
    struct Edge {
        int to, weight;
        Edge(int t, int w = 0) : to(t), weight(w) {}
    };

    UnifiedGraph(Type t) : type(t) {}

    int addVertex() {
        adj.emplace_back();
        return (int)adj.size() - 1;
    }

    void addEdge(int u, int v, int w = 1) {
        ensureVertex(std::max(u, v));
        adj[u].emplace_back(v, w);
        if (type == UndirectedUnweighted || type == UndirectedWeighted) {
            adj[v].emplace_back(u, w);
        }
    }

    int vertexCount() const { return (int)adj.size(); }

    const std::vector<Edge>& neighbors(int u) const { return adj[u]; }

    void clear() { adj.clear(); }

    std::vector<int> bfs(int start) const {
        std::vector<int> order;
        if (start < 0 || start >= (int)adj.size()) return order;
        std::vector<bool> vis((int)adj.size(), false);
        std::queue<int> q;
        q.push(start);
        vis[start] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (const auto& e : adj[u]) {
                if (!vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return order;
    }

    std::vector<int> dfs(int start) const {
        std::vector<int> order;
        if (start < 0 || start >= (int)adj.size()) return order;
        std::vector<bool> vis((int)adj.size(), false);
        std::stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (vis[u]) continue;
            vis[u] = true;
            order.push_back(u);
            for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                int v = adj[u][i].to;
                if (!vis[v]) st.push(v);
            }
        }
        return order;
    }

    Type getType() const { return type; }

private:
    void ensureVertex(int idx) {
        while (idx >= (int)adj.size()) addVertex();
    }

    Type type;
    std::vector<std::vector<Edge>> adj;
};

// Position data for nodes
struct NodePos {
    double x, y;
    NodePos(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

class GraphVisualizer : public QWidget {
    Q_OBJECT
public:
    explicit GraphVisualizer(QWidget* parent = nullptr);

private slots:
    void onTypeChanged(int idx);
    void onAddVertex();
    void onAddEdge();
    void onClear();
    void onReload();
    void onBFS();
    void onDFS();
    void onPlayBFS();
    void onPlayDFS();
    void onSearchVertex();
    void onToggleLayoutMode();
    void onFitView();

private:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void drawGraph();
    void computeCircularLayout();
    void computeForceLayout();
    void computeLayout();
    void updateStatus(const QString& msg, const QString& kind = "info");
    void startTraversalAnimation(const std::vector<int>& seq, const QString& label);

    UnifiedGraph graph{UnifiedGraph::DirectedUnweighted};
    std::vector<NodePos> nodePositions;
    int selectedStart{-1};
    int highlightedVertex{-1};

    // UI
    QComboBox* typeCombo;
    QLineEdit* vertexInput;
    QPushButton* addVertexBtn;
    QLineEdit* edgeU, *edgeV, *edgeW;
    QPushButton* addEdgeBtn;
    QPushButton* clearBtn;
    QPushButton* reloadBtn;
    QLineEdit* searchVertexInput;
    QPushButton* searchVertexBtn;
    QPushButton* bfsBtn, *dfsBtn;
    QPushButton* playBFSBtn, *playDFSBtn;
    QPushButton* toggleLayoutBtn;
    QPushButton* fitViewBtn;
    QScrollBar* vScroll;
    QLabel* statusLabel;
    QLabel* infoLabel;
    QLabel* statsLabel;
    QGroupBox* controlGroup;

    // Animation
    QTimer* traversalTimer{nullptr};
    std::vector<int> traversalSeq;
    int traversalIndex{0};

    bool useForceLayout{false};
    int scrollOffsetY{0};
};

#endif // GRAPHVISUALIZER_H
