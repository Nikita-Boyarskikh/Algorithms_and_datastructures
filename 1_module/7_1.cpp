#include <iostream>
#include <cassert>
#include <cstring>

/*
 * АТЛЕТЫ
 * 
 * В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N -
 * выстроить из своих тел башню максимальной высоты. Башня - это цепочка атлетов, первый стоит
 * на земле, второй у него на плечах, третий стоит на плечах у второго и т. д.
 * Каждый атлет характеризуется силой si (кг) и массов mi (кг). Сила - это максимальная масса, которую
 * атлет способен держать у себя на плечах.
 * К сожалению, ни один из атлетов не умеет программировать, так как они всю жизни занимались физической подготовкой
 * и у них не было времени на изучение языков программирования. Помогите им, напишите программу, которая определит
 * максимальную высоту башни, которую они могут составить.
 * Известно, что если атлет тяжелее, то он и сильнее:
 *     если mi > mj, то и si > sj.
 * Атлеты равной массы могут иметь различную силу.
 * 
 * Формат входных данных
 * Вход содержит только пары целых чисел - массу и силу атлетов. Число атлетов 1 <= n <= 100000.
 * Масса и сила являются положительными целыми числами меньше, чем 2000000.
 * 
 * Формат выходных данных
 * Выход должен содержать натуральное число - максимальную высоту башни.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3 4                   |  3                        |
 * |  2 2                   |                           |
 * |  7 6                   |                           |
 * |  4 5                   |                           |
 */

// Ограничивающие значения по условию
#define MAX_COUNT 100000
#define MAX_VALUE 2000000

// Каждый атлет характеризуется своей массой и силой
struct athlete {
    long weight, force;
};

// Начальный размер массива атлетов
const int BUF_SIZE = 8;

// Ввод и валидация данных.
// Получает с STDIN и записывает в массив данные.
size_t input_data(athlete *athletes, long &counter);

// Сортировка слиянием.
// Сортирует массив athletes длины count по force по возрастанию и weight по возрастанию.
// Возвращает указатель на отсортированный массив.
athlete * MergeSort(athlete * athletes, const long count);

// Непосредственно реализация сортировки слиянием.
// Сортирует массив athletes от left до right, используя буфер buffer.
// Возвращает указатель на отсортированный массив.
athlete * sort(athlete * athletes, athlete * buffer, long left, long right);

// Реаллоцирует память под массив athletes
void ath_realloc(athlete **athletes, long &buf_size);

int main(int argc, char *argv[])
{

    using std::cin;
    using std::cout;
    using std::endl;

    // Инициализация значений и выделение памяти
    long buf_size = BUF_SIZE, counter = 0, result = 1;
    athlete *athletes = new athlete[buf_size];
    assert(athletes);

    // Ввод данных
    input_data(athletes, counter);

    if(counter < 2) {
        delete[] athletes;
        cout<<counter<<endl;
        return 0;
    }

    // Сортировка атлетов по массе и силе по возрастанию
    athletes = MergeSort(athletes, counter);
    assert(athletes);

    long long total_weight = athletes[counter - 1].weight;
            cout<<athletes[counter-1].weight<<' '<<athletes[counter-1].force<<endl;

    // Подсчёт количества атлетов, удовлетворяющих условиям задачи
    for(long i = counter - 1; i > 0; i--) {
            cout<<athletes[i-1].weight<<' '<<athletes[i-1].force<<endl;
        if(athletes[i-1].force >= total_weight) {
            total_weight += athletes[i-1].weight;
            result++;
        }
    }

    // Вывод результатов
    assert(cout<<result<<endl);

    delete[] athletes;

    return 0;
}

// Ввод и валидация данных
size_t input_data(athlete *athletes, long &counter) {
    long athletes_size = BUF_SIZE * sizeof(athletes[0]);
    while(std::cin>>athletes[counter].weight>>athletes[counter].force) {
        // Валидация данных
        assert(athletes[counter].weight <= MAX_VALUE);
        assert(athletes[counter].force <= MAX_VALUE);
        assert(++counter <= MAX_COUNT);

        // Реаллокация памяти в случае её нехватки
        if(counter == BUF_SIZE) {
            ath_realloc(&athletes, athletes_size);
        }
    }
    return athletes_size;
}

// Реаллокация памяти
void ath_realloc(athlete **athletes, long &buf_size) {
    athlete *temp_buf = new athlete[buf_size *= 2];
    assert(temp_buf);
    assert(memmove(temp_buf, *athletes, buf_size));
    delete[] *athletes;
    *athletes = temp_buf;
}

// Сортировка слиянием
// Сортирует массив athletes длины count по weight по возрастанию и force по возрастанию.
// Возвращает указатель на отсортированный массив.
athlete * MergeSort(athlete * athletes, const long count)
{
    assert(athletes);
    assert(count <= MAX_COUNT);

    athlete *buffer = new athlete[count];
    assert(buffer);
    memcpy(buffer, athletes, count*sizeof(athletes[0]));

    athletes = sort(athletes, buffer, 0, count - 1);
    for(int i = 0; i<count; i++)
            std::cout<<athletes[i].weight<<' '<<athletes[i].force<<std::endl;

    delete[] buffer;

    return athletes;
}

// Непосредственно реализация сортировки слиянием.
// Сортирует массив athletes от left до right, используя буфер buffer.
// Возвращает указатель на отсортированный массив.
athlete * sort(athlete * athletes, athlete * buffer, long left, long right)
{
    assert(athletes);
    assert(buffer);
    assert(left <= right);

    if(left == right) {
        athletes[left] = buffer[left];
        return athletes;
    }

    long middle = (right + left)/2;

    // Сортируем отдельно левую и правую половину
    athlete *left_half = sort(athletes, buffer, left, middle);
    assert(left_half);

    athlete *right_half = sort(athletes, buffer, middle + 1, right);
    assert(right_half);

    // Сливаем 2 отсортированные половины
    athlete *target = (left_half == buffer) ? athletes : buffer;

    long l_cur = left, r_cur = middle + 1;
    for(long i = left; i <= right; i++) {
        if(l_cur <= middle && r_cur <= right) {
            // Если сила атлета из левой половины больше, пишем его на выход
            if(left_half[l_cur].weight < right_half[r_cur].weight) {
                target[i] = left_half[l_cur];
                l_cur++;
            }
            // Если сила атлета из правой половины больше, пишем его на выход
            else if(left_half[l_cur].weight > right_half[r_cur].weight) {
                target[i] = right_half[r_cur];
                r_cur++;
            // При равных силах сравниваем массы
            } else {
                // Если масса атлета из левой половины меньше, пишем его на выход
                if(left_half[l_cur].force < right_half[r_cur].force) {
                    target[i] = left_half[l_cur];
                    l_cur++;
                // Если масса атлета из правой половины меньше, пишем его на выход
                } else {
                    target[i] = right_half[r_cur];
                    r_cur++;
                }
            }
        }
        // Дописываем оставшихся атлетов из левой половины
        else if (l_cur <= middle) {
            target[i] = left_half[l_cur];
            l_cur++;
        }
        // Дописываем оставшихся атлетов из правой половины
        else {
            target[i] = right_half[r_cur];
            r_cur++;
        }
    }
    return target;
}
