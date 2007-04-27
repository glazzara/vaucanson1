// boost_graph.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_

# include <vaucanson/automata/implementation/boost_graph.hh>

namespace vcsn
{
  /*
  ** class EdgeLabel
  */

  inline
  EdgeValue::EdgeValue (hstate_t h1, hstate_t h2, unsigned l)
    : label_ (l), from_ (h1), to_ (h2)
  { }

/*  inline
  EdgeValue::operator const EdgeLabel& () const
  {
    return label_;
  }

  template <typename EdgeLabel>
  inline
  EdgeValue<EdgeLabel>::operator EdgeLabel& ()
  {
    return label_;
  }
*/

  /*--------------------.
  | Convenient macros.  |
  `--------------------*/

# define BOOSTGRAPH_TPARAM						\
  template <class Kind, class WordValue, class WeightValue,		\
	    class SeriesValue, class Letter, class Tag, class Geometry>

# define BOOSTGRAPH							\
  Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, Geometry>


  /*-------------------------.
  | Graph's implementation.  |
  `-------------------------*/

  /*---------------.
  | Constructors.  |
  `---------------*/

  BOOSTGRAPH_TPARAM
  inline
  BOOSTGRAPH::Graph ()
    : number_of_state_(0),
      have_epsilon_(0)
  { }

  /*!
  **  Constructor provided for convenience.
  **  Keep compatibility with other implementations.
  **  Because of BMI, this constructor doesn't allocate memory in advance
  **  even if the 'reserve_number_of_edge' is specified.
  **
  **  However, the 'initial_number_of_state' parameter is used and implies
  **  the creation of this number of states.
  */
  BOOSTGRAPH_TPARAM
  BOOSTGRAPH::Graph (unsigned initial_number_of_state,
		     unsigned reserve_number_of_edge)
    : number_of_state_(initial_number_of_state),
      have_epsilon_(0)
  { }

  /*------------------.
  | Basic accessors.  |
  `------------------*/

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::states_t
  BOOSTGRAPH::states() const
  {
    return states_t();
  }

  BOOSTGRAPH_TPARAM
  typename BOOSTGRAPH::edges_t
  BOOSTGRAPH::edges() const
  {
    return graph_;
  }



  BOOSTGRAPH_TPARAM
  hstate_t
  BOOSTGRAPH::src_of (hedge_t) const
  {
    return hstate_t(0);
  }

  // End of syntactic sugar
# undef BOOSTGRAPH_TPARAM
# undef BOOSTGRAPH

} // End of namespace vcsn

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_ //
