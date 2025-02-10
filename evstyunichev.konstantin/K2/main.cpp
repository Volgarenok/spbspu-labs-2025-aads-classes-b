#include <stdexcept>
#include <iostream>

struct FwdList
{
  int value;
  FwdList *next;
};

FwdList * get_element(size_t target, FwdList *ptr)
{
  for (size_t i = 0; (i < target) && ptr; i++)
  {
    ptr = ptr->next;
  }
  return ptr;
}

int add(FwdList *ptr, int value)
{
  try
  {
    FwdList *cur = new FwdList{value, nullptr};
    cur->next = ptr->next;
    ptr->next = cur;
  }
  catch(const std::exception& e)
  {
    return 0;
  }
  return 1;
}

FwdList * insert_to_pos(FwdList *head, size_t pos, size_t k)
{
  FwdList *ptr = get_element(pos, head), *cur = ptr;
  if (ptr)
  {
    for (size_t i = 0; i < k; i++)
    {
      if (add(cur, ptr->value))
      {
        cur = cur->next;
      }
      else
      {
        return nullptr;
      }
    }
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
  head = new FwdList{0, nullptr};
  FwdList *tail = head, *cur = head;
  size_t size = 0;
  for (size_t i = 1; i < 10; i++)
  {
    if (!add(tail, i))
    {
      clear(head);
      return 1;
    }
    tail = tail->next;
  }
  size = 10;
  int a = 0;
  size_t b = 0;
  while (std::cin >> a >> b)
  {
    if (b > size)
    {
      std::cout << "so large position!\n";
    }
    else if (!insert_to_pos(head, --a, b))
    {
      clear(head);
      return 1;
    }
    size += b;
  }
  while (cur)
  {
    std::cout << cur->value;
    cur = cur->next;
    if (cur)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
  clear(head);
  return 0;
}
