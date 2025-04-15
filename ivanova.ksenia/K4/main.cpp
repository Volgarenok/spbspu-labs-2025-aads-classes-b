#include <iostream>
#include <string>
#include <stdexcept>

template <class T>
struct List
{
  T data;
  List<T>* next;
};

template <class T>
void clear(List<T>* head)
{
  while (head)
  {
    List<T>* current = head->next;
    delete head;
    head = current;
  }
}

template <class T>
List<T>* reverse_with_list(List<T>* head)
{
  List<T>* newHead = nullptr;
  while (head)
  {
    List<T>* next = head->next;
    head->next = newHead;
    newHead = head;
    head = next;
  }
  return newHead;
}

template <class T>
List<T>* reverse_cleanly(List<T>* head) noexcept
{
  List<T>* prev = nullptr;
  List<T>* current = head;
  while (current)
  {
    List<T>* next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  return prev;
}

template <class T>
List<T>* reverse_recursively(List<T>* head) noexcept
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

template <class T>
void output_list(std::ostream& out, List<T>* head)
{
  while (head)
  {
    out << head->data << " ";
    head = head->next;
  }
  out << "\n";
}

template <class T>
List<T>* read_list()
{
  List<T>* head = nullptr;
  List<T>** current = &head;
  T value;
    
  while (std::cin >> value)
  {
    try
    {
      *current = new List<T>{value, nullptr};
      current = &((*current)->next);
    }
    catch (const std::bad_alloc&)
    {
      clear(head);
      throw;
    }
  }
    
  if (!std::cin.eof() && std::cin.fail())
  {
    clear(head);
    throw std::runtime_error("Invalid input");
  }
    
  return head;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << (argv[0] ? argv[0] : "./lab") << " <0|1|2>\n";
    return 0;
  }

  std::string mode(argv[1]);
  if (mode != "0" && mode != "1" && mode != "2")
  {
    std::cerr << "Warning: Invalid mode. Using default reverse method.\n";
  }

  try
  {
    List<int>* list = read_list<int>();
      
    if (mode == "0")
    {
      list = reverse_with_list(list);
    }
    else if (mode == "1")
    {
      list = reverse_cleanly(list);
    }
    else if (mode == "2")
    {
      list = reverse_recursively(list);
    }
    else
    {
      list = reverse_cleanly(list);
    }

    output_list(std::cout, list);
      
    clear(list);    
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
