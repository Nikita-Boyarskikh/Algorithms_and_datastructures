#include <iostream>
#include <cassert>
#include <queue>

/*
 * ДЕКАРТОВО ДЕРЕВО
 * 
 * Дано число N < 10^6 и последовательность пар целых чисел из [-2^31..2^31] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
 * Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма,
 * рассказанного на лекции:
 * ●   При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
 *     приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
 *     первом поддереве все ключи меньше x, а во втором больше или равны x.
 *     Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел
 *     вставьте на место узла P.
 * 
 * Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
 * 
 * Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница
 * может быть отрицательна.
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  10                    |  2                        |
 * |  5 11                  |                           |
 * |  18 8                  |                           |
 * |  25 7                  |                           |
 * |  50 12                 |                           |
 * |  30 30                 |                           |
 * |  15 15                 |                           |
 * |  20 10                 |                           |
 * |  22 5                  |                           |
 * |  40 20                 |                           |
 * |  45 9                  |                           |
 * |------------------------+---------------------------|
 * |  10                    |  2                        |
 * |  38 19                 |                           |
 * |  37 5                  |                           |
 * |  47 15                 |                           |
 * |  35 0                  |                           |
 * |  12 3                  |                           |
 * |  0 42                  |                           |
 * |  31 37                 |                           |
 * |  21 45                 |                           |
 * |  30 26                 |                           |
 * |  41 6                  |                           |
 * |------------------------+---------------------------|
 */

template <class T, class K>
class Treap {
  private:
    struct node {
        node* left;
        node* right;
        T key;
        K priority;
        node() : left(nullptr),
                 right(nullptr) {};
    };
    node* root;
    void _split( node* cur, T key, node*& left, node*& right );

  public:
    size_t get_depth();
    Treap() : root(nullptr) {};
    void add( T elem, K priority );
    ~Treap();
};

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
    size_t get_depth();
    void traverse();
    ~Tree();
};
 
int main(int argc, char *argv[])
{
    Tree<long long> tree;
    Treap<long long, long long> treap;
    int n;
    std::cin >> n;
    assert( n >= 0 );

    long long x, y;
    for( int i = 0; i < n; i++ ) {
        std::cin >> x >> y;
        tree.add(x);
        treap.add(x, y);
    }

    std::cout << tree.get_depth() - treap.get_depth() << std::endl;

    return 0;
}

template <class T, class K>
void Treap<T, K>::add( T elem, K priority )
{
    if( !root ) {
        root = new node;
        root->key = elem;
        root->priority = priority;
        return;
    }

    node** tmp = &root;
    while( *tmp ) {
        if( (*tmp)->priority < priority ) {
            break;
        }
        if( elem < (*tmp)->key ) {
            tmp = &(*tmp)->left;
        } else {
            tmp = &(*tmp)->right;
        }
    }
    node* left, *right;
    _split( *tmp, elem, left, right );
    
    node* new_node = new node;
    new_node->left = left;
    new_node->right = right;
    new_node->key = elem;
    new_node->priority = priority;

    *tmp = new_node;
}

template <class T, class K>
size_t Treap<T, K>::get_depth()
{
    if( !root ) {
        return 0;
    }

    std::queue< std::pair<size_t, node*> > q;
    size_t depth = 1;
    for( q.push({ 1, root }); !q.empty(); q.pop() ) {
        std::pair<size_t, node*> tmp = q.front();
        if( tmp.second->left ) {
            q.push({ tmp.first + 1, tmp.second->left });
        }
        if( tmp.second->right ) {
            q.push({ tmp.first + 1, tmp.second->right });
        }
        if( depth < tmp.first ) {
            depth = tmp.first;
        }
    }
    return depth;
}

template <class T, class K>
void Treap<T, K>::_split( node* cur, T key, node*& left, node*& right )
{
    if( !cur ) {
        left = nullptr;
        right = nullptr;
    } else if( cur->key <= key ) {
        _split( cur->right, key, cur->right, right );
        left = cur;
    } else {
        _split( cur->left, key, left, cur->left );
        right = cur;
    }
}

template <class T, class K>
Treap<T, K>::~Treap()
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
size_t Tree<T>::get_depth()
{
    if( !root ) {
        return 0;
    }

    std::queue< std::pair<size_t, node*> > q;
    size_t depth = 1;
    for( q.push({ 1, root }); !q.empty(); q.pop() ) {
        std::pair<size_t, node*> tmp = q.front();
        if( tmp.second->left ) {
            q.push({ tmp.first + 1, tmp.second->left });
        }
        if( tmp.second->right ) {
            q.push({ tmp.first + 1, tmp.second->right });
        }
        if( depth < tmp.first ) {
            depth = tmp.first;
        }
    }
    return depth;
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
