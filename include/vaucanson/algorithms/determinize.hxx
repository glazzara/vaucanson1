// determinize.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/algorithms/realtime.hh>

namespace vcsn {

  //Functor used in do_subset_construction for deltaf query.
  template <typename input_t>
  struct delta_functor
  {
    typedef typename std::set<typename input_t::hstate_t>    subset_t;

    delta_functor(subset_t& q_, const input_t& input_, bool& is_final_)
      : q(q_), input(input_), is_final(is_final_)
    {}

    void operator()(typename input_t::hstate_t s)
    {
      q.insert(s);
      is_final |= input.is_final(s);
    }

    subset_t&	    q;
    const input_t&  input;
    bool&	    is_final;
  };

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
			 std::map<typename output_t::hstate_t,
			  std::set<typename input_t::hstate_t> >& m =
			 std::map<typename output_t::hstate_t,
			  std::set<typename input_t::hstate_t> >())
  {

    /*--------.
    | Typedef |
    `--------*/

    AUTOMATON_TYPES(input_t);
    AUTOMATON_FREEMONOID_TYPES(input_t);
    typedef typename std::set<typename input_t::hstate_t>    subset_t;
    typedef typename std::map<subset_t, typename output_t::hstate_t>
							     subset_set_t;
    typedef std::pair<subset_t, typename output_t::hstate_t> subset_set_pair_t;
    typedef std::vector<typename input_t::hstate_t>	     delta_ret_t;


    /*-----------------.
    | Initialization.  |
    `-----------------*/

    typename output_t::hstate_t qi_hstate = output.add_state();
    subset_t qi;
    bool is_final = false;
    for_all_const_initial_states(i, input)
    {
      qi.insert(*i);
      is_final |= input.is_final(*i);
    }
    output.set_initial(qi_hstate);

    if (is_final)
      output.set_final(qi_hstate);

    subset_set_t subset_set;
    subset_set[qi] = qi_hstate;
    m[qi_hstate] = qi;


    /*------------.
    | Main loop.  |
    `------------*/

    subset_t q;
    const alphabet_t& alphabet(input.structure().series().monoid().alphabet());
    delta_ret_t dst;
    dst.reserve(input.states().size());
    std::queue<subset_t> path;
    path.push(qi);
    while (!path.empty())
    {
      subset_t s = path.front();
      typename input_t::hstate_t s_hstate = subset_set[s];
      path.pop();

      for_all_const_letters(e, alphabet)
      {
	q.clear ();
	bool is_final = false;
	delta_functor<input_t> func(q, input, is_final);
	for_all_const_ (subset_t, j, s)
	  input.letter_deltaf(func, *j, *e, delta_kind::states());
	typename subset_set_t::const_iterator current = subset_set.find(q);
	if (current == subset_set.end())
	{
	  typename output_t::hstate_t qs = output.add_state();
	  current = (subset_set.insert(subset_set_pair_t(q, qs))).first;
	  m[qs] = q;

	  if (is_final)
	    output.set_final(current->second);
	  path.push(q);
	}
	output.add_letter_transition(s_hstate, (*current).second, *e);
      }
    }
  }

  template<typename A, typename T>
  Element<A, T>
  subset_construction(const Element<A, T>& a)
  {
    Element<A, T> res(a.structure());
    do_subset_construction(res.structure(), res, a);
    return res;
  }

  /*--------------.
  | determinize.  |
  `--------------*/
  template <typename A, typename input_t, typename output_t>
  void
  do_determinize(const AutomataBase<A>&	a_set,
		 output_t&		output,
		 const input_t&		input,
		 std::map<typename output_t::hstate_t,
		  std::set<typename input_t::hstate_t> >& m)
  {
    TIMER_SCOPED ("determinize");
    precondition(is_realtime(input));
    do_subset_construction(a_set, output, input, m);
  }

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a,
	      std::map<typename T::hstate_t,
		std::set<typename T::hstate_t> >& m)
  {
    Element<A, T> ret(a.structure());
    do_determinize(ret.structure(), ret, a, m);
    return ret;
  }

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a)
  {
    std::map<typename T::hstate_t, std::set<typename T::hstate_t> > m;
    return determinize(a, m);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HXX
