// suffix.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUFFIX_HXX
# define VCSN_ALGORITHMS_SUFFIX_HXX

# include <vaucanson/algorithms/suffix.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/automata/implementation/transpose_view.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/algorithms/is_trim.hh>

namespace vcsn {

  /*--------------.
  |  suffix_here  |
  `--------------*/

  template<typename A, typename AI>
  void
  suffix_here (Element<A, AI>& a)
  {
    precondition(is_realtime(a));
    precondition(is_trim(a));

    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES (automaton_t);

    for_all_states (i, a)
      a.set_initial (*i);
  }

  /*---------.
  |  suffix  |
  `---------*/

  template<typename A, typename AI>
  Element<A, AI>
  suffix (const Element<A, AI>& a)
  {
    Element<A, AI> res (a);
    suffix_here (res);
    return (res);
  }

} // vcsn

#endif // !VCSN_ALGORITHMS_SUFFIX_HXX
