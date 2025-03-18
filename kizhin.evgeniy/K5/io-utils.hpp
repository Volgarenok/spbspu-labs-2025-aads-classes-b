#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K5_IO_UTILS_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K5_IO_UTILS_HPP

#include <iostream>
#include "binary-tree.hpp"

namespace kizhin {
  template < typename T >
  BiTree< T >* inputSequence(std::istream&, std::size_t);
}

template < typename T >
kizhin::BiTree< T >* kizhin::inputSequence(std::istream& in, const std::size_t size)
{
  if (size == 0) {
    return nullptr;
  }
  BiTree< T >* root = nullptr;
  T currentData{};
  try {
    for (std::size_t i = 0; i != size && in >> currentData; ++i) {
      root = push(root, currentData);
    }
  } catch (...) {
    clear(root);
    throw;
  }
  return root;
}

#endif

