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
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/implementation/kind_adapter.hh>

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
  template <typename EdgeLabel>
  struct EdgeValue
  {
    public:
      EdgeValue (hstate_t from, hstate_t to, const EdgeLabel& l = EdgeLabel());

      operator const EdgeLabel& () const;
      operator EdgeLabel& ();

      EdgeLabel label () const;
      hstate_t from () const;
      hstate_t to () const;

    private:
      EdgeLabel label_;
      hstate_t from_;
      hstate_t to_;

  }; // End of class edge_value


  // State decorator FIXME rm?
  class StateValue
  {
    public:
      typedef /* FIXME: std::set<hedge_t> */ edges_t;

      StateValue (); // TODO

    private:
      edges_t input_edges_;
      edges_t output_edges_;

  }; // End of class state_value


  // class Graph.
  template <typename Kind, typename WordValue, typename WeightValue,
	    typename SeriesValue, typename Letter, typename Tag, typename Geometry>
  class BoostGraph
  {
    public:
      /*
      ** Type definitions
      */

      // self definition.
      typedef BoostGraph<Kind, WordValue, WeightValue,
			 SeriesValue, Letter, Tag, Geometry> self_t;

      typedef typename LabelOf<Kind, WordValue, WeightValue,
			       SeriesValue, Letter>::ret label_t;

      typedef StateValue state_value_t;
      typedef EdgeValue<label_t> edge_value_t;
      typedef SeriesValue series_set_elt_value_t;

      typedef /* FIXME: std::vector<StateValue_t> */ state_data_t;
      typedef /* FIXME: std::vector<EdgeValue_t> */ edge_data_t;

      typedef /* FIXME: StateContainer */ states_t;
      typedef /* FIXME: EdgeContainer */ edges_t;

      /* FIXME: {initial,final}{states,support} */

      typedef Tag tag_t;
      typedef Geometry geometry_t;


      BoostGraph ();
      BoostGraph (unsigned int initial_number_of_state,
		  unsigned int number_of_edge_initially_allocated); // TODO

      // FIXME: add const rettype& versions?

      states_t states () const; // TODO
      edges_t edges () const; // TODO
      initial_support_t initial () const; // TODO
      final_support_t final () const; // TODO

      // state manipulations
      bool has_state (hstate_t h) const; // TODO
      hstate_t add_state (); // TODO
      hstate_t del_state (hstate_t h); // TODO

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

      tag_t& tag () const; // TODO
      const tag_t& tag () const; // TODO
      geometry_t geometry () const; // TODO
      const geometry_t geometry () const; // TODO

      /*
      ** delta...
      ** FIXME: nice comments
      ** TODO: implementation
      */
# define DECLARE_DELTA_FUNCTION (FunName, DeltaKind)			\
      template <typename OutputIterator, typename Query>		\
      void FunName (OutputIterator res, hstate_t from,			\
		    const Query& q, delta_kind::DeltaKind) const
      DECLARE_DELTA_FUNCTION (delta, states);
      DECLARE_DELTA_FUNCTION (delta, edges);
      DECLARE_DELTA_FUNCTION (rdelta, states);
      DECLARE_DELTA_FUNCTION (rdelta, edges);
# undef DECLARE_DELTA_FUNCTION

# define DECLARE_DELTAF_BOOL_FUNCTION (FunName, DeltaKind, IsBool)	\
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

# define DECLARE_DELTAF_FUNCTION (FunName)				\
      template <typename Functor, typename Query, typename DeltaKind>	\
      void FunName (Functor& f, hstate_t from,				\
		    const Query& q, delta_kind::kind<DeltaKind>) const
      DECLARE_DELTAF_FUNCTION (deltaf);
      DECLARE_DELTAF_FUNCTION (rdeltaf);
# undef DECLARE_DELTAF_FUNCTION


    private:
      geometry_t geometry_;
      state_data_t states_;
      /* FIXME */ removed_states_;
      /* FIXME */ removed_edges_;
      tag_t tag_;
      final_t final_;
      initial_t initial_;

  }; // End of class BoostGraph

  // FIXME: add some nice comments
# define BOOSTGRAPH_TPARAM							\
  template <typename S, typename WordValue, typename WeightValue,		\
	    typename SeriesValue, typename Letter, typename Tag, typename Geometry>
  // FIXME: add ADAPT_* here
# undef BOOSTGRAPH_TPARAM

} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/boost_graph.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HH_ //
