
#ifndef MAKE_MCA_HXX
#define MAKE_MCA_HXX

#include <set>
#include <vaucanson/fundamental/element.hh>
#include <vaucanson/automata/concept/automata_base.hh>


#include <algorithms/make_mca.hh>

namespace gi {

  using namespace vcsn;
  using namespace vcsn::algebra;

  template<typename A, typename T, typename W>
  void
  make_mca(Element<A, T>& a, const std::set<W>& sample)
  {
    typedef W word_t;
    typedef std::set<W> sample_set_t;

    // FIXME : 
    // 1°) static check for W 
    // 2°) static check between W's letters and labels of automaton

    a.set_initial(a.add_state());

    for (typename sample_set_t::iterator i = sample.begin(); 
	 i != sample.end(); ++i)
      {
	hstate_t from = *a.initial().begin();    
	hstate_t to;
	for (typename word_t::const_iterator j = i->begin(); j != i->end(); ++j)
	  {
	    to = a.add_state();
	    a.add_letter_edge(from, to, *j);
	    from = to;
	  }
	a.set_final(to);
      }
      
  }
  
} // gi

#endif
