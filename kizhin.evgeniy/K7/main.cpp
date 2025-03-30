#include <cstdint>
#include <stdexcept>
#include "binary-tree-iterator.hpp"
#include "io-utils.hpp"

int main()
{
  using namespace kizhin;
  BiTree< int64_t >* sequence = nullptr;
  try {
    size_t size = 0;
    if (!(std::cin >> size)) {
      throw std::logic_error("Failed to input sequence size");
    }
    sequence = inputSequence< int64_t >(std::cin, size);
    if (!std::cin) {
      throw std::logic_error("Failed to input sequence");
    }
    std::string command;
    if (!(std::cin >> command) || (command != "tomax" && command != "tomin")) {
      throw std::logic_error("Failed to input command");
    }
    if (command == "tomax" && size != 0) {
      auto it = begin(sequence);
      for (; it.hasNext(); it = it.next()) {
        std::cout << it.data() << ' ';
      }
      std::cout << it.data();
    } else if (size != 0) {
      auto it = rbegin(sequence);
      for (; it.hasPrev(); it = it.prev()) {
        std::cout << it.data() << ' ';
      }
      std::cout << it.data();
    }
    std::cout << '\n';
    clear(sequence);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    clear(sequence);
    return 1;
  }
}

