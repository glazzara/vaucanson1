// transpose_view.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HH

# include <vaucanson/automata/implementation/automaton_view.hh>
# include <vaucanson/design_pattern/predecls.hh>

namespace vcsn {

  /**
   * @brief Provides a transposed view of an automaton.
   *
   * This  structure  allow  a  programmer  to work  on  a  transposed
   * automaton   without  having   really   transposed  the   original
   * automaton.  It  is  just  a  kind of  proxy  for  an  automaton's
   * implementation.
   *
   * @see transpose()
   */
  template <class T>
  struct TransposeView : public IdentityView<T>
  {
    TransposeView();
    TransposeView(const T&);
    TransposeView(T&);
    TransposeView(const TransposeView&);
  };

  /// Traits for TransposeView.
  /** @{ */
  template <class T>
  struct transpose_traits
  {
    typedef undefined_type type;
  };

  template <class S, class T>
  struct transpose_traits<Element<S, T> >
  {
    typedef Element<S, TransposeView<T> > type;
  };
  /** @} */

  /**
   * @brief This function creates a transposed view of an automaton.
   *
   * @see transpose(), TransposeView
   */
  /** @{ */
  template <class S, class T>
  Element<S, TransposeView<T> >
  transpose_view(Element<S, T>&);

  template <class S, class T>
  const Element<S, TransposeView<T> >
  transpose_view(const Element<S, T>&);
  /** @} */

  /// automaton_traits specialization for the TransposeView implementation.
  template <typename T>
  struct automaton_traits<TransposeView<T> >
  {
    typedef typename automaton_traits<T>::label_t	label_t;
    typedef typename automaton_traits<T>::series_set_elt_value_t
							series_set_elt_value_t;
    typedef typename automaton_traits<T>::word_value_t	word_value_t;
    typedef typename automaton_traits<T>::semiring_elt_value_t
							semiring_elt_value_t;
    typedef typename automaton_traits<T>::letter_t	letter_t;
    typedef typename automaton_traits<T>::tag_t		tag_t;
    typedef typename automaton_traits<T>::states_t	states_t;
    typedef typename automaton_traits<T>::state_data_t	state_data_t;
    typedef typename automaton_traits<T>::state_iterator
							state_iterator;
    typedef typename automaton_traits<T>::edges_t	edges_t;
    typedef typename automaton_traits<T>::edge_data_t	edge_data_t;
    typedef typename automaton_traits<T>::edge_iterator	edge_iterator;
    typedef typename automaton_traits<T>::initial_t	initial_t;
    typedef typename automaton_traits<T>::initial_iterator
							initial_iterator;
    typedef typename automaton_traits<T>::initial_support_t
							initial_support_t;
    typedef typename automaton_traits<T>::final_t	final_t;
    typedef typename automaton_traits<T>::final_iterator
							final_iterator;
    typedef typename automaton_traits<T>::final_support_t
							final_support_t;
    typedef typename automaton_traits<T>::geometry_t	geometry_t;
  };

#define AutoType(Type) \
  typename Element<S, TransposeView<T> >::Type

  /// Operations on automata implemented with TransposeView.
  /** @{ */
  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::initial_support_t
  op_initial(const AutomataBase<S>&, const TransposeView<T>&);

  template <class S, class T>
  typename automaton_traits<TransposeView<T> >::final_support_t
  op_final(const AutomataBase<S>&, const TransposeView<T>&);

  template <class S, class T>
  void
  op_set_initial(const AutomataBase<S>&, TransposeView<T>&,
		 hstate_t state,
		 const AutoType(series_set_elt_t)& s);

  template <class S, class T>
  AutoType(series_set_elt_t)
  op_get_initial(const AutomataBase<S>&,
		 const TransposeView<T>&,
		 hstate_t);

  template <class S, class T>
  void
  op_set_final(const AutomataBase<S>&, TransposeView<T>&,
	       hstate_t state,
	       const typename Element<S, T>::series_set_elt_t& s);

  template <class S, class T>
  typename Element<S, T>::series_set_elt_t
  op_get_final(const AutomataBase<S>&,
	       const TransposeView<T>&,
	       hstate_t state);

  template <class S, class T>
  void
  op_clear_initial(const AutomataBase<S>&, TransposeView<T>&);

  template <class S, class T>
  void
  op_clear_final(const AutomataBase<S>&, TransposeView<T>&);

  template <class S, class T>
  hstate_t
  op_origin_of(const AutomataBase<S>&, const TransposeView<T>&,
	       hedge_t);

  template <class S, class T>
  hstate_t
  op_aim_of(const AutomataBase<S>&, const TransposeView<T>&,
	    hedge_t);

  /** @} */

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction		= output

  /// store the output edges of the state 'from' using 'res'.
  template <class S, class T,
	    typename OutputIterator>
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res,
		hstate_t from,
		delta_kind::edges k);

  /**
   * @brief Delta with a query and iterator output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template <class S, class T,
	    typename OutputIterator, typename L>
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res,
		hstate_t from,
		const L& query,
		delta_kind::edges k);

  /**
   * @brief Delta on a letter with iterator output.
   *
   * Store  the output  edges  of  the state  'from'  where the  label
   * matches the letter.
   */
  template <class S, class T,
	    typename OutputIterator, typename L>
  void op_letter_delta(const AutomataBase<S>&, const TransposeView<T>&,
		       OutputIterator res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::edges k);

  /// Store the output spontaneous transitions.
  template <class S, class T,
	    typename OutputIterator>
  void op_spontaneous_delta(const AutomataBase<S>&, const TransposeView<T>&,
			    OutputIterator res,
			    hstate_t from,
			    delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction		= output

  /// Store the output edges of the state 'from' in the container 'res'.
  template <class S, class T,
	    typename Container>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, hstate_t from, delta_kind::edges k);

  /**
   * @brief Delta with a query and container output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template <class S, class T,
	    typename Container, typename L>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res,
		 hstate_t from,
		 const L& query,
		 delta_kind::edges k);

  /**
   * @brief Delta on a letter with container output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template <class S, class T,
	    typename Container, typename L>
  void op_letter_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			Container& res,
			hstate_t from,
			const L& letter,
			delta_kind::edges k);

  /// store the output op_spontaneous transitions.
  template <class S, class T, class Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			     Container& res,
			     hstate_t from,
			     delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction		= output

  /**
   * @brief Delta with no condition and iterator output.
   *
   * Store the output states of the state 'from' using 'res'.
   */
  template<class S, class T, typename OutputIterator>
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res,
		hstate_t from,
		delta_kind::states k);

  /**
   * @brief Delta using a query, with iterator output.
   *
   * Store the output states of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_delta(const AutomataBase<S>&, const TransposeView<T>&,
		OutputIterator res,
		hstate_t from,
		const L& query,
		delta_kind::states k);

  /**
   * @brief Delta on a letter with iterator output.
   *
   * Store  the output  states of  the  state 'from'  where the  label
   * matches the letter.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_letter_delta(const AutomataBase<S>&, const TransposeView<T>&,
		       OutputIterator res,
		       hstate_t from,
		       const L& letter,
		       delta_kind::states k);

  /// store the output op_spontaneous transitions.
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_delta(const AutomataBase<S>&, const TransposeView<T>&,
			    OutputIterator res,
			    hstate_t from,
			    delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction		= output

  /**
   * @brief Delta without condition, container output.
   *
   * Store  the output  states of  the state  'from' in  the container
   * 'res'.
   */
  template<class S, class T, typename Container>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res, hstate_t from, delta_kind::states k);

  /**
   * @brief Delta with a query, using container output.
   *
   * Store the output states of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L>
  void op_deltac(const AutomataBase<S>&, const TransposeView<T>&,
		 Container& res,
		 hstate_t from,
		 const L& query,
		 delta_kind::states k);

  /**
   * @brief Delta on a letter, with container output.
   *
   * Store the output states of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L>
  void op_letter_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			Container& res,
			hstate_t from,
			const L& letter,
			delta_kind::states k);

  /// store the output op_spontaneous transitions.
  template<class S, class T, typename Container>
  void op_spontaneous_deltac(const AutomataBase<S>&, const TransposeView<T>&,
			     Container& res,
			     hstate_t from,
			     delta_kind::states k);

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction		= input

  /**
   * @brief Reverse delta without condition, and iterator output.
   *
   * Store the output edges of the state 'from' using 'res'.
   */
  template<class S, class T, typename OutputIterator>
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res,
		 hstate_t from,
		 delta_kind::edges k);

  /**
   * @brief Reverse delta with query, with iterator output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res,
		 hstate_t from,
		 const L& query,
		 delta_kind::edges k);

  /**
   * @brief Reverse delta on a letter, with iterator output.
   *
   * Store  the output  edges  of  the state  'from'  where the  label
   * matches the letter.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_letter_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			OutputIterator res,
			hstate_t from,
			const L& letter,
			delta_kind::edges k);

  /// store the output op_spontaneous transitions.
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			     OutputIterator res,
			     hstate_t from,
			     delta_kind::edges k);

  // output_return_type = Container
  // output_type        = hedge_t
  // direction		= input

  /**
   * @brief Reverse delta on a container, with no condition.
   *
   * Store the output edges of the state 'from' in the container 'res'.
   */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, hstate_t from, delta_kind::edges k);

  /**
   * @brief Reverse delta using a query, with container output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res,
		  hstate_t from,
		  const L& query,
		  delta_kind::edges k);

  /**
   * @brief Reverse delta on a letter, with container output.
   *
   * Store the output edges  of the state 'from' where query(label(e))
   * is true in the container 'res'.
   */
  template<class S, class T, typename Container, typename L>
  void op_letter_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			 Container& res,
			 hstate_t from,
			 const L& letter,
			 delta_kind::edges k);

  /// store the output op_spontaneous transitions.
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			      Container& res,
			      hstate_t from,
			      delta_kind::edges k);

  // output_return_type = OutputIterator
  // output_type        = hstate_t
  // direction		= input

  /// store the output states of the state 'from' using 'res'.
  template<class S, class T, typename OutputIterator>
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res,
		 hstate_t from,
		 delta_kind::states k);

  /**
   * @brief Reverse delta using a query, with iterator output.
   *
   * Store the output states of the state 'from' where query(label(e))
   * is true using 'res'.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
		 OutputIterator res,
		 hstate_t from,
		 const L& query,
		 delta_kind::states k);

  /**
   * @brief Reverse delta on a letter, with iterator output.
   *
   * Store  the output  states of  the  state 'from'  where the  label
   * matches the letter.
   */
  template<class S, class T, typename OutputIterator, typename L>
  void op_letter_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			OutputIterator res,
			hstate_t from,
			const L& letter,
			delta_kind::states k);

  //// store the output op_spontaneous transitions.
  template<class S, class T, typename OutputIterator>
  void op_spontaneous_rdelta(const AutomataBase<S>&, const TransposeView<T>&,
			     OutputIterator res,
			     hstate_t from,
			     delta_kind::states k);

  // output_return_type = Container
  // output_type        = hstate_t
  // direction		= input

  /**
   * @brief Reverse delta on a container, with no conditions.
   *
   * Store  the output  states of  the state  'from' in  the container
   * 'res'
   */
  template<class S, class T, typename Container>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res, hstate_t from, delta_kind::states k);

  /**
   * @brief Reverse delta in a container, with a query.
   *
   * Store the output states of the state 'from' where query(label(e))
   * is true in the container 'res'
   */
  template<class S, class T, typename Container, typename L>
  void op_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
		  Container& res,
		  hstate_t from,
		  const L& query,
		  delta_kind::states k);

  /**
   * @brief Reverse delta in a container, on a letter.
   *
   * Store  in the  container 'res'  the  output states  of the  state
   * 'from' where query(label(e)) is true.
   */
  template<class S, class T, typename Container, typename L>
  void op_letter_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			 Container& res,
			 hstate_t from,
			 const L& letter,
			 delta_kind::states k);

  /// Store the output op_spontaneous transitions.
  template<class S, class T, typename Container>
  void op_spontaneous_rdeltac(const AutomataBase<S>&, const TransposeView<T>&,
			      Container& res,
			      hstate_t from,
			      delta_kind::states k);

} // vcsn

# undef AutoType


#ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/automata/implementation/transpose_view.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_TRANSPOSE_VIEW_HH
