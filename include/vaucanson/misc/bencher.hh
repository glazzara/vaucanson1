// bencher.hh: this file is part of the Vaucanson project.
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

#ifndef BENCHER_HH
# define BENCHER_HH

# include <vector>
# include <iostream>

# include <vaucanson/misc/timer.hh>

NAMESPACE_VCSN_BEGIN

namespace misc
{
  class Bencher
  {
  public:
    /// Add \a t to timers list.
    void push (const Timer& t);

    /// Display all timers + summary
    void print (std::ostream& o);

    void plot (std::ostream& o);

    /// Sum of all the timers.
    Timer sum() const;

    /// Arithmetic mean of all the timers.
    Timer mean() const;

    /// Smallest profile.
    Timer min() const;

    /// Largest profile.
    Timer max() const;

  private:
    /// Ensure they all use the same visual appearance.
    Timer prepare (Timer t) const;

    /// Collected timers
    std::vector<Timer> timers_;
  };
}

NAMESPACE_VCSN_END

# define BENCH_START(N, TIMER)			\
        Bencher b_;				\
	unsigned i_;				\
	for (i_ = 1;		\
	     i_ <= (N); ++i_, b_.push((TIMER)), (TIMER).clear())

# define BENCH_STOP()				\
 	b_.finalize ()

# define BENCH_PRINT(O)				\
 	b_.print ((O))

# define BENCH_PLOT(O)				\
 	b_.plot ((O))

# include <vaucanson/misc/bencher.hxx>

#endif // !BENCHER_HH
