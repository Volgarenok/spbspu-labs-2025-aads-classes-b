#include <iostream>
#include <istream>

template< class T >
struct FwdList {
  T data;
  FwdList* next;
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
      FwdList< FwdList< T >* >* new_node = new FwdList< FwdList< T >* >{head, stack};
      stack = new_node;
      head = head->next;
    } catch(const std::bad_alloc&) {
      clear< FwdList< T >*>(stack);
      throw;
    }
  }
  head = nullptr;
  FwdList< FwdList< T >* >* cur_stack = stack;
  while (cur_stack) {
    FwdList< T >* current_head = cur_stack->data;
    cur_stack = cur_stack->next;
    current_head->next = head;
    head = current_head;
  }
  clear< FwdList< T >*>(stack);
  return head;

}

template< class T >
FwdList< T >* reverse_cleanly(FwdList< T >* head) {
  if (!head) return nullptr;
  FwdList< T >* cur = head->next;
  if (!cur) return head;
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
FwdList<T>* reverse_recursively(FwdList<T>* head) {
    if (!head || !head->next) {
        return head;
    }

    FwdList<T>* new_head = reverse_recursively(head->next);

    head->next->next = head;
    head->next = nullptr;

    return new_head;
}

FwdList< int >* inputListInt(std::istream& in, FwdList< int >* head)
{
  FwdList< int >* cur = head;
  while (!std::cin.eof()) {
    int newData = 0;
    if (!(in >> newData)) {
      clear(head);
    }
    try {
      cur = new FwdList< int >{newData, nullptr};
      cur = cur->next;
    } catch(const std::bad_alloc&) {
      clear< int >(head);
      throw;
    }
  }

}

std::ostream& outputListInt(std::ostream& out, FwdList< int >* head)
{
  while (head) {
    out << head->data;
    head = head->next;
  }
  return out;
}

int main (int argc, char** argv)
{
  *argv = nullptr;
  FwdList< int >* head = inputListInt(std::cin)
  FwdList< int >* new_head = nullptr;
  switch(argc) {
    case 0:
      try {
        new_head = reverse_with_list< int >(head);
        break;
      } catch (const std::bad_alloc&) {
        clear< int >(head);
        clear< int >(new_head);
      }
      
    case 1:
      new_head = reverse_cleanly< int >(head);
      break;
    case 2:
      new_head = reverse_recursively< int >(head);
      break;
    default:
      new_head = reverse_cleanly< int >(head);
  }
  outputListInt(std::cout, new_head);
  clear< int >(new_head);
}