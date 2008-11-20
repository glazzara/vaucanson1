// automata_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson
// Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH

# include <iterator>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/delta_kind.hh>
# include <vaucanson/algebra/concept/series_base.hh>

namespace vcsn {

  /** @addtogroup automata */  /** @{ */
  /** @addtogroup concept  */  /** @{ */

  /*-------------------.
  | AutomataBase<Self> |
  `-------------------*/
  /// The most general concept of automaton.
  /** It symbolises the set of automata with multiplicity over a fixed
   semiring and a fixed free monoid. Note that this class is abstract
   in the hierarchy.
   */
  template <typename Self>
  struct AutomataBase
    : Structure<Self>
  {
    public:
      /// The type of the series set associated with the automaton.
      typedef typename virtual_types<Self>::series_set_t  series_set_t;
      /// The type of the label kind associated with the automaton.
      typedef typename virtual_types<Self>::kind_t kind_t;

    protected:
      /// The default constructor is protected since it is an abstract class.
      AutomataBase();

      /// The copy constructor is protected since it is an abstract class.
      AutomataBase(const AutomataBase& other);

    public:
      /// Accessor to the set of series of the automaton.
      const series_set_t& series() const;
  };

  // FIXME: it must be renamed to automaton_impl_traits
  // traits for automaton implementation.
  template <typename T>
  struct automaton_traits
  {
      typedef undefined_type label_t;
      typedef undefined_type series_set_elt_value_t;
      typedef undefined_type word_value_t;
      typedef undefined_type semiring_elt_value_t;
      typedef undefined_type letter_t;
      typedef undefined_type tag_t;
      typedef undefined_type states_t;
      typedef undefined_type state_iterator;
      typedef undefined_type transitions_t;
      typedef undefined_type transition_iterator;
      typedef undefined_type initial_iterator;
      typedef undefined_type initial_t;
      typedef undefined_type initial_support_t;
      typedef undefined_type final_iterator;
      typedef undefined_type final_t;
      typedef undefined_type final_support_t;
      typedef undefined_type geometry_t;
      typedef undefined_type hstate_t;
      typedef undefined_type htransition_t;
      typedef undefined_type delta_state_iterator;
      typedef undefined_type delta_transition_iterator;
      typedef undefined_type rdelta_state_iterator;
      typedef undefined_type rdelta_transition_iterator;
  };

# define VCSN_MAKE_AUTOMATON_TRAITS(Type)					\
  template <typename Kind,							\
	    typename WordValue,							\
	    typename WeightValue,						\
	    typename SeriesValue,						\
	    typename Letter,							\
	    typename Tag,							\
	    typename GeometryCoords>						\
  struct automaton_traits<Type<Kind, WordValue, WeightValue, SeriesValue,       \
			  Letter, Tag, GeometryCoords> >			\
  {										\
    typedef Type<Kind, WordValue, WeightValue, SeriesValue,		        \
		 Letter, Tag, GeometryCoords>		graph_t;		\
    typedef typename graph_t::semiring_elt_value_t	semiring_elt_value_t;	\
    typedef typename graph_t::monoid_elt_value_t	monoid_elt_value_t;	\
    typedef typename graph_t::word_value_t		word_value_t;		\
    typedef typename graph_t::series_set_elt_value_t	series_set_elt_value_t;	\
    typedef typename graph_t::letter_t			letter_t;		\
    typedef typename graph_t::tag_t			tag_t;			\
    typedef typename graph_t::geometry_t		geometry_t;		\
    typedef typename graph_t::label_t			label_t;		\
    typedef typename graph_t::states_t			states_t;		\
    typedef typename states_t::iterator			state_iterator;		\
    typedef typename graph_t::hstate_t			hstate_t;		\
    typedef typename graph_t::edges_t			transitions_t;		\
    typedef typename transitions_t::iterator		transition_iterator;	\
    typedef typename graph_t::htransition_t		htransition_t;		\
    typedef typename graph_t::initial_t			initial_t;		\
    typedef typename graph_t::initial_support_t		initial_support_t;	\
    typedef typename initial_support_t::iterator	initial_iterator;	\
    typedef typename graph_t::final_t			final_t;		\
    typedef typename graph_t::final_support_t		final_support_t;	\
    typedef typename final_support_t::iterator		final_iterator;		\
    typedef typename graph_t::delta_state_iterator	delta_state_iterator;	\
    typedef typename graph_t::delta_transition_iterator	delta_transition_iterator; \
    typedef typename graph_t::rdelta_state_iterator	rdelta_state_iterator;	\
    typedef typename graph_t::rdelta_transition_iterator	rdelta_transition_iterator; \
  }

  // traits for generalized automaton implementation.
  template <typename Auto>
  struct generalized_traits
  {
    typedef undefined_type automaton_t;
  };

# define VCSN_MAKE_GENERALIZED_AUTOMATON_TRAITS(Type)				\
  template <typename Struct,							\
	    typename Kind,							\
	    typename WordValue,							\
	    typename WeightValue,						\
	    typename SeriesValue,						\
	    typename Letter,							\
	    typename Tag,							\
	    typename GeometryCoords>						\
  struct generalized_traits<Element<Struct, Type<Kind, WordValue,		\
			    WeightValue, SeriesValue, Letter,			\
			    Tag, GeometryCoords> > >				\
  {										\
    typedef Element<Struct, Type<Kind, WordValue, WeightValue, SeriesValue,	\
		    Letter, Tag, GeometryCoords> > Auto_;			\
    typedef typename Auto_::series_set_t		series_set_t;		\
    typedef typename Auto_::kind_t			kind_t;			\
    typedef typename series_set_t::monoid_t		monoid_t;		\
    typedef typename Auto_::series_set_elt_t		series_set_elt_t;	\
    typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;		\
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;	\
    typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;		\
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;	\
    typedef typename Auto_::value_t::geometry_t		geometry_t;		\
    typedef vcsn::Element<vcsn::Automata<series_set_t, Kind>,			\
			  Type<labels_are_series,				\
			  monoid_elt_value_t,					\
			  semiring_elt_value_t,					\
			  rat::exp<monoid_elt_value_t, semiring_elt_value_t>,	\
			  typename monoid_t::letter_t,				\
			  NoTag,						\
			  typename geometry_t::coords_t>			\
			  > automaton_t;					\
    typedef typename automaton_t::hstate_t hstate_t;				\
    typedef typename automaton_t::htransition_t	htransition_t;			\
  }

  // traits to construct an automaton type from a rational expression type,
  // with a given structural type.
  // (the automaton type must be able to hold the value returned by
  // standard_of)
  // FIXME: there is no rat exp concept, so we put the code here. (maybe it
  // should be put here anyway)
  template <typename Struct, typename Ratexp>
  struct standard_of_traits
  {
    typedef undefined_type automaton_t;
  };

# define VCSN_MAKE_STANDARD_OF_TRAITS(Type)						\
  template <typename W,									\
	    typename M,									\
	    typename Tm,								\
	    typename Tw>								\
  struct standard_of_traits<algebra::Series<W, M>, rat::exp<Tm, Tw> >			\
  {											\
    typedef typename algebra::Series<W, M>		series_set_t;			\
    typedef typename algebra::polynom<Tm, Tw>						\
	series_set_elt_value_t;								\
    typedef typename M::letter_t			letter_t;			\
    typedef typename Type<labels_are_series, Tm, Tw,					\
			  series_set_elt_value_t, letter_t,				\
			  NoTag, std::pair<double, double> >				\
	automaton_impl_t;								\
    typedef Element<Automata<series_set_t, labels_are_series>, automaton_impl_t>	\
	automaton_t;									\
  }

  // Traits to construct misc projections from a structural type and
  // an implementation.
  template <typename S, typename T>
  struct projection_traits
  {
    /// Whether the automaton has a first projection computable.
    typedef undefined_type first_projection_t;

    /// Whether the automaton has a second projection computable.
    typedef undefined_type second_projection_t;
  };

  // Traits to mute an existing graph implementation into a projection
  // implementation with TT.
  // FIXME: rename to mute_graph_impl_projection_traits
  template <typename T, typename TT>
  struct mute_graph_impl_traits
  {
    /// Whether the implementation has a first projection computable.
    typedef undefined_type first_projection_t;

    /// Whether the implementation has a second projection computable.
    typedef undefined_type second_projection_t;
  };

# define VCSN_MAKE_MUTE_GRAPH_IMPL_TRAITS(Type)					\
  template <typename Kind,							\
	    typename WordValue,							\
	    typename WeightValue,						\
	    typename SeriesValue,						\
	    typename Letter,							\
	    typename Tag,							\
	    typename GeometryCoords,						\
	    typename TT>							\
  struct mute_graph_impl_traits<Type<Kind,					\
				     WordValue,					\
				     WeightValue,				\
				     SeriesValue,				\
				     Letter,					\
				     Tag,					\
				     GeometryCoords>, TT>			\
  {										\
    typedef Type<Kind, WordValue, WeightValue, SeriesValue,			\
		 Letter, Tag, GeometryCoords> graph_t;				\
    typedef typename algebra::letter_traits<Letter>::				\
			first_projection_t first_letter_t;			\
    typedef typename algebra::letter_traits<Letter>::				\
			second_projection_t second_letter_t;			\
    typedef typename TT::first_projection_t::value_t				\
			first_monoid_elt_value_t;				\
    typedef typename TT::second_projection_t::value_t				\
			second_monoid_elt_value_t;				\
    typedef typename algebra::mute_series_impl<SeriesValue, WeightValue,	\
					       first_monoid_elt_value_t>::ret	\
					       first_series_impl_t;		\
    typedef typename algebra::mute_series_impl<SeriesValue, WeightValue,	\
					       second_monoid_elt_value_t>::ret	\
					       second_series_impl_t;		\
    typedef Type<Kind, first_monoid_elt_value_t,				\
		 WeightValue, first_series_impl_t,				\
		 first_letter_t, Tag, GeometryCoords> first_projection_t;	\
    typedef Type<Kind, second_monoid_elt_value_t,				\
		 WeightValue, second_series_impl_t,				\
		 second_letter_t, Tag, GeometryCoords> second_projection_t;	\
  }

  // Traits to mute an existing graph implementation into another
  // graph implementation with a different word implementation and letter
  // implementation.
  template <typename G, typename W, typename L>
  struct mute_graph_impl_monoid_traits
  {
    /// The computed new implementation.
    typedef undefined_type ret;
  };

# define VCSN_MAKE_MUTE_GRAPH_IMPL_MONOID_TRAITS(Type)				\
  template <typename Kind,							\
	    typename WordValue,							\
	    typename WeightValue,						\
	    typename SeriesValue,						\
	    typename Letter,							\
	    typename Tag,							\
	    typename GeometryCoords,						\
	    typename W,								\
	    typename L>								\
  struct mute_graph_impl_monoid_traits<Type<Kind,				\
					    WordValue,				\
					    WeightValue,			\
					    SeriesValue,			\
					    Letter,				\
					    Tag,				\
					    GeometryCoords>, W, L>		\
  {										\
    typedef Type<Kind, WordValue, WeightValue, SeriesValue,			\
		 Letter, Tag, GeometryCoords> graph_t;				\
    typedef typename algebra::mute_series_impl<SeriesValue, WeightValue,	\
					       W>::ret				\
					       series_impl_t;			\
    typedef Type<Kind, W,							\
		 WeightValue, series_impl_t,					\
		 L, Tag, GeometryCoords> ret;					\
  }

  /*-----------------------------------.
  | virtual_types<AutomataBase<Self> > |
  `-----------------------------------*/

  template <class S>
  struct virtual_types<AutomataBase<S> >
    : virtual_types<Structure<S> >
  { };

  /*------------------------------------.
  | dynamic_traits<AutomataBase<Self> > |
  `------------------------------------*/
  template <class S>
  struct dynamic_traits<AutomataBase<S> >
    : dynamic_traits<Structure<S> >
  { };

  /*-----------------------------------.
  | MetaElement<AutomataBase<Self>, T> |
  `-----------------------------------*/
  /// Services of every element of the automata set.
  /** MetaElement<AutomataBase<Self>, T> defines the interface of
   every automaton that is the result of the interaction of a
   structural element (AutomataBase<Self>) and an implementation T.

   The implementation must be compatible with the automaton
   implementation concept. For this purpose, you can either use
   directly your implementation of automaton or use for example the
   class automaton_impl which is an adapter that enrich basic data
   structures to make them compatible with automaton implementation
   concept.

   */

  // FIXME: Use some of the TYPEDEF_IMPORT macros.
  template <typename Self, typename T>
  struct MetaElement<AutomataBase<Self>, T>
    : MetaElement<Structure<Self>, T>
  {
      /// Type of the interface of an automaton.
      typedef MetaElement<AutomataBase<Self>, T>	self_t;

      /// Type the series set from which is the automaton is built.
      typedef typename AutomataBase<Self>::series_set_t	series_set_t;

      /// Type the label kind with which is the automaton is built.
      typedef typename AutomataBase<Self>::kind_t	kind_t;

      /// Type of the implementation of series that holds the automaton.
      typedef typename automaton_traits<T>::series_set_elt_value_t
      series_set_elt_value_t;

      /// Type of the element of the set of series that holds the automaton.
      typedef Element<series_set_t, series_set_elt_value_t> series_set_elt_t;

      /// Type of the free monoid.
      typedef typename series_set_t::monoid_t		monoid_t;

      /// Type of the free monoid element.
      typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;

      /// Type of the implementation of a word.
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;

      /// Type of the letter.
      typedef typename monoid_t::letter_t		letter_t;

      /// Type of the semiring set.
      typedef typename series_set_t::semiring_t		semiring_t;

      /// Type of the free monoid element.
      typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;

      /// Type of the implementation of a semiring_elt.
      typedef typename series_set_elt_t::semiring_elt_value_t
      semiring_elt_value_t;

      /// Type of additional information that is aggregated to the automaton.
      typedef typename automaton_traits<T>::tag_t		tag_t;

      /// Type of the label of the automaton implementation.
      typedef typename automaton_traits<T>::label_t	label_t;

      /// Type of the states container.
      typedef typename automaton_traits<T>::states_t	states_t;

      /// Type of the iterator over the states set.
      typedef typename automaton_traits<T>::state_iterator state_iterator;

      /// Type of the transitions set.
      typedef typename automaton_traits<T>::transitions_t transitions_t;

      /// Type of the iterator over the transitions.
      typedef typename automaton_traits<T>::transition_iterator transition_iterator;

      /// Type of the initial application support.
      typedef typename automaton_traits<T>::initial_support_t initial_support_t;

      /// Type of the iterator of the initial application support.
      typedef typename automaton_traits<T>::initial_iterator initial_iterator;

      /// Type of the final application support.
      typedef typename automaton_traits<T>::final_support_t final_support_t;

      /// Type of the iterator of the final application support.
      typedef typename automaton_traits<T>::final_iterator final_iterator;

      /// Type of the geometry map containing state coordinates.
      typedef typename automaton_traits<T>::geometry_t	geometry_t;

       /// Type of the coordinates used in the geometry map.
      typedef typename automaton_traits<T>::geometry_t::coords_t geometry_coords_t;

      /// Type of handlers
      typedef typename automaton_traits<T>::hstate_t hstate_t;
      typedef typename automaton_traits<T>::htransition_t htransition_t;

      /// Type of delta iterators
      typedef typename automaton_traits<T>::delta_state_iterator delta_state_iterator;
      typedef typename automaton_traits<T>::delta_transition_iterator delta_transition_iterator;
      typedef typename automaton_traits<T>::rdelta_state_iterator rdelta_state_iterator;
      typedef typename automaton_traits<T>::rdelta_transition_iterator rdelta_transition_iterator;

      /// The set of series from which is build the automaton.
      const series_set_t& series() const;

      /// The optional information aggregated to the automaton.
      tag_t& tag();

      /// The optional information aggregated to the automaton.
      const tag_t& tag() const;

      /// The optional geometry information aggregated to the automaton.
      geometry_t& geometry();

      /// The optional geometry information aggregated to the automaton.
      const geometry_t& geometry() const;

      /// Return true if the automaton is consistent.
      bool exists() const;

      /// FIXME: These next two methods should really be replaced with
      /// (single, i.e. not begin and end) iterators. (See Trac #191.)
      
      /// Accessor to the set of states. (treat as const)
      states_t states() const;

      /// Accessor to the set of transitions. (treat as const)
      transitions_t transitions() const;

      /// Accessor to the initial application.
      initial_support_t initial() const;

      /// Accessor to the final application.
      final_support_t final() const;

      /// Return true if the state is initial (i.e. is in the initial support).
      bool is_initial(const hstate_t& state) const;
      bool is_initial(unsigned state) const;

      /// Return true if the state is final (i.e. is in the final support).
      bool is_final(const hstate_t& state) const;
      bool is_final(unsigned state) const;

      /// Set the state to be initial.
      void set_initial(const hstate_t& state);
      void set_initial(unsigned state);

      /// Set an initial multiplicity to the state.
      void set_initial(const hstate_t& state, const series_set_elt_t& m);
      void set_initial(unsigned state, const series_set_elt_t& m);

      /// Set the state to be final.
      void set_final(const hstate_t& state);
      void set_final(unsigned state);

      /// Set a final multiplicity to the state.
      void set_final(const hstate_t& state, const series_set_elt_t& m);
      void set_final(unsigned state, const series_set_elt_t& m);

      /// Set the state not to be initial.
      void unset_initial(const hstate_t& state);
      void unset_initial(unsigned state);

      /// Set the set not to be final.
      void unset_final(const hstate_t& state);
      void unset_final(unsigned state);

      /// Make the support of the initial application to be empty.
      void clear_initial();

      /// Make the support of the final application to be empty.
      void clear_final();

      /// Return the initial multiplicity of the state.
      Element<series_set_t, series_set_elt_value_t>
      get_initial(const hstate_t& state) const;
      Element<series_set_t, series_set_elt_value_t>
      get_initial(unsigned state) const;

      /// Return the final multiplicity of the state.
      Element<series_set_t, series_set_elt_value_t>
      get_final(const hstate_t& state) const;
      Element<series_set_t, series_set_elt_value_t>
      get_final(unsigned state) const;

      /// Add a new state to the automaton.
      hstate_t add_state();

      /// Return a state descriptor for state number 'state'.
      hstate_t get_state(unsigned state) const;

      /** Return a randomly chosen state. (valid only if the automaton
       is not empty) */
      hstate_t choose_state() const;

      /// Add a new transition between @c src and @c dst labelled by @c label
      htransition_t add_transition(const hstate_t& src, const hstate_t& dst,
				   const label_t& label);
      htransition_t add_transition(unsigned src, unsigned dst,
				   const label_t& label);

      /** Add a new weighted transition, specifying a semiring element
       * and a monoid element. */
      htransition_t add_weighted_transition(const hstate_t& src, const hstate_t& dst,
					    const semiring_elt_t& w,
					    const monoid_elt_value_t& m);
      htransition_t add_weighted_transition(unsigned src, unsigned dst,
					    const semiring_elt_t& w,
					    const monoid_elt_value_t& m);

      /// Add a transition using a series.
      /** If the underlying implementation is not sufficiently general
       *  to support this operation, you will have several transitions
       *  created. */
      htransition_t add_series_transition(const hstate_t& src, const hstate_t& dst,
					  const series_set_elt_t& e);
      htransition_t add_series_transition(unsigned src, unsigned dst,
					  const series_set_elt_t& e);

      /// Add a spontaneous transition between @c src and @c dst.
      htransition_t add_spontaneous(const hstate_t& src, const hstate_t& dst,
				    const semiring_elt_t& w);

      htransition_t add_spontaneous(const hstate_t& src, const hstate_t& dst);

      htransition_t add_spontaneous(unsigned src, unsigned dst,
				    const semiring_elt_t& w);

      htransition_t add_spontaneous(unsigned src, unsigned dst);

      /// Add a transition between @c src and @c dst labelled by a letter.
      htransition_t add_letter_transition(const hstate_t& src, const hstate_t& dst,
					  const letter_t& l);
      htransition_t add_letter_transition(unsigned src, unsigned dst,
					  const letter_t& l);

      /** Add a transition between @c src and @c dst labelled by a letter from
       * its literal representation */
      htransition_t add_letter_transition(const hstate_t& src, const hstate_t& dst,
					  const std::string& l);
      htransition_t add_letter_transition(unsigned src, unsigned dst,
					  const std::string& l);

      /// Update the label of a transition.
      void update(const htransition_t& e, const label_t& l);

      /// Delete the state @c s.
      void del_state(const hstate_t& state);
      void del_state(unsigned state);

      /// Delete the transition @c e.
      void del_transition(const htransition_t& e);

      /// Check if the state @c s is in the automaton.
      bool has_state(const hstate_t& state) const;
      bool has_state(unsigned state) const;

      /// Check if the transition @c e is in the automaton.
      bool has_transition(const htransition_t& e) const;

      /// Return the origin of the transition @c e.
      hstate_t src_of(const htransition_t& e) const;

      /// Return the aim of the transition @c e.
      hstate_t dst_of(const htransition_t& e) const;

      /// Return the label of the transition @c e.
      typename automaton_traits<T>::label_t label_of(const htransition_t& e) const;

      /// Return the label seen as a series.
      series_set_elt_t series_of(const htransition_t& e) const;

      /// Return the label seen as a series implementation.
      series_set_elt_value_t series_value_of(const htransition_t& e) const;

      /// Return true if the transition is spontaneous.
      bool is_spontaneous(const htransition_t& e) const;

      /// Return the label seen as a word.
      monoid_elt_t word_of(const htransition_t& e) const;

      /// Return the label seen as a weight.
      semiring_elt_t weight_of(const htransition_t& e) const;

      /// Returns the label seen as word implementation.
      monoid_elt_value_t word_value_of(const htransition_t& e) const;

      /// Return the label seen as a letter.
      /** Be careful, when you have more general label this method is
       *! probably invalidated (in that case, an exception should be
       *! raised.) */
      letter_t letter_of(const htransition_t& e) const;


    protected:
      MetaElement();
      MetaElement(const MetaElement& other);
  };

  /// @}
  /// @}

  template <typename S, typename St, typename T>
  St& op_rout(const AutomataBase<S>& s, St& st, const T& r);

  template <typename Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from);
} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/concept/automata_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_BASE_HH
