
#ifndef   IS_STRUCTURALLY_COMPLETE_HH_
# define   IS_STRUCTURALLY_COMPLETE_HH_

#include <iostream>
#include <set>

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>


namespace vcsn {

  template<typename A, typename T>
  bool
  is_structurally_complete(const Element<A, T>& a, 
			   std::set<Word> sample);
  
  
} // vcsn


#endif /* !IS_STRUCTURALLY_COMPLETE_HH_ */
