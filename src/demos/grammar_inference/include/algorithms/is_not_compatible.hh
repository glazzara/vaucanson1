// is_not_compatible.hh

#ifndef IS_NOT_COMPATIBLE_HH
#define IS_NOT_COMPATIBLE_HH

#include <set>
#include <vaucanson/fundamental/element.hh>

namespace vcsn {

  // using namespace vcsn;
  // using namespace vcsn::algebra;

  template<typename A, typename T, typename W>
  bool
  is_not_compatible(const Element<A, T>& a, 
		    const std::set<W>& sample);

  
  template<typename A, typename T>
  bool
  is_not_compatible(const Element<A, T>& a,
		    const Element<A, T>& pta);


} // gi

#include <algorithms/is_not_compatible.hxx>

#endif
