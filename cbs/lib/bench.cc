// bench.cc: this file is part of the CBS project.
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
 *  \file lib/bench.cc
 *  \brief Main implementation of the bench library.
 */

// STL
# include <map>
# include <sstream>
# include <fstream>
# include <iostream>
# include <cassert>

// Internal
# include <cbs/bench/bench.hh>
# include <cbs/bench/timer.hh>

namespace bench
{
  static bool started   = false;
  static bool completed = false;

  static std::string name;
  static std::string description;

  typedef std::map<std::string, std::string> string_map;

  static string_map parameters;
  static string_map results;

  static timer::Timer timer;

  // Start a benchmark
  void start(std::string _name,
	     std::string _description)
  {
    name        = _name;
    description = _description;

    parameters.clear();
    results.clear();

    timer.start();

    completed = false;
    started   = true;
  }

  // Stop the current benchmark
  void stop()
  {
    timer.stop();

    completed = true;
    started   = false;

    std::stringstream time;
    time << timer.time();

    result("time", time.str());
  }

  // Add a parameter
  void parameter(std::string name,
		 std::string value)
  {
    parameters.erase(name);
    parameters.insert(std::pair<std::string, std::string>(name, value));
  }

  // Add a result
  void result(std::string name,
	      std::string value)
  {
    results.erase(name);
    results.insert(std::pair<std::string, std::string>(name, value));
  }

  // Start a task
  void task_start(std::string name)
  {
    if (started)
      timer.push(name);
  }

  // End the current task
  void task_stop()
  {
    if (started)
      timer.pop();
  }

  // Start a task within a scope
  ScopedTask::ScopedTask(std::string name)
  {
    if (started)
      timer.push(name);
  }

  ScopedTask::~ScopedTask()
  {
    if (started)
      timer.pop();
  }

  // Plot the memory usage
  void mem_plot(std::string description)
  {
    // FIXME: Not implemented
  }

  static void output_xml(std::ostream& stream, Options options)
  {
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    stream << "<bench>" << std::endl
	   << "  <name>" << name << "</name>" << std::endl
	   << "  <description>" << description << "</description>" << std::endl
	   << "  <parameters>" << std::endl;

    for (string_map::iterator it = parameters.begin();
	 it != parameters.end();
	 ++it)
    {
      stream << "    <parameter name=\"" << (*it).first
	     << "\" value=\"" << (*it).second << "\" />" << std::endl;
    }

    stream << "  </parameters>" << std::endl;
    stream << "  <results>" << std::endl;

    for (string_map::iterator it = results.begin();
	 it != results.end();
	 ++it)
    {
      stream << "    <result name=\"" << (*it).first
	     << "\" value=\"" << (*it).second << "\" />" << std::endl;
    }

    stream << "  </results>" << std::endl
	   << "</bench>" << std::endl;
  }

  static void output_text(std::ostream& stream, Options options)
  {
    stream << name << std::endl
	   << std::endl
	   << description << std::endl
	   << std::endl
	   << "[Parameters:]" << std::endl;

    for (string_map::iterator it = parameters.begin();
	 it != parameters.end();
	 ++it)
    {
      stream << "  * " << (*it).first << ": " << (*it).second << std::endl;
    }

    stream << std::endl;
    stream << "[Results:]" << std::endl;

    for (string_map::iterator it = results.begin();
	 it != results.end();
	 ++it)
    {
      stream << "  * " << (*it).first << ": " << (*it).second << std::endl;
    }

    stream << std::endl;
  }

  static void output_dot(std::ostream& stream, Options options)
  {
    // FIXME: Nothing to output?
  }

  static void output(std::ostream& stream, Options options)
  {
    bool output_timer = (options.contents & Options::CO_CALLGRAPH);
    bool output_memplot = (options.contents & Options::CO_MEMPLOT);

    timer::verbose_degree timer_vd;

    switch (options.verbosity)
    {
    case Options::VE_MINIMAL:
      timer_vd = timer::VERBOSE_MINIMAL;
      break;
    case Options::VE_NORMAL:
      timer_vd = timer::VERBOSE_NORMAL;
      break;
    case Options::VE_FULL:
      timer_vd = timer::VERBOSE_MAXIMAL;
      break;
    default:
      timer_vd = timer::VERBOSE_NONE;
    }

    switch (options.format)
    {
    case Options::FO_TEXT:
      output_text(stream, options);
      if (output_timer)
	timer.print(stream, timer_vd);
      if (output_memplot)
	;
      break;
    case Options::FO_DOT:
      output_dot(stream, options);
      if (output_timer)
	timer.export_dot(stream, timer_vd);
      if (output_memplot)
	;
      break;
    case Options::FO_XML:
      output_xml(stream, options);
      if (output_timer)
	timer.dump(stream);
      if (output_memplot)
	;
      break;
    }

  }

  // Print information about the last benchmark
  void print(Options options)
  {
    assert(completed);

    output(std::cout, options);
  }

  // Print information about the last benchmark
  void dump(std::ostream& stream, Options options)
  {
    assert(completed);

    output(stream, options);
  }

  // Export information about the last benchmark
  void save(std::string filename, Options options)
  {
    assert(completed);

    std::ofstream stream;

    stream.open(filename.c_str());

    if (!stream.fail())
    {
      output(stream, options);
    }
    else
      std::cerr << "Bench error: Could not open file " << filename << ".";

    stream.close();
  }

  Options::Options(Verbosity verbosity_,
	           Format format_,
		   int contents_)
  {
    verbosity = verbosity_;
    format = format_;
    contents = contents_;
  }

}
