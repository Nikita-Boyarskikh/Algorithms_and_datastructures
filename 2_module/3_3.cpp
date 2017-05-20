#include <iostream>
#include <cassert>

/*
 * ЗАКРАСКА ПРЯМОЙ 1
 * 
 * Необходимо реализовать и использовать локальную пирамидальную сортировку 
 * (без использования дополнительной памяти). Общее время работы алгоритма O(n log n). 
 * На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого
 * отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  5                        |
 * |  1 4                   |                           |
 * |  7 8                   |                           |
 * |  2 5                   |                           |
 */

// Шаблонный класс кучи.
template <class T>
class Heap {
  private:
    T* data;
    unsigned long long int size;
    bool (*cmp)(T, T);
    void siftDown(unsigned long long int indx);
  public:
    Heap(T* arr, unsigned long long int size, bool (*cmp)(T, T));
    T Extract();
};

// Конец отрезка
struct end {
    char type; // Начало или конец
    long long int x;
    end(char atype, long long int coord) : type(atype), x(coord) {};
    end() {};
};

// Функция сравнения 2-х концов для создания минимальной кучи на концах.
bool min(end a, end b);

// Шаблонная функция пирамидальной сортировки.
template <class T>
void sort(T* arr, unsigned long long int size, bool (*cmp)(T, T));

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;

    long long int n;
    cin >> n;
    assert(n > 0);

    end* arr = new end[2*n];
    assert(arr);

    for(unsigned long long int i = 0; i < (unsigned long long int)n; i++) {
        long long int begin_x, end_x;
        cin >> begin_x >> end_x;
        arr[i] = end(1, begin_x);
        arr[n + i] = end(-1, end_x);
    }

    sort(arr, 2*n, min);

    unsigned long long int width = 0, length = 0, start = 2*n;
    for(unsigned long long int i = 0; i < (unsigned long long int)2*n; i++) {
        // Считаем толщину линии
        width += arr[i].type;
        // Если кончилась закрашенная область
        if(width == 0) {
            length += arr[i].x - arr[start].x;
            start = 2*n;
        }
        // Если началась закрашенная область
        if(width > 0 && start == (unsigned long long int)2*n) {
            start = i;
        }
    }

    assert(width == 0);
    assert(length >= 0);

    cout << length << endl;
    delete[] arr;

    return 0;
}

// Шаблонная функция пирамидальной сортировки.
template <class T>
void sort(T* arr, unsigned long long int size, bool (*cmp)(T, T))
{
    Heap<T> heap(arr, size, min);
    for(unsigned long long int i = 0; i < size; i++) {
        T elem = heap.Extract();
        arr[size - i - 1] = elem;
    }
}

// Функция сравнения 2-х концов для создания минимальной кучи на концах.
bool min(end a, end b)
{
    if(a.x == b.x) return a.type >= b.type;
    return a.x < b.x;
}

// Публичные методы класса кучи
template <class T>
Heap<T>::Heap(T* arr, unsigned long long int size, bool (*cmp)(T, T))
{
    data = arr;
    this->size = size;
    this->cmp = cmp;
    for(long long int i = size/2 - 1; i >= 0; i--) siftDown(i);
}

template <class T>
T Heap<T>::Extract()
{
    assert(size > 0);
    end result = data[0];
    data[0] = data[--size];
    if(size > 0) siftDown(0);
    return result;
}

// Приватные методы класса кучи
template <class T>
void Heap<T>::siftDown(unsigned long long int indx)
{
    unsigned long long int first_child = 2*indx + 1;
    unsigned long long int second_child = 2*indx + 2;
    unsigned long long int min_child = indx;

    if(first_child < size && cmp(data[min_child], data[first_child]))
        min_child = first_child;
    if(second_child < size && cmp(data[min_child], data[second_child]))
        min_child = second_child;

    if(min_child != indx) {
        std::swap(data[indx], data[min_child]);
        siftDown(min_child);
    }
}
