#include <iostream>
#include <cassert>

/*
 * ИСПОЛЬЗОВАНИЕ АВЛ-ДЕРЕВА
 * 
 * Порядковые статистики.
 * Дано число N и N строк. Каждая строка содержит команду
 * добавления или удаления натуральных чисел, а также запрос на получение k-ой
 * порядковой статистики. Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”. Запрос на получение
 * k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).
 * 
 * |  in                    |  out                      |
 * |------------------------+---------------------------|
 * |  5                     |  40                       |
 * |  40 0                  |  40                       |
 * |  10 1                  |  10                       |
 * |  4 1                   |  4                        |
 * |  -10 0                 |  50                       |
 * |  50 2                  |                           |
 */

template <class T>
class AVLTree {
  private:
    struct node {
        T key;
        size_t depth;
        size_t size;
        node* left;
        node* right;
        node(T key) : key(key), depth(1), size(1),
            left(nullptr), right(nullptr) {};
    };

    node* root;

    node* _add( T elem, node*& tree );
    node* _remove( T elem, node*& tree );
    node* balance( node*& tree );
    node* rotate_left( node*& tree );
    node* rotate_right( node*& tree );
    void fix_depth( node*& tree );
    void fix_size( node* tree );
    node* findmin( node* tree );
    node* removemin( node* tree );
    size_t depth( node* tree );
    int bfactor( node* tree );

  public:
    AVLTree() : root(nullptr) {};
    void add( T elem );
    void del( T elem );
    T get_k_stat( size_t k_stat );
};

int main(int argc, char *argv[])
{
    long long n;
    std::cin >> n;
    assert( n >= 0 );

    AVLTree<long long> tree;
    for( long long i = 0; i < n; i++ ) {
        long long A, k;
        std::cin >> A >> k;
        if( A < 0 ) {
            tree.del(-A);
        } else {
            tree.add(A);
        }
        std::cout << tree.get_k_stat(k) << std::endl;
    }

    return 0;
}

template <class T>
size_t AVLTree<T>::depth( typename AVLTree<T>::node* tree )
{
    return (tree ? tree->depth : 0);
}

template <class T>
void AVLTree<T>::add( T elem )
{
    root = _add( elem, root );
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::_add( T elem, typename AVLTree<T>::node*& tree )
{
    if( !tree ) {
        return new node( elem );
    }
    if( tree->key > elem ) {
        tree->left = _add( elem, tree->left );
    } else {
        tree->right = _add( elem, tree->right );
    }
    return balance( tree );
}

template <class T>
void AVLTree<T>::del( T elem )
{
   root = _remove( elem, root );
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::_remove( T elem, typename AVLTree<T>::node*& tree )
{
    if( !tree ) {
       return nullptr;
    }
    if( elem < tree->key ) {
        tree->left = _remove( elem, tree->left );
    } else if( elem > tree->key ) {
        tree->right = _remove( elem, tree->right );
    } else {
        node* l = tree->left;
        node* r = tree->right;
        delete tree;
        if( !r ) return l;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = l;
        return balance( min );
    }
    return balance( tree );
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::balance( typename AVLTree<T>::node*& tree )
{
    fix_size( tree );
    fix_depth( tree );
    if( bfactor( tree ) == 2 ) {
        if( bfactor( tree->right ) < 0 ) {
            tree->right = rotate_right( tree->right );
        }
        return rotate_left( tree );
    }
    if( bfactor( tree ) == -2 ) {
        if( bfactor( tree ) > 0 ) {
            tree->left = rotate_left( tree->left );
        }
        return rotate_right( tree );
    }
    return tree;
}

template <class T>
void AVLTree<T>::fix_size( typename AVLTree<T>::node* tree )
{
    tree->size = 1;
    if( tree->left ) {
        tree->size += tree->left->size;
    }
    if( tree->right ) {
        tree->size += tree->right->size;
    }
}

template <class T>
int AVLTree<T>::bfactor( node* tree )
{
    return depth(tree->right) - depth(tree->left);
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_left( typename AVLTree<T>::node*& tree )
{
    node* tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    fix_depth( tree );
    fix_depth( tmp );
    fix_size( tree );
    fix_size( tmp );
    return tmp;
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::rotate_right( typename AVLTree<T>::node*& tree )
{
    if( !tree->left ) {
        return nullptr;
    }
    node* tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    fix_depth( tree );
    fix_depth( tmp );
    fix_size( tree );
    fix_size( tmp );
    return tmp;
}

template <class T>
void AVLTree<T>::fix_depth( typename AVLTree<T>::node*& tree )
{
    tree->depth = std::max( depth( tree->left ), depth( tree->right ) ) + 1;
}

template <class T>
T AVLTree<T>::get_k_stat( size_t k_stat )
{
    node* cur = root;
    long long k = k_stat;
    while( cur && k >= 0 ) {
        size_t l_size = cur->left ? cur->left->size : 0;
        if( l_size == k ) {
            return cur->key;
        }
        cur = (l_size > k ? cur->left : cur->right);
        if( l_size < k ) {
            k -= l_size + 1;
        }
    }
    throw std::exception(); //"K'th order statistics not found"
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::findmin( typename AVLTree<T>::node* tree )
{
    return (tree->left ? findmin( tree->left ) : tree);
}

template <class T>
typename AVLTree<T>::node* AVLTree<T>::removemin( typename AVLTree<T>::node* tree )
{
    if( !tree->left ) {
        return tree->right;
    }
    tree->left = removemin( tree->left );
    return balance( tree );
}
