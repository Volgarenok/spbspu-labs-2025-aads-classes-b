#include <cstddef>
#include <iostream>
struct FwdList {
  int value;
  FwdList * next;
};
void outputList(const FwdList* head);
FwdList* editList(FwdList* head, size_t element, size_t count);
FwdList* createList();
void clear(FwdList* head);

int main()
{
  FwdList* head = nullptr;
  try
  {
    head = createList();
    size_t element = 0;
    size_t count = 0;
    size_t size = 10;
    while (std::cin >> element && !std::cin.eof())
    {
      if (element > size || element <= 0)
      {
        clear(head);
        std::cerr << "Element out of range\n";
        return 1;
      }
      if (std::cin >> count && !std::cin.eof())
      {
        editList(head, element, count);
        size += element;
      }
    }
    outputList(head);
    clear(head);
  }
  catch (std::bad_alloc& e)
  {
    clear(head);
    std::cerr << "Out of memmory\n";
    return 1;
  }
}

void outputList(const FwdList* head)
{
  std::cout << head->value;
  head = head->next;
  while (head)
  {
    std::cout << " " << head->value;
    head = head->next;
  }
  std::cout << "\n";
}

FwdList* editList(FwdList* head, size_t element, size_t count)
{
  FwdList* now = head;
  for (size_t i = 1; i < element; i++)
  {
    now = now->next;
  }
  int number = now->value;
  for (size_t i = 0; i < count; i++)
  {
    FwdList* new_element = new FwdList{number, nullptr};
    new_element->next = now->next;
    now->next = new_element;
  }
  return now;
}

FwdList* createList()
{
  FwdList* head = nullptr;
  head = new FwdList{0, nullptr};
  FwdList* now = head;
  for (int i = 1; i < 10; i++)
  {
    now->next = new FwdList{i, nullptr};
    now = now->next;
  }
  return head;
}

void clear(FwdList* head)
{
  while (head)
  {
    FwdList* now = head->next;
    delete head;
    head = now;
  }
}
