// backward_realtime.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX
# define VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX

# include <vaucanson/algorithms/backward_realtime.hh>
# include <vaucanson/algorithms/cut_up.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/eps_removal.hh>
# include <vaucanson/algorithms/accessible.hh>

# include <queue>
# include <set>

namespace vcsn {



  /*--------------------------------------------.
  | Special treatment to cut words into letters |
  `--------------------------------------------*/

  template <class Auto, class Label>
  int do_realtime_words(Auto& a,
			hstate_t start, hstate_t stop,
			const Label& label, bool initial, bool final)
  {
    AUTOMATON_TYPES(Auto);
    hstate_t			s1;

    semiring_elt_t s_ident =
      algebra::identity_as<semiring_elt_value_t>
      ::of(a.structure().series().semiring());

    monoid_elt_t m1(a.structure().series().monoid(), *label.supp().begin());
    monoid_elt_value_t w1 = m1.value();

    int cpt = 0;

    unsigned int size = w1.size();

    if (size > 1)
    {
      monoid_elt_t m(a.structure().series().monoid());

      semiring_elt_t s = label.get(m1);
      series_set_elt_t in_series(a.structure().series());

      m = w1.substr(cpt++, 1);

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

      for (unsigned int i = 1; i < size - 1; ++i)
      {
	m = w1.substr(cpt++, 1);
	hstate_t s0 = s1;
	s1 = a.add_state();
	series_set_elt_t series(a.structure().series());
	series.assoc(m, s_ident);
	a.add_series_transition(s0, s1, series);
      }

      m = w1.substr(cpt++, 1);

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

    transitions_t transitions = res.transitions();
    vector_t i_states; i_states.reserve(res.initial().size());
    vector_t f_states; f_states.reserve(res.final().size());

    for_all_initial_states(f, res)
      i_states.push_back(*f);
    for_all_final_states(i, res)
      f_states.push_back(*i);

    for_all_(vector_t, i, i_states)
      do_realtime_words(res, hstate_t(), *i,
			res.get_initial(*i), true, false);

    for_all_(vector_t, f, f_states)
      do_realtime_words(res, *f, hstate_t(),
			res.get_final(*f), false, true);

    for_all_(transitions_t, e, transitions)
      if (do_realtime_words(res, res.src_of(*e), res.dst_of(*e),
			    res.series_of(*e), false, false))
	res.del_transition(*e);
  }


  template <class A_, typename Auto_>
  void
  do_backward_realtime_here(const AutomataBase<A_>&, Auto_& a)
  {
    AUTOMATON_TYPES(Auto_);
    typedef std::set<htransition_t>			delta_ret_t;
    typedef std::deque<htransition_t>			queue_t;

    queue_t		to_del, origin_d;
    delta_ret_t		aim_d;
    monoid_elt_t	monoid_identity =
      algebra::identity_as<monoid_elt_value_t>::
      of(a.structure().series().monoid());
    semiring_elt_t	semiring_zero =
      algebra::zero_as<semiring_elt_value_t>::
      of(a.structure().series().semiring());
    series_set_elt_t	series_identity =
      algebra::identity_as<series_set_elt_value_t>::of(a.structure().series());

    backward_eps_removal_here(a);

    for (typename automaton_t::state_iterator origin = a.states().begin();
	 origin != a.states().end();
	 ++origin)
    {
      std::insert_iterator<queue_t> origin_i(origin_d, origin_d.begin());
      a.delta(origin_i, *origin, delta_kind::transitions());

      while (!origin_d.empty())
      {
	htransition_t d_o = origin_d.front();
	origin_d.pop_front();
	if (a.series_of(d_o).get(monoid_identity) != semiring_zero)
	{
	  aim_d.clear();
	  a.deltac(aim_d, a.dst_of(d_o), delta_kind::transitions());
	  for (typename delta_ret_t::const_iterator d = aim_d.begin();
	       d != aim_d.end();
	       ++d)
	    if (a.series_of(*d).get(monoid_identity) == semiring_zero)
	    {
	      bool new_transition = true;
	      for (typename queue_t::const_iterator d__o =
		     origin_d.begin();
		   d__o != origin_d.end();
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
		  (*origin,
		   a.dst_of(*d),
		   a.series_of(d_o) * a.series_of(*d));
		origin_d.push_back(new_htransition);
	      }
	    }
	  if (a.is_final(a.dst_of(d_o)))
	    a.set_final(*origin);
	}
      }
    }

    for (typename automaton_t::transition_iterator e = a.transitions().begin();
	 e != a.transitions().end();
	 ++e)
      if (a.series_of(*e).get(monoid_identity) != semiring_zero)
	to_del.push_back(*e);

    while (!to_del.empty())
    {
      htransition_t e = to_del.front();
      to_del.pop_front();
      a.del_transition(e);
    }

    accessible_here(a);

    realtime_words_here(a);
  }


  template<typename A, typename T>
  void
  backward_realtime_here(Element<A, T>& a)
  {
    do_backward_realtime_here(a.structure(), a);
  }

  template <class A_, typename Auto_>
  Auto_
  do_backward_realtime(const AutomataBase<A_>&, const Auto_& a)
  {
    Auto_ ret(a);
    do_backward_realtime_here(ret.structure(), ret);
    return ret;
  }

  template<typename A, typename T>
  Element<A, T>
  backward_realtime(const Element<A, T>& a)
  {
    return do_backward_realtime(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_BACKWARD_REALTIME_HXX
