#include <iostream>

struct FwdList
{
  int value;
  FwdList* next;
};

FwdList* ListManip(FwdList* head, size_t number, size_t count)
{
  FwdList* correct = head;
  for (size_t i = 1; i < number; i++)
  {
    correct = correct->next;
  }
  if (correct == nullptr)
  {
    throw std::out_of_range("Position is out of range");
  }
  FwdList* point = correct;
  FwdList* dubl = correct->next;
  for (size_t i = 0; i < count; i++)
  {
    try
    {
      FwdList* newList = new FwdList{correct->value, nullptr};
      correct->next = newList;
      correct = newList;
    }
    catch (...)
    {
      throw;
    }
  }
  correct->next = dubl;
  return point;
}

void deleteList(FwdList* head)
{
  while (head)
  {
    FwdList* temp = head;
    head = head->next;
    delete temp;
  }
}

int main()
{
  constexpr int size = 10;
  FwdList* head = new FwdList{0, nullptr};
  FwdList* tail = head;
  for (int i = 1; i < size; ++i)
  {
    tail->next = new FwdList{i, nullptr};
    tail = tail->next;
  }
  size_t pos, count;
  while (std::cin >> pos >> count)
  {
    if (pos == 0)
    {
      std::cerr << "Error\n";
      deleteList(head);
      return 1;
    }
    try
    {
      ListManip(head, pos, count);
    }
    catch (...)
    {
      std::cerr << "Error\n";
      deleteList(head);
      return 1;
    }
  }
  FwdList* current = head;
  while (current)
  {
    std::cout << current->value;
    if (current->next)
    {
      std::cout << " ";
    }
    FwdList* temp = current;
    current = current->next;
    delete temp;
  }
  std::cout << "\n";
  return 0;
}

