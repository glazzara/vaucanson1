// is_trim.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_TRIM_HXX
# define VCSN_ALGORITHMS_IS_TRIM_HXX

# include <vaucanson/algorithms/is_trim.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/algorithms/accessible.hh>

#include <algorithm>

namespace vcsn
{
  template<typename A, typename AI>
  bool
  is_trim (const Element<A, AI>& a)
  {
    int size = a.states ().size ();

    if (size == accessible_states (a).size ())
      return coaccessible_states (a).size () == size;
    return false;
  }
} // !vcsn

#endif // !VCSN_ALGORITHMS_IS_TRIM_HXX
