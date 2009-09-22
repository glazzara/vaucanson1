// timer_gathering.cc: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2008, 2009 The CBS authors.
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
 ** \file lib/timer_gathering.cc
 ** Implementation of data gathering classes declared in
 ** include/cbs/bench/internal/timer_gathering.hh.
 ** These classes are used in Timer (include/cbs/bench/timer.hh)
 */

// UNIX
#include <sys/time.h>
#include <sys/resource.h>

// Internal
#include <cbs/bench/internal/timer_gathering.hh>


#define INLINE_TIMER_CC


namespace timer
{
  /*-----------------.
  | Timer::TimeVal.  |
  `-----------------*/

  INLINE_TIMER_CC
  std::ostream&
  TimeVal::print (std::ostream&  o,
		  time_unit      u) const
  {
    switch (u)
    {
    case TIME_DEFAULT:
      if (ms () < 200)
	return o << ms () << "ms";
      if (s () < 300)
	return o << s () << "s ";
      if (m () < 60)
	return o << m () << "m ";
      return o << h () << "h ";
    case TIME_H:
      return o << h () << "h ";
    case TIME_M:
      return o << m () << "m ";
    case TIME_S:
      return o << s () << "s ";
    default:
      return o << ms () << "ms";
    }
  }

  /*-------------------.
  | Timer::TimeStamp.  |
  `-------------------*/

  INLINE_TIMER_CC
  void
  TimeStamp::clear ()
  {
    user_.clear ();
    sys_.clear ();
    cuser_.clear ();
    csys_.clear ();
    wall_.clear();
  }

  INLINE_TIMER_CC
  void
  TimeStamp::set_to_now ()
  {
    struct rusage ru;

    getrusage (RUSAGE_SELF, &ru);
    user_.set (ru.ru_utime);
    sys_.set (ru.ru_stime);

    getrusage (RUSAGE_CHILDREN, &ru);
    cuser_.set (ru.ru_utime);
    csys_.set (ru.ru_stime);

    struct timeval wall;
    gettimeofday (&wall, 0);

    wall_.set (wall);
  }

  INLINE_TIMER_CC
  void
  TimeStamp::set_to_lap ()
  {
    struct rusage ru;

    getrusage (RUSAGE_SELF, &ru);

    user_ = (TimeVal (ru.ru_utime)) - user_;
    sys_  = (TimeVal (ru.ru_stime)) - sys_;

    getrusage (RUSAGE_CHILDREN, &ru);

    cuser_ = (TimeVal (ru.ru_utime)) - cuser_;
    csys_  = (TimeVal (ru.ru_stime)) - csys_;

    struct timeval wall;
    gettimeofday (&wall, 0);

    wall_ = (TimeVal (wall)) - wall_;
  }

  INLINE_TIMER_CC
  TimeStamp&
  TimeStamp::operator+= (const TimeStamp& rhs)
  {
    user_ += rhs.user_;
    sys_  += rhs.sys_;
    cuser_ += rhs.cuser_;
    csys_  += rhs.csys_;
    wall_ += rhs.wall_;

    return *this;
  }

  INLINE_TIMER_CC
  TimeStamp&
  TimeStamp::operator-= (const TimeStamp& rhs)
  {
    user_ -= rhs.user_;
    sys_  -= rhs.sys_;
    cuser_ -= rhs.cuser_;
    csys_  -= rhs.csys_;
    wall_  -= rhs.wall_;

    return *this;
  }

  /*--------------.
  | Timer::Task.  |
  `--------------*/

  INLINE_TIMER_CC
  Task::Task (const Task& task)
  {
    id_    = task.id_;
    name_  = task.name_;
    calls_ = task.calls_;
  }

  /*--------------.
  | Timer::Call.  |
  `--------------*/

  INLINE_TIMER_CC
  Call::Call (unsigned int called)
  {
    count_  = 0;
    called_ = called;

    self_.clear ();
    total_.clear ();
  }

  INLINE_TIMER_CC
  Call&
  Call::operator+= (const Call& call)
  {
    total_ += call.total_;
    self_  += call.self_;

    count_ += call.count_;

    return *this;
  }

  INLINE_TIMER_CC
  void
  Call::add (const StackedCall&       call)
  {
    total_ += call.total_;

    self_  -= call.children_;
    self_  += call.total_;

    ++count_;
  }

} // namespace timer


#undef INLINE_TIMER_CC
