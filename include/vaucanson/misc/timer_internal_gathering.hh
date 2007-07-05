// timer_internal_gathering.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_MISC_TIMER_INTERNAL_GATHERING_HH
# define VCSN_MISC_TIMER_INTERNAL_GATHERING_HH

/**
 ** \file misc/timer_internal_gathering.hh
 ** This file contains classes used by Timer in timer.hh to gather
 ** data during timer execution.
 ** Classes declared here are not meant to be used on their own.
 ** See timer.hh for information on how to use the Timer class to time
 ** nested tasks.
 */

# include <stack>
# include <vector>
# include <map>
# include <list>
# include <string>
# include <iosfwd>

# ifdef VAUCANSON
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
  class Timer;

  namespace timer
  {
    // Internal Time representation
    class TimeStamp;

    // Data collection classes
    class Task;
    class Call;
    class StackedCall;

    typedef std::map<const std::string, int> task_names_map;
    typedef std::vector<Task> task_vector;
    typedef std::map<int, Call> call_map;
    typedef std::stack<StackedCall> call_stack;


    // Friends of TimeStamp
    class GraphCall;
    class GraphComponent;
    class GraphTask;

    class TimeStamp
    {
      friend class misc::Timer;
      friend class Call;
      friend class StackedCall;
      friend class GraphCall;
      friend class GraphComponent;
      friend class GraphTask;

      TimeStamp ();

      // Set to the current time
      void set_to_now ();

      // Set to the difference between the current time and the time
      // previously set.time_.set_to_lap();
      void set_to_lap ();

      // Set internal values to 0;
      void clear ();

      std::ostream& print (std::ostream& o) const;

      TimeStamp& operator+= (const TimeStamp& rhs);
      TimeStamp& operator-= (const TimeStamp& rhs);

      // Returns the divison of the total CPU time by n
      double operator/ (unsigned int n) const;

      // Ordering using CPU time.
      bool operator< (const TimeStamp& rhs) const;

    private:
      clock_t   wall_;
      clock_t   user_;
      clock_t   sys_;
    };

    // Data collection classes
    class Task
    {
    public:
      friend class misc::Timer;

      Task ();

      Task (const Task& task);

      // Create a new task.
      Task (const std::string&  name,
            unsigned int        id);

      // Free call list upon destruction.
      ~Task ();

      // Add the call if it doesn't exist.  Return the call to the
      // called task.
      Call& call (unsigned int called);

    private:
      std::string       name_;
      unsigned int      id_;
      call_map          calls_;
    };

    class Call
    {
    public:
      friend class misc::Timer;
      friend class Task;

      // Initialize upon creation.
      explicit Call (unsigned int called = 0);

      // Sum up the call stats;
      Call& operator+= (const Call& call);

    private:
      // Adds the calculated time of a task instance to the associated
      // call on Timer::pop()
      void add (const StackedCall&      call);


      // Total time of the called task and its children.
      TimeStamp total_;

      // Time of the called task itself only.
      TimeStamp self_;

      // Number of calls with the same calling and called tasks.
      unsigned int count_;

      unsigned int called_;
    };

    class StackedCall
    {
    public:
      friend class misc::Timer;
      friend class Task;
      friend class Call;

      explicit StackedCall (unsigned int called = 0);
      StackedCall ();

    private:
      TimeStamp    total_;
      TimeStamp    children_;

      unsigned int called_;
    };
  } // namespace timer
} // namespace misc

NAMESPACE_VCSN_END

// Include full definition of all classes.
# ifdef VAUCANSON
#  include <vaucanson/misc/timer.hh>
#  include <vaucanson/misc/timer_internal_graph.hh>
#  include <vaucanson/misc/timer_internal_gathering.hh>
# else
#  include "timer.hh"
#  include "timer_internal_graph.hh"
#  include "timer_internal_gathering.hh"
# endif

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  ifdef VAUCANSON
#   include <vaucanson/misc/timer_internal_gathering.hxx>
#  else
#   include "timer_internal_gathering.hxx"
#  endif
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_MISC_TIMER_INTERNAL_GATHERING_HH
