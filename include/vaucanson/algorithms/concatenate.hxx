// concatenate.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
#ifndef VCSN_ALGORITHMS_CONCATENATE_HXX
# define VCSN_ALGORITHMS_CONCATENATE_HXX

# include <map>
# include <vaucanson/algorithms/concatenate.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  // author: Yann Regis-Gianas.
  // Return the concatenation of two automata using epsilon
  // transitions. 
  template <class Self, class Auto>
  void
  do_auto_in_concat(const AutomataBase<Self>&   , 
		    Auto&			lhs,
		    const Auto&			rhs)
  {
    AUTOMATON_TYPES(Auto);
    std::map<hstate_t, hstate_t>	trans;

    for_each_state(s, rhs)
      {
	hstate_t ns = lhs.add_state();
	trans[*s] = ns;
	if (rhs.is_initial(*s))
	  for_each_final_state(f, lhs)
	    lhs.add_spontaneous(*f, ns);
      }
    for_each_edge(e, rhs)
      lhs.add_edge(trans[rhs.origin_of(*e)], 
		   trans[rhs.aim_of(*e)], 
		   rhs.label_of(*e));
    lhs.clear_final();
    for_each_final_state(f, rhs)
      lhs.set_final(trans[*f], rhs.get_final(*f)); 
  }
  

  // Return the concatenation of two automata using epsilon
  // transitions. 
  template <class A, class T>
  Element<A, T> 
  concatenate(const Element<A, T>& lhs, const Element<A, T>& rhs)
  {
    Element<A, T> ret(lhs);
    do_auto_in_concat(ret.set(), ret, rhs);
    return ret;
  }

  // Return the concatenation of two automata using epsilon
  // transitions. 
  template <class A, class T>
  void
  concatenate_here(Element<A, T>& lhs, const Element<A, T>& rhs)
  {
    do_auto_in_concat(lhs.set(), lhs, rhs);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_CONCATENATE_HXX
