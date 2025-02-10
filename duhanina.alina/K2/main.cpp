#include <iostream>
#include <stdexcept>

struct FwdList
{
  int value;
  FwdList* next;
};

FwdList* insertDuplicates(FwdList* head, size_t position, size_t count)
{
  FwdList* current = head;
  for (size_t i = 1; i < position && current != nullptr; ++i)
  {
    current = current->next;
  }
  if (current == nullptr)
  {
    throw std::out_of_range("Position is out of range");
  }
  for (size_t i = 0; i < count; ++i)
  {
    FwdList* newNode = new FwdList{current->value, current->next};
    current->next = newNode;
    current = newNode;
  }
  return head;
}

FwdList* createList()
{
  FwdList* head = new FwdList{0, nullptr};
  FwdList* current = head;
  for (int i = 1; i < 10; ++i)
  {
    current->next = new FwdList{i, nullptr};
    current = current->next;
  }
  return head;
}

void printList(FwdList* head)
{
  FwdList* current = head;
  std::cout << current->value;
  current = current->next;
  while (current != nullptr)
  {
    std::cout << " " << current->value;
    current = current->next;
  }
  std::cout << "\n";
}

void deleteList(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* temp = head;
    head = head->next;
    delete temp;
  }
}

int main()
{
  FwdList* head = createList();
  size_t position = 0;
  size_t count = 0;
  while (std::cin >> position >> count)
  {
    if (position == 0)
    {
      std::cerr << "Error\n";
      deleteList(head);
      return 1;
    }
    try
    {
      head = insertDuplicates(head, position, count);
    }
    catch (...)
    {
      std::cerr << "Error\n";
      deleteList(head);
      return 1;
    }
  }
  printList(head);
  deleteList(head);
  return 0;
}
