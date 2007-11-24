// boostg_graph_impl.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_IMPL_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_IMPL_HH_
# include <boost/dynamic_bitset.hpp>
# include <boost/multi_index_container.hpp>
# include <boost/multi_index/member.hpp>
# include <boost/multi_index/ordered_index.hpp>
# include <boost/multi_index/hashed_index.hpp>
# include <boost/functional/hash/hash.hpp>
# include <boost/multi_index/sequenced_index.hpp>
# include <boost/tuple/tuple.hpp>
# include <boost/multi_index/composite_key.hpp>

# include <vaucanson/automata/implementation/boostg/boostg_handlers.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/implementation/boostg/boostg_support.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/smart_label.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/misc/hash.hh>
# include <vaucanson/automata/implementation/boostg/initial_value.hh>
# include <vaucanson/automata/implementation/boostg/graphcontainer.hh>
# include <vaucanson/automata/implementation/boostg/edge_value.hh>
# include <vaucanson/automata/implementation/boostg/boostg_functors.hh>
# include <vaucanson/automata/implementation/boostg/initial_container.hh>

using ::boost::multi_index_container;
using ::boost::multi_index::hashed_non_unique;
using ::boost::multi_index::indexed_by;
using ::boost::multi_index::composite_key;
using ::boost::multi_index::hashed_non_unique;
using ::boost::multi_index::tag;
using ::boost::multi_index::member;
using ::boost::multi_index::index_iterator;
using ::boost::multi_index::get;
using ::boost::multi_index::project;
using ::boost::multi_index::composite_key_hash;
using ::boost::dynamic_bitset;

namespace vcsn
{
  namespace boostg
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

	typedef typename SmartLabelContainer<label_t>::hlabel_t
							hlabel_t;

	// State descriptor.
	//
	typedef handler<state_h, unsigned*>		hstate_t;

	typedef EdgeValue<hstate_t, hlabel_t>		edge_data_t;

	typedef GraphContainer<hstate_t, hlabel_t, edge_data_t>	graph_data_t;
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
	typedef typename GraphContainer<hstate_t, hlabel_t, edge_data_t>::iterator
							edges_iterator;
	typedef handler<transition_h, edges_iterator>	htransition_t;
	typedef htransition_t				hedge_t;

	class VGraphContainerIterator
	{
	  public:
	    typedef edges_iterator	iterator;
	    VGraphContainerIterator(const graph_data_t& c, edges_iterator i);
	    htransition_t operator*() const;

	    bool operator==(const VGraphContainerIterator& v) const;
	    bool operator!=(const VGraphContainerIterator& v) const;
	    VGraphContainerIterator& operator++();
	    VGraphContainerIterator operator++(int);

	  private:
	    iterator it_;
	    iterator next_;
	    const graph_data_t& container_;
	};

	class VGraphContainer
	{
	  public:
	    typedef VGraphContainerIterator iterator;
	    typedef iterator		    const_iterator;

	    VGraphContainer(const graph_data_t& g);

	    iterator begin() const;
	    iterator end() const;

	    size_t size() const;

	  private:
	    const graph_data_t& graph_;
	};

	//The graph stores  edges only, thus we can define this type.
	typedef VGraphContainer			edges_t;
	typedef std::vector<hstate_t>		states_data_t;
	typedef misc::Support<states_data_t>	states_t;

	//FIXME: find a better name than initial_container_t. The word initial
	//is ambiguous since we use it also for final_t
	typedef InitialValue<hstate_t, series_set_elt_value_t>
							  initial_value_t;
	typedef initial_value_t				  final_value_t;
	typedef InitialContainer<initial_value_t, hstate_t>
							  initial_container_t;

	typedef typename initial_container_t::Type	  initial_t;
	typedef initial_t				  final_t;

	typedef misc::Support<initial_container_t>	  initial_support_t;
	typedef misc::Support<initial_container_t>	  final_support_t;

	typedef GeometryCoords				  geometry_coords_t;

	typedef geometry<hstate_t, htransition_t, GeometryCoords>
							  geometry_t;

	//Definition of various iterator types for the graph structure.
	typedef typename VGraphContainer::iterator	  iterator;
	typedef typename VGraphContainer::const_iterator  const_iterator;
	typedef iterator				  transition_iterator;

	typedef typename index_iterator<graph_data_t, src>::type
							  src_iterator;
	typedef src_iterator				  src_const_iterator;
	typedef typename index_iterator<graph_data_t, dst>::type
							  dst_iterator;
	typedef dst_iterator				  dst_const_iterator;
	typedef typename index_iterator<graph_data_t, pred>::type
							  pred_iterator;
	typedef pred_iterator				  pred_const_iterator;
	typedef typename index_iterator<graph_data_t, succ>::type
							  succ_iterator;
	typedef succ_iterator				  succ_const_iterator;
	typedef std::pair<src_iterator, src_iterator>	  src_range;
	typedef std::pair<dst_iterator, dst_iterator>	  dst_range;
	typedef std::pair<pred_iterator, pred_iterator>	  pred_range;
	typedef std::pair<succ_iterator, succ_iterator>	  succ_range;


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

      /*
      ** delta...
      ** FIXME: nice comments
      */
# define DECLARE_DELTA_FUNCTION(FunName, DeltaKind)			\
	template <typename OutputIterator, typename Query>		\
	void FunName (OutputIterator res, const hstate_t& from,		\
	              const Query& q, ::vcsn::delta_kind::DeltaKind) const
	DECLARE_DELTA_FUNCTION (delta, states);
	DECLARE_DELTA_FUNCTION (delta, transitions);
	DECLARE_DELTA_FUNCTION (rdelta, states);
	DECLARE_DELTA_FUNCTION (rdelta, transitions);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION(FunName, DeltaKind, IsBool)	\
	template <typename Functor, typename Query>			\
	void FunName (Functor& f, const hstate_t& from, const Query& q,	\
                      ::vcsn::delta_kind::DeltaKind, misc::IsBool ## _t) const
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (deltaf, transitions, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, false);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, true);
	DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, transitions, false);
# undef DECLARE_DELTAF_BOOL_FUNCTION

# define DECLARE_DELTAF_FUNCTION(FunName)				\
	template <typename Functor, typename Query, typename DeltaKind>	\
	void FunName (Functor& f, const hstate_t& from,			\
	              const Query& q, ::vcsn::delta_kind::kind<DeltaKind>) const
	DECLARE_DELTAF_FUNCTION (deltaf);
	DECLARE_DELTAF_FUNCTION (rdeltaf);
# undef DECLARE_DELTAF_FUNCTION


      private:
	typename graph_data_t::const_iterator
			  find_edge(const hstate_t&,
				    const hstate_t&,
				    const hlabel_t&) const;

	geometry_t	  geometry_;
	graph_data_t	  graph_;
	tag_t		  tag_;
	final_t		  final_;
	initial_t	  initial_;

	//NEW ATTRIBUTES
	dynamic_bitset<>  initial_bitset_;
	dynamic_bitset<>  final_bitset_;
	unsigned	  number_of_epsilon_;

	// number_of_state_ == 0 => there is no state.
	unsigned	  number_of_state_;
	states_data_t	  states_;

	SmartLabelContainer<label_t>
			  label_container_;

    }; // End of class Graph

    // FIXME: add some nice comments

# define BOOSTGRAPH_TPARAM						      \
    template <class S, class WordValue, class WeightValue, class SeriesValue, \
	      class Letter, class Tag, class GeometryCoords>

# define BOOSTGRAPH_SERIES					  \
    Graph<labels_are_series, WordValue, WeightValue, SeriesValue, \
	  Letter, Tag, GeometryCoords>

    BOOSTGRAPH_TPARAM
    ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(BOOSTGRAPH_SERIES);

    BOOSTGRAPH_TPARAM
    ADAPT_LETTER_OF_TO_SERIES_LABEL(BOOSTGRAPH_SERIES);

    BOOSTGRAPH_TPARAM
    ADAPT_WORD_OF_TO_SERIES_LABEL(BOOSTGRAPH_SERIES);

# undef BOOSTGRAPH_SERIES
# define BOOSTGRAPH_LETTERS					  \
    Graph<labels_are_letters, WordValue, WeightValue, SeriesValue,\
	  Letter, Tag, GeometryCoords>

    BOOSTGRAPH_TPARAM
    ADAPT_WORD_OF_TO_LETTERS_LABEL(BOOSTGRAPH_LETTERS);

    BOOSTGRAPH_TPARAM
    ADAPT_SERIE_OF_TO_LETTERS_LABEL(BOOSTGRAPH_LETTERS);

    BOOSTGRAPH_TPARAM
    ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(BOOSTGRAPH_LETTERS);

# undef BOOSTGRAPH
# define BOOSTGRAPH						\
    Graph<Kind, WordValue, WeightValue, SerieValue, \
	  Letter, Tag, GeometryCoords>

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    Tag& op_tag(const AutomataBase<I>&, BOOSTGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const Tag& op_tag(const AutomataBase<I>&, BOOSTGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    typename BOOSTGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, BOOSTGRAPH&);

    template <class Kind, class WordValue, class WeightValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const typename BOOSTGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, const BOOSTGRAPH&);

# undef BOOSTGRAPH
# undef BOOSTGRAPH_TPARAM

  } // End of namespace boostg

  // This implementation can be used as an implementation of automaton.
  VCSN_MAKE_AUTOMATON_TRAITS(boostg::Graph);

  // This implementation can be used as a transducer one.
  template <class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct transducer_traits<boostg::Graph<Kind,
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
  template <class S,
            class Kind,
            class WordValue,
            class WeightValue,
            class SeriesValue,
            class Letter,
            class Tag,
            class GeometryCoords>
  struct projection_traits<S, boostg::Graph<Kind,
                                    WordValue,
                                    WeightValue,
                                    SeriesValue,
                                    Letter,
                                    Tag,
                                    GeometryCoords> >
  {
    typedef boostg::Graph<Kind, WordValue, WeightValue, SeriesValue,
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
    boostg::Graph<Kind,
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
  struct output_projection_traits<boostg::Graph<Kind,
                                        WordValue,
                                        WeightValue,
                                        SeriesValue,
                                        Letter,
                                        Tag,
                                        GeometryCoords> >
  {
    typedef boostg::Graph<Kind, WordValue, WeightValue, SeriesValue,
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
    boostg::Graph<Kind,
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
  struct extension_traits<boostg::Graph<Kind,
                                WordValue,
                                WeightValue,
                                SeriesValue,
                                Letter,
                                Tag,
                                GeometryCoords> >
  {
    typedef boostg::Graph<Kind, WordValue, WeightValue,
                         SeriesValue, Letter, Tag, GeometryCoords>
                                  self_t;
    typedef typename automaton_traits<self_t>::monoid_elt_value_t
                                  monoid_elt_value_t;
    typedef typename algebra::mute_series_impl<SeriesValue,
                                                SeriesValue,
                                                monoid_elt_value_t>::ret
                                  series_set_elt_value_t;

    typedef
    boostg::Graph<Kind,
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
#  include <vaucanson/automata/implementation/boostg_graph_impl.hxx>
#  include <vaucanson/automata/implementation/boostg/vgraph_container.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_GRAPH_IMPL_HH_ //

