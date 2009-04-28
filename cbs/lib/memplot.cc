// memplot.cc: this file is part of the CBS project.
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
 *  \file lib/memplot.cc
 *  \brief Main implementation for memplot.
 */

// STL
#include <cassert>
#include <ctime>

// Check whether needed
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <sys/time.h>
#include <sys/resource.h>

// Internal
#include <cbs/bench/memplot.hh>

namespace memplot
{
  Memplot::Plot::Plot(std::string task_, std::string description_)
    : task(task_),
      description(description_),
      memory(0),
      memory_rss(0),
      rawtime(0)
  {
    time(&rawtime);

    std::ifstream file;
    std::string str_;
    unsigned val_;
    unsigned rss_;
    unsigned vm_size_;

    file.open("/proc/self/stat");

    if (file.is_open())
      ;

    file >> val_ // pid
	 >> str_ // command
	 >> str_ // state
	 >> val_ // ppid
	 >> val_ // prgp
	 >> val_ // session
	 >> val_ // tty
	 >> val_ // tpgid
	 >> val_ // flags
	 >> val_ // minflt
	 >> val_ // cminflt
	 >> val_ // majflt
	 >> val_ // cmajflt
	 >> val_ // utime
	 >> val_ // stime
	 >> val_ // cutime
	 >> val_ // cstime
	 >> val_ // counter
	 >> val_ // priority
	 >> val_ // timeout
	 >> val_ // itrealvalue
	 >> val_ // starttime
	 >> vm_size_ // vsize
	 >> rss_; // rss

    file.close();

    memory = vm_size_;
    memory_rss = rss_;
  }

  Memplot::Plot::Plot(const Memplot::Plot& plot)
    : task(plot.task),
      description(plot.description),
      memory(plot.memory),
      memory_rss(plot.memory_rss),
      rawtime(plot.rawtime)
  {
  }

  const Memplot::Plot&
  Memplot::Plot::operator=(const Memplot::Plot& plot)
  {
    if (this == &plot)
      return *this;

    task = plot.task;
    description = plot.description;
    memory = plot.memory;
    memory_rss = plot.memory_rss;
    rawtime = plot.rawtime;

    return *this;
  }

  bool
  Memplot::Plot::operator<(const Memplot::Plot& plot)
  {
    if (memory < plot.memory)
      return true;
    return false;
  }

  Memplot::Memplot()
    : max_("", "Starting memory usage")
  {
  }

  Memplot::~Memplot()
  {
    plots_.clear();
  }

  // Measure the memory usage at a given time.
  void
  Memplot::plot(const std::string& task, const std::string& description)
  {
    Plot plot(task, description);

    plots_.push_back(plot);

    if (max_ < plot)
      max_ = plot;
  }

  // Clear all data.
  void
  Memplot::clear()
  {
    plots_.clear();
    max_ = Plot("", "Starting memory usage");
  }

  // Return the maximum memory used.
  const Memplot::Plot&
  Memplot::max()
  {
    return max_;
  }

  // Export the current data.
  void
  Memplot::dump(std::ostream& stream, bench::Options options)
  {
    switch (options.format)
    {
    case bench::Options::FO_TEXT:
      dump_text_(stream, options);
      break;
    case bench::Options::FO_DOT:
      dump_dot_(stream, options);
      break;
    case bench::Options::FO_XML:
      dump_xml_(stream, options);
      break;
    }
  }

  void
  Memplot::dump_xml_(std::ostream& stream, bench::Options options)
  {
    stream << "<memplot>" << std::endl;

    for (std::vector<Plot>::iterator it = plots_.begin();
	 it != plots_.end();
	 ++it)
    {
      stream << "  <plot>" << std::endl
	     << "    <time>" << (*it).rawtime << "</time>" << std::endl
	     << "    <memory>" << (*it).memory << "</memory>" << std::endl
	     << "    <memory_rss>"
	     << (*it).memory_rss << "</memory_rss>" << std::endl
	     << "    <task>" << (*it).task << "</task>" << std::endl
	     << "    <description>"
	     << (*it).description << "</description>" << std::endl
	     << "  </plot>" << std::endl;
    }
    stream << "</memplot>" << std::endl;
  }

  void
  Memplot::dump_text_(std::ostream& stream, bench::Options options)
  {
  }

  void
  Memplot::dump_dot_(std::ostream& stream, bench::Options options)
  {
  }
}
