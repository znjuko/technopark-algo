//
// Created by Черных Никита Алекандрович on 3/15/21.
//

// Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин.
// Вначале вводится количество вершин, затем последовательно целочисленные координаты всех вершин в порядке обхода по часовой стрелке.
//
// n < 1000, координаты < 10000.
//
// Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей трапеций под каждой стороной многоугольника.

// i tried to use this formula :
// https://ru.wikipedia.org/wiki/%D0%A4%D0%BE%D1%80%D0%BC%D1%83%D0%BB%D0%B0_%D0%BF%D0%BB%D0%BE%D1%89%D0%B0%D0%B4%D0%B8_%D0%93%D0%B0%D1%83%D1%81%D1%81%D0%B0



#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef struct {
    double x;
    double y;
} Point;


double getSquare(const std::vector<Point>& points) {
    double square = 0;
    auto size = points.size();

    size_t next = 0;
    for(size_t i = 0 ; i < size ; ++i) {
        next = (next + 1) % size;

        auto curr_point = points[i];
        auto next_point = points[next];

        square += (curr_point.x * next_point.y - next_point.x * curr_point.y);
    }

    return abs(square) / 2;
}

int main() {
    size_t size = 0 ;
    cin >> size;

    vector<Point> points(size);

    for(size_t i = 0 ; i < size; ++i) {
        double x = 0 , y = 0 ;
        cin >> x >> y;

        Point p;
        p.x = x;
        p.y = y;

        points[i] = p;
    }

    cout << getSquare(points) << endl;

    return 0;
}