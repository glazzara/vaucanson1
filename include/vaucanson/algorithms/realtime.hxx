// realtime.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_REALTIME_HXX
# define VCSN_ALGORITHMS_REALTIME_HXX

# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/algorithms/eps_removal.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/algorithms/cut_up.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <deque>
# include <set>

namespace vcsn {


  /*--------------------.
  | do_realtime_words.  |
  `--------------------*/

  template <class Auto, class Label>
  int do_realtime_words(Auto& a,
			hstate_t start, hstate_t stop,
			const Label& label, bool initial, bool final)
  {
    AUTOMATON_TYPES(Auto);
    hstate_t			s1;
    semiring_elt_t		s_ident = algebra::identity_as<semiring_elt_value_t>
      ::of(a.structure().series().semiring());


    monoid_elt_t m1(a.structure().series().monoid(), *label.supp().begin());
    monoid_elt_value_t w1 = m1.value();

    unsigned int size = m1.length();

    if (size > 1)
    {
      monoid_elt_t m(a.structure().series().monoid());

      semiring_elt_t s = label.get(m1);
      series_set_elt_t in_series(a.structure().series());
      typename monoid_elt_t::iterator l = m1.begin();

      m = *l;

      in_series.assoc(m, s);

      if (initial)
      {
	hstate_t s0 = a.add_state();
	a.set_initial(s0, in_series);
	a.unset_initial(stop);
	s1 = s0;
      }
      else
      {
	hstate_t s0 = start;
	s1 = a.add_state();
	a.add_series_transition(s0, s1, in_series);
      }

      l++;
      for (typename monoid_elt_t::iterator end = m1.begin() + (size - 1);
	   l != end; ++l)
      {
	m = *l;
	hstate_t s0 = s1;
	s1 = a.add_state();
	series_set_elt_t series(a.structure().series());
	series.assoc(m, s_ident);
	a.add_series_transition(s0, s1, series);
      }

      m = *l;

      series_set_elt_t out_series(a.structure().series());
      out_series.assoc(m, s_ident);

      if (final)
      {
	a.unset_final(start);
	a.set_final(s1, out_series);
      }
      else
	a.add_series_transition(s1, stop, out_series);

      return 1;
    }

    return 0;
  }


  template <class S, class T>
  void realtime_words_here(Element<S, T>& res)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);
    typedef std::vector<hstate_t> vector_t;

    // perform cut-up.
    cut_up_here(res);

    vector_t tmp(res.initial().size());
    for_all_initial_states(i, res)
      tmp.push_back(*i);
    for_all(vector_t, i, tmp)
      do_realtime_words(res, hstate_t(), *i, res.get_initial(*i), true, false);

    tmp.clear();
    for_all_final_states(f, res)
      tmp.push_back(*f);
    for_all(vector_t, f, tmp)
      do_realtime_words(res, *f, hstate_t(), res.get_final(*f), false, true);

    transitions_t transitions = res.transitions();
    for_all_(transitions_t, e, transitions)
      if (do_realtime_words(res, res.src_of(*e), res.dst_of(*e), res.series_of(*e), false, false))
	res.del_transition(*e);
  }



  /*--------------.
  | is_realtime.  |
  `--------------*/
  template <class A_, typename Auto_>
  bool
  do_is_realtime(const AutomataBase<A_>&,
		 const Auto_&		   a)
  {
    for (typename Auto_::transition_iterator e = a.transitions().begin();
	 e != a.transitions().end();
	 ++e)
      if (a.series_of(*e) ==
	  a.structure().series().
	  identity(SELECT(typename Auto_::series_set_elt_value_t)))
	return false;
    return true;
  }


  /*--------------.
  | realtime_here. |
  `--------------*/

  template<typename Auto_, typename A_>
  void
  do_realtime_here(const AutomataBase<A_>&, Auto_& a,
		   misc::direction_type type = misc::forward)
  {
    typedef Auto_ automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef std::set<htransition_t> delta_ret_t;
    typedef std::deque<htransition_t> queue_t;

    queue_t		  to_del, src_d;
    delta_ret_t		  dst_d;
    monoid_elt_t	  monoid_identity =
      algebra::identity_as<monoid_elt_value_t>::
      of(a.structure().series().monoid());
    semiring_elt_t		  semiring_zero =
      algebra::zero_as<semiring_elt_value_t>::
      of(a.structure().series().semiring());
    series_set_elt_t	      series_identity =
      algebra::identity_as<series_set_elt_value_t>::of(a.structure().series());

    eps_removal_here(a, type);

    for_all_states(src, a)
    {
      std::insert_iterator<queue_t> src_i(src_d, src_d.begin());
      a.delta(src_i, *src, delta_kind::transitions());

      while (!src_d.empty())
      {
	htransition_t d_o = src_d.front();
	src_d.pop_front();
	if (a.series_of(d_o).get(monoid_identity) != semiring_zero)
	{
	  dst_d.clear();
	  a.deltac(dst_d, a.dst_of(d_o), delta_kind::transitions());
	  for (typename delta_ret_t::const_iterator d = dst_d.begin();
	       d != dst_d.end();
	       ++d)
	    if (a.series_of(*d).get(monoid_identity) == semiring_zero)
	    {
	      bool new_transition = true;
	      for (typename queue_t::const_iterator d__o =
		     src_d.begin();
		   d__o != src_d.end();
		   ++d__o)
		if ((a.dst_of(*d__o) == a.dst_of(*d) &&
		     (a.label_of(*d__o) == a.label_of(*d))))
		{
		  new_transition = false;
		  break;
		}

	      if (new_transition)
	      {
		htransition_t new_htransition = a.add_series_transition
		  (*src,
		   a.dst_of(*d),
		   a.series_of(d_o) * a.series_of(*d));
		src_d.push_back(new_htransition);
	      }
	    }
	  if (a.is_final(a.dst_of(d_o)))
	    a.set_final(*src);
	}
      }
    }

    for_all_transitions (t, a)
      if (a.series_of(*t).get(monoid_identity) != semiring_zero)
	to_del.push_back(*t);

    while (!to_del.empty())
    {
      htransition_t t = to_del.front();
      to_del.pop_front();
      a.del_transition(t);
    }

    if (type == misc::forward)
      coaccessible_here(a);
    else
      accessible_here(a);

    realtime_words_here(a);
  }


  template<typename S, typename T>
  void
  realtime_here(Element<S, T>& a, misc::direction_type type)
  {
    do_realtime_here(a.structure(), a, type);
  }


  /*-----------.
  | realtime.  |
  `-----------*/

  template<typename Auto_, typename A_>
  Auto_
  do_realtime(const AutomataBase<A_>&b,
	      const Auto_& a,
	      misc::direction_type type = misc::forward)
  {
    Auto_ ret(a);
    do_realtime_here(b, ret, type);
    return ret;
  }

  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, misc::direction_type type)
  {
    return do_realtime(a.structure(), a, type);
  }


} // vcsn

#endif // ! VCSN_ALGORITHMS_REALTIME_HXX
