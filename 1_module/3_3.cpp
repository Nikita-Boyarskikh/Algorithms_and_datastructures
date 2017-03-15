#include <iostream>
#include <cassert>

/*
 * Даны два массива неповторяющихся целых чисел, упорядоченных по возрастанию. A[0..n-1] и B[0..m-1].
 * n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
 * n, k <= 10000.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  5                     |  1 3 5                    |
 * |  3                     |                           |
 * |  1 2 3 4 5             |                           |
 * |  1 3 5                 |                           |
 */


// Прототип функции, находящей пересечение массивов first (длины first_size) и second (длины second_size).
// Последним параметром принимает указатель на массив result, в котором будет располагаться найденное множество.
// Функция возвращает фактический размер полученного множества (в количестве элементов).
size_t intersection(int *first, size_t first_size, int *second, size_t second_size, int* result);

// Прототип функции двоичного поиска элемента x в массиве array длины size с позиции left до позиции right.
// Функция возвращает позицию найденного элемента или -1, если элемент не найден.
int binary_search(int x, int *array, size_t left, size_t righ);

int main(int argc, char *argv[])
{

    using std::cin;
    using std::cout;
    using std::endl;

    // Ввод и проверка корректности длины массивов
    int n, m;
    assert(cin>>n>>m);
    assert(n > 0);
    assert(n <= 10000);
    assert(m > 0);
    assert(m <= 10000);

    // Переписываем значения после валидации в безопасный тип
    size_t A_size = n, B_size = m;

    // Выделяем память
    int* A = new int[A_size];
    int* B = new int[B_size];
    int* result = new int[B_size];

    // Ввод самих массивов
    for(size_t i=0; i<A_size; i++) {
        assert(cin>>A[i]);
    }
    for(size_t i=0; i<B_size; i++) {
        assert(cin>>B[i]);
    }

    // Нахождение пересечения введённых множеств чисел
    size_t result_length = intersection(A, A_size, B, B_size, result);

    // Вывод результатов
    if(result_length > 0) {
        cout<<result[0];
        for(size_t i=1; i<result_length; i++) {
            cout<<' '<<result[i];
        }
        cout<<endl;
    }

    delete[] A;
    delete[] B;
    delete[] result;

    return 0;
}

/************************************************************************************************************
 * ПРИВЕДЁННЫЙ АЛГОРИТМ ЗА O(m * log(k)) ЭФФЕКТИВЕН ТОЛЬКО ПРИ БОЛЬШОМ КОЛИЧЕСТВЕ ВХОДНЫХ ДАННЫХ.           *
 * ПРИ СРАВНИТЕЛЬНО НЕБОЛЬШОЙ ВЫБОРКЕ БУДЕТ ЭФФЕКТИВНЕЕ РАБОТАТЬ АЛГОРИТМ, АНАЛОГИЧНЫЙ АЛГОРИТМУ СЛИЯНИЯ,   *
 * КОТОРЫЙ ИСПОЛЬЗУЕТСЯ В MERGE SORT, ТОЛЬКО ВМЕСТО ВЫБОРА НАИМЕНЬШЕГО ИЛИ НАИБОЛЬШЕГО И ЗАПИСИ ОБОИХ,      *
 * НЕОБХОДИМО ВЫБРАТЬ ТОЛЬКО РАВНЫЕ. ЭФФЕКТИВНОСТЬ ПРИВЕДЁННОГО АЛЬТЕРНАТИВНОГО АЛГОРИТМА БУДЕТ O(n + m).   * 
 ************************************************************************************************************/

// Функция, находящая пересечение массивов first (длины first_size) и second (длины second_size).
// Последним параметром принимает указатель на массив result, в котором будет располагаться найденное множество.
// Функция возвращает фактический размер полученного множества (в количестве элементов).
size_t intersection(int *first, size_t first_size, int *second, size_t second_size, int* result)
{
    assert(first_size > second_size);
    assert(first);
    assert(second);
    assert(result);

    int result_length = 0;

    // Изначально у нас нет последнего найденного элемента
    int last_find = -1;
    for(size_t i=0; i<second_size; i++) {

        // Флаг, сигнализирующий о том, что найден элемент
        bool find = false;
        // Позиция искомого элемента в первом массиве
        size_t pos;

        // Проматываем по степеням двойки первый массив, начиная с элемента, следующего за последним найденным
        // (так как оба массива, по условию, отсортированы), пока не найдём элемент, больший или равный текущему во втором массиве
        size_t powered2 = 1;
        size_t right = last_find + 1;

        do {
            powered2 *= 2;
            right += powered2;

            // Досрочно завершаем поиск, если при перемотке наткнулись на искомый элемент
            if(first[right] == second[i]) {
                find = true;
                pos = right;
            }
        } while(!find && right < first_size && first[right] < second[i]);

        // Вычисляем левую границу поиска
        int left = right - powered2;
        if(left < 0) {
            left = 0;
        }

        // Всё пролистали - ищем элемент до конца
        if(right > first_size) {
            right = first_size;
        }

        // Если не нашли элемент на границе, ищем на интервале
        if(!find) {
            // Ищем элемент в выявленном участке методом половинного деления, в случае ошибки, приравниваем его длине массива
            int search_result = binary_search(second[i], first, left, right);
            if(search_result < 0) {
                find = false;
            } else {
                find = true;
                pos = search_result;
            }
        }

        // Запоминаем элемент, если нашли, и его позицию
        if(find) {
            result[result_length++] = first[pos];
            last_find = pos;
        } else {
            last_find = left;
        }
    }

    return result_length;
}

// Функции двоичного поиска элемента x в массиве array длины size с позиции left до позиции right.
// Функция возвращает позицию найденного элемента или -1, если элемент не найден.
int binary_search(int x, int *array, size_t left, size_t right)
{
    assert(array);
    assert(left <= right);

    if(array[left] == x) {
        return left;
    }

    while(left < right) {
        size_t middle = (right + left)/2;
        if(x <= array[middle]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }

    // Вернём -1, если не нашли
    return ( array[left] != x ) ? -1 : left;
}
