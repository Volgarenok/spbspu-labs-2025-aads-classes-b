#ifndef BITREE_HPP
#define BITREE_HPP

#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp);

template< class T, class Cmp >
BiTree< T > * insertBT(T new_val, BiTree< T > * root, Cmp cmp);

template< class T >
void clear(BiTree< T > * root);

template< class T, class Cmp >
BiTree< T > * insertBT(T new_val, BiTree< T > * root, Cmp cmp)
{
  if (!root) {
    return new BiTree<T>{new_val, nullptr, nullptr};
  }

  BiTree< T >* cur_root = root;
  BiTree< T >* parent = nullptr;

  while (cur_root) {
    parent = cur_root;
    if (cmp(new_val, parent->data)) {
      cur_root = cur_root->left;
    } else {
      cur_root = cur_root->right;
    }
  }

  if (cmp(new_val, parent->data)) {
    parent->left = new BiTree<T>{new_val, nullptr, nullptr};
  } else {
    parent->right = new BiTree<T>{new_val, nullptr, nullptr};
  }
  return root;
}

template< class T >
void clear(BiTree< T > * root)
{
  if (!root) {
    return;
  }
  clear< T >(root->left);
  clear< T >(root->right);
  delete root;
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  while (root && root->data != value) {
    if (cmp(value, root->data)) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return root;
}

#endif
