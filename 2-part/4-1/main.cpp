//В одной военной части решили построить в одну шеренгу по росту.
// Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
// Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие.
// За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста.
// Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
// Требуемая скорость выполнения команды - O(log n).

#include <iostream>

template<class T>
struct Node {
    Node(const T &data) : data(data), height(1), leftCount(0), rightCount(0), left(nullptr), right(nullptr) {};

    T data;
    int height, leftCount, rightCount;
    Node<T> *left;
    Node<T> *right;
};

template<class T>
struct LessComparator {
    bool operator()(const Node<T> &l, const Node<T> &r) {
        return l.data < r.data;
    }
};

template<class T, class Comparator>
class Tree {
public:
    Tree() : head(nullptr), cmp(nullptr) {};

    Tree(const Comparator &comp) : head(nullptr), cmp(comp) {};

    int AddValue(const T &value) {
        int counter = 0;
        head = insertValue(head, value, &counter);

        return counter;
    };

    void RemoveElement(const int& position) {
        // counting from zero !
        head = removePosition(head, position + 1, 0);
    };

    ~Tree() {
        deleteNode(head);
    };

private:
    Node<T> *insertValue(Node<T> *ptr, const T &value, int *position) {
        if (ptr == nullptr) {
            return new Node(value);
        }

        if (cmp(value, ptr->data)) {
            *position += ptr->rightCount + 1;
            ptr->left = insertValue(ptr->left, value, position);
        } else {
            ptr->right = insertValue(ptr->right, value, position);
        }

        return balanceNode(ptr);
    };

    // i guess it seems lil bad
    Node<T> *removePosition(Node<T> *ptr, const int &idx, const int &counted) {
        auto curr = counted + ptr->rightCount + 1;

        if (curr == idx) {
            auto left = ptr->left;
            auto right = ptr->right;
            ptr->left = nullptr;
            ptr->right = nullptr;
            delete ptr;

            if (right == nullptr) {
                return left;
            }

            auto p = removeMin(right);
            p.first->right = p.second;
            p.first->left = left;

            return balanceNode(p.first);
        }

        if (curr < idx) {
            ptr->left = removePosition(ptr->left, idx, counted + ptr->rightCount + 1);
        }
        if (curr > idx) {
            ptr->right = removePosition(ptr->right, idx, counted);
        }

        return balanceNode(ptr);
    };

    // read - awful code
    std::pair<Node<T> *, Node<T> *> removeMin(Node<T> *ptr) {
        if (ptr->left == nullptr) {
            return std::make_pair(ptr, ptr->right);
        }

        auto p = removeMin(ptr->left);
        ptr->left = p.second;
        return std::make_pair(p.first, balanceNode(ptr));
    };

    Node<T> *balanceNode(Node<T> *ptr) {
        fixNode(ptr);
        auto factor = getFactor(ptr);

        if (factor == 2) {
            if (getFactor(ptr->right) < 0)
                ptr->right = rotateRight(ptr->right);

            return rotateLeft(ptr);
        }

        if (factor == -2) {
            if (getFactor(ptr->left) > 0)
                ptr->left = rotateLeft(ptr->left);

            return rotateRight(ptr);
        }

        return ptr;
    };

    Node<T> *rotateRight(Node<T> *ptr) {
        Node<T> *left = ptr->left;
        ptr->left = left->right;
        left->right = ptr;
        fixNode(ptr);
        fixNode(left);

        return left;
    };

    Node<T> *rotateLeft(Node<T> *ptr) {
        Node<T> *right = ptr->right;
        ptr->right = right->left;
        right->left = ptr;
        fixNode(ptr);
        fixNode(right);

        return right;
    };

    void deleteNode(Node<T> *ptr) {
        if (ptr == nullptr)
            return;

        deleteNode(ptr->left);
        deleteNode(ptr->right);
        delete ptr;
    }

    // mb move them to node functions ?
    int getCount(const Node<T> *node) {
        return node == nullptr ? 0 : (node->rightCount + node->leftCount + 1);
    }

    int getHeight(const Node<T> *node) {
        return node == nullptr ? 0 : node->height;
    }

    int getFactor(const Node<T> *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void fixNode(Node<T> *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        node->leftCount = getCount(node->left);
        node->rightCount = getCount(node->right);
    }

    Node<T> *head;
    Comparator cmp;
};

int main() {
    auto t = new Tree<int, LessComparator<int>>(LessComparator<int>{});
    int count = 0, command = 0, value = 0;

    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        std::cin >> command >> value;

        switch (command) {
            case 1: {
                std::cout << t->AddValue(value) << std::endl;
                break;
            }
            case 2: {
                t->RemoveElement(value);
                break;
            }
            default: {
            }
        }
    }

    delete t;
    return 0;
}