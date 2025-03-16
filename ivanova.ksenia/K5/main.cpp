#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp)
{
  if (root == nullptr) {
    return nullptr;
  }
  if (cmp(value, root->data)) {
    return find(root->left, value, cmp);
  } else if (cmp(root->data, value)) {
    return find(root->right, value, cmp);
  } else {
    return root;
  }
}

int main()
{
    std::cout << "hrrr memememme, was on the lessons, real" << '\n';
}