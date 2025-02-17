#include <iostream>
#include <stdexcept>

struct FwdList
{
  int value;
  FwdList *next;
};

FwdList * get_element(size_t target, FwdList *ptr)
{
  if (!ptr)
  {
    throw std::out_of_range("out of range");
  }
  for (size_t i = 0; i < target; i++)
  {
    ptr = ptr->next;
    if (!ptr)
    {
      throw std::out_of_range("out of range");
    }
  }
  return ptr;
}

void add(FwdList *ptr, int value)
{
  FwdList *cur = new FwdList{value, nullptr};
  cur->next = ptr->next;
  ptr->next = cur;
}

FwdList * insert_to_pos(FwdList *head, size_t pos, size_t k)
{
  FwdList *ptr = get_element(pos, head), *cur = ptr;
  for (size_t i = 0; i < k; i++)
  {
    add(cur, ptr->value);
  }
  return ptr;
}

void clear(FwdList *head)
{
  FwdList *cur = head;
  while (head)
  {
    cur = head->next;
    delete head;
    head = cur;
  }
  return;
}

int main()
{
  FwdList *head = nullptr;
  try
  {
    head = new FwdList{0, nullptr};
    FwdList *tail = head, *cur = head;
    size_t size = 0;
    for (size_t i = 1; i < 10; i++)
    {
      add(tail, i);
      tail = tail->next;
    }
    size = 10;
    int a = 0;
    size_t b = 0;
    while (std::cin >> a >> b)
    {
      insert_to_pos(head, --a, b);
      size += b;
    }
    std::cout << cur->value;
    cur = cur->next;
    while (cur)
    {
      std::cout << ' ';
      std::cout << cur->value;
      cur = cur->next;
    }
    std::cout << '\n';
    clear(head);
    return 0;
  }
  catch(const std::bad_alloc& e)
  {
    clear(head);
    return 1;
  }
  catch(const std::out_of_range& e)
  {
    clear(head);
    return 2;
  }
}
