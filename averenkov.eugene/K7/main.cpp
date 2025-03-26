#include <iostream>
#include <string>
#include <sstream>


template< class T, class Cmp >
struct BiTree
{
  T data_;
  Cmp cmp_;
  BiTree< T, Cmp >* left;
  BiTree< T, Cmp >* right;
  BiTree< T, Cmp >* parent;
};

using BiTreeInt = BiTree< int, std::less< int > >;

template< class T, class Cmp >
struct BiTreeIterator
{

public:
  hasPrev() const;
  hasNext() const;
  BiTreeIterator next() const;
  BiTreeIterator prev() const;
  

private:
  BiTree< T, Cmp >* node;

};


template< class T, class Cmp >
bool BiTreeIterator::hasPrev() const
{
  return node && (node->left || node->parent);
}

template< class T, class Cmp >
bool BiTreeIterator::hasNext() const
{
  return node && (node->right || node->parent);
}

template< class T, class Cmp >
BiTreeIterator::BiTreeIterator< T, Cmp > next() const
{
  BiTree< T, Cmp >* n = node;
  if (n->right)
  {
    n = n->right;
    while (n->left) n = n->left;
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
BiTreeIterator::BiTreeIterator< T, Cmp > prev() const
{
  BiTree< T, Cmp >* n = node;
  if (n->left)
  {
    n = n->left;
    while (n->right) n = n->right;
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
const T& BiTreeIterator::data_() const
{
  return node->data_;
}


BiTreeInt* insert(BiTreeInt* root, int value)
{
  if (!root) return new BiTreeInt{ value, std::les3s< int >(), nullptr, nullptr, nullptr };
  BiTreeInt* parent = nullptr;
  BiTreeInt* current = root;
  while (current)
  {
    parent = current;
    if (value < current->data_) current = current->left;
    else current = current->right;
  }
  auto* newNode = new BiTreeInt{ value, std::less< int >(), nullptr, nullptr, parent };
  if (value < parent->data_) parent->left = newNode;
  else parent->right = newNode;
  return root;
}

BiTreeInt* findMin(BiTreeInt* node)
{
  while (node->left) node = node->left;
  return node;
}

BiTreeInt* findMax(BiTreeInt* node)
{
  while (node->right) node = node->right;
  return node;
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
      return 1;
    }
    root = insert(root, value);
  }

  std::string command;
  if (!(std::cin >> command))
  {
    std::cerr << "Error\n";
    return 1;
  }

  if (command == "tomax")
  {
    for (BiTreeIterator< int, std::less< int > > it{ findMin(root) }; it.node; it = it.next())
    {
      std::cout << it.data_() << ' ';
    }
  }
  else if (command == "tomin")
  {
    for (BiTreeIterator< int, std::less< int > > it{ findMax(root) }; it.node; it = it.prev())
    {
      std::cout << it.data_() << ' ';
    }
  }
  else
  {
    std::cerr << "Error\n";
    return 1;
  }

  std::cout << "\n";
  return 0;
}

