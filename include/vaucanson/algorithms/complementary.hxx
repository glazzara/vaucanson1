// complementary.hxx
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


# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complementary(Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for (state_iterator i = e.states().begin(); i != e.states().end(); i++)
      if (e.is_final(*i))
	e.unset_final(*i);
      else if (!e.is_initial(*i))
	e.set_final(*i);
  }

  template <typename A, typename T>
  Element<A, T>
  auto_complementary(const Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
  
    automaton_t work(e);
    work.emancipate();
    auto_in_complementary(work);
    return work;
  }

} // vcsn
