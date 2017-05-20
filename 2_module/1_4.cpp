#include <iostream>
#include <cassert>
#include <string>
#include <vector>

/*
 * СТРОКИ
 * 
 * Напишите программу, печатающую набор строк в лексикографическом порядке.
 * Строки разделяются символом перевода строки '\n'. Если последний символ в потоке ввода '\n',
 * считать, что после него нет пустой строки. Максимальная длина строки 255 символов. Написать
 * свою функцию сравнения строк.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  4                     |  ab                       |
 * |  caba                  |  aba                      |
 * |  abba                  |  abba                     |
 * |  ab                    |  caba                     |
 * |  aba                   |                           |
 */

// Функция сравнения строк.
bool less(std::string a, std::string b);

// Шаблонная функция сортировки элементов.
template <class CT, class T>
void sort(CT &container, bool(cmp)(T, T));

int main(int argc, char *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    using std::vector;

    long long int n;
    cin >> n;
    assert(n > 0);

    vector<string> strs(n);
    string str;
    getline(cin, str);

    // Читаем строки
    for(long long int i = 0; i < n; i++) {
        getline(cin, str);
        strs[i] = str;
    }

    sort(strs, less);

    for(long long int i = 0; i < n; i++) {
        cout << strs[i] << endl;
    }

    return 0;
}

// Шаблонная функция сортировки элементов.
template <class CT, class T>
void sort(CT &container, bool(cmp)(T, T))
{
    // Сортировка вставками
    for(long long int i = 1; i < container.size(); i++) {
        T tmp = container[i];
        long long int j = i - 1;
        for(; (j >= 0) && !cmp(container[j], tmp); j--) {
            container[j + 1] = container[j];
        }
        container[j + 1] = tmp;
    }
}

// Функция сравнения по умолчанию
bool less(std::string a, std::string b)
{
    unsigned long long i = 0;
    for(; (a[i] == b[i]) && ( i < std::min(a.size(), b.size()) ); i++);
    if(i == std::min(a.size(), b.size())) return a.size() < b.size();
    for(; i < std::min(a.size(), b.size()); i++) {
        if(a[i] >= b[i]) return false;
    }
    return true;
}
