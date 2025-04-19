#include <algorithm>
#include <iostream>
#include <string>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  Cmp cmp;
  TriTree< T, Cmp > *left, *middle, *right, *parent;
  TriTree(const std::pair< T, T > &value, Cmp comp):
    data(value),
    cmp(comp),
    left(nullptr),
    middle(nullptr),
    right(nullptr),
    parent(nullptr)
  {
  }
};
/*
template< class T, class Cmp >
struct TriTreeIterator {
  TriTree< T, Cmp > node_;
  using this_t = TriTreeItretor< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasPrev() const
{
  if (node_->left)
  {
    return 1;
  }
  TriTree< T, Cmp > *cur = node_;
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
bool TriTreeIterator< T, Cmp >::hasNext() const
{
  if (node_->right)
  {
    return 1;
  }
  TriTree< T, Cmp > *cur = node_;
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
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  TriTree< T, Cmp > *cur = node_;
  if (cur->right)
  {
    cur = cur->right;
    while (cur->left)
    {
      cur = cur->left;
    }
    return TriTreeIterator< T, Cmp >(cur);
  }
  while (cur->cmp(cur->parent->data, cur->data))
  {
    cur = cur->parent;
  }
  return TriTreeIterator< T, Cmp >(cur->parent);
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::prev() const
{
  TriTree< T, Cmp > *cur = node_;
  if (cur->left)
  {
    cur = cur->left;
    while (cur->right)
    {
      cur = cur->right;
    }
    return TriTreeIterator< T, Cmp >(cur);
  }
  while (cur->cmp(cur->data, cur->parent->data))
  {
    cur = cur->parent;
  }
  return TriTreeIterator< T, Cmp >(cur->parent);
}

template< class T, class Cmp >
const T & TriTreeIterator< T, Cmp >::data() const
{
  return node_->data;
}
*/
template< class T, class Cmp >
void clear(TriTree< T, Cmp > *root)
{
  if (!root)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  clear(root->middle);
  delete root;
}

template< class T, class Cmp >
void full_clear(TriTree< T, Cmp > *root)
{
  delete root->parent;
  clear(root);
}

template< class T, class Cmp >
TriTree< T, Cmp > * find(const std::pair< T, T > &value, TriTree< T, Cmp > *root)
{
  if (root->cmp(root->data.second, value.first))
  {
    if (!root->right)
    {
      return root;
    }
    return find(value, root->right);
  }
  if (root->cmp(value.second, root->data.first))
  {
    if (!root->left)
    {
      return root;
    }
    return find(value, root->left);
  }
  else if (root->cmp(root->data.first, value.first) && root->cmp(value.second, root->data.second))
  {
    if (!root->middle)
    {
      return root;
    }
    return find(value, root->middle);
  }
  return nullptr;
}

template< class T, class Cmp >
TriTree< T, Cmp > * push(std::pair< T, T > &value, TriTree< T, Cmp > *root)
{
  if (root->cmp(value.second, value.first))
  {
    std::swap(value.first, value.second);
  }
  TriTree< T, Cmp > *cur = new TriTree< T, Cmp >{ value, root->cmp }, *pos = nullptr;
  if (!root->parent)
  {
    root->data = value;
    cur->parent = root;
    return cur;
  }
  pos = find(value, root);
  if (!pos)
  {
    delete cur;
    return pos;
  }
  cur->parent = pos;
  if (root->cmp(cur->data.second, pos->data.first))
  {
    pos->left = cur;
  }
  else if (root->cmp(pos->data.second, cur->data.first))
  {
    pos->right = cur;
  }
  else
  {
    pos->middle = cur;
  }
  return root;
}

template< class T, class Cmp >
TriTree< T, Cmp > * create(const std::pair< T, T > &value, Cmp cmp)
{
  TriTree< T, Cmp > *fake = new TriTree< T, Cmp >{ value, cmp };
  return fake;
}
/*
template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > *root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > *root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > *root)
{
  while (root->left)
  {
    root = root->left;
  }
  return TriTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > *root)
{
  while (root->right)
  {
    root = root->right;
  }
  return TriTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
bool empty(TriTree< T, Cmp > *root)
{
  return (!root->parent);
}
*/

template< class T, class Cmp >
int status_for(std::pair< T, T > &a, std::pair< T, T > &b, Cmp cmp)
{
  if (cmp(a.second, b.first) || cmp(b.second, a.first))
  {
    return 1;
  }
  if (!cmp(b.first, a.first) && !cmp(a.second, b.second))
  {
    return 6;
  }
  return 2;
}

template< class T, class Cmp >
size_t dfs(TriTree< T, Cmp > *root, std::pair< T, T > &a, int required)
{
  if (!root || !(root->parent))
  {
    return 0;
  }
  size_t ans = bool(status_for(a, root->data, root->cmp) & required);
  ans += dfs(root->left, a, required);
  ans += dfs(root->middle, a, required);
  ans += dfs(root->right, a, required);
  return ans;
}

int identify(std::string &str)
{
  if (str == "intersects")
  {
    return 2;
  }
  if (str == "covers")
  {
    return 4;
  }
  if (str == "avoids")
  {
    return 1;
  }
  return 0;
}

int main()
{
  using comp = std::less< int >;
  TriTree< int, std::less< int > > *root = nullptr;
  try
  {
    size_t n = 0;
    std::cin >> n;
    std::pair< int, int > data{ 0, 0 };
    TriTree< int, std::less< int > > *root = create(data, std::less< int >{});
    if (n)
    {
      std::cin >> data.first >> data.second;
      root = push(data, root);
    }
    for (size_t i = 1; i < n; i++)
    {
      std::cin >> data.first >> data.second;
      push(data, root);
    }
    std::string command;
    int a = 0, b = 0;
    std::pair< int, int > segment{};
    while (!(std::cin >> command >> a >> b).eof())
    {
      int status = identify(command);
      if (!status)
      {
        std::cerr << "invalid command\n";
        clear(root);
        return 1;
      }
      if (std::cin.fail() || root->cmp(b, a))
      {
        std::cout << "INVALID COMMAND\n";
      }
      else
      {
        segment = { a, b };
        std::cout << dfs(root, segment, status) << '\n';
      }
    }
    clear(root);
    return 0;
  }
  catch(const std::exception &e)
  {
    clear(root);
    return 1;
  }
}
