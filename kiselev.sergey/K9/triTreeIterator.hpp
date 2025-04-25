#ifndef TRITREEITERATOR_HPP
#define TRITREEITERATOR_HPP
#include <functional>
#include <ostream>
#include <utility>

namespace kiselev
{
  template< class T >
  struct TreeNode;
  template< typename T, class Cmp = std::less< T > >
  struct TriTreeIterator
  {
    using this_t = TriTreeIterator< T >;
    using Node = TreeNode< T >;
    TriTreeIterator() = default;
    TriTreeIterator(Node* nod):
      node(nod)
    {}
    bool hasNext() const;
    bool hasPrev() const;

    this_t prev() const;
    this_t next() const;

    std::pair< T, T > & data();

    Node* node;
  };

  template< class T >
  TreeNode< T >* max(TreeNode< T >* node)
  {
    while (node->right || node->middle)
    {
      node = (node->right ? node->right : node->middle);
    }
    return node;
  }

  template< class T >
  TreeNode< T >* min(TreeNode< T >* node)
  {
    while (node->left)
    {
      node = node->left;
    }
    return node;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasNext() const
  {
    if (!node)
    {
      return false;
    }
    if (node->right || node->middle)
    {
      return true;
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left == temp && (parent->middle || parent->right))
      {
        return 1;
      }
      if (parent->middle == temp && parent->right)
      {
        return 1;
        }
      temp = parent;
      parent = parent->parent;
    }
    return false;
  }

  template< class T, class Cmp >
  bool TriTreeIterator< T, Cmp >::hasPrev() const
  {
    if (!node)
    {
      return false;
    }
    if (node->left)
    {
      return true;
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left != temp)
      {
        return true;
      }
      temp = parent;
      parent = parent->parent;
    }
    return false;
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTreeIterator< T, Cmp >::next() const
  {
    if (node->middle)
    {
      return this_t(min(node->middle));
    }
    else if (node->right)
    {
      return this_t(min(node->right));
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left == temp)
      {
        return this_t(parent);
      }
      else if (parent->middle == temp && temp->parent->right)
      {
        if (parent->right)
        {
          return this_t(min(parent->right));
        }
        return this_t(parent);
      }
      temp = parent;
      parent = parent->parent;
    }
    return this_t(temp);
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTreeIterator< T, Cmp >::prev() const
  {
    if (node->left)
    {
      return this_t(max(node->left));
    }
    Node* temp = node;
    Node* parent = node->parent;
    while (parent)
    {
      if (parent->left != temp)
      {
        return this_t(parent);
      }
      temp = parent;
      parent = parent->parent;
    }
    return this_t(temp);
  }

  template< class T, class Cmp >
  std::pair< T, T >& TriTreeIterator< T, Cmp >::data()
  {
    return node->data;
  }
}
#endif
