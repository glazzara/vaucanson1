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
    std::ostream& print (std::ostream& o) const;

    void plot (std::ostream& o) const;

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


  /// Dump \a b on \a o.
  std::ostream& operator<< (std::ostream& o, const Bencher& t);
}

NAMESPACE_VCSN_END

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/bencher.hxx>
#  if VAUCANSON
#   include <vaucanson/misc/bencher.cc>
#  endif
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !BENCHER_HH
