// functors.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_MISC_FUNCTORS_HXX
# define VCSN_MISC_FUNCTORS_HXX

# include <vaucanson/misc/functors.hh>
# include <algorithm>

namespace vcsn
{
  namespace misc
  {

    template <typename T>
    std::pair<T, T> pair<T>::operator () (T x, T y) const
    {
      return std::pair<T, T> (x, y);
    }


    template <typename T>
    std::pair<T, T> discrepancy<T>::operator () (T x, T y) const
    {
      T	left = std::max<T> (0, x - y);
      T	right = std::max<T> (0, y - x);

      return std::pair<T, T> (left, right);
    }

  } // End of namespace misc.
} // End of namespace vcsn.

#endif // ! VCSN_MISC_FUNCTORS_HXX
