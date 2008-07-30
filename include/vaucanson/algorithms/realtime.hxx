// realtime.hxx: this file is part of the Vaucanson project.
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
			typename Auto::hstate_t start,
			typename Auto::hstate_t stop,
			const Label& label, bool initial, bool final)
  {
    AUTOMATON_TYPES(Auto);
    hstate_t			s1;
    semiring_elt_t		s_ident = algebra::identity_as<semiring_elt_value_t>
      ::of(a.structure().series().semiring());


    if (label.supp().begin() == label.supp().end())
      return 0;

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

    vector_t tmp;
    tmp.reserve(res.initial().size());
    for_all_const_initial_states(i, res)
      tmp.push_back(*i);
    for_all(typename vector_t, i, tmp)
      do_realtime_words(res, hstate_t(), *i, res.get_initial(*i), true, false);
    tmp.clear();
    for_all_const_final_states(f, res)
      tmp.push_back(*f);
    for_all(typename vector_t, f, tmp)
      do_realtime_words(res, *f, hstate_t(), res.get_final(*f), false, true);

    transitions_t transitions = res.transitions();
    for_all_(transitions_t, e, transitions)
      if (do_realtime_words(res, res.src_of(*e), res.dst_of(*e),
			    res.series_of(*e), false, false))
	res.del_transition(*e);
  }



  /*--------------.
  | is_realtime.  |
  `--------------*/
  template <class A, typename AI>
  bool
  do_is_realtime(const AutomataBase<A>&, const Element<A, AI>& a)
  {
    TIMER_SCOPED("is_realtime (automaton)");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    for_all_const_transitions(e, a)
      if (!is_support_in_alphabet(a.series_of(*e)))
	return false;
    return true;
  }


  /*--------------.
  | realtime_here. |
  `--------------*/

  template<typename A, typename AI>
  void
  do_realtime_here(const AutomataBase<A>&,
                   Element<A, AI>& a,
		   misc::direction_type dir = misc::backward)
  {
    realtime_words_here(a);

    eps_removal_here(a, dir);

    // FIXME: This is not wanted.  See #121.
    if (dir == misc::forward)
      coaccessible_here(a);
    else
      accessible_here(a);
  }


  template<typename A, typename AI>
  void
  realtime_here(Element<A, AI>& a, misc::direction_type dir)
  {
    do_realtime_here(a.structure(), a, dir);
  }


  /*-----------.
  | realtime.  |
  `-----------*/

  template<typename A, typename AI>
  Element<A, AI>
  do_realtime(const AutomataBase<A>& b,
	      const Element<A, AI>&  a,
	      misc::direction_type dir = misc::backward)
  {
    Element<A, AI> ret(a);
    do_realtime_here(b, ret, dir);
    return ret;
  }

  template<typename A, typename AI>
  Element<A, AI>
  realtime(const Element<A, AI>& a, misc::direction_type dir)
  {
    return do_realtime(a.structure(), a, dir);
  }


} // vcsn

#endif // ! VCSN_ALGORITHMS_REALTIME_HXX
