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
  BiTree< T >* new_node = new BiTree<T>{new_val, nullptr, nullptr};
  if (!root) {
    return new_node;
  }

  BiTree< T >* parent = find(root, new_val, cmp);

  if (cmp(new_val, parent->data)) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
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
  if (!root) {
    return nullptr;
  }
  while (true) {
    if (cmp(value, root->data)) {
      if (root->left) {
        root = root->left;
      } else {
        return root;
      }
    } else if (cmp(root->data, value)) {
      if (root->right) {
        root = root->right;
      } else {
        return root;
      }
    } else {
      return root;
    }
  }
}

#endif
