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
    sequence = inputSequence< int64_t >(std::cin, size);
    if (!std::cin) {
      throw std::logic_error("Failed to input sequence");
    }
    int64_t current = 0;
    if (!(std::cin >> current)) {
      throw std::logic_error("Failed to input values");
    }
    do {
      const BiTree< int64_t >* foundNode = find(sequence, current);
      std::cout << (foundNode && foundNode->data == current ? "<FOUND>" : "<NOT FOUND>");
      std::cout << '\n';
    } while (std::cin >> current);
    clear(sequence);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    clear(sequence);
    return 1;
  }
}

