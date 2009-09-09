// timer_graph.hxx: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 The CBS Authors.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the Do What The Fuck You Want To
// Public License (WTFPL) version 2.
//
// The complete WTFPL license text can be found as the
// `COPYING' file in the root directory.
//
// The CBS Authors consists of people listed in the `AUTHORS' file.
//

/**
 ** \file include/cbs/bench/timer_graph.hxx
 ** Implementation of classes declared in timer_graph.hh.
 ** These classes are used in Timer (../timer.hh) to build a graph
 ** of the results and export it in DOT language.
 */

#ifndef BENCH_INTERNAL_TIMER_GRAPH_HXX
# define BENCH_INTERNAL_TIMER_GRAPH_HXX

// Internal
# include <cbs/bench/internal/timer_graph.hh>

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


#endif //!BENCH_INTERNAL_TIMER_GRAPH_HXX
