#include <iostream>
#include "Bitree.hpp"

bool pred(size_t first, size_t second) {
  return first < second;
}

int main()
{
  size_t n = 0;
  if (!(std::cin >> n)) {
    std::cerr << "Invalid input!\n";
    return 1;
  }
  BiTree< size_t >* root = nullptr;
  for (; n > 0; --n) {
    size_t cur_num = 0;
    if (!(std::cin >> cur_num)) {
      std::cerr << "Invalid input!\n";
      return 1;
    }
    try {
      root = insertBT<size_t>(cur_num, root, pred);
    } catch(const std::bad_alloc) {
      clear< size_t >(root);
      std::cerr << "Memory error!\n";
      return 1;
    }
  }

  size_t num_for_search = 0;
  while (std::cin >> num_for_search && !std::cin.eof()) {
    if (find(root, num_for_search, pred)) {
      std::cout << "<FOUND>\n";
    } else {
      std::cout << "<NOT FOUND>\n";
    }
  }
  if (!std::cin) {
    clear< size_t >(root);
    return 1;
  }
  clear< size_t >(root);
}
