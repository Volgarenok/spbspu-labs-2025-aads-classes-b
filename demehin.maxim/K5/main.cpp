#include <iostream>
#include <functional>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left, * right;
};

template< class T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr)
  {
    return nullptr;
  }

  if (!cmp(value, root->data) && !cmp(root->data, value))
  {
    return root;
  }
  else if (cmp(value, root->data))
  {
    return find(root->left, value, cmp);
  }
  else
  {
    return find(root->right, value, cmp);
  }
}

template< class T, class Cmp >
BiTree< T >* insNode(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr)
  {
    BiTree< T >* newNode = new BiTree< T >{value, nullptr, nullptr};
    return newNode;
  }

  if (cmp(value, root->data))
  {
    root->left = insNode(root->left, value, cmp);
  }
  else
  {
    root->right = insNode(root->right, value, cmp);
  }
  return root;
}

template< typename T >
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

int main()
{
  size_t s = 0;
  if (!(std::cin >> s))
  {
    std::cerr << "input error\n";
    return 1;
  }

  BiTree< int >* root = nullptr;
  for (size_t i = 0; i < s; i++)
  {
    int val = 0;
    if (!(std::cin >> val))
    {
      std::cerr << "input error\n";
      clear(root);
      return 1;
    }
    root = insNode(root, val, std::less< int >());
  }

  int num = 0;
  while (true)
  {
    if (!(std::cin >> num))
    {
      if (std::cin.eof())
      {
        break;
      }
      std::cerr << "input error\n";
      clear(root);
      return 1;
    }

    if (find(root, num, std::less< int >()) != nullptr)
    {
      std::cout << "<FOUND>\n";
    }
    else
    {
      std::cout << "<NOT FOUND>\n";
    }
  }
  clear(root);
}
