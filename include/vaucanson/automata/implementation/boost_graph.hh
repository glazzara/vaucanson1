// boost_graph.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HH_

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/smart_label.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>
# include <vaucanson/automata/concept/tags.hh>

//NEW INCLUDES
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vaucanson/misc/counter_support.hh>
#include <functional>

// FIXME: how to handle htransition_t?
// FIXME: do we have enough to handle it?

// FIXME: remove
using namespace vcsn::misc;

namespace vcsn
{
  // FIXME: add comments?
  typedef htransition_t hedge_t;
  namespace delta_kind
  {
    typedef transitions edges;
  } // End of namespace delta_kind

  // FIXME: full public or {access,gett}ors
  // Edge decorator
/*
  struct GenEdgeLabel
  { };
  template <typename Label>
  struct EdgeLabel : public GenEdgeLabel,
    public SmartLabelContainer<Label>::hlabel_t
  { };
*/

  template <typename Label>
  struct EdgeValue : public GenEdgeValue
  {
    typedef typename SmartLabelContainer<Label>::hlabel_t hlabel_t;
    EdgeValue (hstate_t from, hstate_t to, hlabel_t l);

    hlabel_t label_;
    hstate_t from_;
    hstate_t to_;
  }; // End of class EdgeValue

  struct succ {};
  struct pred {};
  struct src {};
  struct dst {};

  // FIXME use VCSN_BMI and remove those using
# define VCSN_BMI(Type) ::boost::multi_index::Type
  using ::boost::multi_index_container;
  using ::boost::multi_index::hashed_non_unique;
  using ::boost::multi_index::indexed_by;
  using ::boost::multi_index::composite_key;
  using ::boost::multi_index::hashed_non_unique;
  using ::boost::multi_index::tag;
  using ::boost::multi_index::member;
  using ::boost::dynamic_bitset;

  template <typename Label>
  struct SuccessorKey : composite_key <
    EdgeValue<Label>,
    BOOST_MULTI_INDEX_MEMBER(EdgeValue<Label>, hstate_t, from_),
    BOOST_MULTI_INDEX_MEMBER(EdgeValue<Label>, typename EdgeValue<Label>::hlabel_t, label_)
  > {};

  template <typename Label>
  struct PredecessorKey : composite_key <
    EdgeValue<Label>,
    BOOST_MULTI_INDEX_MEMBER(EdgeValue<Label>, hstate_t, from_),
    BOOST_MULTI_INDEX_MEMBER(EdgeValue<Label>, typename EdgeValue<Label>::hlabel_t, label_)
  > {};

  template <typename Label>
  struct SourceKey : BOOST_MULTI_INDEX_MEMBER (
    EdgeValue<Label>, hstate_t, from_
  ) {};

  template <typename Label>
  struct DestinationKey : BOOST_MULTI_INDEX_MEMBER (
    EdgeValue<Label>, hstate_t, to_
  ) {};

  template <typename Label>
  struct SourceAndLabel : hashed_non_unique <
    tag<succ>,
    SuccessorKey<Label>
  > {};

  template <typename Label>
  struct DestinationAndLabel : hashed_non_unique <
    tag<pred>,
    PredecessorKey<Label>
  > {};

  template <typename Label>
  struct Source : hashed_non_unique <
    tag<src>,
    SourceKey<Label>
  > {};

  template <typename Label>
  struct Destination : hashed_non_unique <
    tag<dst>,
    DestinationKey<Label>
  > {};

  template <typename Label>
  struct GraphContainer
  : public multi_index_container
  <
    EdgeValue<Label>,
    indexed_by
    <
      SourceAndLabel<Label>,
      DestinationAndLabel<Label>,
      Source<Label>,
      Destination<Label>
    >
  >
  { };

  template <typename S>
  struct InitialValue
  {
    InitialValue(const hstate_t& state, const S& series)
      : first(state),
    second(series) {}

    hstate_t first; // state
    S second; // series
  };

  template <typename Label>
  struct VGraphContainerIterator : GraphContainer<Label>::iterator
  {
    VGraphContainerIterator(const typename GraphContainer<Label>::iterator& i) : GraphContainer<Label>::iterator(i) {}
    htransition_t operator*()
    {
      // FIXME: remove this const_cast
      return htransition_t(const_cast<EdgeValue<Label>*>(&(GraphContainer<Label>::iterator::operator*())));
    }
  };

  template <typename Label>
  struct VGraphContainer : GraphContainer<Label>
  {
    typedef VGraphContainerIterator<Label> iterator;

    VGraphContainer() {}
    //VGraphContainer(const VGraphContainer&c) : GraphContainer(c) {}

    iterator begin() { return VGraphContainerIterator<Label>(GraphContainer<Label>::begin()); }
    iterator end() { return VGraphContainerIterator<Label>(GraphContainer<Label>::end()); }
  };

  // class Graph.
  template <typename Kind, typename WordValue, typename WeightValue,
	    typename SeriesValue, typename Letter, typename Tag, typename Geometry>
  class Graph
  {
    public:
      /*
      ** Type definitions
      */

      // self definition.
      typedef Graph<Kind, WordValue, WeightValue,
			 SeriesValue, Letter, Tag, Geometry> self_t;

      typedef typename LabelOf<Kind, WordValue, WeightValue,
			       SeriesValue, Letter>::ret label_t;

      typedef typename SmartLabelContainer<label_t>::hlabel_t hlabel_t;

//      typedef StateValue state_value_t;
      typedef EdgeValue<label_t> edge_value_t;
      typedef SeriesValue series_set_elt_value_t;

//      typedef /* FIXME: std::vector<StateValue_t> */ state_data_t;
//      typedef /* FIXME: std::vector<EdgeValue_t> */ edge_data_t;

//      typedef /* FIXME: StateContainer */ states_t;
      typedef VGraphContainer<label_t> graph_data_t;
      //The graph stores  edges only, thus we can define this type.
      typedef graph_data_t edges_t;
      typedef CounterSupport states_t;

      //FIXME: find a better name than initial_container_t. The word initial
      //is ambiguous since we use it also for final_t
      typedef misc::InitialContainer<InitialValue<series_set_elt_value_t>, hstate_t>
	initial_container_t;
      typedef typename initial_container_t::Type initial_t;
      typedef initial_t final_t;

      typedef misc::Support<initial_container_t>	initial_support_t;
      typedef misc::Support<initial_container_t>	final_support_t;

      typedef Tag tag_t;
      typedef Geometry geometry_t;


      Graph ();
      Graph (unsigned int initial_number_of_state,
		  unsigned int number_of_edge_initially_allocated);

      // FIXME: add const rettype& versions?

      states_t states () const; // TODO
      edges_t edges () const; // TODO
      initial_support_t initial () const; // TODO
      final_support_t final () const; // TODO

      // state manipulations
      bool has_state (hstate_t h) const; // TODO
      hstate_t add_state ();
      hstate_t del_state (hstate_t h); // TODO

      void set_initial(hstate_t s,
		       const series_set_elt_value_t& v,
		       const series_set_elt_value_t& z);
      const series_set_elt_value_t&
      get_initial(hstate_t, const series_set_elt_value_t&) const;
      void clear_initial();

      void set_final(hstate_t,
		     const series_set_elt_value_t&,
		     const series_set_elt_value_t&);
      const series_set_elt_value_t&
      get_final(hstate_t, const series_set_elt_value_t&) const;
      void clear_final();

      bool is_final(hstate_t s) const;
      bool is_initial(hstate_t s) const;

      // edge manipulations
      bool has_edge (hedge_t h) const; // TODO
      hedge_t add_edge (hstate_t from, hstate_t to, const label_t& l); // TODO
      hedge_t del_edge (hedge_t h); // TODO

      hstate_t src_of (hedge_t h) const; // TODO
      hstate_t dst_of (hedge_t h) const; // TODO

      const label_t& label_of (hedge_t h) const; // TODO
      void update(hedge_t h, const label_t& l); // TODO

      // check the consistency of an automata
      template <class S>
      bool exists (const AutomataBase<S>& s) const; // TODO

      self_t& clone () const; // TODO

      tag_t& tag (); // TODO
      const tag_t& tag () const; // TODO
      geometry_t geometry (); // TODO
      const geometry_t geometry () const; // TODO

      /*
      ** delta...
      ** FIXME: nice comments
      ** TODO: implementation
      */
# define DECLARE_DELTA_FUNCTION(FunName, DeltaKind)			\
      template <typename OutputIterator, typename Query>		\
      void FunName (OutputIterator res, hstate_t from,			\
		    const Query& q, delta_kind::DeltaKind) const
      DECLARE_DELTA_FUNCTION (delta, states);
      DECLARE_DELTA_FUNCTION (delta, edges);
      DECLARE_DELTA_FUNCTION (rdelta, states);
      DECLARE_DELTA_FUNCTION (rdelta, edges);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION(FunName, DeltaKind, IsBool)	\
      template <typename Functor, typename Query>			\
      void FunName (Functor& f, hstate_t from, const Query& q,		\
		    delta_kind::DeltaKind, misc::IsBool ## _t) const
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, true);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, states, false);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, edges, true);
      DECLARE_DELTAF_BOOL_FUNCTION (deltaf, edges, false);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, true);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, states, false);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, edges, true);
      DECLARE_DELTAF_BOOL_FUNCTION (rdeltaf, edges, false);
# undef DECLARE_DELTAF_BOOL_FUNCTION

# define DECLARE_DELTAF_FUNCTION(FunName)				\
      template <typename Functor, typename Query, typename DeltaKind>	\
      void FunName (Functor& f, hstate_t from,				\
		    const Query& q, delta_kind::kind<DeltaKind>) const
      DECLARE_DELTAF_FUNCTION (deltaf);
      DECLARE_DELTAF_FUNCTION (rdeltaf);
# undef DECLARE_DELTAF_FUNCTION


    private:
      geometry_t geometry_;
      graph_data_t graph_;
//      state_data_t states_;
//      /* FIXME */ removed_states_;
//      /* FIXME */ removed_edges_;
      tag_t tag_;
      final_t final_;
      initial_t initial_;

      //NEW ATTRIBUTES
      dynamic_bitset<> initial_bitset_;
      dynamic_bitset<> final_bitset_;
      unsigned  number_of_epsilon_;
//      alphabet_t    alpha_;
      // FIXME: starting from 0??
      // FIXME: specify its range
      // number_of_state_ == 0 => there is no state.
      unsigned  number_of_state_;

      SmartLabelContainer<label_t> label_container_;

  }; // End of class Graph

  // FIXME: add some nice comments

# define BOOSTGRAPH_TPARAM								\
  template <class S, class WordValue, class WeightValue, class SeriesValue, \
	    class Letter, class Tag, class Geometry>

  BOOSTGRAPH_TPARAM
  ADAPT_ADD_LETTER_TRANSITION_TO_SERIES_LABEL(Graph<labels_are_series,
					      WordValue, WeightValue,
					      SeriesValue, Letter, Tag, Geometry>);


  BOOSTGRAPH_TPARAM
  ADAPT_LETTER_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag, Geometry>);

  BOOSTGRAPH_TPARAM
  ADAPT_WORD_OF_TO_SERIES_LABEL(Graph<labels_are_series,
				WordValue, WeightValue,
				SeriesValue, Letter, Tag, Geometry>);

  BOOSTGRAPH_TPARAM
  ADAPT_WORD_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				 WordValue, WeightValue,
				 SeriesValue, Letter, Tag, Geometry>);

  BOOSTGRAPH_TPARAM
  ADAPT_SERIE_OF_TO_LETTERS_LABEL(Graph<labels_are_letters,
				  WordValue, WeightValue,
				  SeriesValue, Letter, Tag, Geometry>);

  BOOSTGRAPH_TPARAM
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



# undef BOOSTGRAPH_TPARAM

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

      typedef VGraphContainer<label_t>			transitions_t;
      typedef CounterSupport				states_t;

      typedef typename states_t::iterator		state_iterator;
      typedef typename transitions_t::iterator		transition_iterator;

      typedef misc::InitialContainer<InitialValue<series_set_elt_value_t>, hstate_t>
	initial_container_t;
      typedef typename initial_container_t::Type initial_t;
      typedef initial_t final_t;

      typedef misc::Support<initial_container_t>	initial_support_t;
      typedef misc::Support<initial_container_t>	final_support_t;

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


} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/boost_graph.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

# undef BOOST_BMI

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HH_ //

