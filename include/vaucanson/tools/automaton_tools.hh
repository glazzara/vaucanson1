// automaton_tools.hh
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef TOOLS_AUTOMATON_TOOLS_HH
# define TOOLS_AUTOMATON_TOOLS_HH

# include <algorithm>
# include <deque>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/misc/random.hh>

namespace vcsn {

  template <class Auto>
  std::deque<hstate_t>
  choose_n_states(const Auto& a, unsigned n)
  {
    std::deque<hstate_t> s;
    std::insert_iterator<std::deque<hstate_t> > i(s, s.begin());
    vcsn::misc::random_sample_n(a.states().begin(), 
				a.states().end(), 
				i,
				n);
    return s;
  }

} // vcsn

#endif // TOOLS_AUTOMATON_TOOLS_HH
