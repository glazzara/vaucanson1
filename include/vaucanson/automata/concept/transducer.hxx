// transducer.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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

  template <class Series>
  Transducer<Series>::Transducer(const series_set_t& s):
    SetSlot<Series>(s)
  {}

  template <class Series>
  const typename Transducer<Series>::series_set_t&
  Transducer<Series>::series() const
  {
    return this->_structure_get();
  }

  template <class Series>
  bool
  operator==(const Transducer<Series>& lhs,
	     const Transducer<Series>& rhs)
  {
    return & lhs.series() == & rhs.series();
  }

  template <class S, class T>
  typename identity_transducer_helper<S, T>::ret
  partial_identity(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename identity_transducer_helper<S, T>::ret  ret_t;
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
