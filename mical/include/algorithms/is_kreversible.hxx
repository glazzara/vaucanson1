// is_kreversible.hxx
//
// MICAL_HEADER

#ifndef   IS_KREVERSIBLE_HXX_
# define   IS_KREVERSIBLE_HXX_

#include <vaucanson/fundamental/element.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/transpose.hh>

#include <algorithms/is_kdeterministic.hh>

#include <algorithms/is_kreversible.hh>

using namespace vcsn;

namespace mical {

  template <class A, class T>
  bool is_kreversible(const Element<A, T>& a, unsigned k)
  {
    typedef Element<A, T> automaton_t;

    return (is_deterministic(a) && is_kdeterministic(auto_transpose(a), k));
  }


} // mical


#endif /* !IS_KREVERSIBLE_HXX_ */
