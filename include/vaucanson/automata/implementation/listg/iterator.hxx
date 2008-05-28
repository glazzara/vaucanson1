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
# define LISTG_ITERATOR_TPARAM template <typename Graph, typename Handler, typename Direction>
# define LISTG_ITERATOR DeltaConstIterator<Graph, Handler, Direction>

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

    /*
    ** Helper for the operator*
    ** Used to retrieve the underlying data based on the iterator type
    ** without having to specialize the DeltaConstIterator for each type.
    */
    template <typename IteratorType>
    typename IteratorType::data_type
    op_get_delta_iterator_value(const IteratorType&,
				typename IteratorType::iterator_type i,
				const typename IteratorType::graph_type&);
# define LISTG_DCI(Handler, Dir) DeltaConstIterator<Graph, typename Graph::Handler, Dir>
// Note: GraphName is here to avoid the `unused parameter' warning.
# define LISTG_OP_DELTAI(Dir, H, GetData, GraphName)			    \
    template <typename Graph>						    \
    typename LISTG_DCI(H, Dir)::data_type				    \
    op_get_delta_iterator_value(const LISTG_DCI(H, Dir)&,		    \
				typename LISTG_DCI(H,Dir)::iterator_type i, \
				const Graph& GraphName)			    \
    {									    \
      return GetData;							    \
    }
    LISTG_OP_DELTAI(backward_iterator, hstate_t, g.edges_[*i].from, g);
    LISTG_OP_DELTAI(forward_iterator, hstate_t, g.edges_[*i].to, g);
    LISTG_OP_DELTAI(backward_iterator, htransition_t, *i,);
    LISTG_OP_DELTAI(forward_iterator, htransition_t, *i,);
# undef LISTG_OP_DELTAI
# undef LISTG_DCI


    LISTG_ITERATOR_TPARAM
    typename LISTG_ITERATOR::data_type
    LISTG_ITERATOR::operator*() const
    {
      return op_get_delta_iterator_value(*this, i_, graph_);
    }

# undef LISTG_ITERATOR_TPARAM
# undef LISTG_ITERATOR

  } // End of namespace listg

} // End of namespace vcsn


#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_LISTG_ITERATOR_HXX
