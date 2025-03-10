#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp);

template< class T >
void clear(BiTree< T >* root)
{
  while (root->left != nullptr && root->right != nullptr)
  {
    BiTree< T >* now = root;
    while (now->left != nullptr && now->right != nullptr)
    {
      if (now->right != nullptr)
      {
        now = now->right;
      }
      if (now->left != nullptr)
      {
        now = now->left;
      }
    }
    delete now;
    now = nullptr;
  }
  delete root;
}

template< class T >
BiTree< T > * output_tree(size_t size, std::ostream& out)
{
  BiTree< T >* root = nullptr;
  try
  {
    T x = 0;
    out >> x;
    root = new BiTree< T >{x, nullptr, nullptr};
    for (size_t i = 0, i < size, i++)
    {
      out >> x;
      BiTree< T >* now = root;
      while (now != nullptr)
      {
        if (x > now->data)
        {
          now = now->right;
        }
        else
        {
          now = now->left;
        }
      }
      now = new BiTree< T >{x, nullptr, nullptr};
    }
  }
  catch (const std::bad_alloc& e)
  {
    clear(root);
    throw;
  }
}

int main()
{
  size_t size_tree = 0;
  std::cin >> size_tree;
  BiTree< int >* root = nullptr;
  try
  {
    root = output_tree(size, std::cin);
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr <<'Out of memory\n';
    return 1;
  } 
}
