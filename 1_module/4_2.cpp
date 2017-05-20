#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

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
const int CHANK_SIZE = 2;

// Интерфейс класса Дек
class Dequeue {
  private:
    unsigned long long head;
    unsigned long long tail;
    unsigned long long size;
    unsigned long long *data;
    void expand_data_size();
  public:
    Dequeue();
    ~Dequeue();
    void push_front(unsigned long long elem);
    long long pop_front();
    void push_back(unsigned long long elem);
    long long pop_back();
};

}

//---------------main.cpp---------------

int main(int argc, char *argv[])
{

    using std::cin;
    using std::cout;
    using std::endl;

    long long n=0;
    assert(cin>>n);
    assert(n > 0);
    assert(n <= 1000000);

    Deq::Dequeue dequeue;

    int command;
    long long parameter;
    for(long long i=0; i<n; i++) {
        assert(cin>>command);
        assert(command > 0);
        assert(command <= 4);
        assert(cin>>parameter);
//////////////////////////////////
        long lol;
/////////////////////////
        try {
            switch(command) {
              case push_front:
                dequeue.push_front(parameter);
                break;
              case pop_front:
                lol = dequeue.pop_front(); if(lol != parameter) {
                    cout<<"NO"<<lol<<endl;
                    return 0;
                }
                break;
              case push_back:
                dequeue.push_back(parameter);
                break;
              case pop_back:
                lol = dequeue.pop_back(); if(lol != parameter) {
                    cout<<"NO"<<lol<<endl;
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

    cout<<"YES"<<endl;
    return 0;
}

//---------------Dequeue.cpp---------------

Deq::Dequeue::Dequeue() {
    head = 0;
    tail = 0;
    size = Deq::CHANK_SIZE;
    data = nullptr;
    data = new unsigned long long[Deq::CHANK_SIZE];
    if(!data) {
        throw new ErrAlloc;
    }
}

Deq::Dequeue::~Dequeue() {
    if(data != nullptr) {
        delete[] data;
    }
}

void Deq::Dequeue::push_front(unsigned long long elem) {
    std::cout<<"head = "<<head<<std::endl<<"tail  = "<<tail<<std::endl<<"data = ";
    for(size_t i = 0; i < size; i++) std::cout<<data[i]<<" ";
    std::cout<<std::endl;
    size_t temp_ptr = (size + head - 1) % size;
    if( (temp_ptr == (size - 1) && tail == 0) || tail - temp_ptr == 1) {
        expand_data_size();
        temp_ptr = (size + head - 1) % size;
    }
    head = temp_ptr;
    data[head] = elem;
}

long long Deq::Dequeue::pop_front() {
    std::cout<<"head = "<<head<<std::endl<<"tail  = "<<tail<<std::endl<<"data = ";
    for(size_t i = 0; i < size; i++) std::cout<<data[i]<<" ";
    std::cout<<std::endl;
    if(head == tail) {
        return -1;
    }
    unsigned long long result = data[head];
    head = (head + 1) % size;
    return result;
}

void Deq::Dequeue::push_back(unsigned long long elem) {
    std::cout<<"head = "<<head<<std::endl<<"tail  = "<<tail<<std::endl<<"data = ";
    for(size_t i = 0; i < size; i++) std::cout<<data[i]<<" ";
    std::cout<<std::endl;
    size_t temp_ptr = (tail + 1) % size;
    if( (head == (size - 1) && temp_ptr == 0) || temp_ptr - head == 1) {
        expand_data_size();
        temp_ptr = (tail + 1) % size;
    }
    data[tail] = elem;
    tail = temp_ptr;
}

long long Deq::Dequeue::pop_back() {
    std::cout<<"head = "<<head<<std::endl<<"tail  = "<<tail<<std::endl<<"data = ";
    for(size_t i = 0; i < size; i++) std::cout<<data[i]<<" ";
    std::cout<<std::endl;
    if(head == tail) {
        return -1;
    }
    tail = (size + tail - 1) % size;
    return data[tail];
}

void Deq::Dequeue::expand_data_size() {
    unsigned long long *temp = new unsigned long long[size *= 2];
    if(!temp) {
        delete[] data;
        throw new Deq::ErrAlloc;
    }
    memmove(temp, data, size*sizeof(data[0]));
    delete[] data;
    data = temp;
}
