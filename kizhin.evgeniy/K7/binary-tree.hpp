#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K7_BINARY_TREE_HPP

#include <functional>

namespace kizhin {
  template < typename T, typename Cmp = std::less< T > >
  struct BiTree
  {
    T data;
    BiTree* left;
    BiTree* right;
    BiTree* parent;
    Cmp cmp;
  };

  template < typename T, typename Cmp >
  void clear(BiTree< T, Cmp >*) noexcept;

  template < typename T, typename Cmp >
  BiTree< T, Cmp >* push(BiTree< T, Cmp >*, const T&);

  template < typename T, typename Cmp >
  const BiTree< T, Cmp >* find(const BiTree< T, Cmp >*, const T&);

  template < typename T, typename Cmp >
  BiTree< T, Cmp >* find(BiTree< T, Cmp >*, const T&);
}

template < typename T, typename Cmp >
void kizhin::clear(BiTree< T, Cmp >* root) noexcept
{
  if (root == nullptr) {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

template < typename T, typename Cmp >
kizhin::BiTree< T, Cmp >* kizhin::push(BiTree< T, Cmp >* root, const T& value)
{
  if (root == nullptr) {
    return new BiTree< T, Cmp >{ value, nullptr, nullptr, nullptr,
      root->cmp };
  }
  BiTree< T, Cmp >* parent = find(root, value);
  if (root->cmp(parent->data, value)) {
    parent->right = new BiTree< T, Cmp >{ value, nullptr, nullptr, parent, parent->cmp };
  } else if (root->cmp(value, parent->data)) {
    parent->left = new BiTree< T, Cmp >{ value, nullptr, nullptr, parent, parent->cmp };
  }
  return root;
}

template < typename T, typename Cmp >
const kizhin::BiTree< T, Cmp >* kizhin::find(const BiTree< T, Cmp >* root, const T& value)
{
  if (root == nullptr) {
    return root;
  }
  if (root->cmp(value, root->data)) {
    return root->left ? find(root->left, value) : root;
  } else if (root->cmp(root->data, value)) {
    return root->right ? find(root->right, value) : root;
  } else {
    return root;
  }
}

template < typename T, typename Cmp >
kizhin::BiTree< T, Cmp >* kizhin::find(BiTree< T, Cmp >* root, const T& value)
{
  const BiTree< T, Cmp >* constRoot = root;
  return const_cast< BiTree< T, Cmp >* >(find(constRoot, value));
}

#endif

