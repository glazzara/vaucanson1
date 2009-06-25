// extension.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_EXTENSION_HXX
# define VCSN_ALGORITHMS_EXTENSION_HXX

# include <vaucanson/algorithms/extension.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  template <typename S, typename K, typename T, typename Auto_t>
  typename identity_transducer_helper<S, K, T>::ret
  do_extension(const AutomataBase<S>& s,
	       const Auto_t& a)
  {
    AUTOMATON_TYPES(Auto_t);
    // ret_t is the type of the transducer returned.
    typedef typename identity_transducer_helper<S, K, T>::ret    ret_t;

    AUTOMATON_TYPES_(ret_t, t_);
    typedef typename ret_t::set_t		 set_t;
    typedef typename set_t::series_set_t	 o_series_set_t;
    typedef typename ret_t::series_set_elt_t	 output_series_set_elt_t;
    typedef typename series_set_elt_t::support_t support_t;

    set_t
      ts(o_series_set_t (a.structure().series(),
			 a.structure().series().monoid()));
    ret_t	   t_ret(ts);

    monoid_elt_t   neutre   = a.series().monoid().VCSN_EMPTY_;
    monoid_elt_t	t_neutre = t_ret.series().monoid().
      identity(SELECT(typename t_monoid_elt_t::value_t));

    std::vector<hstate_t>	conv(a.states().size());

    for_all_const_states (s, a)
      conv[t_ret.add_state()] = *s;

    for_all_const_transitions (e, a)
    {
      series_set_elt_t t = a.series_of(*e);
      series_set_elt_t s(t);
      output_series_set_elt_t os(t_ret.structure().series());
      support_t supp = s.supp();
      for_all_const_(support_t, m, supp)
      {
	series_set_elt_t tmp(a.structure().series());
	// try to associate the neutral monoid element with a weight
	// to create a series which will be a weight in the series os
	tmp.assoc(neutre, s.get(*m));
	os.assoc(*m, tmp);
      }
      htransition_t f = t_ret.add_series_transition(conv[a.src_of(*e)],
						    conv[a.dst_of(*e)],
						    os);
    }

    initial_iterator i;
    for (initial_iterator next = a.initial().begin();
	 next != a.initial().end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      i = next;
      next++;

      series_set_elt_t a_series = a.get_initial(*i);
      t_series_set_elt_t s;
      s.set(t_neutre, a_series);
      t_ret.set_initial(conv[*i], s);
    }

    final_iterator f;
    for (final_iterator next = a.final().begin();
	 next != a.final().end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      f = next;
      next++;
      series_set_elt_t a_series = a.get_final(*f);
      t_series_set_elt_t s;
      s.value_set(t_neutre, a_series);
      t_ret.set_final(conv[*f], s);
    }

    return t_ret;
  }

  template<typename S, typename K, typename T>
  typename identity_transducer_helper<S, K, T>::ret
  extension(const Element<S, T>& a)
  {
    BENCH_TASK_SCOPED("extension/1");
    return do_extension(a.structure(), a);
  }


  /*----------------.
  | Two arguments.  |
  `----------------*/


  template<typename SA, typename ST, typename Auto_t, typename Trans_t>
  Trans_t do_extension(const AutomataBase<SA>&,
		       const TransducerBase<ST>&,
		       const Auto_t& a,
		       const Trans_t& t)
  {
    AUTOMATON_TYPES_(Trans_t, t_);
    AUTOMATON_TYPES_(Auto_t, a_);
    typedef typename Auto_t::hstate_t hstate_t;
    typedef typename Trans_t::series_set_elt_t	t_output_series_set_elt_t;
    typedef typename Auto_t::series_set_elt_t::support_t a_support_t;
    typedef typename Trans_t::semiring_elt_t	t_weight_t;

    Trans_t		      tt(t.structure());
    std::map<hstate_t, hstate_t>   conv;

    a_monoid_elt_t a_neutre =
      a.series().monoid().identity(SELECT(typename a_monoid_elt_t::value_t));
    t_monoid_elt_t t_neutre =
      t.series().monoid().identity(SELECT(typename t_monoid_elt_t::value_t));

    for(a_state_iterator p = a.states().begin(); p != a.states().end(); ++p)
      conv[*p] = tt.add_state();

    // convert transitions
    for(a_transition_iterator e = a.transitions().begin();
	e != a.transitions().end(); ++e)
    {
      a_series_set_elt_t s_ = a.series_of(*e);
      a_series_set_elt_t s(s_);

      t_output_series_set_elt_t os(t.structure().series());

      a_support_t supp = s.supp();
      for(typename a_support_t::const_iterator m = supp.begin();
	  m != supp.end(); ++m)
      {
	t_weight_t tmp(t.structure().series().semiring());
	tmp.assoc(a_neutre, s.get(*m));
	os.assoc(a_monoid_elt_t (a.structure().series().monoid(), *m), tmp);
      }

      tt.add_series_transition(conv[a.src_of(*e)], conv[a.dst_of(*e)], os);
    }

    a_initial_iterator i;
    for (a_initial_iterator next = a.initial().begin();
	 next != a.initial().end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      i = next;
      next++;
      a_series_set_elt_t a_series = a.get_initial(*i);
      t_series_set_elt_t s (t.structure().series());
      s.assoc(t_neutre, a_series);
      tt.set_initial(conv[*i], s);
    }

    a_final_iterator f;
    for (a_final_iterator next = a.final().begin();
	 next != a.final().end();)
    {
      //We need to store the next iterator before using the current one
      //to avoid an invalid iterator after having called set_final.
      //Indeed, set_final can delete the iterator if its second parameter
      //is the zero of the serie.
      f = next;
      next++;
      a_series_set_elt_t a_series = a.get_final(*f);
      t_series_set_elt_t s (t.structure().series());
      s.assoc(t_neutre, a_series);
      tt.set_final(conv[*f], s);
    }

    return tt;
  }

  template<typename SA, typename TA, typename ST, typename TT>
  Element<ST, TT>
  extension(const Element<SA, TA>& a, const Element<ST, TT>& t)
  {
    BENCH_TASK_SCOPED("extension/2");
    return do_extension(a.structure(), t.structure(), a, t);
  }

}

#endif // ! VCSN_ALGORITHMS_EXTENSION_HXX
