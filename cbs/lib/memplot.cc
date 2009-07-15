// memplot.cc: this file is part of the CBS project.
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

// Unset to use sbrk (fast execution time but no rss value)
// Set to parse /proc/self/stat (slow, but rss value available)
//#define MEMPLOT_USE_PROC_SELF_STAT

namespace memplot
{
  Memplot::Plot::Plot(std::string task_, std::string description_)
    : task(task_),
      description(description_),
      memory(0),
      memory_rss(0),
      time(0)
  {
    struct timeval wall;
    gettimeofday(&wall, 0);

    time = wall.tv_usec / 1000 + 1000 * wall.tv_sec;

#ifndef MEMPLOT_USE_PROC_SELF_STAT
    memory = (unsigned long) sbrk(0);
    return;
#else
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
#endif // MEMPLOT_USE_SBRK
  }

  Memplot::Plot::Plot(const Memplot::Plot& plot)
    : task(plot.task),
      description(plot.description),
      memory(plot.memory),
      memory_rss(plot.memory_rss),
      time(plot.time)
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
    time = plot.time;

    return *this;
  }

  const Memplot::Plot&
  Memplot::Plot::operator-(const Memplot::Plot& plot)
  {
    if (this == &plot)
      return *this;

    description += " (relative to " + plot.description + ")";
    memory -= plot.memory;
    memory_rss -= plot.memory_rss;

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
    : start_("", "Starting memory")
    , max_(start_)
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
    start_ = Plot("", "Starting memory");
    max_ = start_;
  }

  // Return the maximum memory used.
  const Memplot::Plot&
  Memplot::max()
  {
    return max_;
  }

  // Return the maximum memory used (relatively to the starting memory
  // usage).
  const Memplot::Plot&
  Memplot::relative_max()
  {
    return max_ - start_;
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
    case bench::Options::FO_GNUPLOT:
      dump_gnuplot_(stream, options);
      break;
    }
  }

  inline static void plot_dump_xml_(std::ostream& stream,
				    bench::Options options,
				    const Memplot::Plot& plot,
				    unsigned long time_offset)
  {
    stream << "  <plot>" << std::endl
	   << "    <time>" << plot.time - time_offset << "</time>"
	   << std::endl
	   << "    <memory>" << plot.memory << "</memory>" << std::endl
	   << "    <memory_rss>"
	   << plot.memory_rss << "</memory_rss>" << std::endl
	   << "    <task>" << plot.task << "</task>" << std::endl
	   << "    <description>"
	   << plot.description << "</description>" << std::endl
	   << "  </plot>" << std::endl;
  }

  void
  Memplot::dump_xml_(std::ostream& stream, bench::Options options)
  {
    stream << "<memplot>" << std::endl;

    plot_dump_xml_(stream, options, start_, start_.time);

    for (std::vector<Plot>::iterator it = plots_.begin();
	 it != plots_.end();
	 ++it)
    {
      plot_dump_xml_(stream, options, (*it), start_.time);
    }
    stream << "</memplot>" << std::endl;
  }

  inline static void plot_dump_text_(std::ostream& stream,
				     bench::Options options,
				     const Memplot::Plot& plot,
				     unsigned long time_offset)
  {
    stream << "  * (" << plot.time - time_offset << ")"
	   << "(" << plot.task << "): "
	   << plot.memory << "B - " << plot.description << std::endl;
  }

  void
  Memplot::dump_text_(std::ostream& stream, bench::Options options)
  {
    stream << "[Memplot:]" << std::endl << std::endl;

    plot_dump_text_(stream, options, start_, start_.time);

    for (std::vector<Plot>::iterator it = plots_.begin();
	 it != plots_.end();
	 ++it)
    {
      plot_dump_text_(stream, options, (*it), start_.time);
    }
    stream << std::endl;
  }

  void
  Memplot::dump_dot_(std::ostream& stream, bench::Options options)
  {
  }

  inline static void plot_dump_gnuplot_(std::ostream& stream,
					bench::Options options,
					const Memplot::Plot& plot,
					unsigned long time_offset)
  {
    stream << plot.time - time_offset << " "
	   << "\"" << plot.task << "\" "
	   << plot.memory << " "
	   << plot.memory_rss << " "
	   << "\"" << plot.description << "\"" << std::endl;
  }

  void
  Memplot::dump_gnuplot_(std::ostream& stream, bench::Options options)
  {
    stream << "# Memplot:" << std::endl
	   << "#" << std::endl
	   << "# * Time" << std::endl
	   << "# * \"Task name\"" << std::endl
	   << "# * Virtual memory (B)" << std::endl
	   << "# * RSS (MB)" << std::endl
	   << "# * \"Description\"" << std::endl;

    plot_dump_gnuplot_(stream, options, start_, start_.time);

    for (std::vector<Plot>::iterator it = plots_.begin();
	 it != plots_.end();
	 ++it)
    {
      plot_dump_gnuplot_(stream, options, (*it), start_.time);
    }
    stream << std::endl;
  }
}
