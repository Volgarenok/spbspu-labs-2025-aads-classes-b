#ifndef BITREE_HPP
#define BITREE_HPP

#include <functional>

namespace gavrilova {

  template< class T >
  struct BiTreeIterator {
    BiTree< T, Cmp > * node;

    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator< T, Cmp > next() const;
    BiTreeIterator< T, Cmp > prev() const;

    const T & data() const;
  };

  template< class T >
  bool hasPrev() const
  {

  }

  template< class T >
  bool hasNext() const
  {

  }

  template< class T >
  BiTreeIterator< T, Cmp > next() const
  {

  }

  template< class T >
  BiTreeIterator< T, Cmp > prev() const
  {

  }

  template< class T >
  const T & data() const
  {
    
  }
  
}

#endif