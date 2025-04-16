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
};

int main()
{}
