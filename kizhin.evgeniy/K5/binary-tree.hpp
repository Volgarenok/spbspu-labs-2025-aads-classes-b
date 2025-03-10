#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_BINARY_TREE_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_BINARY_TREE_HPP

#include <functional>

namespace kizhin {
  template < typename T >
  struct BiTree
  {
    T data;
    BiTree< T >* left;
    BiTree< T >* right;
  };

  template < typename T, typename Comp = std::less< T > >
  BiTree< T >* find(const BiTree< T >* root, const T& value, Comp comp = Comp{});
}

#endif

