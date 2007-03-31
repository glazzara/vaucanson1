// normalized.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
# include <vaucanson/algorithms/sum.hh>

# include <stack>

namespace vcsn {

  /*-----------.
  | normalized |
  `-----------*/
  template <class A_, typename Auto_>
  void
  do_normalize_here(const AutomataBase<A_>&,
		    Auto_& a)
  {
    TIMER_SCOPED("normalize");
    AUTOMATON_TYPES(Auto_);

    hstate_t h = a.add_state();

    for_all_initial_states(i, a)
      a.add_series_transition(h, *i, a.get_initial(*i));

    a.clear_initial();
    a.set_initial(h);

    h = a.add_state();

    for_all_final_states(i, a)
      a.add_series_transition(*i, h, a.get_final(*i));

    a.clear_final();
    a.set_final(h);
  }

  template <typename A, typename T>
  Element<A, T>
  normalize(const Element<A, T>& a)
  {
    Element<A, T> result(a);
    do_normalize_here(result.structure(), result);
    return result;
  }

  template<typename A, typename T>
  void
  normalize_here(Element<A, T>& a)
  {
    do_normalize_here(a.structure(), a);
  }


  /*--------------------.
  | union_of_normalized |
  `--------------------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void do_union_of_normalized_here(const AutomataBase<A>&,
				   lhs_t& lhs,
				   const rhs_t& rhs)
  {
    TIMER_SCOPED("union_of_normalized");
    AUTOMATON_TYPES(lhs_t);
    monoid_elt_t monoid_identity =
      lhs.series().monoid().identity(SELECT(monoid_elt_value_t));
    hstate_t new_i = lhs.add_state();
    hstate_t new_f = lhs.add_state();

    sum_here(lhs, rhs);

    for_all_initial_states(i, lhs)
      lhs.add_spontaneous(new_i, *i, lhs.get_initial(*i).get(monoid_identity));
    typename lhs_t::initial_iterator i;
    for (typename lhs_t::initial_iterator next = lhs.initial().begin();
	 next != lhs.initial().end();)
    {
      i = next;
      ++next;
      lhs.unset_initial(*i);
    }

    for_all_final_states(f, lhs)
      lhs.add_spontaneous(*f, new_f, lhs.get_final(*f).get(monoid_identity));
    typename lhs_t::final_iterator f;
    for (typename lhs_t::final_iterator next = lhs.final().begin();
	 next != lhs.final().end();)
    {
      f = next;
      ++next;
      lhs.unset_final(*f);
    }
    lhs.set_final(new_f);
    lhs.set_initial(new_i);
  }

  template<typename A, typename T, typename U>
  void union_of_normalized_here(Element<A, T>& lhs,
				const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    do_union_of_normalized_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  union_of_normalized(const Element<A, T>& lhs,
		      const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(lhs);
    do_union_of_normalized_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*--------------.
  | is_normalized |
  `--------------*/
  template <typename A, typename auto_t>
  bool
  do_is_normalized(const AutomataBase<A>&,
		   const auto_t& a)
  {
    TIMER_SCOPED("is_normalized");
    typedef typename auto_t::series_set_elt_value_t	series_set_elt_value_t;
    typedef typename auto_t::series_set_elt_t		series_set_elt_t;

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

  template<typename A, typename T>
  bool
  is_normalized(const Element<A, T>& a)
  {
    return do_is_normalized(a.structure(), a);
  }

  /*--------------------------.
  | concatenate_of_normalized |
  `--------------------------*/
  template <typename A, typename lhs_t, typename rhs_t>
  void do_concatenate_of_normalized_here(const AutomataBase<A>&,
					 lhs_t& lhs,
					 const rhs_t& rhs)
  {
    TIMER_SCOPED("concatenate_of_normalized");
    AUTOMATON_TYPES(rhs_t);
    typedef std::map<hstate_t, hstate_t>	map_lhs_rhs_t;
    typedef std::set<htransition_t>		delta_ret_t;

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

    for_all_states(s, rhs)
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
    for_all_transitions(t, rhs)
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

  template<typename A, typename T, typename U>
  void concatenate_of_normalized_here(Element<A, T>& lhs,
				      const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    do_concatenate_of_normalized_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  concatenate_of_normalized(const Element<A, T>& lhs,
			    const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(lhs);
    do_concatenate_of_normalized_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*-------------------.
  | star_of_normalized |
  `-------------------*/
  template <typename A, typename auto_t>
  void do_star_of_normalized_here(const AutomataBase<A>&,
				  auto_t& a)
  {
    TIMER_SCOPED("star_of_normalized");
    AUTOMATON_TYPES(auto_t);
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

  template<typename A, typename T>
  void star_of_normalized_here(Element<A, T>& a)
  {
    do_star_of_normalized_here(a.structure(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  star_of_normalized(const Element<A, T>& a)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(a);
    do_star_of_normalized_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_NORMALIZED_HXX
