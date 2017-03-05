#include <iostream>
#include <cassert>

/*
 * Вычислить площадь выпуклого n-угольника, заданного координатами своих вершин в порядке обхода против числовой стрелки.
 * n < 1000, координаты < 10000.
 * Указание. Для вычисления площади n-угольника можно посчитать сумму ориентированных площадей
 * трапеций под каждой стороной многоугольника.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  1.5                      |
 * |  0 1                   |                           |
 * |  1 0                   |                           |
 * |  2 2                   |                           |
 */

// Структура, хранящая декартовы двухмерные координаты x и y
struct coord {
    int x;
    int y;
};

// Прототип функции, считающей площадь замкнутого многоугольника с количеством вершин number.
// Координаты вершин находятся в массиве vertices, перечисленные против часовой стрелки.
float square(coord *vertices, int number);

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;

    int n = 0;
    assert(cin>>n);
    assert(n < 1000);
    assert(n > 2);

    coord *vertices = new coord[n];

    for(int i=0; i<n; i++) {
        int x, y;
        assert(cin>>x);
        assert(cin>>y);
        assert(abs(x) < 10000);
        assert(abs(y) < 10000);

        vertices[i].x = x;
        vertices[i].y = y;
    }

    cout<<square(vertices, n);

    delete[] vertices;
    return 0;
}

// Функция, считающая площадь замкнутого многоугольника с количеством вершин number.
// Координаты вершин находятся в массиве vertices, перечисленные против часовой стрелки.
float square(coord *vertices, int number)
{
    int result = 0;
    int delta_x, sum_y;
    for(int i=1; i<number; i++) {
        delta_x = vertices[i-1].x - vertices[i].x;
        sum_y = vertices[i-1].y + vertices[i].y;
        result += delta_x * sum_y;
    }
    delta_x = vertices[number-1].x - vertices[0].x;
    sum_y = vertices[number-1].y + vertices[0].y;
    result += delta_x * sum_y;
    return result/2;
}
