#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K4_FORWARD_LIST_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K4_FORWARD_LIST_HPP

namespace kizhin {
  template < typename T >
  struct FwdList
  {
    T value;
    FwdList* next;
  };

  template < typename T >
  void clear(FwdList< T >* head) noexcept
  {
    FwdList< T >* tmp = nullptr;
    while (head != nullptr) {
      tmp = head;
      head = head->next;
      delete tmp;
    }
  }

  template < class T >
  FwdList< T >* reverseWithList(FwdList< T >* head)
  {
    FwdList< T >* stack = nullptr;
    while (head != nullptr) {
      FwdList< T >* nextNode = head->next;
      head->next = stack;
      stack = head;
      head = nextNode;
    }
    return stack;
  }

  template < class T >
  FwdList< T >* reverseCleanly(FwdList< T >* head) noexcept
  {
    FwdList< T >* prev = nullptr;
    FwdList< T >* curr = head;
    while (curr != nullptr) {
      FwdList< T >* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }

  template < class T >
  FwdList< T >* reverseRecursively(FwdList< T >* head) noexcept
  {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }
    FwdList< T >* rest = reverseRecursively(head->next);
    head->next->next = head;
    head->next = nullptr;
    return rest;
  }
}

#endif
