#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

FwdList* duplicate(FwdList* head, size_t index, size_t count)
{
  FwdList* current = head;
  for (size_t i = 0; i < index; i++)
  {
    current = current->next;
  }
  if (!current)
  {
    std::cerr << "Out of range" << '\n';
    return nullptr;
  }
  for (size_t i = 0; i < count; ++i) {
    FwdList* newNode = new FwdList{current->value, current->next};
    current->next = newNode;
    current = newNode;
  }
  return current;
}

void clear(FwdList* head) 
{
  while (head)
  {
    FwdList* temp = head;
    head = head->next;
    delete temp;
  }
}

void print(FwdList* head)
{
  std::cout << head->value;
  while (head->next) {
    std::cout << " " << head->next->value;
    head = head->next;
  }
  std::cout << "\n";
}

int main() 
{
  FwdList* head = new FwdList{0, nullptr};
  FwdList* current = head;
  for (int i = 1; i < 10; ++i) {
    current->next = new FwdList{i, nullptr};
    current = current->next;
  }

  size_t index, count;
  while (std::cin >> index >> count)
  {
    if (index == 0)
    {
      std::cerr << "Error" << '\n';
      clear(head);
      return 0;
    }
    try
    {
      duplicate(head, index, count);
    }
    catch (const std::exception &e)
    {
      std::cerr << "Error" << '\n';
      clear(head);
      return 0;
    }
  }
  FwdList* current = head;
  print(head);
  return 0;
}
