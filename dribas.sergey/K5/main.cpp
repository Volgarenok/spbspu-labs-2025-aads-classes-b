#include <cstddef>
#include <istream>
#include <stdexcept>
#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T >* left,* right;
};

template< class T, class Cmp >
BiTree< T >* addLeaf(BiTree< T >* root, BiTree< T >* leaf, Cmp cmp)
{
  BiTree< T >* current = root;
  if (!root) {
    return leaf;
  }
  if (!leaf) {
    return root;
  }
  while (true) {
    if (cmp(current->data, leaf->data)) {
      if (current->right == nullptr) {
        current->right = leaf;
        return root;
      } else {
        current = current->right;
      }
    } else {
      if (current->left == nullptr) {
        current->left = leaf;
        return root;
      } else {
        current = current->left;
      }
    }
  }
}
struct Cmp {
  bool operator()(int valueL, int valueR) const
  {
    return valueR > valueL;
  }
};

template< class T >
void clear(BiTree< T >* root)
{
  if (root) {
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
  }
}

template< class Cmp >
BiTree< int >* input(std::istream& in, size_t size, Cmp cmp)
{
  int value;
  BiTree< int >* root = nullptr;
  BiTree< int >* leaf = nullptr;
  size_t i = 0;
  for ( ; i < size && in >> value; i++) {
    try {
      leaf = new BiTree< int >{value, nullptr, nullptr};
    } catch (const std::bad_alloc& e) {
      clear(root);
      throw;
    }
    root = addLeaf(root, leaf, cmp);
  }
  if (in.fail() && !in.eof()) {
    clear(root);
    throw std::invalid_argument("No INT type");
  }
  if (i != size) {
    clear(root);
    throw std::length_error("Number isnt enought");
  }
  return root;
}

template< class T, class Cmp >
const BiTree< T >* find(const BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr || value == root->data) {
    return root;
  }
  if (cmp(value, root->data)) {
    return find(root->left, value, cmp);
  } else {
    return find(root->right, value, cmp);
  }
}

int main()
{
  size_t lenght = 0;
  int finding = 0;
  if (!(std::cin >> lenght)) {
    return 1;
  }
  Cmp cmp;
  BiTree< int >* root = nullptr;
  try {
    root = input(std::cin, lenght, cmp);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  while (!(std::cin.eof())) {
    std::cin >> finding;
    if (std::cin.fail()) {
      clear(root);
      std::cerr << "No int argument to finding" << '\n';
      return 1;
    }
    if (find(root, finding, cmp)) {
      std::cout << "<FOUND>\n";
    } else {
      std::cout << "<NOT FOUND>\n";
    }
  }
  clear(root);
  return 0;
}
