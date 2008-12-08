// eval.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVAL_HXX
# define VCSN_ALGORITHMS_EVAL_HXX

# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <algorithm>
# include <vector>

namespace vcsn {

  /*-----.
  | Eval |
  `-----*/

  // precondition : the automaton is realtime
  template <typename auto_t, typename input_t, typename Selt>
  struct eval_functor
  {
      AUTOMATON_TYPES(auto_t);

      typedef std::vector<semiring_elt_t> weights;

      const auto_t& a;
      int max_hstate;

      weights v1, v2;

      typename weights::const_iterator w;
      typename input_t::const_iterator l;

      template <typename A>
      eval_functor(const AutomataBase<A>&, const auto_t& aut)
	: a(aut), max_hstate(a.states().back() + 1),
	  v1(max_hstate, a.series().semiring().wzero_), v2(max_hstate)
      {}

      void execute(const input_t& word, Selt& result)
      {
	const monoid_elt_t empty = algebra::identity_as<monoid_elt_value_t>::of(a.series().monoid());

	// Initialize
	for_all_const_initial_states(i, a)
	  v1[*i] = a.get_initial(*i).get(empty);

	const semiring_elt_t zero = a.series().semiring().wzero_;

	// Computation
	l = word.begin();
	for (typename input_t::const_iterator w_end = word.end();
	     l != w_end; ++l)
	{
	  std::fill(v2.begin(), v2.end(), zero);
	  int i = 0;
	  w = v1.begin();
	  for (typename weights::const_iterator v1_end = v1.end();
	       w != v1_end; ++w)
	  {
	    if (*w != zero)
            {
              for (delta_iterator t(a.value(), a.get_state(i)); ! t.done(); t.next())
              {
                monoid_elt_t l_w(a.series_of(*t).structure().monoid(), *l);
                if (a.series_of(*t).get(l_w) != a.series().semiring().wzero_)
                {
                  v2[a.dst_of(*t)] += *w *
                    a.series_of(*t).get(monoid_elt_t(a.structure().series().monoid(), *l));
                }
              }
            }
	    ++i;
	  }
	  std::swap(v1, v2);
	}

	// Result
	result = zero;
	int i = 0;
	for_all_const_ (weights, w, v1)
	{
	  if (*w != zero)
	    result += *w * a.get_final(i).get(empty);
	  ++i;
	}
      }
  };

  /*----------.
  | Wrapper.  |
  `----------*/

  template<typename A, typename AI, typename W>
  typename Element<A, AI>::semiring_elt_t
  eval(const Element<A, AI>& a, const W& word)
  {
    TIMER_SCOPED("eval");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    semiring_elt_t ret(a.structure().series().semiring());

    // Check if the automaton is empty.
    if (!is_empty(a))
    {
      eval_functor<automaton_t, W, semiring_elt_t> evalf(a.structure(), a);
      evalf.execute(word, ret);
    }

    return ret;
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_EVAL_HXX
