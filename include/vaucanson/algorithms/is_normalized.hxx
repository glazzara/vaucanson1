// is_normalized.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_NORMALIZED_HXX
# define VCSN_ALGORITHMS_IS_NORMALIZED_HXX

# include <vaucanson/algorithms/is_normalized.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  template<typename S, typename A>
  bool
  do_is_normalized_transducer(const AutomataBase<S>& trans_set, 
			      const A& trans)
  {
    AUTOMATON_TYPES(A);
    bool is_normalized = false; 
    for_each_edge(e, trans)
      {
        is_normalized ^= is_letter_support(trans.serie_of(*e));
	for_each_const_(series_elt_t::support_t, i, trans.serie_of(*e).supp())
	  {	
	    is_normalized ^= is_letter_support(trans.serie_of(*e).get(*i)); 
	    if (!is_normalized)
	      return false;
	  }
      }
    return true;
  }

  template<typename S, typename A>
  bool
  is_normalized_transducer(const Element<S, A>& a)
  {
    return do_is_normalized_transducer(a.set(), a);
  }
}

#endif // VCSN_ALGORITHMS_IS_NORMALIZED_HXX
