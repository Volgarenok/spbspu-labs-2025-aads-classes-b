#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <stdexcept>
#include <assert.h>
#include "beTree.hpp"

namespace kiselev
{
  template< class T >
  struct BiTreeIterator
  {
    BiTree< T >* node;

    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator< T > next() const;
    BiTreeIterator< T > prev() const;

    const T& data() const;
  };

  template< class T >
  bool BiTreeIterator< T >::hasPrev() const
  {
    if (!node)
    {
      return false;
    }
    BiTree< T >* temp = node;
    if (temp->left)
    {
      return true;
    }
    while (temp->parent && temp == temp->parent->left)
    {
      temp = temp->parent;
    }
    return temp->parent != nullptr;
  }

  template< class T >
  bool BiTreeIterator< T >::hasNext() const
  {
    if (!node)
    {
      return false;
    }
    BiTree< T >* temp = node;
    if (temp->right)
    {
      return true;
    }
    while (temp->parent && temp == temp->parent->right)
    {
      temp = temp->parent;
    }
    return temp->parent != nullptr;
  }

  template< class T >
  BiTreeIterator< T > BiTreeIterator< T >::next() const
  {
    if (!hasNext())
    {
      throw std::logic_error("No next");
    }
    BiTree< T >* temp = node;
    if (temp->right)
    {
      temp = temp->right;
      while (temp->left)
      {
        temp = temp->left;
      }
      return BiTreeIterator< T >{ temp };
    }
    while (temp->parent && temp == temp->parent->right)
    {
      temp = temp->parent;
    }
    return BiTreeIterator< T >{ temp->parent };
  }

  template< class T >
  BiTreeIterator< T > BiTreeIterator< T >::prev() const
  {
    if (!hasPrev())
    {
      throw std::logic_error("No prev");
    }
    BiTree< T >* temp = node;
    if (temp->left)
    {
      temp = temp->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      return BiTreeIterator< T >{ temp };
    }
    while (temp->parent && temp == temp->parent->left)
    {
      temp = temp->parent;
    }
    return BiTreeIterator< T >{ temp->parent };
  }

  template< class T >
  const T& BiTreeIterator< T >::data() const
  {
    assert(node);
    return node->data;
  }

  template< typename T >
  BiTreeIterator< T > begin(BiTree< T >* root)
  {
    BiTreeIterator< T > it{ root };
    while (it.hasPrev())
    {
      it = it.prev();
    }
    return it;
  }

  template< typename T >
  BiTreeIterator< T > rbegin(BiTree< T >* root)
  {
    BiTreeIterator< T > it{ root };
    while (it.hasNext())
    {
      it = it.next();
    }
    return it;
  }
}
#endif
