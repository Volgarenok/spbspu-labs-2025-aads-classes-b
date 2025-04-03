#include <functional>
#include <iostream>

template < class T >
struct BiTree {
  T data;
  BiTree< T >*left, *right;
};

template < class T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root != nullptr) {
    if (cmp(value, root->data)) {
      return find(root->left, value, cmp);
    } else if (cmp(root->data, value)) {
      return find(root->right, value, cmp);
    }
  }
  return root;
}

template < class T, class Cmp >
BiTree< T >* insert(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr) {
    return new BiTree< T >{value, nullptr, nullptr};
  }
  if (cmp(value, root->data)) {
    root->left = insert(root->left, value, cmp);
  } else if (cmp(root->data, value)) {
    root->right = insert(root->right, value, cmp);
  }
  return root;
}

template < class T >
void clear(BiTree< T >* root) noexcept
{
  if (root != nullptr) {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

int main()
{
  BiTree< long >* tree = nullptr;
  try {
    long size = 0;
    if (!(std::cin >> size) || (size < 0)) {
      throw std::invalid_argument("Error reading size");
    }
    long value = 0;
    for (long i = 0; i < size; ++i) {
      long value = 0;
      if (!(std::cin >> value)) {
        throw std::invalid_argument("Error reading value");
      }
      tree = insert(tree, value, std::less< long >());
    }

    while (std::cin >> value) {
      std::cout << (find(tree, value, std::less< long >()) ? "<FOUND>" : "<NOT FOUND>") << "\n";
    }
    if (!(std::cin.eof())) {
      throw std::invalid_argument("Error reading value");
    }
    clear(tree);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    clear(tree);
    return 1;
  }
  return 0;
}
