// timer.hh: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 The CBS Authors.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The CBS Authors consists of people listed in the `AUTHORS' file.
//

/**
 ** \file src/timer.hxx
 ** \brief Inline methods for src/timer.hh.
 */

#ifndef BENCH_TIMER_HXX
# define BENCH_TIMER_HXX

// STL
# include <iosfwd>

// Unix
# include <sys/times.h>
# include <unistd.h>

// Internal
# include <cbs/bench/timer.hh>


namespace timer
{

  /*------------------.
  | Timer.            |
  | General methods.  |
  `------------------*/

  inline
  Timer::~Timer ()
  {
  }

  inline
  long
  Timer::time ()
  {
    return last_time_;
  }

  /*--------------.
  | Timer.        |
  | Arithmetics.  |
  `--------------*/

  inline
  bool
  Timer::operator< (const Timer& rhs) const
  {
    assert (! (is_running_ || rhs.is_running_));

    return graph_[0].total.cpu < rhs.graph_[0].total.cpu;
  }

  /*----------------------.
  | Timer.                |
  | Result computation.   |
  `----------------------*/

  inline
  void
  Timer::build_connected_components ()
  {
    comp_id_.resize (num_vertices (graph_));
    comp_count_ = strong_components (graph_, &comp_id_[0]);
  }

  /*-----------.
  | Timer.     |
  | Printing.  |
  `-----------*/

  inline
  std::ostream&
  Timer::print (std::ostream&         o,
                timer::verbose_degree vd) const
  {
    print_output_graph(o, vd);

    return o;
  }

  inline
  std::ostream&
  Timer::export_dot (std::ostream&         o,
                     timer::verbose_degree vd,
                     double                ccr) const
  {
    write_graphviz (o, graph_,
                    timer::VertexWriter (*this, vd, ccr),
                    timer::EdgeWriter   (*this, vd, ccr),
                    timer::GraphWriter  (*this, vd, ccr));
    return o;
  }

  /*--------------.
  | ScopedTimer.  |
  `--------------*/

  inline
  ScopedTimer::ScopedTimer (Timer&             timer,
                            const unsigned int i)
  {
    timer_ = &timer;
    timer.push (i);
  }

  inline
  ScopedTimer::ScopedTimer (Timer&             timer,
                            const std::string& name)
  {
    timer_ = &timer;
    timer.push (name);
  }

  inline
  ScopedTimer::~ScopedTimer ()
  {
    timer_->pop ();
  }

  /*--------------------------.
  | Free standing functions.  |
  `--------------------------*/

  /// Dump \a t on \a o.
  inline
  std::ostream&
  operator<< (std::ostream& o,
              const Timer&  t)
  {
    return t.print (o, timer::VERBOSE_NONE);
  }


} // namespace timer


#endif //!BENCH_TIMER_HXX
