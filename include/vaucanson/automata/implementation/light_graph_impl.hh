// light_graph_impl.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HH

# include <set>
# include <map>
# include <vector>

# include <vaucanson/misc/sparse_interval.hh>
# include <vaucanson/misc/static.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/automata/implementation/light/light_support.hh>

namespace vcsn
{
  namespace light
  {
    /// Graph
    template <class K, class WordValue, class WeightValue,
	      class SeriesValue, class Letter, class Tag, class GeometryCoords>
    class Graph
    {
      /// Self type definition.
      public:
	typedef Graph<K, WordValue, WeightValue, SeriesValue,
		      Letter, Tag, GeometryCoords>  self_t;

        typedef WeightValue             semiring_elt_value_t;
        typedef WordValue               monoid_elt_value_t;
	typedef WordValue               word_value_t;
        typedef SeriesValue             series_set_elt_value_t;
        typedef Letter                  letter_t;
        typedef Tag                 tag_t;

	/// Typedefs on automaton related graphs elements.
	typedef typename LabelOf<K, WordValue, WeightValue, SeriesValue, Letter>
	  ::ret						label_t;

	typedef handler<state_h, int>				hstate_t;
	typedef handler<transition_h, int>		htransition_t;
	typedef htransition_t								hedge_t;


	struct EdgeValue
	{
	  EdgeValue (const hstate_t& from, const hstate_t& to, label_t l)
	    : from_(from), to_(to), label_(l) {}

	  hstate_t from_;
	  hstate_t to_;
	  label_t label_;
	}; // End of class EdgeValue

	typedef hstate_t				state_data_t;
	typedef std::vector<hstate_t>			states_base_t;
	typedef misc::Support<states_base_t>		states_t;
	typedef std::vector<htransition_t>		edges_base_t;
	typedef misc::Support<edges_base_t>		edges_t;
	typedef std::vector<EdgeValue>			edge_data_t;

	typedef std::map<hstate_t, series_set_elt_value_t>
	  initial_t;
	typedef std::map<hstate_t, series_set_elt_value_t>
	  final_t;

	typedef misc::Support<initial_t>		initial_support_t;
	typedef misc::Support<final_t>			final_support_t;

	// we guarantee that the handlers of state are indexed from 0 to
	// initial_number_of_state - 1 when using this constructor.
	Graph();
	Graph(unsigned reserve_number_of_state,
	      unsigned reserve_number_of_edge);

	/// Return states set.
	states_t	    states() const;

	/// Return edges set.
	edges_t		    edges() const;

	/// Initial/final state supports.
	initial_support_t   initial() const;
	final_support_t	    final() const;

	/** @name State's manipulation
	** @{ */
	bool		    has_state(const hstate_t& n) const;

	hstate_t	    add_state();

	/// Remove state \a n.
	///
	/// \pre \a n is a state of this graph.
	void		    del_state(const hstate_t& n);

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
	void		    set_initial(const hstate_t& s,
					const series_set_elt_value_t& v,
					const series_set_elt_value_t& z);
	const series_set_elt_value_t&
			    get_initial(const hstate_t&,
					const series_set_elt_value_t&) const;
	bool		    is_initial(const hstate_t& s,
				       const series_set_elt_value_t&) const;

	void		    clear_initial();

	/// Change whether a state is final or not.
	/// \param s  the state
	/// \param v  its associated label
	/// \param z  the zero for the labels
	///
	/// \sa set_initial().
	void		    set_final(const hstate_t&,
				      const series_set_elt_value_t&,
				      const series_set_elt_value_t&);
	const series_set_elt_value_t&
			    get_final(const hstate_t&,
				      const series_set_elt_value_t&) const;
	bool		    is_final(const hstate_t& s,
				     const series_set_elt_value_t&) const;

	void		    clear_final();
	/** @}*/


	/** @name Edge's manipulation
	** @{ */
	bool		    has_edge(const hedge_t& n) const;

	hedge_t		    add_edge(const hstate_t& h1,
				     const hstate_t& h2,
				     const label_t& v);
	void		    del_edge(const hedge_t& e);

	hstate_t	    src_of(const hedge_t& e1) const;
	hstate_t	    dst_of(const hedge_t& e2) const;

	const label_t&	    label_of(const hedge_t& n) const;
	void		    update(const hedge_t&, const label_t&);
	/** @} */

	/** @name Only automaton related methods
	** @{ */
	template <class S>
	bool		    exists(const AutomataBase<S>& s) const;

	/// Delta, Reverse deltas, for functor and iterator.
# define DECLARE_DELTA_FUNCTION(DeltaName, DKind)			\
	template <class OutputIterator, typename Query>			\
	void DeltaName(OutputIterator res, const hstate_t& from,	\
		       const Query& q, ::vcsn::delta_kind::DKind) const
	DECLARE_DELTA_FUNCTION (delta, states);
	DECLARE_DELTA_FUNCTION (delta, transitions);
	DECLARE_DELTA_FUNCTION (rdelta, states);
	DECLARE_DELTA_FUNCTION (rdelta, transitions);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION(DeltaName, DKind, IsBool)		\
	template <class Functor, typename Query>			\
	void DeltaName(Functor& fun, const hstate_t& from,		\
		       const Query& q, ::vcsn::delta_kind::DKind,	\
		       misc::IsBool ## _t) const
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, false);
# undef DECLARE_DELTAF_BOOL_FUNCTION

# define DECLARE_DELTAF_FUNCTION(DeltaName)				\
	template <class Functor, typename Query, typename DKind>	\
	void DeltaName(Functor& fun, const hstate_t& from,		\
		       const Query& q, ::vcsn::delta_kind::kind<DKind>) const
	DECLARE_DELTAF_FUNCTION (deltaf);
	DECLARE_DELTAF_FUNCTION (rdeltaf);

# undef DECLARE_DELTAF_FUNCTION

	/** @}*/

	/// FIXME: Not implemented.
	self_t&		    clone() const;

	/** @name Tag access
	** @{ */
	tag_t&		    tag();
	const tag_t&	    tag() const;
	/** @}*/

	/** @name Geometry access
	** @{ */
	typedef geometry<hstate_t, hedge_t, GeometryCoords> geometry_t;
	geometry_t&	    geometry();
	const geometry_t&   geometry() const;
	/** @}*/

      	private:
	  geometry_t	    geometry_;
	  states_base_t	    states_;
	  edges_base_t	    edges_;
	  edge_data_t	    edge_data_;
	  tag_t		    tag_;
	  final_t	    final_;
	  initial_t	    initial_;
    };


# define TParam								\
    template <class S, class WordValue, class WeightValue, class SeriesValue, \
	      class Letter, class Tag, class GeometryCoords>
# define GRAPH \
    Graph<Kind, WordValue, WeightValue, SerieValue, \
	  Letter, Tag, GeometryCoords>



    TParam
    ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(Graph<labels_are_series,
						WordValue, WeightValue,
						SeriesValue, Letter, Tag,
						GeometryCoords>);

    TParam
    ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				    WordValue, WeightValue,
				    SeriesValue, Letter, Tag,
				    GeometryCoords>);

    TParam
    ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag,
				  GeometryCoords>);

    TParam
    ADAPT_WORD_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				   WordValue, WeightValue,
				   SeriesValue, Letter, Tag,
				   GeometryCoords>);

    TParam
    ADAPT_SERIE_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				    WordValue, WeightValue,
				    SeriesValue, Letter, Tag,
				    GeometryCoords>);

    TParam
    ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(Graph<labels_are_letters,
						WordValue, WeightValue,
						SeriesValue, Letter, Tag,
						GeometryCoords>);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    Tag&		    op_tag(const AutomataBase<I>&,
				   Graph<Kind, WordValue, WeightValue,
				   SerieValue, Letter, Tag,
				   GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const Tag&		    op_tag(const AutomataBase<I>&,
				   const Graph<Kind, WordValue, WeightValue,
				   SerieValue, Letter, Tag, GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    typename GRAPH::geometry_t&
			    op_geometry(const AutomataBase<I>&,
					Graph<Kind, WordValue, WeightValue,
					SerieValue, Letter, Tag, GeometryCoords>&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const typename GRAPH::geometry_t&
			    op_geometry(const AutomataBase<I>&,
					const Graph<Kind, WordValue,
					WeightValue, SerieValue, Letter, Tag,
					GeometryCoords>&);
# undef TParam
# undef GRAPH

  } // End of namespace light


  // This implementation can be used as an implementation of automaton.
  VCSN_MAKE_AUTOMATON_TRAITS(light::Graph);

  // This implementation can be used as a transducer one.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct transducer_traits<light::Graph<Kind,
					 WordValue,
					 WeightValue,
					 SeriesValue,
					 Letter,
					 Tag,
					 GeometryCoords> >
  {
    typedef WordValue	      input_monoid_elt_value_t;
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
	    class GeometryCoords>
  struct projection_traits<S, light::Graph<Kind,
					    WordValue,
					    WeightValue,
					    SeriesValue,
					    Letter,
					    Tag,
					    GeometryCoords> >
  {
    typedef light::Graph<Kind, WordValue, WeightValue, SeriesValue,
			  Letter, Tag, GeometryCoords>
			      self_t;
    typedef typename transducer_traits<self_t>::output_semiring_elt_value_t
			      semiring_elt_value_t;
    typedef typename transducer_traits<self_t>::input_monoid_elt_value_t
			      monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
					       semiring_elt_value_t,
					       monoid_elt_value_t>::ret
			      series_set_elt_value_t;

    typedef
    light::Graph<Kind,
		  monoid_elt_value_t,
		  semiring_elt_value_t,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct output_projection_traits<light::Graph<Kind,
						WordValue,
						WeightValue,
						SeriesValue,
						Letter,
						Tag, GeometryCoords> >
  {
    typedef light::Graph<Kind, WordValue, WeightValue, SeriesValue,
			  Letter, Tag, GeometryCoords>
			      self_t;

    typedef typename automaton_traits<self_t>::semiring_elt_value_t
			      series_set_elt_value_t;

    typedef typename
    algebra::series_traits<series_set_elt_value_t>::monoid_elt_value_t
			      monoid_elt_value_t;

    typedef typename
    algebra::series_traits<series_set_elt_value_t>::semiring_elt_value_t
			      semiring_elt_value_t;

    typedef
    light::Graph<Kind,
		  monoid_elt_value_t,
		  semiring_elt_value_t,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };

  // Explain how to extend an input automaton into a transducer.
  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SeriesValue,
	    class Letter,
	    class Tag,
	    class GeometryCoords>
  struct extension_traits<light::Graph<Kind,
					WordValue,
					WeightValue,
					SeriesValue,
					Letter,
					Tag,
					GeometryCoords> >
  {
    typedef light::Graph<Kind, WordValue, WeightValue,
			  SeriesValue, Letter, Tag, GeometryCoords>
			      self_t;
    typedef typename automaton_traits<self_t>::monoid_elt_value_t
			      monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
					       SeriesValue,
					       monoid_elt_value_t>::ret
			      series_set_elt_value_t;

    typedef
    light::Graph<Kind,
		  monoid_elt_value_t,
		  SeriesValue,
		  series_set_elt_value_t,
		  Letter,
		  Tag,
		  GeometryCoords>
			      ret;
  };
} // Enf of namespace vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/light_graph_impl.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_GRAPH_IMPL_HH
