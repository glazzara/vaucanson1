// is_kreversible.hh
//
// MICAL_HEADER

#ifndef   IS_KREVERSIBLE_HH_
# define   IS_KREVERSIBLE_HH_

#include <vaucanson/fundamental/element.hh>

namespace mical {

  template <class A, class T>
  bool is_kreversible(const Element<A, T>& a, unsigned k);

} // mical

#include <algorithms/is_kreversible.hxx>

#endif /* !IS_KREVERSIBLE_HH_ */
