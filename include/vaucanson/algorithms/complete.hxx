// complete.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_COMPLETE_HXX
# define VCSN_ALGORITHMS_COMPLETE_HXX

# include <vaucanson/algorithms/complete.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <list>
# include <set>

namespace vcsn {

  /*--------------.
  | complete_here |
  `--------------*/

  template <typename A, typename T>
  void
  complete_here(Element<A, T>& work)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t puits = work.add_state();
    std::list<hstate_t> aim;

    for_each_state(i, work)
      {
	for_each_letter(j, work.structure().series().monoid().alphabet())
	  {
	    aim.clear();
	    work.letter_deltac(aim, *i, *j, delta_kind::states());
	    if (aim.size() == 0)
	      work.add_letter_edge(*i, puits, *j);
	  }
      }
  }

  /*---------.
  | complete |
  `---------*/

  template <typename A, typename T>
  Element<A, T>
  complete(const Element<A, T>& e)
  {
    Element<A, T> res(e);
    complete_here(res);
    return res;
  }

  /*------------.
  | is_complete |
  `------------*/

  template <class A, class T>
  bool
  is_complete(const Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_each_state(i, e)
      {
	std::set<hstate_t> aim;
	const alphabet_t& alpha = e.structure().series().monoid().alphabet();
	for_each_letter(j, alpha)
	  {
	    aim.clear();
	    e.letter_deltac(aim, *i, *j, delta_kind::states());

	    if (aim.size() == 0)
	      return false;
	  }
      }
    return true;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_COMPLETE_HXX
