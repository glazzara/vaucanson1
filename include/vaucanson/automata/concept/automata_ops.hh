// automata_ops.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HH

/** @addtogroup automata *//** @{ */
/** @addtogroup automata_ops Operators on automata *//** @{ */
/**
 * @file automata_ops.hh
 *
 * This file holds the default operations for the elements of the automata set.
 */
/** @} */
/** @} */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

#define AutoType(Type)				\
  typename Element<S, T>::Type

  /** @addtogroup automata *//** @{ */
  /** @addtogroup automata_ops *//** @{ */

  /// @name Default operation on automata.
  //@{

  template <class S, class T>
  const typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, const T&);

  template <class S, class T>
  typename automaton_traits<T>::tag_t&
  op_get_tag(const AutomataBase<S>&, T&);

  template <class S, class T>
  const typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, const T&);

  template <class S, class T>
  typename automaton_traits<T>::geometry_t&
  op_get_geometry(const AutomataBase<S>&, T&);

  template <class S, class T>
  bool
  op_exists(const AutomataBase<S>& s, const T&);

  template <class S, class T>
  typename automaton_traits<T>::states_t
  op_states(const AutomataBase<S>&, const T&);

  template <class S, class T>
  typename automaton_traits<T>::transitions_t
  op_transitions(const AutomataBase<S>&, const T&);

  template <class S, class T>
  typename automaton_traits<T>::initial_support_t
  op_initial(const AutomataBase<S>&, const T&);

  template <class S, class T>
  typename automaton_traits<T>::final_support_t
  op_final(const AutomataBase<S>&, const T&);

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>&, T&,
		 hstate_t state,
		 const AutoType(series_set_elt_t)& s);

  template <class S, class T>
  AutoType(series_set_elt_t)
  op_get_initial(const AutomataBase<S>&,
		 const T&,
		 hstate_t state);

  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>&, T&,
	       hstate_t state,
	       const typename Element<S, T>::series_set_elt_t& s);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>&,
	       const T&,
	       hstate_t state);

  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, T&);

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, T&);

  template <class S, class T>
  hstate_t
  op_add_state(const AutomataBase<S>&, T&);

  template <class S, class T>
  hstate_t
  op_choose_state(const AutomataBase<S>&, T&);

  template <class S, class T>
  htransition_t
  op_add_transition(const AutomataBase<S>&, T&,
		    hstate_t from,
		    hstate_t to,
		    const typename Element<S, T>::label_t& label);

  template<class S, class T>
  htransition_t
  op_add_weighted_transition(const AutomataBase<S>&, T&,
			     hstate_t from,
			     hstate_t to,
			     const typename Element<S, T>::semiring_elt_t& w,
			     const typename Element<S, T>::monoid_elt_value_t& m);

  template <class S, class T>
  htransition_t
  op_add_series_transition(const AutomataBase<S>&, T&,
			   hstate_t from,
			   hstate_t to,
			   const typename Element<S, T>::series_set_elt_t&);

  template <class S, class T>
  htransition_t
  op_add_spontaneous(const AutomataBase<S>&, T&,
		     hstate_t from,
		     hstate_t to,
		     const typename Element<S, T>::semiring_elt_t&);

  template <class S, class T>
  htransition_t
  op_add_letter_transition(const AutomataBase<S>&, T&,
			   hstate_t from,
			   hstate_t to,
			   const typename Element<S, T>::letter_t&);

  template <class S, class T>
  void
  op_update(const AutomataBase<S>&, T&,
	    htransition_t,
	    const AutoType(label_t)& l);

  template <class S, class T>
  void
  op_del_state(const AutomataBase<S>&, T&,
	       hstate_t);

  template <class S, class T>
  void
  op_del_transition(const AutomataBase<S>&, T&,
		    htransition_t);

  template <class S, class T>
  bool
  op_has_state(const AutomataBase<S>&, const T&,
	       hstate_t);

  template <class S, class T>
  bool
  op_has_transition(const AutomataBase<S>&, const T&,
		    htransition_t);

  template <class S, class T>
  hstate_t
  op_src_of(const AutomataBase<S>&, const T&,
	    htransition_t);

  template <class S, class T>
  hstate_t
  op_dst_of(const AutomataBase<S>&, const T&,
	    htransition_t);

  template <class S, class T>
  typename Element<S, T>::label_t
  op_label_of(const AutomataBase<S>&, const T&,
	      htransition_t);

  template <class S, class T>
  const typename Element<S, T>::series_set_elt_t
  op_series_of(const AutomataBase<S>&, const T&,
	       htransition_t);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_value_t
  op_series_value_of(const AutomataBase<S>&, const T&,
		     htransition_t);


  template <class S, class T>
  typename Element<S, T>::monoid_elt_t
  op_word_of(const AutomataBase<S>&, const T&,
	     htransition_t);

  template <class S, class T>
  typename Element<S, T>::semiring_elt_t
  op_weight_of(const AutomataBase<S>&, const T&,
	       htransition_t);

  template <class S, class T>
  typename Element<S, T>::monoid_elt_value_t
  op_word_value_of(const AutomataBase<S>&, const T&,
		   htransition_t);

  template <class S, class T>
  typename Element<S, T>::letter_t
  op_letter_of(const AutomataBase<S>&, const T&,
	       htransition_t);

  template <class S, class T>
  bool
  op_is_spontaneous(const AutomataBase<S>&, const T&,
		    htransition_t);

  //@}

  // output_return_type = OutputIterator
  // output_type	= htransition_t
  // direction		= output

  /// store the output transitions of the state 'from' using 'res'.
  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_delta(const AutomataBase<S>&, const T&,
		OutputIterator res,
		hstate_t from,
		delta_kind::kind<Kind> k);

  /**
   * Delta using a query, with iterator output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_delta(const AutomataBase<S>&, const T&,
		OutputIterator res,
		hstate_t from,
		const L& query,
		delta_kind::kind<Kind> k);

  /**
   * Delta on a letter, with iterator output.
   *
   * Store  the output	transitions  of	 the state  'from'  where the  label
   * matches the letter.
   */
  template <class S, class T,
	    typename OutputIterator, typename L, typename Kind>
  void op_letter_delta(const AutomataBase<S>&, const T&,
		       OutputIterator res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::kind<Kind> k);

  /// Store the output spontaneous transitions.
  template <class S, class T,
	    typename OutputIterator, typename Kind>
  void op_spontaneous_delta(const AutomataBase<S>&, const T&,
			    OutputIterator res,
			    hstate_t from,
			    delta_kind::kind<Kind> k);

  // output_return_type = Container
  // output_type	= htransition_t
  // direction		= output

  /// Store the output transitions of the state 'from' in the container 'res'.
  template <class S, class T,
	    typename Container, typename Kind>
  void op_deltac(const AutomataBase<S>&, const T&,
		 Container& res, hstate_t from, delta_kind::kind<Kind> k);

  /**
   * Delta using a query, with container output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_deltac(const AutomataBase<S>&, const T&,
		 Container& res,
		 hstate_t from,
		 const L& query,
		 delta_kind::kind<Kind> k);

  /**
   * Delta on a letter, with container output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template <class S, class T,
	    typename Container, typename L, typename Kind>
  void op_letter_deltac(const AutomataBase<S>&, const T&,
			Container& res,
			hstate_t from,
			const L& letter,
			delta_kind::kind<Kind> k);

  /// Store the output op_spontaneous transitions.
  template <class S, class T, class Container, typename Kind>
  void op_spontaneous_deltac(const AutomataBase<S>&, const T&,
			     Container& res,
			     hstate_t from,
			     delta_kind::kind<Kind> k);

  // output_return_type = OutputIterator
  // output_type	= hstate_t
  // direction		= output

  // output_return_type = OutputIterator
  // output_type	= htransition_t
  // direction		= input

  /// Store the output transitions of the state 'from' using 'res'.
  template<class S, class T, typename OutputIterator, typename Kind>
  void op_rdelta(const AutomataBase<S>&, const T&,
		 OutputIterator res,
		 hstate_t from,
		 delta_kind::kind<Kind> k);

  /**
   * Reverse delta using a query, with iterator output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template<class S, class T, typename OutputIterator, typename L, typename Kind>
  void op_rdelta(const AutomataBase<S>&, const T&,
		 OutputIterator res,
		 hstate_t from,
		 const L& query,
		 delta_kind::kind<Kind> k);

  /**
   * Reverse delta on a letter, with iterator output.
   *
   * Store  the output	transitions  of	 the state  'from'  where the  label
   * matches the letter.
   */
  template<class S, class T, typename OutputIterator, typename L, typename Kind>
  void op_letter_rdelta(const AutomataBase<S>&, const T&,
			OutputIterator res,
			hstate_t from,
			const L& letter,
			delta_kind::kind<Kind> k);

  /// Store the output op_spontaneous transitions.
  template<class S, class T, typename OutputIterator, typename Kind>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const T&,
			     OutputIterator res,
			     hstate_t from,
			     delta_kind::kind<Kind> k);

  // output_return_type = Container
  // output_type	= htransition_t
  // direction		= input

  /// store the output transitions of the state 'from' in the container 'res'.
  template<class S, class T, typename Container, typename Kind>
  void op_rdeltac(const AutomataBase<S>&, const T&,
		  Container& res, hstate_t from, delta_kind::kind<Kind> k);

  /**
   * Reverse delta using a query, with container output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L, typename Kind>
  void op_rdeltac(const AutomataBase<S>&, const T&,
		  Container& res,
		  hstate_t from,
		  const L& query,
		  delta_kind::kind<Kind> k);

  /**
   * Reverse delta on a letter, with container output.
   *
   * Store the output transitions  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L, typename Kind>
  void op_letter_rdeltac(const AutomataBase<S>&, const T&,
			 Container& res,
			 hstate_t from,
			 const L& letter,
			 delta_kind::kind<Kind> k);

  /// store the output op_spontaneous transitions.
  template<class S, class T, typename Container, typename Kind>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const T&,
			      Container& res,
			      hstate_t from,
			      delta_kind::kind<Kind> k);

  // output_return_type = OutputIterator
  // output_type	= hstate_t
  // direction		= input

  /** @} */
  /** @} */

} // vcsn


#  include <vaucanson/automata/concept/automata_ops.hxx>


#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_OPS_HH
