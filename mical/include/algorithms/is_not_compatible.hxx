// is_not_compatible.hxx

#ifndef IS_NOT_COMPATIBLE_HXX
#define IS_NOT_COMPATIBLE_HXX

#include <algorithms/is_not_compatible.hh>

#include <set>
#include <vaucanson/algorithms/compute.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/trim.hh>

namespace vcsn {

  template<typename A, typename T, typename W>
  bool
  is_not_compatible(const Element<A, T>& a, const std::set<W>& sample)
  {
    typedef typename std::set<W> sample_set_t;

    for (typename sample_set_t::const_iterator i = sample.begin();
	 i != sample.end(); ++i)
      if (compute(a, *i))
	return false;
    
    return true;
  }
  
  template<typename A, typename T>
  bool
  is_not_compatible(const Element<A, T>& a,
		    const Element<A, T>& pta)
  {
    return (useful_states((auto_product(a, pta))).size() == 0);
  }

//   bool
//   do_is_not_compatible(const Element<A, T>& a,
// 		       hstate_t a_from,
// 		       const Element<A, T>& pta)
//   {
//     typedef typename std::set<hedge_t>    delta_ret_t;
//     typedef typename std::queue<state_t>  fifo_state_t;

//     // pta have only one intial state
//     hstate_t pta_from = *pta.begin(), pta_to, a_to;
//     delta_ret_t pta_delta_ret, a_delta_ret;
//     fifo_state_t fifo_state;

//     fifo_state.push(a_from);
//     do
//       { 
// 	a_from = fifo_state.front();
// 	fifo_state.pop()
	  
// 	pta.deltac(pta_delta_ret, pta_from, delta_kind::edges());
// 	a.deltac(a_delta_ret, a_from, delta_kind::edges());

	

// 	for (delta_ret_t::iterator j = pta_delta_ret.begin(); 
// 	     j != pta_delta_ret.end(); ++j)
// 	  {
	    
// 	  }
	

//       } while (fifo_state.size())    
//   }
    

} // gi

#endif
