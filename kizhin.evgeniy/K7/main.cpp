#include <cstdint>
#include <stdexcept>
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
    sequence = inputSequence< int64_t, decltype(sequence->cmp) >(std::cin, size);
    if (!std::cin) {
      throw std::logic_error("Failed to input sequence");
    }
    std::string command;
    if (!(std::cin >> command) || (command != "tomax" && command != "tomin")) {
      throw std::logic_error("Failed to input command");
    }
    /* TODO walk */
    clear(sequence);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    clear(sequence);
    return 1;
  }
}

