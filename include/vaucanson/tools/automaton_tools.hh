// automaton_tools.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_AUTOMATON_TOOLS_HH
# define VCSN_TOOLS_AUTOMATON_TOOLS_HH

# include <algorithm>
# include <deque>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/misc/random.hh>

namespace vcsn
{
  namespace tools
  {
    template <class Auto>
    std::deque<typename Auto::hstate_t>
    choose_n_states(const Auto& a, unsigned n)
    {
      typedef typename Auto::hstate_t hstate_t;

      std::deque<typename Auto::hstate_t> s;
      std::insert_iterator<std::deque<hstate_t> > i(s, s.begin());
      misc::random::sample_n(hstate_t(),
			     a.states().begin(),
			     a.states().end(),
			     i,
			     n);
      return s;
    }
  } // tools
} // vcsn

#endif // ! VCSN_TOOLS_AUTOMATON_TOOLS_HH
