#include <algorithm>
#include <iostream>
#include <string>

template< class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp > *left, *right, *parent;
  BiTree(const T &value, Cmp comp):
    data(value),
    cmp(comp),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}
  BiTree(const T &value, Cmp comp, BiTree< T, Cmp > *p):
    data(value),
    cmp(comp),
    left(nullptr),
    right(nullptr),
    parent(p)
  {}
};

template< class T, class Cmp >
struct BiTreeIterator {
  BiTree< T, Cmp > *node_;

  BiTreeIterator(BiTree< T, Cmp > *node);

  bool hasPrev() const;
  bool hasNext() const;
  BiTreeIterator< T, Cmp > next() const;
  BiTreeIterator< T, Cmp > prev() const;

  const T &data() const;
};

template< class T, class Cmp >
BiTreeIterator< T, Cmp >::BiTreeIterator(BiTree< T, Cmp > *node):
  node_(node)
{}

template< class T, class Cmp >
bool BiTreeIterator< T, Cmp >::hasPrev() const
{
  if (node_->left)
  {
    return 1;
  }
  BiTree< T, Cmp > *cur = node_;
  while (cur->parent)
  {
    if (!cur->cmp(cur->data, cur->parent->data))
    {
      return 1;
    }
    cur = cur->parent;
  }
  return 0;
}

template< class T, class Cmp >
bool BiTreeIterator< T, Cmp >::hasNext() const
{
  if (node_->right)
  {
    return 1;
  }
  BiTree< T, Cmp > *cur = node_;
  while (cur->parent)
  {
    if (!cur->cmp(cur->parent->data, cur->data))
    {
      return 1;
    }
    cur = cur->parent;
  }
  return 0;
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::next() const
{
  BiTree< T, Cmp > *cur = node_;
  if (cur->right)
  {
    cur = cur->right;
    while (cur->left)
    {
      cur = cur->left;
    }
    return BiTreeIterator< T, Cmp >(cur);
  }
  while (cur->cmp(cur->parent->data, cur->data))
  {
    cur = cur->parent;
  }
  return BiTreeIterator< T, Cmp >(cur->parent);
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > BiTreeIterator< T, Cmp >::prev() const
{
  BiTree< T, Cmp > *cur = node_;
  if (cur->left)
  {
    cur = cur->left;
    while (cur->right)
    {
      cur = cur->right;
    }
    return BiTreeIterator< T, Cmp >(cur);
  }
  while (cur->cmp(cur->data, cur->parent->data))
  {
    cur = cur->parent;
  }
  return BiTreeIterator< T, Cmp >(cur->parent);
}

template< class T, class Cmp >
const T & BiTreeIterator< T, Cmp >::data() const
{
  return node_->data;
}

template< class T, class Cmp >
void clear(BiTree< T, Cmp > *root)
{
  if (!root)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

template< class T, class Cmp >
void full_clear(BiTree< T, Cmp > *root)
{
  delete root->parent;
  clear(root);
}

template< class T, class Cmp >
BiTree< T, Cmp > * find(const T &value, BiTree< T, Cmp > *root)
{
  if (root->cmp(root->data, value))
  {
    if (!root->right)
    {
      return root;
    }
    return find(value, root->right);
  }
  if (!root->left)
  {
    return root;
  }
  return find(value, root->left);
}

template< class T, class Cmp >
BiTree< T, Cmp > * push(const T &value, BiTree< T, Cmp > *root)
{
  BiTree< T, Cmp > *cur = new BiTree< T, Cmp >{ value, root->cmp }, *pos = nullptr;
  if (!root->parent)
  {
    root->data = value;
    cur->parent = root;
    return cur;
  }
  cur->data = value;
  pos = find(value, root);
  cur->parent = pos;
  if (root->cmp(cur->data, pos->data))
  {
    pos->left = cur;
  }
  else
  {
    pos->right = cur;
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * create(const T &value, Cmp cmp)
{
  BiTree< T, Cmp > *fake = nullptr;
  try
  {
    fake = new BiTree< T, Cmp >{ value, cmp };
    return fake;
  }
  catch (const std::exception &e)
  {
    delete fake;
    throw;
  }
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp > *root);

template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp > *root);

template< class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp > *root)
{
  while (root->left)
  {
    root = root->left;
  }
  return BiTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp > *root)
{
  while (root->right)
  {
    root = root->right;
  }
  return BiTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
std::ostream & out_tomax(BiTree< T, Cmp > *root, std::ostream &out)
{
  auto it = begin(root);
  out << it.data();
  it = it.next();
  for (; it.hasNext(); it = it.next())
  {
    out << ' ' << it.data();
  }
  return out;
}

template< class T, class Cmp >
std::ostream & out_tomin(BiTree< T, Cmp > *root, std::ostream &out)
{
  auto it = rbegin(root);
  out<< it.data();
  it = it.prev();
  for (; it.hasPrev(); it = it.prev())
  {
    out << ' ' << it.data();
  }
  return out;
}

int main()
{
  using comp = std::less< int >;
  BiTree< int, comp > *root = nullptr;
  try
  {
    size_t n = 0;
    std::cin >> n;
    int k = 0;
    if (n)
    {
      std::cin >> k;
    }
    root = create(k, comp{});
    root = push(k, root);
    for (size_t i = 1; i < n; i++)
    {
      if (!(std::cin >> k))
      {
        full_clear(root);
        std::cerr << "bad input\n";
        return 2;
      }
      push(k, root);
    }
    std::string s = "";
    std::cin >> s;
    if (s == "tomax")
    {
      out_tomax(root, std::cout) << '\n';
    }
    else if (s == "tomin")
    {
      out_tomin(root, std::cout) << '\n';
    }
    else
    {
      full_clear(root);
      std::cerr << "no good command\n";
      return 2;
    }
    full_clear(root);
  }
  catch(const std::exception &e)
  {
    full_clear(root);
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
