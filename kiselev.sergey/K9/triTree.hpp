#ifndef TRITREE_HPP
#define TRITREE_HPP
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include "triTreeIterator.hpp"

namespace kiselev
{
  template< class T >
  struct TreeNode
  {
    std::pair< T, T > data;
    TreeNode< T >* left;
    TreeNode< T >* middle;
    TreeNode< T >* right;
    TreeNode< T >* parent;

    TreeNode(const std::pair< T, T >& d, TreeNode< T >* p = nullptr):
      data(d.first < d.second ? d : std::pair< T, T >(d.second, d.first)),
      left(nullptr),
      middle(nullptr),
      right(nullptr),
      parent(p)
    {
      if (data.first == data.second)
      {
        throw std::invalid_argument("Incorrect pair");
      }
    }
  };

  template< class T, class Cmp = std::less< T > >
  struct TriTree
  {
    using Iterator = TriTreeIterator< T >;
    using Node = TreeNode< T >;

    TriTree():
      root(nullptr),
      size(0)
    {}
    Node* insert(std::pair< T, T >);
    void clear() noexcept;
    void clear(Node* root) noexcept;
    TriTreeIterator< T > begin() const noexcept;
    TriTreeIterator< T > rbegin() const noexcept;

    Node* root;
    size_t size;
    Cmp cmp;
  };

  template< class T, class Cmp >
  void TriTree< T, Cmp >::clear() noexcept
  {
    clear(root);
    root = nullptr;
  }
  template< class T, class Cmp >
  void TriTree< T, Cmp >::clear(Node* root) noexcept
  {
    if (!root)
    {
      return;
    }
    clear(root->left);
    clear(root->middle);
    clear(root->right);
    delete root;
  }

  template< class T, class Cmp >
  TreeNode< T >* TriTree< T, Cmp >::insert(std::pair< T, T > value)
  {
    if (!root)
    {
      root = new Node(value);
      size++;
      return root;
    }
    Node* temp = root;
    Node* parent = nullptr;
    while (temp)
    {
      parent = temp;
      if (cmp(value.second, temp->data.first))
      {
        temp = temp->left;
      }
      else if (value.first > temp->data.second)
      {
        temp = temp->right;
      }
      else if (cmp(temp->data.first, value.first) && cmp(value.second, temp->data.second))
      {
        temp = temp->middle;
      }
      else
      {
        return nullptr;
      }
    }
    Node* newNode = new Node(value, parent);
    if (cmp(value.second, parent->data.first))
    {
      parent->left = newNode;
    }
    else if (cmp(parent->data.second, value.first))
    {
      parent->right = newNode;
    }
    else
    {
      parent->middle = newNode;
    }
    size++;
    return root;
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTree< T, Cmp >::begin() const noexcept
  {
    return Iterator(min(root));
  }

  template< class T, class Cmp >
  TriTreeIterator< T > TriTree< T, Cmp >::rbegin() const noexcept
  {
    return Iterator(max(root));
  }
}
#endif
