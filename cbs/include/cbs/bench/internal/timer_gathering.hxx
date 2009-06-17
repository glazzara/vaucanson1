// timer_gathering.hxx: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 The CBS Authors.
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
 ** \file include/cbs/bench/internal/timer_gathering.hxx
 ** Inline methods of data gathering classes declared in timer_gathering.hh.
 ** These classes are used in Timer (../timer.hh)
 */

#ifndef BENCH_INTERNAL_TIMER_GATHERING_HXX
# define BENCH_INTERNAL_TIMER_GATHERING_HXX

// STL
# include <iostream>
# include <iomanip>

// Internal
# include <cbs/bench/internal/timer_gathering.hh>


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
  long
  TimeVal::to_ms () const
  {
    return tv_usec / 1000 + 1000 * tv_sec;
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
    return o << '(' << user_ + cuser_ << ", " << sys_ + csys_<< ", " << wall_ << ')';
  }

  inline
  bool
  TimeStamp::operator< (const TimeStamp& rhs) const
  {
    return user_ + cuser_ + sys_ + csys_
      < rhs.user_ + rhs.cuser_ + rhs.sys_ + rhs.csys_;
  }

  inline
  long
  TimeStamp::to_ms () const
  {
    return user_.to_ms () + sys_.to_ms () + cuser_.to_ms () + csys_.to_ms ();
  }

  inline
  long
  TimeStamp::user_to_ms () const
  {
    return user_.to_ms ();
  }

  inline
  long
  TimeStamp::system_to_ms () const
  {
    return sys_.to_ms ();
  }

  inline
  long
  TimeStamp::user_children_to_ms () const
  {
    return cuser_.to_ms ();
  }

  inline
  long
  TimeStamp::system_children_to_ms () const
  {
    return csys_.to_ms ();
  }

  inline
  long
  TimeStamp::wall_to_ms () const
  {
    return wall_.to_ms ();
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


#endif //!BENCH_INTERNAL_TIMER_GATHERING_HXX
