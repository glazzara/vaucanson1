// k_ri.hxx
//
// MICAL_HEADER

#ifndef   K_RI_HXX_
# define   K_RI_HXX_

#include <algorithms/k_ri.hh>

#include <algorithms/make_pta.hh>
#include <algorithms/fusion.hh>
#include <set>
#include <utility>

namespace mical {

  using namespace vcsn;
  using std::set;
  using std::pair;

  template <typename A, typename T, typename Word>
  void
  k_ri(Element<A, T>& a, unsigned k, const set<Word>& sample)
  {
    bool flag = true;
    set<pair<hstate_t, hstate_t> > res;

    make_pta(a, sample);
    
    SAVE_AUTOMATON_DOT_SIMPLE("pta", a);

    unsigned count = 0;

    while(flag)
      {
	flag = false;
	if ((res = condition1(a, k)).size()) 
	  {
	    std::cout << "CONDITION 1 " 
		      <<  res.begin()->first << " | " <<  res.begin()->second
		      << std::endl;
	    fusion(a, res.begin()->first, res.begin()->second);
	    flag = true;
	  }
	else if ((res = condition2(a, k)).size()) 
	  {
	    std::cout << "CONDITION 2 "  
		      <<  res.begin()->first << " | " <<  res.begin()->second
		      << std::endl;
	    fusion(a, res.begin()->first, res.begin()->second);
	    flag = true;
	  }
	else if ((res = condition3(a, k)).size())
	  {
	    std::cout << "CONDITION 3 "  
		      <<  res.begin()->first << " | " <<  res.begin()->second
		      << std::endl;
	    fusion(a, res.begin()->first, res.begin()->second);
	    flag = true;
	  }
	SAVE_AUTOMATON_DOT_SIMPLE(count, a);
	count++;
      }
  }
  
  template <typename A, typename T>
  set<pair<hstate_t, hstate_t> > condition1(const Element<A, T>& a, unsigned k)
  {
    typedef Element<A, T> automaton_t;
    
    set<pair<hstate_t, hstate_t> > res; 

    for (typename automaton_t::state_iterator h = a.states().begin();
	 h != a.states().end(); h++)
      {
	set<hedge_t> delta_edge;
	
	a.deltac(delta_edge, *h, delta_kind::edges());	

// 	std::cout << "STATE " << *h << " NB_EDGES " 
// 		  << delta_edge.size()  << std::endl;
	
	for (typename set<hedge_t>::iterator i = delta_edge.begin();
	     i != delta_edge.end(); i++)
	  for (typename set<hedge_t>::iterator j = i;
	       j != delta_edge.end(); j++)
	    if (j != i)
	      if (a.label_of(*i) == a.label_of(*j))
		{
		  res.insert(pair<hstate_t, hstate_t>(a.aim_of(*i), a.aim_of(*j)));
		  return res;
		}
      }
    
    return res;
  }
  

  template <typename A, typename T>
  set<pair<hstate_t, hstate_t> > condition3(const Element<A, T>& a, unsigned k)
  {
    typedef Element<A, T> automaton_t;

    set<pair<hstate_t, hstate_t> > res;

    for (typename automaton_t::state_iterator h = a.states().begin();
	 h != a.states().end(); h++)
      for (typename automaton_t::monoid_t::alphabet_t::iterator 
	     i = a.series().monoid().alphabet().begin();
	   i != a.series().monoid().alphabet().end(); i++)
	{	
	  set<hedge_t> delta_edge;
	  
	  a.letter_rdeltac(delta_edge, *h, *i, delta_kind::edges());
	  
	  for (typename set<hedge_t>::iterator j = delta_edge.begin();
	       j != delta_edge.end(); j++)
	    for (typename set<hedge_t>::iterator l = j;
		 l != delta_edge.end(); l++)
	      if (j != l)
	      {
		set<typename automaton_t::monoid_elt_t> kset1, kset2, inter;
		
		search_prefix(a, a.origin_of(*j), k, kset1);
		search_prefix(a, a.origin_of(*l), k, kset2);
		
		set_intersection(kset1.begin(), kset1.end(),
				 kset2.begin(), kset2.end(),
				 inserter(inter, inter.begin()));
		
		if (inter.size())
		  {
		    res.insert(pair<hstate_t, hstate_t>(a.origin_of(*j), 
							a.origin_of(*l)));
		    return res;
		  }
	      }
	}
    
    return res;
  }
  
  template <typename A, typename T>
  set<pair<hstate_t, hstate_t> > condition2(const Element<A, T>& a, unsigned k)
  {
    typedef Element<A, T> automaton_t;

    set<pair<hstate_t, hstate_t> > res;

    for (typename automaton_t::final_iterator i = a.final().begin();
	 i != a.final().end(); i++)
      for (typename automaton_t::final_iterator j = i;
	   j != a.final().end(); j++)
	if (j != i)
	  {
	    set<typename automaton_t::monoid_elt_t> kset1, kset2, inter;
	    
	    search_prefix(a, *i, k, kset1);
	    search_prefix(a, *j, k, kset2);

	    set_intersection(kset1.begin(), kset1.end(),
			     kset2.begin(), kset2.end(),
			     inserter(inter, inter.begin()));
	    
	    if (inter.size())
	      {
		res.insert(pair<hstate_t, hstate_t>(*i, *j));
		return res;
	      }
	  }

    return res;
  }

  template <typename A, typename T>
  void search_prefix(const Element<A, T>& a, 
		     hstate_t current, 
		     unsigned k,
		     set<typename Element<A, T>::monoid_elt_t>& res)
  {
    typename Element<A, T>::monoid_elt_t str;
    
    search_prefix_(a, current, 0, k, str, res);
  }

  template <typename A, typename T>
  void search_prefix_(const Element<A, T>& a, 
		      hstate_t current, 
		      unsigned actual,
		      unsigned k,
		      typename Element<A, T>::monoid_elt_t& str,
		      set<typename Element<A, T>::monoid_elt_t>& res)
  {
    typedef typename Element<A, T>::monoid_elt_t Word;

    if (actual == k)
      {
	res.insert(str);
      }
    else
      {
	set<hedge_t> delta_edge;
	
	a.rdeltac(delta_edge, current, delta_kind::edges());
	
	for (typename set<hedge_t>::iterator i = delta_edge.begin();
	     i != delta_edge.end(); i++)
	  {
	    Word svg = str;
	    str = str * a.label_of(*i).begin()->first;
	    
	    search_prefix_(a, a.origin_of(*i), actual + 1, k, str, res);

	    str = svg;
	  }
      }
  }

} // mical

#endif /* !K_RI_HXX_ */
