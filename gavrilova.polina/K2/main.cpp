#include <iostream>

struct FwdList {
  int value;
  FwdList * next;
};

FwdList* dublicate(FwdList* head, size_t for_dubl, size_t number);
FwdList* createList(FwdList* head, int size);
void clear(FwdList* head, size_t size);
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
    };
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
      clear(head, i);
      throw;
    }
  }
  return head;
}

FwdList* dublicate(FwdList* head, size_t for_dubl, size_t number)
{
  for (size_t i = 0; i < (for_dubl - 1); ++i) {
    head = head->next;
    if (!head) {
      throw std::out_of_range("!");
    }
  }

  FwdList* cur = head;
  FwdList* original_next = nullptr;
  if (cur->next) {
    original_next = cur->next;
  }

  for (size_t i = 0; i < number; ++i) {
    FwdList* node = nullptr;
    try {
      node = new FwdList{cur->value, nullptr};
    } catch(const std::bad_alloc&) {
      clear(head->next, i);
      head->next = original_next;
      throw;
    }
    node->next = cur->next;
    cur->next = node;
    cur = node;
  }
  return head;
}

void clear(FwdList* head, size_t size)
{
  if (!head) return;
  FwdList* new_head = head->next;
  for (size_t i =0; i < size; ++i) {
    if (head) {
      delete head;
      head = new_head;
      new_head = head->next;
    }
  }
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
