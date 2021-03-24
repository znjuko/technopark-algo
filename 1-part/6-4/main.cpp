//
// Created by Черных Никита Алекандрович on 3/17/21.
//
// Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
// Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>
#include <random>

using namespace std;

template<class T>
struct LessComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

template<class T, class Comparator=LessComparator<T>>
class StatisticSearcher {
public:
    StatisticSearcher() = default;

    StatisticSearcher(T *array, int size) : array(array), size(size) {};

    ~StatisticSearcher() {
        delete[] array;
    };


    T FindStatistic(int statistic) {
        int left = 0, right = size - 1;
        while (true) {
            int m = partition(array, left, right);

            if (m == statistic) {
                return array[m];
            }

            if (m > statistic) {
                right = m;
                continue;
            }

            if (m < statistic) {
                left = m + 1;
            }
        }
    }

private:
    int partition(T *arr, int left, int right) {
        size_t partValue = arr[(left + right) / 2];
        swap(arr[partValue], arr[right]);
        int i = right - 1, j = right - 1;

        while (i >= left && j >= left) {
            while (i >= left && !cmp(arr[i], arr[right]))
                --i;
            while (j >= left && cmp(arr[j], arr[right]))
                --j;

            swap(arr[j--], arr[i--]);
        }
        swap(arr[right], arr[i]);

        return i;
    }

    int generate(int left, int right) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(left, right);
        return dist(gen);
    }

    T *array;
    int size{};
    Comparator cmp;
};

int main() {
    int size = 0, statistic = 0;
    cin >> size >> statistic;

    auto array = new int[size];
    for (size_t i = 0; i < size; ++i) {
        cin >> array[i];
    }

    auto searcher = new StatisticSearcher<int>(array, size);
    cout << searcher->FindStatistic(statistic) << endl;

    delete searcher;

    return 0;
}