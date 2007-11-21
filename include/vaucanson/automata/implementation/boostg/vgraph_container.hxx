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

    /*--------------------------.
    | VGraphContainer iterator. |
    `--------------------------*/

    BOOSTGRAPH_TPARAM
    BOOSTGRAPH::VGraphContainerIterator
      ::VGraphContainerIterator(const GraphContainer& c,
				typename GraphContainer::iterator i)
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


    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::htransition_t
    BOOSTGRAPH::VGraphContainerIterator::operator*() const
    {
      return htransition_t(it_);
    }

    BOOSTGRAPH_TPARAM
    bool
    BOOSTGRAPH::VGraphContainerIterator::operator==(const VGraphContainerIterator& v) const
    {
      return v.it_ == it_;
    }

    BOOSTGRAPH_TPARAM
    bool
    BOOSTGRAPH::VGraphContainerIterator::operator!=(const VGraphContainerIterator& v) const
    {
      return v.it_ != it_;
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::VGraphContainerIterator::VGraphContainerIterator&
    BOOSTGRAPH::VGraphContainerIterator::operator++()
    {
      if (next_ != container_.end())
	it_ = next_++;
      else
	it_ = next_;
      return *this;
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::VGraphContainerIterator::VGraphContainerIterator
    BOOSTGRAPH::VGraphContainerIterator::operator++(int)
    {
      it_ = next_;
      return VGraphContainerIterator(container_, it_);
    }

    /*-----------------------------------------.
    | Container wrapper for Boost multi_index. |
    `-----------------------------------------*/

    BOOSTGRAPH_TPARAM
    BOOSTGRAPH::VGraphContainer::VGraphContainer(const GraphContainer& g)
      : graph_(g)
    {
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::VGraphContainer::iterator
    BOOSTGRAPH::VGraphContainer::begin() const
    {
      return VGraphContainerIterator(graph_, graph_.begin());
    }

    BOOSTGRAPH_TPARAM
    typename BOOSTGRAPH::VGraphContainer::iterator
    BOOSTGRAPH::VGraphContainer::end() const
    {
      return VGraphContainerIterator(graph_, graph_.end());
    }

    BOOSTGRAPH_TPARAM
    size_t
    BOOSTGRAPH::VGraphContainer::size() const
    {
      return graph_.size();
    }

  }
}

# undef BOOSTGRAPH_TPARAM
# undef BOOSTGRAPH
#endif // !VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HXX

