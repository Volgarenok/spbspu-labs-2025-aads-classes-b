#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_ITERATOR_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_ITERATOR_HPP

#include <cassert>
#include "binary-tree.hpp"

namespace kizhin {
  template < typename T, typename Cmp >
  struct BiTreeIterator
  {
  public:
    BiTreeIterator() = default;
    explicit BiTreeIterator(BiTree< T, Cmp >*);
    bool hasPrev() const;
    bool hasNext() const;
    BiTreeIterator next() const;
    BiTreeIterator prev() const;

    const T& data() const noexcept;
    T& data() noexcept;

  private:
    BiTree< T, Cmp >* node_ = nullptr;
  };

  template < typename T, typename Cmp >
  BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp >*);

  template < typename T, typename Cmp >
  BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp >*);
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp >::BiTreeIterator(BiTree< T, Cmp >* node):
  node_(node)
{}

template < typename T, typename Cmp >
bool kizhin::BiTreeIterator< T, Cmp >::hasNext() const
{
  assert(node_ != nullptr && "hasNext() called on empty iterator");
  BiTree< T, Cmp >* current = node_;
  if (current->right != nullptr) {
    return true;
  }
  BiTree< T, Cmp >* p = current->parent;
  while (p != nullptr && current == p->right) {
    current = p;
    p = p->parent;
  }
  return p != nullptr;
}

template < typename T, typename Cmp >
bool kizhin::BiTreeIterator< T, Cmp >::hasPrev() const
{
  assert(node_ != nullptr && "hasPrev() called on empty iterator");
  BiTree< T, Cmp >* current = node_;
  if (current->left != nullptr) {
    return true;
  }
  BiTree< T, Cmp >* p = current->parent;
  while (p != nullptr && current == p->left) {
    current = p;
    p = p->parent;
  }
  return p != nullptr;
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::BiTreeIterator< T, Cmp >::next() const
{
  assert(node_ != nullptr && "Incrementing empty iterator");
  assert(hasNext() && "Incrementing end iterator");
  BiTree< T, Cmp >* current = node_;
  BiTree< T, Cmp >* nextNode = nullptr;
  if (current->right != nullptr) {
    nextNode = current->right;
    while (nextNode->left != nullptr) {
      nextNode = nextNode->left;
    }
  } else {
    BiTree< T, Cmp >* p = current->parent;
    while (p != nullptr && current == p->right) {
      current = p;
      p = p->parent;
    }
    nextNode = p;
  }
  return BiTreeIterator< T, Cmp >(nextNode);
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::BiTreeIterator< T, Cmp >::prev() const
{
  assert(node_ != nullptr && "Decrementing empty iterator");
  assert(hasPrev() && "Decrementing begin iterator");
  BiTree< T, Cmp >* current = node_;
  BiTree< T, Cmp >* prevNode = nullptr;
  if (current->left != nullptr) {
    prevNode = current->left;
    while (prevNode->right != nullptr) {
      prevNode = prevNode->right;
    }
  } else {
    BiTree< T, Cmp >* p = current->parent;
    while (p != nullptr && current == p->left) {
      current = p;
      p = p->parent;
    }
    prevNode = p;
  }
  return BiTreeIterator< T, Cmp >(prevNode);
}

template < typename T, typename Cmp >
const T& kizhin::BiTreeIterator< T, Cmp >::data() const noexcept
{
  assert(node_ != nullptr && "Dereferencing empty iterator");
  return node_->data;
}

template < typename T, typename Cmp >
T& kizhin::BiTreeIterator< T, Cmp >::data() noexcept
{
  assert(node_ != nullptr && "Dereferencing empty iterator");
  return node_->data;
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::begin(BiTree< T, Cmp >* root)
{
  if (root != nullptr) {
    while (root->left != nullptr) {
      root = root->left;
    }
  }
  return BiTreeIterator< T, Cmp >(root);
}

template < typename T, typename Cmp >
kizhin::BiTreeIterator< T, Cmp > kizhin::rbegin(BiTree< T, Cmp >* root)
{
  if (root != nullptr) {
    while (root->right != nullptr) {
      root = root->right;
    }
  }
  return BiTreeIterator< T, Cmp >(root);
}

#endif

