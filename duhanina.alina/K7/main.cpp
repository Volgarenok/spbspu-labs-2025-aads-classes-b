#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp >* left;
  BiTree< T, Cmp >* right;
  BiTree< T, Cmp >* parent;
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
bool BiTreeIterator< T, Cmp >::hasPrev() const
{
  if (!node)
  {
    return false;
  }
  if (node->left)
  {
    return true;
  }
  BiTree< T, Cmp >* current = node;
  while (current->parent)
  {
    if (current->parent->right == current)
    {
      return true;
    }
    current = current->parent;
  }
  return false;
}

template< class T, class Cmp >
bool BiTreeIterator< T, Cmp >::hasNext() const
{
  if (!node)
  {
    return false;
  }
  if (node->right)
  {
    return true;
  }
  BiTree< T, Cmp >* current = node;
  while (current->parent)
  {
    if (current->parent->left == current)
    {
      return true;
    }
    current = current->parent;
  }
  return false;
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::next() const
{
  BiTree< T, Cmp >* current = node;
  if (current->right)
  {
    current = current->right;
    while (current->left)
    {
      current = current->left;
    }
  }
  else
  {
    while (current->parent && current == current->parent->right)
    {
      current = current->parent;
    }
    current = current->parent;
  }
  return { current };
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::prev() const
{
  BiTree< T, Cmp >* current = node;
  if (current->left)
  {
    current = current->left;
    while (current->right)
    {
      current = current->right;
    }
  }
  else
  {
    while (current->parent && current == current->parent->left)
    {
      current = current->parent;
    }
    current = current->parent;
  }
  return { current };
}

template< class T, class Cmp >
const T& BiTreeIterator< T, Cmp >::data() const
{
  return node->data;
}

template< class T, class Cmp >
BiTree< T, Cmp >* insert(BiTree< T, Cmp >* node, const T& value, BiTree< T, Cmp >* parent = nullptr)
{
  if (!node)
  {
    BiTree< T, Cmp >* newNode = new BiTree< T, Cmp >{ value, Cmp(), nullptr, nullptr, parent };
    return newNode;
  }
  if (node->cmp(value, node->data))
  {
    node->left = insert(node->left, value, node);
  }
  else
  {
    node->right = insert(node->right, value, node);
  }
  return node;
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp >* root)
{
  BiTreeIterator< T, Cmp > it{ root };
  while (it.hasPrev())
  {
    it = it.prev();
  }
  return it;
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp >* root)
{
  BiTreeIterator< T, Cmp > it{ root };
  while (it.hasNext())
  {
    it = it.next();
  }
  return it;
}

template< class T, class Cmp >
void free_tree(BiTree< T, Cmp >* node)
{
  if (node)
  {
    free_tree(node->left);
    free_tree(node->right);
    delete node;
  }
}

int main()
{
  try
  {
    BiTree< int, std::less< int > >* root = nullptr;
    size_t length = 0;
    std::cin >> length;
    for (size_t i = 0; i < length; ++i)
    {
      int value = 0;
      if (!(std::cin >> value))
      {
        free_tree(root);
        throw std::runtime_error("Failed");
      }
      root = insert(root, value);
    }
    std::string command;
    if (!(std::cin >> command))
    {
      free_tree(root);
      throw std::runtime_error("No command");
    }
    if (length == 0)
    {
      std::cout << "\n";
      return 0;
    }
    if (command == "tomax")
    {
      BiTreeIterator< int, std::less< int > > it = begin(root);
      std::cout << it.data();
      for (it = it.next(); it.node; it = it.next())
      {
        std::cout << " " << it.data();
      }
      std::cout << "\n";
    }
    else if (command == "tomin")
    {
      BiTreeIterator< int, std::less< int > > it = rbegin(root);
      std::cout << it.data();
      for (it = it.prev(); it.node; it = it.prev())
      {
        std::cout << " " << it.data();
      }
      std::cout << "\n";
    }
    else
    {
      free_tree(root);
      throw std::runtime_error("Invalid command");
    }
    free_tree(root);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
