
#ifndef FUSION_HXX
#define FUSION_HXX

#include <assert.h>

#include <tools/predefs.hh>

namespace mical {

  template<typename A, typename T>
  void
  fusion(Element<A, T>& a, 
	 hstate_t lhs,
	 hstate_t rhs)
  {
    typedef typename std::set<hedge_t> delta_ret_t;

    delta_ret_t delta_ret;
   
    if (!a.has_state(lhs) || !a.has_state(rhs) || rhs == lhs)
      return;
    
    a.deltac(delta_ret, lhs, delta_kind::edges());
    a.rdeltac(delta_ret, lhs, delta_kind::edges());
    for (typename delta_ret_t::const_iterator i = delta_ret.begin();
	   i != delta_ret.end(); i++)
      {
	if (a.aim_of(*i) == lhs)
	  if (a.origin_of(*i) != lhs)
	    add_edge(a, a.origin_of(*i), rhs, a.label_of(*i));
	  else
	    add_edge(a, rhs, rhs, a.label_of(*i));
	else
	  if (a.origin_of(*i) == lhs)
	    if (a.aim_of(*i) != rhs)
	      add_edge(a, rhs, a.aim_of(*i), a.label_of(*i));
	    else
	      add_edge(a, rhs, rhs, a.label_of(*i));
	  else
	    assert(0); // something is wrong ...
	
	a.del_edge(*i);
      }

    if (a.is_initial(lhs))
      a.set_initial(rhs);
    
    if (a.is_final(lhs))
      a.set_final(rhs);
    
    a.del_state(lhs);
  }

  template<typename A, typename T>
  Element<A, T>
  get_fusion(const Element<A, T>& a, 
	     hstate_t lhs,
	     hstate_t rhs)
  {
    Element<A, T> res = a;

    fusion(res, lhs, rhs);
    return res;
  }


} // mical

#endif
