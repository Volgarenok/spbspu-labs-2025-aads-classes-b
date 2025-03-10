#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp);

int main()
{
    std::cout << "hrrr memememme, was on the lessons, real" << '\n';
}