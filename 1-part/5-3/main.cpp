//
// Created by Черных Никита Алекандрович on 3/17/21.
//
// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка (Li и Ri).
// Найти длину окрашенной части числовой прямой.

#include <iostream>

using namespace std;

class Segment {
public:
    unsigned long int start;
    unsigned long int end;

    friend bool operator<(const Segment &l, const Segment &r) {
        return l.start < r.start;
    }
};

template<class T>
struct LessComparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

template<class T, class Comparator = LessComparator<T> >
class Sorter {
public:
    Sorter() : size(0) {
        array = new T[size];
    };

    Sorter(T *array, size_t size) : size(size), array(array) {};

    ~Sorter() {
        delete[] array;
    }

    T *Sort() {
        return sort(array, 0, size - 1);
    }

    size_t GetSize() {
        return size;
    }

private:
    T *sort(T *const data, size_t left, size_t right) {
        if (left >= right) {
            auto one = new T[1];
            one[0] = data[0];
            return one;
        }

        auto med = (right + left) / 2;

        auto leftPart = sort(data + left, 0, med);
        auto rightPart = sort(data + med + 1, 0, right - med - 1);
        auto merged = merge(leftPart, rightPart, med - left + 1, right - med);

        delete[] leftPart;
        delete[] rightPart;

        return merged;
    };

    T *merge(T *const first, T *const second, size_t const &firstSize, size_t const &secondSize) {
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

template<class T, class Comparator = LessComparator<T> >
class Solver {
public:
    Solver() : s() {};

    Solver(Sorter<T, Comparator> *s) : s(s) {};

    ~Solver() {
        delete s;
    }

    size_t Solve() {
        auto sorted = s->Sort();
        auto size = s->GetSize();
        size_t length = 0, current_start = 0, current_end = 0;

        for (size_t i = 0; i < size; ++i) {
            if (sorted[i].end <= current_end) {
                continue;
            }

            if (current_end == sorted[i].end && current_start == sorted[i].start) {
                continue;
            }

            current_start = sorted[i].start <= current_end ? current_end : sorted[i].start;
            current_end = sorted[i].end;
            length += current_end - current_start;
        }

        delete[] sorted;

        return length;
    }

private:
    Sorter<T, Comparator> *s;
};

int main() {
    size_t size = 0;
    cin >> size;
    auto array = new Segment[size];
    for (size_t i = 0; i < size; ++i) {
        cin >> array[i].start >> array[i].end;
    }

    auto sorter = new Sorter<Segment>(array, size);
    auto solver = new Solver<Segment>(sorter);
    cout << solver->Solve() << endl;

    delete solver;
    return 0;
}