#include "bitree.hpp"

template< class T >
bool brevnov::BiTreeIterator::hasPrev() const
{

}

template< class T >
bool brevnov::BiTreeIterator::hasNext() const
{

}

template< class T >
brevnov::BiTreeIterator< T > brevnov::BiTreeIterator::next() const
{

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
