#include <iostream>
#include <cassert>

/*
 * ВЫСОКАЯ ПИРАМИДА
 * 
 * Дано N кубиков. Требуется определить, каким количеством способов можно выстроить из этих кубиков пирамиду.
 * Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
 * N <= 200.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  3                        |
 * |  5                     |  7                        |
 * |  7                     |  15                       |
 */

// Ограничивающие значение, заданные в условии
#define MAX_CUBES 200

// Прототип функции, вычисляющей количество возможных "высоких" пирамид, которые можно построить из cubes кубиков.
// Функция возвращает количество возможных вариантов
unsigned long long high_piramid_variants(size_t cubes);

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;

    // Ввод количества кубиков и его валидация
    int N;
    assert(cin>>N);
    assert(N > 0);
    assert(N <= MAX_CUBES);
    // Сохраняем в переменную безопасного типа
    size_t cubes = N;

    // Вычисляем результат и выводим на экран
    unsigned long long result = high_piramid_variants(cubes);
    assert(cout<<result<<endl);

    return 0;
}

// Функции, вычисляющая количество возможных "высоких" пирамид, которые можно построить из cubes кубиков.
// Функция возвращает количество возможных вариантов
unsigned long long high_piramid_variants(size_t cubes)
{
    assert(cubes <= MAX_CUBES);
    unsigned long long result = 0;

    // Выделяем память для сохранения половины таблицы N x N, так как нам для вычислений
    // понадобится только левая верхняя половина
    unsigned long long **variants = new unsigned long long *[cubes];
    assert(variants);
    for(size_t i = 0; i < cubes; i++) {
        variants[i] = new unsigned long long [cubes - i];
        assert(variants[i]);
    }

    // Инициализируем граничные значения
    for(size_t i = 0; i < cubes; i++) {
        // Пирамиду любой допустимой ширины из 1 кубика можно построить только одну
        variants[0][i] = 1;
        // Пирамиду ширины 1 можно построить только 1 - стольбец из i кубиков
        variants[i][0] = 1;
    }

    // Заполняем таблицу, опираясь на которую можно найти ответ на поставленную задачу
    for(size_t left = 1; left < cubes; left++) {
        for(size_t width = 1; width + left < cubes; width++) {
            if(left > width) {
                variants[left][width] = variants[left][width - 1] + variants[left - width - 1][width];
            } else {
                variants[left][width] = variants[left][width - 1];
            }
        }
    }

    for(size_t i = 0; i < cubes; i++) {
        result += variants[cubes - i - 1][i];
    }

    // Освобождения памяти
    for(size_t i = 0; i < cubes; i++) {
        delete[] variants[i];
    }
    delete[] variants;

    return result;
}
