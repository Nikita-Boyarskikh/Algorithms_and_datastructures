#include <iostream>
#include <cassert>
#include <cstring>

/*
 * СОРТИРОВКА ПОЧТИ УПОРЯДОЧЕННОЙ ПОСЛЕДОВАТЕЛЬНОСТИ
 * 
 * Дана последовательность целых чисел a1..an и натуральное число k, такое что для любых i, j:
 * если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность
 * может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  10 4                  |  0 1 2 3 4 5 6 7 8 9      |
 * |  0 4 3 2 1 8 7 6 5 9   |                           |
 */

// Сортировка слиянием
// Сортирует массив arr по возрастанию от left до right, используя буфер buffer.
// Возвращает указатель на отсортированный массив.
template <class T>
T* sort(T* arr,  T* buffer, T left, T right);

// Сливает 2 отсортированные половины
template <class T>
T* merge(T* target, T* left_half, T* right_half, T left, T right);

// Сортировка почти отсортированного массива. Обёртка над sort.
template <class T>
T* MergeSort(T* arr, T* buffer, T n, T k);

// Ввод данных
template <class T>
void input(T* arr, T n);

// Вывод данных
template <class T>
void output(T* arr, T n);

int main(int argc, char *argv[])
{
    long long n, k;

    std::cin >> n >> k;

    assert(n > 0);
    assert(k > 0);

    long long *arr = new long long[n];
    long long *buffer = new long long[2 * k];

    input(arr, n);
    memmove(buffer, arr, 2 * k * sizeof(long long));
    arr = MergeSort(arr, buffer, n, k);
    output(arr, n);

    delete[] arr;
    delete[] buffer;
    return 0;
}

// Ввод данных
template <class T>
void input(T* arr, T n)
{
    for(T i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

// Вывод данных
template <class T>
void output(T* arr, T n)
{
    for(T i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

// Сортировка почти отсортированного массива. Обёртка над sort.
template <class T>
T* MergeSort(T* arr, T* buffer, T n, T k)
{
    T* first_k = sort(arr, buffer, (T)0, (k - 1) % (n - 1));
    T* pref_k = (first_k == buffer) ? arr : buffer;
    T* new_buf = new T();
    for(T i = k; i < n; i += k) {
        T last_indx = i + k - 1 < n ? i + k - 1 : n - 1;
        T* second_k = sort(arr, buffer, i, last_indx);
        merge(&arr[i - k], buffer, &arr[n - 1], (T)0, last_indx);
        output(first_k, k);
        output(second_k, k);
        first_k = second_k;
        pref_k = (first_k == buffer) ? arr + (i % n) : buffer;
    }
    return pref_k;
}

// Cортировкa слиянием
// Сортирует массив arr по возрастанию от left до right, используя буфер buffer.
// Возвращает указатель на отсортированный массив.
template <class T>
T* sort(T* arr, T* buffer, T left, T right)
{
    assert(buffer);
    assert(left <= right);

    if(left == right) {
        arr[left] = buffer[left];
        return arr;
    }

    T middle = (right + left)/2;

    // Сортируем отдельно левую и правую половину
    T* left_half = sort(arr, buffer, left, middle);
    assert(left_half);

    T* right_half = sort(arr, buffer, middle + 1, right);
    assert(right_half);

    T* target = (left_half == buffer) ? arr : buffer;
    return merge(target, left_half, right_half, left, right);
}

// Сливаем 2 отсортированные половины
template <class T>
T* merge(T* target, T* left_half, T* right_half, T left, T right)
{
    T middle = (right + left)/2;
    T l_cur = left, r_cur = middle + 1;
    for(T i = left; i <= right; i++) {
        if(l_cur <= middle && r_cur <= right) {
            if(left_half[l_cur] < right_half[r_cur]) {
                target[i] = left_half[l_cur];
                l_cur++;
            } else {
                target[i] = right_half[r_cur];
                r_cur++;
            }
        }
        // Дописываем оставшиеся элементы
        else if (l_cur <= middle) {
            target[i] = left_half[l_cur];
            l_cur++;
        }
        else {
            target[i] = right_half[r_cur];
            r_cur++;
        }
    }
    return target;
}
