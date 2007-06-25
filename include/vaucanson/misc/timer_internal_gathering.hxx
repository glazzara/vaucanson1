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
      return o << '(' << wall_ << ',' << user_ << ',' << sys_ << ')';
    }

    inline
    double
    TimeStamp::operator/ (unsigned int n) const
    {
      return 10 * (user_ + sys_) / (n == 0 ? 1.0 : n);
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

#endif //!VCSN_MISC_TIMER_INTERNAL_GATHERING_CC
