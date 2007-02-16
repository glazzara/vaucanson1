// bencher.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2007 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef MISC_BENCHER_HXX_
# define MISC_BENCHER_HXX_

# include <vaucanson/misc/bencher.hh>

NAMESPACE_VCSN_BEGIN

namespace misc
{

  void
  Bencher::push (const Timer& t)
  {
    timers_.push_back (t);
  }

  void
  Bencher::print (std::ostream& o)
  {
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << "------------------------" << std::endl;
      o << (*i);
    }
    o<< std::endl << "-------------------------" << std::endl;
    o << "        SUMMARY" << std::endl;
    o << "-------------------------" << std::endl;
    o << "ARITHMETIC MEANS" << std::endl
      << std::endl;
    o << prepare(mean());
    o << "-------------------------" << std::endl;
    o << "MIN" << std::endl
      << std::endl;
    o << prepare(min());
    o << "-------------------------" << std::endl;
    o << "MAX" << std::endl
      << std::endl;
    o << prepare(max());
  }

  void
  Bencher::plot (std::ostream& o)
  {
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << (float) i->total.elapsed.wall / i->clocks_per_sec
	<< std::endl;
    }
  }

  Timer
  Bencher::sum () const
  {
    Timer res;
    // Summarize total times by classic mean.
    for (std::vector< Timer >::const_iterator i = this->timers_.begin ();
	 i != this->timers_.end (); ++i)
      res += *i;
    return res;
  }

  Timer
  Bencher::mean () const
  {
    precondition (!timers_.empty());
    return sum() / timers_.size();
  }

  Timer
  Bencher::min () const
  {
    precondition (!timers_.empty());
    std::vector< Timer >::const_iterator i = timers_.begin ();
    Timer res = *i;
    for (/* nothing. */; i != this->timers_.end (); ++i)
      res = res.min (*i);
    return res;
  }

  Timer
  Bencher::max () const
  {
    precondition (!timers_.empty());
    std::vector< Timer >::const_iterator i = timers_.begin ();
    Timer res = *i;
    for (/* nothing. */; i != this->timers_.end (); ++i)
      res = res.max (*i);
    return res;
  }

  Timer
  Bencher::prepare (Timer t) const
  {
    precondition (!timers_.empty());
    t.tab_to_disp = timers_.begin()->tab_to_disp;
    t.task_ordered = timers_.begin()->task_ordered;
    return t;
  }

}

NAMESPACE_VCSN_END

#endif // !MISC_BENCHER_HXX_
