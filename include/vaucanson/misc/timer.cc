// timer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/**
 ** \file misc/timer.cc
 ** \brief Implementation for misc/timer.hh.
 */

#ifndef VCSN_MISC_TIMER_CC
# define VCSN_MISC_TIMER_CC

# include <iostream>
# include <iomanip>

# include <sys/times.h>
# include <unistd.h>

# include <vaucanson/misc/timer.hh>
# include <vaucanson/misc/contract.hh>

/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# if VAUCANSON
#  define INLINE_TIMER_CC inline
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /*-----------------.
  | Timer::TimeVar.  |
  `-----------------*/
  INLINE_TIMER_CC
  Timer::TimeVar::TimeVar ()
    : initial (true)
  { }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::start ()
  {
    struct tms tms;

    begin.wall = times (&tms);
    begin.user = tms.tms_utime;
    begin.sys	 = tms.tms_stime;

    if (initial)
    {
      initial = false;
      first = begin;
    }
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::stop ()
  {
    struct tms tms;

    last.wall = times (&tms);
    last.user = tms.tms_utime;
    last.sys = tms.tms_stime;
    elapsed.wall += last.wall - begin.wall;
    elapsed.user += last.user - begin.user;
    elapsed.sys += last.sys - begin.sys;
  }

  INLINE_TIMER_CC
  bool
  Timer::TimeVar::is_zero ()
  {
    return (true
	    && elapsed.wall == 0
	    && elapsed.user == 0
	    && elapsed.sys  == 0);
  }


  /*--------.
  | Timer.  |
  `--------*/

  INLINE_TIMER_CC
  Timer::Timer () :
    dump_stream (0),
    clocks_per_sec (sysconf (_SC_CLK_TCK))
  { }

  INLINE_TIMER_CC
  // Duplicate a Timer. No tasks should be running.
  Timer::Timer (const Timer& rhs) :
    intmap (rhs.intmap),
    total (rhs.total),
    dump_stream (rhs.dump_stream),
    clocks_per_sec (rhs.clocks_per_sec)
  {
    precondition (rhs.tasks.empty ());

    for (task_map_type::const_iterator i = rhs.tasksmap.begin ();
	 i != rhs.tasksmap.end (); ++i)
      if (tasksmap.find (i->first) == tasksmap.end ())
	tasksmap[i->first] = new TimeVar (*i->second);
  }


  INLINE_TIMER_CC
  Timer::~Timer ()
  {
    // If magic is asked on destruction, let it happen completely.
    if (dump_stream)
    {
      // Consider that if the tasks were not properly closed, then
      // stop was not invoked either.
      if (!tasks.empty ())
      {
	do
	  pop ();
	while (!tasks.empty ());
	stop ();
      }
      dump (*dump_stream);
    }

    // Deallocate all our TimeVar.
    for (task_map_type::iterator i = tasksmap.begin ();
	 i != tasksmap.end (); ++i)
      delete i->second;
  }


  INLINE_TIMER_CC
  void
  Timer::name (int i, const std::string& task_name)
  {
    intmap[i] = task_name;
  }

  INLINE_TIMER_CC
  void
  Timer::timeinfo (long time, long total_time, std::ostream& out)
  {
    out << setiosflags (std::ios::left);
    out << std::setw (6) << std::setprecision (6)
	<< (float) (time) / clocks_per_sec;
    out << resetiosflags (std::ios::left);
    out << " (";
    out << std::setw (5) << std::setprecision (3)
	<< (total_time ?
	    (float) time * 100 / total_time :
	    (float) time);
    out << "%) ";
  }


  INLINE_TIMER_CC
  void
  Timer::dump (std::ostream& out = std::cerr)
  {
    out << "Execution times (seconds)" << std::endl;
    for (task_map_type::const_iterator i = tasksmap.begin ();
	 i != tasksmap.end (); ++i)
    {
      if (!(i->second->is_zero ()))
      {
	out << " " << i->first << std::setw (26 - i->first.length ());
	out << ": ";
	timeinfo (i->second->elapsed.user, total.elapsed.user, out);
	out << "  ";
	timeinfo (i->second->elapsed.sys, total.elapsed.sys, out);
	out << "  ";
	timeinfo (i->second->elapsed.wall, total.elapsed.wall, out);
	out << std::endl;
      }
    }
    out << std::endl;

    out << "Cumulated times (seconds)" << std::endl;
    for (task_map_type::const_iterator i = tasksmap.begin ();
	 i != tasksmap.end (); ++i)
    {
      if (0 != (i->second->last.wall - i->second->first.wall))
      {
	out << " " << i->first << std::setw (26 - i->first.length ());
	out << ": ";
	timeinfo (i->second->last.user - i->second->first.user,
		  total.elapsed.user, out);
	out << "  ";
	timeinfo (i->second->last.sys - i->second->first.sys,
		  total.elapsed.sys, out);
	out << "  ";
	timeinfo (i->second->last.wall - i->second->first.wall,
		  total.elapsed.wall, out);
	out << std::endl;
      }
    }
    out << std::endl;

    out << " TOTAL (seconds)"	 << std::setw (11) << ": "

	<< setiosflags (std::ios::left) << std::setw (7)
	<< (float) total.elapsed.user / clocks_per_sec
	<< std::setw (11)
	<< "user,"

	<< std::setw (7)
	<< (float) total.elapsed.sys / clocks_per_sec
	<< std::setw (11)
	<< "system,"

	<< std::setw (7)
	<< (float) total.elapsed.wall / clocks_per_sec
	<< "wall"

	<< resetiosflags (std::ios::left) << std::endl;
  }

  INLINE_TIMER_CC
  void
  Timer::push (const std::string& task_name)
  {
    // If stack isn't empty, we set elapsed time for the current task.
    if (!tasks.empty ())
      tasks.top ()->stop ();

    if (tasksmap.find (task_name) == tasksmap.end ())
      tasksmap[task_name] = new TimeVar;

    TimeVar* current = tasksmap[task_name];
    tasks.push (current);
    current->start ();
  }

  INLINE_TIMER_CC
  void
  Timer::pop ()
  {
    precondition (!tasks.empty ());

    // Set the Elapsed time for the task we are closing
    tasks.top ()->stop ();

    // Current task is removed of the stack
    tasks.pop ();

    // We set the start time of the previous task at current time
    if (!tasks.empty ())
      tasks.top ()->start ();
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator<< (const Timer& rhs)
  {
    // No task should be running when merging timers.
    precondition (rhs.tasks.empty ());

    for (task_map_type::const_iterator i = rhs.tasksmap.begin ();
	 i != rhs.tasksmap.end (); ++i)
    {
      if (tasksmap.find (i->first) == tasksmap.end ())
	tasksmap[i->first] = new TimeVar (*i->second);
    }

    intmap.insert (rhs.intmap.begin (), rhs.intmap.end ());
    return *this;
  }

} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC

#endif //!VCSN_MISC_TIMER_CC
