// complete.hxx
// 
// $Id$
// VCSN_HEADER

# include <set>

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complete(Element<A, T>& work)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t puits = work.add_state();

    for (state_iterator i = work.states().begin();
	 i != work.states().end(); i++)
      {
	std::set<hstate_t> aim;
	alphabet_t& alpha = work.series().monoid().alphabet();
	for (alphabet_iterator j = alpha.begin();
	     j != alpha.end(); j++)
	  {
	    aim.clear();
	    work.letter_deltac(aim, *i, *j, delta_kind::states());
	  
	    if (!aim.size())
	      work.add_letter_edge(*i, puits, *j);
	  }
	
      }
  }

  
  template <typename A, typename T>
  Element<A, T>
  auto_complete(const Element<A, T>& e)
  {
    Element<A, T> res(e);
    res.emancipate();
    auto_in_complete(res);
    return res;
  }

} //vcsn
