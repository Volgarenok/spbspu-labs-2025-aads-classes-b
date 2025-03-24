#include "iostream"

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

template< class T >
bool BiTreeIterator::hasPrev() const
{
  return prev() != nullptr;
}

template< class T >
bool BiTreeIterator::hasNext() const
{
  return next() != nullptr;
}

template< class T >
BiTreeIterator< T > BiTreeIterator::prev() const
{
  if (node == nullptr)
  {
    return node;
  }
  if (node->left == nullptr)
  {
    BiTree< T > * prev = node;
    node = node->parent;
    while (node->right != prev && node != nullptr)
    {
      prev = node;
      node = node->parent;
    }
    return node;
  }
  else
  {
    node = node->left;
    while (node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  }
}

template< class T >
BiTreeIterator< T > BiTreeIterator::next() const
{
  if (node == nullptr)
  {
    return node;
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
BiTree< T > * addElTree(BiTree< T > * root, const T & value, Cmp cmp)
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
void clear(BiTree< T > * head)
{
  if (head == nullptr)
  {
    return;
  }
  clear(head->left);
  clear(head->right);
  delete head;
}

int main() 
{

}
