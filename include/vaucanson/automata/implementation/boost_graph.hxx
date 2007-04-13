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

  template <typename EdgeLabel>
  inline
  EdgeValue<EdgeLabel>::EdgeValue (hstate_t h1, hstate_t h2, const EdgeLabel& l)
    : label_ (l), from_ (h1), to_ (h2)
  { }

  template <typename EdgeLabel>
  inline
  EdgeValue<EdgeLabel>::operator const EdgeLabel& () const
  {
    return label_;
  }

  template <typename EdgeLabel>
  inline
  EdgeValue<EdgeLabel>::operator EdgeLabel& ()
  {
    return label_;
  }


  /*
  ** class BoostGraph
  */

  // Syntactic sugar
# define BOOSTGRAPH_TPARAM							\
  template <typename Kind, typename WordValue, typename WeightValue,		\
	    typename SeriesValue, typename Letter, typename Geometry>
# define BOOSTGRAPH								\
  BoostGraph<Kind, WordValue, WeightValue, SeriesValue, Letter, Geometry>

  BOOSTGRAPH_TPARAM
  inline
  BOOSTGRAPH::BoostGraph ()
  { }

  // End of syntactic sugar
# undef BOOSTGRAPH_TPARAM
# undef BOOSTGRAPH

} // End of namespace vcsn

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOST_GRAPH_HXX_ //
