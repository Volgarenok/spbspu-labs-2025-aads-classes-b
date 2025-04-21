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

template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp > * root)
{
  if (!root) return BiTreeIterator<T, Cmp>{nullptr};
  while (root->left)
  {
    root = root->left;
  }
  return BiTreeIterator<T, Cmp>{root};
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp > * root)
{
  if (!root) return BiTreeIterator<T, Cmp>{nullptr};
  while (root->right)
  {
    root = root->right;
  }
  return BiTreeIterator<T, Cmp>{root};
}

template< class T, class Cmp = std::less<T> >
void insert(BiTree< T, Cmp > ** root, const T & value)
{
  BiTree< T, Cmp > ** current = root;
  BiTree< T, Cmp > * parent = nullptr;

  while (*current)
  {
    parent = *current;
    if ((*current)->cmp(value, (*current)->data))
    {
      current = &(*current)->left;
    }
    else if ((*current)->cmp((*current)->data, value))
    {
      current = &(*current)->right;
    }
    else
    {
      throw std::runtime_error("Duplicate values not allowed");
    }
  }

  *current = new BiTree< T, Cmp >{value, Cmp{}, nullptr, nullptr, parent};
}

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (!root) return;
  clear(root->left);
  clear(root->right);
  delete root;
}

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
