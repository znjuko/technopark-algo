//
// Created by Черных Никита Алекандрович on 3/17/21.
//
// Дан массив целых чисел A[0..n), n не превосходит 100 000.
// Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n.
// Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n log n), память O(n).

#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<class T>
struct LessComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

template<class T, class Comparator = LessComparator<T> >
class MergeSort {
public:
    MergeSort() : size(0) {
        array = new T[size];
    };

    MergeSort(T *array, size_t size) : size(size), array(array) {};

    ~MergeSort() {
        delete[] array;
    }

    T *Sort() {
        return sort(array, 0, size - 1);
    }

private:
    T *sort(T *const data, size_t left, size_t right) {
        if (left >= right)
            return data;

        cout << endl;

        auto med = left + (right - left) / 2;

        auto leftPart = sort(data, left, med);
        auto rightPart = sort(data, med + 1, right);
        auto merged = merge(leftPart + left, rightPart + med, med - left + 1, right - med);

        return merged;
    };

    T *merge(T *const first, T *const second, size_t firstSize, size_t secondSize) {
        auto merged = new T[firstSize + secondSize];
        size_t firstIterator = 0, secondIterator = 0, mergedIterator = 0;

        while (firstIterator < firstSize && secondIterator < secondSize) {
            if (cmp(first[firstIterator], second[secondIterator])) {
                merged[mergedIterator++] = first[firstIterator++];
            } else {
                merged[mergedIterator++] = second[secondIterator++];
            }
        }

        while (firstIterator < firstSize) {
            merged[mergedIterator++] = first[firstIterator++];
        }

        while (secondIterator < secondSize) {
            merged[mergedIterator++] = second[secondIterator++];
        }

        return merged;
    };


    T *array;
    size_t size;
    Comparator cmp;
};

// 0 2 4
// 1 3

// 0 2 4 1 3
// 0 1 4 2 3
// 0 1 2 4 3

int main() {
    size_t size = 0;
    cin >> size;
    auto array = new int[size];
    for (size_t i = 0; i < size; ++i) {
        cin >> array[i];
    }

    auto solver = new MergeSort<int>(array, size);

    auto resp = solver->Sort();

    for (size_t i = 0; i < size; ++i) {
        cout << resp[i] << " ";
    }

    delete resp;
    delete solver;
    return 0;
}