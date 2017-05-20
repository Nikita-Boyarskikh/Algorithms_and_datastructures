#include <iostream>
#include <cassert>
#include <vector>

/*
 * БЫСТРЕЙШАЯ СОРТИРОВКА
 *
 * Отсортировать массив целых чисел.
 * Последовательность случайная, максимальный размер 25000000.
 * Вывести каждое десятое число в отсортированном массиве.
 * За основу должен быть взят алгоритм быстрой сортировки.
 * Набор оптимизаций, которые необходимо реализовать:
 *     1. Оптимизация выбора опорного элемента.
 *     2. Оптимизация Partition.
 *     3. Оптимизация концевой рекурсии - гибридная сортировка с использованием InsertionSort.
 *     4. Написать без рекурсии.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3 0 2 1 5 4 21 4 6 5  |  21                       |
 */

template <class T, CMP>
void qsort(T arr, CMP isLess);

// Сортировка по умолчанию
template <class T>
bool default(T a, T b) { return a < b; }

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::vector;

    vector<long long> arr;
    long long num;
    while(cin >> num) {
        arr.push_back(num);
    }

    assert(arr.size() <= 25000000);

    qsort(arr, default);

    for(int i = 0; i < arr.size(); i+=10) {
        cout << arr.at(i) << ' ';
    }
    cout << endl;

    return 0;
}


void Partition( int* a, int n ) {
    if( n <= 1 ) {
        return 0;
    }

    const int& pivot = a[n - 1];
    int i = 0; j = n – 2;
    while( i <= j ) {
        // Не проверяем, что i < n - 1, т.к. a[n - 1] == pivot.
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= 0 && !( a[j] < pivot ); —j ) {}
        if( i < j ) {
            swap( a[i++], a[j--] );
        }
    }

    swap( a[i], a[n - 1] );
    return i;
}

template <class T, CMP>
void qsort(T a, CMP isLess) {
    int part = Partition(a, n);
    if(part > 0) QuickSort(a, part);
    if(part + 1 < n) QuickSort(a + part + 1, n – (part + 1));
}
