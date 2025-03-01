#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

namespace dribas
{
  template< class T >
  struct List {
    T data;
    List< T > * next;
  };

  template< class T >
  List< T > * reverse_with_list(List< T > * head);
  template< class T >
  List< T > * reverse_cleanly(List< T > * head) noexcept;
  template< class T>
  List< T > * reverse_recursively(List< T > * head) noexcept;

  template< class T >
  List< T > * input(List < T > * head, std::istream & in);

  template < class T >
  void clear(List < T > * head);

  template< class T >
  void outputList(std::ostream& out, List< T > * head);
}

#endif