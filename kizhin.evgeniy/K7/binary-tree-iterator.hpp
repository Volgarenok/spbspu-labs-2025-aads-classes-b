#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_ITERATOR_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_ITERATOR_HPP

#include <cassert>
#include "binary-tree.hpp"

namespace kizhin {
  template < typename T, typename Cmp >
  struct BiTreeIterator
  {
    BiTree< T, Cmp >* node = nullptr;

    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator< T, Cmp > next() const;
    BiTreeIterator< T, Cmp > prev() const;

    const T& data() const noexcept;
    T& data() noexcept;
  };
}

template < typename T, typename Cmp >
bool kizhin::BiTreeIterator< T, Cmp >::hasPrev() const
{
  if (node == nullptr) {
    return false;
  }
  /* TODO: Implement hasPrev/hasNext */
  return true;
}

template < typename T, typename Cmp >
bool kizhin::BiTreeIterator< T, Cmp >::hasNext() const
{
  if (node == nullptr) {
    return false;
  }
  /* TODO: Implement hasPrev/hasNext */
  return true;
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::BiTreeIterator< T, Cmp >::next() const
{
  assert(node != nullptr && "Incrementing empty iterator");
  BiTreeIterator copy = *this;
  /* TODO: Implement prev/next */
  return copy;
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::BiTreeIterator< T, Cmp >::prev() const
{
  assert(node != nullptr && "Decrementing empty iterator");
  BiTreeIterator copy = *this;
  /* TODO: Implement prev/next */
  return copy;
}

template < typename T, typename Cmp >
const T& kizhin::BiTreeIterator< T, Cmp >::data() const noexcept
{
  assert(node != nullptr && "Dereferencing empty iterator");
  return node->data;
}

template < typename T, typename Cmp >
T& kizhin::BiTreeIterator< T, Cmp >::data() noexcept
{
  assert(node != nullptr && "Dereferencing empty iterator");
  return node->data;
}

#endif

