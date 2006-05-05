// determinize.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_DETERMINIZE_HXX
# define VCSN_ALGORITHMS_DETERMINIZE_HXX

# include <map>
# include <set>
# include <queue>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/accessible.hh>

namespace vcsn {

  /*--------------------.
  | subset_construction |
  `--------------------*/
  // preconditions :
  //	- output has been initialized with good series set
  //	  (alphabet is well initialized) ;
  //	- this algorithm is intended to work with realtime automaton
  //	  over |B<A*> => add concept checking.
  //

  template <typename A, typename input_t, typename output_t>
  void
  do_subset_construction(const AutomataBase<A>&	,
			 output_t&		output,
			 const input_t&		input,
			 std::map<hstate_t, std::set<hstate_t> >& m =
			 std::map<hstate_t, std::set<hstate_t> >())
  {
    AUTOMATON_TYPES(input_t);
    AUTOMATON_FREEMONOID_TYPES(input_t);
    typedef typename input_t::series_set_t			    series_set_t;
    typedef typename std::set<hstate_t>			    subset_t;
    typedef typename std::map<subset_t, hstate_t>	    subset_set_t;
    typedef std::pair<subset_t, hstate_t>		    subset_set_pair_t;
    typedef std::vector<hstate_t>			    delta_ret_t;

    hstate_t		   qi_hstate = output.add_state();
    subset_t		   qi;
    subset_set_t	   subset_set;
    const alphabet_t&	   alphabet(input.structure().series().monoid().alphabet());
    subset_t		   q;
    subset_t		   s;
    delta_ret_t		   aim;
    hstate_t		   s_hstate;
    typename subset_set_t::const_iterator	current;

    /*---------------.
    | Initialization |
    `---------------*/
    bool is_final = false;
    aim.reserve(input.states().size());

    for_each_initial_state(i, input)
    {
      qi.insert(*i);
      is_final |= input.is_final(*i);
      output.set_initial(qi_hstate);
    }

    if (is_final)
      output.set_final(qi_hstate);

    subset_set[qi] = qi_hstate;
    m[qi_hstate] = qi;


    /*----------.
    | Main loop |
    `----------*/
    std::queue<subset_t> path;
    path.push(qi);

    do {
      s	       = path.front();
      s_hstate = subset_set[s];
      path.pop();

      for_each_letter(e, alphabet)
      {
	q.clear();
	is_final = false;
	for (typename subset_t::const_iterator j = s.begin();
	     j != s.end(); ++j)
	{
	  aim.clear();

	  input.letter_deltac(aim, *j, *e, delta_kind::states());
	  for_all_const_(delta_ret_t, k, aim)
	  {
	    hstate_t state = *k;
	    q.insert(state);
	    is_final   |= input.is_final(state);
	  }
	}
	current = subset_set.find(q);
	if (current == subset_set.end())
	{
	  hstate_t qs = output.add_state();
	  current = (subset_set.insert
		     (subset_set_pair_t(q, qs))).first;
	  m[qs] = q;



	  if (is_final)
	    output.set_final(current->second);
	  path.push(q);
	}
	output.add_letter_transition(s_hstate, (*current).second, *e);
      }
    } while (!path.empty());
  }

  template<typename A, typename T>
  Element<A, T>
  subset_construction(const Element<A, T>& a)
  {
    Element<A, T>    ret(a.structure());
    do_subset_construction(ret.structure(), ret, a);
    return ret;
  }

  /*------------.
  | determinize |
  `------------*/
  template <typename A, typename input_t, typename output_t>
  void
  do_determinize(const AutomataBase<A>&	a_set,
		 output_t&			output,
		 const input_t&		input,
		 std::map<hstate_t, std::set<hstate_t> >& m)
  {
    do_subset_construction(a_set, output, input, m);
  }

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a)
  {
    std::map<hstate_t, std::set<hstate_t> > m;
    return determinize(a, m);
  }

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a,
	      std::map<hstate_t, std::set<hstate_t> >& m)
  {
    Element<A, T> ret(a.structure());
    do_determinize(ret.structure(), ret, a, m);
    return ret;
  }

  template <typename input_t>
  static bool
  is_state_deterministic (input_t&						input,
			  typename input_t::state_iterator&			current_state,
			  typename input_t::series_set_elt_t::semiring_elt_t&	zero_semiring)
  {
    AUTOMATON_TYPES(input_t);

    typedef typename series_set_elt_t::support_t	support_t;
    typedef typename std::set<htransition_t>		delta_ret_t;
    delta_ret_t	delta_ret;

    input.deltac(delta_ret, *current_state, delta_kind::transitions());
    // FIXME : O(n^2) => O(nlog(n)) There is maybe an algorithm in O(nlog(n))
    for_all_const_(delta_ret_t, j, delta_ret)
      {
	series_set_elt_t s = input.series_of(*j);
	typename delta_ret_t::const_iterator k = j;
	++k;
	for (; k != delta_ret.end(); ++k)
	  {
	    series_set_elt_t s_ = input.series_of(*k);
	    for_all_(support_t, supp, s.supp())
	      if (s_.get(*supp) != zero_semiring)
		return false;
	  }
      }
    return true;
  }




  /*-----------------.
  | is_deterministic |
  `-----------------*/
  template <typename A, typename input_t>
  bool
  do_is_deterministic(const AutomataBase<A>&	,
		      const input_t&		input)
  {
    AUTOMATON_TYPES(input_t);
    semiring_elt_t		  zero_semiring
      = input.structure().series().semiring()
      .zero(SELECT(typename semiring_elt_t::value_t));

    // Empty automaton is not deterministic
    if (input.states().size() == 0)
      return false;

    if (input.initial().size() != 1)
      return false;

    for_each_state(i, input)
    {
      if (not is_state_deterministic (input, i, zero_semiring))
	return false;
    }
    return true;
  }


  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a)
  {
    return do_is_deterministic(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HXX
