

#ifndef MAKE_PTA_HH
#define MAKE_PTA_HH

#include <set>
#include <vaucanson/fundamental/element.hh>

namespace gi {

  template<typename A, typename T, typename W>
  void
  make_pta(Element<A, T>& a, const std::set<W>& sample);

  template<typename A, typename T>
  Element<T, A>
  pta_from_mca(const Element<T, A>& mca);
  
} // gi

#include <algorithms/make_pta.hxx>

#endif
