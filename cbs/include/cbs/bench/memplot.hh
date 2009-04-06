// memplot.hh: this file is part of the CBS project.
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

#ifndef BENCH_MEMPLOT_HH_
# define BENCH_MEMPLOT_HH_

# include <cbs/bench/bench.hh>

namespace memplot
{
  struct Plot
  {
    std::string task;
    std::string description;

    long int memory;
    long int time;
  };

  // Measure the memory usage at a given time.
  void plot(const std::string& task, const std::string& description);

  // Clear all data.
  void clear();

  // Return the maximum memory used.
  const Plot& max();

  // Export the current data.
  void dump(std::ostream& stream, bench::Options options);
}

#endif //!BENCH_MEMPLOT_HH_
