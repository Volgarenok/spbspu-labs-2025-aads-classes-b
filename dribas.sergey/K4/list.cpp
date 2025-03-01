#include "list.hpp"

template< class T >
dribas::List < T > * dribas::input(List < T > * head, std::istream& in)
{
  in >> head.data;
  head.next = new List< T >;
  return head;
}

template< class T >
void dribas::clear(List < T > * head)
{
  if (head) {
    List < T > * interim = head;
    while (head) {
      interim = head->next;
      delete head;
      head = interim;
    }
  }
}

template< class T >
dribas::List< T > * dribas::reverse_with_list(List< T > * head)
{
  List< T > * stackH = nullptr;

  while(head != nullptr) {
    List< T > * node = new List< T >{head->data, stackH};
    stackH = node;
    head = head.next;
  }
  return stackH;
}

template< class T >
dribas::List< T > * dribas::reverse_cleanly(List< T > * head) noexcept
{
  List< T > * prefix = nullptr;
  List< T > * current = head;
  List< T > * next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prefix;
    prefix = current;
    current = next;
  }
  return prefix;
}

template< class T>
dribas::List< T > * dribas::reverse_recursively(List< T > * head) noexcept
{
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  List< T > * current = reverse_recursively(head.next);
  head->next.next = head;
  head->next = nullptr;
  return current;
}

template< class T >
void dribas::outputList(std::ostream& out, List< T > * head)
{
  if (head != nullptr) {
    out << head->data;
    head = head->next;
    while (head)
    {
      out << " " << head->data;
      head = head->next;
    }
  }
}
