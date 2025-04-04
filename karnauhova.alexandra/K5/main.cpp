#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

bool isGreater(int first, int second)
{
  return first > second;
}

template< class T, class Cmp >
BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp)
{
  const BiTree< T >* big_root = root;
  while (big_root != nullptr)
  {
    if (cmp(value, big_root->data))
    {
      big_root = big_root->right;
    }
    else
    {
      if (value == big_root->data)
      {
        return const_cast< BiTree< T >* >(big_root);
      }
      big_root = big_root->left;
    }
  }
  return nullptr;
}

template< class T >
void clear(BiTree< T >* root)
{
  if (root == nullptr)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

template< class T, class Cmp >
BiTree< T > * intput_tree(size_t size, std::istream& in, Cmp cmp)
{
  BiTree< T >* root = nullptr;
  if (!size)
  {
    return root;
  }
  try
  {
    T x = 0;
    in >> x;
    root = new BiTree< T >{x, nullptr, nullptr};
    for (size_t i = 1; i < size; i++)
    {
      in >> x;
      BiTree< T >* now = root;
      while (now != nullptr)
      {
        if (cmp(x, now->data))
        {
          if (now->right == nullptr)
          {
            now->right = new BiTree<T>{x, nullptr, nullptr};
            break;
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
            break;
          }
          else
          {
            now = now->left;
          }
        }
      }
    }
  }
  catch (const std::bad_alloc& e)
  {
    clear(root);
    throw;
  }
  return root;
}

int main()
{
  size_t size_tree = 0;
  std::cin >> size_tree;
  int x = 0;
  BiTree< int >* root = nullptr;
  try
  {
    root = intput_tree<int>(size_tree, std::cin, isGreater);
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr <<"Out of memory\n";
    return 1;
  }
  while (std::cin >> x)
  {
    if (find< int >(root, x, isGreater))
    {
      std::cout << "<FOUND>\n";
    }
    else
    {
      std::cout << "<NOT FOUND>\n";
    }
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "Incorrect number\n";
    clear(root);
    return 1;
  }
  clear(root);
}
