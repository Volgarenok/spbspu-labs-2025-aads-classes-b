#include <exception>
#include <iostream>
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

FwdList* createList(FwdList* head)
{
  head = new FwdList { 0, nullptr };
  FwdList* head_ = head;
  const int size = 10;
  for (int i = 1; i < size; ++i)
  {
    head->next = new FwdList { i, nullptr };
    head = head->next;
  }
  return head_;
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
  for (size_t i = 0; i < count; ++i)
  {
    FwdList* node = new FwdList { element->value, element->next };
    element->next = node;
    element = node;
  }
  return element;
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
    head = createList(head);
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
