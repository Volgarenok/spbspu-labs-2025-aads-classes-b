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
    while (std::cin >> current) {
      std::cout << (find(sequence, current) ? "<FOUND>\n" : "<NOT FOUND>\n");
    }
    clear(sequence);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    clear(sequence);
    return 1;
  }
}

