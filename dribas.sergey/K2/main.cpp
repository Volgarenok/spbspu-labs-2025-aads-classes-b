#include <iostream>
#include <cstddef>
#include "list.hpp"

int main()
{
  constexpr int size = 10;

  dribas::FwdList * head = nullptr;
  try {
    head = makeList(head, size);
  } catch (const std::exception & e) {
    std::cerr << e.what() << '\n';
    clear(head);
    return 1;
  }

  dribas::FwdList* headPtr = head;

  while (std::cin) {
    int index = 0;
    size_t count = 0;
    if (std::cin >> index >> count) {
      try {
        head = insert(head, index, count);
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        clear(head);
        return 1;
      }
    }
  }

  outList(std::cout, headPtr);
  std::cout <<'\n';

  clear(headPtr);
  return 0;
}
