
#ifndef   IS_STRUCTURALLY_COMPLETE_HH_
# define   IS_STRUCTURALLY_COMPLETE_HH_

#include <set>

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>

using namespace vcsn;

namespace mical { 

  template<typename A, typename T, typename W>
  bool
  is_structurally_complete(const Element<A, T>& a, 
			   std::set<W> sample);
  
  
} // mical

#include <algorithms/is_structurally_complete.hxx>

#endif /* !IS_STRUCTURALLY_COMPLETE_HH_ */
