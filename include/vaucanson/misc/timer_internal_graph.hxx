// timer_internal_graph.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

/**
 ** \file misc/timer_internal_graph.cc
 ** Implementation of classes declared in
 ** misc/timer_internal_graph.hh.
 ** These classes are used in Timer (misc/timer.hh) to build a graph
 ** of the results and export it in DOT language.
 */

#ifndef VCSN_MISC_TIMER_INTERNAL_GRAPH_HXX
# define VCSN_MISC_TIMER_INTERNAL_GRAPH_HXX

# ifdef VAUCANSON
#  include <vaucanson/misc/timer_internal_graph.hh>
# else
#  include "timer_internal_graph.hh"
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{
  namespace timer
  {
    /*----------------------.
    | Timer::GraphTask.     |
    `----------------------*/

    inline
    bool
    GraphTask::operator< (const GraphTask& task) const
    {
      return self.cpu == task.self.cpu ?
        id < task.id :
        self.cpu > task.self.cpu;
    }

    /*------------------------.
    | Timer::GraphComponent.  |
    `------------------------*/

    inline
    void
    GraphComponent::add_call_out (GraphCall&    call)
    {
      out_calls += call.count;

      calls_out.push_back (&call);
    }

    inline
    void
    GraphComponent::add_call_internal (GraphCall&       call)
    {
      int_calls += call.count;
    }

  } // namespace timer
} // namespace misc

NAMESPACE_VCSN_END

#endif //!VCSN_MISC_TIMER_INTERNAL_GRAPH_HXX
