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

}

NAMESPACE_VCSN_END

# if VAUCANSON
#  include <vaucanson/misc/bencher.cc>
# endif

#endif // !MISC_BENCHER_HXX_
