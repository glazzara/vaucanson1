// k_tssi.hh
// 
// MICAL_HEADER

#ifndef   K_TSSI_HH_
# define   K_TSSI_HH_

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

#include <set>

namespace mical {

  using namespace vcsn;
  using std::set;

  template <typename A, typename T, typename Word>
  void
  k_tssi(Element<A, T>& a, unsigned k, const set<Word>& sample);

} // mical

#include <algorithms/k_tssi.hxx>

#endif /* !K_TSSI_HH_ */
