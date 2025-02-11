#include "list.hpp"

dribas::FwdList* dribas::insert(FwdList* head, int index, size_t count)
{
    if (index < 1) {
      throw std::out_of_range("index is out of range");
    }
    FwdList* current = head;
    for (int i = 1; i < index && current != nullptr; ++i) {
      current = current->next;
    }
    if (!current) {
      throw std::out_of_range("index is out of range");
    }
    for (size_t i = 0; i < count; i++) {
      FwdList* newNode = new FwdList{current->value, current->next};
      current->next = newNode;
      current = newNode;
    }
    return head;
}

dribas::FwdList* dribas::makeList(FwdList* head, int size)
{
  try {
    head = new FwdList {0, nullptr};
    FwdList* current = head;
    for (int i = 1; i < size; i++) {
      current->next = new FwdList {i, nullptr};
      current = current->next;
    }
  } catch (...) {
    throw;
  }
  return head;
}

void dribas::outList(std::ostream& out, FwdList* head)
{
  if (head) {
    out << head->value;
    head = head->next;
    while (head) {
      out << " " << head->value;
      head = head->next;
    }
  }
}

void dribas::clear(FwdList* head)
{
  FwdList* interim = head;
  while (head) {
    interim = head->next;
    delete head;
    head = interim;
  }
}
