#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>
#include <stddef.h>

struct FwdList
{
  int value;
  FwdList* next;
};

void deleteList(FwdList* list)
{
  while (list)
  {
    FwdList* temp = list->next;
    delete list;
    list = temp;
  }
}

FwdList* createList()
{
  FwdList* list = new FwdList { 0, nullptr };
  FwdList* head = list;
  const int size = 10;
  try
  {
    for (int i = 1; i < size; ++i)
    {
      list->next = new FwdList { i, nullptr };
      list = list->next;
    }
    return head;
  }
  catch (const std::bad_alloc&)
  {
    deleteList(head);
    throw;
  }
}

FwdList* addNumber(FwdList* head, size_t number, size_t count)
{
  FwdList* element = head;
  for (size_t i = 0; i < number; ++i)
  {
    element = element->next;
  }
  if (!element)
  {
    throw std::logic_error("The number exceeds the number of elements");
  }
  FwdList* toReturn = element;
  FwdList* firstElement = new FwdList { element->value, nullptr };
  element = firstElement;
  try
  {
    for (size_t i = 1; i < count; ++i)
    {
      FwdList* node = new FwdList { element->value, nullptr };
      element->next = node;
      element = node;
    }
  }
  catch (const std::bad_alloc&)
  {
    deleteList(firstElement);
    throw;
  }
  element->next = toReturn->next;
  toReturn->next = firstElement;
  return toReturn;
}

std::ostream& outputList(std::ostream& out, FwdList* head)
{
  out << head->value;
  head = head->next;
  while (head)
  {
    out << " " << head->value;
    head = head->next;
  }
  return out;
}

int main()
{
  FwdList* head = nullptr;
  size_t number = 0;
  size_t count = 0;
  try
  {
    head = createList();
    while (std::cin >> number >> count)
    {
      if (number == 0)
      {
        throw std::invalid_argument("Incorrect parameter");
      }
      addNumber(head, number - 1, count);
    }
    outputList(std::cout, head) << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    deleteList(head);
    return 1;
  }
  deleteList(head);
}
