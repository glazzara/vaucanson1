// get_structcomp_sample.hh
//
// MICAL_HEADER

#ifndef   GET_STRUCTCOMP_SAMPLE_HH_
# define   GET_STRUCTCOMP_SAMPLE_HH_

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

#include <set>
#include <utility>

using namespace vcsn;

using std::set;
using std::pair;

namespace mical { 

  template<typename A, typename T, typename W>
  void
  get_structcomp_sample(const Element<A, T>& a, 
			W str,
			hstate_t current,
			pair<set<hedge_t>, set<hstate_t> >& used,
			std::set<W>& sample);
  

} // mical

#include <algorithms/get_structcomp_sample.hxx>

#endif /* !GET_STRUCTCOMP_SAMPLE_HH_ */
