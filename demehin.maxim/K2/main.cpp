#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

void freeList(FwdList* head)
{
  FwdList* current = head;
  while (current != nullptr)
  {
    FwdList* next = current->next;
    delete current;
    current = next;
  }
}

FwdList* addDubls(FwdList* head, size_t num, size_t dubls)
{
  FwdList* target = head;
  if (num == 0)
  {
    throw std::out_of_range("out of range");
  }

  for (size_t i = 1; i < num; i++)
  {
    if (target->next == nullptr)
    {
      throw std::out_of_range("out of range");
    }
    target = target->next;
  }

  FwdList* current = target;
  for (size_t i = 0; i < dubls; i++)
  {
    try
    {
      FwdList* dublNode = new FwdList{target->value, current->next};
      current->next = dublNode;
      current = dublNode;
    }
    catch (const std::bad_alloc&)
    {
      return target;
    }
  }

  return target;
}

void printList(std::ostream& out, FwdList* head)
{
  out << head->value;
  FwdList* current = head->next;
  while (current != nullptr)
  {
    out << " " << current->value;
    current = current->next;
  }
}

int main()
{
  FwdList* head = new FwdList{0, nullptr};
  for (int i = 1; i < 10; i++)
  {
    try
    {
      FwdList* newNode = new FwdList{i, nullptr};
      FwdList* current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = newNode;
    }
    catch (const std::bad_alloc&)
    {
      freeList(head);
    }
  }
  size_t num = 0, dubls = 0;

  while (std::cin >> num >> dubls)
  {
    try
    {
      addDubls(head, num, dubls);
    }
    catch(const std::out_of_range& e)
    {
      std::cerr << e.what() << "\n";
      freeList(head);
      return 1;
    }
  }

  printList(std::cout, head);
  std::cout << "\n";
  freeList(head);
}
