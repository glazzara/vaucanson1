
#ifndef MAKE_MCA_HH
#define MAKE_MCA_HH

#include <set>
#include <vaucanson/fundamental/element.hh>

namespace gi {

  using namespace vcsn;

  template<typename A, typename T, typename W>
  void
  make_mca(Element<A, T>& a, const std::set<W>& sample);
  
} // gi

#include <algorithms/make_mca.hxx>

#endif
