#include <iostream>
#include <functional>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cpm;
  BiTree< T, Cmp >* left, * right, * parent;
};

template< class T, class Cmp >
struct BiTreeIterator
{
  BiTree< T, Cmp >* node;

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T, Cmp > next() const;
  BiTreeIterator< T, Cmp > prev() const;

  const T& data() const;
};

template< class T, class Cmp >
BiTree< T, Cmp >* insNode(BiTree< T, Cmp >* root, const T& value, Cmp cmp, BiTree< T, Cmp >* parent = nullptr)
{
  if (root == nullptr)
  {
    BiTree< T, Cmp >* newNode = new BiTree< T, Cmp >{value, cmp, nullptr, nullptr, parent};
    return newNode;
  }

  if (cmp(value, root->data))
  {
    root->left = insNode(root->left, value, cmp, root);
  }
  else
  {
    root->right = insNode(root->right, value, cmp, root);
  }
  return root;
}

template< class T, class Cmp >
void clear(BiTree< T, Cmp >* root)
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
  size_t n = 0;
  std::cin >> n;
  BiTree< int, std::less< int > >* root = nullptr;
  int num = 0;
  for (size_t i = 0; i < n; i++)
  {
    if (!(std::cin >> num))
    {
      std::cerr << "input error\n";
      clear(root);
      return 1;
    }
    root = insNode(root, num, std::less< int >(), root);
  }

  clear(root);
}
