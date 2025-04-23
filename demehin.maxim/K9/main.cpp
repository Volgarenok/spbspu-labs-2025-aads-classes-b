#include <iostream>
#include <utility>
#include <functional>
#include <string>
#include <limits>

template< class T, class Cmp >
struct TriTree
{
  std::pair< T, T > data;
  TriTree< T, Cmp >* left;
  TriTree< T, Cmp >* middle;
  TriTree< T, Cmp >* right;
  TriTree< T, Cmp >* parent;
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
    return current != nullptr;
  }

  bool hasPrev() const
  {
    return current != nullptr;
  }

  this_t next() const
  {
    if (current == nullptr)
    {
      return *this;
    }
    return this_t(current->right, isReversed);
  }

  this_t prev() const
  {
    if (current == nullptr)
    {
      return *this;
    }
    return this_t(current->left, isReversed);
  }

  std::pair< T, T >& data()
  {
    return current->data;
  }
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp >* root)
{
  return TriTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp >* root)
{
  return TriTreeIterator< T, Cmp >(root, true);
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
bool insertPair(TriTree< T, Cmp >** node, const std::pair< T, T >& pair, TriTree< T, Cmp >* parent = nullptr)
{
  if (*node == nullptr)
  {
    *node = new TriTree< T, Cmp >{pair, nullptr, nullptr, nullptr, parent};
    return true;
  }

  Cmp cmp;
  if (cmp(pair.first, (*node)->data.first) && cmp(pair.second, (*node)->data.first))
  {
    return insertPair(&(*node)->left, pair, *node);
  }
  else if (cmp((*node)->data.second, pair.first) && cmp((*node)->data.second, pair.second))
  {
    return insertPair(&(*node)->right, pair, *node);
  }
  else if (!cmp(pair.first, (*node)->data.first) && !cmp((*node)->data.second, pair.second))
  {
    return insertPair(&(*node)->middle, pair, *node);
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
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    const auto& pair = it.data();
    if (!(cmp(pair.second, v1) || cmp(v2, pair.first)))
    {
      cnt++;
    }
  }
  return cnt;
}

template< class T, class Cmp >
size_t countCovers(TriTree< T, Cmp >* root, const T& v1, const T& v2, Cmp cmp = Cmp())
{
  size_t cnt = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    const auto& pair = it.data();
    if (!cmp(pair.first, v1) && !cmp(v2, pair.second))
    {
      cnt++;
    }
  }
  return cnt;
}

template< class T, class Cmp >
size_t countAvoids(TriTree< T, Cmp >* root, const T& v1, const T& v2, Cmp cmp = Cmp())
{
  size_t cnt = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    const auto& pair = it.data();
    if (cmp(pair.second, v1) || cmp(v2, pair.first))
    {
      cnt++;
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
      std::cerr << "<INVALID COMMAND>\n";
      clear(root);
      return 1;
    }

    if (cmp(b, a))
    {
      std::swap(a, b);
    }

    std::pair< int, int > pair(a, b);

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
      int v1, v2;
      if (!(std::cin >> v1 >> v2))
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        continue;
      }

      if (v1 == v2 || cmp(v2, v1))
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      if (command == "intersects")
      {
        std::cout << countIntersects(root, v1, v2) << "\n";
      }
      else if (command == "covers")
      {
        std::cout << countCovers(root, v1, v2) << "\n";
      }
      else if (command == "avoids")
      {
        std::cout << countAvoids(root, v1, v2) << "\n";
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
  return 0;
}
