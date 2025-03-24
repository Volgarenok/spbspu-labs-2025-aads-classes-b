#ifndef BITREE_HPP
#define BITREE_HPP
namespace brevnov
{
  template< class T, class Cmp >
  struct BiTree {
    T data;
    Cmp cmp;
    BiTree< T > * left, * right, * parent;
  };

  template< class T >
  struct BiTreeIterator {
    BiTree< T > * node;

    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator< T > next() const;
    BiTreeIterator< T > prev() const;

    const T & data() const;
  };

  template< class T, class Cmp = std::less< T > >
  BiTree< T > * addElTree(BiTree< T > * root, const T & value, Cmp = Cmp{});

  template< class T >
  void clear(BiTree< T > * head);
}
#endif