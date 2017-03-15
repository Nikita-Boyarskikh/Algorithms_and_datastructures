#include <iostream>
#include <cstring>
#include <cassert>

/*
 * Написать структуру данных, обрабатывающую команы push* и pop*.
 *
 * Формат входных данных.
 * В первой строке количество команд n. n <= 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 * Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 * Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 * Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается "-1"
 *
 * Формат выходных данных
 * Требуется написать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * Реализовать дек с динамическим зацикленным буфером
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  YES                      |
 * |  1 44                  |                           |
 * |  3 50                  |                           |
 * |  2 44                  |                           |
 * |------------------------+---------------------------|
 * |  2                     |  YES                      |
 * |  2 -1                  |                           |
 * |  1 10                  |                           |
 * |------------------------+---------------------------|
 * |  2                     |  NO                       |
 * |  3 44                  |                           |
 * |  4 66                  |                           |
 */

// Перечисление пользовательских команд
enum command {
    push_front=1,
    pop_front,
    push_back,
    pop_back
};

//---------------Dequeue.h---------------
namespace Deq {

// Общий класс исключений для Dequeue
class Exception : public std::exception {};
// Исключение, возникающее при ошибке выделения динамической памяти
class ErrAlloc : public Exception {};

// Начальный размер буфера
const int CHANK_SIZE = 64;

// Интерфейс класса Дек
class Dequeue {
  private:
    size_t head;
    size_t tail;
    size_t size;
    int *data;
  public:
    Dequeue();
    ~Dequeue();
    void push_front(int elem);
    int pop_front();
    void push_back(int elem);
    int pop_back();
};

}

//---------------main.cpp---------------

int main(int argc, char *argv[])
{

    using std::cin;
    using std::cout;

    int n=0;
    assert(cin>>n);
    assert(n <= 1000000);

    Deq::Dequeue dequeue;

    int command;
    int parameter;
    for(int i=0; i<n; i++) {
        assert(cin>>command);
        assert(command > 0);
        assert(command <= 4);
        assert(cin>>parameter);
        try {
            switch(command) {
              case push_front:
                dequeue.push_front(parameter);
                break;
              case pop_front:
                if(dequeue.pop_front() != parameter) {
                    cout<<"NO";
                    return 0;
                }
                break;
              case push_back:
                dequeue.push_back(parameter);
                break;
              case pop_back:
                if(dequeue.pop_back() != parameter) {
                    cout<<"NO";
                    return 0;
                }
                break;
            }
        }
        catch (Deq::Exception)
        {
            throw;
        }
    }

    cout<<"YES";
    return 0;
}

//---------------Dequeue.cpp---------------

Deq::Dequeue::Dequeue() {
    head = 0;
    tail = 0;
    size = Deq::CHANK_SIZE;
    data = nullptr;
    data = new int[Deq::CHANK_SIZE];
    if(!data) {
        throw new ErrAlloc;
    }
}

Deq::Dequeue::~Dequeue() {
    if(data != nullptr) {
        delete[] data;
    }
}

void Deq::Dequeue::push_front(int elem) {
    head = (Deq::CHANK_SIZE + head - 1) % Deq::CHANK_SIZE;
    data[head] = elem;
    if( (tail == (Deq::CHANK_SIZE - 1) && head == 0) || head - tail == 1) {
        int *temp = new int[size *= 2];
        if(!temp) {
            throw new Deq::ErrAlloc;
        }
        if(!memcpy(temp, &data[head], size/2) || !memcpy(&temp[size/2], data, size - head)) {
            delete[] temp;
            delete[] data;
            throw new Deq::ErrAlloc;
        }
        delete[] data;
        data = temp;
    }
}

int Deq::Dequeue::pop_front() {
    if(head == tail) {
        return -1;
    }
    int result = data[head];
    head = (head + 1) % Deq::CHANK_SIZE;
    return result;
}

void Deq::Dequeue::push_back(int elem) {
    data[tail] = elem;
    tail = (tail + 1) % Deq::CHANK_SIZE;
    if( ( (tail == (Deq::CHANK_SIZE - 1)) && (head == 0) ) || (head - tail == 1) ) {
        if( !realloc(data, size *= 2) ) {
            delete[] data;
            throw new Deq::ErrAlloc;
        }
    }
}

int Deq::Dequeue::pop_back() {
    if(head == tail) {
        return -1;
    }
    tail = (tail - 1) % Deq::CHANK_SIZE;
    return data[tail];
}
