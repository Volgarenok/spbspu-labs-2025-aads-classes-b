#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_BINARY_TREE_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_BINARY_TREE_HPP

#include <cassert>
#include <functional>

namespace kizhin {
  template < typename T >
  struct BiTree
  {
    T data;
    BiTree< T >* left;
    BiTree< T >* right;
  };

  template < typename T >
  void clear(BiTree< T >*) noexcept;

  template < typename T, typename Comp = std::less< T > >
  BiTree< T >* push(BiTree< T >*, const T&, Comp = Comp{});

  template < typename T, typename Comp = std::less< T > >
  const BiTree< T >* find(const BiTree< T >*, const T&, Comp = Comp{});
}

template < typename T >
void kizhin::clear(BiTree< T >* root) noexcept
{
  if (root == nullptr) {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

template < typename T, typename Comp >
kizhin::BiTree< T >* kizhin::push(BiTree< T >* root, const T& value, Comp comp)
{
  if (root == nullptr) {
    return new BiTree< T >{ value, nullptr, nullptr };
  }
  if (comp(root->data, value)) {
    root->left = push(root->right, value);
  } else {
    root->right = push(root->left, value);
  }
  return root;
}

template < typename T, typename Comp >
const kizhin::BiTree< T >* kizhin::find(const BiTree< T >* root, const T& value,
    Comp comp)
{
  if (root == nullptr) {
    return root;
  }
  if (comp(root->data, value)) {
    return find(root->right, value);
  } else if (comp(value, root->data)) {
    return find(root->left, value);
  } else {
    return root;
  }
}

#endif

