// k_ri.hh
//
// MICAL_HEADER

#ifndef   K_RI_HH_
# define   K_RI_HH_

#include <set>

namespace mical {

  using namespace vcsn;
  using std::set;

  template <typename A, typename T, typename Word>
  void
  k_ri(Element<A, T>& a, unsigned k, const set<Word>& sample);

} // mical

#include <algorithms/k_ri.hxx>


#endif /* !K_RI_HH_ */
