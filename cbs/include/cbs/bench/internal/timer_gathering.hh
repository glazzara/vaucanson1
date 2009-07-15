// timer_gathering.hh: this file is part of the CBS project.
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

#ifndef BENCH_INTERNAL_TIMER_GATHERING_HH
# define BENCH_INTERNAL_TIMER_GATHERING_HH

/**
 ** \file include/cbs/bench/internal/timer_gathering.hh
 ** This file contains classes used by Timer in timer.hh to gather
 ** data during timer execution.
 ** Classes declared here are not meant to be used on their own.
 ** See timer.hh for information on how to use the Timer class to time
 ** nested tasks.
 */

// STL
# include <stack>
# include <vector>
# include <map>
# include <list>
# include <string>
# include <iosfwd>
# include <cassert>

// UNIX
# include <sys/time.h>
# include <sys/resource.h>


namespace timer
{
  class Timer;

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


  // Time units for printing
  enum time_unit
    {
      TIME_DEFAULT,
      TIME_H,
      TIME_M,
      TIME_S,
      TIME_MS
    };

  struct TimeVal
  {
    TimeVal ();

    // \param d: Time in seconds.
    TimeVal (double d);
    // \param i: Time in seconds.
    TimeVal (int i);
    TimeVal (const TimeVal& tv);
    TimeVal (const timeval& tv);

    TimeVal operator+ (const TimeVal& tv) const;
    TimeVal operator- (const TimeVal& tv) const;
    TimeVal& operator+= (const TimeVal& tv);
    TimeVal& operator-= (const TimeVal& tv);
    TimeVal& operator= (const TimeVal& tv);

    TimeVal& operator/= (double d);
    TimeVal operator/ (double d) const;

    bool operator== (const TimeVal& tv) const;
    bool operator< (const TimeVal& tv) const;
    bool operator> (const TimeVal& tv) const;

    double us () const;
    double ms () const;
    double s () const;
    double m () const;
    double h () const;

    long to_ms () const;

    std::ostream& print (std::ostream&  o,
			 time_unit      u = TIME_DEFAULT) const;

    void clear ();
    void set (const timeval&);

    long tv_sec;
    long tv_usec;
  };

  // Print time in given unit
  std::ostream& print_time (std::ostream&   o,
			    timer::TimeVal& time,
			    time_unit       u = TIME_DEFAULT);

  class TimeStamp
  {
    friend class Timer;
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

    // Get the total time in ms
    long to_ms () const;

    // Get the total user time in ms
    long user_to_ms () const;

    // Get the total system time in ms
    long system_to_ms () const;

    // Get the total user time in ms for children processes
    long user_children_to_ms () const;

    // Get the total system time in ms for children processes
    long system_children_to_ms () const;

    // Get the total system time in ms
    long wall_to_ms () const;

    std::ostream& print (std::ostream& o) const;

    TimeStamp& operator+= (const TimeStamp& rhs);
    TimeStamp& operator-= (const TimeStamp& rhs);

    // Ordering using CPU time.
    bool operator< (const TimeStamp& rhs) const;

  private:
    TimeVal   user_;  // Time spent in user code
    TimeVal   sys_;   // Time spent in system calls
    TimeVal   cuser_; // Time spent in user code (children processes)
    TimeVal   csys_;  // Time spent in system calls (children processes)
    TimeVal   wall_;  // Wall clock (observed time)
  };

  // Data collection classes
  class Task
  {
  public:
    friend class Timer;

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
    friend class Timer;
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
    friend class Timer;
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

# include <cbs/bench/internal/timer_gathering.hxx>

#endif // !BENCH_INTERNAL_TIMER_GATHERING_HH
