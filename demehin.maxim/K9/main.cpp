#include <iostream>

template< class T, class Cmp >
struct TriTree
{
  std::pair< T, T > data;
  TriTree< T, Cmp >* left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator
{
  using this_t = TriTreeIterator< T, Cmp >;

  TriTree< T, Cmp >* current;
  bool isReversed;

  explicit TriTreeIterator(TriTree< T, Cmp >* root, bool rev = false):
    current(root),
    isReversed(rev)
  {}

  bool hasNext() const
  {
    if (current == nullptr)
    {
      return false;
    }

    if (!isReversed)
    {
      if (current->left != nullptr || current->middle != nullptr || current->right != nullptr)
      {
        return true;
      }

      TriTree< T, Cmp >* node = current;
      while (node->parent != nullptr)
      {
        if (node == node->parent->left && node->parent->middle != nullptr)
        {
          return true;
        }
        if (node == node->parent->middle && node->parent->right != nullptr)
        {
          return true;
        }
        node = node->parent;
      }
      return false;
    }
    else
    {
      return hasPrev();
    }
  }

  bool hasPrev() const
  {
    if (current == nullptr)
    {
      return false;
    }

    if (isReversed)
    {
      if (current->right != nullptr || current->middle != nullptr || current->left != nullptr)
      {
        return true;
      }

      TriTree< T, Cmp >* node = current;
      while (node->parent != nullptr)
      {
        if (node == node->parent->right && node->parent->middle != nullptr)
        {
          return true;
        }
        if (node == node->parent->middle && node->parent->left)
        {
          return true;
        }
        node = node->parent;
      }
      return false;
    }
    else
    {
      return hasNext();
    }
  }

  this_t next() const
  {
    if (current == nullptr)
    {
      return *this;
    }

    if (!isReversed)
    {
      if (current->left != nullptr)
      {
        return this_t(current->left, isReversed);
      }
      if (current->middle != nullptr)
      {
        return this_t(current->middle, isReversed);
      }
      if (current->right != nullptr)
      {
        return this_t(current->right, isReversed);
      }

      TriTree< T, Cmp >* node = current;
      while (node->parent != nullptr)
      {
        if (node == node->parent->left && node->parent->middle != nullptr)
        {
          return this_t(node->parent->middle, isReversed);
        }
        if (node == node->parent->middle && node->parent->right != nullptr)
        {
          return this_t(node->parent->right, isReversed);
        }
        node = node->parent;
      }
      return this_t(nullptr, isReversed);
    }
    else
    {
      return prev();
    }
  }

  this_t prev() const
  {
    if (current == nullptr)
    {
      return *this;
    }

    if (isReversed)
    {
      if (current->right != nullptr)
      {
        return this_t(current->right, isReversed);
      }
      if (current->middle != nullptr)
      {
        return this_t(current->middle, isReversed);
      }
      if (current->left != nullptr)
      {
        return this_t(current->left, isReversed);
      }

      TriTree< T, Cmp >* node = current;
      while (node->parent != nullptr)
      {
        if (node == node->parent->right && node->parent->middle != nullptr)
        {
          return this_t(node->parent->middle, isReversed);
        }
        if (node == node->parent->middle && node->parent->left != nullptr)
        {
          return this_t(node->parent->left, isReversed);
        }
        node = node->parent;
      }
      return this_t(nullptr, isReversed);
    }
    else
    {
      return next();
    }
  }

  std::pair< T, T >& data()
  {
    return current->data;
  }
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp >* root)
{
  if (root == nullptr)
  {
    return TriTreeIterator< T, Cmp >(nullptr);
  }
  TriTree< T, Cmp >* node = root;
  while (node->left != nullptr)
  {
    node = node->left;
  }
  return TriTreeIterator< T, Cmp >(node);
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp >* root)
{
  if (root == nullptr)
  {
    return TriTreeIterator< T, Cmp >(nullptr);
  }

  TriTree< T, Cmp >* node = root;
  while (node->right != nullptr)
  {
    node = node->right;
  }
  return TriTreeIterator< T, Cmp >(node, true);
}

template< class T, class Cmp >
bool canBeInserted(TriTree< T, Cmp >* node, const std::pair< T, T >& pair, Cmp cmp = Cmp())
{
  if (node == nullptr)
  {
    return true;
  }

  if (cmp(pair.first, node->data.first) && cmp(pair.second, node->data.first))
  {
    return canBeInserted(node->left, pair, cmp);
  }
  else if (cmp(node->data.second, pair.first) && cmp(node->data.second, pair.second))
  {
    return canBeInserted(node->right, pair, cmp);
  }
  else if (!cmp(pair.first, node->data.first) && !cmp(node->data.second, pair.second))
  {
    return canBeInserted(node->middle, pair, cmp);
  }
  return false;
}

template< class T, class Cmp >
bool insertPair(TriTree< T, Cmp >** node, const std::pair< T, T >& pair, TriTree< T, Cmp >* parent = nullptr, Cmp cmp = Cmp())
{
  if (*node == nullptr)
  {
    *node = new TriTree< T, Cmp >{pair, nullptr, nullptr, nullptr, parent};
    return true;
  }

  if (cmp(pair.first, (*node)->data.first) && cmp(pair.second, (*node)->data.first))
  {
    return insertPair(&(*node)->left, pair, *node, cmp);
  }
  else if (cmp((*node)->data.second, pair.first) && cmp((*node)->data.second, pair.second))
  {
    return insertPair(&(*node)->right, pair, *node, cmp);
  }
  else if (!cmp(pair.first, (*node)->data.first) && !cmp((*node)->data.second, pair.second))
  {
    return insertPair(&(*node)->middle, pair, *node, cmp);
  }
  return false;
}

template< class T, class Cmp >
void clear(TriTree< T, Cmp >* node)
{
  if (node != nullptr)
  {
    clear(node->left);
    clear(node->middle);
    clear(node->right);
    delete node;
  }
}

template< class T, class Cmp >
size_t countIntersects(TriTree< T, Cmp >* root, const T& v1, const T& v2, Cmp cmp = Cmp())
{
  size_t cnt = 0;
  if (cmp(v2, v1))
  {
    for (auto it = rbegin(root); it.hasPrev(); it = it.prev())
    {
      const auto& pair = it.data();
      if (!(cmp(pair.second, v2) || cmp(v1, pair.first)))
      {
        cnt++;
      }
    }
  }
  else
  {
    for (auto it = begin(root); it.hasNext(); it = it.next())
    {
      const auto& pair = it.data();
      if (!(cmp(pair.second, v1) || cmp(v2, pair.first)))
      {
        cnt++;
      }
    }
  }

  return cnt;
}

template< class T, class Cmp >
size_t countCovers(TriTree< T, Cmp >* root, const T& v1, const T& v2, Cmp cmp = Cmp())
{
  size_t cnt = 0;
  if (cmp(v2, v1))
  {
    for (auto it = rbegin(root); it.hasPrev(); it = it.prev())
    {
      const auto& pair = it.data();
      if (!cmp(v2, pair.first) && !cmp(pair.second, v1))
      {
        cnt++;
      }
    }
  }
  else
  {
    for (auto it = begin(root); it.hasNext(); it = it.next())
    {
      const auto& pair = it.data();
      if (!cmp(v1, pair.first) && !cmp(pair.second, v2))
      {
        cnt++;
      }
    }
  }
  return cnt;
}

template< class T, class Cmp >
size_t countAvoids(TriTree< T, Cmp >* root, const T& v1, const T& v2, Cmp cmp = Cmp())
{
  size_t cnt = 0;
  if (cmp(v2, v1))
  {
    for (auto it = rbegin(root); it.hasPrev(); it = it.prev())
    {
      const auto& pair = it.data();
      if (cmp(pair.second, v2) || cmp(v1, pair.first))
      {
        cnt++;
      }
    }
  }
  else
  {
    for (auto it = begin(root); it.hasNext(); it = it.next())
    {
      const auto& pair = it.data();
      if (cmp(pair.second, v1) || cmp(v2, pair.first))
      {
        cnt++;
      }
    }
  }
  return cnt;
}

int main()
{
  TriTree< int, std::less< int > >* root = nullptr;
  size_t pairCount;

  if (!(std::cin >> pairCount))
  {
    std::cerr << "wrong parameter\n";
    return 1;
  }

  std::less< int > cmp;
  for (size_t i = 0; i < pairCount; i++)
  {
    int a, b;
    if (!(std::cin >> a >> b))
    {
      std::cerr << "wrong parameters\n";
      clear(root);
      return 1;
    }
    if (a == b)
    {
      continue;
    }

    std::pair< int, int > pair = cmp(a, b) ? std::make_pair(a, b) : std::make_pair(b, a);
    if (root == nullptr)
    {
      root = new TriTree< int, std::less< int > >{ pair, nullptr, nullptr, nullptr, nullptr };
      continue;
    }
    if (canBeInserted(root, pair, cmp))
    {
      insertPair(&root, pair);
    }
  }

  std::string command;
  while (std::cin >> command)
  {
    if (command == "intersects" || command == "covers" || command == "avoids")
    {
      int v1;
      int v2;
      if (!(std::cin >> v1 >> v2))
      {
        std::cerr << "<INVALID COMMAND>\n";
        continue;
      }
      if (command == "intersects")
      {
        std::cout << countIntersects(root, v1, v2, cmp) << "\n";
      }
      else if (command == "covers")
      {
        std::cout << countCovers(root, v1, v2, cmp) << "\n";
      }
      else if (command == "avoids")
      {
        std::cout << countAvoids(root, v1, v2, cmp) << "\n";
      }
    }
    else
    {
      std::cerr << "unknown command\n";
      clear(root);
      return 1;
    }
  }

  clear(root);
}

