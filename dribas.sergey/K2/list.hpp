#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <iostream>

namespace dribas
{
  struct FwdList {
    long unsigned int value;
    FwdList * next;
  };

  FwdList* insert(FwdList* head, int index, size_t count);
  FwdList* makeList(size_t size);
  void outList(std::ostream& out, FwdList* head);
  void clear(FwdList* head);
}

#endif
