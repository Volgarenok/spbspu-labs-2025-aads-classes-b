#include <iostream>
#include <stdexcept>

template< class T >
struct List {
  T data;
  List< T > *next;
};
// 1
template< class T >
List< T > * reverse_with_list(List< T > *head);
// 2
template< class T >
List< T > * reverse_cleanly(List< T > *head) noexcept;
// 3
template< class T >
List< T > * reverse_recursively(List< T > *head) noexcept;

template< class T >
void clear(List< T > *head);

template< class T >
List< T > * push_back(T data, List< T > *tail = nullptr);

template< class T >
void clear(List< T > *head)
{
  List< T > *cur = head;
  while (head)
  {
    head = head->next;
    delete cur;
    cur = head;
  }
  return;
}

template< class T >
List< T > * push_back(T data, List< T > *tail)
{
  List< T > *cur = new List< T >{ data, nullptr };
  if (tail)
  {
    tail->next = cur;
  }
  return cur;
}

template< class T >
void insert_after(List< T > *node, List< T > *tail)
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
List< T > * reverse_with_list(List< T > *head1)
{
  List< List< T > * > *head2 = nullptr, *cur = head2;
  List< T > *temp = head1;
  try
  {
    head2 = push_back(temp);
    cur = head2;
    while (temp->next)
    {
      temp = temp->next;
      push_back(temp, cur);
      cur = cur->next;
    }
    cur = head2;
    head1->next = nullptr;
    while (cur->next)
    {
      cur->next->data->next = cur->data;
      cur = cur->next;
    }
    clear(head2);
  }
  catch (const std::exception &e)
  {
    clear(head2);
    throw;
  }
  return temp;
}

template< class T >
List< T > * reverse_cleanly(List< T > *head) noexcept
{
  List< T > *tail = head, *temp = head;
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
List< T > * reverse_rec(List< T > *head) noexcept
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
List< T > * reverse_recursively(List< T > *head) noexcept
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

int main(int argc, char *argv[])
{
  List< int > *head = nullptr, *tail = head;
  try
  {
    int n = 0;
    if ((std::cin >> n).eof())
    {
      std::cout << '\n';
      return 0;
    }
    head = push_back(n);
    tail = head;
    while (std::cin >> n)
    {
      push_back(n, tail);
      tail = tail->next;
    }
    if (!std::cin.eof())
    {
      clear(head);
      std::cerr << "input error\n";
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
