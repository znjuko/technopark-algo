//
// Created by Черных Никита Алекандрович on 3/17/21.
//


//Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
// A[0..n-1] и B[0..m-1]. n » m.
// Найдите их пересечение.
// Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A..
// В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.


#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    bool found;
    int place;
} Place;

Place binarySearch(const vector<int> &array, const int &el, const int &start, const int &end) {
    int left_border = start;
    int right_border = end - 1;
    int middle = 0;

    while (left_border <= right_border) {
        middle = (left_border + right_border) / 2;

        if (el < array[middle]) {
            right_border = middle - 1;
            continue;
        }

        if (el > array[middle]) {
            left_border = middle + 1;
            continue;
        }

        return Place{true, middle};
    }


    return Place{false, middle};
}

vector<int> intersection(const vector<int> &from, const vector<int> &what) {
    vector<int> result;
    Place place;
    int start = 0, end = from.size();

    for (auto elem : what) {
        place = binarySearch(from, elem, start, end);
        start = place.place;

        if (place.found) {
            result.push_back(elem);
        }
    }

    return result;
}


int main() {
    size_t n, m;
    cin >> n >> m;
    vector<int> first(n, 0);
    vector<int> second(m, 0);;
    for (size_t i = 0; i < n; ++i) {
        cin >> first[i];
    }
    for (size_t i = 0; i < m; ++i) {
        cin >> second[i];
    }

    auto response = intersection(first, second);

    for (auto elem : response) {
        cout << elem << " ";
    }

    cout << endl;

    return 0;
}