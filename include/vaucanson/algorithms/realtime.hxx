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

  template <class Auto>
  void do_realtime_words(Auto& a)
  {
    AUTOMATON_TYPES(Auto);
    hstate_t			s1;
    semiring_elt_t		s_ident = algebra::identity_as<semiring_elt_value_t>
      ::of(a.structure().series().semiring());

    typedef std::vector<htransition_t> transition_vector_t;
    transitions_t transitions = a.transitions();
    transition_vector_t tmp_trans;
    for_all_(transitions_t, e, transitions)
      tmp_trans.push_back(*e);

    for_all(typename transition_vector_t, e, tmp_trans)
    {
      hstate_t start = a.src_of(*e);
      hstate_t stop = a.dst_of(*e);
      series_set_elt_t label = a.series_of(*e);

      assert(label.supp().begin() != label.supp().end());

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

        s1 = a.add_state();
        a.add_series_transition(start, s1, in_series);

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

        a.add_series_transition(s1, stop, out_series);
        a.del_transition(*e);
      }
    }
  }


  template <class S, class T>
  void realtime_words_here(Element<S, T>& res)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);
    typedef std::vector<hstate_t> state_vector_t;
    typedef std::vector<htransition_t> transition_vector_t;
    state_vector_t tmp;

    // perform cut-up.
    cut_up_here(res);

    // Remove any labels from initial arrows.
    tmp.reserve(res.initial().size());
    for_all_const_initial_states(i, res)
      tmp.push_back(*i);
    for_all(typename state_vector_t, i, tmp)
    {
      series_set_elt_t l = res.get_initial(*i);
      assert(l.supp().begin() != l.supp().end());
      monoid_elt_t m(res.structure().series().monoid(), *l.supp().begin());
      if (m.length() > 0)
      {
        hstate_t s = res.add_state();
        res.add_series_transition(s, *i, l);
        res.set_initial(s);
        res.unset_initial(*i);
      }
    }
    tmp.clear();

    // Remove any labels from final arrows.
    tmp.reserve(res.final().size());
    for_all_const_final_states(f, res)
      tmp.push_back(*f);
    for_all(typename state_vector_t, f, tmp)
    {
      series_set_elt_t l = res.get_final(*f);
      assert(l.supp().begin() != l.supp().end());
      monoid_elt_t m(res.structure().series().monoid(), *l.supp().begin());
      if (m.length() > 0)
      {
	hstate_t s = res.add_state();
	res.add_series_transition(*f, s, l);
	res.set_final(s);
	res.unset_final(*f);
      }
    }

    // Make the transitions realtime (now includes any former initial
    // or final labels).
    do_realtime_words(res);
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
    for_all_const_initial_states(e, a)
      {
	series_set_elt_t l = a.get_initial(*e);
	if (l.supp().size() > 1)
	  return false;
	// We assume that an initial transition cannot be labeled by
	// the empty series.  In other words, l.size() >= 1.
	assertion(l.supp().size() == 1);
	monoid_elt_t m(a.structure().series().monoid(), *l.supp().begin());
	if (m.length() > 0)
	  return false;
      }
    for_all_const_final_states(e, a)
      {
	series_set_elt_t l = a.get_final(*e);
	if (l.supp().size() > 1)
	  return false;
	// We assume that a final transition cannot be labeled by
	// the empty series.  In other words, l.size() >= 1.
	assertion(l.supp().size() == 1);
	monoid_elt_t m(a.structure().series().monoid(), *l.supp().begin());
	if (m.length() > 0)
	  return false;
      }
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
