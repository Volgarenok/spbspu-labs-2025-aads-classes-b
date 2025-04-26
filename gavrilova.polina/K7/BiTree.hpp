#ifndef BITREE_HPP
#define BITREE_HPP
#include <iostream>

namespace gavrilova {
  template< class T, class Cmp = std::less< T > >
  struct BiTree {
    T data;
    BiTree< T, Cmp > * left, * right, * parent;
    Cmp cmp;
  };

  template< class T, class Cmp = std::less< T > >
  BiTree< T > * find(BiTree< T > * root, const T & value);

  template< class T, class Cmp = std::less< T > >
  BiTree< T > * insertBT(T new_val, BiTree< T > * root);

  template< class T >
  void clear(BiTree< T > * root);

  template< class T, class Cmp = std::less< T > >
  BiTree< T > * insertBT(T new_val, BiTree< T > * root)
  {
    BiTree< T >* new_node = new BiTree<T>{new_val, nullptr, nullptr, nullptr};
    if (!root) {
      return new_node;
    }

    BiTree< T >* parent = find(root, new_val);

    if (root->cmp(new_val, parent->data)) {
      parent->left = new_node;
      new_node->parent = parent;
    } else {
      parent->right = new_node;
      new_node->parent = parent;
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

  template< class T, class Cmp = std::less< T > >
  BiTree< T > * find(BiTree< T > * root, const T & value)
  {
    if (!root) {
      return nullptr;
    }
    while (true) {
      if (root->cmp(value, root->data)) {
        if (root->left) {
          root = root->left;
        } else {
          return root;
        }
      } else if (root->cmp(root->data, value)) {
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
}

#endif
