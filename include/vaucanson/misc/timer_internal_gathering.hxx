// timer_internal_gathering.hxx: this file is part of the Vaucanson project.
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
 ** \file misc/timer_internal_gathering.hxx
 ** Inline methods of data gathering classes declared in
 ** misc/timer_internal_gathering.hh.
 ** These classes are used in Timer (misc/timer.hh)
 */

#ifndef VCSN_MISC_TIMER_INTERNAL_GATHERING_HXX
# define VCSN_MISC_TIMER_INTERNAL_GATHERING_HXX

# include <iostream>
# include <iomanip>

# ifdef VAUCANSON
#  include <vaucanson/misc/timer_internal_gathering.hh>
# else
#  include "timer_internal_gathering.hh"
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{
  namespace timer
  {
    /*-----------------.
    | Timer::TimeVal.  |
    `-----------------*/

    inline
    TimeVal::TimeVal ()
      : tv_sec  (0),
	tv_usec (0)
    {
    }

    inline
    TimeVal::TimeVal (int i)
      : tv_sec  (i),
	tv_usec (0)
    {
    }

    inline
    TimeVal::TimeVal (double d)
      : tv_sec  (long (d)),
	tv_usec (long (d * 1000000) % 1000000)
    {
    }


    inline
    TimeVal::TimeVal (const TimeVal& tv)
      : tv_sec  (tv.tv_sec),
	tv_usec (tv.tv_usec)
    {
    }

    inline
    TimeVal::TimeVal (const timeval& tv)
      : tv_sec  (tv.tv_sec),
	tv_usec (tv.tv_usec)
    {
    }

    inline
    TimeVal
    TimeVal::operator+ (const TimeVal& tv) const
    {
      TimeVal res;
      res.tv_sec = tv.tv_sec + tv_sec;
      res.tv_usec = tv.tv_usec + tv_usec;
      res.tv_sec += res.tv_usec / 1000000;
      res.tv_usec = res.tv_usec % 1000000;
      return res;
    }

    inline
    TimeVal
    TimeVal::operator- (const TimeVal& tv) const
    {
      TimeVal res (*this);
      res.tv_sec -= tv.tv_sec;
      res.tv_usec -= tv.tv_usec;
      res.tv_sec += res.tv_usec / 1000000;
      res.tv_usec = res.tv_usec % 1000000;
      return res;
    }

    inline
    TimeVal&
    TimeVal::operator+= (const TimeVal& tv)
    {
      tv_sec += tv.tv_sec;
      tv_usec += tv.tv_usec;
      tv_sec += tv_usec / 1000000;
      tv_usec = tv_usec % 1000000;
      return *this;
    }

    inline
    TimeVal&
    TimeVal::operator-= (const TimeVal& tv)
    {
      tv_sec -= tv.tv_sec;
      tv_usec -= tv.tv_usec;
      tv_sec += tv_usec / 1000000;
      tv_usec = tv_usec % 1000000;
      return *this;
    }

    inline
    TimeVal&
    TimeVal::operator= (const TimeVal& tv)
    {
      if (this == &tv)
	return *this;
      tv_sec = tv.tv_sec;
      tv_usec = tv.tv_usec;
      return *this;
    }

    inline
    TimeVal&
    TimeVal::operator/= (double d)
    {
      double t;

      t = tv_sec / d;
      tv_sec = long (t);
      tv_usec = long (tv_usec / d + (t - tv_sec) * 1000000);
      tv_sec += tv_usec / 1000000;
      tv_usec = tv_usec % 1000000;
      return *this;
    }

    inline
    TimeVal
    TimeVal::operator/ (double d) const
    {
      TimeVal res;
      double t;

      t = tv_sec / d;
      res.tv_sec = long (t);
      res.tv_usec = long (tv_usec / d + (t - res.tv_sec) * 1000000);
      return res;
    }

    inline
    bool
    TimeVal::operator< (const TimeVal& tv) const
    {
      return (tv_sec == tv.tv_sec ?
	      tv_usec < tv.tv_usec :
	      tv_sec < tv.tv_sec);
    }

    inline
    bool
    TimeVal::operator> (const TimeVal& tv) const
    {
      return (tv_sec == tv.tv_sec ?
	      tv_usec > tv.tv_usec :
	      tv_sec > tv.tv_sec);
    }

    inline
    bool
    TimeVal::operator== (const TimeVal& tv) const
    {
      return (tv_sec == tv.tv_sec && tv_usec == tv.tv_usec);
    }


    inline
    void
    TimeVal::clear ()
    {
      tv_sec = 0;
      tv_usec = 0;
    }

    inline
    void
    TimeVal::set (const timeval& tv)
    {
      tv_sec = tv.tv_sec;
      tv_usec = tv.tv_usec;
    }

    inline
    double
    TimeVal::us () const
    {
      return tv_usec + 1000000 * tv_sec;
    }

    inline
    double
    TimeVal::ms () const
    {
      return double (tv_usec) / 1000 + 1000 * tv_sec;
    }

    inline
    double
    TimeVal::s () const
    {
      return double (tv_usec) / 1000000 + tv_sec;
    }

    inline
    double
    TimeVal::m () const
    {
      return (double (tv_usec) / 1000000 + double (tv_sec)) / 60;
    }

    inline
    double
    TimeVal::h () const
    {
      return (double (tv_usec) / 1000000 + double (tv_sec)) / 3600;
    }


    /*--------------------------.
    | Free standing functions.  |
    `--------------------------*/

    inline
    std::ostream&
    operator<< (std::ostream&  o,
		const TimeVal& tv)
    {
      return tv.print (o);
    }

    inline
    std::ostream& print_time (std::ostream&   o,
                              timer::TimeVal& time,
                              time_unit       u)
    {
      return time.print (o, u);
    }

    /*-------------------.
    | Timer::TimeStamp.  |
    `-------------------*/

    inline
    TimeStamp::TimeStamp ()
    {
    }

    inline
    std::ostream&
    TimeStamp::print (std::ostream& o) const
    {
      return o << '(' << user_ << ", " << sys_ << ')';
    }

    inline
    bool
    TimeStamp::operator< (const TimeStamp& rhs) const
    {
      return user_ + sys_ < rhs.user_ + rhs.sys_;
    }

    /*--------------.
    | Timer::Task.  |
    `--------------*/

    inline
    Task::Task ()
    {
    }

    inline
    Task::Task (const std::string& name,
		unsigned int       id)
      : name_ (name),
        id_   (id)
    {
    }

    inline
    Task::~Task ()
    {
    }

    inline
    Call&
    Task::call(unsigned int called)
    {
      return calls_[called];
    }

    /*---------------------.
    | Timer::StackedCall.  |
    `---------------------*/

    inline
    StackedCall::StackedCall ()
    {
      total_.set_to_now ();
      children_.clear ();
    }

    inline
    StackedCall::StackedCall (unsigned int called)
    {
      called_ = called;
      total_.set_to_now ();
      children_.clear ();
    }
  } // namespace timer
} // namespace misc

NAMESPACE_VCSN_END

#endif //!VCSN_MISC_TIMER_INTERNAL_GATHERING_HXX
