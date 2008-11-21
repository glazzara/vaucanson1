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
#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HXX
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HXX

# include <vaucanson/automata/implementation/bmig_graph_impl.hh>
# include <vaucanson/automata/implementation/bmig/iterator.hh>

namespace vcsn
{
  namespace bmig
  {

    // Syntactic sugar
# define BMIG_ITERATOR_TPARAM template <typename Graph, typename I>
# define BMIG_ITERATOR DeltaConstIterator<Graph, I>

    BMIG_ITERATOR_TPARAM
    BMIG_ITERATOR::DeltaConstIterator(const graph_type& g,
				      typename graph_type::hstate_t s)
      : graph_(g)
    {
      range_type	tmp = graph_.deltai(s, iterator_type());
      i_ = tmp.first;
      end_ = tmp.second;
    }

    BMIG_ITERATOR_TPARAM
    BMIG_ITERATOR::~DeltaConstIterator()
    { }

    BMIG_ITERATOR_TPARAM
    void
    BMIG_ITERATOR::next()
    {
      ++i_;
    }

    BMIG_ITERATOR_TPARAM
    bool
    BMIG_ITERATOR::done() const
    {
      return i_ == end_;
    }

    BMIG_ITERATOR_TPARAM
    typename BMIG_ITERATOR::graph_type::htransition_t
    BMIG_ITERATOR::operator*() const
    {
      return graph_.get_htransition(i_);
    }

# undef BMIG_ITERATOR_TPARAM
# undef BMIG_ITERATOR

  } // End of namespace bmig

} // End of namespace vcsn

#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_BMIG_ITERATOR_HXX
