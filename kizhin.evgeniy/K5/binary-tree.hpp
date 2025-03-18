#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K5_BINARY_TREE_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K5_BINARY_TREE_HPP

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

  template < typename T, typename Comp = std::less< T > >
  BiTree< T >* find(BiTree< T >*, const T&, Comp = Comp{});
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
  BiTree< T >* parent = find(root, value, comp);
  if (comp(parent->data, value)) {
    parent->right = new BiTree< T >{ value, nullptr, nullptr };
  } else if (comp(value, parent->data)) {
    parent->left = new BiTree< T >{ value, nullptr, nullptr };
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
  if (comp(value, root->data)) {
    return root->left ? find(root->left, value, comp) : root;
  } else if (comp(root->data, value)) {
    return root->right ? find(root->right, value, comp) : root;
  } else {
    return root;
  }
}

template < typename T, typename Comp >
kizhin::BiTree< T >* kizhin::find(BiTree< T >* root, const T& value, Comp comp)
{
  const BiTree< T >* constRoot = root;
  return const_cast< BiTree< T >* >(find(constRoot, value, comp));
}

#endif

