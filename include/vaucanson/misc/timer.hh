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

#ifndef VCSN_MISC_TIMER_HH
# define VCSN_MISC_TIMER_HH

/**
 ** \file misc/timer.hh
 ** \brief Timer: Timing nested tasks.
 */

# include <stack>
# include <map>
# include <list>
# include <string>
# include <iosfwd>

# define VAUCANSON 1

# if defined VAUCANSON
#  define NAMESPACE_VCSN_BEGIN namespace vcsn {
#  define NAMESPACE_VCSN_END   } // namespace vcsn
#  include <vaucanson/misc/contract.hh>
# else
#  define NAMESPACE_VCSN_BEGIN
#  define NAMESPACE_VCSN_END
#  include <cassert>
#  define precondition(C) assert(C)
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /// Timing nested tasks.
  class Timer
  {
  public:
    friend class Bencher;

    class TimeVar;
    typedef std::map<const std::string, TimeVar> task_map_type;

    Timer ();
    Timer (const Timer& rhs);
    ~Timer ();

    Timer operator= (const Timer& rhs);

    /// Start a sub-timer for a named task.
    /// \param name a constant string which is the task's name
    void push (const std::string& name);

    /// Start a sub-timer with an integer which refers to a string.
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
    /// \param o an ostream.
    std::ostream& print (std::ostream& o, const bool) const;

    /// Write results when the timer is destroyed.
    /// \param out an ostream which defaults to cerr.
    void print_on_destruction (std::ostream& out);

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

    /// \brief Accumulate another timer.
    Timer& operator+= (const Timer& rhs);

    /// \brief Divide in place.
    Timer& operator/= (unsigned rhs);

    /// \brief Divide.
    Timer operator/ (unsigned rhs) const;

    /// \brief Comparison between two Timers.
    /// This operators enables the use of std::min and std::max.
    /// It check only the \a total time, so it's a strict weak ordering.
    bool operator< (const Timer& rhs) const;

    /// Reset all timers to zero.
    void clear();

    TimeVar& operator[] (const std::string& s);

  public :
    /// User, system and wall clock time convenient interface.
    class Time
    {
      friend class Bencher;
      friend class Timer;
      friend class Timer::TimeVar;
    public:
      /// Initially set to 0.
      Time ();
      /// Set to the current time.
      void set_to_now ();
      /// Return the time now.
      static Time now ();

      /// Reset to 0.
      void clear ();

      /// \name Comparison to 0.
      /// \{
      /// Whether a field is not null.
      operator bool () const;
      /// Whether all fields are null.
      bool operator ! () const;
      /// \}

      /// \name Arithmetics.
      /// \{
      /// Accumulate \c rhs into \a this.
      Time& operator += (const Time& rhs);
      /// Return the sum of \a this and \a rhs.
      Time operator + (const Time& rhs) const;

      /// Subtract \c rhs from \a this.
      Time& operator -= (const Time& rhs);
      /// Return the subtraction of \a this and \a rhs.
      Time operator - (const Time& rhs) const;

      /// Divide times in place by \a n.
      Time& operator/= (unsigned n);
      /// Return the division of \a this and \a n.
      Time operator/ (unsigned n) const;
      /// \}

      /// \brief Comparison between two Times.
      /// This operators enables the use of std::min and std::max.
      /// It check only the \a total time, so it's a strict weak ordering.
      bool operator< (const Time& rhs) const;

    private:
      /// User time.
      long user;
      /// System time.
      long sys;
      /// Wall clock time.
      long wall;
    };

    /// An actual sub-timer.
    class TimeVar
    {
    public:
      friend class Timer;
      friend class Bencher;

      TimeVar ();
      /// The task is started.
      void start ();
      /// We activate a child.
      void start_child ();
      /// We just left a child.
      void stop_child ();
      /// The task is left.
      void stop ();

      /// Reset to 0.
      void clear ();

      /// \name Comparison to 0.
      /// \{
      /// Whether \a elapsed is not null.
      operator bool () const;
      /// Whether \a elapsed is null.
      bool operator ! () const;
      /// \}

      TimeVar operator+= (const TimeVar& rhs);
      TimeVar operator+ (const TimeVar& rhs) const;
      TimeVar operator/= (unsigned n);
      TimeVar operator/ (unsigned n) const;

      /// \brief Comparison between two TimeVars.
      /// This operators enables the use of std::min and std::max.
      /// It check only the \a total time, so it's a strict weak ordering.
      bool operator< (const TimeVar& rhs) const;


    private:
      /// Return the elapsed time since begin, and reset begin.
      Time lap ();

      /// The date of the latest activation.
      Time begin;

      /// The time spent in this TimeVar (all the start()-stop() intervals).
      Time elapsed;

      /// The time spent in this TimeVar and its children.
      Time cumulated;
    };

    /// Format timing results.
    std::ostream& print_time (long t, long total, std::ostream& o) const;
    /// Print statistics on a Time.
    /// \param s		title
    /// \param t		Time to report
    /// \param tot		total Time \a t is a part of
    /// \param o		output stream
    /// \param tree_mode	Activate tree mode display
    std::ostream& print_time (std::string s,
			      const Time& t, const Time& tot,
			      std::ostream& o,
			      const bool tree_mode) const;


  private:
    /// Store differents tasks you benched.
    task_map_type tasksmap;

    /// Storage for tree-like output.
    std::map<std::string, std::string> tab_to_disp;

    // Store tasks in order of creation
    std::list<std::string> task_ordered;

    /// Currently opened tasks, in order.
    std::stack<TimeVar*> tasks;

    /// Map for int and string couples (to call push (int)).
    std::map<int, std::string> intmap;

    /// Total time spent in the program.
    /// \see start (), stop ()
    TimeVar total;

    /// Stream onto which the results are dumped upon destruction.
    std::ostream* dump_stream;

    /// Number of clocks ticks per second, set according to the system
    /// timing function used.
    const long clocks_per_sec;
  };

  /// Dump \a t on \a o.
  std::ostream& operator<< (std::ostream& o, const Timer& t);

  /// A timer which starts at its construction, and stops at its destruction.
  class ScopedTimer
  {
  public:
    /// Start a sub-timer named \a key, register in \a timer.
    ScopedTimer (Timer& timer, const std::string& key);
    /// Stop this timer.
    ~ScopedTimer ();
  private:
    /// The host timer.
    Timer& timer_;
    /// The name of this task.
    const std::string key_;
  };

} // namespace misc

NAMESPACE_VCSN_END

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/timer.hxx>
#  if defined VAUCANSON
#   include <vaucanson/misc/timer.cc>
#  endif
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_MISC_TIMER_HH
