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

  for (size_t i = 1; i < num; i++)
  {
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
      freeList(head);
      throw;
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

bool isOutOfRange(FwdList* head, size_t num)
{
  if (num < 1)
  {
    return true;
  }

  FwdList* headCopy = head;
  for (size_t i = 1; i < num; i++)
  {
    if (headCopy->next == nullptr)
    {
      return true;
    }
    headCopy = headCopy->next;
  }

  return false;
}

int main()
{
  FwdList* head = nullptr;
  for (int i = 0; i < 10; i++)
  {
    try
    {
      FwdList* newNode = new FwdList{i, nullptr};
      if (head == nullptr)
      {
        head = newNode;
      }
      else
      {
        FwdList* current = head;
        while (current->next != nullptr)
        {
          current = current->next;
        }
        current->next = newNode;
      }
    }
    catch (const std::bad_alloc&)
    {
      freeList(head);
    }
  }
  size_t num = 0, dubls = 0;

  while (std::cin >> num >> dubls)
  {
    if (isOutOfRange(head, num))
    {
      freeList(head);
      return 1;
    }
    addDubls(head, num, dubls);
  }

  printList(std::cout, head);
  std::cout << "\n";
  freeList(head);
}
