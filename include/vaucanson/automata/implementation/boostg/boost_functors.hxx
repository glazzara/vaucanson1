// boost_functors.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX
# define VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX

namespace vcsn
{
  namespace boostg
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/

  # define BOOSTGRAPH_TPARAM						\
    template <class Kind, class WordValue, class WeightValue,		\
              class SeriesValue, class Letter, class Tag, class GeometryCoords>

  # define BOOSTGRAPH							\
    Graph<Kind, WordValue, WeightValue, SeriesValue, Letter, Tag, GeometryCoords>

    /*-------------------------------------------------.
    | Functor used to update a label in a multi_index. |
    `-------------------------------------------------*/

    BOOSTGRAPH_TPARAM
    BOOSTGRAPH::update_label::update_label(hlabel_t i_)
      : i(i_)
    {
    }

    BOOSTGRAPH_TPARAM
    void
    BOOSTGRAPH::update_label::operator()(hlabel_t &key)
    {
      key = i;
    }

  }
}

# undef BOOSTGRAPH_TPARAM
# undef BOOSTGRAPH
#endif // ! VCSN_AUTOMATON_IMPLEMENTATION_BOOSTG_BOOST_FUNCTORS_HXX

