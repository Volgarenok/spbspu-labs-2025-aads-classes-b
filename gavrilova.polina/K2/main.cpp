#include <iostream>

struct FwdList {
  int value;
  FwdList * next;
};

FwdList* dublicate(FwdList* head, size_t for_dubl, size_t number);
FwdList* createList(FwdList* head, int size);
std::pair< FwdList*, FwdList* > createList(FwdList* head, int size, int value);
void clear(FwdList* head);
void outList(FwdList* head);

int main()
{
  FwdList* head = nullptr;
  try {
    head = createList(head, 10);
  } catch(const std::bad_alloc &) {
    std::cerr << "Memory error!";
    return 1;
  }
  FwdList* origin_head = head;

  while (!std::cin.eof()) {
    size_t for_dubl = 0;
    size_t num = 0;
    if (!(std::cin >> for_dubl >> num)) {
      break;
    }
    if (for_dubl == 0) {
      clear(origin_head);
      return 1;
    }
    try {
      head = dublicate(origin_head, for_dubl, num);
    } catch(const std::exception& e) {
      std::cerr << e.what();
      clear(origin_head);
      return 1;
    }
  }

  outList(origin_head);
  clear(origin_head);
}

FwdList* createList(FwdList * head, int size)
{
  head = new FwdList{0, nullptr};
  FwdList* cur = head;
  for (int i = 1; i < size; ++i) {
    try {
      cur->next = new FwdList{i, nullptr};
      cur = cur->next;
    } catch(const std::bad_alloc&) {
      cur->next = nullptr;
      clear(head);
      throw;
    }
  }
  return head;
}

std::pair< FwdList*, FwdList* > createList(int size, int value)
{
  FwdList* head = new FwdList{value, nullptr};
  FwdList* cur = head;
  for (int i = 1; i < size; ++i) {
    try {
      cur->next = new FwdList{value, nullptr};
      cur = cur->next;
    } catch(const std::bad_alloc&) {
      cur->next = nullptr;
      clear(head);
      throw;
    }
  }
  return {head, cur};
}

FwdList* dublicate(FwdList* head, size_t for_dubl, size_t number)
{
  for (size_t i = 0; i < (for_dubl - 1); ++i) {
    head = head->next;
    if (!head) {
      throw std::out_of_range("!");
    }
  }
  auto node = createList(number, head->value);
  node.second->next = head->next;
  head->next = node.first;
  return head;
}

void clear(FwdList* head)
{
  while (head) {
    FwdList * new_head = head->next;
    delete head;
    head = new_head;
  }

}

void outList(FwdList* head) {
  if (!head) return;
  std::cout << head->value;
  while (head->next) {
    std::cout << " ";
    std::cout << head->next->value;
    head = head->next;
  }
  std::cout << "\n";
}
