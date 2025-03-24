#include "bitree.hpp"

template< class T >
bool brevnov::BiTreeIterator::hasPrev() const
{
  return node->
}

template< class T >
bool brevnov::BiTreeIterator::hasNext() const
{
  return next() != nullptr;
}

template< class T >
brevnov::BiTreeIterator< T > brevnov::BiTreeIterator::next() const
{
  if (node == nullptr)
  {
    return nullptr;
  }
  if (node->right == nullptr)
  {
    BiTree< T > * prev = node;
    node = node->parent;
    while (node->left != prev && node != nullptr)
    {
      prev = node;
      node = node->parent;
    }
    return node;
  }
  else
  {
    node = node->right;
    while (node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }
}

template< class T, class Cmp >
brevnov::BiTree< T > * brevnov::addElTree(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< T > * sub = root;
  if (root == nullptr)
  {
    return new BiTree< T >{value, nullptr, nullptr};
  }
  bool done = false;
  while (!done)
  {
    if (cmp(sub->data, value))
    {
      if (sub->right == nullptr)
      {
        sub->right = new BiTree< T >{value, nullptr, nullptr};
        done = true;
      }
      else
      {
        sub = sub->right;
      }
    }
    else
    {
      if (sub->left == nullptr)
      {
        sub->left = new BiTree< T >{value, nullptr, nullptr};
        done = true;
      }
      else
      {
        sub = sub->left;
      }
    }
  }
  return root;
}

template< class T >
void brevnov::clear(BiTree< T > * head)
{
  if (head == nullptr)
  {
    return;
  }
  clear(head->left);
  clear(head->right);
  delete head;
}
