// sub_automaton.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_SUB_AUTOMATON_HXX
# define VCSN_ALGORITHMS_SUB_AUTOMATON_HXX

# include <vaucanson/algorithms/sub_automaton.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <list>

namespace vcsn {

  /*----------------------------------------.
  | SubAutomaton defined by a set of states |
  `----------------------------------------*/

  template<typename A, typename auto_t, typename list_t>
  void do_sub_automaton(const AutomataBase<A>&,
		       auto_t& a,
		       const list_t& selected,
		       bool check_states)
  {
    std::list<hstate_t> to_be_removed;
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end(); ++i)
      {
	if (std::find(selected.begin(), selected.end(), *i)
	    == selected.end())
	  to_be_removed.push_back(*i);
      }

    for_each_const_(std::list<hstate_t>, i, to_be_removed)
      if ((!check_states) || (a.has_state(*i)))
	a.del_state(*i);
  }


  // wrapper:
  template<typename A, typename T, typename StatesSet>
  Element<A, T>
  sub_automaton(const Element<A, T>& a, const StatesSet& s, bool check_states)
  {
    Element<A, T> ret(a);
    do_sub_automaton(ret.structure(), ret, s, check_states);
    return ret;
  }

  template<typename A, typename T, typename StatesSet>
  void sub_automaton_here(Element<A, T>& a, const StatesSet& s, bool check_states)
  {
    do_sub_automaton(a.structure(), a, s, check_states);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_SUB_AUTOMATON_HXX
