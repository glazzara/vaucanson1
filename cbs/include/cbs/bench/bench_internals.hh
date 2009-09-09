// bench_internals.hh: this file is part of the CBS project.
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

#ifndef BENCH_BENCH_INTERNALS_HH
# define BENCH_BENCH_INTERNALS_HH

/**
 *  \file src/bench_internals.hh
 *  \brief Interface to allow access to internal variables in bench.
 */

// CBS
# include <cbs/bench/bench.hh>
# include <cbs/bench/timer.hh>

namespace bench
{
  // Return the underlying timer instance.
  const timer::Timer& current_timer();

  // Restart the benchmark using the same parameters and results.
  // Note: time and memory results will be updated when the benchmark
  // is stopped.
  void restart();
}

#endif //!BENCH_BENCH_INTERNALS_HH
