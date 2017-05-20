#include <iostream>
#include <cassert>

/*
 * BINARY MSD ДЛЯ LONG LONG
 *
 * Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6.
 * Отсортировать массив методом MSD по битам (бинарный QuickSort).
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  4 7 1000000              |
 * |  4 1000000 7           |                           |
 */

// Функция ввода и валидации данных.
void input(unsigned long long* arr, size_t n);

// Возвращает digit бит числа value
unsigned char bit(long long int value, size_t digit);

// Сортировка MSD по битам.
// Сортирует массив arr от left до right по digit биту и старшим.
template <class T>
void BMSD(T* arr, size_t left, size_t right, size_t digit);

// Функция вывода данных.
void output(unsigned long long* arr, size_t n);

int main(int argc, char *argv[])
{
    long int n;
    std::cin >> n;
    assert(n > 0 && n <= 1000000);

    unsigned long long int *arr = new unsigned long long int[n];

    input(arr, (size_t)n);
    BMSD(arr, 0, (size_t)(n - 1), 8*sizeof(long long));
    output(arr, (size_t)n);

    delete[] arr;
    return 0;
}

// Функция ввода и валидации данных.
void input(unsigned long long* arr, size_t n)
{
    for(size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

// Функция вывода данных.
void output(unsigned long long* arr, size_t n)
{
    for(size_t i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

// Возвращает digit бит числа value
template <class T>
unsigned char bit(T value, size_t digit)
{
    return (value >> (digit - 1))&1;
}

// Сортировка MSD по битам.
// Сортирует массив arr от left до right по digit биту и старшим.
template <class T>
void BMSD(T* arr, size_t left, size_t right, size_t digit)
{
    if(right <= left || digit == 0) return;
    size_t i = left, j = right;
    while(i != j) {
        while(bit(arr[i], digit) == 0 && i < j ) i++;
        while(bit(arr[j], digit) == 1 && i < j ) j--;
        if(i != j) std::swap(arr[i], arr[j]);
    }
    if( bit(arr[j], digit) == 0 ) j++;
    BMSD(arr, left, j - 1, digit - 1);
    BMSD(arr, j, right, digit - 1);
}
