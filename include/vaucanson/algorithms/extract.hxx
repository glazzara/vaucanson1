/**************************************
 * <vaucanson/algorithms/extract.hxx> *
 **************************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef ALGORITHMS_EXTRACT_HXX
# define ALGORITHMS_EXTRACT_HXX

# include <vaucanson/algorithms/extract.hh>

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*----------------------------------------.
  | SubAutomaton defined by a set of states |
  `----------------------------------------*/
 
  template<typename A, typename auto_t, typename list_t>
  void auto_do_extract(const AutomataBase<A>& a_set, 
		       auto_t& a,
		       const list_t& selected, 
		       bool check_states)
  {
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end();
	 ++i)
      if (selected.find(*i) == selected.end()) // this state has to be removed
	{
	  if (check_states)
	    {
	      if (a.has_state(*i))
		a.safe_del_state(*i);
	    }
	  else
	    a.safe_del_state(*i);
	}
  }


  // wrapper:
  template<typename A, typename T, typename StatesSet>
  Element<A, T> 
  auto_extract(const Element<A, T>& a, const StatesSet& s, bool check_states = true)
  { 
    Element<A, T> ret(a);
    ret.emancipate();
    auto_do_extract(ret.set(), ret, s, check_states);
    return ret;
  }

  template<typename A, typename T, typename StatesSet>
  void auto_in_extract(Element<A, T>& a, const StatesSet& s, bool check_states = true)
  {
    auto_do_extract(a.set(), a, s, check_states);
  }
  
} // vcsn

#endif // ALGO_EXTRACT_HXX
