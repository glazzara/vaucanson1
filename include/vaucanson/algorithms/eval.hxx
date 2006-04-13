// eval.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_EVAL_HXX
# define VCSN_ALGORITHMS_EVAL_HXX

# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <algorithm>
# include <vector>

namespace vcsn {

  /*-----.
  | Eval |
  `-----*/
  // precondition : the automaton is realtime
  //
  // author: Yann Regis-Gianas.
  template <typename A, typename auto_t,
	    typename Selt, typename input_t>
  void
  do_eval(const AutomataBase<A>&,
	  const auto_t&	    a,
	  const input_t&    word,
	  Selt&		    result,
	  bool&		    b_result)
  {
    AUTOMATON_TYPES(auto_t);
    // FIXME: for the moment, we use large vectors because the set of hstate_t
    // FIXME: can be sparsed. We wanted to be as general as possible.
    // FIXME: Variants of eval will be available soon of course.

    hstate_t max_hstate_t = 0;
    for_each_state(i, a)
      max_hstate_t = std::max(*i, max_hstate_t);

    std::vector<semiring_elt_t>	v1(max_hstate_t + 1,
				   semiring_elt_t (a.series().semiring()));
    std::vector<bool>		v1_b(max_hstate_t + 1, false);
    std::vector<semiring_elt_t>	v2(max_hstate_t + 1,
				   semiring_elt_t (a.series().semiring()));
    std::vector<bool>		v2_b(max_hstate_t + 1, false);
    std::list<htransition_t>		delta_ret;
    const typename semiring_elt_t::set_t &semiring = a.series().semiring();
    semiring_elt_t zero =
      semiring.zero(SELECT(typename semiring_elt_t::value_t));
    monoid_elt_t empty(a.series().monoid());

    /*-------------------.
    | Initialize the set |
    `-------------------*/
    std::fill(v1.begin(), v1.end(), zero);

    /*--------.
    | Initial |
    `--------*/
    // FIXME: here we assume that there is only weight in the initial app.
    for_each_initial_state(i, a)
    {
      v1[*i] = a.get_initial(*i).get(empty);
      v1_b[*i] = true;
    }

    /*------------.
    | Computation |
    `------------*/
    for_all_const_(input_t, e, word)
    {
      std::fill(v2.begin(), v2.end(), zero);
      std::fill(v2_b.begin(), v2_b.end(), false);
      for (unsigned i = 0; i < v1.size(); ++i)
	if (v1_b[i])
	{
	  // FIXME : use the other version of delta to be more efficient !
	  delta_ret.clear();
	  a.letter_deltac(delta_ret, i, *e, delta_kind::transitions());
	  for_all_const_(std::list<htransition_t>, l, delta_ret)
	  {
	    v2[a.aim_of(*l)] += v1[i] *
	      a.series_of(*l).get(monoid_elt_t(a.structure().series().monoid(), *e));
	    v2_b[a.aim_of(*l)] = true;
	  }
	}
      std::swap(v1, v2);
      std::swap(v1_b, v2_b);
    }

    /*-----------------.
    | Final and Result |
    `-----------------*/
    result = zero;
    b_result = false;
    for (unsigned i = 0; i < v1.size(); ++i)
      if (v1_b[i])
      {
	result += v1[i] * a.get_final(i).get(empty);
	if (a.is_final(i))
	  b_result = true;
      }
  }

  /*---------.
  | Wrappers |
  `---------*/
  template<typename A, typename T, typename W>
  typename Element<A, T>::semiring_elt_t
  eval(const Element<A, T>& a, const W& word)
  {
    typename Element<A, T>::semiring_elt_t ret(a.structure().series().semiring());
    bool				   b_ret;

    do_eval(a.structure(), a, word, ret, b_ret);
    return ret;
  }

  template<typename A, typename T, typename W>
  typename Element<A, T>::semiring_elt_t
  eval(const Element<A, T>& a, const W& word, bool& b_ret)
  {
    typename Element<A, T>::semiring_elt_t ret(a.structure().series().semiring());

    do_eval(a.structure(), a, word, ret, b_ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EVAL_HXX
