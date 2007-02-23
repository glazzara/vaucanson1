// functors.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_FUNCTORS_HH
# define VCSN_MISC_FUNCTORS_HH

# include <functional>
# include <utility>

namespace vcsn
{
  namespace misc
  {

    template <typename T>
    struct pair : public std::binary_function<T, T, std::pair<T, T > >
    {
	std::pair<T, T>	operator () (T x, T y) const;
    };


    template <typename T>
    struct discrepancy : public std::binary_function<T, T, std::pair<T, T> >
    {
	std::pair<T, T>	operator () (T x, T y) const;
    };

  } // End of namespace misc.
} // End of namespace vcsn.


#  include <vaucanson/misc/functors.hxx>

#endif // ! VCSN_MISC_FUNCTORS_HH
