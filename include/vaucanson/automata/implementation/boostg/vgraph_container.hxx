// vgraph_container.hxx: this file is part of the Vaucanson project.
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

#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HXX
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HXX

# include <vaucanson/automata/implementation/boostg/vgraph_container.hh>

namespace vcsn
{
  namespace boostg
  {

    /*--------------------.
    | Convenient macros.  |
    `--------------------*/

# define TPARAM						\
    template<typename EdgesIterator, typename GraphData, typename HTransition>

    /*--------------------------.
    | VGraphContainer iterator. |
    `--------------------------*/

# define ITERATOR						\
    VGraphContainerIterator<EdgesIterator, GraphData, HTransition>

    TPARAM
    ITERATOR::VGraphContainerIterator(const GraphData& c,
				      EdgesIterator i)
      : container_(c)
    {
      if (i != c.end())
      {
	it_ = i++;
	next_ = i;
      }
      else
      {
	it_ = i;
	next_ = i;
      }
    }


    TPARAM
    HTransition
    ITERATOR::operator*() const
    {
      return HTransition(it_);
    }

    TPARAM
    bool
    ITERATOR::operator==(const VGraphContainerIterator& v) const
    {
      return v.it_ == it_;
    }

    TPARAM
    bool
    ITERATOR::operator!=(const VGraphContainerIterator& v) const
    {
      return v.it_ != it_;
    }

    TPARAM
    typename ITERATOR::VGraphContainerIterator&
    ITERATOR::operator++()
    {
      if (next_ != container_.end())
	it_ = next_++;
      else
	it_ = next_;
      return *this;
    }

    TPARAM
    typename ITERATOR::VGraphContainerIterator
    ITERATOR::operator++(int)
    {
      iterator tmp = it_;
      if (next_ != container_.end())
	it_ = next_++;
      else
	it_ = next_;
      return ITERATOR(container_, tmp);
    }

    /*-----------------------------------------.
    | Container wrapper for Boost multi_index. |
    `-----------------------------------------*/

# define CONTAINER						\
    VGraphContainer<EdgesIterator, GraphData, HTransition> 

    TPARAM
    CONTAINER::VGraphContainer(const GraphData& g)
      : graph_(g)
    {
    }

    TPARAM
    typename CONTAINER::iterator
    CONTAINER::begin() const
    {
      return ITERATOR(graph_, graph_.begin());
    }

    TPARAM
    typename CONTAINER::iterator
    CONTAINER::end() const
    {
      return ITERATOR(graph_, graph_.end());
    }

    TPARAM
    size_t
    CONTAINER::size() const
    {
      return graph_.size();
    }

  }
}

# undef ITERATOR
# undef CONTAINER
# undef BOOSTGRAPH
#endif // !VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HXX

