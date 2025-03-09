#include <iostream>
#include "list.hpp"

template< class T >
struct List {
  T data;
  List< T > * next;
};

template< typename T >
void clear(List < T > * head)
{
  while (head) {
    List < T >* interim = head->next;
    delete head;
    head = interim;
  }
}

List < int >* input(std::istream& in)
{
  int value = 0;
  List < int >* head = nullptr;
  List < int >* realHead = head;
  try {
    while(in >> value) {
      if (!head) {
        head = new List < int > {value, nullptr};
        realHead = head;
      } else {
        head->next = new List < int > {value, nullptr};
        head = head->next;
      }
    }
    if (in.fail() && !in.eof()) {
      throw std::invalid_argument("Invalid input");
    }
    return realHead;
  } catch (const std::bad_alloc&) {
    clear(realHead);
    throw;
  }
}

template< typename T >
List< T > * reverse_with_list(List< T > * head)
{
  List< T > * stackH = nullptr;

  while(head != nullptr) {
    List< T > * node = new List< T >{head->data, stackH};
    stackH = node;
    head = head->next;
  }
  return stackH;
}

template< typename T >
List< T > * reverse_cleanly(List< T > * head) noexcept
{
  List< T > * prefix = nullptr;
  List< T > * current = head;
  List< T > * next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prefix;
    prefix = current;
    current = next;
  }
  return prefix;
}

template< typename T>
List< T > * reverse_recursively(List< T > * head) noexcept
{
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  List< T > * current = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return current;
}

template< typename T >
void outputList(std::ostream& out, List< T > * head)
{
  if (head != nullptr) {
    out << head->data;
    head = head->next;
    while (head)
    {
      out << " " << head->data;
      head = head->next;
    }
  }
}

int main(int argc, char* argv[])
{
  List < int > * head = nullptr;
  try {
    head = input(std::cin);
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    clear(head);
    return 1;
  }
  if (argc == 2 && argv[1][0] == '0') {
    head = reverse_with_list(head);
  } else if (argc == 2 && argv[1][0] == '1') {
    head = reverse_cleanly(head);
  } else if (argc == 2 && argv[1][0] == '2') {
    head = reverse_recursively(head);
  } else {
    std::cerr << "no parametr found\n";
  }

  outputList(std::cout, head);
  std::cout << '\n';
  clear(head);
  return 0;
}
