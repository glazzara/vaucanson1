// determinize.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ALGO_DETERMINIZE_HXX
# define ALGO_DETERMINIZE_HXX

# include <map>
# include <set>
# include <queue>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/history.hh>
# include <vaucanson/algorithms/reachable.hh>

namespace vcsn {

  /*--------------------.
  | subset_construction |
  `--------------------*/
  // preconditions : 
  //    - output has been initialized with good series set 
  //      (alphabet is well initialized) ;
  //    - this algorithm is intended to work with realtime automaton 
  //      over |B<A*> => add concept checking.
  //

  template <typename A, typename input_t, typename output_t>
  void 
  do_subset_construction(const AutomataBase<A>&	a_set,
			 output_t&	       	output,
			 const input_t&		input)
  {    
    typedef typename input_t::series_t			    series_t;
    typedef typename series_t::monoid_t			    monoid_t;
    typedef typename std::set<hstate_t>	                    subset_t;

    typedef typename std::map<subset_t, hstate_t>           subset_set_t;
    typedef std::pair<subset_t, hstate_t>		    subset_set_pair_t;
   
    // FIXME : here we assume monoid is a free monoid -> concept checking ?
    typedef typename monoid_t::alphabet_t		    alphabet_t;
    typedef typename alphabet_t::letter_t		    letter_t;

    typedef subset_t					    delta_ret_t;
    
    hstate_t		   qi_hstate = output.add_state();
    subset_t		   qi;
    subset_set_t	   subset_set; 
    const alphabet_t&	   alphabet(input.series().monoid().alphabet());
    subset_t		   q;
    subset_t		   s;
    delta_ret_t		   aim;
    hstate_t		   s_hstate;
    typename subset_set_t::const_iterator	current;   

    /*---------------.
    | Initialization |
    `---------------*/
    bool is_final = false;

    for (typename input_t::initial_iterator i = input.initial().begin();
	 i != input.initial().end();
	 ++i)
      {
	qi.insert(*i);
	is_final |= input.is_final(*i);
	output.set_initial(qi_hstate);
      }

    if (is_final)
      output.set_final(qi_hstate);

    subset_set[qi] = qi_hstate;

    // FIXME : log history ?

    /*----------.
    | Main loop |
    `----------*/
    std::queue<subset_t> path;
    path.push(qi);

    do {
      s        = path.front();
      s_hstate = subset_set[s];
      path.pop();
      
      for (typename alphabet_t::const_iterator e = alphabet.begin();
	   e != alphabet.end();
	   ++e)
	{
	  q.clear();
	  is_final = false;
	  for (typename subset_t::const_iterator j = s.begin(); 
	       j != s.end(); ++j)
	    {
	      aim.clear();
	      // FIXME : Use a more efficient version of delta !
	      input.letter_deltac(aim, *j, *e, delta_kind::states());
	      for (typename delta_ret_t::const_iterator k = aim.begin(); 
		   k != aim.end(); ++k)
		{
		  hstate_t state = *k;
		  q.insert(state);
		  is_final   |= input.is_final(state);
		}
	    }
	  current = subset_set.find(q);
	  if (current == subset_set.end()) 
	    {
	      current = (subset_set.insert
			 (subset_set_pair_t(q, output.add_state()))).first;

	      // Log history ?

	      if (is_final)   
		output.set_final(current->second);
	      path.push(q);
	    }
	  output.add_letter_edge(s_hstate, (*current).second, *e);
	}
    } while (!path.empty());
  }

  template<typename A, typename T>
  Element<A, T>
  subset_construction(const Element<A, T>& a)
  {
    Element<A, T>    ret;

    ret.create();
    ret.series() = a.series();
    do_subset_construction(ret.set(), ret, a);
    return ret;
  }


  /*------------.
  | determinize |
  `------------*/
  template <typename A, typename input_t, typename output_t>
  void
  do_determinize(const AutomataBase<A>&	a_set,
	      output_t&			output,
	      const input_t&		input)
  {
  // FIXME : for the moment, it uses subset_construction and trim but
  // it must be rewritten to do the twice at the same time more efficiently.
    do_subset_construction(a_set, output, input);
    auto_in_start_reachable(output);
  }

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a)
  {
    Element<A, T>    ret;

    ret.create();
    ret.series() = a.series();
    do_determinize(ret.set(), ret, a);
    return ret;
  }


  /*-----------------.
  | is_deterministic |
  `-----------------*/
  // FIXME : verbose mode will be modified for being clearer.
  template <typename A, typename input_t>
  bool
  do_is_deterministic(const AutomataBase<A>&	a_set,
		      const input_t&		input)
  {
    typedef typename std::set<hedge_t>		delta_ret_t;	
    typedef typename input_t::series_t		series_t;
    typedef typename input_t::series_value_t	series_value_t;
    typedef typename series_t::weights_t	weights_t;
    typedef typename input_t::series_elt_t     	series_elt_t;
    typedef typename series_elt_t::weight_t	weight_t;

    delta_ret_t	delta_ret;
    weight_t		  zero_semiring
      = input.series().weights().zero(SELECT(typename weight_t::value_t));

    // Empty automaton is not deterministic
    if (input.states().size() == 0)
      return false;

    if (input.initial().size() != 1)
      return false;

    for (typename input_t::state_iterator i = input.states().begin();
	 i != input.states().end();
	 ++i)
      {
	delta_ret.clear();
	input.deltac(delta_ret, *i, delta_kind::edges());
	// FIXME : O(n^2) => O(nlog(n))
	for (typename delta_ret_t::const_iterator j = delta_ret.begin(); 
	     j != delta_ret.end(); 
	     ++j)
	  {
	    series_elt_t s = input.serie_of(*j);
	    typename delta_ret_t::const_iterator k = j;
	    ++k;
	    for (; k != delta_ret.end(); ++k)
	      {
		series_elt_t s_ = input.serie_of(*k);
		for (typename series_value_t::iterator supp = s.supp().begin();
		     supp != s.supp().end();
		     ++supp)
		  if (s_.get(supp->first) != zero_semiring)
		    return false;
	      }
	  }
      }
    return true;
  }

  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a)
  {
    return do_is_deterministic(a.set(), a);
  }

} // vcsn

#endif // ALGO_DETERMINIZE_HXX
