#include <cstring>
#include <iostream>

template < class T >
struct List {
  T data;
  List< T >* next;
};

template < class T >
List< T >* addElem(List< T >* head, const T& data)
{
  if (head == nullptr) {
    return new List< T >{data, head};
  }
  List< T >* p = head;
  while (p->next != nullptr) {
    p = p->next;
  }
  p->next = new List< T >{data, nullptr};
  return head;
}

template < class T >
void deleteList(List< T >* head) noexcept
{
  while (head != nullptr) {
    List< T >* temp = head;
    head = head->next;
    delete temp;
  }
}

template < class T >
std::ostream& printList(std::ostream& out, List< T >* head)
{
  if (head != nullptr) {
    out << head->data;
    head = head->next;
    while (head != nullptr) {
      out << " " << head->data;
      head = head->next;
    }
  }
  return out;
}

template < class T >
List< T >* reverse_with_list(List< T >* head)
{
  if (head == nullptr) {
    return head;
  }
  List< List< T >* >* ref_head = nullptr;
  try {
    while (head != nullptr) {
      ref_head = new List< List< T >* >{head, ref_head};
      head = head->next;
    }
  } catch (const std::bad_alloc&) {
    deleteList(ref_head);
    throw;
  }
  List< T >* rev_list = ref_head->data;
  while (ref_head->next != nullptr) {
    ref_head->data->next = ref_head->next->data;
    List< List< T >* >* temp = ref_head;
    ref_head = ref_head->next;
    delete temp;
  }
  ref_head->data->next = nullptr;
  delete ref_head;
  return rev_list;
}

template < class T >
List< T >* reverse_cleanly(List< T >* head) noexcept
{
  List< T >* prev = nullptr;
  while (head != nullptr) {
    List< T >* temp = head->next;
    head->next = prev;
    prev = head;
    head = temp;
  }
  return prev;
}

template < class T >
List< T >* reverse_recursively(List< T >* head) noexcept
{
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  List< T >* new_head = reverse_recursively(head->next);
  head->next->next = head;
  head->next = nullptr;
  return new_head;
}

template < class T >
List< T >* inputList(std::istream& input)
{
  List< T >* list = nullptr;
  long value = 0;
  try {
    while (input >> value) {
      list = addElem(list, value);
    }
    if (!input.eof()) {
      throw std::invalid_argument("Invalid input data");
    }
  } catch (const std::exception&) {
    deleteList(list);
    throw;
  }
  return list;
}

int main(int argc, char* argv[])
{
  try {
    auto list = inputList< long >(std::cin);
    bool is_param_correct = true;
    if (argc > 1) {
      if (std::strcmp(argv[1], "0") == 0) {
        list = reverse_with_list(list);
      } else if (std::strcmp(argv[1], "1") == 0) {
        list = reverse_cleanly(list);
      } else if (std::strcmp(argv[1], "2") == 0) {
        list = reverse_recursively(list);
      } else {
        is_param_correct = false;
      }
    } else {
      is_param_correct = false;
    }
    if (!is_param_correct) {
      std::cerr << "Invalid params\n";
      list = reverse_cleanly(list);
    }
    printList(std::cout, list) << "\n";
    deleteList(list);
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
