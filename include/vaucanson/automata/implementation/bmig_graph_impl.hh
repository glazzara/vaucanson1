// bmig_graph_impl.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HH_
# include <boost/dynamic_bitset.hpp>
# include <boost/shared_ptr.hpp>

# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/automata/implementation/bmig/vgraph_container.hh>
# include <vaucanson/automata/implementation/bmig/bmig_handlers.hh>
# include <vaucanson/automata/implementation/bmig/iterator.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/implementation/bmig/bmig_support.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/smart_label.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/misc/hash.hh>
# include <vaucanson/automata/implementation/bmig/initial_value.hh>
# include <vaucanson/automata/implementation/bmig/graphcontainer.hh>
# include <vaucanson/automata/implementation/bmig/edge_value.hh>
# include <vaucanson/automata/implementation/bmig/bmig_functors.hh>
# include <vaucanson/automata/implementation/bmig/initial_container.hh>

namespace vcsn
{
  namespace bmig
  {

    // class Graph.
    template <typename Kind, typename WordValue, typename WeightValue,
    typename SeriesValue, typename Letter, typename Tag, typename GeometryCoords>
    class Graph
    {
      public:
	/*
	** Type definitions
	*/

	// self definition.
	typedef Graph<Kind, WordValue, WeightValue,
		SeriesValue, Letter, Tag, GeometryCoords>
							self_t;

	typedef WeightValue				semiring_elt_value_t;
	typedef WordValue				monoid_elt_value_t;
	typedef WordValue				word_value_t;
	typedef SeriesValue				series_set_elt_value_t;
	typedef Letter					letter_t;
	typedef Tag					tag_t;

	typedef typename LabelOf<Kind, WordValue, WeightValue,
		SeriesValue, Letter>::ret		label_t;

	//typedef typename SmartLabelContainer<label_t>::hlabel_t
	typedef label_t
							hlabel_t;

	typedef boost::shared_ptr<std::size_t>		state_t;
	// State descriptor.
	//
	typedef handler<state_h, state_t>		hstate_t;

	typedef EdgeValue<state_t, label_t>		edge_data_t;
	//typedef EdgeValue<state_t, hlabel_t>		edge_data_t;

	typedef GraphContainer<state_t, label_t, edge_data_t>	graph_data_t;
	//typedef GraphContainer<state_t, hlabel_t, edge_data_t>	graph_data_t;

	// Transition descriptor.
	//
	// We store a pointer to an EdgeValue to avoid a new index on transitions and
	// get the data more quickly. Actually this is the adresse of an element
	// inserted in the multi_index.
	// We are allowed to do so since Boost::multi_index guaranties that the data
	// inserted will not be reallocated.
	//
	// We may need to try storing an iterator instead of a pointer. We haven't tried yet
	// since its size is higher than a simple pointer.
	typedef typename graph_data_t::iterator
							edges_iterator;
	typedef handler<transition_h, edges_iterator>	htransition_t;
	typedef htransition_t				hedge_t;

	//The graph stores  edges only, thus we can define this type.
        typedef VGraphContainer<edges_iterator, graph_data_t, htransition_t> edges_t;
	typedef std::vector<state_t>		states_data_t;
	typedef misc::Support<states_data_t>	states_t;

	//FIXME: find a better name than initial_container_t. The word initial
	//is ambiguous since we use it also for final_t
	typedef InitialValue<state_t, series_set_elt_value_t>
							  initial_value_t;
	typedef initial_value_t				  final_value_t;
	typedef InitialContainer<initial_value_t, state_t>
							  initial_container_t;

	typedef typename initial_container_t::Type	  initial_t;
	typedef initial_t				  final_t;

	typedef misc::Support<initial_container_t>	  initial_support_t;
	typedef misc::Support<initial_container_t>	  final_support_t;

	typedef GeometryCoords				  geometry_coords_t;

	typedef vcsn::geometry<hstate_t, htransition_t, GeometryCoords>
							  geometry_t;

	//Definition of various iterator types for the graph structure.
        typedef typename graph_data_t::iterator	          iterator;
	typedef typename graph_data_t::const_iterator     const_iterator;
	typedef iterator				  transition_iterator;

	typedef typename index_iterator<graph_data_t, src>::type
							  src_iterator;
	typedef src_iterator				  src_const_iterator;
	typedef typename index_iterator<graph_data_t, dst>::type
							  dst_iterator;
	typedef dst_iterator				  dst_const_iterator;
	typedef std::pair<src_iterator, src_iterator>	  src_range;
	typedef std::pair<dst_iterator, dst_iterator>	  dst_range;

// FIXME: is it useful?
//	typedef typename index_iterator<graph_data_t, pred>::type
//							  pred_iterator;
//	typedef pred_iterator				  pred_const_iterator;
//	typedef std::pair<pred_iterator, pred_iterator>	  pred_range;
	typedef typename index_iterator<graph_data_t, succ>::type
							  succ_iterator;
	typedef succ_iterator				  succ_const_iterator;
	typedef std::pair<succ_iterator, succ_iterator>	  succ_range;

	typedef ::vcsn::bmig::DeltaConstIterator<self_t, hstate_t, src_iterator>
							  delta_state_iterator;
	typedef ::vcsn::bmig::DeltaConstIterator<self_t, htransition_t, src_iterator>
							  delta_transition_iterator;
	typedef ::vcsn::bmig::DeltaConstIterator<self_t, hstate_t, dst_iterator>
							  rdelta_state_iterator;
	typedef ::vcsn::bmig::DeltaConstIterator<self_t, htransition_t, dst_iterator>
							  rdelta_transition_iterator;

	Graph ();
	Graph (unsigned int reserve_number_of_state,
	       unsigned int reserve_number_edge);
	Graph (const self_t&);
	~Graph ();

	self_t& operator= (const self_t&);

	// FIXME: add const rettype& versions?

	states_t	  states () const;
	edges_t		  edges () const;
	initial_support_t initial () const;
	final_support_t	  final () const;

	// state manipulations
	bool		  has_state (const hstate_t& h) const;
	hstate_t	  add_state ();
	hstate_t	  get_state (unsigned h) const;
	void		  del_state (const hstate_t& h);

	void		  set_initial(const hstate_t& s,
				      const series_set_elt_value_t& v,
				      const series_set_elt_value_t& z);
	const series_set_elt_value_t&
			  get_initial(const hstate_t&,
				      const series_set_elt_value_t&) const;
	bool		  is_initial(const hstate_t& s,
				     const series_set_elt_value_t&) const;
	void		  clear_initial();

	void		  set_final(const hstate_t&,
				    const series_set_elt_value_t&,
				    const series_set_elt_value_t&);
	const series_set_elt_value_t&
			  get_final(const hstate_t&,
				    const series_set_elt_value_t&) const;
	bool		  is_final(const hstate_t& s,
				   const series_set_elt_value_t&) const;
	void		  clear_final();


	// edge manipulations
	bool		  has_edge (const hedge_t& h) const;
	hedge_t		  add_edge (const hstate_t& from,
				    const hstate_t& to,
				    const label_t& l);
	void		  del_edge (const hedge_t& h);

	hstate_t	  src_of (const hedge_t& h) const;
	hstate_t	  dst_of (const hedge_t& h) const;

	const label_t&	  label_of (const hedge_t& h) const;
	void		  update(const hedge_t& h, const label_t& l);

	// check the consistency of an automata
	template <class S>
	bool		  exists (const AutomataBase<S>& s) const;

	self_t&		  clone () const; // TODO

	tag_t&		  tag ();
	const tag_t&	  tag () const;
	geometry_t&	  geometry ();
	const geometry_t& geometry () const;

	// Helper used in deltai.
	// Gives the htransition held by a boost iterator.
	// Avoid the burden of carrying a reference to the main hash table
	// when we are working on a sub-hash. (this is related to the projection).
	template <typename I>
	htransition_t	  get_htransition(const I& i) const;

      /*
      ** delta...
      ** FIXME: nice comments
      */
# define DECLARE_DELTAC_FUNCTION(FunName, DeltaKind)			\
	template <typename Container, typename Query>			\
	void FunName (Container& res, const hstate_t& from,		\
	              const Query& q, ::vcsn::delta_kind::DeltaKind) const
	DECLARE_DELTAC_FUNCTION (deltac, states);
	DECLARE_DELTAC_FUNCTION (deltac, transitions);
	DECLARE_DELTAC_FUNCTION (rdeltac, states);
	DECLARE_DELTAC_FUNCTION (rdeltac, transitions);
# undef DECLARE_DELTAC_FUNCTION

	// Retrieve the (src|dst)_range from a given state
	// Used by the delta iterators
# define DECLARE_DELTAI_FUNCTION(DeltaKind)					\
	std::pair<DeltaKind##_iterator, DeltaKind##_iterator>			\
	deltai(const hstate_t& s, DeltaKind##_iterator) const
	DECLARE_DELTAI_FUNCTION(src);
	DECLARE_DELTAI_FUNCTION(dst);
# undef DECLARE_DELTAI_FUNCTION

      private:
	typename graph_data_t::const_iterator
			  find_edge(const state_t&,
				    const state_t&,
				    const hlabel_t&) const;

	geometry_t	  geometry_;
	graph_data_t	  graph_;
	tag_t		  tag_;
	final_t		  final_;
	initial_t	  initial_;

	//NEW ATTRIBUTES
	boost::dynamic_bitset<>  initial_bitset_;
	boost::dynamic_bitset<>  final_bitset_;
	unsigned	  number_of_epsilon_;

	// number_of_state_ == 0 => there is no state.
	unsigned	  number_of_state_;
	states_data_t	  states_;

	SmartLabelContainer<label_t>
			  label_container_;

    }; // End of class Graph

    // FIXME: add some nice comments

# define BMIGRAPH_TPARAM						      \
    template <class S, class WordValue, class WeightValue, class SeriesValue, \
	      class Letter, class Tag, class GeometryCoords>

# define BMIGRAPH_SERIES					  \
    Graph<labels_are_series, WordValue, WeightValue, SeriesValue, \
	  Letter, Tag, GeometryCoords>

    BMIGRAPH_TPARAM
    ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(BMIGRAPH_SERIES);

    BMIGRAPH_TPARAM
    ADAPT_LETTER_OF_TO_SERIES_LABEL(BMIGRAPH_SERIES);

    BMIGRAPH_TPARAM
    ADAPT_WORD_OF_TO_SERIES_LABEL(BMIGRAPH_SERIES);

# undef BMIGRAPH_SERIES
# define BMIGRAPH_LETTERS                                       \
  Graph<labels_are_letters, WordValue, WeightValue, SeriesValue,\
        Letter, Tag, GeometryCoords>

    BMIGRAPH_TPARAM
    ADAPT_WORD_OF_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

    BMIGRAPH_TPARAM
    ADAPT_SERIE_OF_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

    BMIGRAPH_TPARAM
    ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

# undef BMIGRAPH_LETTERS

# define BMIGRAPH						\
    Graph<Kind, WordValue, WeightValue, SerieValue, \
	  Letter, Tag, GeometryCoords>

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    Tag& op_tag(const AutomataBase<I>&, BMIGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const Tag& op_tag(const AutomataBase<I>&, BMIGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, BMIGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, const BMIGRAPH&);

# undef BMIGRAPH
# undef BMIGRAPH_TPARAM

  } // End of namespace bmig

  // This implementation can be used as an implementation of automaton.
  VCSN_MAKE_AUTOMATON_TRAITS(bmig::Graph);
  VCSN_MAKE_GENERALIZED_AUTOMATON_TRAITS(bmig::Graph);
  VCSN_MAKE_MUTE_GRAPH_IMPL_TRAITS(bmig::Graph);
  VCSN_MAKE_MUTE_GRAPH_IMPL_MONOID_TRAITS(bmig::Graph);

  // This implementation can be used as a transducer one.
  template <class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct transducer_traits<bmig::Graph<Kind,
                                  WordValue,
                                  WeightValue,
                                  SeriesValue,
                                  Letter,
                                  Tag,
                                  GeometryCoords> >
  {
    typedef WordValue		    input_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::monoid_elt_value_t
                                  output_monoid_elt_value_t;
    typedef typename algebra::series_traits<WeightValue>::semiring_elt_value_t
                                  output_semiring_elt_value_t;
  };

  // Explain how to project type of transducer into input automaton type.
  template <class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct input_projection_traits<bmig::Graph<Kind,
					     WordValue,
					     WeightValue,
					     SeriesValue,
					     Letter,
					     Tag,
					     GeometryCoords> >
  {
    typedef bmig::Graph<Kind, WordValue, WeightValue, SeriesValue,
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
    bmig::Graph<Kind,
          monoid_elt_value_t,
          semiring_elt_value_t,
          series_set_elt_value_t,
          Letter,
          Tag,
          GeometryCoords>
                                  ret;
  };

  // Input projection for FMP transducers.
  template <class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct fmp_input_projection_traits<bmig::Graph<Kind,
						 WordValue,
						 WeightValue,
						 SeriesValue,
						 Letter,
						 Tag,
						 GeometryCoords> >
  {
    typedef bmig::Graph<Kind, WordValue, WeightValue, SeriesValue,
                         Letter, Tag, GeometryCoords>
                                  self_t;

    typedef typename automaton_traits<self_t>::semiring_elt_value_t
                                  semiring_elt_value_t;

    typedef typename WordValue::first_type monoid_elt_value_t;
    typedef typename monoid_elt_value_t::value_type letter_t;

    typedef typename algebra::mute_series_impl<SeriesValue,
                                               semiring_elt_value_t,
					       monoid_elt_value_t>::ret
				  series_set_elt_value_t;

    typedef
    bmig::Graph<Kind,
          monoid_elt_value_t,
          semiring_elt_value_t,
          series_set_elt_value_t,
          letter_t,
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
  struct output_projection_traits<bmig::Graph<Kind,
                                        WordValue,
                                        WeightValue,
                                        SeriesValue,
                                        Letter,
                                        Tag,
                                        GeometryCoords> >
  {
    typedef bmig::Graph<Kind, WordValue, WeightValue, SeriesValue,
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
    bmig::Graph<Kind,
          monoid_elt_value_t,
          semiring_elt_value_t,
          series_set_elt_value_t,
          Letter,
          Tag,
          GeometryCoords>
                                  ret;
  };

  // Output projection for FMP transducers.
  template <class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct fmp_output_projection_traits<bmig::Graph<Kind,
                                        WordValue,
                                        WeightValue,
                                        SeriesValue,
                                        Letter,
                                        Tag,
                                        GeometryCoords> >
  {
    typedef bmig::Graph<Kind, WordValue, WeightValue, SeriesValue,
                         Letter, Tag, GeometryCoords>
                                  self_t;

    typedef typename WordValue::second_type monoid_elt_value_t;
    typedef typename monoid_elt_value_t::value_type letter_t;

    typedef typename automaton_traits<self_t>::semiring_elt_value_t
                                  semiring_elt_value_t;

    typedef typename algebra::mute_series_impl<SeriesValue,
	    semiring_elt_value_t,
	    monoid_elt_value_t>::ret series_set_elt_value_t;

    typedef
    bmig::Graph<Kind,
          monoid_elt_value_t,
          semiring_elt_value_t,
          series_set_elt_value_t,
          letter_t,
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
  struct extension_traits<bmig::Graph<Kind,
                                WordValue,
                                WeightValue,
                                SeriesValue,
                                Letter,
                                Tag,
                                GeometryCoords> >
  {
    typedef bmig::Graph<Kind, WordValue, WeightValue,
                         SeriesValue, Letter, Tag, GeometryCoords>
                                  self_t;
    typedef typename automaton_traits<self_t>::monoid_elt_value_t
                                  monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
                                                SeriesValue,
                                                monoid_elt_value_t>::ret
                                  series_set_elt_value_t;

    typedef
    bmig::Graph<Kind,
          monoid_elt_value_t,
          SeriesValue,
          series_set_elt_value_t,
          Letter,
          Tag,
          GeometryCoords>
                                  ret;
  };
} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/bmig_graph_impl.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

// FIXME __ITERATOR__  put back again later
//# include <vaucanson/automata/implementation/bmig_graph_letters_spec.hh>

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_IMPL_HH_ //

