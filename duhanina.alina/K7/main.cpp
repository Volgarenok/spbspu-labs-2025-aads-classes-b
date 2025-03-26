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

  bool hasPrev() const
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
    }
    return false;
  }

  bool hasNext() const
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
    }
    return false;
  }

  BiTreeIterator< T, Cmp > next() const
  {
    if (!node)
    {
      throw std::runtime_error("No next node");
    }
    if (node->right)
    {
      BiTree< T, Cmp >* current = node->right;
      while (current->left)
      {
        current = current->left;
      }
      return BiTreeIterator< T, Cmp >{ current };
    }
    BiTree< T, Cmp >* current = node;
    while (current->parent)
    {
      if (current->parent->left == current)
      {
        return BiTreeIterator< T, Cmp >{ current->parent };
      }
      current = current->parent;
    }
    throw std::runtime_error("No next node");
  }

  BiTreeIterator< T, Cmp > prev() const
  {
    if (!node)
    {
      throw std::runtime_error("No prev node");
    }
    if (node->left)
    {
      BiTree< T, Cmp >* current = node->left;
      while (current->right)
      {
        current = current->right;
      }
      return BiTreeIterator< T, Cmp >{ current };
    }
    BiTree< T, Cmp >* current = node;
    while (current->parent)
    {
      if (current->parent->right == current)
      {
        return BiTreeIterator< T, Cmp >{ current->parent };
      }
      current = current->parent;
    }
    throw std::runtime_error("No prev node");
  }

  const T& data() const
  {
    if (!node)
    {
      throw std::runtime_error("No data");
    }
    return node->data;
  }
};

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
BiTree< T, Cmp >* find_min(BiTree< T, Cmp >* node)
{
  while (node && node->left)
  {
    node = node->left;
  }
  return node;
}

template< class T, class Cmp >
BiTree< T, Cmp >* find_max(BiTree< T, Cmp >* node)
{
  while (node && node->right)
  {
    node = node->right;
  }
  return node;
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
      int value;
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
    if (command == "tomax")
    {
      BiTreeIterator< int, std::less< int > > it{ find_min(root) };
      if (it.node)
      {
        std::cout << it.data();
        while (it.hasNext())
        {
          it = it.next();
          std::cout << " " << it.data();
        }
      }
      std::cout << "\n";
    }
    else if (command == "tomin")
    {
      BiTreeIterator< int, std::less< int > > it{ find_max(root) };
      if (it.node)
      {
        std::cout << it.data();
        while (it.hasPrev())
        {
          it = it.prev();
          std::cout << " " << it.data();
        }
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
