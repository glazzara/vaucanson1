// automata_base.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata_ops.hh>

namespace vcsn {

  template <typename Self>
  AutomataBase<Self>::AutomataBase()
  {}

  template <typename Self>
  AutomataBase<Self>::AutomataBase(const AutomataBase& other) :
    Structure<Self>(other)
  {}

  template <typename Self>
  const typename AutomataBase<Self>::series_set_t&
  AutomataBase<Self>::series() const
  {
    return this->self().series();
  }

  
  /** */
  template <typename Self, typename T>
  MetaElement<AutomataBase<Self>, T>::MetaElement()
  {}

  /** copy constructor */
  template <typename Self, typename T>
  MetaElement<AutomataBase<Self>, T>::MetaElement(const MetaElement& a):
    MetaElement<Structure<Self>, T>::MetaElement(a)
  {}

  /** the optional information aggregated to the automaton. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::tag_t&
  MetaElement<AutomataBase<Self>, T>::tag()
  {
    return op_tag(this->structure(), this->value());
  }

  /** the optional information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::tag_t&
  MetaElement<AutomataBase<Self>, T>:: tag() const
  {
    return op_tag(this->structure(), this->value());
  }

  /** the optional geometry information aggregated to the automaton. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::geometry_t&
  MetaElement<AutomataBase<Self>, T>::geometry()
  {
    return op_geometry(this->structure(), this->value());
  }

  /** the optional geometry information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::geometry_t&
  MetaElement<AutomataBase<Self>, T>::geometry() const
  {
    return op_geometry(this->structure(), this->value());
  }
  
  /** return true if the automaton is consistent. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::exists() const
  {
    return op_exists(this->structure(), this->value());
  }

  /** accessor to the set of states. (const version) */
  template <typename Self, typename T>
  typename automaton_traits<T>::states_t
  MetaElement<AutomataBase<Self>, T>::states() const
  {
    return op_states(this->structure(), this->value());
  }

  /** accessor to the set of states. (const version) */
  template <typename Self, typename T>
  typename automaton_traits<T>::edges_t
  MetaElement<AutomataBase<Self>, T>::edges() const
  {
    return op_edges(this->structure(), this->value());
  }

  /** the optional information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::series_set_t&
  MetaElement<AutomataBase<Self>, T>::series() const
  {
    return this->structure().series();
  }

  /** accessor to the initial application. */
  template <typename Self, typename T>
  typename automaton_traits<T>::initial_support_t
  MetaElement<AutomataBase<Self>, T>::initial() const
  {
    return op_initial(this->structure(), this->value());
  }

  /** accessor to the final application. */
  template <typename Self, typename T>
  typename automaton_traits<T>::final_support_t

  MetaElement<AutomataBase<Self>, T>::final() const
  {
    return op_final(this->structure(), this->value());
  }

  /** return true if the state is initial (ie it is in the initial
    support) . */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_initial(hstate_t state) const
  {
    return (op_get_initial(this->structure(), this->value(), state) !=
	    this->structure().series().zero(SELECT(series_set_elt_value_t)));
  }

  /** return true if the state is final (ie it is in the final support). */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_final(hstate_t state) const
  {
    return
      op_get_final(this->structure(), this->value(), state) !=
      algebra::zero_as<series_set_elt_value_t>::
      of(this->structure().series());
  }

  /** set the state to be initial. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_initial(hstate_t state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   this->structure().series().
		   identity(SELECT(series_set_elt_value_t)));
  }

  /** set an initial multiplicity to the state. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_initial(hstate_t state, const series_set_elt_t& s)
  {
    op_set_initial(this->structure(), this->value(), state, s);
  }

  /** set the state to be final. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_final(hstate_t state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 this->structure().series().
		 identity(SELECT(series_set_elt_value_t)));
  }

  /** set a final multiplicity to the state. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_final(hstate_t state, const series_set_elt_t& s)
  {
    op_set_final(this->structure(), this->value(), state, s);
  }

  /** set the state not to be initial. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_initial(hstate_t state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   algebra::zero_as<series_set_elt_value_t>::
		   of(this->structure().series()));
  }

  /** set the set not to be final. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_final(hstate_t state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 algebra::zero_as<series_set_elt_value_t>::
		 of(this->structure().series()));
  }

  /** make the support of the initial application to be empty. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::clear_initial()
  {
    return op_clear_initial(this->structure(), this->value());
  }

  /** make the support of the final application to be empty. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::clear_final()
  {
    return op_clear_final(this->structure(), this->value());
  }

  /** return the initial multiplicity of the state. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_initial(hstate_t state) const
  {
    return op_get_initial(this->structure(), this->value(), state);
  }

  /** return the final multiplicity of the state. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_final(hstate_t what) const
  {
    return op_get_final(this->structure(), this->value(), what);
  }

  /** add a new state to the automaton. */
  template <typename Self, typename T>
  hstate_t
  MetaElement<AutomataBase<Self>, T>::add_state()
  {
    return op_add_state(this->structure(), this->value());
  }

  /** return a randomly chosen state. (valid only if the automaton
    is not empty) */
  template <typename Self, typename T>
  hstate_t
  MetaElement<AutomataBase<Self>, T>::choose_state() const
  {
    return op_choose_state(this->structure(), this->value());
  }

  /** add a new edge between 'from' and 'to' labelled by 'label' */
  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>::add_edge(hstate_t from,
					       hstate_t to,
					       const label_t& label)
  {
    return op_add_edge(this->structure(), this->value(),
		       from, to, label);
  }

  /** add a new weighted edge. */
  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>::
  add_weighted_edge(hstate_t from,
		    hstate_t to,
		    const semiring_elt_t& w,
		    const monoid_elt_value_t& m)
  {
    return op_add_weighted_edge(this->structure(), this->value(),
				from, to, w, m);
  }

  /** add an edge using a series. */
  /** If the underlying implementation is not sufficiently general
   *  to support this operation, you will have several edges created.*/
  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>::add_series_edge(hstate_t from,
						     hstate_t to,
						     const series_set_elt_t& e)
  {
    return op_add_series_edge(this->structure(), this->value(), from, to, e);
  }

  /** add a spontaneous transition between 'from' and 'to'. */
  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>::add_spontaneous(hstate_t from,
						      hstate_t to)
  {
    semiring_elt_t w(this->structure().series().semiring());
    w = algebra::identity_as<semiring_elt_value_t>
      ::of(this->structure().series().semiring());
    return op_add_spontaneous(this->structure(), this->value(), from, to, w);
  }

  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>
  ::add_spontaneous(hstate_t from,
		    hstate_t to,
		    const semiring_elt_t& w)
  {
    return op_add_spontaneous(this->structure(), this->value(), from, to, w);
  }

  /** add an transition between 'from' and 'to' labelled by a letter. */
  template <typename Self, typename T>
  hedge_t
  MetaElement<AutomataBase<Self>, T>::add_letter_edge(hstate_t from,
						      hstate_t to,
						      const letter_t& l)
  {
    return op_add_letter_edge(this->structure(), this->value(), from, to, l);
  }

  /** update the label of an edge. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::update(hedge_t e, const label_t& l)
  {
    op_update(this->structure(), this->value(), e, l);
  }

  /** delete the state 's'. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::del_state(hstate_t s)
  {
    return op_del_state(this->structure(), this->value(), s);
  }

  /** delete the edge 'e'. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::del_edge(hedge_t e)
  {
    return op_del_edge(this->structure(), this->value(), e);
  }

  /** check if the state 's' is in the automaton. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::has_state(hstate_t s) const
  {
    return op_has_state(this->structure(), this->value(), s);
  }

  /** check if the edge 'e' is in the automaton. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::has_edge(hedge_t e) const
  {
    return op_has_edge(this->structure(), this->value(), e);
  }

  /** return the origin of the edge 'e'. */
  template <typename Self, typename T>
  hstate_t
  MetaElement<AutomataBase<Self>, T>::origin_of(hedge_t e) const
  {
    return op_origin_of(this->structure(), this->value(), e);
  }

  /** return the aim of the edge 'e'. */
  template <typename Self, typename T>
  hstate_t
  MetaElement<AutomataBase<Self>, T>::aim_of(hedge_t e) const
  {
    return op_aim_of(this->structure(), this->value(), e);
  }

  /** return the label of the edge 'e'. */
  template <typename Self, typename T>
  typename automaton_traits<T>::label_t
  MetaElement<AutomataBase<Self>, T>::label_of(hedge_t e) const
  {
    return op_label_of(this->structure(), this->value(), e);
  }

  /** return the label seen as a series. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::series_of(hedge_t e) const
  {
    return op_series_of(this->structure(), this->value(), e);
  }

  /** return the label seen as a series implementation. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_value_t
  MetaElement<AutomataBase<Self>, T>::series_value_of(hedge_t e) const
  {
    return op_series_value_of(this->structure(), this->value(), e);
  }

  /** return true if the transition is spontaneous. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_spontaneous(hedge_t e) const
  {
    return op_is_spontaneous(this->structure(), this->value(), e);
  }

  /** return the label seen as a word. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::monoid_elt_t
  MetaElement<AutomataBase<Self>, T>::word_of(hedge_t e) const
  {
    return op_word_of(this->structure(), this->value(), e);
  }

  /** return the label seen as a weight. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::semiring_elt_t
  MetaElement<AutomataBase<Self>, T>::weight_of(hedge_t e) const
  {
    return op_weight_of(this->structure(), this->value(), e);
  }

  /** returns the label seen as word implementation. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::monoid_elt_value_t
  MetaElement<AutomataBase<Self>, T>::word_value_of(hedge_t e) const
  {
    return op_word_value_of(this->structure(), this->value(), e);
  }

  /** return the label seen as a letter. */
  /** Becareful, when you have more general label this method is
   *  probably invalidated. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::letter_t
  MetaElement<AutomataBase<Self>, T>::letter_of(hedge_t e) const
  {
    return op_letter_of(this->structure(), this->value(), e);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /** store the output edges of the state 'from' using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    hstate_t from,
					    delta_kind::edges k) const
  {
    op_delta(this->structure(), this->value(), res, from, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    hstate_t from,
					    const L& query,
					    delta_kind::edges k) const
  {
    op_delta(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output edges of the state 'from' where
    the label matches the letter. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_delta(OutputIterator res,
						   hstate_t from,
						   const L& letter,
						   delta_kind::edges k) const
  {
    op_letter_delta(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_delta(OutputIterator res,
		      hstate_t from,
		      delta_kind::edges k) const
  {
    return op_spontaneous_delta(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /** store the output edges of the state 'from' in the container
    'res' */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res, hstate_t from,
					     delta_kind::edges k) const
  {
    op_deltac(this->structure(), this->value(), res, from, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res,
					     hstate_t from,
					     const L& query,
					     delta_kind::edges k) const
  {
    op_deltac(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltac(Container& res,
						    hstate_t from,
						    const L& letter,
						    delta_kind::edges k) const
  {
    op_letter_deltac(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltac(Container& res,
		       hstate_t from,
		       delta_kind::edges k) const
  {
    op_spontaneous_deltac(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /** store the output edges of the state 'from' using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    hstate_t from,
					    delta_kind::states k) const
  {
    op_delta(this->structure(), this->value(), res, from, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    hstate_t from,
					    const L& query,
					    delta_kind::states k) const
  {
    op_delta(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output states of the state 'from' where
    the label matches the letter. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_delta(OutputIterator res,
						   hstate_t from,
						   const L& letter,
						   delta_kind::states k) const
  {
    op_letter_delta(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_delta(OutputIterator res,
		      hstate_t from,
		      delta_kind::states k) const
  {
    return op_spontaneous_delta(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /** store the output states of the state 'from' in the container
    'res' */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res, hstate_t from,
					     delta_kind::states k) const
  {
    op_deltac(this->structure(), this->value(), res, from, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res,
					     hstate_t from,
					     const L& query,
					     delta_kind::states k) const
  {
    op_deltac(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltac(Container& res,
						    hstate_t from,
						    const L& letter,
						    delta_kind::states k) const
  {
    op_letter_deltac(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltac(Container& res,
		       hstate_t from,
		       delta_kind::states k) const
  {
    op_spontaneous_deltac(this->structure(), this->value(), res, from, k);
  }


  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = input

  /** store the output edges of the state 'from' using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					    hstate_t from,
					    delta_kind::edges k) const
  {
    op_rdelta(this->structure(), this->value(), res, from, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					    hstate_t from,
					    const L& query,
					    delta_kind::edges k) const
  {
    op_rdelta(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output edges of the state 'from' where
    the label matches the letter. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdelta(OutputIterator res,
						   hstate_t from,
						   const L& letter,
						   delta_kind::edges k) const
  {
    op_letter_rdelta(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdelta(OutputIterator res,
		      hstate_t from,
		      delta_kind::edges k) const
  {
    return op_spontaneous_rdelta(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	        = input

  /** store the output edges of the state 'from' in the container
    'res' */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res, hstate_t from,
					     delta_kind::edges k) const
  {
    op_rdeltac(this->structure(), this->value(), res, from, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res,
					     hstate_t from,
					     const L& query,
					     delta_kind::edges k) const
  {
    op_rdeltac(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output edges of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltac(Container& res,
						    hstate_t from,
						    const L& letter,
						    delta_kind::edges k) const
  {
    op_letter_rdeltac(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltac(Container& res,
		       hstate_t from,
		       delta_kind::edges k) const
  {
    op_spontaneous_rdeltac(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = OutputIterator
  // output_type        = hedge_t
  // direction	  = output

  /** store the output edges of the state 'from' using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					    hstate_t from,
					    delta_kind::states k) const
  {
    op_rdelta(this->structure(), this->value(), res, from, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true using 'res'. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					    hstate_t from,
					    const L& query,
					    delta_kind::states k) const
  {
    op_rdelta(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output states of the state 'from' where
    the label matches the letter. */
  template <typename Self, typename T>
  template <typename OutputIterator, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdelta(OutputIterator res,
						   hstate_t from,
						   const L& letter,
						   delta_kind::states k) const
  {
    op_letter_rdelta(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename OutputIterator>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdelta(OutputIterator res,
		       hstate_t from,
		       delta_kind::states k) const
  {
    return op_spontaneous_rdelta(this->structure(), this->value(), res, from, k);
  }

  // output_return_type = Container
  // output_type        = hedge_t
  // direction	  = output

  /** store the output states of the state 'from' in the container
    'res' */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res, hstate_t from,
					     delta_kind::states k) const
  {
    op_rdeltac(this->structure(), this->value(), res, from, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res,
					     hstate_t from,
					     const L& query,
					     delta_kind::states k) const
  {
    op_rdeltac(this->structure(), this->value(), res, from, query, k);
  }

  /** store the output states of the state 'from' where
    query(label(e)) = true in the container 'res' */
  template <typename Self, typename T>
  template <typename Container, typename L>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltac(Container& res,
						    hstate_t from,
						    const L& letter,
						    delta_kind::states k) const
  {
    op_letter_rdeltac(this->structure(), this->value(), res, from, letter, k);
  }

  /** store the output spontaneous transitions. */
  template <typename Self, typename T>
  template <typename Container>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltac(Container& res,
		       hstate_t from,
		       delta_kind::states k) const
  {
    op_spontaneous_rdeltac(this->structure(), this->value(), res, from, k);
  }


  template<typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& v)
  {
    Element<S, T> r(s.self(), v);
    st << "{ "
       << r.states().size() << " states, "
       << r.edges().size() << " edges, "
       << "#I = " << r.initial().size() << ", "
       << "#T = " << r.final().size()
       << " }";
    return st;
  }


} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX
