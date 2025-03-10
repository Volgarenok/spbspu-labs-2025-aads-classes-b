#include <iostream>
#include <istream>

template< class T >
struct FwdList {
  T data;
  FwdList< T >* next;
};

template< class T >
void clear(FwdList< T >* head)
{
  while (head) {
    FwdList< T >* new_head = head->next;
    delete head;
    head = new_head;
  }
}

template< class T >
FwdList< T >* reverse_with_list(FwdList< T >* head)
{
  FwdList< FwdList< T >* >* stack = new FwdList< FwdList< T >* >{head, nullptr};
  while (head) {
    try {
      FwdList< FwdList< int >* >* new_node = new FwdList< FwdList< T >* >{head, stack};
      stack = new_node;
      head = head->next;
    } catch(const std::bad_alloc&) {
      clear< FwdList< T >*>(stack);
      throw;
    }
  }
  head = stack->data;
  FwdList< T >* current_head = head;
  FwdList< FwdList< T >* >* cur_stack = stack;
  while (cur_stack->next) {
    current_head->next = cur_stack->next->data;
    cur_stack = cur_stack->next;
    current_head = current_head->next;
    delete stack;
    stack = cur_stack;
  }
  return head;

}

template< class T >
FwdList< T >* reverse_cleanly(FwdList< T >* head) noexcept {
  if (!head) {
    return nullptr;
  }
  FwdList< T >* cur = head->next;
  if (!cur) {
    return head;
  }
  FwdList< T >* temp = cur->next;
  head->next = nullptr;
  while (temp) {
    cur->next = head;
    head = cur;
    cur = temp;
    temp = temp->next;
  }
  return cur;
}

template<class T>
FwdList<T>* reverse_recursively(FwdList<T>* head) noexcept {
    if (!head || !head->next) {
      return head;
    }

    FwdList<T>* new_head = reverse_recursively(head->next);

    head->next->next = head;
    head->next = nullptr;

    return new_head;
}

FwdList< int >* inputListInt(std::istream& in)
{
  int newData = 0;
  if (!(std::cin >> newData)) {
    return nullptr;
  }
  FwdList< int >* head = new FwdList< int >{newData, nullptr};
  FwdList< int >* cur = head;
  while (in >> newData && !in.eof()) {
    try {
      FwdList< int >* new_node = new FwdList< int >{newData, nullptr};
      cur->next = new_node;
      cur = cur->next;
    } catch(const std::bad_alloc&) {
      clear< int >(head);
      throw;
    }
  }
  return head;
}

std::ostream& outputListInt(std::ostream& out, FwdList< int >* head)
{
  while (head) {
    out << head->data;
    if (head->next) {
      out << " ";
    }
    head = head->next;
  }
  return out;
}

int main (int argc, char** argv)
{
  FwdList< int >* head = nullptr;
  try {
    head = inputListInt(std::cin);
  } catch(const std::bad_alloc&) {
    std::cerr << "Memory error";
    return 1;
  }
  FwdList< int >* new_head = nullptr;

  if (argc == 2 && argv[1][0] == '0')
  {
    try {
      new_head = reverse_with_list(head);
    } catch(const std::bad_alloc&) {
      std::cerr << "Memory error";
      return 1;
    }
  }
  else if (argc == 2 && argv[1][0] == '1')
  {
    new_head = reverse_cleanly(head);
  }
  else if (argc == 2 && argv[1][0] == '2')
  {
    new_head = reverse_recursively(head);
  }
  else
  {
    std::cerr << "Invalid parametrs\n";
    new_head = reverse_cleanly(head);
  }
  outputListInt(std::cout, new_head);
  clear< int >(new_head);
}
