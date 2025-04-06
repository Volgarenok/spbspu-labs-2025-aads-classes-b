#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
struct BiTreeIterator
{
  BiTree< T > * node;

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T > next() const;
  BiTreeIterator< T > prev() const;

  const T & data() const;
};

template< class T >
bool BiTreeIterator< T >::hasPrev() const
{
  if (node->left)
  {
    return true;
  }
  BiTree< T >* last = node;
  while(last->parent)
  {
    BiTree< T >* parent = last->parent;
    if (parent->right == last)
    {
      return true;
    }
    last = last->parent;
  }
  return false;
}

template< class T >
bool BiTreeIterator< T >::hasNext() const
{
  if (node->right)
  {
    return true;
  }
  BiTree< T >* last = node;
  while(last->parent)
  {
    BiTree< T >* parent = last->parent;
    if (parent->left == last)
    {
      return true;
    }
    last = last->parent;
  }
  return false;
}

template< class T >
BiTreeIterator< T > BiTreeIterator< T >::next() const
{
  if (!hasNext())
  {
    throw std::logic_error("Error: no next");
  }
  if (node->right)
  {
    BiTree< T >* current = node->right;
    while (current->left)
    {
      current = current->left;
    }
    BiTreeIterator< T > it{current};
    return it;
  }
  BiTree< T >* parent = node->parent;
  BiTree< T >* last = node;
  while (parent->left != last && parent->parent)
  {
    last = last->parent;
    parent = parent->parent;
  }
  BiTreeIterator< T > it{parent};
  return it;
}

template< class T >
BiTreeIterator< T > BiTreeIterator< T >::prev() const
{
  if (!hasPrev())
  {
    throw std::logic_error("Error: no prev");
  }
  if (node->left)
  {
    BiTree< T >* current = node->left;
    while (current->right)
    {
      current = current->right;
    }
    BiTreeIterator< T > it{current};
    return it;
  }
  BiTree< T >* parent = node->parent;
  BiTree< T >* last = node;
  while (parent->right != last && parent->parent)
  {
    last = last->parent;
    parent = parent->parent;
  }
  BiTreeIterator< T > it{parent};
  return it;
}

template< class T >
const T& BiTreeIterator< T >::data() const
{
  return node->data;
}

template< class T >
BiTreeIterator< T > begin(BiTree< T > * root)
{
  if (root == nullptr)
  {
    return BiTreeIterator< T >{nullptr};
  }
  BiTree< T >* min = root;
  while (min->left)
  {
    min = min->left;
  }
  BiTreeIterator< T > begin{min};
  return begin;
}

template< class T >
BiTreeIterator< T > rbegin(BiTree< T > * root)
{
  if (root == nullptr)
  {
    return BiTreeIterator< T >{nullptr};
  }
  BiTree< T >* max = root;
  while (max->right)
  {
    max = max->right;
  }
  BiTreeIterator< T > rbegin{max};
  return rbegin;
}

template< class T, class Cmp = std::less< T > >
void add_root(T x, BiTree< T >* root, Cmp cmp)
{
  BiTree< T >* now = root;
  while (now != nullptr)
  {
    if (cmp(x, now->data))
    {
      if (now->left == nullptr)
      {
        now->left = new BiTree< T >{x, nullptr, nullptr, now};
        return;
      }
        now = now->left;
    }
    else
    {
      if (now->right == nullptr)
      {
        now->right = new BiTree< T >{x, nullptr, nullptr, now};
        return;
      }
      now = now->right;
    }
  }
}

template< class T >
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

template< class T, class Cmp = std::less< T > >
BiTree< T >* input_tree(std::istream& in, size_t size, Cmp cmp = Cmp())
{
  T x = 0;
  if (size == 0)
  {
    return nullptr;
  }
  in >> x;
  if (!in)
  {
    throw std::logic_error("Error in input\n");
  }
  BiTree< T >* root = nullptr;
  try
  {
    root = new BiTree< T >{x, nullptr, nullptr, nullptr};
    for (size_t i = 1; i < size; i++)
    {
      in >> x;
      if (!in)
      {
        throw std::logic_error("Error in input\n");
      }
      add_root(x, root, cmp);
    }
    return root;
  }
  catch(const std::exception& e)
  {
    clear(root);
    throw;
  }
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (!std::cin)
  {
    std::cerr << "Error in input\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  try
  {
    root = input_tree<int>(std::cin, size);
  }
  catch(const std::exception& e)
  {
    clear(root);
    std::cerr << e.what() << '\n';
  }
  std::string way = "meow";
  std::cin >> way;
  if (way == "tomax")
  {
    auto it = begin(root);
    for (; it.hasNext(); it = it.next())
    {
      std::cout << it.data() << " ";
    }
    std::cout << it.data();
  }
  else if (way == "tomin")
  {
    auto it = rbegin(root);
    for (; it.hasPrev(); it = it.prev())
    {
      std::cout << it.data() << " ";
    }
    std::cout << it.data();
  }
  else
  {
    clear(root);
    std::cerr << "Incorrect input\n";
    return 1;
  }
  std::cout << "\n";
  clear(root);
}
