// transducer.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX

# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

  template <typename Series, typename Kind>
  Transducer<Series, Kind>::Transducer(const series_set_t& s):
    SetSlot<Series>(s)
  {}

  template <typename Series, typename Kind>
  const typename Transducer<Series, Kind>::series_set_t&
  Transducer<Series, Kind>::series() const
  {
    return this->_structure_get();
  }

  template <typename Series, typename Kind>
  bool
  operator==(const Transducer<Series, Kind>& lhs,
	     const Transducer<Series, Kind>& rhs)
  {
    return & lhs.series() == & rhs.series();
  }

  //
  // Projections for RW transducers
  //

  template <typename S, typename K, typename T>
  inline typename input_projection_helper<Transducer<S, K>, T>::ret
  input_projection_helper<Transducer<S, K>, T>::
  make_input_projection_automaton(const Element<Transducer<S, K>, T>& t)
  {
    // Type helpers.
    typedef typename ret::set_t set_t;
    typedef typename set_t::series_set_t series_set_t;

    set_t
    auto_set(series_set_t(t.structure().series().
			  semiring().semiring(), t.structure().
			  series().monoid()));

    return ret(auto_set);
  }

  template <typename S, typename K, typename T>
  inline typename output_projection_helper<Transducer<S, K>, T>::ret
  output_projection_helper<Transducer<S, K>, T>::
  make_output_projection_automaton(const Element<Transducer<S, K>, T>& t)
  {
    // Type helpers.
    typedef typename ret::set_t set_t;
    typedef typename set_t::series_set_t series_set_t;

    set_t
    auto_set(series_set_t(t.structure().series().semiring()));

    return ret(auto_set);
  }

  //
  // Projections for FMP transducers
  //

  template <typename S, typename K, typename T>
  inline typename input_projection_helper<Automata<S, K>, T>::ret
  input_projection_helper<Automata<S, K>, T>::
  make_input_projection_automaton(const Element<Automata<S, K>, T>& t)
  {
    // Type helpers.
    typedef typename ret::set_t set_t;
    typedef typename set_t::series_set_t series_set_t;

    set_t
    auto_set(series_set_t(t.structure().series().
			  semiring(), t.structure().series().
			  monoid().first_monoid()));

    return ret(auto_set);
  }

  template <typename S, typename K, typename T>
  inline typename output_projection_helper<Automata<S, K>, T>::ret
  output_projection_helper<Automata<S, K>, T>::
  make_output_projection_automaton(const Element<Automata<S, K>, T>& t)
  {
    // Type helpers.
    typedef typename ret::set_t set_t;
    typedef typename set_t::series_set_t series_set_t;

    set_t
    auto_set(series_set_t(t.structure().series().
			  semiring(), t.structure().series().
			  monoid().second_monoid()));

    return ret(auto_set);
  }

  template <typename S, typename K, typename T>
  typename identity_transducer_helper<S, K, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, K, T>::ret  ret_t;
    typedef typename ret_t::series_set_elt_t output_series_set_elt_t;
    typedef typename series_set_elt_t::support_t support_t;
    typedef typename ret_t::set_t set_t;
    typedef typename set_t::series_set_t o_series_set_t;
    set_t s (o_series_set_t (a.structure().series(),
			     a.structure().series().monoid()));
    ret_t ret(s);
    std::vector<hstate_t> conv(a.states().size());

    for_all_states(s, a)
      conv[ret.add_state()] = *s;
    for_all_transitions(e, a)
    {
      series_set_elt_t t = a.series_of(*e);
      series_set_elt_t s(t);
      output_series_set_elt_t os(ret.structure().series());
      support_t supp = s.supp();
      for_all_const_(support_t, m, supp)
      {
	series_set_elt_t tmp(a.structure().series());
	tmp.assoc(*m, s.get(*m));
	os.assoc(*m, tmp);
      }
      htransition_t f = ret.add_series_transition(conv[a.src_of(*e)],
						  conv[a.dst_of(*e)],
						  os);
    }
    // FIXME: set initial/final weights.
    for_all_initial_states(i, a)
      ret.set_initial(conv[*i], a.get_initial(*i));
    for_all_final_states(f, a)
      ret.set_final(conv[*f], a.get_final(*f));
    return ret;
  }

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_HXX
