// is_kdeterministic.hxx
//
// MICAL_HEADER

#ifndef   IS_KDETERMINISTIC_HXX_
# define   IS_KDETERMINISTIC_HXX_

#include <vaucanson/fundamental/element.hh>

#include <algorithms/is_kdeterministic.hh>

#include <set>
#include <utility>

using namespace vcsn;
using std::pair;
using std::set;

namespace mical {

  // deterministic with anticipation k
  template <class A, class T>
  bool is_kdeterministic(const Element<A, T>& a, unsigned k)
  {
    typedef Element<A, T> automaton_t;

    for (typename automaton_t::state_iterator i = a.states().begin();
	 i != a.states().end(); i++)
      {
	bool res = true;
	typename Element<A, T>::monoid_elt_t str;
	set<pair<typename Element<A, T>::monoid_elt_t, hstate_t> > acu;
	set<hstate_t> marked;

	std::cout << "NEW_STATE ---------" << std::endl;

	kanticip(a, *i, 0, k, str, acu, marked, res);
	if (!res)
	  return false;
      }
    
    return true;
  }
  
  template <typename A, typename T>
  void kanticip(const Element<A, T>& a, 
		hstate_t current, 
		unsigned actual,
		unsigned k,
		typename Element<A, T>::monoid_elt_t& str,
		set<pair<typename Element<A, T>::monoid_elt_t, hstate_t> >& acu,
		set<hstate_t>& marked,
		bool& res)
  {
    typedef typename Element<A, T>::monoid_elt_t Word;
    typedef set<pair<Word, hstate_t> > word_state_t;

    std::cout << "STATE : " << current << " STR : " << str << std::endl;
    
    if (actual > k)
      {
	if (!acu.size())
	  acu.insert(pair<Word, hstate_t>(str, current));
	else
	  {
	  for (typename word_state_t::iterator i = acu.begin();
	       i != acu.end(); i++)
	    {
	      std::cout << i->first 
			<< " | " << i->second 
			<< " | " << (i->first == str) << std::endl;
	      if ((i->first == str) && (i->second != current))
		res = false;
	    }
	  if (!res)
	    {
	      std::cout << "yep" << std::endl;
	      return;
	    }
	  else
	    acu.insert(pair<Word, hstate_t>(str, current));
	  }
      }
    if (find(marked.begin(), marked.end(), current) != marked.end())
      return;

    marked.insert(current);
    
    set<hedge_t> delta_edge;
    
    a.deltac(delta_edge, current, delta_kind::edges());
	
    for (typename set<hedge_t>::iterator i = delta_edge.begin();
	 i != delta_edge.end(); i++)
      {
	  Word svg = str;
	  str = str * a.label_of(*i).begin()->first;
	  
	  kanticip(a, a.aim_of(*i), actual + 1, k, str, acu, marked, res);
	      
	  if (res == false)
	    return;
	  
	  str = svg;
      }
  }


} // mical


#endif /* !IS_KDETERMINISTIC_HXX_ */
