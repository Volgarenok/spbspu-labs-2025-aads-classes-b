#include "forward-list.hpp"
#include <cassert>
#include <iostream>

kizhin::FwdList* kizhin::initList(int start, const int stop)
{
  FwdList* head = new FwdList{ start++, nullptr };
  FwdList* current = head;
  try {
    for (; start != stop; ++start) {
      current->next = new FwdList{ start, nullptr };
      current = current->next;
    }
  } catch (...) {
    clear(head);
    throw;
  }
  return head;
}

kizhin::FwdList* kizhin::insertDuplicates(FwdList* const head, const std::size_t position,
    const std::size_t size)
{
  assert(size != 0);
  FwdList* target = head;
  for (std::size_t i = 0; target != nullptr && i != position; ++i) {
    target = target->next;
  }
  if (target == nullptr) {
    throw std::logic_error("Failed to find position node");
  }
  FwdList* first = new FwdList{ target->value, nullptr };
  FwdList* last = first;
  try {
    for (std::size_t i = 1; i != size; ++i) {
      FwdList* newNode = new FwdList{ target->value, nullptr };
      last->next = newNode;
      last = newNode;
    }
  } catch (...) {
    clear(first);
    throw;
  }
  FwdList* originalNext = target->next;
  target->next = first;
  last->next = originalNext;
  return target;
}

void kizhin::clear(FwdList* head) noexcept
{
  if (head == nullptr) {
    return;
  }
  FwdList* tmp = head;
  while (head->next) {
    tmp = head->next;
    delete head;
    head = tmp;
  }
  delete head;
}

std::ostream& kizhin::outputList(std::ostream& out, FwdList* list)
{
  assert(list);
  FwdList* current = list;
  out << current->value;
  current = current->next;
  while (current) {
    out << ' ' << current->value;
    current = current->next;
  }
  return out;
}

