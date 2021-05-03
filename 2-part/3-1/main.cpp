//
// Created by Черных Никита Алекандрович on 5/3/21.
//

#include <iostream>

using namespace std;

struct Node {
    int value;
    int priority;
    Node *left;
    Node *right;

    Node(int value, int priority) : left(nullptr), right(nullptr), value(value), priority(priority) {};

    bool CheckLeaf() {
        return left == nullptr && right == nullptr;
    }
};

bool CmpLess(Node *n, int value) {
    return n->value < value;
}

bool CmpGte(Node *n, int value) {
    return n->value >= value;
}

Node *GetRight(Node *n) {
    return n->right;
}

Node *GetLeft(Node *n) {
    return n->left;
}

void SetLeft(Node *n, Node *node) {
    n->left = node;
}

void SetRight(Node *n, Node *node) {
    n->right = node;
}

struct SubTrees {
    SubTrees() : left(nullptr), right(nullptr) {};

    SubTrees(Node *left, Node *right) : left(left), right(right) {};

    Node *left;
    Node *right;
};

void SetLeftTree(SubTrees *n, Node *node) {
    n->left = node;
}

void SetRightTree(SubTrees *n, Node *node) {
    n->right = node;
}

class DecartTree {
public:
    DecartTree() : head(nullptr) {};

    void AddElement(Node *node) {
        if (head == nullptr) {
            head = node;
            return;
        }

        auto buf = head;
        Node *previous = nullptr;
        while (buf != nullptr && buf->priority >= node->priority) {
            previous = buf;
            if (buf->value >= node->value) {
                buf = buf->left;
                continue;
            }
            buf = buf->right;
        }

        if (previous == nullptr) {
            split(head, node->value, node->left, node->right);
            head = node;
            return;
        }

        split(buf, node->value, node->left, node->right);
        if (previous->value >= node->value) {
            previous->left = node;
            return;
        }

        previous->right = node;
    };

    size_t Size() {
        auto buf = head;
        return size(buf, 0);
    };
private:
    size_t size(Node *n, size_t s) {
        if (n == nullptr) {
            return s;
        }

        return max(size(n->left, (s + 1)), size(n->right, (s + 1)));
    }

    void split(Node *n, const int &value, Node *&left, Node *&right) {
        if (n == nullptr) {
            right = nullptr;
            left = nullptr;
            return;
        }

        if (n->value <= value) {
            split(n->right, value, n->right, right);
            left = n;
            return;
        }

        split(n->left, value, left, n->left);
        right = n;
    };


    Node *head;
};

struct Data {
    Data(int value) : value(value), left(nullptr), right(nullptr) {};

    bool CheckLeaf() {
        return left == nullptr && right == nullptr;
    }

    Data *left;
    Data *right;
    int value;
};

class BinaryTree {
public:

    BinaryTree() : head(nullptr) {}

    void Add(const int &value) {
        if (head == nullptr) {
            head = new Data(value);
            return;
        }

        auto ptr = head;
        auto newNode = new Data(value);
        while (ptr != nullptr) {
            if (ptr->value <= value) {
                if (ptr->right != nullptr) {
                    ptr = ptr->right;
                    continue;
                }

                ptr->right = newNode;
                return;
            }

            if (ptr->left != nullptr) {
                ptr = ptr->left;
                continue;
            }

            ptr->left = newNode;
            return;
        }
        return;
    };

    size_t Size() {
        auto buf = head;
        return size(buf, 0);
    };

private:
    size_t size(Data *n, size_t s) {
        if (n == nullptr) {
            return s;
        }

        return max(size(n->left, (s + 1)), size(n->right, (s + 1)));
    }

    Data *head;
};

int main() {
    int size = 0, value = 0, priority = 0;
    auto dt = new DecartTree;
    auto bt = new BinaryTree;
    cin >> size;

    for (int i = 0; i < size; ++i) {
        cin >> value >> priority;
        dt->AddElement(new Node(value, priority));
        bt->Add(value);
    }

    cout << bt->Size() - dt->Size() << endl;

    delete dt;
    delete bt;
}