#include <iostream>

template< class T >
struct List
{
  T data;
  List< T >* next;
};

template< class T >
List< T >* reverse_with_list(List< T >* head)
{
  List< T >* stackHead = nullptr;
  List< T >* current = head;

  while (current != nullptr)
  {
    List< T >* newNode = new List< T >{current->data, stackHead};
    stackHead = newNode;
    current = current->next;
  }
  return stackHead;

}

template< class T >
List< T >* reverse_cleanly(List< T >* head) noexcept
{
  List< T >* prev = nullptr;
  List< T >* next = nullptr;
  List< T >* current = head;
  while (current != nullptr)
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
  if (head == nullptr || head->next == nullptr)
  {
    return head;
  }

  List< T >* newHead = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return newHead;
}

template< class T >
void free_list(List< T >* head)
{
  List< T >* current = head;
  while (current != nullptr)
  {
    List< T >* next = current->next;
    delete current;
    current = next;
  }
}

template< class T >
void print_list(std::ostream& out, List< T >* head)
{
  List< T >* current = head;
  out << current->data;
  current = current->next;
  while (current != nullptr)
  {
    out << " " << current->data;
    current = current->next;
  }
}

int main(int argc, char* argv[])
{
  int num = 0;
  if (!(std::cin >> num) && std::cin.eof())
  {
    std::cout << "\n";
    return 0;
  }
  List< int >* head = new List< int >{num, nullptr};
  try
  {
    while(std::cin >> num || !std::cin.eof())
    {
      if (!std::cin)
      {
        std::cerr << "incorrect input\n";
        free_list(head);
        return 1;
      }
      List< int >* newNode = new List< int >{num, nullptr};
      List< int >* current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = newNode;
    }
  }
  catch (const std::bad_alloc&)
  {
    free_list(head);
    return 1;
  }

  if (argc == 2 && argv[1][0] == '0')
  {
    List< int >* oldHead = head;
    head = reverse_with_list(head);
    free_list(oldHead);
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
    std::cerr << "incorrect param\n";
    head = reverse_cleanly(head);
  }

  print_list(std::cout, head);
  std::cout << "\n";

  free_list(head);
}
