// timer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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
 ** \file misc/timer.hxx
 ** \brief Inline methods for misc/timer.hh.
 */

#ifndef VCSN_MISC_TIMER_HXX
# define VCSN_MISC_TIMER_HXX

# include <vaucanson/misc/timer.hh>
# include <vaucanson/misc/contract.hh>

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /*--------.
  | Timer.  |
  `--------*/

  inline
  void
  Timer::push (const int i)
  {
    precondition (intmap.find (i) != intmap.end ());
    push (intmap[i]);
  }

  inline
  void
  Timer::pop (const std::string& task_name)
  {
    precondition (tasksmap[task_name] == tasks.top ());
    pop ();
  }

  inline
  void
  Timer::pop (const int i)
  {
    pop (intmap[i]);
  }


  inline
  void
  Timer::print_on_destruction (std::ostream& o)
  {
    dump_stream = &o;
  }

  inline
  void
  Timer::start ()
  {
    total.start ();
  }

  inline
  void
  Timer::stop ()
  {
    total.stop ();
  }

  inline
  void
  Timer::clear ()
  {
    precondition(this->tasks.empty ());

    this->tasksmap.clear ();
    this->intmap.clear ();
    this->total.clear ();
    this->tab_to_disp.clear ();
    this->task_ordered.clear ();
  }

  // Fixme
  inline
  Timer::TimeVar&
  Timer::operator[] (std::string s)
  {
    Timer::TimeVar* tmp = this->tasksmap[s];
    Timer::TimeVar* res = new Timer::TimeVar(*tmp);
    return *res;
  }


  /*--------------.
  | Timer::Time.  |
  `--------------*/

  inline
  Timer::Time::Time ()
    : user (0), sys (0), wall (0)
  { }

  inline
  Timer::Time::operator bool () const
  {
    return (false
	    || wall
	    || user
	    || sys);
  }

  inline
  bool
  Timer::Time::operator ! () const
  {
    return (true
	    && !wall
	    && !user
	    && !sys);
  }

  inline
  Timer::Time&
  Timer::Time::operator+= (const Time& lhs)
  {
    wall += lhs.wall;
    user += lhs.user;
    sys  += lhs.sys;
    return *this;
  }

  inline
  Timer::Time
  Timer::Time::operator+ (const Time& lhs) const
  {
    Timer::Time res = *this;
    return res += lhs;
  }

  inline
  Timer::Time&
  Timer::Time::operator-= (const Time& lhs)
  {
    wall -= lhs.wall;
    user -= lhs.user;
    sys  -= lhs.sys;
    return *this;
  }

  inline
  Timer::Time
  Timer::Time::operator- (const Time& lhs) const
  {
    Timer::Time res = *this;
    return res -= lhs;
  }

  inline
  Timer::Time&
  Timer::Time::operator/= (const long n)
  {
    wall /= n;
    user /= n;
    sys  /= n;
    return *this;
  }

  inline
  Timer::Time
  Timer::Time::operator/ (const long n) const
  {
    Timer::Time res = *this;
    return res /= n;
  }

  inline
  Timer::Time
  Timer::Time::min (const Timer::Time& rhs) const
  {
    Timer::Time res = *new Timer::Time ();
    res.wall = std::min (this->wall, rhs.wall);
    res.user = std::min (this->user, rhs.user);
    res.sys = std::min (this->sys, rhs.sys);
    return res;
  }

  inline
  Timer::Time
  Timer::Time::max (const Timer::Time& rhs) const
  {
    Timer::Time res = *new Timer::Time ();
    res.wall = std::max (this->wall, rhs.wall);
    res.user = std::max (this->user, rhs.user);
    res.sys = std::max (this->sys, rhs.sys);
    return res;
  }

  /*--------------.
  | ScopedTimer.  |
  `--------------*/

  inline
  ScopedTimer::ScopedTimer (Timer& timer, const std::string& key)
    : timer_ (timer), key_ (key)
  {
    timer_.push (key_);
  }

  inline
  ScopedTimer::~ScopedTimer ()
  {
    timer_.pop (key_);
  }

} // namespace misc

NAMESPACE_VCSN_END

# if VAUCANSON
#  include <vaucanson/misc/timer.cc>
# endif

#endif // !VCSN_MISC_TIMER_HXX
