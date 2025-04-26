#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "BiTree.hpp"
namespace gavrilova {

  template< class T >
  struct BiTreeIterator {
    BiTree< T >* node;

    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator< T > next() const;
    BiTreeIterator< T > prev() const;

    const T & data() const;
  };

  template< class T, class Cmp = std::less< T > >
  BiTreeIterator< T > begin(BiTree< T, Cmp >* root);

  template< class T, class Cmp = std::less< T > >
  BiTreeIterator< T > rbegin(BiTree< T, Cmp >* root);

  template< class T >
  bool BiTreeIterator< T >::hasPrev() const
  {
    return prev().node != nullptr;
  }

  template< class T >
  bool BiTreeIterator< T >::hasNext() const
  {
    return next().node != nullptr;
  }


  template< class T >
  BiTreeIterator< T > BiTreeIterator< T >::next() const
  {
    if (!node) {
      return BiTreeIterator< T >{node};
    }

    if (node->right) {
      BiTree< T >* cur = node->right;
      while (cur->left) {
        cur = cur->left;
      }
      return BiTreeIterator< T >{cur};
    } else {
      BiTree< T >* prev = node;
      BiTree< T >* cur = prev->parent;
      while (cur && cur->cmp(cur->data, prev->data)) {
        prev = cur;
        cur = cur->parent;
      }
      if (cur) {
        return BiTreeIterator< T >{cur};
      } else {
        return BiTreeIterator< T >{nullptr};
      }
    }
  }

  template< class T >
  BiTreeIterator< T > BiTreeIterator< T >::prev() const
  {
    if (!node) {
      return BiTreeIterator< T >{node};
    }

    if (node->left) {
      BiTree< T >* cur = node->left;
      while (cur->right) {
        cur = cur->right;
      }
      return BiTreeIterator< T >{cur};
    } else {
      BiTree< T >* cur = node->parent;
      if (cur->right == node) {
        return BiTreeIterator< T >{cur};
      } else {
        return BiTreeIterator< T >{nullptr};
      }
    }
  }

  template< class T >
  const T & BiTreeIterator< T >::data() const
  {
    return node->data;
  }

  template< class T, class Cmp = std::less< T > >
  BiTreeIterator< T > begin(BiTree< T >* root)
  {
    if (root) {
      while (root->left) {
        root = root->left;
      }
    }
    return BiTreeIterator< T >{root};
  }

  template< class T, class Cmp = std::less< T > >
  BiTreeIterator< T > rbegin(BiTree< T >* root)
  {
    if (root) {
      while (root->right) {
        root = root->right;
      }
    }
    return BiTreeIterator< T >{root};
  }
}
#endif
