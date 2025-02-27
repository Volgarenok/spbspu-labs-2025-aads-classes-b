#include <iostream>
#include <stdexcept>

template< class T >
struct List {
  T data;
  List< T > * next;
};
// 1
template< class T >
List< T > * reverse_with_list(List< T > * head);
// 2
template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept;
// 3
template< class T >
List< T > * reverse_recursively(List< T > * head) noexcept;

template< class T >
void clear(List< T > * head);

template< class T >
void push_back(List< T > * head, T data);

template< class T >
List< T > * push_front(List< T > * head, T data);

template< class T >
void clear(List< T > * head)
{
  List< T > * cur = head;
  while (head)
  {
    head = head->next;
    delete cur;
    cur = head;
  }
  return;
}

template< class T >
void push_back(List< T > * tail, T data)
{
  List< T > * cur = new List< T >{data, tail->next};
  tail->next = cur;
  return;
}

template< class T >
List< T > * push_front(List< T > * head, T data)
{
  List< T > * cur = new List< T >{data, head};
  return cur;
}

template< class T >
void insert_after(List< T > * node, List< T > * tail)
{
  List< T > *cur = nullptr;
  if (tail)
  {
    cur = tail->next;
  }
  tail->next = node;
  node->next = cur;
  return;
}

template< class T >
List< T > * reverse_with_list(List< T > * head)
{
  List< T > * cur = nullptr;
  try
  {
    List< T > * cur = new List< T >{head->data, nullptr};
    while (head->next)
    {
      head = head->next;
      cur = push_front(cur, head->data);
    }
    return cur;
  }
  catch (const std::bad_alloc &e)
  {
    clear(cur);
    throw;
  }
}

template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept
{
  List< T > * tail = head, * temp = head;
  while (tail->next)
  {
    tail = tail->next;
  }
  while (head != tail)
  {
    head = head->next;
    insert_after(temp, tail);
    temp = head;
  }
  return tail;
}

template< class T >
List< T > * reverse_rec(List< T > * head) noexcept
{
  if (!head->next)
  {
    return head;
  }
  List< T > *cur = reverse_rec(head->next);
  cur->next = head;
  cur->next->next = nullptr;
  return head;
}

template< class T >
List< T > * reverse_recursively(List< T > * head) noexcept
{
  List< T > *cur = head;
  while (cur->next)
  {
    cur = cur->next;
  }
  reverse_rec(head);
  return cur;
}

template < class T >
std::ostream & out_list(std::ostream &out, List< T > *head)
{
  out << head->data;
  head = head->next;
  while (head)
  {
    std::cout << ' ' << head->data;
    head = head->next;
  }
  return out;
}

int main(int argc, const char **argv)
{
  int n = 0;
  if ((std::cin >> n).eof())
  {
    std::cout << '\n';
    return 0;
  }
  List< int > *head = nullptr, *tail = head;
  try
  {
    head = new List< int >{n, nullptr};
    tail = head;
    while (std::cin >> n)
    {
      push_back(tail, n);
      tail = tail->next;
    }
    if (!std::cin.eof())
    {
      clear(head);
      std::cerr << "input error";
      return 1;
    }
    if (argc == 2 && argv[1][0] == '0')
    {
      head = reverse_with_list(head);
    }
    else if (argc == 2 && argv[1][0] == '1')
    {
      head = reverse_cleanly(head);
    }
    else if (argc == 2 && argv[1][0] == '2')
    {
      head = reverse_recursively(head);
    }
    else
    {
      std::cerr << "not 0 or 1 or 2\n";
      head = reverse_cleanly(head);
    }
    out_list(std::cout, head) << '\n';
    clear(head);
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr << e.what() << '\n';
    clear(head);
  }
  return 0;
}
