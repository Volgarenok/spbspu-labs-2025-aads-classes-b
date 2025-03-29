#ifndef BITREE_HPP
#define BITREE_HPP

#include <functional>

namespace gavrilova {

  template< class T, class Cmp = std::less< T > >
  struct BiTree {
    T data;
    BiTree< T > * left, * right, *parent;
    Cmp cmp;
  };
  
}

#endif