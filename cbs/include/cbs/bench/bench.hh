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
  /// \brief Start a benchmark
  /// \param name the benchmark name.
  /// \param description a description for the benchmark.
  void start(std::string name,
	     std::string description);

  /// \brief Stop the current benchmark
  void stop();

  /// \brief Add a parameter
  /// Use after start(), and optionally after stop(),
  /// but before print(), save(), or dump().
  /// \param name the parameter name.
  /// \param name the parameter value.
  void parameter(std::string name,
		 std::string value);

  /// Convenient overload
  void parameter(std::string name,
		 long value);

  /// Convenient overload
  void parameter(std::string name,
		 double value);

  /// \brief Add a result
  /// Use after start(), and optionally after stop(),
  /// but before print(), save(), or dump().
  /// \param name the result name.
  /// \param name the result value.
  void result(std::string name,
	      std::string value);

  /// Convenient overload
  void result(std::string name,
	      long value);

  /// Convenient overload
  void result(std::string name,
	      double value);

  /// \brief Start a task
  /// \param name the task name
  void task_start(std::string name);

  /// \brief End the current task
  void task_stop();

  /// \brief Start a task within a scope
  /// A task starts when an instance is created and ends
  /// when it is destroyed.
  struct ScopedTask
  {
    /// \param name the task name
    ScopedTask(std::string name);
    ~ScopedTask();
  };

  /// \brief Make a memory usage measure
  /// \param name a description for the measure
  void memplot(std::string description);

  /// Options for the export functions (print(), save(), dump()).
  struct Options
  {
    /// Verbosity level, i.e. how much information is exported.
    enum Verbosity
    {
      VE_NONE,
      VE_MINIMAL,
      VE_NORMAL,
      VE_FULL
    };

    /// Output format.
    /// Note: Only the Callgraph can be exported in dot format.
    enum Format
    {
      FO_TEXT,
      FO_DOT,
      FO_XML
    };

    /// Contents, i.e. what parts of the benchmark are exported.
    /// Callgraph - List of all the task and their duration.
    /// Memplot - Memory usage measures.
    /// Summary - Parameters and main results of the benchmark.
    enum Contents
    {
      CO_CALLGRAPH = 0x1,
      CO_MEMPLOT   = 0x2,
      CO_NOSUMMARY = 0x4
    };

    /// Options constructor.
    /// Options default to full xml export
    Options(Verbosity verbosity = VE_NORMAL,
	    Format format = FO_XML,
	    int contents = CO_CALLGRAPH | CO_MEMPLOT);

    /// Return the verbosity level corresponding to an int value.
    /// \param i verbosity level in int form.
    static Verbosity get_verbosity(int i);

    Verbosity	verbosity;
    Format	format;
    int		contents;
  };

  /// \brief Print information about the last benchmark
  /// Use std::cout.
  /// \param options export options.
  void print(Options options);

  /// \brief Print information about the last benchmark
  /// Use the stream parameter.
  /// \param stream output stream.
  /// \param options export options.
  void dump(std::ostream& stream, Options options);

  /// \brief Export information about the last benchmark in a file.
  /// \param filename file to save in.
  /// \param options export options.
  void save(std::string filename, Options options);
}

#endif //!BENCH_BENCH_HH
