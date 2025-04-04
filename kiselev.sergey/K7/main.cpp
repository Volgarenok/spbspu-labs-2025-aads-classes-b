#include <exception>
#include <limits>
#include <iostream>
#include <string>
#include "beTree.hpp"
#include "iterator.hpp"

template< typename T >
std::ostream& output(std::ostream& out, kiselev::BiTree< T >* root, const std::string& text)
{
  if (!root)
  {
    return out;
  }
  if (text == "tomax")
  {
    auto it = kiselev::begin(root);
    for (; it.hasNext(); it = it.next())
    {
      out << it.data() << " ";
    }
    out << it.data();
  }
  else if (text == "tomin")
  {
    auto it = kiselev::rbegin(root);
    for (; it.hasPrev(); it = it.prev())
    {
      out << it.data() << " ";
    }
    out << it.data();
  }
  else
  {
    throw std::logic_error("Unknown command");
  }
  return out;
}
int main()
{
  size_t length;
  if (!(std::cin >> length))
  {
    std::cerr << "Invalid length\n";
    return 1;
  }
  kiselev::BiTree< int >* root = nullptr;
  try
  {
    for (size_t i = 0; i < length; ++i)
    {
      int number = 0;
      if (!(std::cin >> number))
      {
        std::cerr << "Incorrect number\n";
        deleteTree(root);
        return 1;
      }
      root = pushTree(root, number);
    }
    std::string command;
    if (!(std::cin >> command))
    {
      std::cerr << "Invalid command\n";
      kiselev::deleteTree(root);
      return 1;
    }
    if (length == 0 && command.empty())
    {
      std::cerr << "No elements\n";
      return 1;
    }
    output(std::cout, root, command) << "\n";
    kiselev::deleteTree(root);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    deleteTree(root);
    return 1;
  }
}
