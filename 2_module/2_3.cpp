#include <iostream>
#include <cassert>

/*
 * ТУПИКИ
 * 
 * Решение предполагает использование кучи.
 *
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички. Этот вокзал является
 * их конечной станцией. Дано расписание движения электричек, в котором для каждой электрички
 * указано время ее прибытия, а также время отправления в следующий рейс. Электрички в
 * расписании упорядочены по времени прибытия. Когда электричка прибывает, ее ставят в
 * свободный тупик с минимальным номером. При этом если электричка из какого-то тупика
 * отправилась в момент времени X, то электричку, которая прибывает в момент времени X, в этот
 * тупик ставить нельзя, а электричку, прибывающую в момент X+1 — можно.
 * В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
 * Напишите программу, которая по данному расписанию определяет, какое минимальное
 * количество тупиков требуется для работы вокзала.
 * 
 * Формат входных данных.
 * Вначале вводится n - количество электричек в расписании. Затем
 * вводится n строк для каждой электрички, в строке - время прибытия и время отправления. Время -
 * натуральное число от 0 до 10^9. Строки в расписании упорядочены по времени прибытия.
 * 
 * Формат выходных данных.
 * Натуральное число - минимальное количеством тупиков.
 * 
 * Максимальное время: 50мс, память: 5Мб.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  1                     |  1                        |
 * |  10 20                 |                           |
 * |------------------------+---------------------------|
 * |  2                     |  2                        |
 * |  10 20                 |                           |
 * |  20 25                 |                           |
 * |------------------------+---------------------------|
 * |  3                     |  2                        |
 * |  10 20                 |                           |
 * |  20 25                 |                           |
 * |  21 30                 |                           |
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

// Событие - прибытие или отправление.
struct event {
    char value;
    size_t time;
    event(char val, size_t t) : value(val), time(t) {};
    event() {};
};

// Функция сравнения 2-х событий для создания минимальной кучи на событиях.
bool min(event a, event b);

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;

    long long int n;
    cin >> n;

    event* arr = new event[2*n];
    assert(arr);

    for(unsigned long long int i = 0; i < (unsigned long long int)n; i++) {
        // При заланных условиях можно соптимизировать создание кучи и предварительно отсортировать
        // входные данные вставками, но я этого делать не буду, потому что не по ТЗ :)
        long int arrive, leave;
        cin >> arrive >> leave;
        assert(arrive >= 0 && arrive <= 1000000000);
        assert(leave >= 0 && leave <= 1000000000);
        arr[i] = event(1, (size_t)arrive);
        arr[n + i] = event(-1, (size_t)leave);
    }

    Heap<event> heap(arr, 2*n, min);

    size_t result = 0, count = 0;

    for(long long int i = 0; i < 2*n; i++) {
        event event = heap.Extract();
        count += event.value;
        if(result < count) result = count;
    }

    cout << result << endl;
    delete[] arr;

    return 0;
}

// Функция сравнения 2-х событий для создания минимальной кучи на событиях.
bool min(event a, event b)
{
    if(a.time == b.time) return a.value >= b.value;
    return a.time < b.time;
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
    event result = data[0];
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

    if(first_child < size && !cmp(data[min_child], data[first_child]))
        min_child = first_child;
    if(second_child < size && !cmp(data[min_child], data[second_child]))
        min_child = second_child;

    if(min_child != indx) {
        std::swap(data[indx], data[min_child]);
        siftDown(min_child);
    }
}
