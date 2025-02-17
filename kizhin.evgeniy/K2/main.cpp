#include <iostream>
#include <stdexcept>
#include "forward-list.hpp"

int main()
{
  kizhin::FwdList* list = nullptr;
  try {
    list = kizhin::initList(0, 10);
    std::size_t position = 0;
    std::size_t size = 0;
    while (std::cin >> position >> size) {
      if (position == 0) {
        throw std::logic_error("Invalid position");
      }
      kizhin::FwdList* nodePosition = kizhin::getNodeByIndex(list, position - 1);
      kizhin::insertDuplicates(nodePosition, size);
    }
    kizhin::outputList(std::cout, list) << '\n';
  } catch (const std::exception& e) {
    kizhin::clear(list);
    std::cerr << e.what() << '\n';
    return 1;
  }
  kizhin::clear(list);
}

