// transpose.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_TRANSPOSE_HXX
# define VCSN_ALGORITHMS_TRANSPOSE_HXX

#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/automata/implementation/transpose_view.hh>
#include <vaucanson/automata/concept/copy.hh>

namespace vcsn
{
  template<typename A, typename AI1, typename AI2>
  void
  transpose(Element<A, AI1>& dst, const Element<A, AI2>& from)
  {
    TIMER_SCOPED("transpose");
    typedef Element<A, AI1> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    auto_copy(dst, transpose_view(from));
    // transpose_view is still a quick transposition without label transpose.
    // transpose now inverts all transitions of the dst_ automaton.
    for_all_transitions(e, dst)
      dst.series_of(*e).transpose();
  }

  template<typename A, typename AI>
  Element<A, AI>
  transpose(const Element<A, AI>& from)
  {
    Element<A, AI> dst(from.structure());
    transpose(dst, from);
    return dst;
  }

} //vcsn

#endif // ! VCSN_ALGORITHMS_TRANSPOSE_HXX
