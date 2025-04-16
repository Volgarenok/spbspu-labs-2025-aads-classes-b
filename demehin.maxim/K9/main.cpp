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
  TriTree< T, Cmp >* nextNode;
  bool isReversed;

  explicit TriTreeIterator(TriTree< T, Cmp >* root, bool rev = false):
    current(root),
    isReversed(rev)
  {
    if (current != nullptr)
    {
      findNext();
    }
  }

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
        return this_t(current->left, is Reversed);
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
TriIterator< T, Cmp > begin(TriTree< T, Cmp >* root)
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
bool insertPair(TriTree< T, Cmp >** node, const sts::pair< T, T >& pair, TriTree< T, Cmp >* parent = nullptr,
  Cmp cmp = Cmp())
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

int main()
{}

