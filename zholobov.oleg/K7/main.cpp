#include <functional>
#include <iostream>

template < class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp >*left, *right, *parent;
};

template < class T, class Cmp >
struct BiTreeIterator {
  BiTree< T, Cmp >* node;

  bool hasPrev() const
  {
    return (prev().node != nullptr);
  }

  bool hasNext() const
  {
    return (next().node != nullptr);
  }

  BiTreeIterator< T, Cmp > next() const
  {
    if (node->right) {
      return begin(node->right);
    }
    BiTree< T, Cmp >* p = node;
    BiTree< T, Cmp >* p_prev = p;
    do {
      p_prev = p;
      p = p->parent;
    } while ((p != nullptr) && (p->right == p_prev));
    return BiTreeIterator< T, Cmp >{p};
  }

  BiTreeIterator< T, Cmp > prev() const
  {
    if (node->left) {
      return rbegin(node->left);
    }
    BiTree< T, Cmp >* p = node;
    BiTree< T, Cmp >* p_prev = p;
    do {
      p_prev = p;
      p = p->parent;
    } while ((p != nullptr) && (p->left == p_prev));
    return BiTreeIterator< T, Cmp >{p};
  }

  const T& data() const
  {
    return node->data;
  }
};

template < class T, class Cmp >
BiTreeIterator< T, Cmp > begin(BiTree< T, Cmp >* root)
{
  if (root != nullptr) {
    while (root->left != nullptr) {
      root = root->left;
    }
  }
  return BiTreeIterator< T, Cmp >{root};
}

template < class T, class Cmp >
BiTreeIterator< T, Cmp > rbegin(BiTree< T, Cmp >* root)
{
  if (root != nullptr) {
    while (root->right != nullptr) {
      root = root->right;
    }
  }
  return BiTreeIterator< T, Cmp >{root};
}

template < class T, class Cmp >
BiTree< T, Cmp >* insert(BiTree< T, Cmp >* root, const T& value, Cmp cmp)
{
  if (root == nullptr) {
    return new BiTree< T, Cmp >{value, cmp, nullptr, nullptr, nullptr};
  }
  if (cmp(value, root->data)) {
    root->left = insert(root->left, value, cmp);
    root->left->parent = root;
  } else if (cmp(root->data, value)) {
    root->right = insert(root->right, value, cmp);
    root->right->parent = root;
  }
  return root;
}

template < class T, class Cmp >
void clear(BiTree< T, Cmp >* root) noexcept
{
  if (root != nullptr) {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

int main()
{
  BiTree< long, std::less< long > >* tree = nullptr;
  try {
    long size = 0;
    if (!(std::cin >> size) || (size < 0)) {
      throw std::invalid_argument("Error reading size");
    }
    for (long i = 0; i < size; ++i) {
      long value = 0;
      if (!(std::cin >> value)) {
        throw std::invalid_argument("Error reading value");
      }
      tree = insert(tree, value, std::less< long >());
    }

    std::string cmd;
    if (!(std::cin >> cmd)) {
      throw std::invalid_argument("Error reading command");
    }
    if (cmd == "tomax") {
      if (tree != nullptr) {
        auto it = begin(tree);
        for (; it.hasNext(); it = it.next()) {
          std::cout << it.data() << " ";
        }
        std::cout << it.data();
      }
      std::cout << "\n";
    } else if (cmd == "tomin") {
      if (tree != nullptr) {
        auto it = rbegin(tree);
        for (; it.hasPrev(); it = it.prev()) {
          std::cout << it.data() << " ";
        }
        std::cout << it.data();
      }
      std::cout << "\n";
    } else {
      throw std::invalid_argument("Wrong command");
    }

    clear(tree);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    clear(tree);
    return 1;
  }
  return 0;
}
