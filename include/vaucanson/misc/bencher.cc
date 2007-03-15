/*
 * Copyright (C) 2007  The Vaucanson Group.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

/**
 ** \file misc/bencher.cc
 ** \brief Implementation for misc/bencher.hh.
 */

#ifndef VCSN_MISC_BENCHER_CC
# define VCSN_MISC_BENCHER_CC

# include <vaucanson/misc/bencher.hh>

/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# if VAUCANSON
#  define INLINE_BENCHER_CC inline
# else
#  define INLINE_BENCHER_CC
# endif


NAMESPACE_VCSN_BEGIN

namespace misc
{

  INLINE_BENCHER_CC
  Timer
  Bencher::sum () const
  {
    Timer res;
    for (std::vector< Timer >::const_iterator i = timers_.begin ();
	 i != timers_.end (); ++i)
      res += *i;
    return res;
  }

  INLINE_BENCHER_CC
  Timer
  Bencher::mean () const
  {
    precondition (!timers_.empty());
    return sum() / timers_.size();
  }

  INLINE_BENCHER_CC
  Timer
  Bencher::min () const
  {
    precondition (!timers_.empty());
    return *std::min_element(timers_.begin (), timers_.end ());
  }

  INLINE_BENCHER_CC
  Timer
  Bencher::max () const
  {
    precondition (!timers_.empty());
    return *std::max_element(timers_.begin (), timers_.end ());
  }

  INLINE_BENCHER_CC
  Timer
  Bencher::prepare (Timer t) const
  {
    precondition (!timers_.empty());
    t.tab_to_disp = timers_.begin()->tab_to_disp;
    t.task_ordered = timers_.begin()->task_ordered;
    return t;
  }

  INLINE_BENCHER_CC
  std::ostream&
  Bencher::print (std::ostream& o) const
  {
    const char* line = "-------------------------";
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << line << std::endl
	<< (*i);
    }
    o << std::endl
      << line << " SUMMARY " << line << std::endl
      << line << " Arithmetic means" << std::endl << prepare(mean())
      // << line << " Sum"              << std::endl << prepare(sum())
      << line << " Min"              << std::endl << prepare(min())
      << line << " Max"              << std::endl << prepare(max());
    return o;
  }

  INLINE_BENCHER_CC
  void
  Bencher::plot (std::ostream& o) const
  {
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << (float) i->total.elapsed.wall / i->clocks_per_sec
	<< std::endl;
    }
  }


  /*--------------------------.
  | Free standing functions.  |
  `--------------------------*/

  /// Dump \a t on \a o.
  INLINE_BENCHER_CC
  std::ostream&
  operator<< (std::ostream& o, const Bencher& t)
  {
    return t.print (o);
  }

}// namespace misc

NAMESPACE_VCSN_END


# if TEST_BENCHER

# include <iostream>
# include <vaucanson/misc/bencher.hh>
# include <fstream>

# define msleep(MilliSecond) usleep(MilliSecond * 1000)

/// Test the bencher.
int
main ()
{
#  if defined VAUCANSON
  using namespace vcsn;
#  endif

  misc::Bencher b;
  misc::Timer timer;
  enum timevar
    {
      One = 1,
      Two,
      Three,
      Four
    };

  std::ofstream outfile ("test.plot",
			 std::ofstream::out | std::ofstream::trunc);

  for (int i = 0; i < 10; i++)
  {
    timer.clear();

    timer.name (One, "One");
    timer.name (Two, "Two");
    timer.name (Three, "Three");
    timer.name (Four, "Four");

    timer.start ();

    timer.push (One);
    msleep (i * 10);

    timer.push ("Two");
    msleep (i * 10);
    timer.push ("Four");
    msleep (i * 10);

    timer.pop ("Four");
    timer.pop ("Two");
    timer.pop (1);

    timer.push ("Three");
    msleep (i * 10);
    timer.pop (Three);

    timer.stop ();
    b.push (timer);
  }
  b.print(std::cerr);
  b.plot(outfile);

  outfile.close();
  return 0;
}

# endif // TEST_BENCHER

#endif // !VCSN_MISC_BENCHER_CC

/// Local Variables:
/// compile-command: "g++ -I ../.. -I ../../../_build/include -DTEST_BENCHER timer.cc bencher.cc -o test-bencher -Wall && ./test-bencher"
/// End:
