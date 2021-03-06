//
// Created by Черных Никита Алекандрович on 3/17/21.
//
// Дан массив целых чисел A[0..n), n не превосходит 100 000.
// Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
// Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n log n), память O(n).

#include <iostream>
using namespace std;

template<class T>
struct Element {
    size_t position;
    T data;
};

template<class T>
struct LessComparator {
    bool operator()(const Element<T> &l, const Element<T> &r) {
        return l.data < r.data;
    }
};

template<class T, class Comparator = LessComparator<T>>
class Heap {
public:
    Heap() : size(0), capacity(1), sizeMultiply(0) {
        array = new Element<T>[capacity];
    };

    Heap(Element<T> *array, size_t size, size_t capacity, size_t size_multiply) : size(size), capacity(capacity),
                                                                                  sizeMultiply(size_multiply),
                                                                                  array(array) {
        buildHeap();
    };

    ~Heap() {
        delete[] array;
    };

    void Add(const Element<T> &el) {
        if (capacity == size)
            resize();

        array[capacity] = el;
        siftUp(capacity);
        capacity++;
    };

    Element<T> Get() {
        Element<T> elem = array[0];
        capacity--;
        array[0] = array[capacity];
        siftDown(0);
        return elem;
    };

    size_t GetCapacity() {
        return capacity;
    };

private:
    void resize() {
        size *= sizeMultiply;
        auto newArray = new Element<T>[size];
        for (size_t i = 0; i < capacity; ++i) {
            newArray[i] = array[i];
        }
        delete array;
        array = newArray;
    };

    void buildHeap() {
        for (size_t i = capacity / 2; i >= 0; --i) {
            siftDown(i);

            if (i == 0) {
                break;
            }
        }
    };

    size_t calculateParent(size_t idx) {
        if (idx == 0)
            return 0;

        return (idx - 1) / 2;
    };

    size_t calculateLeftChild(size_t idx) {
        return idx * 2 + 1;
    }

    size_t calculateRightChild(size_t idx) {
        return idx * 2 + 2;
    };

    void siftDown(size_t idx) {
        auto new_idx = siftOneDown(idx);
        while (idx != new_idx) {
            idx = new_idx;
            new_idx = siftOneDown(idx);
        }
    };

    void siftUp(size_t idx) {
        auto new_idx = siftOneUp(idx);
        while (idx != new_idx && new_idx != 0) {
            idx = new_idx;
            new_idx = siftOneUp(idx);
        }
    };

    size_t siftOneDown(size_t idx) {
        auto leftChild = calculateLeftChild(idx);
        auto rightChild = calculateRightChild(idx);
        auto largest = idx;

        if (leftChild < capacity && cmp(array[largest], array[leftChild]))
            largest = leftChild;

        if (rightChild < capacity && cmp(array[largest], array[rightChild]))
            largest = rightChild;

        if (largest != idx) {
            std::swap(array[idx], array[largest]);
        }

        return largest;
    };

    size_t siftOneUp(size_t idx) {
        auto parent = calculateParent(idx);

        if (cmp(array[parent], array[idx])) {
            std::swap(array[parent], array[idx]);
            idx = parent;
        }

        return idx;
    };

    Element<T> *array;
    size_t size;
    size_t capacity;
    size_t sizeMultiply;
    Comparator cmp;
};

template<class T>
struct Maximum {
    T value;
    size_t end;
    bool notEmpty;
};

template<class T>
class Solver {
public:
    explicit Solver(Heap<T> *heap) : heap(heap) {};

    ~Solver() {
        delete heap;
    };

    void Solve(size_t window) {
        if (window == 0) {
            return;
        }

        auto cap = heap->GetCapacity();
        size_t parts = cap - window + 1, totalElements = 0, windowIncludingCurrent = window - 1;
        auto windowResponse = new Maximum<T>[parts];
        std::fill_n(windowResponse, parts, Maximum<T>{T(), 0, false});

        while (totalElements < parts) {
            auto el = heap->Get();

            size_t elementStart = el.position < windowIncludingCurrent ? 0 : el.position - windowIncludingCurrent;
            size_t elementEnd = el.position;
            Maximum<T> el_section = {el.data, elementEnd, true};

            while (elementStart <= elementEnd && totalElements <= parts && elementStart < parts) {
                if (windowResponse[elementStart].notEmpty) {
                    elementStart = windowResponse[elementStart].end + 1;
                    continue;
                }
                windowResponse[elementStart] = el_section;
                totalElements++;
                elementStart++;
            }
        }

        for(size_t i = 0 ; i < parts ; ++i)
            cout << windowResponse[i].value << " ";

        delete[] windowResponse;
    };

private:
    Heap<T> *heap;
};

const size_t size_multiply = 2;

int main() {
    size_t size = 0;
    cin >> size;
    size_t capacity = size;
    auto arr = new Element<int>[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i].position = i;
        cin >> arr[i].data;
    }
    auto heap = new Heap<int>(arr, size, capacity, size_multiply);
    auto solver = new Solver<int>(heap);
    size_t window = 0;
    cin >> window;

    solver->Solve(window);

    delete solver;

    return 0;
}