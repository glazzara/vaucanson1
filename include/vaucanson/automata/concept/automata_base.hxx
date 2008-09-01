// automata_base.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX

# include <vaucanson/automata/concept/copy.hh>
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

  /** Copy constructor */
  template <typename Self, typename T>
  MetaElement<AutomataBase<Self>, T>::MetaElement(const MetaElement& a):
    MetaElement<Structure<Self>, T>::MetaElement(a)
  {}

  /** The optional information aggregated to the automaton. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::tag_t&
  MetaElement<AutomataBase<Self>, T>::tag()
  {
    return op_tag(this->structure(), this->value());
  }

  /** The optional information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::tag_t&
  MetaElement<AutomataBase<Self>, T>:: tag() const
  {
    return op_tag(this->structure(), this->value());
  }

  /** The optional geometry information aggregated to the automaton. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::geometry_t&
  MetaElement<AutomataBase<Self>, T>::geometry()
  {
    return op_geometry(this->structure(), this->value());
  }

  /** The optional geometry information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::geometry_t&
  MetaElement<AutomataBase<Self>, T>::geometry() const
  {
    return op_geometry(this->structure(), this->value());
  }

  /** Return true if the automaton is consistent. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::exists() const
  {
    return op_exists(this->structure(), this->value());
  }

  /** Accessor to the set of states. (const version) */
  template <typename Self, typename T>
  typename automaton_traits<T>::states_t
  MetaElement<AutomataBase<Self>, T>::states() const
  {
    return op_states(this->structure(), this->value());
  }

  /** Accessor to the set of states. (const version) */
  template <typename Self, typename T>
  typename automaton_traits<T>::transitions_t
  MetaElement<AutomataBase<Self>, T>::transitions() const
  {
    return op_transitions(this->structure(), this->value());
  }

  /** The optional information aggregated to the automaton. */
  template <typename Self, typename T>
  const typename MetaElement<AutomataBase<Self>, T>::series_set_t&
  MetaElement<AutomataBase<Self>, T>::series() const
  {
    return this->structure().series();
  }

  /** Accessor to the initial application. */
  template <typename Self, typename T>
  typename automaton_traits<T>::initial_support_t
  MetaElement<AutomataBase<Self>, T>::initial() const
  {
    return op_initial(this->structure(), this->value());
  }

  /** Accessor to the final application. */
  template <typename Self, typename T>
  typename automaton_traits<T>::final_support_t

  MetaElement<AutomataBase<Self>, T>::final() const
  {
    return op_final(this->structure(), this->value());
  }

  /** Return true if the state is initial (ie it is in the initial
   support) . */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_initial(const typename automaton_traits<T>::hstate_t& state) const
  {
    return op_is_initial(this->structure(), this->value(), state);
  }

  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_initial(unsigned state) const
  {
    return op_is_initial(this->structure(), this->value(), state);
  }

  /** Return true if the state is final (ie it is in the final support). */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_final(const typename automaton_traits<T>::hstate_t& state) const
  {
    return op_is_final(this->structure(), this->value(), state);
  }

  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_final(unsigned state) const
  {
    return op_is_final(this->structure(), this->value(), state);
  }

  /** Set the state to be initial. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_initial(const typename automaton_traits<T>::hstate_t& state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   this->structure().series().
		   identity(SELECT(series_set_elt_value_t)));
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_initial(unsigned state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   this->structure().series().
		   identity(SELECT(series_set_elt_value_t)));
  }

  /** Set an initial multiplicity to the state. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_initial(const typename automaton_traits<T>::hstate_t& state, const series_set_elt_t& s)
  {
    op_set_initial(this->structure(), this->value(), state, s);
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_initial(unsigned state, const series_set_elt_t& s)
  {
    op_set_initial(this->structure(), this->value(), state, s);
  }

  /** Set the state to be final. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_final(const typename automaton_traits<T>::hstate_t& state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 this->structure().series().
		 identity(SELECT(series_set_elt_value_t)));
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::set_final(unsigned state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 this->structure().series().
		 identity(SELECT(series_set_elt_value_t)));
  }

  /** Set a final multiplicity to the state. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_final(const typename automaton_traits<T>::hstate_t& state, const series_set_elt_t& s)
  {
    op_set_final(this->structure(), this->value(), state, s);
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::
  set_final(unsigned state, const series_set_elt_t& s)
  {
    op_set_final(this->structure(), this->value(), state, s);
  }

  /** Set the state not to be initial. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_initial(const typename automaton_traits<T>::hstate_t& state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   algebra::zero_as<series_set_elt_value_t>::
		   of(this->structure().series()));
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_initial(unsigned state)
  {
    op_set_initial(this->structure(),
		   this->value(),
		   state,
		   algebra::zero_as<series_set_elt_value_t>::
		   of(this->structure().series()));
  }

  /** Set the set not to be final. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_final(const typename automaton_traits<T>::hstate_t& state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 algebra::zero_as<series_set_elt_value_t>::
		 of(this->structure().series()));
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::unset_final(unsigned state)
  {
    op_set_final(this->structure(),
		 this->value(),
		 state,
		 algebra::zero_as<series_set_elt_value_t>::
		 of(this->structure().series()));
  }

  /** Make the support of the initial application to be empty. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::clear_initial()
  {
    return op_clear_initial(this->structure(), this->value());
  }

  /** Make the support of the final application to be empty. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::clear_final()
  {
    return op_clear_final(this->structure(), this->value());
  }

  /** Return the initial multiplicity of the state. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_initial(const typename automaton_traits<T>::hstate_t& state) const
  {
    return op_get_initial(this->structure(), this->value(), state);
  }

  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_initial(unsigned state) const
  {
    return op_get_initial(this->structure(), this->value(), state);
  }

  /** Return the final multiplicity of the state. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_final(const typename automaton_traits<T>::hstate_t& state) const
  {
    return op_get_final(this->structure(), this->value(), state);
  }

  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::get_final(unsigned state) const
  {
    return op_get_final(this->structure(), this->value(), state);
  }

  /** Add a new state to the automaton. */
  template <typename Self, typename T>
  typename automaton_traits<T>::hstate_t
  MetaElement<AutomataBase<Self>, T>::add_state()
  {
    return op_add_state(this->structure(), this->value());
  }

  /** Return a state descriptor for state number 'state'. */
  template <typename Self, typename T>
  typename automaton_traits<T>::hstate_t
  MetaElement<AutomataBase<Self>, T>::get_state(unsigned state) const
  {
    return op_get_state(this->structure(), this->value(), state);
  }

  /** Return a randomly chosen state. (valid only if the automaton
   is not empty) */
  template <typename Self, typename T>
  typename automaton_traits<T>::hstate_t
  MetaElement<AutomataBase<Self>, T>::choose_state() const
  {
    return op_choose_state(this->structure(), this->value());
  }

  /** Add a new transition between @c src and @c to labelled by @c label */
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_transition(const typename automaton_traits<T>::hstate_t& src,
						     const typename automaton_traits<T>::hstate_t& dst,
						     const label_t& label)
  {
    return op_add_transition(this->structure(), this->value(),
			     src, dst, label);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_transition(unsigned src,
						     unsigned dst,
						     const label_t& label)
  {
    return op_add_transition(this->structure(), this->value(),
			     src, dst, label);
  }

  /** Add a new weighted transition. */
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::
  add_weighted_transition(const typename automaton_traits<T>::hstate_t& src,
			  const typename automaton_traits<T>::hstate_t& dst,
			  const semiring_elt_t& w,
			  const monoid_elt_value_t& m)
  {
    return op_add_weighted_transition(this->structure(), this->value(),
				      src, dst, w, m);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::
  add_weighted_transition(unsigned src,
			  unsigned dst,
			  const semiring_elt_t& w,
			  const monoid_elt_value_t& m)
  {
    return op_add_weighted_transition(this->structure(), this->value(),
				      src, dst, w, m);
  }

  /** Add a transition using a series. */
  /** If the underlying implementation is not sufficiently general
   *  to support this operation, you will have several transitions created.*/
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_series_transition(const typename automaton_traits<T>::hstate_t& src,
							    const typename automaton_traits<T>::hstate_t& dst,
							    const series_set_elt_t& e)
  {
    return op_add_series_transition(this->structure(), this->value(),
				    src, dst, e);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_series_transition(unsigned src,
							    unsigned dst,
							    const series_set_elt_t& e)
  {
    return op_add_series_transition(this->structure(), this->value(),
				    src, dst, e);
  }

  /** Add a spontaneous transition between @c src and @c dst. */
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_spontaneous(const typename automaton_traits<T>::hstate_t& src,
						      const typename automaton_traits<T>::hstate_t& dst)
  {
    semiring_elt_t w(this->structure().series().semiring());
    w = algebra::identity_as<semiring_elt_value_t>
      ::of(this->structure().series().semiring());
    return op_add_spontaneous(this->structure(), this->value(), src, dst, w);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_spontaneous(unsigned src,
						      unsigned dst)
  {
    semiring_elt_t w(this->structure().series().semiring());
    w = algebra::identity_as<semiring_elt_value_t>
      ::of(this->structure().series().semiring());
    return op_add_spontaneous(this->structure(), this->value(), src, dst, w);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_spontaneous(const typename automaton_traits<T>::hstate_t& src,
						      const typename automaton_traits<T>::hstate_t& dst,
						      const semiring_elt_t& w)
  {
    return op_add_spontaneous(this->structure(), this->value(), src, dst, w);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_spontaneous(unsigned src,
						      unsigned dst,
						      const semiring_elt_t& w)
  {
    return op_add_spontaneous(this->structure(), this->value(), src, dst, w);
  }

  /** Add a transition between @c src and @c dst labelled by a letter. */
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_letter_transition(const typename automaton_traits<T>::hstate_t& src,
							    const typename automaton_traits<T>::hstate_t& dst,
							    const letter_t& l)
  {
    return op_add_letter_transition(this->structure(), this->value(),
				    src, dst, l);
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_letter_transition(unsigned src,
							    unsigned dst,
							    const letter_t& l)
  {
    return op_add_letter_transition(this->structure(), this->value(),
				    src, dst, l);
  }

  /** Add a transition between @c src and @c dst labelled by a letter from
   * its literal representation. */
  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_letter_transition(const typename automaton_traits<T>::hstate_t& src,
							    const typename automaton_traits<T>::hstate_t& dst,
							    const std::string& l)
  {
    return op_add_letter_transition(this->structure(), this->value(),
				    src, dst, algebra::letter_traits<letter_t>::
				    literal_to_letter(l));
  }

  template <typename Self, typename T>
  typename automaton_traits<T>::htransition_t
  MetaElement<AutomataBase<Self>, T>::add_letter_transition(unsigned src,
							    unsigned dst,
							    const std::string& l)
  {
    return op_add_letter_transition(this->structure(), this->value(),
				    src, dst, algebra::letter_traits<letter_t>::
				    literal_to_letter(l));
  }

  /** Update the label of a transition. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::update(const typename automaton_traits<T>::htransition_t& e, const label_t& l)
  {
    op_update(this->structure(), this->value(), e, l);
  }

  /** Delete the state @c s. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::del_state(const typename automaton_traits<T>::hstate_t& s)
  {
    return op_del_state(this->structure(), this->value(), s);
  }

  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::del_state(unsigned state)
  {
    return op_del_state(this->structure(), this->value(), state);
  }

  /** Delete the transition @c e. */
  template <typename Self, typename T>
  void
  MetaElement<AutomataBase<Self>, T>::del_transition(const typename automaton_traits<T>::htransition_t& e)
  {
    return op_del_transition(this->structure(), this->value(), e);
  }

  /** Check if the state @c s is in the automaton. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::has_state(const typename automaton_traits<T>::hstate_t& s) const
  {
    return op_has_state(this->structure(), this->value(), s);
  }

  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::has_state(unsigned state) const
  {
    return op_has_state(this->structure(), this->value(), state);
  }

  /** Check if the transition @c e is in the automaton. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::has_transition(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_has_transition(this->structure(), this->value(), e);
  }

  /** Return the origin of the transition @c e. */
  template <typename Self, typename T>
  typename automaton_traits<T>::hstate_t
  MetaElement<AutomataBase<Self>, T>::src_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_src_of(this->structure(), this->value(), e);
  }

  /** Return the aim of the transition @c e. */
  template <typename Self, typename T>
  typename automaton_traits<T>::hstate_t
  MetaElement<AutomataBase<Self>, T>::dst_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_dst_of(this->structure(), this->value(), e);
  }

  /** Return the label of the transition @c e. */
  template <typename Self, typename T>
  typename automaton_traits<T>::label_t
  MetaElement<AutomataBase<Self>, T>::label_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_label_of(this->structure(), this->value(), e);
  }

  /** Return the label seen as a series. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_t
  MetaElement<AutomataBase<Self>, T>::series_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_series_of(this->structure(), this->value(), e);
  }

  /** Return the label seen as a series implementation. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::series_set_elt_value_t
  MetaElement<AutomataBase<Self>, T>::series_value_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_series_value_of(this->structure(), this->value(), e);
  }

  /** Return true if the transition is spontaneous. */
  template <typename Self, typename T>
  bool
  MetaElement<AutomataBase<Self>, T>::is_spontaneous(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_is_spontaneous(this->structure(), this->value(), e);
  }

  /** Return the label seen as a word. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::monoid_elt_t
  MetaElement<AutomataBase<Self>, T>::word_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_word_of(this->structure(), this->value(), e);
  }

  /** Return the label seen as a weight. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::semiring_elt_t
  MetaElement<AutomataBase<Self>, T>::weight_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_weight_of(this->structure(), this->value(), e);
  }

  /** Returns the label seen as word implementation. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::monoid_elt_value_t
  MetaElement<AutomataBase<Self>, T>::word_value_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_word_value_of(this->structure(), this->value(), e);
  }

  /** Return the label seen as a letter. */
  /** Becareful, when you have more general label this method is
   *  probably invalidated. */
  template <typename Self, typename T>
  typename MetaElement<AutomataBase<Self>, T>::letter_t
  MetaElement<AutomataBase<Self>, T>::letter_of(const typename automaton_traits<T>::htransition_t& e) const
  {
    return op_letter_of(this->structure(), this->value(), e);
  }

  /*---------.
  | Deltas.  |
  `---------*/

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    const typename automaton_traits<T>::hstate_t& src,
					    delta_kind::kind<Kind> k) const
  {
    op_delta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    unsigned src,
					    delta_kind::kind<Kind> k) const
  {
    op_delta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    const typename automaton_traits<T>::hstate_t& src,
					    const L& query,
					    delta_kind::kind<Kind> k) const
  {
    op_delta(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::delta(OutputIterator res,
					    unsigned src,
					    const L& query,
					    delta_kind::kind<Kind> k) const
  {
    op_delta(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_delta(OutputIterator res,
						   const typename automaton_traits<T>::hstate_t& src,
						   const L& letter,
						   delta_kind::kind<Kind> k) const
  {
    op_letter_delta(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_delta(OutputIterator res,
						   unsigned src,
						   const L& letter,
						   delta_kind::kind<Kind> k) const
  {
    op_letter_delta(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_delta(OutputIterator res,
		      const typename automaton_traits<T>::hstate_t& src,
		      delta_kind::kind<Kind> k) const
  {
    return op_spontaneous_delta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_delta(OutputIterator res,
		      unsigned src,
		      delta_kind::kind<Kind> k) const
  {
    return op_spontaneous_delta(this->structure(), this->value(), res, src, k);
  }

  /*----------.
  | Deltacs.  |
  `----------*/

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res, const typename automaton_traits<T>::hstate_t& src,
					     delta_kind::kind<Kind> k) const
  {
    op_deltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res, unsigned src,
					     delta_kind::kind<Kind> k) const
  {
    op_deltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res,
					     const typename automaton_traits<T>::hstate_t& src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_deltac(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltac(Container& res,
					     unsigned src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_deltac(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltac(Container& res,
						    const typename automaton_traits<T>::hstate_t& src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_deltac(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltac(Container& res,
						    unsigned src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_deltac(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltac(Container& res,
		       const typename automaton_traits<T>::hstate_t& src,
		       delta_kind::kind<Kind> k) const
  {
    op_spontaneous_deltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltac(Container& res,
		       unsigned src,
		       delta_kind::kind<Kind> k) const
  {
    op_spontaneous_deltac(this->structure(), this->value(), res, src, k);
  }

  /*----------.
  | Deltafs.  |
  `----------*/

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltaf(Functor& fun, const typename automaton_traits<T>::hstate_t& src,
					     delta_kind::kind<Kind> k) const
  {
    op_deltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltaf(Functor& fun, unsigned src,
					     delta_kind::kind<Kind> k) const
  {
    op_deltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltaf(Functor& fun,
					     const typename automaton_traits<T>::hstate_t& src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_deltaf(this->structure(), this->value(), fun, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::deltaf(Functor& fun,
					     unsigned src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_deltaf(this->structure(), this->value(), fun, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltaf(Functor& fun,
						    const typename automaton_traits<T>::hstate_t& src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_deltaf(this->structure(), this->value(), fun, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_deltaf(Functor& fun,
						    unsigned src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_deltaf(this->structure(), this->value(), fun, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltaf(Functor& fun,
		       const typename automaton_traits<T>::hstate_t& src,
		       delta_kind::kind<Kind> k) const
  {
    op_spontaneous_deltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_deltaf(Functor& fun,
		       unsigned src,
		       delta_kind::kind<Kind> k) const
  {
    op_spontaneous_deltaf(this->structure(), this->value(), fun, src, k);
  }

  /*-----------------.
  | Reverse deltas.  |
  `-----------------*/

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					     const typename automaton_traits<T>::hstate_t& src,
					     delta_kind::kind<Kind> k) const
  {
    op_rdelta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					     unsigned src,
					     delta_kind::kind<Kind> k) const
  {
    op_rdelta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					     const typename automaton_traits<T>::hstate_t& src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_rdelta(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdelta(OutputIterator res,
					     unsigned src,
					     const L& query,
					     delta_kind::kind<Kind> k) const
  {
    op_rdelta(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdelta(OutputIterator res,
						    const typename automaton_traits<T>::hstate_t& src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_rdelta(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdelta(OutputIterator res,
						    unsigned src,
						    const L& letter,
						    delta_kind::kind<Kind> k) const
  {
    op_letter_rdelta(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdelta(OutputIterator res,
		       const typename automaton_traits<T>::hstate_t& src,
		       delta_kind::kind<Kind> k) const
  {
    return op_spontaneous_rdelta(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename OutputIterator, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdelta(OutputIterator res,
		       unsigned src,
		       delta_kind::kind<Kind> k) const
  {
    return op_spontaneous_rdelta(this->structure(), this->value(), res, src, k);
  }

  /*------------------.
  | Reverse deltacs.  |
  `------------------*/

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res, const typename automaton_traits<T>::hstate_t& src,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res, unsigned src,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res,
					      const typename automaton_traits<T>::hstate_t& src,
					      const L& query,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltac(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltac(Container& res,
					      unsigned src,
					      const L& query,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltac(this->structure(), this->value(), res, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltac(Container& res,
						     const typename automaton_traits<T>::hstate_t& src,
						     const L& letter,
						     delta_kind::kind<Kind> k) const
  {
    op_letter_rdeltac(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltac(Container& res,
						     unsigned src,
						     const L& letter,
						     delta_kind::kind<Kind> k) const
  {
    op_letter_rdeltac(this->structure(), this->value(), res, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltac(Container& res,
			const typename automaton_traits<T>::hstate_t& src,
			delta_kind::kind<Kind> k) const
  {
    op_spontaneous_rdeltac(this->structure(), this->value(), res, src, k);
  }

  template <typename Self, typename T>
  template <typename Container, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltac(Container& res,
			unsigned src,
			delta_kind::kind<Kind> k) const
  {
    op_spontaneous_rdeltac(this->structure(), this->value(), res, src, k);
  }

  /*------------------.
  | Reverse deltafs.  |
  `------------------*/

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltaf(Functor& fun, const typename automaton_traits<T>::hstate_t& src,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltaf(Functor& fun, unsigned src,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltaf(Functor& fun,
					      const typename automaton_traits<T>::hstate_t& src,
					      const L& query,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltaf(this->structure(), this->value(), fun, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::rdeltaf(Functor& fun,
					      unsigned src,
					      const L& query,
					      delta_kind::kind<Kind> k) const
  {
    op_rdeltaf(this->structure(), this->value(), fun, src, query, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltaf(Functor& fun,
						     const typename automaton_traits<T>::hstate_t& src,
						     const L& letter,
						     delta_kind::kind<Kind> k) const
  {
    op_letter_rdeltaf(this->structure(), this->value(), fun, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename L, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>::letter_rdeltaf(Functor& fun,
						     unsigned src,
						     const L& letter,
						     delta_kind::kind<Kind> k) const
  {
    op_letter_rdeltaf(this->structure(), this->value(), fun, src, letter, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltaf(Functor& fun,
			const typename automaton_traits<T>::hstate_t& src,
			delta_kind::kind<Kind> k) const
  {
    op_spontaneous_rdeltaf(this->structure(), this->value(), fun, src, k);
  }

  template <typename Self, typename T>
  template <typename Functor, typename Kind>
  void
  MetaElement<AutomataBase<Self>, T>
  ::spontaneous_rdeltaf(Functor& fun,
			unsigned src,
			delta_kind::kind<Kind> k) const
  {
    op_spontaneous_rdeltaf(this->structure(), this->value(), fun, src, k);
  }


  template<typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& v)
  {
    Element<S, T> r(s.self(), v);
    st << "{ "
       << r.states().size() << " states, "
       << r.transitions().size() << " transitions, "
       << "#I = " << r.initial().size() << ", "
       << "#T = " << r.final().size()
       << " }";
    return st;
  }

  /*----------------------------------------------.
  | automaton to generalized automaton convertion |
  `----------------------------------------------*/

  template <typename Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from)
  {
    typename generalized_traits<Auto_>::automaton_t to(from.structure());
    auto_copy(to, from);
    return to;
  }

} // ! vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HXX
