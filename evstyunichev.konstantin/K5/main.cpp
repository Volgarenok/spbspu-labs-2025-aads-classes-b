#include <iostream>
#include <functional>
#include <stdexcept>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
  BiTree(T &);
};

template< class T >
BiTree< T >::BiTree(T &d):
  data(d),
  left(nullptr),
  right(nullptr)
{
}

template< class T >
void clear(BiTree< T > *root)
{
  if (!root)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

template< class T >
BiTree< T > * create(T data)
{
  return new BiTree< T >{ data };
}

template< class T, class Cmp >
void push(BiTree< T > *subroot, T data, Cmp cmp)
{
  if (cmp(data, subroot->data))
  {
    if (!subroot->left)
    {
      subroot->left = new BiTree< T >{ data };
      return;
    }
    push(subroot->left, data, cmp);
    return;
  }
  else if (cmp(subroot->data, data))
  {
    if (!subroot->right)
    {
      subroot->right = new BiTree< T >{ data };
      return;
    }
    push(subroot->right, data, cmp);
    return;
  }
  return;
}

template< class T, class Cmp >
const BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp)
{
  if (!root)
  {
    return root;
  }

  if (cmp(value, root->data))
  {
    return find(root->left, value, cmp);
  }
  else if (cmp(root->data, value))
  {
    return find(root->right, value, cmp);
  }
  else
  {
    return root;
  }
}

bool comp(int a, int b)
{
  return a < b;
}

int main()
{
  BiTree< int > *root = nullptr;
  try
  {
    size_t n = 0;
    std::cin >> n;
    int data = 0;
    if (n)
    {
      std::cin >> data;
      root = create(data);
    }
    for (size_t i = 1; i < n; i++)
    {
      if (std::cin >> data)
      {
        push(root, data, comp);
      }
      else
      {
        throw std::invalid_argument("vnrejv");
      }
    }
    while (std::cin >> data)
    {
      if (!find(root, data, comp))
      {
        std::cout << "NOTFOUND\n";
      }
      else
      {
        std::cout << "FOUND\n";
      }
    }
    clear(root);
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    clear(root);
    return 1;
  }
}
