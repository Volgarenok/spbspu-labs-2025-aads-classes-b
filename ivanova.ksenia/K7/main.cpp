#include <iostream>

template< class T, class Cmp = std::less<T> >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp = std::less<T> >
struct BiTreeIterator
{
  BiTree< T, Cmp > * node;

  bool hasPrev() const
  {
    if(!node)
    {
      return false;
    }
    return node->left;
  }
  
  bool hasNext() const
  {
    if(!node)
    {
      return false;
    }
    return node->right;
  }
  
  BiTreeIterator< T, Cmp > next() const
  {
    if (!node || !node->right)
    {
      throw std::runtime_error("No next element");
    }
    return BiTreeIterator<T, Cmp>{node->right};
  }
  
  BiTreeIterator< T, Cmp > prev() const
  {
    if (!node || !node->left)
    {
      throw std::runtime_error("No previous element");
    }
    return BiTreeIterator<T, Cmp>{node->left};
  }

  const T & data() const
  {
    if (!node)
    {
      throw std::runtime_error("Iterator is not dereferenceable");
    }
    return node->data;
  }
};

int main()
{
  int n;
  std::cin >> n;
  if (n < 0) {
    std::cerr << "Invalid sequence length" << '\n';
    return 1;
  }
  //в твоём сообщении много букв
  //значит мне уже пофиг
}
