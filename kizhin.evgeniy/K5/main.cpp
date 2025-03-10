#include <cstdint>
#include <stdexcept>
#include "io-utils.hpp"

int main()
{
  using namespace kizhin;
  try {
    size_t size = 0;
    if (!(std::cin >> size)) {
      throw std::logic_error("Failed to input sequence size");
    }
    BiTree< int64_t >* sequence = inputSequence< int64_t >(std::cin, size);
    if (!std::cin) {
      throw std::logic_error("Failed to input sequence");
    }
    int64_t current = 0;
    while (std::cin >> current) {
      std::cout << (find(sequence, current) ? "<FOUND>\n" : "<NOT FOUND>\n");
    }
    if (!std::cin) {
      throw std::logic_error("Failed to input values");
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

