#include <iostream>
#include <string>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp >* left;
  BiTree< T, Cmp >* right;
  BiTree< T, Cmp >* parent;
};

using BiTreeInt = BiTree< int, std::less< int > >;

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
bool BiTreeIterator< T, Cmp >::hasPrev() const
{
  return node && (node->left || node->parent);
}

template< class T, class Cmp >
bool BiTreeIterator< T, Cmp >::hasNext() const
{
  return node && (node->right || node->parent);
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::next() const
{
  BiTree< T, Cmp >* n = node;
  if (n->right)
  {
    n = n->right;
    while (n->left)
    {
      n = n->left;
    }
  }
  else
  {
    while (n->parent && n == n->parent->right)
    {
      n = n->parent;
    }
    n = n->parent;
  }
  return { n };
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::prev() const
{
  BiTree< T, Cmp >* n = node;
  if (n->left)
  {
    n = n->left;
    while (n->right)
    {
      n = n->right;
    }
  }
  else
  {
    while (n->parent && n == n->parent->left)
    {
      n = n->parent;
    }
    n = n->parent;
  }
  return { n };
}

template< class T, class Cmp >
const T& BiTreeIterator< T, Cmp >::data() const
{
  return node->data;
}

BiTreeInt* insert(BiTreeInt* root, int value)
{
  if (!root)
  {
    return new BiTreeInt{ value, std::less< int >(), nullptr, nullptr, nullptr };
  }
  BiTreeInt* parent = nullptr;
  BiTreeInt* current = root;
  while (current)
  {
    parent = current;
    if (value < current->data)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  auto* newNode = new BiTreeInt{ value, std::less< int >(), nullptr, nullptr, parent };
  if (value < parent->data)
  {
    parent->left = newNode;
  }
  else
  {
    parent->right = newNode;
  }
  return root;
}

BiTreeInt* findMin(BiTreeInt* node)
{
  if (!node)
  {
    return nullptr;
  }
  while (node->left)
  {
    node = node->left;
  }
  return node;
}

BiTreeInt* findMax(BiTreeInt* node)
{
  if (!node)
  {
    return nullptr;
  }
  while (node->right)
  {
    node = node->right;
  }
  return node;
}

void deleteTree(BiTreeInt* node)
{
  if (!node)
  {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

int main()
{
  int n;
  if (!(std::cin >> n))
  {
    std::cerr << "Error\n";
    return 1;
  }

  BiTreeInt* root = nullptr;
  for (int i = 0; i < n; ++i)
  {
    int value;
    if (!(std::cin >> value))
    {
      std::cerr << "Error\n";
      deleteTree(root);
      return 1;
    }
    root = insert(root, value);
  }

  std::string command;
  if (!(std::cin >> command))
  {
    std::cerr << "Error\n";
    deleteTree(root);
    return 1;
  }

  if (command == "tomax")
  {
    BiTreeInt* minNode = findMin(root);
    if (minNode)
    {
      BiTreeIterator< int, std::less< int > > it{ minNode };
      std::cout << it.data();
      for (it = it.next(); it.node; it = it.next())
      {
        std::cout << ' ' << it.data();
      }
    }
  }
  else if (command == "tomin")
  {
    BiTreeInt* maxNode = findMax(root);
    if (maxNode)
    {
      BiTreeIterator< int, std::less< int > > it{ maxNode };
      std::cout << it.data();
      for (it = it.prev(); it.node; it = it.prev())
      {
        std::cout << ' ' << it.data();
      }
    }
  }
  else
  {
    std::cerr << "Error\n";
    deleteTree(root);
    return 1;
  }
  std::cout << "\n";
  deleteTree(root);
  return 0;
}
