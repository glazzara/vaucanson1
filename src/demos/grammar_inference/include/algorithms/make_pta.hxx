
#ifndef MAKE_PTA_HXX
#define MAKE_PTA_HXX

#include <set>
#include <algorithms/make_pta.hh>
#include <vaucanson/fundamental/element.hh>
#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/algorithms/determinize.hh>

namespace gi {

  using namespace vcsn;
  using namespace vcsn::algebra;

  template<typename A, typename T, typename W>
  void
  make_pta(Element<A, T>& a, const std::set<W>& sample)
  {
    typedef W                    word_t;
    typedef std::set<W> sample_set_t;
    typedef std::set<hedge_t>    delta_ret_t;

    // FIXME : 
    // 1°) static check for W 
    // 2°) static check between W's letters and labels of automaton

    hstate_t init = a.add_state();
    a.set_initial(init);

    for (typename sample_set_t::iterator i = sample.begin(); 
	 i != sample.end(); ++i)
      {
	hstate_t from = init;
	hstate_t to;
	delta_ret_t res;
	bool flag;
    
	for (typename word_t::const_iterator j = i->begin(); j != i->end(); ++j)
	  {
	    hstate_t ret;
	    flag = true;
	    
	    res.clear();
	    a.deltac(res, from, delta_kind::edges());
	    for (delta_ret_t::iterator k = res.begin(); k != res.end(); ++k)
	      {
		if (*a.label_of(*k).begin()->first.begin() == *j)
 		  {
 		    flag = false;
 		    ret = a.aim_of(*k);
 		  }
	      }
	    
 	    if (flag)
 	      {
		to = a.add_state();
		a.add_letter_edge(from, to, *j);
 	      }
	    else 
	      to = ret;
	    
	    from = to;
	  }
	a.set_final(to);
      }
  }
  

  template<typename A, typename T>
  Element<T, A>
  pta_from_mca(const Element<T, A>& mca)
  {
    // FIXME
  }
  

} // gi

#endif
