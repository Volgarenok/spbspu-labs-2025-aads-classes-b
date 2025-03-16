#include <iostream>

template< class T >
struct List {
  T data;
  List< T > * next;
};

template< class T >
void clear(List< T >* head)
{
  while (head)
  {
    List< T >* current = head->next;
    delete head;
    head = current;
  }
}

template< class T >
List< T > * reverse_with_list(List< T >* head)
{
  if (!head || !head->next)
  {
    return head;
  }
  List< T > * newHead = head;
  List< T > * last = new List< T >{newHead->data, nullptr};
  while (!newHead->next)
  {
    try
    {
      newHead = newHead->next;
      last = new List< T >{newHhead->data, last};
    }
    catch(const std::bad_alloc& e)
    {
      clear(last);
      throw;
    }
  }
  clear(head);
  return last;
}

template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept
{
  List< T >* prev = nullptr;
  List< T >* next = nullptr;
  List< T >* current = head;
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
List< T > * reverse_recursively(List< T > * head) noexcept
{
  if (!head || !head->next)
  {
    return head;
  }
  List<T>* newHead = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return newHead;
}

template< class T >
void output_list(std::ostream& out, List< T > * head)
{
  while (head)
  {
    out << head->data << " ";
    head = head->next;
  }
  out << "\n";
  return out;
}

int main(int argc, char** argv)
{

}
