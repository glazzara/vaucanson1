// trim.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_TRIM_HXX
# define VCSN_ALGORITHMS_TRIM_HXX

# include <vaucanson/algorithms/trim.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/algorithms/accessible.hh>

# include <algorithm>

namespace vcsn {

  /*---------------------.
  | do_start_trim_states |
  `---------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_useful_states(const AutomataBase<A_>&,
		   const Auto_&		   a)
  {
    std::set<hstate_t> start = accessible_states(a);
    std::set<hstate_t> final = coaccessible_states(a);
    std::set<hstate_t> result;
    std::insert_iterator<std::set<hstate_t> > i(result, result.begin());

    set_intersection(start.begin(), start.end(), final.begin(), final.end(), i);
    return result;
  }

  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a)
  {
    return do_useful_states(a.structure(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a)
  {
    return sub_automaton(a, useful_states(a));
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_TRIM_HXX
