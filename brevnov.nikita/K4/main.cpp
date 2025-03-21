#include <iostream>

template< class T >
struct List
{
  T data;
  List< T > * next;
};

template< class T >
void clear(List< T > * head)
{
  while (head != nullptr)
  {
    List< T > * next = head->next;
    delete head;
    head = next;
  }
}

template< class T >
void outputing(List< T > * head, std::ostream& out)
{
  if (head == nullptr)
  {
    return;
  }
  out << head->data;
  while (head->next != nullptr)
  {
    out << " " << head->next->data;
    head = head->next;
  }
}

template< class T >
List< T > * reverse_with_list(List< T > * head)
{
  if (head == nullptr || head->next == nullptr)
  {
    return head;
  }
  List< T > * dhead = head;
  size_t count = 1;
  while (dhead->next != nullptr)
  {
    count++;
    dhead = dhead->next;
  }
  List< List < T > * > * last = new List< List < T > * >{dhead, nullptr};
  List< List < T > * > * dlast = last;
  while (count > 0)
  {
    dhead = head;
    for (size_t i = 1; i < count; i++)
    {
      dhead = dhead->next;
    }
    count--;
    try
    {
      dlast->next = new List< List < T > * >{dhead, nullptr};
    }
    catch (const std::bad_alloc& e)
    {
      clear(last);
      throw;
    }
    dlast = dlast->next;
  }
  dlast = last;
  while (dlast->next != nullptr)
  {
    dlast->data->next = dlast->next->data;
    dlast = dlast->next;
  }
  dlast->data->next = nullptr;
  head = last->data;
  clear(last);
  return head;
}

template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept
{
  if (head == nullptr && head->next == nullptr)
  {
    return head;
  }
  List< T > * nextl = head->next;
  List< T > * help = nextl->next;
  head->next = nullptr;
  while (help != nullptr)
  {
    nextl->next = head;
    head = nextl;
    nextl = help;
    help = help->next;
  }
  nextl->next = head;
  return nextl;
}

template< class T >
List< T > * reverse_recursively(List< T > * head) noexcept
{
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  List< T > * subHead = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return subHead;
}

int main (int argc, char** argv)
{
  char * str = argv[1];
  int a = 0;
  List< int > * head = nullptr;
  std::cin >> a;
  if (!std::cin.eof())
  {
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cerr << "Not correct input\n";
      clear(head);
      return 1;
    }
    try
    {
      head = new List< int >{a, nullptr};
    }
    catch (const std::bad_alloc& e)
    {
      std::cerr << "Not enough memory!\n";
      return 1;
    }
  }
  List< int > * tail = head;
  std::cin >> a;
  while (!std::cin.eof())
  {
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cerr << "Not correct input\n";
      clear(head);
      return 1;
    }
    try
    {
      tail->next = new List< int >{a, nullptr};
    }
    catch (const std::bad_alloc& e)
    {
      clear(head);
      std::cerr << "Not enough memory!\n";
      return 1;
    }
    tail = tail->next;
    std::cin >> a;
  }
  if (argc == 2 && str[0] == '2')
  {
    head = reverse_recursively(head);
  }
  else if (argc == 2 && str[0] == '0')
  {
    try
    {
      head = reverse_with_list(head);
    }
    catch (const std::bad_alloc& e)
    {
      clear(head);
      std::cerr << "Not enough memory!\n";
      return 1;
    }
  }
  else if (argc == 2 && str[0] == '1')
  {
    head = reverse_cleanly(head);
  }
  else
  {
    std::cerr << "Not correct parametr\n";
    head = reverse_cleanly(head);
  }
  outputing(head, std::cout);
  clear(head);
  std::cout << "\n";
  return 0;
}
