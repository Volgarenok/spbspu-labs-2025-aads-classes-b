#include <iostream>
#include <functional>
#include <string>

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

  bool hasPrev() const
  {
    if (node == nullptr)
    {
      return false;
    }
    if (node->left != nullptr)
    {
      return true;
    }

    BiTree< T, Cmp >* current = node;
    while (current->parent != nullptr && current == current->parent->left)
    {
      current = current->parent;
    }
    return current->parent != nullptr;
  }

  bool hasNext() const
  {
    if (node == nullptr)
    {
      return false;
    }
    if (node->right != nullptr)
    {
      return true;
    }

    BiTree< T, Cmp >* current = node;
    while (current->parent != nullptr && current == current->parent->right)
    {
      current = current->parent;
    }
    return current->parent != nullptr;

  }

  BiTreeIterator< T, Cmp > next() const
  {
    if (node == nullptr)
    {
      return {nullptr};
    }

    if (node->right)
    {
      BiTree< T, Cmp >* current = node->right;
      while (current->left != nullptr)
      {
        current = current->left;
      }
      return {current};
    }
    else
    {
      BiTree< T, Cmp >* current = node;
      while (current->parent != nullptr && current == current->parent->right)
      {
        current = current->parent;
      }
      return {current->parent};
    }
  }

  BiTreeIterator< T, Cmp > prev() const
  {
    if (node == nullptr)
    {
      return {nullptr};
    }
    if (node->left != nullptr)
    {
      BiTree< T, Cmp >* current = node->left;
      while (current->right != nullptr)
      {
        current = current->right;
      }
      return {current};
    }
    else
    {
      BiTree< T, Cmp >* current = node;
      while (current->parent != nullptr && current == current->parent->left)
      {
        current = current->parent;
      }
      return {current->parent};
    }
  }

  const T& data() const
  {
    return node->data;
  }
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

template< class T, class Cmp >
void printTomax(BiTree< T, Cmp >* root, std::ostream& out)
{
  BiTreeIterator< T, Cmp > minIt{root};
  while (minIt.hasPrev())
  {
    minIt = minIt.prev();
  }
  out << minIt.data();
  while (minIt.hasNext())
  {
    minIt = minIt.next();
    out << "\n" << minIt.data();
  }
}

template< class T, class Cmp >
void printTomin(BiTree< T, Cmp >* root, std::ostream& out)
{
  BiTreeIterator< T, Cmp > maxIt{root};
  while (maxIt.hasNext())
  {
    maxIt = maxIt.next();
  }
  out << maxIt.data();
  while (maxIt.hasPrev())
  {
    maxIt = maxIt.prev();
    out << "\n" << maxIt.data();
  }
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
  std::string comand;
  if (!(std::cin >> comand))
  {
    std::cerr << "input error\n";
    clear(root);
    return 1;
  }

  if (comand == "tomax")
  {
    printTomax(root, std::cout);
    std::cout << "\n";
  }
  else if (comand == "tomin")
  {
    printTomin(root, std::cout);
    std::cout << "\n";
  }
  else
  {
    std::cerr << "wrong comand\n";
    clear(root);
    return 1;
  }

  clear(root);
}
