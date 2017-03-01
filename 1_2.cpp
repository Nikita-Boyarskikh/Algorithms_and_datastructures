#include <iostream>
#include <cassert>

/*
 * Вывести разложение натурального числа n на простые множители.
 * Простые множители должны быть выведены по возрастанию и разделены пробелами.
 * 2 <= n <= 10^6
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  75                    |  3 5 5                    |
 */

// Вычисляет простые числа до заданного number, возвращает количество найденных простых чисел
// Принимает указатель на буфер для простых чисел размером size_of_buffer, и заполняет его простыми числами
int calcPrimes(int *result, int size_of_buffer, int number) {
    assert(result != NULL);
    int index = 0;
    for(int i = 2; i*i <= number; i++)
    {
        while(number%i == 0)
        {
            // Проверка на достаточный размер буфера
            assert(size_of_buffer > index);
            number /= i;
            result[index++] = i;
        }
    }
    if(number > 1) {
        result[index++] = number;
    }
    return index;
}

int main(int argc, char *argv[])
{

    using std::cout;
    using std::cin;

    int n = 0;
    assert(cin>>n);
    assert(n >= 0);

    if(n < 4) {
        cout<<n;
        return 0;
    }

    // Достаточный размер буфера под простые числа до заданного
    int size_of_buffer = n/2 + 1;
    // Буфер для простых чисел
    int *primes = new int[size_of_buffer];
    int prime_count = calcPrimes(primes, size_of_buffer, n);

    for (int i=0; i<prime_count; i++) {
        cout<<primes[i]<<" ";
    }

    delete[] primes;
    return 0;
}
