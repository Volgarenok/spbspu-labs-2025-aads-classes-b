#ifndef SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K2_FORWARD_LIST_HPP
#define SPBSPU_LABS_2025_AADS_CLASSES_B_KIZHIN_EVGENIY_K2_FORWARD_LIST_HPP

#include <iosfwd>

namespace kizhin {
  struct FwdList
  {
    int value;
    FwdList* next;
  };

  FwdList* initList(int start, int stop);
  FwdList* insertDuplicates(FwdList*, std::size_t);
  const FwdList* getNodeByIndex(const FwdList*, std::size_t);
  FwdList* getNodeByIndex(FwdList*, std::size_t);
  void clear(FwdList*) noexcept;
  std::ostream& outputList(std::ostream&, const FwdList*);
}

#endif

