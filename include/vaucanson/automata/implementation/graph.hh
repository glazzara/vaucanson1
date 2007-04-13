// graph.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HH

# include <set>
# include <map>
# include <vector>

# include <vaucanson/misc/sparse_interval.hh>
# include <vaucanson/misc/support.hh>
# include <vaucanson/misc/static.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/implementation/geometry.hh>


namespace vcsn
{


  typedef htransition_t hedge_t;
  namespace delta_kind
  {
    typedef transitions edges;
  }

  /// Edge decorator.
  template<typename EdgeLabel>
  struct edge_value
  {
      edge_value(hstate_t, hstate_t, const EdgeLabel& v = EdgeLabel());

      operator const EdgeLabel& () const
      { return label; }
      operator EdgeLabel& ()
      { return label; }

      EdgeLabel	label;
      hstate_t	from;
      hstate_t	to;
  };

  /// State decorator.
  struct state_value
  {
      typedef std::set<hedge_t> edges_t;
      state_value();

      edges_t output_edges;
      edges_t input_edges;
  };

  /// Needed containers.
  /// FIXME: How about using std::vector instead of std::set?
  typedef misc::SparseInterval<hstate_t, std::set<hstate_t> > StateContainer;
  typedef misc::SparseInterval<hedge_t, std::set<hedge_t> > EdgeContainer;


  /// Graph
  template <class K, class WordValue, class WeightValue,
	    class SeriesValue, class Letter, class Tag, class Geometry>
  class Graph
  {
      /// Self type definition.
    public:
      typedef Graph<K, WordValue, WeightValue, SeriesValue,
		    Letter, Tag, Geometry>			self_t;

      /// Typedefs on automaton related graphs elements.
    public:
      typedef typename LabelOf<K, WordValue, WeightValue, SeriesValue, Letter>
      ::ret label_t;

      typedef state_value			state_value_t;
      typedef edge_value<label_t>		edge_value_t;

// FIXME: clean from automaton_traits
      typedef std::vector<state_value_t>	state_data_t;
// FIXME rm?     typedef std::vector<edge_value_t>		edge_data_t;

      typedef StateContainer		states_t;
      typedef EdgeContainer		edges_t;

      typedef SeriesValue			series_set_elt_value_t;

      typedef std::map<hstate_t, series_set_elt_value_t> initial_t;
      typedef std::map<hstate_t, series_set_elt_value_t> final_t;

      typedef misc::Support<initial_t>	initial_support_t;
      typedef misc::Support<final_t>	final_support_t;

    public:
      // we guarantee that the handlers of state are indexed from 0 to
      // initial_number_of_state - 1 when using this constructor.
      Graph();
      Graph(unsigned initial_number_of_state,
	    unsigned number_of_edge_initially_allocated);

      /// Return states set.
      states_t states() const;

      /// Return edges set.
      edges_t edges() const;

      /// Initial/final state supports.
      initial_support_t initial() const;
      final_support_t final() const;

      /** @name State's manipulation
       ** @{ */
    public:
      bool has_state(hstate_t n) const;

    public:
      hstate_t add_state();

      /// Remove state \a n.
      ///
      /// \pre \a n is a state of this graph.
      void del_state(hstate_t n);

    public:
      /// Change whether a state is initial or not.
      /// \param s  the state
      /// \param v  its associated label
      /// \param z  the zero for the labels
      ///
      /// \note If v == z then state is removed from the set of initial
      /// states.  Because of this, one cannot simply write
      /// \code
      /// typename automaton_t::series_set_elt_t some_weight = ...;
      /// for_all_final_states(f, aut)
      ///   lhs.set_final(*f, aut.get_final(*f) * some_weight);
      /// \endcode
      /// because if \c some_weight is equal to \c z, then the state
      /// is removed from the set of final states, and invalidates all
      /// the iterators: the loop is broken.
      void set_initial(hstate_t s,
		       const series_set_elt_value_t& v,
		       const series_set_elt_value_t& z);
      const series_set_elt_value_t&
      get_initial(hstate_t, const series_set_elt_value_t&) const;
      void clear_initial();

      /// Change whether a state is final or not.
      /// \param s  the state
      /// \param v  its associated label
      /// \param z  the zero for the labels
      ///
      /// \sa set_initial().
      void set_final(hstate_t,
		     const series_set_elt_value_t&,
		     const series_set_elt_value_t&);
      const series_set_elt_value_t&
      get_final(hstate_t, const series_set_elt_value_t&) const;
      void clear_final();
      /** @}*/


      /** @name Edge's manipulation
       ** @{ */
    public:
      bool has_edge(hedge_t n) const;

    public:
      hedge_t add_edge(hstate_t h1, hstate_t h2, const label_t& v);
      void del_edge(hedge_t e);

    public:
      hstate_t src_of(hedge_t e1) const;
      hstate_t dst_of(hedge_t e2) const;

    public:
      const label_t& label_of(hedge_t n) const;
      void update(hedge_t, label_t);
      /** @} */

      /** @name Only automaton related methods
       ** @{ */
    public:
      template <class S>
      bool exists(const AutomataBase<S>& s) const;

    public:

      /// Delta, Reverse deltas, for functor and iterator.
# define DECLARE_DELTA_FUNCTION(DeltaName, DKind)			\
    template <class OutputIterator, typename Query>			\
    void DeltaName(OutputIterator res, hstate_t from,			\
		   const Query& q, delta_kind::DKind) const
      DECLARE_DELTA_FUNCTION (delta, states);
      DECLARE_DELTA_FUNCTION (delta, edges);
      DECLARE_DELTA_FUNCTION (rdelta, states);
      DECLARE_DELTA_FUNCTION (rdelta, edges);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION(DeltaName, DKind, IsBool)		\
    template <class Functor, typename Query>				\
    void DeltaName(Functor& fun, hstate_t from,				\
		   const Query& q, delta_kind::DKind,			\
		   misc::IsBool ## _t) const
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, true);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, false);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, edges, true);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, edges, false);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, true);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, false);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, edges, true);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, edges, false);
# undef DECLARE_DELTAF_BOOL_FUNCTION

# define DECLARE_DELTAF_FUNCTION(DeltaName)				\
    template <class Functor, typename Query, typename DKind>		\
    void DeltaName(Functor& fun, hstate_t from,				\
		   const Query& q, delta_kind::kind<DKind>) const
      DECLARE_DELTAF_FUNCTION (deltaf);
      DECLARE_DELTAF_FUNCTION (rdeltaf);

# undef DECLARE_DELTAF_FUNCTION

      /** @}*/

    public:
      /// FIXME: Not implemented.
      self_t& clone() const;

      /** @name Tag access
       ** @{ */
    public:
      typedef Tag tag_t;
      tag_t& tag();
      const tag_t& tag() const;
      /** @}*/

      /** @name Geometry access
       ** @{ */
    public:
      typedef Geometry geometry_t;
      geometry_t& geometry();
      const geometry_t&	geometry() const;
      /** @}*/

    private:
      geometry_t		geometry_;

    public:
      state_data_t		states_;
      edge_data_t		edges_;
      std::set<hstate_t>	removed_states_;
      std::set<hedge_t>		removed_edges_;
      tag_t			tag_;
      final_t			final_;
      initial_t			initial_;
  };


# define TParam								\
  template <class S, class WordValue, class WeightValue, class SeriesValue, \
	    class Letter, class Tag, class Geometry>

  TParam
  ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(Graph<labels_are_series,
					      WordValue, WeightValue,
					      SeriesValue, Letter, Tag, Geometry>);


  TParam
  ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag, Geometry>);

  TParam
  ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				WordValue, WeightValue,
				SeriesValue, Letter, Tag, Geometry>);

  TParam
  ADAPT_WORD_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				 WordValue, WeightValue,
				 SeriesValue, Letter, Tag, Geometry>);

  TParam
  ADAPT_SERIE_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag, Geometry>);

  TParam
  ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(Graph<labels_are_letters,
					      WordValue, WeightValue,
					      SeriesValue, Letter, Tag, Geometry>);

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  Tag& op_tag(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag, Geometry>&);

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  const Tag& op_tag(const AutomataBase<I>&,
		    const Graph<Kind, WordValue, WeightValue,
		    SerieValue, Letter, Tag, Geometry>&);

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  Geometry&
  op_geometry(const AutomataBase<I>&,
	      Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag, Geometry>&);

  template <class Kind, class WordValue, class WeightValue, class SerieValue,
	    class Letter, class Tag, class Geometry, class I>
  const Geometry&
  op_geometry(const AutomataBase<I>&,
	      const Graph<Kind, WordValue, WeightValue,
	      SerieValue, Letter, Tag, Geometry>&);



# undef TParam

  // This implementation can be used as an implementation of automaton.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class Geometry>
  struct automaton_traits<Graph<Kind,
				WordValue,
				WeightValue,
				SeriesValue,
				Letter,
				Tag,
				Geometry>  >
  {
      typedef SeriesValue				series_set_elt_value_t;
      typedef WordValue					word_value_t;
      typedef WordValue					monoid_elt_value_t;
      typedef WeightValue				semiring_elt_value_t;
      typedef Letter					letter_t;
      typedef typename LabelOf<Kind, WordValue, WeightValue, SeriesValue, Letter>
      ::ret						label_t;
      typedef Tag					tag_t;
      typedef edge_value<label_t>			transition_value_t;
      typedef state_value				state_value_t;
      typedef std::vector<state_value_t>		state_data_t;
      typedef std::vector<transition_value_t>		transition_data_t;

      typedef StateContainer				states_t;
      typedef EdgeContainer				transitions_t;

      typedef typename states_t::iterator		state_iterator;
      typedef typename transitions_t::iterator		transition_iterator;

      typedef std::map<hstate_t, series_set_elt_value_t>	initial_t;
      typedef std::map<hstate_t, series_set_elt_value_t>	final_t;
      typedef misc::Support<initial_t>			initial_support_t;
      typedef misc::Support<final_t>			final_support_t;
      typedef typename initial_support_t::iterator	initial_iterator;
      typedef typename final_support_t::iterator	final_iterator;

      typedef Geometry					geometry_t;
  };

  // This implementation can be used as a transducer one.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class Geometry>
  struct transducer_traits<Graph<Kind,
				 WordValue,
				 WeightValue,
				 SeriesValue,
				 Letter,
				 Tag,
				 Geometry>  >
  {
      typedef WordValue			input_monoid_elt_value_t;
      typedef typename algebra::series_traits<WeightValue>::monoid_elt_value_t
      output_monoid_elt_value_t;
      typedef typename algebra::series_traits<WeightValue>::semiring_elt_value_t
      output_semiring_elt_value_t;
  };

  // Explain how to project type of transducer into input automaton type.
  template <class S,
	    class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class Geometry>
  struct projection_traits<S, Graph<Kind,
				    WordValue,
				    WeightValue,
				    SeriesValue,
				    Letter,
				    Tag,
				    Geometry>  >
  {
      typedef Graph<Kind, WordValue, WeightValue, SeriesValue,
		    Letter, Tag, Geometry>			self_t;
      typedef typename transducer_traits<self_t>::output_semiring_elt_value_t
      semiring_elt_value_t;
      typedef typename transducer_traits<self_t>::input_monoid_elt_value_t
      monoid_elt_value_t;
      typedef typename algebra::mute_series_impl<SeriesValue,
						 semiring_elt_value_t,
						 monoid_elt_value_t>
      ::ret series_set_elt_value_t;

      typedef
      Graph<Kind,
	    monoid_elt_value_t,
	    semiring_elt_value_t,
	    series_set_elt_value_t,
	    Letter,
	    Tag,
	    Geometry>
      ret;
  };

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class Geometry>
  struct output_projection_traits<Graph<Kind,
					WordValue,
					WeightValue,
					SeriesValue,
					Letter,
					Tag, Geometry>	>
  {
      typedef Graph<Kind, WordValue, WeightValue, SeriesValue,
		    Letter, Tag, Geometry>			self_t;

      typedef typename automaton_traits<self_t>::semiring_elt_value_t
      series_set_elt_value_t;

      typedef typename
      algebra::series_traits<series_set_elt_value_t>::monoid_elt_value_t
      monoid_elt_value_t;

      typedef typename
      algebra::series_traits<series_set_elt_value_t>::semiring_elt_value_t
      semiring_elt_value_t;

      typedef
      Graph<Kind,
	    monoid_elt_value_t,
	    semiring_elt_value_t,
	    series_set_elt_value_t,
	    Letter,
	    Tag,
	    Geometry>
      ret;
  };

  // Explain how to extend an input automaton into a transducer.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class Geometry>
  struct extension_traits<Graph<Kind,
				WordValue,
				WeightValue,
				SeriesValue,
				Letter,
				Tag,
				Geometry>  >
  {
      typedef Graph<Kind, WordValue, WeightValue,
		    SeriesValue, Letter, Tag, Geometry>		self_t;
      typedef typename automaton_traits<self_t>::monoid_elt_value_t
      monoid_elt_value_t;
      typedef typename algebra::mute_series_impl<SeriesValue, SeriesValue, monoid_elt_value_t>
      ::ret series_set_elt_value_t;

      typedef
      Graph<Kind,
	    monoid_elt_value_t,
	    SeriesValue,
	    series_set_elt_value_t,
	    Letter,
	    Tag,
	    Geometry>
      ret;
  };

}


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/graph.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GRAPH_HH
