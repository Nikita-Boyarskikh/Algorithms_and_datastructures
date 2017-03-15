#include <iostream>
#include <cassert>

/*
 * ВЫСОКАЯ ПИРАМИДА
 * 
 * Дано N кубиков. Требуется определить, каким количеством способов можно выстроить из этих кубиков пирамиду.
 * Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
 * N <= 200.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  3                        |
 * |  5                     |  7                        |
 * |  7                     |  15                       |
 */

// Запись для компактного хранения вычисленных данных
struct node {
    size_t data;
    node *next;
}

int main(int argc, char *argv[])
{

    using std::cin;
    using std::cout;

    size_t N;
    assert(cin>>N);
    assert(N > 0);
    assert(N <= 200);

    // Аллокация памяти
    size_t **variants = new size_t*[N];
    for(size_t i = 0; i < N; i++) {
        variants[i] = new node;
    }

    size_t result = high_piramid_variants(N, N);
    assert(cout<<result);

    // Освобождения памяти
    for(size_t i = 0; i < N; i++) {
        while(variants[i]->next != std::nullptr) {
            node *deleting_node = variants[i];
            variants[i] = variants[i]->next;
        }
    }
    delete[] variants;

    return 0;
}
