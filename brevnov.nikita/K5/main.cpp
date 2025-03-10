#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T >
bool comp(const T & a, const T & b)
{
  return a <= b;
}

template< class T, class Cmp >
void addElTree(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< T > * sub = root;
  if (root == nullptr)
  {
    root = new BiTree< T >{value, nullptr, nullptr};
    return;
  }
  bool done = false;
  while (!done)
  {
    if (cmp.funComp(sub->data, value))
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

template< class T, class Cmp >
const BiTree< T > * find(const BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< T >  * sub = root;
  while (sub != nullptr)
  {
    if (sub->data == value)
    {
      return sub;
    }
    else if (cmp(sub->data, value))
    {
      sub = sub->right;
    }
    else
    {
      sub = sub->left;
    }
  }
  return sub;
}

int main()
{
  size_t n = 0;
  std::cin >> n;
  if (std::cin.fail())
  {
    std::cerr << "Not correct input!\n";
    return 1;
  }
  BiTree< int > * root = nullptr;
  int b = 0;
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> b;
    if (std::cin.fail())
    {
      std::cerr << "Not correct input!\n";
      clear(root);
      return 1;
    }
    if (std::cin.eof())
    {
      std::cerr << "Not enough elements!\n";
      clear(root);
      return 1;
    }
    try
    {
      addElTree(root, b, comp);
    }
    catch(const std::bad_alloc & e)
    {
      std::cerr << "Nor enough memory!\n";
      clear(root);
      return 1;
    }
  }
  while (std::cin >> b && std::cin.good())
  {
    if (find(root, b, comp))
    {
      std::cout << "<FOUND>\n";
    }
    else
    {
      std::cout << "<NOT FOUND>\n";
    }
  }
  if (std::cin.fail())
  {
    std::cerr << "Not correct input!\n";
    clear(root);
    return 1;
  }
  clear(root);
  return 0;
}
