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
  if (idx == 0) {
    throw std::out_of_range("index should be greater than 0");
  }

  while ((--idx != 0) && (head != nullptr)) {
    head = head->next;
  }

  if (head == nullptr) {
    throw std::out_of_range("index greater than number of elements in the list");
  }

  while (num-- != 0) {
    FwdList* new_elem = new FwdList{head->value, head->next};
    head->next = new_elem;
  }
  return head;
}

void print_list(const FwdList* list) noexcept
{
  if (list != nullptr) {
    std::cout << list->value;
    while ((list = list->next) != nullptr) {
      std::cout << " " << list->value;
    }
  }
}

int main()
{
  FwdList* list = nullptr;
  try {
    for (int i = 0; i < 10; ++i) {
      FwdList* cur = new FwdList{9 - i, list};
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
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    del_list(list);
    return 1;
  }
  print_list(list);
  std::cout << "\n";
  del_list(list);
  return 0;
}
