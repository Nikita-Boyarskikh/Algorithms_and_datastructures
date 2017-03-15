#include <iostream>
#include <cassert>
#include <string>
#include <stack>

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

// Прототип функции, дополняющей скобочную последовательность до сбалансированного вида.
// Функция принимает строку source, содержащую символы '(){}[]' и, возможно, '\n';
// возвращает строку result, представляющую из себя дополненную скобками слева и справа строку source
// до сбалансированного вида. Функция возвращает длину вычисленной строки.
// Если балансировка таким способом невозможна, функция вернёт 0.
size_t complete_breakets_list(const std::string source, std::string &result);

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;

    std::string str, result, buf;

    while(std::getline(cin, buf)) {
        str = str + buf;
    }

    if(str.length() == 0) {
        return 0;
    }

    assert(str.length() <= 200000);

    size_t result_length = complete_breakets_list(str, result);
    if(result_length == 0) {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    assert(result_length >= str.length());

    cout<<result<<endl;

    return 0;
}

// Функция, дополняющая скобочную последовательность до сбалансированного вида.
// Функция принимает строку source, содержащую символы '(){}[]' и, возможно, '\n';
// возвращает строку result, представляющую из себя дополненную скобками слева и справа строку source
// до сбалансированного вида. Функция возвращает длину вычисленной строки.
// Если балансировка таким способом невозможна, функция вернёт 0.
size_t complete_breakets_list(const std::string source, std::string &result)
{
    std::stack<char> check, tail;

    for(size_t i=0; i<source.length(); i++) {
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
            throw std::exception();
        }
    }

    while(!tail.empty()) {
        result = result + tail.top();
        tail.pop();
    }

    result = result + source;

    while(!check.empty()) {
        switch(check.top()) {
          case '(':
            result = result + ')';
            break;
          case '{':
            result = result + '}';
            break;
          case '[':
            result = result + ']';
            break;
        }
        check.pop();
    }

    return result.length();
}
