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

// STL
# include <ctime>
# include <iostream>
# include <vector>
# include <string>

// CBS
# include <cbs/bench/bench.hh>

namespace memplot
{
  class Memplot
  {
  public:
    struct Plot
    {
      std::string task;
      std::string description;

      unsigned memory;
      unsigned memory_rss;
      unsigned long time;

      Plot(std::string task, std::string description);
      Plot(const Plot& plot);
      const Plot& operator=(const Plot& plot);
      const Plot& operator-(const Plot& plot);

      bool operator<(const Plot& plot);
    };

    Memplot();
    ~Memplot();

    // Measure the memory usage at a given time.
    void plot(const std::string& task, const std::string& description);

    // Clear all data.
    void clear();

    // Return the maximum memory used.
    const Plot& max();

    // Return the maximum memory used.
    const Plot& relative_max();

    // Export the current data.
    void dump(std::ostream& stream, bench::Options options);

  private:
    void dump_xml_(std::ostream& stream, bench::Options options);
    void dump_text_(std::ostream& stream, bench::Options options);
    void dump_dot_(std::ostream& stream, bench::Options options);
    void dump_gnuplot_(std::ostream& stream, bench::Options options);

    Plot start_;
    Plot max_;
    std::vector<Plot> plots_;
  };
}

#endif //!BENCH_MEMPLOT_HH_
