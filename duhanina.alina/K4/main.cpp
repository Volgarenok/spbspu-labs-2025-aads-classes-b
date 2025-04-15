#include <iostream>
#include <string>

template< class T >
struct List
{
  T data;
  List< T >* next;
};

template< class T >
void free_stack(List< List< T >* >* head)
{
  while (head != nullptr)
  {
    List< List< T >* >* temp = head;
    head = head->next;
    delete temp;
  }
}

template< class T >
List< T >* reverse_with_list(List< T >* head)
{
  List< List< T >* >* temp_stack = nullptr;
  List< T >* current_node = head;
  try
  {
    while (current_node != nullptr)
    {
      List< List< T >* >* new_stack_node = new List< List< T >* >{ current_node, temp_stack };
      temp_stack = new_stack_node;
      current_node = current_node->next;
    }
    List< List< T >* >* stack_node = temp_stack;
    List< T >* new_head = nullptr;
    List< T >* prev_node = nullptr;
    while (stack_node != nullptr)
    {
      List< T >* node = stack_node->data;
      if (new_head == nullptr)
      {
        new_head = node;
      }
      if (prev_node != nullptr)
      {
        prev_node->next = node;
      }
      prev_node = node;
      stack_node = stack_node->next;
    }
    if (prev_node != nullptr)
    {
      prev_node->next = nullptr;
    }
    free_stack(temp_stack);
    return new_head;
  }
  catch (...)
  {
    free_stack(temp_stack);
    throw;
  }
}

template< class T >
List< T >* reverse_cleanly(List< T >* head) noexcept
{
  List< T >* prev = nullptr;
  List< T >* current = head;
  List< T >* next = nullptr;
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
  List< T >* reversed_head = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return reversed_head;
}

template< class T >
void free_list(List< T >* head)
{
  while (head != nullptr)
  {
    List< T >* temp = head;
    head = head->next;
    delete temp;
  }
}

template< class T >
List< T >* create_node(List< T >* node, T data)
{
  if (!node)
  {
    return new List< T > { data, nullptr };
  }
  List< T >* current = node;
  while (current->next)
  {
    current = current->next;
  }
  current->next = new List< T > { data, nullptr };
  return node;
}

int main(int argc, char** argv)
{
  if (argc < 1)
  {
    return 1;
  }
  List< int >* head = nullptr;
  int data = 0;
  int mode = 0;
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (...)
  {
    std::cerr << "error\n";
  }
  try
  {
    while (std::cin >> data)
    {
      head = create_node(head, data);
    }
    if (std::cin.eof() && head == nullptr)
    {
      std::cout << "\n";
      return 0;
    }
    if (!std::cin.eof() && std::cin.fail())
    {
      std::cerr << "error\n";
      free_list(head);
      return 1;
    }
    if (mode == 0)
    {
      head = reverse_with_list(head);
    }
    else if (mode == 1)
    {
      head = reverse_cleanly(head);
    }
    else if (mode == 2)
    {
      head = reverse_recursively(head);
    }
    else
    {
      head = reverse_recursively(head);
      std::cerr << "error\n";
    }
  }
  catch (...)
  {
    free_list(head);
    std::cerr << "error\n";
    return 1;
  }
  List< int >* current = head;
  std::cout << current->data;
  current = current->next;
  while (current != nullptr)
  {
    std::cout << " " << current->data;
    current = current->next;
  }
  std::cout << "\n";
  free_list(head);
  return 0;
}
