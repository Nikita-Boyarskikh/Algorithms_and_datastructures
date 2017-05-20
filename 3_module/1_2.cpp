#include <iostream>
#include <cassert>
#include <string>
#include <vector>

/*
 * ХЕШ-ТАБЛИЦА
 *
 * Реализуйте структуру данных типа “множество строк” на основе динамической
 * хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных
 * латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения
 * многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
 * при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
 * 
 * Структура данных должна поддерживать операции добавления строки в множество,
 * удаления строки из множества и проверки принадлежности данной строки множеству.
 * 
 * Для разрешения коллизий используйте двойное хеширование.
 *
 * Формат входных данных
 * 
 * Каждая строка входных данных задает одну операцию над множеством. Запись операции
 * состоит из типа операции и следующей за ним через пробел строки, над которой
 * проводится операция.
 * 
 * Тип операции – один из трех символов:
 *     + означает добавление данной строки в множество;
 *     - означает удаление строки из множества;
 *     ? означает проверку принадлежности данной строки множеству.
 * 
 * При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом
 * множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он
 * присутствует в этом множестве.
 * 
 * Формат выходных данных
 * 
 * Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в
 * зависимости от того, встречается ли данное слово в нашем множестве.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  + hello               |  OK                       |
 * |  + bye                 |  OK                       |
 * |  ? bye                 |  OK                       |
 * |  + bye                 |  FAIL                     |
 * |  - bye                 |  OK                       |
 * |  ? bye                 |  FAIL                     |
 * |  ? hello               |  OK                       |
 */

const std::string NIL = "NIL";
const std::string DEL = "DEL";

const int HASH_CONST1 = 307;
const int HASH_CONST2 = 401;

template <class T>
struct Hasher {
    Hasher() {};
    size_t operator() ( T str, size_t size, bool type );
};

template <class T, class H = Hasher<T> >
class Set {
  private:
    const static size_t initial_size = 8;

    T* arr;
    H _hasher;
    size_t elems;
    size_t size;

    void expand();

  public:
    Set();
    ~Set();
    bool add( T data );
    bool del( T data );
    bool has( T data );
};

int main(int argc, char *argv[])
{
    char command;
    std::string str;
    Set<std::string> set;
    Hasher<std::string> h;
    while( (std::cin >> command) && std::cin.ignore() && getline(std::cin, str) ) {
        switch( command ) {
          case '+':
              std::cout << (set.add(str) ? "OK" : "FAIL");
              break;
          case '-':
              std::cout << (set.del(str) ? "OK" : "FAIL");
              break;
          case '?':
              std::cout << (set.has(str) ? "OK" : "FAIL");
              break;
          default:
              throw std::exception();
        }
        std::cout << std::endl;
    }

    return 0;
}

template<class T>
size_t Hasher<T>::operator() ( T str, size_t size, bool type )
{
    size_t hash = 0;
    for( size_t i = 0; i < str.size(); i++ ) {
        hash = ( 2*(hash*(type ? HASH_CONST1 : HASH_CONST2) + str[i]) + 1 ) % size;
    }
    return hash;
}

template <class T, class H>
Set<T, H>::Set()
{
    elems = 0;
    size = initial_size;
    arr = new T[size];
    for( size_t i = 0; i < size; i++ ) {
        arr[i] = NIL;
    }
}

template <class T, class H>
bool Set<T, H>::add( T data )
{
    if( elems >= size * 3/4 ) {
        expand();
    }

    bool finded = false;
    size_t indx;
    size_t hash1 = _hasher( data, size, 0 );
    size_t hash2 = _hasher( data, size, 1 );
    for( size_t i = 0; i < size; i++ ) {
        size_t hash = (hash1 + i*hash2 ) % size;
        if( arr[hash] == data ) {
            return false;
        }
        if( arr[hash] == NIL || arr[hash] == DEL ) {
            indx = hash;
            finded = true;
            if( arr[hash] == NIL ) {
                break;
            }
        }
    }
    if( finded ) {
        arr[indx] = data;
        elems++;
    }
    return finded;
}

template <class T, class H>
bool Set<T, H>::del( T data )
{
    size_t hash1 = _hasher( data, size, 0 );
    size_t hash2 = _hasher( data, size, 1 );
    for( size_t i = 0; i < size; i++ ) {
        size_t hash = (hash1 + i*hash2 ) % size;
        if( arr[hash] == NIL ) {
            return false;
        }
        if( arr[hash] == data ) {
            arr[hash] = DEL;
            elems--;
            return true;
        }
    }

    return false;
}

template <class T, class H>
bool Set<T, H>::has( T data )
{
    size_t hash1 = _hasher( data, size, 0 );
    size_t hash2 = _hasher( data, size, 1 );
    for( size_t i = 0; i < size; i++ ) {
        size_t hash = (hash1 + i*hash2 ) % size;
        if( arr[hash] == NIL ) {
            return false;
        }
        if( arr[hash] == data ) {
            return true;
        }
    }

    return false;
}

template <class T, class H>
void Set<T, H>::expand()
{
    T* tmp = arr;
    arr = new T[ size *= 2 ];
    for( size_t i = 0; i < size; i++ ) {
        arr[i] = NIL;
    }

    for( size_t i = 0; i < size/2; i++ ) {
        if( tmp[i] != DEL && tmp[i] != NIL ) {
            add(tmp[i]);
            elems--;
        }
    }

    delete[] tmp;
}

template <class T, class H>
Set<T, H>::~Set()
{
    delete[] arr;
}
