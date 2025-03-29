#include <iostream>
#include <new>
template< class T >
struct BiTree {
    T data;
    BiTree< T >* left, * right;
};

template< class T, class Cmp = std::less< T > >
std::pair< const BiTree< T >*, BiTree< T >* > findWithParent(const BiTree< T >* root, const T& value, Cmp = Cmp{});

template< typename T, class Cmp = std::less< T > >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp = Cmp{});

template< class T, class Cmp = std::less< T > >
BiTree< T >* pushTree(BiTree< T >* root, const T& value, Cmp = Cmp{});

template< typename T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp cmp)
{
  return findWithParent(root, value, cmp).first;
}
template< class T, class Cmp >
std::pair< const BiTree< T >*, BiTree< T >* > findWithParent(const BiTree< T >* root, const T& value, Cmp cmp)
{
  BiTree< T >* parent = nullptr;
  while (root)
  {
    parent = const_cast< BiTree< T >* >(root);
    if (cmp(root->data, value))
    {
      root = root->right;
    }
    else if (cmp(value, root->data))
    {
      root = root->left;
    }
    else
    {
      return { root, parent };
    }
  }
  return { nullptr, parent };
}

template< class T, class Cmp >
BiTree< T >* pushTree(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (!root)
  {
    root = new BiTree< T >{value, nullptr, nullptr };
  }
  BiTree< T >* temp = root;
  BiTree< T >* parentTemp = findWithParent(temp, value, cmp).second;
  if (cmp(value, parentTemp->data))
  {
    parentTemp->left = new BiTree< T >{ value, nullptr, nullptr };
  }
  else
  {
    parentTemp->right = new BiTree< T >{ value, nullptr, nullptr };
  }
  return root;
}

template< class T >
void deleteTree(BiTree< T >* root)
{
  if(!root)
  {
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

int main()
{
  size_t length = 0;
  std::cin >> length;
  BiTree< int >* root = nullptr;
  for (size_t i = 0; i < length; ++i)
  {
    int number;
    if (!(std::cin >> number))
    {
      std::cerr << "Incorrect number\n";
      deleteTree(root);
      return 1;
    }
    try
    {
      root = pushTree(root, number);
    }
    catch (std::bad_alloc&)
    {
      deleteTree(root);
      std::cerr << "Out of memory\n";
      return 0;
    }
  }
  int findNum;
  while (std::cin >> findNum)
  {
    if (find(root, findNum))
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
    deleteTree(root);
    return 1;
  }
  deleteTree(root);
  return 0;
}
