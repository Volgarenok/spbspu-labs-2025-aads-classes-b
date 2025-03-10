#include <cctype>
#include <exception>
#include <iostream>
#include <new>
#include <ostream>
#include <stdexcept>
#include <string>
#include <endian.h>
template< class T >
struct List
{
  T data;
  List< T >* next;
};

template< typename T >
void deleteList(List< T >* list)
{
  while (list)
  {
    List< T >* temp = list->next;
    delete list;
    list = temp;
  }
}

List< int >* createList(std::istream& input)
{
  int a = 0;
  if (!(input >> a))
  {
    return nullptr;
  }
  List< int >* list = new List< int >{a, nullptr };
  List< int >* head = list;
  try
  {
    while (input >> a)
    {
      list->next = new List< int >{ a, nullptr };
      list = list->next;
    }
    return head;
  }
  catch (const std::exception&)
  {
    deleteList(head);
    throw;
  }
}

template< typename T >
List< T >* reverse_with_list(List< T >* head)
{
  List< List< T >* >* stack = nullptr;
  List< T >* temp = head;
  try
  {
    while (temp)
    {
      stack = new List< List< T >* >{ temp, stack };
      temp = temp->next;
    }
  }
  catch (std::bad_alloc&)
  {
    deleteList(stack);
    throw;
  }
  head = stack->data;
  List< List< T >* >* tempStack = stack;
  temp = head;
  while (stack)
  {
    temp->next = stack->data;
    temp = temp->next;
    stack = stack->next;
  }
  temp->next = nullptr;
  deleteList(tempStack);
  return head;
}

template < typename T >
List< T >* reverse_cleanly(List< T >* head) noexcept
{
  List< T >* prev = nullptr;
  List< T >* temp = head;
  List< T >* next = nullptr;
  while (temp)
  {
    next = temp->next;
    temp->next = prev;
    prev = temp;
    temp = next;
  }
  return prev;
}

template< typename T >
List< T >* reverse_recursively(List< T >* head) noexcept
{
  if (!head->next)
  {
    return head;
  }
  List< T >* temp = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return temp;
}
template< typename T >
std::ostream& printList(std::ostream& output, List< T >* list)
{
  if (!list)
  {
    throw std::logic_error("List is empty");
  }
  output << list->data;
  list = list->next;
  while (list)
  {
    output << " " << list->data;
    list = list->next;
  }
  return output;
}

int main(int argc, char** argv)
{
  List< int >* list = nullptr;
  try
  {
    list = createList(std::cin);
    if (!std::cin.eof() && !std::cin)
    {
      std::cerr << "Incorrect input\n";
      deleteList(list);
      return 1;
    }
    else if (!list && std::cin.eof())
    {
      std::cout << "\n";
      return 0;
    }
    if (list->next)
    {
      if (argc == 2 && argv[1][0] == '0')
      {
        list = reverse_with_list(list);
      }
      else if (argc == 2 && argv[1][0] == '1')
      {
        list = reverse_cleanly(list);
      }
      else if (argc == 2 && argv[1][0] == '2')
      {
        list = reverse_recursively(list);
      }
      else
      {
        std::cerr << "Unknown parameter\n";
        list = reverse_cleanly(list);
      }
    }
    printList(std::cout, list) << "\n";
    deleteList(list);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    deleteList(list);
    return 1;
  }
}
