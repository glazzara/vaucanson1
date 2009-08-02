// standard.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
// The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_STANDARD_HXX
# define VCSN_ALGORITHMS_STANDARD_HXX

# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/internal/has_neighbour.hh>

# include <vaucanson/algorithms/sum.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <set>

namespace vcsn {

  /*---------.
  | standard |
  `---------*/
  template <class A, typename AI>
  void
  do_in_standardize(const AutomataBase<A>&, Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("standardize");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t i = a.add_state();
    std::list<htransition_t> transition_oi;
    series_set_elt_t final_series =
      algebra::zero_as<series_set_elt_value_t>::of(a.series());

    for_all_const_initial_states(oi, a)
    {
      series_set_elt_t s = a.get_initial(*oi);

      // Handle each transitions.
      transition_oi.clear();
      for (delta_iterator oil(a.value(), *oi);
           ! oil.done();
           oil.next())
        transition_oi.push_back(*oil);
      for_all_const_(std::list<htransition_t>, oil, transition_oi)
      {
	series_set_elt_t t = s * a.series_of(*oil);
	a.add_series_transition(i, a.dst_of(*oil), t);
      }
      // Accumulate final transition series of each initial state.
      final_series += s * a.get_final(*oi);
    }

    // Suppress initial states which are not accessible.  We don't use
    // @c accessible_here for efficienty issues, and because the
    // definition of a standard automaton does not imply the
    // admissible property.
    for (initial_iterator oi = a.initial().begin(), next = oi;
	 oi != a.initial().end();
	 oi = next)
    {
      ++next;
      if (!has_predecessors(a, *oi))
	a.del_state(*oi);
    }
    a.clear_initial();
    a.set_initial(i);
    a.set_final(i, final_series);
  }

  template<typename A, typename AI>
  void
  standardize(Element<A, AI>& a)
  {
    do_in_standardize(a.structure(), a);
  }

  /*-----------------.
  | standard_union.  |
  `-----------------*/

  template <typename A, typename AI1, typename AI2>
  void
  do_union_of_standard_here(const AutomataBase<A>&,
			    Element<A, AI1>& lhs,
			    const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));

    BENCH_TASK_SCOPED("union_of_standard");

    typedef Element<A, AI1> lhs_t;

    // The resulting initial state is that of lhs.
    typename lhs_t::hstate_t new_i = *lhs.initial().begin();
    sum_here(lhs, rhs);

    assertion (lhs.initial().size() == 2);
    typename lhs_t::initial_iterator i = lhs.initial().begin();
    typename lhs_t::hstate_t old_i = *i != new_i ? *i : *++i;

    union_of_standard_here_common(lhs.structure(), lhs, new_i, old_i);
  }

  // Group the common part of the union of standard automata algorithm,
  // considering the two automata we want to unify are contained in 'a'.
  // 'new_i' being the initial state of the resulting automata (the initial
  // state of the "first" automata), only linking and deleting is done here.
  template<typename A, typename AI>
  void
  union_of_standard_here_common(const AutomataBase<A>&,
                                Element<A, AI>& a,
                                typename Element<A, AI>::hstate_t& new_i,
                                typename Element<A, AI>::hstate_t& old_i)
  {
    typedef Element<A, AI>                       automaton_t;
    typedef typename automaton_t::htransition_t  htransition_t;
    typedef typename automaton_t::delta_iterator delta_iterator_t;
    typedef std::list<htransition_t>             delta_ret_t;

    // Merge old_i with new_i, thus letting in a only new_i as
    // initial state, making a standard.
    a.set_final(new_i,
                a.get_final(new_i) + a.get_final(old_i));

    // All the storage done here is the consequence of implementation
    // concerns as BMIG structure used for transitions' representation
    // is modified whenever a transition is added to the automata.
    // Thus, when add_series_transition is called, the delta_iterator
    // we could have used would have been modified, provocking data
    // corruption.
    delta_ret_t dst;

    for (delta_iterator_t i(a.value(), old_i);
         ! i.done();
         i.next())
      dst.push_back(*i);

    for_all_const_(delta_ret_t, d, dst)
    {
      a.add_series_transition(new_i,
                              a.dst_of(*d),
                              a.series_of(*d));
      a.del_transition(*d);
    }

    a.del_state(old_i);
  }

  template<typename A, typename AI1, typename AI2>
  void
  union_of_standard_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    do_union_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  union_of_standard(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    union_of_standard_here(ret, rhs);
    return ret;
  }

  /*--------------.
  | is_standard.  |
  `--------------*/
  template<typename A, typename AI>
  bool
  do_is_standard(const AutomataBase<A>&, const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("is_standard");
    typedef Element<A, AI> automaton_t;
    typedef typename automaton_t::series_set_elt_value_t	series_set_elt_value_t;

    // Check there is only one initial state.
    if (a.initial().size() != 1)
      return false;

    // Check the multiplicity of the initial state.
    typename automaton_t::hstate_t s = *a.initial().begin();
    if (a.get_initial(s)
	!= a.series().identity(SELECT(series_set_elt_value_t)))
      return false;

    // Check that there is no input transition on the initial state.
    return !has_predecessors(a, s);
  }

  template<typename A, typename AI>
  bool
  is_standard(const Element<A, AI>& a)
  {
    return do_is_standard(a.structure(), a);
  }

  /*---------------------.
  | concat_of_standard.  |
  `---------------------*/
  template <typename A, typename AI1, typename AI2>
  void
  do_concat_of_standard_here(const AutomataBase<A>&,
			     Element<A, AI1>& lhs,
			     const Element<A, AI2>& rhs)
  {
    precondition(is_standard(lhs));
    precondition(is_standard(rhs));

    BENCH_TASK_SCOPED("concat_of_standard");
    typedef Element<A, AI1> lhs_t;
    typedef Element<A, AI2> rhs_t;
    typedef typename lhs_t::hstate_t l_hstate_t;
    typedef typename rhs_t::hstate_t r_hstate_t;
    typedef std::map<l_hstate_t, r_hstate_t>	map_t;

    /*------------------.
    | Concat of states. |
    `------------------*/
    map_t	map_h;
    l_hstate_t	new_state;

    // Add states except the initial one.
    for (typename rhs_t::state_iterator s = rhs.states().begin();
	 s != rhs.states().end();
	 ++s)
      if (!rhs.is_initial(*s))
      {
	new_state = lhs.add_state();
	map_h[*s] = new_state;
      }

    // Add transitions.
    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      if (!rhs.is_initial(*i))
      {
        for (typename rhs_t::delta_iterator d(rhs.value(), *i);
             ! d.done();
             d.next())
	  lhs.add_transition(map_h[*i],
			     map_h[rhs.dst_of(*d)],
			     rhs.label_of(*d));
      }


    r_hstate_t rhs_i = *rhs.initial().begin();

    concat_of_standard_here_common(lhs.structure(),
                                   lhs,
                                   rhs,
                                   rhs_i,
                                   lhs.final().begin(),
                                   lhs.final().end(),
                                   map_h);

    // Set transitions coming from rhs to final if needed.
    for_all_const_(map_t, nf, map_h)
      if (rhs.is_final(nf->first))
	lhs.set_final(nf->second, rhs.get_final(nf->first));
  }

  // Group the common part of the concat of standard automata algorithm.
  // - 'lhs' and 'rhs' are the two automata to concatanate.
  // - 'rhs_i' is the initial state of rhs.
  // - 'lhs_final_*' are respectively the begin and end iterator of the set
  // containing the final states of lhs.
  // - accessor is a view of the states of lhs states corresponding to rhs
  // states
  template<typename A, typename AI1, typename AI2, typename T1, typename T2>
  void
  concat_of_standard_here_common(const AutomataBase<A>&,
                                 Element<A, AI1>& lhs,
                                 const Element<A, AI2>& rhs,
                                 typename Element<A, AI2>::hstate_t& rhs_i,
                                 const T1& lhs_finals_b,
                                 const T1& lhs_finals_e,
                                 T2& accessor)
  {
    typedef Element<A, AI1>                     lhs_t;
    typedef Element<A, AI2>                     rhs_t;
    typedef T1                                  lhs_final_it_t;
    typedef typename rhs_t::delta_iterator      delta_iterator_t;
    typedef typename lhs_t::htransition_t       htransition_t;
    typedef std::list<htransition_t>            delta_ret_t;

    delta_ret_t dst;

    for (delta_iterator_t i(rhs.value(), rhs_i);
         ! i.done();
         i.next())
      dst.push_back(*i);

    // Concat final states of lhs to the rhs' intial state's followers.
    for (lhs_final_it_t f = lhs_finals_b;
         f != lhs_finals_e;
         ++f)
    {
      typename lhs_t::series_set_elt_t weight = lhs.get_final(*f);

      for_all_const_(delta_ret_t, d, dst)
        lhs.add_series_transition(*f,
                                  accessor[rhs.dst_of(*d)],
                                  weight * rhs.label_of(*d));
    }

    // Multiply final transitions of lhs by the final multiplicity of the
    // initial state of rhs.
    typename lhs_t::series_set_elt_t rhs_iw = rhs.get_final(rhs_i);

    for (lhs_final_it_t next = lhs_finals_b;
	 next != lhs_finals_e;)
    {
      lhs_final_it_t f = next;
      next++;
      lhs.set_final(*f, lhs.get_final(*f) * rhs_iw);
    }
  }

  template<typename A, typename AI1, typename AI2>
  void
  concat_of_standard_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    do_concat_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  concat_of_standard(const Element<A, AI1>& lhs,
		     const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    do_concat_of_standard_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*----------------.
  | standard_star.  |
  `----------------*/
  template <typename A, typename AI>
  void
  do_star_of_standard_here(const AutomataBase<A>&, Element<A, AI>& a)
  {
    precondition(is_standard(a));

    BENCH_TASK_SCOPED("star_of_standard");

    assertion (a.initial().size() == 1);
    typename Element<A, AI>::hstate_t new_i = *a.initial().begin();
    star_of_standard_here_common(a.structure(), a, new_i);
  }

  // Group the common part of the star of standard automata algorithm.
  template<typename A, typename AI>
  void
  star_of_standard_here_common(const AutomataBase<A>&,
                               Element<A, AI>& a,
                               typename Element<A, AI>::hstate_t& new_i)
  {
    typedef Element<A, AI>              automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef std::list<htransition_t>    delta_ret_t;

    // Let p a final state of A and i the initial state of A
    // and Tp the current value of the final transition of p
    // We have here: Tp = Tp * Ti.
    // We add transitions from p to all i's followers, labeled by
    // Ti*Tp*E(i,j) with E(i,j) the value of the transition from i to j.

    series_set_elt_t			out_mult = a.get_final(new_i);

    out_mult.star();

    delta_ret_t dst;

    for (delta_iterator i(a.value(), new_i);
         ! i.done();
         i.next())
      dst.push_back(*i);

    for_all_final_states(f, a)
    {
      if (*f != new_i)
      {
	series_set_elt_t f_mult = a.get_final(*f) * out_mult;
	a.set_final(*f, f_mult);

        for_all_const_(delta_ret_t, d, dst)
          a.add_series_transition(*f, a.dst_of(*d), f_mult * a.label_of(*d));
      }
    }
    a.set_final(new_i, out_mult);
  }

  template<typename A, typename AI>
  void
  star_of_standard_here(Element<A, AI>& a)
  {
    do_star_of_standard_here(a.structure(), a);
  }

  template<typename A, typename AI>
  Element<A, AI>
  star_of_standard(const Element<A, AI>& a)
  {
    Element<A, AI> ret(a);
    do_star_of_standard_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_STANDARD_HXX
