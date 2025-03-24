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
    List< T >* now = head->next;
    delete head;
    head = now;
  }
}

template< class T >
List< T > * reverse_with_list(List< T >* head)
{
  List< List< T >* >* it = nullptr;
  List< List< T >* >* now = nullptr;
  List< T >* new_head = nullptr;
  List< T >* temp = head;
  try
  {
    while (temp)
    {
      now = new List< List< T >* >{temp, it};
      it = now;
      temp = temp->next;
    }
    List< List< T >* >* new_list = it;
    while (new_list)
    {
      List< T >* element = new_list->data;
      if (!element->next)
      {
        new_head = element;
      }
      List< List< T >* >* next_node = new_list->next;
      new_list->data = nullptr;
      if (next_node)
      {
        element->next = next_node->data;
      }
      else
      {
        element->next = nullptr;
      }
      new_list = new_list->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    clear(it);
    throw;
  }
  clear(it);
  return new_head;
}

template< class T >
List< T > * reverse_cleanly(List< T > * head) noexcept
{
  if (!head)
  {
    return head;
  }
  List< T > * next = head->next;
  head->next = nullptr;
  List< T > * last = head;
  while (next)
  {
    List< T > * remember = next->next;
    next->next = last;
    last = next;
    next = remember;
  }
  return last;
}

template< class T >
List< T > * reverse_recursively(List< T > * head) noexcept
{
  if (head == nullptr || head->next == nullptr)
  {
    return head;
  }
  List<T>* new_head = reverse_cleanly(head->next);
  head->next->next = head;
  head->next = nullptr;
  return new_head;
}

template< class T >
void output_list(std::ostream& out, List< T > * head)
{
  if (head == nullptr)
  {
    return;
  }
  List< T >* list = head;
  out << list->data;
  list = list->next;
  while (list)
  {
    out << " " << list->data;
    list = list->next;
  }
}

int main(int argc, char** argv)
{
  int x = 0;
  List< int >* head = nullptr;
  try
  {
    if (std::cin >> x && !std::cin.eof())
    {
      head = new List< int >{x, nullptr};
    }
    List< int >* last = head;
    while (std::cin >> x && !std::cin.eof())
    {
      last->next = new List< int >{x, nullptr};
      last = last->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    clear(head);
    std::cerr << "Out of memory\n";
    return 1;
  }
  if (!std::cin.eof())
  {
    std::cerr << "Error in input\n";
    clear(head);
    return 1;
  }
  char* str = argv[1];
  try
  {
    if (argc == 2 && str[0] == '0')
    {
      head = reverse_with_list(head);
    }
    else if (argc == 2 && str[0] == '1')
    {
      head = reverse_cleanly(head);
    }
    else if (argc == 2 && str[0] == '2')
    {
      head = reverse_recursively(head);
    }
    else
    {
      std::cerr << "Error in parameter\n";
      head = reverse_cleanly(head);
    }
  }
  catch (const std::bad_alloc& e)
  {
    clear(head);
    std::cerr << "Out of memory\n";
    return 1;
  }
  output_list(std::cout, head);
  std::cout << "\n";
  clear(head);
}
