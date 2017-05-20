#include <iostream>
#include <cassert>
#include <queue>

/*
 * ПОРЯДОК ОБХОДА
 * 
 * Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то
 * узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * Рекурсия запрещена.
 * 
 * Выведите элементы в порядке level-order (по слоям, “в ширину”).
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  3                     |  2 1 3                    |
 * |  2 1 3                 |                           |
 * |------------------------+---------------------------|
 * |  3                     |  1 2 3                    |
 * |  1 2 3                 |                           |
 * |------------------------+---------------------------|
 * |  3                     |  3 1 2                    |
 * |  3 1 2                 |                           |
 * |------------------------+---------------------------|
 * |  4                     |  3 1 4 2                  |
 * |  3 1 4 2               |                           |
 */

// Двоичное дерево
template <class T>
class Tree {
  private:
    struct node {
        node* left;
        node* right;
        T value;
        node() : left(nullptr),
                 right(nullptr) {};
    };
    node* root;
  public:
    Tree() : root(nullptr) {};
    void add( T data );
    void traverse();
    ~Tree();
};
 
int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    assert( n >= 0 );

    long long tmp;
    Tree<long long> tree;
    for( int i = 0; i < n; i++ ) {
        std::cin >> tmp;
        tree.add(tmp);
    }
    tree.traverse();
    std::cout << std::endl;

    return 0;
}

template <class T>
void Tree<T>::add( T data )
{
    if( !root ) {
        root = new node;
        root->value = data;
        return;
    }

    node* tmp = root;
    while( (tmp->left && data < tmp->value) ||
           (tmp->right && data >= tmp->value) ) {
        if( tmp->left && data < tmp->value ) {
            tmp = tmp->left;
        }
        if( tmp->right && data >= tmp->value ) {
            tmp = tmp->right;
        }
    }

    if( data < tmp->value ) {
        tmp->left = new node;
        tmp = tmp->left;
    } else {
        tmp->right = new node;
        tmp = tmp->right;
    }
    tmp->value = data;
}

template <class T>
void Tree<T>::traverse()
{
    if( !root ) {
        return;
    }

    std::queue<node*> q;
    for( q.push(root); !q.empty(); q.pop() ) {
        const node* const tmp = q.front();
        std::cout << tmp->value << ' ';

        if( tmp->left ) {
            q.push( tmp->left );
        }
        if( tmp->right ) {
            q.push( tmp->right );
        }
    }
}

template <class T>
Tree<T>::~Tree()
{
    if( !root ) {
        return;
    }

    std::queue<node*> q;
    for( q.push(root); !q.empty(); q.pop() ) {
        const node* const tmp = q.front();
        if( tmp->left ) {
            q.push(tmp->left);
        }
        if( tmp->right ) {
            q.push(tmp->right);
        }
        delete tmp;
    }
}
