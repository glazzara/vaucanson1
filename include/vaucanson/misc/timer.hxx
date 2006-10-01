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
