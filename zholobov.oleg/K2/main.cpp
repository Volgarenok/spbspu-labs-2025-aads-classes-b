#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

void del_list(FwdList* list) noexcept
{
  while (list != nullptr) {
    FwdList* next = list->next;
    delete list;
    list = next;
  }
}

FwdList* add_duplicates(FwdList* head, size_t idx, size_t num)
{
  if (num == 0) {
    throw std::out_of_range("index should be greater than 0");
  }

  while ((--idx != 0) || (head == nullptr)) {
    head = head->next;
  }

  if (head == nullptr) {
    throw std::out_of_range("index greater than number of elements in the list");
  }

  while (num-- != 0) {
    FwdList* new_elem = new FwdList;
    new_elem->value = head->value;
    new_elem->next = head->next;
    head->next = new_elem;
  }
  return head;
}

void print_list(const FwdList* list) noexcept
{
  while (list != nullptr) {
    std::cout << list->value << " ";
    list = list->next;
  }
}

int main()
{
  FwdList* list = nullptr;
  try {
    for (size_t i = 0; i < 10; ++i) {
      FwdList* cur = new FwdList;
      cur->value = 9 - i;
      cur->next = list;
      list = cur;
    }
    while (!std::cin.eof()) {
      size_t idx = 0;
      size_t num = 0;
      if (!(std::cin >> idx >> num)) {
        break;
      }
      add_duplicates(list, idx, num);
    }
  } catch (const std::out_of_range& e) {
    std::cerr << e.what() << "\n";
    del_list(list);
    return 1;
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << "\n";
    del_list(list);
  }
  print_list(list);
  std::cout << "\n";
  del_list(list);
  return 0;
}
