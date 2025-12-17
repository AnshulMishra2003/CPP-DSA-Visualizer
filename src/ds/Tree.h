#ifndef TREE_H
#define TREE_H

#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

class BSTree {
public:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int v): value(v), left(nullptr), right(nullptr) {}
    };

    BSTree(): root_(nullptr), count_(0) {}

    ~BSTree() { clear(); }

    bool insert(int v) {
        bool inserted = false;
        root_ = insertRec(root_, v, inserted);
        if (inserted) ++count_;
        return inserted;
    }

    bool contains(int v) const {
        Node* cur = root_;
        while (cur) {
            if (v == cur->value) return true;
            cur = v < cur->value ? cur->left : cur->right;
        }
        return false;
    }

    bool remove(int v) {
        bool removed = false;
        root_ = removeRec(root_, v, removed);
        if (removed) --count_;
        return removed;
    }

    void clear() {
        clearRec(root_);
        root_ = nullptr;
        count_ = 0;
    }

    int size() const { return count_; }

    int height() const { return heightRec(root_); }

    Node* getRoot() const { return root_; }

    // Min/Max
    int min() const {
        if (!root_) return std::numeric_limits<int>::min();
        Node* n = root_;
        while (n->left) n = n->left;
        return n->value;
    }
    int max() const {
        if (!root_) return std::numeric_limits<int>::max();
        Node* n = root_;
        while (n->right) n = n->right;
        return n->value;
    }

    // Traversals
    std::vector<int> inorder() const {
        std::vector<int> out; out.reserve(count_);
        inorderRec(root_, out); return out;
    }
    std::vector<int> preorder() const {
        std::vector<int> out; out.reserve(count_);
        preorderRec(root_, out); return out;
    }
    std::vector<int> postorder() const {
        std::vector<int> out; out.reserve(count_);
        postorderRec(root_, out); return out;
    }
    std::vector<int> levelorder() const {
        std::vector<int> out; out.reserve(count_);
        if (!root_) return out;
        std::queue<Node*> q; q.push(root_);
        while (!q.empty()) {
            Node* n = q.front(); q.pop();
            out.push_back(n->value);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        return out;
    }

private:
    Node* root_;
    int count_;

    static Node* insertRec(Node* node, int v, bool& inserted) {
        if (!node) { inserted = true; return new Node(v); }
        if (v == node->value) return node; // no duplicates
        if (v < node->value) node->left = insertRec(node->left, v, inserted);
        else node->right = insertRec(node->right, v, inserted);
        return node;
    }

    static Node* minNode(Node* node) { while (node && node->left) node = node->left; return node; }

    static Node* removeRec(Node* node, int v, bool& removed) {
        if (!node) return nullptr;
        if (v < node->value) node->left = removeRec(node->left, v, removed);
        else if (v > node->value) node->right = removeRec(node->right, v, removed);
        else {
            removed = true;
            if (!node->left) { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left; delete node; return l; }
            Node* succ = minNode(node->right);
            node->value = succ->value;
            node->right = removeRec(node->right, succ->value, removed = true);
        }
        return node;
    }

    static void clearRec(Node* node) {
        if (!node) return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    static int heightRec(Node* node) {
        if (!node) return -1;
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
        }

    static void inorderRec(Node* n, std::vector<int>& out) {
        if (!n) return; inorderRec(n->left, out); out.push_back(n->value); inorderRec(n->right, out);
    }
    static void preorderRec(Node* n, std::vector<int>& out) {
        if (!n) return; out.push_back(n->value); preorderRec(n->left, out); preorderRec(n->right, out);
    }
    static void postorderRec(Node* n, std::vector<int>& out) {
        if (!n) return; postorderRec(n->left, out); postorderRec(n->right, out); out.push_back(n->value);
    }
};

#endif // TREE_H
