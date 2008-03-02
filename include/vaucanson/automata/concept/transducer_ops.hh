// transducer_ops.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

#define AutoType(Type)				\
  typename Element<S, T>::Type

  template <class S, class T>
  typename Element<S, T>::input_monoid_elt_t
  op_input_of(const TransducerBase<S>& s,
	      const T& v,
	      typename automaton_traits<T>::htransition_t e);

  template <class S, class T>
  typename Element<S, T>::output_series_set_elt_t
  op_output_of(const TransducerBase<S>& s,
	       const T& v,
	       typename automaton_traits<T>::htransition_t e);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_io_transition(const TransducerBase<S>& s,
		       T& v,
		       typename automaton_traits<T>::hstate_t from,
		       typename automaton_traits<T>::hstate_t to,
		       AutoType(input_letter_t) i,
		       AutoType(output_letter_t) o,
		       AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_io_transition(const TransducerBase<S>& s,
		       T& v,
		       typename automaton_traits<T>::hstate_t from,
		       typename automaton_traits<T>::hstate_t to,
		       AutoType(input_monoid_elt_t) input_w,
		       AutoType(output_monoid_elt_t) output_w,
		       AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_i_transition(const TransducerBase<S>& s,
		      T& v,
		      typename automaton_traits<T>::hstate_t from,
		      typename automaton_traits<T>::hstate_t to,
		      AutoType(input_letter_t) i,
		      AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  typename automaton_traits<T>::htransition_t
  op_add_o_transition(const TransducerBase<S>& s,
		      T& v,
		      typename automaton_traits<T>::hstate_t from,
		      typename automaton_traits<T>::hstate_t to,
		      AutoType(input_letter_t) o,
		      AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  static AutoType(series_set_elt_t)
  make_series(const TransducerBase<S>& s,
	      AutoType(output_monoid_elt_value_t) o);

  template <class S, class T>
  void
  op_set_o_final(const TransducerBase<S>& s,
		 T& v,
		 typename automaton_traits<T>::hstate_t final,
		 AutoType(output_monoid_elt_value_t) o);

  template <class S, class T>
  void
  op_set_o_initial(const TransducerBase<S>& s,
		   T& v,
		   typename automaton_traits<T>::hstate_t initial,
		   AutoType(output_monoid_elt_value_t) o);
} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/transducer_ops.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
