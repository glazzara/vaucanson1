// is_kdeterministic.hh
//
// MICAL_HEADER

#ifndef   IS_KDETERMINISTIC_HH_
# define   IS_KDETERMINISTIC_HH_

#include <vaucanson/fundamental/element.hh>

namespace mical {

  template <class A, class T>
  bool is_kdeterministic(const Element<A, T>& a, unsigned k);

} // mical

#include <algorithms/is_kdeterministic.hxx>

#endif /* !IS_KDETERMINISTIC_HH_ */
