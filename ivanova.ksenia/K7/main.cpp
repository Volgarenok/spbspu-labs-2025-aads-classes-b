#include <iostream>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T > * left, * right, * parent;
};

template< class T >
struct BiTreeIterator
{
  BiTree< T > * node;

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
  BiTreeIterator< T > next() const
  {
    if (!node || !node->right)
    {
      std::cerr << "No previous element" << '\n';
      throw;
    }
    return BiTreeIterator<T, Cmp>(node->right);
  }
  BiTreeIterator< T > prev() const
  {
    if (!node || !node->left)
    {
      std::cerr << "No previous element" << '\n';
      throw;
    }
    return BiTreeIterator<T, Cmp>(node->left);
  }

  const T & data() const
  {
    if (!node)
    {
      std::cerr << "Iterator is not dereferenceable" << '\n';
      throw;
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
