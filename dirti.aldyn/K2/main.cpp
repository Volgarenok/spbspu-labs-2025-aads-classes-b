#include <iostream>
#include <stdexcept>

struct FwdList
{
  int value;
  FwdList * next;
};

void clear(FwdList * head);

FwdList * startList()
{
  FwdList * head = new FwdList{0, nullptr};
  FwdList * tempHead = head;
  for (int i = 1; i < 10; ++i)
  {
    try
    {
      tempHead->next = new FwdList{i, nullptr};
      tempHead = tempHead->next;
    }
    catch (const std::bad_alloc & e)
    {
      clear(head);
      throw;
    }
  }
  return head;
}

void clear(FwdList * head)
{
  while (head)
  {
    FwdList * nextHead = head->next;
    delete head;
    head = nextHead;
  }
}

void newList(FwdList * head, size_t number, size_t size)
{
  if (number == 0)
  {
    throw;
  }
  FwdList * tempHead = head;
  for (size_t i = 1; i < number; ++i)
  {
    tempHead = tempHead->next;
    if (!tempHead)
    {
      throw;
    }
  }
  FwdList * next = tempHead->next;
  FwdList * newHead = nullptr;
  for (size_t i = 0; i < size; ++i)
  {
    try
    {
      newHead = new FwdList{tempHead->value, next};
      tempHead->next = newHead;
      tempHead = newHead;
    }
    catch (const std::bad_alloc & e)
    {
      throw;
    }
  }
}

int main()
{
  FwdList * head = nullptr;
  try
  {
    head = startList();
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Error" << "\n";
    return 1;
  }
  size_t number = 0;
  size_t size = 0;
  while (std::cin)
  {
    if (std::cin >> number >> size)
    {
      try
      {
        newList(head, number, size);
      }
      catch (const std::exception & e)
      {
        clear(head);
        std::cerr << "Error" << "\n";
        return 1;
      }
    }
  }
  std::cout << head->value;
  FwdList * tempHead = head->next;
  while (tempHead)
  {
    std::cout << " " << tempHead->value;
    tempHead = tempHead->next;
  }
  std::cout << "\n";
  clear(head);
}
