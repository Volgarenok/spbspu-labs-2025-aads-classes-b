#include <algorithm>
#include <iostream>
#include <string>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator {
  /* ??? */
  using this_t = TriTreeItretor< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);

int main()
{
}
