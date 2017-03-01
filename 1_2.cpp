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

int main(int argc, char *argv[])
{

    using std::cout;
    using std::cin;

    int n = 0;
    assert(cin>>n);

    for(int i = 2; i*i <= n; i++)
    {
        while(n%i == 0)
        {
            n /= i;
            cout<<i<<" ";
        }
    }

    return 0;
}
