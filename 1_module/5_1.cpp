#include <iostream>
#include <cassert>
#include <cstring>

/*
 * СКОБОЧНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ
 * 
 * Дан фрагмент последовательности скобок, состоящей из символов (){}[].
 * Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив корректную
 * последовательность.
 * Длины исходной последовательности <= 200000.
 * 
 * Формат входных данных.
 * Строка, содержащая символы (){}[] и, возможно, перевод строки.
 * 
 * Формат выходных данных.
 * Если возможно - вывести минимальную корректную последовательность,
 * иначе - напечатать "IMPOSSIBLE".
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  {}[[[[{}[]            |  {}[[[[{}[]]]]]           |
 * |  {][[[[{}[]            |  IMPOSSIBLE               |
 * |  ]()}[](({}            |  {[]()}[](({}))           |
 */

namespace Stack {

class Exception : public std::exception {};
class Overflow : public Exception {};

template <class T>
class Stack {
  private:
    unsigned long long size, cur, chunk;
    T *data;
  public:
    Stack();
    ~Stack();
    void pop();
    T top();
    void push(T data);
    bool empty();
};

}

// Исключение, возникающее при прочтении неизвестного символа
class UnknownSymbol : public std::exception {};

// Функция, дополняющая строку data размером data_size строкой add размером add_size и, в случае необходимости,
// динамически увеличивающая размер строки data.
// Функция возвращает указатель на объединённую строку или NULL в случае ошибки.
char *realloc_strcat(char **data, unsigned long long &data_size, char const * const add, const unsigned long long add_size);

// Прототип функции, дополняющей скобочную последовательность до сбалансированного вида.
// Функция принимает массив строк source, содержащий строки, состоящие из символов '(){}[]' и, возможно, '\n';
// возвращает строку result, представляющую из себя дополненные скобками слева и справа объединённые строки source
// до сбалансированного вида. Функция возвращает длину вычисленной строки.
// Если балансировка таким способом невозможна, функция вернёт 0.
unsigned long long complete_breakets_list(char const * const source, char ** result);

// Прототип функции получения данных из STDIN
unsigned long long input_data(char **input);

// Начальный размер динамических буферов
const unsigned long long CHUNK_SIZE = 64;

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;


    // Ввод данных
    char *input = new char[CHUNK_SIZE];  // Массив входных строк
    input_data(&input);

//    assert(strlen(input) <= 200000);

    if(strlen(input) == 0) {
        return 0;
    }

    // Дополнение скобочной последовательности
    char* result;
    unsigned long long result_size = complete_breakets_list(input, &result); 

    // Проверка на успешность выполнения
    if(result_size == 0) {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    assert(strlen(result) >= strlen(input));

    // Вывод результатов
    cout<<result<<endl;

    return 0;
}

// Функция, дополняющая строку data размером data_size строкой add размером add_size и, в случае необходимости,
// динамически увеличивающая размер строки data.
// Функция возвращает указатель на объединённую строку или NULL в случае ошибки.
char *realloc_strcat(char **data, unsigned long long &data_size, char const * const add, const unsigned long long add_size)
{
    // Если данные не умещаются в буфере, расширим его
    while(strlen(*data) + strlen(add) >= data_size) {
        // Расширяем буфер в 2 раза
        char *temp = new char[data_size *= 2];
        if(temp == NULL) {
            return NULL;
        }

        // Копируем данные в новый буфер и удаляем старый буфер
        if(!strncpy(temp, *data, strlen(*data))) {
            if(data_size > 0) delete[] *data;
            return NULL;
        }
        if(data_size > 0) delete[] *data;
        *data = temp;
    }

    // Добавим данные в буфер
    *data = strncat(*data, add, strlen(add));
    return *data;
}

// Функция получения данных из STDIN
// Прочитанные данных помещаются в массив массивов по 255 символов - input.
// Функция возвращает количество прочитанных символов.
unsigned long long input_data(char **input) {
    assert(input);

    unsigned long long input_size = CHUNK_SIZE;  // Размер массива входных данных
    char buf[255];  // Временный буфер для чтения данных
    unsigned long long input_length = 0;

    while(fgets(buf, 255, stdin)) {
        input_length += strlen(buf);
        *input = realloc_strcat(input, input_size, buf, 255);
    }

    // Проверяем успешность чтения
    //assert(ferror(stdin));
    return input_length;
}

// Функция, дополняющая скобочную последовательность до сбалансированного вида.
// Функция принимает строку source, содержащую символы '(){}[]' и, возможно, '\n';
// возвращает строку result, представляющую из себя дополненную скобками слева и справа строку source
// до сбалансированного вида. Функция возвращает длину вычисленной строки.
// Если балансировка таким способом невозможна, функция вернёт 0.
unsigned long long complete_breakets_list(char const * const source, char ** result)
{
    unsigned long long input_size = strlen(source);
    unsigned long long result_size = 0;
    char symbol;

    Stack::Stack<char> check, tail;

    for(unsigned long long i=0; i<input_size; i++) {
        switch(source[i]) {
          case '(':
          case '{':
          case '[':
            check.push(source[i]);
            break;

          case ')':
            if(check.empty()) {
                tail.push('(');
            }
            else if(check.top() == '(') {
                check.pop();
            } else {
                return 0;
            }
            break;

          case '}':
            if(check.empty()) {
                tail.push('{');
            }
            else if(check.top() == '{') {
                check.pop();
            } else {
                return 0;
            }
            break;

          case ']':
            if(check.empty()) {
                tail.push('[');
            }
            else if(check.top() == '[') {
                check.pop();
            } else {
                return 0;
            }
            break;

          case EOF:
          case '\n':
            break;

          default:
            throw UnknownSymbol();
        }
    }

    while(!tail.empty()) {
        symbol = tail.top();
        *result = realloc_strcat(result, result_size, &symbol, 1);
        tail.pop();
    }

    *result = realloc_strcat(result, result_size, source, input_size);

    while(!check.empty()) {
        // Если данные не умещаются в буфере, расширим его
        if(strlen(*result) + 1 >= result_size) {
            // Расширяем буфер в 2 раза
            char *temp = new char[result_size *= 2];
            assert(temp);

            // Копируем данные в новый буфер и удаляем старый буфер
            temp = strncpy(temp, *result, strlen(*result));
            delete[] result;
            *result = temp;  // Копируем указатель
        }
        switch(check.top()) {
          case '(':
            symbol = ')';
            *result = strncat(*result, &symbol, 1);
            break;
          case '{':
            symbol = '}';
            *result = strncat(*result, &symbol, 1);
            break;
          case '[':
            symbol = ']';
            *result = strncat(*result, &symbol, 1);
            break;
        }
        check.pop();
    }

    return strlen(*result);
}

template <class T>
Stack::Stack<T>::Stack()
{
    chunk = CHUNK_SIZE;
    size = chunk;
    data = new T[size];
    assert(data);
    cur = 0;
}

template <class T>
void Stack::Stack<T>::pop()
{
    if(cur < 1) throw Overflow();
    if(size - cur == chunk) {
        size -= chunk;
        T *temp = new T[size];
        assert(temp);
        assert(memmove(temp, data, size));
        delete[] data;
        data = temp;
        chunk /= 2;
    }
    cur--;
}

template <class T>
void Stack::Stack<T>::push(T data)
{
    this->data[++cur] = data;
    if(cur == size - 1) {
        size += chunk;
        T *temp = new T[size];
        assert(temp);
        assert(memmove(temp, this->data, size - chunk));
	delete[] this->data;
	this->data = temp;
        chunk *= 2;
    }
}

template <class T>
bool Stack::Stack<T>::empty()
{
    return cur == 0;
}

template <class T>
T Stack::Stack<T>::top()
{
    return data[cur];
}

template <class T>
Stack::Stack<T>::~Stack()
{
    delete[] data;
}
