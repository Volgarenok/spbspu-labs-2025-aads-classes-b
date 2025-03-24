#ifndef LIST_HPP
#define LIST_HPP

template< class T >
struct List
{
  T data;
  List< T >* next;
};

template< class T >
List< T >* pushIn(List< T >* head, T data)
{
  List< T >* newList = new List< T > {data, nullptr};
  newList->next = head;
  return newList;
}

template< class T >
void clear(List< T >* head)
{
  while (head)
  {
    List< T >* temp = head;
    head = head->next;
    delete temp;
  }
}

template< class T >
List< T >* reverse_with_list(List< T >* head1)
{
  if (!head1)
  {
    return head1;
  }
  List< List< T >* >* head2 = nullptr;
  List< T >* cur = head1;
  try
  {
    while (cur)
    {
      head2 = pushIn(head2, cur);
      cur = cur->next;
    }
  }
  catch (...)
  {
    clear(head2);
    throw;
  }
  List< T >* newHead = head2->data;
  List< List< T >* >* cur2 = head2;
  while (cur2->next)
  {
    cur2->data->next = cur2->next->data;
    cur2 = cur2->next;
  }
  cur2->data->next = nullptr;
  clear(head2);
  return newHead;
}

template< class T >
List< T >* reverse_cleanly(List< T >* head) noexcept
{
  List< T >* prev = nullptr;
  List< T >* current = head;
  List< T >* next = nullptr;
  while (current)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  return prev;
}

template< class T >
List< T >* reverse_recursively(List< T >* head) noexcept
{
  if (!head || !head->next)
  {
    return head;
  }
  List< T >* newHead = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return newHead;
}

#endif
