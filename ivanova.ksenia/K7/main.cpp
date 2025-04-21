#include <iostream>
#include <string>
#include <stdexcept>

template< class T, class Cmp = std::less<T> >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp = std::less<T> >
struct BiTreeIterator
{
  BiTree< T, Cmp > * node;

  bool hasPrev() const
  {
    if(!node)
    {
      return false;
    }
    return node->left;
  }
  
  bool hasNext() const
  {
    if(!node)
    {
      return false;
    }
    return node->right;
  }
  
  BiTreeIterator< T, Cmp > next() const
  {
    if (!node || !node->right)
    {
      throw std::runtime_error("No next element");
    }
    return BiTreeIterator<T, Cmp>{node->right};
  }
  
  BiTreeIterator< T, Cmp > prev() const
  {
    if (!node || !node->left)
    {
      throw std::runtime_error("No previous element");
    }
    return BiTreeIterator<T, Cmp>{node->left};
  }

  const T & data() const
  {
    if (!node)
    {
      throw std::runtime_error("Iterator is not dereferenceable");
    }
    return node->data;
  }
};

template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp > * root)
{
  if (!root) return BiTreeIterator<T, Cmp>{nullptr};
  while (root->left)
  {
    root = root->left;
  }
  return BiTreeIterator<T, Cmp>{root};
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp > * root)
{
  if (!root) return BiTreeIterator<T, Cmp>{nullptr};
  while (root->right)
  {
    root = root->right;
  }
  return BiTreeIterator<T, Cmp>{root};
}

template< class T, class Cmp = std::less<T> >
void insert(BiTree< T, Cmp > ** root, const T & value)
{
  BiTree< T, Cmp > ** current = root;
  BiTree< T, Cmp > * parent = nullptr;

  while (*current)
  {
    parent = *current;
    if ((*current)->cmp(value, (*current)->data))
    {
      current = &(*current)->left;
    }
    else if ((*current)->cmp((*current)->data, value))
    {
      current = &(*current)->right;
    }
    else
    {
      throw std::runtime_error("Duplicate values not allowed");
    }
  }

  *current = new BiTree< T, Cmp >{value, Cmp{}, nullptr, nullptr, parent};
}

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (!root) return;
  clear(root->left);
  clear(root->right);
  delete root;
}


int main()
{
  try
  {
    int n;
    if (!(std::cin >> n))
    {
      throw std::runtime_error("Failed to read sequence length");
    }
    if (n < 0)
    {
      throw std::runtime_error("Invalid sequence length");
    }

    BiTree<int> * root = nullptr;
    for (int i = 0; i < n; ++i)
    {
      int value;
      if (!(std::cin >> value))
      {
        clear(root);
        throw std::runtime_error("Failed to read sequence element");
      }
      insert(&root, value);
    }

    std::string command;
    if (!(std::cin >> command))
    {
      clear(root);
      throw std::runtime_error("No command provided");
    }

    if (command == "tomax")
    {
      for (auto it = begin(root); it.node; it = it.next())
      {
        std::cout << it.data() << " ";
      }
      std::cout << "\n";
    }
    else if (command == "tomin")
    {
      for (auto it = rbegin(root); it.node; it = it.prev())
      {
        std::cout << it.data() << " ";
      }
      std::cout << '\n';
    }
    else
    {
      clear(root);
      throw std::runtime_error("Invalid command");
    }

    clear(root);
    return 0;
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
