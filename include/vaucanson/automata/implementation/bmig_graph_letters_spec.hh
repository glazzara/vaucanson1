// bmig_graph_letters_spec.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_LETTERS_SPEC_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_LETTERS_SPEC_HH_

# include <set>
# include <vaucanson/automata/implementation/bmig_graph_impl.hh>

namespace vcsn
{
  namespace bmig
  {

    // class Graph.
    template <typename WordValue,
    typename SeriesValue, typename Letter, typename Tag, typename GeometryCoords>
    class Graph<labels_are_letters, WordValue, bool, SeriesValue, Letter,
		Tag, GeometryCoords>
    {
      public:
	/*
	** Type definitions
	*/

	// self definition.
	typedef Graph<labels_are_letters, WordValue, bool,
		SeriesValue, Letter, Tag, GeometryCoords>
							self_t;

        typedef bool				        semiring_elt_value_t;
	typedef WordValue				monoid_elt_value_t;
	typedef WordValue				word_value_t;
	typedef SeriesValue				series_set_elt_value_t;
	typedef Letter					letter_t;
	typedef Tag					tag_t;

	typedef typename LabelOf<labels_are_letters, WordValue, bool,
		SeriesValue, Letter>::ret		label_t;

	typedef boost::shared_ptr<std::size_t>		state_t;
	// State descriptor.
	//
	typedef handler<state_h, state_t>		hstate_t;

	typedef EdgeValue<state_t, label_t>		edge_data_t;

	typedef GraphContainer<state_t, label_t, edge_data_t>	graph_data_t;

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
        typedef typename graph_data_t::iterator         edges_iterator;
	typedef handler<transition_h, edges_iterator>	htransition_t;
	typedef htransition_t				hedge_t;

        typedef VGraphContainer<edges_iterator, graph_data_t, htransition_t> edges_t;
	typedef std::vector<state_t>		          states_data_t;
        typedef misc::Support<states_data_t>	          states_t;

	typedef std::set<state_t>                        initial_t;
        typedef std::set<state_t>                        final_t;

	typedef misc::Support<initial_t>		  initial_support_t;
	typedef misc::Support<final_t>			  final_support_t;

	typedef GeometryCoords				  geometry_coords_t;

	typedef geometry<hstate_t, htransition_t, GeometryCoords>
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


      /// Delta, Reverse deltas, for functor and iterator.
# define DECLARE_DELTA_FUNCTION(FunName, DeltaKind)			\
	template <typename OutputIterator, typename Query>		\
	void FunName (OutputIterator res, const hstate_t& from,		\
	              const Query& q, ::vcsn::delta_kind::DeltaKind) const
	DECLARE_DELTA_FUNCTION (delta, states);
	DECLARE_DELTA_FUNCTION (delta, transitions);
	DECLARE_DELTA_FUNCTION (rdelta, states);
	DECLARE_DELTA_FUNCTION (rdelta, transitions);
# undef DECLARE_DELTA_FUNCTION


      private:
	typename graph_data_t::const_iterator
			  find_edge(const state_t&,
				    const state_t&,
				    const label_t&) const;

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

    }; // End of class Graph


# define BMIGRAPH_TPARAM				    \
    template <class S, class WordValue, class SeriesValue,  \
	      class Letter, class Tag, class GeometryCoords>

# define BMIGRAPH_LETTERS					   \
    Graph<labels_are_letters, WordValue, bool, SeriesValue,	   \
    	  Letter, Tag, GeometryCoords>

    BMIGRAPH_TPARAM
    ADAPT_WORD_OF_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

    BMIGRAPH_TPARAM
    ADAPT_SERIE_OF_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

    BMIGRAPH_TPARAM
    ADAPT_ADD_SERIE_TRANSITION_TO_LETTERS_LABEL(BMIGRAPH_LETTERS);

# define BMIGRAPH						  \
    Graph<labels_are_letters, WordValue, bool, SerieValue,	  \
	  Letter, Tag, GeometryCoords>

    template <class WordValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    Tag& op_tag(const AutomataBase<I>&, BMIGRAPH&);

    template <class WordValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const Tag& op_tag(const AutomataBase<I>&, BMIGRAPH&);

    template <class WordValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, BMIGRAPH&);

    template <class WordValue, class SerieValue,
	      class Letter, class Tag, class GeometryCoords, class I>
    const typename BMIGRAPH::geometry_t&
    op_geometry(const AutomataBase<I>&, const BMIGRAPH&);

# undef BMIGRAPH
# undef BMIGRAPH_TPARAM

  } // End of namespace bmig

  // This implementation can be used as an implementation of automaton.
  template <typename WordValue,
	    typename SeriesValue,
	    typename Letter,
	    typename Tag,
	    typename GeometryCoords>
  struct automaton_traits<bmig::Graph<labels_are_letters, WordValue, bool, SeriesValue,
			  Letter, Tag, GeometryCoords> >
  {
    typedef bmig::Graph<labels_are_letters, WordValue, bool, SeriesValue,
		 Letter, Tag, GeometryCoords>		graph_t;
    typedef typename graph_t::semiring_elt_value_t	semiring_elt_value_t;
    typedef typename graph_t::monoid_elt_value_t	monoid_elt_value_t;
    typedef typename graph_t::word_value_t		word_value_t;
    typedef typename graph_t::series_set_elt_value_t	series_set_elt_value_t;
    typedef typename graph_t::letter_t			letter_t;
    typedef typename graph_t::tag_t			tag_t;
    typedef typename graph_t::geometry_t		geometry_t;
    typedef typename graph_t::label_t			label_t;
    typedef typename graph_t::states_t			states_t;
    typedef typename states_t::iterator			state_iterator;
    typedef typename graph_t::hstate_t			hstate_t;
    typedef typename graph_t::edges_t			transitions_t;
    typedef typename transitions_t::iterator		transition_iterator;
    typedef typename graph_t::htransition_t		htransition_t;
    typedef typename graph_t::initial_t			initial_t;
    typedef typename graph_t::initial_support_t		initial_support_t;
    typedef typename initial_support_t::iterator	initial_iterator;
    typedef typename graph_t::final_t			final_t;
    typedef typename graph_t::final_support_t		final_support_t;
    typedef typename final_support_t::iterator		final_iterator;
  };

 } // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/bmig_graph_letters_spec.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BMIG_GRAPH_LETTERS_SPEC_HH_ //

