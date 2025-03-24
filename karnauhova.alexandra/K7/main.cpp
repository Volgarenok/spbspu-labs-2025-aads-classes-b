#include <iostream>

template< class T, class Cmp = std::less< T > >
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
void add_root(T x, BiTree< T >* root, Cmp cmp)
{
  BiTree< T >* now = root;
  while (now != nullptr)
  {
    if (cmp(x, now->data))
    {
      if (now->right == nullptr)
      {
        now->right = new BiTree<T>{x, nullptr, nullptr};
        return;
      }
      else
      {
        now = now->right;
      }
    }
    else
    {
      if (now->left == nullptr)
      {
        now->left = new BiTree<T>{x, nullptr, nullptr};
        return;
      }
      else
      {
        now = now->left;
      }
    }
  }
}

template< class T, class Cmp = std::less< T > >
BiTree< T >* input_tree(std::istream& in, size_t size, Cmp cmp)
{
  T x = 0;
  if (size == 0)
  {
    return nullptr;
  }
  in >> x;
  if (!in)
  {
    throw std::logic_error("Error in input\n");
  }
  try
  {
    BiTree< T >* root = new BiTree< T >{x, nullptr, nullptr, nullptr};
    for (size_t i = 0; i < size; i++)
    {
        in >> x;
        if (!in)
        {
        throw std::logic_error("Error in input\n");
        }
        add_root(x, root, cmp);
    }
    return root;
  }
  catch(const std::exception& e)
  {
    clear(root);
    throw;
  }
  
  
}

int main()
{
  size_t size = 0;
  std::cin >> size;

}
