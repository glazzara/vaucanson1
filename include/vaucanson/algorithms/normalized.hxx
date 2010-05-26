// normalized.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2010 The
// Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_NORMALIZED_HXX
# define VCSN_ALGORITHMS_NORMALIZED_HXX

# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/algorithms/internal/has_neighbour.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/algorithms/standard.hh>

# include <stack>

namespace vcsn {

  /*-----------.
  | normalized |
  `-----------*/
  template <typename A, typename AI>
  void
  do_normalize_here(const AutomataBase<A>&,
		    Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("normalize");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t h = a.add_state();

    for_all_const_initial_states(i, a)
      a.add_series_transition(h, *i, a.get_initial(*i));

    a.clear_initial();
    a.set_initial(h);

    h = a.add_state();

    for_all_const_final_states(i, a)
      a.add_series_transition(*i, h, a.get_final(*i));

    a.clear_final();
    a.set_final(h);
  }

  template <typename A, typename AI>
  Element<A, AI>
  normalize(const Element<A, AI>& a)
  {
    Element<A, AI> result(a);
    do_normalize_here(result.structure(), result);
    return result;
  }

  template<typename A, typename AI>
  void
  normalize_here(Element<A, AI>& a)
  {
    do_normalize_here(a.structure(), a);
  }


  /*--------------------.
  | union_of_normalized |
  `--------------------*/

  template <typename A, typename AI1, typename AI2>
  void
  do_union_of_normalized_here(const AutomataBase<A>&,
			      Element<A, AI1>& lhs,
			      const Element<A, AI2>& rhs)
  {
    BENCH_TASK_SCOPED("union_of_normalized");
    typedef Element<A, AI1> lhs_t;
    typedef Element<A, AI2> rhs_t;
    AUTOMATON_TYPES(lhs_t);
    monoid_elt_t monoid_identity =
      lhs.series().monoid().identity(SELECT(monoid_elt_value_t));
    hstate_t new_i = lhs.add_state();
    hstate_t new_f = lhs.add_state();

    union_here(lhs, rhs);

    for_all_const_initial_states(i, lhs)
      lhs.add_spontaneous(new_i, *i, lhs.get_initial(*i).get(monoid_identity));
    lhs.clear_initial();

    for_all_const_final_states(f, lhs)
      lhs.add_spontaneous(*f, new_f, lhs.get_final(*f).get(monoid_identity));
    lhs.clear_final();

    lhs.set_final(new_f);
    lhs.set_initial(new_i);
  }

  template<typename A, typename AI1, typename AI2>
  void
  union_of_normalized_here(Element<A, AI1>& lhs,
			   const Element<A, AI2>& rhs)
  {
    do_union_of_normalized_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  union_of_normalized(const Element<A, AI1>& lhs,
		      const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    do_union_of_normalized_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*--------------.
  | is_normalized |
  `--------------*/
  template <typename A, typename AI>
  bool
  do_is_normalized(const AutomataBase<A>&,
		   const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("is_normalized");
    typedef Element<A, AI> automaton_t;
    typedef typename automaton_t::series_set_elt_value_t	series_set_elt_value_t;
    typedef typename automaton_t::series_set_elt_t		series_set_elt_t;

    series_set_elt_t series_identity =
      a.series().identity(SELECT(series_set_elt_value_t));

    if (a.initial().size() != 1
	|| a.final().size() != 1
	|| a.get_initial(*a.initial().begin()) != series_identity
	|| a.get_final(*a.final().begin()) != series_identity)
      return false;

    // Check that there is no input transition on the initial state
    // and no output transition on the final state.
    return !has_successors(a, *a.final().begin())
      && !has_predecessors(a, *a.initial().begin());
  }

  template<typename A, typename AI>
  bool
  is_normalized(const Element<A, AI>& a)
  {
    return do_is_normalized(a.structure(), a);
  }

  /*--------------------------.
  | concatenate_of_normalized |
  `--------------------------*/
  template <typename A, typename AI1, typename AI2>
  void
  do_concatenate_of_normalized_here(const AutomataBase<A>&,
				    Element<A, AI1>& lhs,
				    const Element<A, AI2>& rhs)
  {
    BENCH_TASK_SCOPED("concatenate_of_normalized");
    typedef Element<A, AI1> lhs_t;
    typedef Element<A, AI2> rhs_t;
    AUTOMATON_TYPES(rhs_t);
    typedef std::map<hstate_t, hstate_t>	map_lhs_rhs_t;
    typedef std::list<htransition_t>		delta_ret_t;

    hstate_t	glue_state = *lhs.final().begin();

    /*-----------------.
    | Concat of states |
    `-----------------*/
    map_lhs_rhs_t	map_h;

    // If rhs initial multiplicity is 1 and so is lhs final multiplicity,
    // we can merge the lhs final state and the rhs initial state.
    bool merge_lhs_final_and_rhs_initial =
      (lhs.get_final(*lhs.final().begin()).value() ==
       lhs.series().identity(SELECT(series_set_elt_value_t)) &&
       rhs.get_initial(*rhs.initial().begin()).value() ==
       rhs.series().identity(SELECT(series_set_elt_value_t)));

    for_all_const_states(s, rhs)
    {
      hstate_t new_state;

      if (merge_lhs_final_and_rhs_initial)
      {
	if (rhs.is_initial(*s))
	  new_state = glue_state;
	else
	  new_state = lhs.add_state();
      }
      else
	new_state = lhs.add_state();
      map_h[*s] = new_state;
      lhs.set_final(new_state, rhs.get_final(*s));
    }

    /*------------------------.
    | Concat of transitions.  |
    `------------------------*/
    for_all_const_transitions(t, rhs)
      lhs.add_transition(map_h[rhs.src_of(*t)],
			 map_h[rhs.dst_of(*t)],
			 rhs.label_of(*t));

    // If initial multiplicity of rhs isn't 1, add a spontaneous transition
    // between lhs final state and rhs initial state, with lhs final
    // multiplicity * rhs initial multiplicity.
    if (!merge_lhs_final_and_rhs_initial)
    {
      monoid_elt_t monoid_identity =
	rhs.series().monoid().identity(SELECT(monoid_elt_value_t));
      hstate_t i = *rhs.initial().begin();
      hstate_t f = *lhs.final().begin();

      lhs.add_spontaneous(f, map_h[i],
			  lhs.get_final(f).get(monoid_identity) *
			  rhs.get_initial(i).get(monoid_identity));
      lhs.unset_final(f);
      lhs.unset_initial(map_h[i]);
    }
  }

  template<typename A, typename AI1, typename AI2>
  void
  concatenate_of_normalized_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    do_concatenate_of_normalized_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  concatenate_of_normalized(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    do_concatenate_of_normalized_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*-------------------.
  | star_of_normalized |
  `-------------------*/
  template <typename A, typename AI>
  void
  do_star_of_normalized_here(const AutomataBase<A>&, Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("star_of_normalized");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    monoid_elt_t monoid_identity =
      a.series().monoid().identity(SELECT(monoid_elt_value_t));
    hstate_t old_i = *a.initial().begin();
    hstate_t old_f = *a.final().begin();
    hstate_t new_i = a.add_state();
    hstate_t new_f = a.add_state();

    a.add_spontaneous(old_f, old_i, a.get_initial(old_i).get(monoid_identity));
    a.add_spontaneous(new_i, old_i, a.get_initial(old_i).get(monoid_identity));
    a.add_spontaneous(old_f, new_f, a.get_final(old_f).get(monoid_identity));
    a.add_spontaneous(new_i, new_f);
    a.set_final(new_f);
    a.unset_final(old_f);
    a.set_initial(new_i);
    a.unset_initial(old_i);
  }

  template<typename A, typename AI>
  void
  star_of_normalized_here(Element<A, AI>& a)
  {
    do_star_of_normalized_here(a.structure(), a);
  }

  template<typename A, typename AI>
  Element<A, AI>
  star_of_normalized(const Element<A, AI>& a)
  {
    Element<A, AI> ret(a);
    do_star_of_normalized_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_NORMALIZED_HXX
