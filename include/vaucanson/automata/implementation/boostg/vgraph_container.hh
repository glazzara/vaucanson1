// vgraph_container.hh: this file is part of the Vaucanson project.
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

#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HH
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HH

#include <iterator>

namespace vcsn
{
  namespace boostg
  {
    template<typename EdgesIterator, typename GraphData, typename HTransition>
    class VGraphContainerIterator
    {
    public:
      typedef EdgesIterator	iterator;
      VGraphContainerIterator(const GraphData& c, EdgesIterator i);
      HTransition operator*() const;

      bool operator==(const VGraphContainerIterator& v) const;
      bool operator!=(const VGraphContainerIterator& v) const;
      VGraphContainerIterator& operator++();
      VGraphContainerIterator operator++(int);

    private:
      iterator it_;
      iterator next_;
      const GraphData& container_;
    };

    template<typename EdgesIterator, typename GraphData, typename HTransition>
    class VGraphContainer
    {
    public:
      typedef VGraphContainerIterator<EdgesIterator, GraphData, HTransition> iterator;
      typedef iterator		    const_iterator;

      VGraphContainer(const GraphData& g);

      iterator begin() const;
      iterator end() const;

      size_t size() const;

    private:
      const GraphData& graph_;
    };
  }
}

# include <vaucanson/automata/implementation/boostg/vgraph_container.hxx>

#endif // !VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_VGRAPH_CONTAINER_HH
