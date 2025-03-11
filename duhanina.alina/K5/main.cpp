#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left, * right;
};

template< class T >
void deleteTree(BiTree< T >* root)
{
  if (root != nullptr)
  {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

bool comp(int a, int b)
{
  return a < b;
}

template< class T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp cmp)
{
  while (root != nullptr)
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

template< class T, class Cmp >
BiTree<T>* insert(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr)
  {
    root = new BiTree< T >{ value, nullptr, nullptr };
  }
  else if (cmp(value, root->data))
  {
    root->left = insert(root->left, value, cmp);
  }
  else
  {
    root->right = insert(root->right, value, cmp);
  }
  return root;
}

int main()
{
  size_t length = 0;
  if (!(std::cin >> length))
  {
    std::cerr << "Error\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  for (size_t i = 0; i < length; ++i)
  {
    int value = 0;
    if (!(std::cin >> value))
    {
      std::cerr << "Error\n";
      deleteTree(root);
      return 1;
    }
    root = insert(root, value, comp);
  }
  int searchValue = 0;
  while (std::cin >> searchValue)
  {
    if (find(root, searchValue, comp))
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
    std::cerr << "Error\n";
    deleteTree(root);
    return 1;
  }
  deleteTree(root);
  return 0;
}
