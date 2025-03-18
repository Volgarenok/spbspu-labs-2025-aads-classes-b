#include <iostream>

template < class T >
struct BiTree
{
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
};

template < class T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T &value, Cmp cmp)
{
  while (root)
  {
    if (cmp(value, root->data))
    {
      root = root->left;
    }
    else if (cmp(root->data, value))
    {
      root = root->right;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}

template < class T, class Cmp >
BiTree< T >* insert(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (!root)
  {
    return new BiTree< T >{value, nullptr, nullptr};
  }
  if (cmp(value, root->data))
  {
    root->left = insert(root->left, value, cmp);
  }
  else
  {
    root->right = insert(root->right, value, cmp);
  }
  return root;
}

template < class T >
void clear(BiTree< T >* root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

struct IntComparator
{
  bool operator()(int a, int b) const
  {
    return a < b;
  }
};

int main()
{
  int n;
  if (!(std::cin >> n))
  {
    std::cerr << "error input\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  IntComparator cmp;
  for (int i = 0, x; i < n; i++)
  {
    if (!(std::cin >> x))
    {
      std::cerr << "error\n";
      clear(root);
      return 1;
    }
    root = insert(root, x, cmp);
  }
  int x;
  while (std::cin >> x)
  {
    if (find(root, x, cmp))
    {
      std::cout << "<FOUND>\n";
    }
    else
    {
      std::cout << "<NOT FOUND>\n";
    }
  }
  if (!std::cin.eof())
  {
    std::cerr << "error input\n";
    clear(root);
    return 1;
  }
  clear(root);
  return 0;
}

