
#ifndef   IS_STRUCTURALLY_COMPLETE_HXX_
# define   IS_STRUCTURALLY_COMPLETE_HXX_

#include <iostream>
#include <set>

#include <vaucanson/algebra/concrete/free_monoid/predefs.hh>
#include <vaucanson/algorithm/trim.hh>

namespace vcsn {

  template<typename A, typename T, typename W>
  bool
  is_structurally_complete(const Element<A, T>& a, 
			   std::set<W> sample)
  {
    typedef typename std::set<W> samples_t;
    typedef typename std::set<hedge_t> delta_ret_t;

    delta_ret_t res;

    for (samples_t::const_iterator i = sample.begin();
	 i != sample.end(); ++i)
      {
	
	for (samples_t::const_iterator j = i->begin();
	     j != i->end(); ++j)
	  {


	    
	    for (typename auto_t::initial_iterator i = a.initial().begin();
		 i != a.initial().end(); ++i)
	      v1[*i] = a.get_initial(*i);
	  }

	
      }
  }
  
  
} // vcsn


#endif /* !IS_STRUCTURALLY_COMPLETE_HXX_ */
