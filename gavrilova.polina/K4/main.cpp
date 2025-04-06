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
  if (!head) {
    return nullptr;
  }
  FwdList< FwdList< T >* >* stack = new FwdList< FwdList< T >* >{head, nullptr};
  head = head->next;
  while (head) {
    try {
      FwdList< FwdList< T >* >* new_node = new FwdList< FwdList< T >* >{head, stack};
      stack = new_node;
      head = head->next;
    } catch(const std::bad_alloc&) {
      clear< FwdList< T >*>(stack);
      throw;
    }
  }
  head = stack->data;
  FwdList< T >* current_head = head;
  FwdList< FwdList< T >* >* cur_stack = stack->next;
  while (cur_stack) {
    current_head->next = cur_stack->data;
    current_head = current_head->next;
    FwdList< FwdList< T >* >* temp_stack = cur_stack;
    cur_stack = cur_stack->next;
    delete temp_stack;
  }
  delete stack;
  current_head->next = nullptr;
  return head;
}

template< class T >
FwdList< T >* reverse_cleanly(FwdList< T >* head) noexcept {
  if (!head) {
    return nullptr;
  }

  FwdList< T >* prev = nullptr;
  FwdList< T >* cur = head;
  FwdList< T >* next = nullptr;

  while (cur) {
    next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  return prev;
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
  if (!(in >> newData)) {
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
    std::cerr << "Memory error\n";
    return 1;
  }
  if (!std::cin && !std::cin.eof()) {
    std::cerr << "Invalid input\n";
    clear< int >(head);
    return 1;
  }
  FwdList< int >* new_head = nullptr;

  if (argc == 2 && std::string(argv[1]) == "0")
  {
    try {
      new_head = reverse_with_list(head);
    } catch(const std::bad_alloc&) {
      std::cerr << "Memory error";
      clear< int >(head);
      return 1;
    }
  }
  else if (argc == 2 && std::string(argv[1]) == "1")
  {
    new_head = reverse_cleanly(head);
  }
  else if (argc == 2 && std::string(argv[1]) == "2")
  {
    new_head = reverse_recursively(head);
  }
  else
  {
    new_head = reverse_cleanly(head);
    std::cerr << "Invalid paRAMETRS\n";
  }
  outputListInt(std::cout, new_head);
  std::cout << "\n";
  clear< int >(new_head);
}
