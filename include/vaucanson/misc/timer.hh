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

#ifndef VCSN_MISC_TIMER_HH
# define VCSN_MISC_TIMER_HH

/**
 ** \file misc/timer.hh
 ** \brief Timer: Timing nested tasks.
 */

# include <stack>
# include <map>
# include <string>
# include <iosfwd>

# if VAUCANSON
#  define NAMESPACE_VCSN_BEGIN namespace vcsn {
#  define NAMESPACE_VCSN_END   } // namespace vcsn
# else
#  define NAMESPACE_VCSN_BEGIN
#  define NAMESPACE_VCSN_END
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /// Timing nested tasks.
  class Timer
  {
    public:
      Timer ();
      Timer (const Timer& rhs);
      ~Timer ();

      /// Start a sub timer for a named task.
      /// \param name a constant string which is the task's name
      void push (const std::string& name);

      /// Start a sub timer with an integer which refers to a string.
      /// \see push (), name ()
      void push (const int i);

      /// Stop the named task. Take a const string as parameter
      /// that make sure that what is popped is indeed what is on top.
      void pop (const std::string& task_name);

      /// \see pop (), pop (const std::string name)
      void pop (const int i);

      /// Stop the current task's timer (the last task pushed).
      void pop ();

      /// Write results.
      /// \param out an ostream which defaults to cerr.
      void dump (std::ostream& out);

      /// Write results when the timer is destroyed.
      /// \param out an ostream which defaults to cerr.
      void dump_on_destruction (std::ostream& out);

      /// The name function links an int and a constant string.
      /// \param i     the integer key to register
      /// \param name  the associated task name
      void name (int i, const std::string& name);

      /// The start function must be called at the beginning of the program
      /// to get the total time spend in the whole program.
      /// \see stop ()
      void start ();

      /// The stop function must be called at the end of the program.
      /// \see start ()
      void stop ();

      /// \brief Import timer.
      ///
      /// Import tasks defined in \a rhs. There must be not stacked task.
      /// Total execution time of \a rhs is ignored.
      Timer& operator<< (const Timer& rhs);

    private :
      class TimeVar;
      class Time
      {
	  friend class Timer;
	  friend class Timer::TimeVar;
	public:
	  Time ();

	  Time & operator += (const Time& rhs);

	private :
	  long user;
	  long sys;
	  long wall;
      };

      class TimeVar
      {
	public:
	  TimeVar ();

	  void start ();
	  void stop ();

	  bool is_zero ();

	  Time begin;
	  Time elapsed;
	  Time first;
	  Time last;
	  bool initial;
      };

      /// Format timing results.
      void timeinfo (long, long, std::ostream&);

      typedef std::map<const std::string, TimeVar*> task_map_type;

      /// Store differents tasks you benched.
      task_map_type tasksmap;

      /// Currently opened tasks, in order.
      std::stack<TimeVar*> tasks;

      /// Map for int and string couples (to call push (int)).
      std::map<int, std::string> intmap;

      /// Total time spent in the program.
      /// \see start (), stop ()
      TimeVar total;

      /** \brief A stream onto which the results are dumped when the
       oject is destroyed.  */
      std::ostream* dump_stream;

      /// Number of clocks ticks per second, set according to the system
      /// timing function used.
      const long clocks_per_sec;
  };

  /// A timer which starts at its construction, and stop at its destruction.
  class ScopedTimer
  {
  public:
    ScopedTimer (Timer& timer, const std::string& key);
    ~ScopedTimer ();
  private:
    Timer& timer_;
    const std::string key_;
  };

} // namespace misc

NAMESPACE_VCSN_END

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/timer.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_MISC_TIMER_HH
