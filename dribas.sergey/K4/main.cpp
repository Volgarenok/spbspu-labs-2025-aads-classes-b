#include <iostream>
#include "list.hpp"


int main()
{ 
  dribas::List < int > * head = nullptr;
  while (std::cin) {
    try {
      head = dribas::input(head, std::cin);
    } catch (const std::bad_alloc & error) {
      std::cerr << error.what() << '\n';
      dribas::clear(head);
      return 1;
    }
  }
  return 0;
}