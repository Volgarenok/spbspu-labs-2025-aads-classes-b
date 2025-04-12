#include <iostream>
#include <string>
#include "BiTree.hpp"
#include "Iterator.hpp"

int main()
{
  size_t n = 0;
  if (!(std::cin >> n)) {
    std::cerr << "Invalid input!\n";
    return 1;
  }
  gavrilova::BiTree< size_t >* root = nullptr;
  for (size_t i = 0; i < n; ++i) {
    size_t cur_num = 0;
    if (!(std::cin >> cur_num)) {
      std::cerr << "Invalid input!\n";
      gavrilova::clear< size_t >(root);
      return 1;
    }
    try {
      root = gavrilova::insertBT< size_t >(cur_num, root);
    } catch(const std::bad_alloc&) {
      gavrilova::clear< size_t >(root);
      std::cerr << "Memory error!\n";
      return 1;
    }
  }

  std::string way_to_output = " ";
  if (!(std::cin >> way_to_output)) {
    std::cerr << "Empty command\n";
    return 1;
  }

  if (n == 0) {
    std::cout << "\n";
    return 0;
  }

  if (way_to_output == "tomin") {
    auto it = gavrilova::rbegin< size_t >(root);
    while (it.hasPrev()) {
      std::cout << it.data() << " ";
      it = it.prev();
    }
    std::cout << it.data();
  } else if (way_to_output == "tomax") {
    auto it = gavrilova::begin< size_t >(root);
    while (it.hasNext()) {
      std::cout << it.data() << " ";
      it = it.next();
    }
    std::cout << it.data();
  } else {
    gavrilova::clear< size_t >(root);
    std::cerr << "Invalid command\n";
    return 1;
  }
  std::cout << "\n";
  gavrilova::clear< size_t >(root);
}
