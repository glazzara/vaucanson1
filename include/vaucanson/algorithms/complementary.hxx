// complementary.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_COMPLEMENTARY_HXX
# define VCSN_ALGORITHMS_COMPLEMENTARY_HXX 

# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complementary(Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    precondition(is_complete(e) && is_deterministic(e));
    for_each_state(i, e)
      if (e.is_final(*i))
	e.unset_final(*i);
      else
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

#endif // VCSN_ALGORITHMS_COMPLEMENTARY_HXX 
