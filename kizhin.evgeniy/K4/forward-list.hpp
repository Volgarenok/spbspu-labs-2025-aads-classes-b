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
    if (head == nullptr) {
      return head;
    }
    using StackNode = FwdList< FwdList< T >* >;
    StackNode* stack_head = nullptr;
    FwdList< T >* current = head;
    try {
      while (current != nullptr) {
        stack_head = new StackNode{ current, stack_head };
        current = current->next;
      }
    } catch (...) {
      clear(stack_head);
      throw;
    }
    FwdList< T >* new_head = stack_head->value;
    StackNode* stack_current = stack_head;
    current = new_head;
    while (stack_current != nullptr) {
      StackNode* next_stack = stack_current->next;
      current->next = next_stack ? next_stack->value : nullptr;
      current = current->next;
      stack_current = next_stack;
    }
    clear(stack_head);
    return new_head;
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
