#include <iostream>
#include <string>

template< class T, class Cmp = std::less< T >>
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T > * left, * right, * parent;
};

template< class T >
struct BiTreeIterator {
  BiTreeIterator(BiTree< T > * node_): node(node_) {}
  BiTree< T > * node;

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T > next() const;
  BiTreeIterator< T > prev() const;

  const T & data() const;
};

template< class T, class Cmp = std::less< T > >
BiTree< T > * addElTree(BiTree< T > * root, const T & value, Cmp = Cmp{});

template< class T >
void clear(BiTree< T > * head);

template< class T >
bool BiTreeIterator< T >::hasPrev() const
{
  return prev().node != nullptr;
}

template< class T >
bool BiTreeIterator< T >::hasNext() const
{
  return next().node != nullptr;
}

template< class T >
BiTreeIterator< T > BiTreeIterator< T >::prev() const
{
  if (node == nullptr)
  {
    return node;
  }
  BiTree< T > * help = node;
  if (help->left == nullptr)
  {
    BiTree< T > * prev = help;
    help = help->parent;
    while (help->right != prev && help != nullptr)
    {
      prev = help;
      help = help->parent;
    }
    return help;
  }
  else
  {
    help = help->left;
    while (help->right != nullptr)
    {
      help = help->right;
    }
    return help;
  }
}

template< class T >
BiTreeIterator< T > BiTreeIterator< T >::next() const
{
  if (node == nullptr)
  {
    return node;
  }
  BiTree< T > * help = node;
  if (help->right == nullptr)
  {
    BiTree< T > * prev = help;
    help = help->parent;
    while (help->left != prev && help != nullptr)
    {
      prev = help;
      help = help->parent;
    }
    return help;
  }
  else
  {
    help = help->right;
    while (help->left != nullptr)
    {
      help = help->left;
    }
    return help;
  }
}

template< class T >
const T & BiTreeIterator< T >::data() const
{
  return node->data;
}

template< class T, class Cmp >
BiTree< T > * addElTree(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< T > * sub = root;
  if (root == nullptr)
  {
    return new BiTree< T >{value, cmp, nullptr, nullptr, nullptr};
  }
  bool done = false;
  while (!done)
  {
    if (cmp(sub->data, value))
    {
      if (sub->right == nullptr)
      {
        sub->right = new BiTree< T >{value, cmp, nullptr, nullptr, sub};
        done = true;
      }
      else
      {
        sub = sub->right;
      }
    }
    else
    {
      if (sub->left == nullptr)
      {
        sub->left = new BiTree< T >{value, cmp, nullptr, nullptr, sub};
        done = true;
      }
      else
      {
        sub = sub->left;
      }
    }
  }
  return root;
}

template< class T >
void clear(BiTree< T > * head)
{
  if (head == nullptr)
  {
    return;
  }
  clear(head->left);
  clear(head->right);
  delete head;
}

int main()
{
  int n = 0;
  std::cin >> n;
  if (n <= 0)
  {
    std::cerr << "Not correct input!\n";
    return 1;
  }
  BiTree< int > * root = nullptr;
  int b = 0;
  for (int i = 0; i < n; i++)
  {
    std::cin >> b;
    if (std::cin.fail())
    {
      std::cerr << "Not correct input!\n";
      clear(root);
      return 1;
    }
    if (std::cin.eof())
    {
      std::cerr << "Not enough elements!\n";
      clear(root);
      return 1;
    }
    try
    {
      root = addElTree(root, b);
    }
    catch(const std::bad_alloc & e)
    {
      std::cerr << "Nor enough memory!\n";
      clear(root);
      return 1;
    }
  }
  std::string com = "";
  std::cin >> com;
  BiTree< int > * help = root;
  if (com == "tomax")
  {
    if (!root)
    {
      std::cout << "\n";
      return 0;
    }
    while (help->left != nullptr)
    {
      help = help->left;
    }
    BiTreeIterator< int > start(help);
    while (start.hasNext())
    {
      std::cout << start.data() << " ";
      start = start.next();
    }
    std::cout << start.data() << "\n";
    clear(root);
    return 0;
  }
  else if (com == "tomin")
  {
    if (!root)
    {
      std::cout << "\n";
      return 0;
    }
    while (help->right != nullptr)
    {
      help = help->right;
    }
    BiTreeIterator< int > start(help);
    while (start.hasPrev())
    {
      std::cout << start.data() << " ";
      start = start.prev();
    }
    std::cout << start.data() << "\n";
    clear(root);
    return 0;
  }
  else
  {
    std::cerr << "Not correct command!\n";
    clear(root);
    return 1;
  }
}
