// factor.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_FACTOR_HXX
# define VCSN_ALGORITHMS_FACTOR_HXX

# include <vaucanson/algorithms/factor.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/automata/implementation/transpose_view.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  /*--------------.
  |  factor_here  |
  `--------------*/

  template<typename A, typename AI>
  void
  factor_here (Element<A, AI>& a)
  {
    // FIXME: Missing preconditions is_realtime and is_trim

    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES (automaton_t);

    for_all_states (i, a)
      {
	a.set_initial (*i);
	a.set_final (*i);
      }
  }

  /*---------.
  |  factor  |
  `---------*/

  template<typename A, typename AI>
  Element<A, AI>
  factor (const Element<A, AI>& a)
  {
    Element<A, AI> res (a);
    factor_here (res);
    return (res);
  }

} // vcsn

#endif // !VCSN_ALGORITHMS_FACTOR_HXX
