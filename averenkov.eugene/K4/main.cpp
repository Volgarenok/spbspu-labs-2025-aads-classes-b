#include <iostream>
#include "list.hpp"

template < class T>
void deleteList(List< T >* head)
{
  while(head)
  {
    List< T >* fake = head;
    head = head->next;
    delete fake;
  }
}

template < class T >
void printList(List< T >* head)
{
  if (!head)
  {
    return;
  }
  std::cout << head->data;
  head = head->next;
  while(head)
  {
    std::cout << " " << head->data;
    head = head->next;
  }
}

int main(int argc, char** argv)
{
  if (argc < 1)
  {
    std::cerr << "Error!!\n";
    return 0;
  }
  int arg = 0;
  try
  {
    arg = std::stoi(argv[1]);
  }
  catch (...)
  {
    std::cerr << "Error\n";
  }
  int data = 0;
  List< int >* head = nullptr;
  List< int >* current = nullptr;
  while (std::cin >> data)
  {
    try
    {
      if (head == nullptr)
      {
        head = new List< int > { data, nullptr };
        current = head;
      }
      else
      {
        current->next = new List< int > { data, nullptr };
        current = current->next;
      }
    }
    catch (...)
    {
      std::cerr << "memory error\n";
      deleteList(head);
      return 1;
    }
  }
  if (std::cin.eof() && head == nullptr)
  {
    std::cout << "\n";
    return 0;
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "error\n";
    deleteList(head);
    return 1;
  }
  if (arg == 0)
  {
    try
    {
      head = reverse_with_list(head);
    }
    catch (...)
    {
      std::cerr << "error\n";
      deleteList(head);
      return 1;
    }
  }
  else if (arg == 1)
  {
    head = reverse_cleanly(head);
  }
  else if (arg == 2)
  {
    head = reverse_recursively(head);
  }
  else
  {
    head = reverse_cleanly(head);
    std::cerr << "bad input!!\n";
  }
  printList(head);
  std::cout << "\n";
  deleteList(head);
  return 0;
}
