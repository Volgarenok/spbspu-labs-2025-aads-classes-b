#ifndef BETREE_HPP
#define BETREE_HPP
#include <functional>

namespace kiselev
{
  template< class T >
  struct BiTree
  {
    T data;
    BiTree< T >* left;
    BiTree< T >* right;
    BiTree< T >* parent;
  };
  template< class T, class Cmp = std::less< T > >
  BiTree< T >* findForInsert(BiTree< T >* root, const T& value, Cmp = Cmp{});

  template< class T, class Cmp = std::less< T > >
  BiTree< T >* pushTree(BiTree< T >* root, const T& value, Cmp = Cmp{});

  template< class T, class Cmp >
  BiTree< T >* findForInsert(BiTree< T >* root, const T& value, Cmp cmp)
  {
    BiTree< T >* parent = nullptr;
    while (root)
    {
      parent = root;
      if (cmp(root->data, value))
      {
        root = root->right;
      }
      else if (cmp(value, root->data))
      {
        root = root->left;
      }
      else
      {
        return nullptr;
      }
    }
    return parent;
  }


  template< class T, class Cmp >
  BiTree< T >* pushTree(BiTree< T >* root, const T& value, Cmp cmp)
  {
    if (!root)
    {
      root = new BiTree< T >{value, nullptr, nullptr, nullptr };
    }
    BiTree< T >* temp = root;
    BiTree< T >* parentTemp = findForInsert(temp, value, cmp);
    if (!parentTemp)
    {
      return root;
    }
    if (cmp(value, parentTemp->data))
    {
      parentTemp->left = new BiTree< T >{ value, nullptr, nullptr, parentTemp };
    }
    else
    {
      parentTemp->right = new BiTree< T >{ value, nullptr, nullptr, parentTemp };
    }
    return root;
  }
  template< class T >
  void deleteTree(BiTree< T >* root)
  {
    if (!root)
    {
      return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}
#endif
