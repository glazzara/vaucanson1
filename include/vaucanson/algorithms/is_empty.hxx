// is_empty.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_EMPTY_HXX
# define VCSN_ALGORITHMS_IS_EMPTY_HXX

# include <vaucanson/algorithms/is_empty.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <algorithm>

namespace vcsn {

  template<typename A, typename AI>
  bool
  is_empty(const Element<A, AI>& a)
  {
    return a.states ().size () == 0;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_IS_EMPTY_HXX
