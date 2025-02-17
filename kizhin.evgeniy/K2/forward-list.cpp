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

kizhin::FwdList* kizhin::insertDuplicates(FwdList* const position, const std::size_t size)
{
  assert(size != 0 && position != nullptr);
  FwdList* first = new FwdList{ position->value, nullptr };
  FwdList* last = first;
  try {
    for (std::size_t i = 1; i != size; ++i) {
      FwdList* newNode = new FwdList{ position->value, nullptr };
      last->next = newNode;
      last = newNode;
    }
  } catch (...) {
    clear(first);
    throw;
  }
  FwdList* originalNext = position->next;
  position->next = first;
  last->next = originalNext;
  return position;
}

const kizhin::FwdList* kizhin::getNodeByIndex(const FwdList* head,
    const std::size_t index)
{
  assert(head != nullptr);
  for (std::size_t i = 0; i != index; ++i) {
    head = head->next;
  }
  return head;
}

kizhin::FwdList* kizhin::getNodeByIndex(FwdList* head, const std::size_t index)
{
  const FwdList* constHead = head;
  return const_cast< FwdList* >(getNodeByIndex(constHead, index));
}

void kizhin::clear(FwdList* head) noexcept
{
  FwdList* tmp = nullptr;
  while (head != nullptr) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
}

std::ostream& kizhin::outputList(std::ostream& out, const FwdList* head)
{
  assert(head);
  out << head->value;
  head = head->next;
  while (head) {
    out << ' ' << head->value;
    head = head->next;
  }
  return out;
}

