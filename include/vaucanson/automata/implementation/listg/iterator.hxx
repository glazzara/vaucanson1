// iterator.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HXX
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HXX

# include <vaucanson/automata/implementation/listg/iterator.hh>

namespace vcsn
{
  namespace listg
  {

    // Syntactic sugar
# define LISTG_ITERATOR_TPARAM template <typename Graph, typename Direction>
# define LISTG_ITERATOR DeltaConstIterator<Graph, Direction>

    LISTG_ITERATOR_TPARAM
    LISTG_ITERATOR::DeltaConstIterator(const graph_type& g, typename graph_type::hstate_t s)
      : graph_(g), s_(s)
    {
      initialize(direction());
    }

    LISTG_ITERATOR_TPARAM
    LISTG_ITERATOR::~DeltaConstIterator()
    { }

    LISTG_ITERATOR_TPARAM
    void
    LISTG_ITERATOR::next()
    {
      ++i_;
    }

    LISTG_ITERATOR_TPARAM
    bool
    LISTG_ITERATOR::done() const
    {
      return i_ == end_;
    }

    LISTG_ITERATOR_TPARAM
    void
    LISTG_ITERATOR::initialize(const backward_iterator&)
    {
      i_ = graph_.states_[s_].input_edges.begin();
      end_ = graph_.states_[s_].input_edges.end();
    }

    LISTG_ITERATOR_TPARAM
    void
    LISTG_ITERATOR::initialize(const forward_iterator&)
    {
      i_ = graph_.states_[s_].output_edges.begin();
      end_ = graph_.states_[s_].output_edges.end();
    }

    LISTG_ITERATOR_TPARAM
    typename LISTG_ITERATOR::graph_type::htransition_t
    LISTG_ITERATOR::operator*() const
    {
      return *i_;
    }

# undef LISTG_ITERATOR_TPARAM
# undef LISTG_ITERATOR

  } // End of namespace listg

} // End of namespace vcsn


#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HXX
