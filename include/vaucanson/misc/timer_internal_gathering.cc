// timer_internal_gathering.cc: this file is part of the Vaucanson project.
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
 ** \file misc/timer_internal_gathering.cc
 ** Implementation of data gathering classes declared in
 ** misc/timer_internal_gathering.hh.
 ** These classes are used in Timer (misc/timer.hh)
 */

#ifndef VCSN_MISC_TIMER_INTERNAL_GATHERING_CC
# define VCSN_MISC_TIMER_INTERNAL_GATHERING_CC

# include <sys/time.h>
# include <sys/resource.h>

# ifdef VAUCANSON
#  include <vaucanson/misc/timer_internal_gathering.hh>
#  include <vaucanson/misc/timer_internal_gathering.hxx>
# else
#  include "timer_internal_gathering.hh"
#  include "timer_internal_gathering.hxx"
# endif


/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# ifdef VAUCANSON
#  define INLINE_TIMER_CC inline
# else
#  define INLINE_TIMER_CC
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{
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
    }

    INLINE_TIMER_CC
    void
    TimeStamp::set_to_now ()
    {
      struct rusage ru;

      getrusage (RUSAGE_SELF, &ru);
      user_.set (ru.ru_utime);
      sys_.set (ru.ru_stime);
    }

    INLINE_TIMER_CC
    void
    TimeStamp::set_to_lap ()
    {
      struct rusage ru;

      getrusage (RUSAGE_SELF, &ru);

      user_ = (TimeVal (ru.ru_utime)) - user_;
      sys_  = (TimeVal (ru.ru_stime)) - sys_;
    }

    INLINE_TIMER_CC
    TimeStamp&
    TimeStamp::operator+= (const TimeStamp& rhs)
    {
      user_ += rhs.user_;
      sys_  += rhs.sys_;

      return *this;
    }

    INLINE_TIMER_CC  
    TimeStamp&
    TimeStamp::operator-= (const TimeStamp& rhs)
    {
      user_ -= rhs.user_;
      sys_  -= rhs.sys_;

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
} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC

#endif //!VCSN_MISC_TIMER_INTERNAL_GATHERING_CC
