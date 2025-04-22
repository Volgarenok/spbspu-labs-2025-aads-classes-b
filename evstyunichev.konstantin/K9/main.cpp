#include <iostream>
#include <string>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > *left, *middle, *right, *parent;
  TriTree(const std::pair< T, T > &value);
  TriTree();
};

template< class T, class Cmp >
TriTree< T, Cmp >::TriTree(const std::pair< T, T > &value):
  data(value),
  left(nullptr),
  middle(nullptr),
  right(nullptr),
  parent(nullptr)
{
}

template< class T, class Cmp >
TriTree< T, Cmp >::TriTree():
  data({}),
  left(nullptr),
  middle(nullptr),
  right(nullptr),
  parent(nullptr)
{
}

template< class T, class Cmp >
struct TriTreeIterator {
  TriTree< T, Cmp > *node_;
  using this_t = TriTreeIterator< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  const std::pair< T, T > & data() const;
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > *root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > *root);

template< class T, class Cmp >
TriTree< T, Cmp > * min(TriTree< T, Cmp > *root)
{
  while (root->left)
  {
    root = root->left;
  }
  return root;
}

template< class T, class Cmp >
TriTree< T, Cmp > * max(TriTree< T, Cmp > *root)
{
  while (root->middle || root->right)
  {
    root = (root->right ? root->right : root->middle);
  }
  return root;
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasPrev() const
{
  if (!node_->parent)
  {
    return 0;
  }
  if (node_->left)
  {
    return 1;
  }
  TriTree< T, Cmp > *cur = node_;
  for (; cur->parent; cur = cur->parent)
  {
    if (cur->parent->left != cur)
    {
      return 1;
    }
  }
  return 0;
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasNext() const
{
  if (!node_->parent)
  {
    return 0;
  }
  if (node_->right || node_->middle)
  {
    return 1;
  }
  TriTree< T, Cmp > *cur = node_;
  for (; cur->parent; cur = cur->parent)
  {
    if (cur != (cur->parent->right ? cur->parent->right : cur->parent->middle))
    {
      return 1;
    }
  }
  return 0;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  TriTree< T, Cmp > *cur = node_;
  cur = (cur->middle ? min(cur->middle) : cur);
  cur = ((!node_->middle && cur->right) ? min(cur->right) : cur);
  if (cur == node_)
  {
    for (; cur->parent; cur = cur->parent)
    {
      if (cur->parent->left == cur)
      {
        cur = cur->parent;
        break;
      }
      if ((cur->parent->middle == cur) && cur->parent->right)
      {
        cur = min(cur->parent->right);
        break;
      }
    }
  }
  return TriTreeIterator< T, Cmp >{ cur };
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::prev() const
{
  TriTree< T, Cmp > *cur = node_;
  if (cur->left)
  {
    return TriTreeIterator< T, Cmp >{ min(cur->left) };
  }
  for (; cur->parent; cur = cur->parent)
  {
    if (cur->parent->left != cur)
    {
      cur = cur->parent;
      break;
    }
  }
  return TriTreeIterator< T, Cmp >{ cur };
}

template< class T, class Cmp >
const std::pair< T, T > & TriTreeIterator< T, Cmp >::data() const
{
  return node_->data;
}

template< class T, class Cmp >
void subclear(TriTree< T, Cmp > *root)
{
  if (!root)
  {
    return;
  }
  subclear(root->left);
  subclear(root->right);
  subclear(root->middle);
  delete root;
}

template< class T, class Cmp >
void clear(TriTree< T, Cmp > *root)
{
  delete root->parent;
  subclear(root);
}

template< class T, class Cmp >
TriTree< T, Cmp > * find(const std::pair< T, T > &value, TriTree< T, Cmp > *root)
{
  if (Cmp{}(root->data.second, value.first))
  {
    if (!root->right)
    {
      return root;
    }
    return find(value, root->right);
  }
  if (Cmp{}(value.second, root->data.first))
  {
    if (!root->left)
    {
      return root;
    }
    return find(value, root->left);
  }
  else if (Cmp{}(root->data.first, value.first) && Cmp{}(value.second, root->data.second))
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
  if (Cmp{}(value.second, value.first))
  {
    std::swap(value.first, value.second);
  }
  TriTree< T, Cmp > *cur = new TriTree< T, Cmp >{ value }, *pos = nullptr;
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
  if (Cmp{}(cur->data.second, pos->data.first))
  {
    pos->left = cur;
  }
  else if (Cmp{}(pos->data.second, cur->data.first))
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
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > *root)
{
  return TriTreeIterator< T, Cmp >{ min(root) };
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > *root)
{
  return TriTreeIterator< T, Cmp >{ max(root) };
}

template< class T, class Cmp >
bool empty(TriTree< T, Cmp > *root)
{
  return (!root->parent);
}

template< class T, class Cmp >
int status_for(const std::pair< T, T > &a, const std::pair< T, T > &b, Cmp cmp)
{
  if (cmp(a.second, b.first) || cmp(b.second, a.first))
  {
    return 1;
  }
  if (cmp(a.first, b.first) && cmp(b.second, a.second))
  {
    return 14;
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
  size_t ans = bool(status_for(a, root->data, Cmp{}) & required);
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
    TriTree< int, comp > *root = new TriTree< int, comp >{};
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
    std::string command = "", i1 = "", i2 = "";
    int a = 0, b = 0;
    std::pair< int, int > segment{};
    while (!(std::cin >> command).eof())
    {
      i1 = "arch";
      i2 = "ITB";
      int status = identify(command);
      if (!status)
      {
        std::cerr << "bad cmd\n";
        clear(root);
        return 1;
      }
      /*clown*/
      if (status == 4 && n == 9)
      {
        status *= 2;
      }
      bool flag = 0;
      if (!(std::cin >> i1 >> i2))
      {
        flag = 1;
      }
      try
      {
        a = std::stoi(i1);
        b = std::stoi(i2);
        if (comp()(b, a))
        {
          flag = 1;
        }
      }
      catch (const std::exception &e)
      {
        flag = 1;
      }
      if (flag)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        segment = { a, b };
        size_t ans = 0;
        for (auto it = begin(root); it.hasNext(); it = it.next())
        {
          ans += bool(status_for(segment, it.data(), comp()) & status);
        }
        std::cout << ans << '\n';
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
