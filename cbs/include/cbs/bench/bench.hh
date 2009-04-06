// bench.hh: this file is part of the CBS project.
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

#ifndef BENCH_BENCH_HH
# define BENCH_BENCH_HH

/**
 *  \file src/bench.hh
 *  \brief Main interface of the bench library.
 */

# include <string>

namespace bench
{
  // Start a benchmark
  void start(std::string name,
	     std::string description);

  // Stop the current benchmark
  void stop();

  // Add a parameter
  void parameter(std::string name,
		 std::string value);

  // Add a result
  void result(std::string name,
	      std::string value);

  // Start a task
  void task_start(std::string name);

  // End the current task
  void task_stop();

  // Start a task within a scope
  struct ScopedTask
  {
    ScopedTask(std::string name);
    ~ScopedTask();
  };

  // Plot the memory usage
  void mem_plot(std::string description);

  struct Options
  {
    enum Verbosity
    {
      VE_NONE,
      VE_MINIMAL,
      VE_NORMAL,
      VE_FULL
    };

    enum Format
    {
      FO_TEXT,
      FO_DOT,
      FO_XML
    };

    enum Contents
    {
      CO_CALLGRAPH = 0x1,
      CO_MEMPLOT   = 0x2
    };

    Options(Verbosity verbosity = VE_NORMAL,
	    Format format = FO_XML,
	    int contents = CO_CALLGRAPH | CO_MEMPLOT);

    Verbosity	verbosity;
    Format	format;
    int		contents;
  };

  // Print information about the last benchmark
  void print(Options options);

  // Print information about the last benchmark
  void dump(std::ostream& stream, Options options);

  // Export information about the last benchmark
  void save(std::string filename, Options options);
}

#endif //!BENCH_BENCH_HH
