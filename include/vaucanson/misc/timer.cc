// timer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# if defined VAUCANSON
#  define INLINE_TIMER_CC inline
# else
#  define INLINE_TIMER_CC
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /*--------------.
  | Timer::Time.  |
  `--------------*/

  INLINE_TIMER_CC
  void
  Timer::Time::set_to_now ()
  {
    tms tms;
    wall = times (&tms);
    user = tms.tms_utime;
    sys	 = tms.tms_stime;
  }

  INLINE_TIMER_CC
  Timer::Time
  Timer::Time::now ()
  {
    Timer::Time res;
    res.set_to_now();
    return res;
  }

  INLINE_TIMER_CC
  void
  Timer::Time::clear ()
  {
    wall = 0;
    user = 0;
    sys	 = 0;
  }

  /*-----------------.
  | Timer::TimeVar.  |
  `-----------------*/

  INLINE_TIMER_CC
  Timer::TimeVar::TimeVar ()
  { }


  INLINE_TIMER_CC
  Timer::Time
  Timer::TimeVar::lap ()
  {
    // The lap time is credited to self and cumulated times.
    Time now = Timer::Time::now();
    Time res = now - begin;
    begin = now;
    return res;
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::start ()
  {
    begin = Timer::Time::now();
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::start_child ()
  {
    // The lap time is credited to self and cumulated times.
    Time lap_time = lap();
    elapsed += lap_time;
    cumulated += lap_time;
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::stop_child ()
  {
    // The time run by the child contributes to the cumulated time.
    cumulated += lap();
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::stop ()
  {
    // Same as starting a child.  We only update begin for nothing.
    start_child();
  }

  INLINE_TIMER_CC
  void
  Timer::TimeVar::clear ()
  {
    begin.clear ();
    elapsed.clear ();
    cumulated.clear ();
  }

  INLINE_TIMER_CC
  Timer::TimeVar Timer::TimeVar::operator+ (const TimeVar& rhs) const
  {
    Timer::TimeVar res(*this);
    return res += rhs;
  }

  INLINE_TIMER_CC
  Timer::TimeVar Timer::TimeVar::operator+= (const TimeVar& rhs)
  {
    elapsed += rhs.elapsed;
    cumulated += rhs.cumulated;
    return *this;
  }

  INLINE_TIMER_CC
  Timer::TimeVar Timer::TimeVar::operator/ (unsigned n) const
  {
    Timer::TimeVar res(*this);
    return res /= n;
  }

  INLINE_TIMER_CC
  Timer::TimeVar Timer::TimeVar::operator/= (unsigned n)
  {
    elapsed /= n;
    cumulated /= n;
    return *this;
  }

  INLINE_TIMER_CC
  bool
  Timer::TimeVar::operator< (const Timer::TimeVar& rhs) const
  {
    return cumulated < rhs.cumulated;
  }

  INLINE_TIMER_CC
  Timer::TimeVar::operator bool () const
  {
    return elapsed;
  }

  INLINE_TIMER_CC
  bool
  Timer::TimeVar::operator ! () const
  {
    return ! elapsed;
  }


  /*--------.
  | Timer.  |
  `--------*/

  INLINE_TIMER_CC
  Timer::Timer ()
    : dump_stream (0),
      clocks_per_sec (sysconf (_SC_CLK_TCK))
  { }

  INLINE_TIMER_CC
  // Duplicate a Timer. No tasks should be running.
  Timer::Timer (const Timer& rhs)
    : tasksmap (rhs.tasksmap),
      tab_to_disp (rhs.tab_to_disp),
      task_ordered (rhs.task_ordered),
      intmap (rhs.intmap),
      total (rhs.total),
      dump_stream (rhs.dump_stream),
      clocks_per_sec (rhs.clocks_per_sec)
  {
    // Hardly a precondition here...
    precondition (rhs.tasks.empty ());
  }

  INLINE_TIMER_CC
  Timer Timer::operator= (const Timer& rhs)
  {
    intmap = rhs.intmap;
    total = rhs.total;
    dump_stream = rhs.dump_stream;
    //clocks_per_sec = rhs.clocks_per_sec;

    precondition (rhs.tasks.empty ());
    tasksmap = rhs.tasksmap;
    return rhs;
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
      print (*dump_stream, true);
    }
  }


  INLINE_TIMER_CC
  void
  Timer::name (int i, const std::string& task_name)
  {
    intmap[i] = task_name;
  }

  INLINE_TIMER_CC
  std::ostream&
  Timer::print_time (long time, long total_time, std::ostream& o) const
  {
    return o
      << std::setiosflags (std::ios::left)
      << std::setw (6) << std::setprecision (6)
      << (float) (time) / clocks_per_sec
      << std::resetiosflags (std::ios::left)
      << " ("
      << std::setw (5) << std::setprecision (3)
      << (total_time
	  ? (float) time * 100 / total_time
	  : (float) time)
      << "%) ";
  }


  INLINE_TIMER_CC
  std::ostream&
  Timer::print_time (std::string s,
		     const Time& t, const Time& total, std::ostream& o,
		     const bool tree_mode = false) const
  {
    if (tree_mode && tab_to_disp.find(s) != tab_to_disp.end())
      s = tab_to_disp.find(s)->second + s;
    int w = tree_mode ? 50 : 26;
    o << " " << s << std::setw (w - s.length ()) << ": ";
    print_time (t.user, total.user, o);
    o << "  ";
    print_time (t.sys, total.sys, o);
    o << "  ";
    print_time (t.wall, total.wall, o);
    o << std::endl;
    return o;
  }


  INLINE_TIMER_CC
  std::ostream&
  Timer::print (std::ostream& o, const bool tree_mode = true) const
  {
    o << "Execution times (seconds)" << std::endl;
    for (std::list<std::string>::const_iterator i = task_ordered.begin ();
	 i != task_ordered.end (); ++i)
    {
      task_map_type::const_iterator j = tasksmap.find(*i);
      if (j->second)
	print_time (j->first, j->second.elapsed,
		    total.elapsed, o, tree_mode);
    }
    o << std::endl;

    o << "Cumulated times (seconds)" << std::endl;
    for (std::list<std::string>::const_iterator i = task_ordered.begin ();
	 i != task_ordered.end (); ++i)
    {
      task_map_type::const_iterator j = tasksmap.find(*i);
      if (j->second)
	print_time (j->first, j->second.cumulated,
		    total.elapsed, o, tree_mode);
    }
    o << std::endl;

    o << " TOTAL (seconds)"	 << std::setw (tree_mode ? 35 : 5) << ": "
      << std::setiosflags (std::ios::left) << std::setw (7)
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

      << std::resetiosflags (std::ios::left)
      << std::endl;

    return o;
  }

  INLINE_TIMER_CC
  void
  Timer::push (const std::string& task_name)
  {
    std::string tabs = "";

    // If stack isn't empty, we set elapsed time for the current task.
    if (!tasks.empty ())
      tasks.top ()->start_child ();

    if (tasksmap.find (task_name) == tasksmap.end ())
    {
      // Adjustment for Display
      task_ordered.push_back(task_name);
      for (unsigned i = 1; i <= tasks.size (); ++i)
	if (i == tasks.size ())
	  tabs += "|___";
	else
	  tabs += "   ";
    }

    if (tab_to_disp.find (task_name) == tab_to_disp.end ())
      tab_to_disp[task_name] = tabs;
    // FIXME : Bug is task is already in taskmap (first is not
    // reinitialized) Reset current to initial.
    TimeVar& current = tasksmap[task_name];

    // FIXME: Do we know for a fact that maps don't move their
    // content?  We might need an iterator here.
    tasks.push (&current);
    current.start ();
  }

  INLINE_TIMER_CC
  void
  Timer::pop ()
  {
    precondition (!tasks.empty ());

    // Set the elapsed time for the task we are closing.
    tasks.top ()->stop ();

    // Current task is removed of the stack
    tasks.pop ();

    // We set the start time of the previous task at current time
    if (!tasks.empty ())
      tasks.top ()->stop_child ();
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator<< (const Timer& rhs)
  {
    // No task should be running when merging timers.
    precondition (rhs.tasks.empty ());

    for (task_map_type::const_iterator i = rhs.tasksmap.begin ();
	 i != rhs.tasksmap.end (); ++i)
      if (tasksmap.find (i->first) == tasksmap.end ())
	tasksmap[i->first] = i->second;

    intmap.insert (rhs.intmap.begin (), rhs.intmap.end ());
    return *this;
  }


  INLINE_TIMER_CC
  Timer&
  Timer::operator+= (const Timer& rhs)
  {
    // FIXME: This is not sufficient, it's just an approximation.
    for (task_map_type::const_iterator i = rhs.tasksmap.begin ();
	 i != rhs.tasksmap.end (); ++i)
      tasksmap[i->first] += i->second;
    intmap.insert (rhs.intmap.begin (), rhs.intmap.end ());
    total += rhs.total;
    return *this;
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator/= (unsigned rhs)
  {
    // FIXME: This is not sufficient, it's just an approximation.
    for (task_map_type::iterator i = tasksmap.begin ();
	 i != tasksmap.end (); ++i)
      i->second /= rhs;
    total /= rhs;
    return *this;
  }


  INLINE_TIMER_CC
  Timer
  Timer::operator/ (unsigned rhs) const
  {
    Timer res = *this;
    return res /= rhs;
  }



  /*--------------------------.
  | Free standing functions.  |
  `--------------------------*/

  /// Dump \a t on \a o.
  INLINE_TIMER_CC
  std::ostream&
  operator<< (std::ostream& o, const Timer& t)
  {
    return t.print (o);
  }

} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC


  /*--------.
  | Tests.  |
  `--------*/

# if defined TEST_TIMER

#  include <iostream>

/// Test the timers.
int
main ()
{
#  if defined VAUCANSON
  using namespace vcsn;
#  endif

  misc::Timer timer;
  enum timevar
  {
    One = 1,
    Two,
    Three,
    Four
  };

  timer.name (One, "One");
  timer.name (Two, "Two");
  timer.name (Three, "Three");
  timer.name (Four, "Four");

  timer.start ();

  timer.push (One);
  sleep (1);


  timer.push ("Two");
  timer.push ("Three");
  sleep (1);
  timer.pop ("Three");
  sleep (2);
  timer.pop ("Two");
  timer.pop (1);

  timer.push ("Four");
  sleep (1);
  timer.pop (Four);

  timer.stop ();
  std::cerr << timer << std::endl;
  return 0;
}

# endif // TEST_TIMER

#endif //!VCSN_MISC_TIMER_CC

/// Local Variables:
/// compile-command: "g++ -I ../.. -I ../../../_build/include -DTEST_TIMER timer.cc -o test-timer -Wall && ./test-timer"
/// End:
