// realtime.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_REALTIME_HXX
# define VCSN_ALGORITHMS_REALTIME_HXX

# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/algorithms/forward_realtime.hh>
# include <vaucanson/algorithms/backward_realtime.hh>

namespace vcsn {

  /*------------.
  | is_realtime |
  `------------*/
  template <class A_, typename Auto_>
  bool
  do_is_realtime(const AutomataBase<A_>&,
		 const Auto_&		   a)
  {
    for (typename Auto_::edge_iterator e = a.edges().begin();
	 e != a.edges().end();
	 ++e)
      if (a.series_of(*e) ==
	  a.structure().series().
	  identity(SELECT(typename Auto_::series_set_elt_value_t)))
	return false;
    return true;
  }


  /*--------------.
  | realtime_here |
  `--------------*/

  template<typename Auto_, typename A_>
  void
  do_realtime_here(const AutomataBase<A_>&,
		   Auto_& a,
		   realtime_type type = forward)
  {
    if (type == forward)
      return forward_realtime_here(a);
    else
      return backward_realtime_here(a);
  }


  template<typename A, typename T>
  void
  realtime_here(Element<A, T>& a, realtime_type type)
  {
    return do_realtime_here(a.structure(), a, type);
  }

  /*---------.
  | realtime |
  `---------*/

  template<typename Auto_, typename A_>
  Auto_
  do_realtime(const AutomataBase<A_>&,
	      const Auto_& a,
	      realtime_type type = forward)
  {
    if (type == forward)
      return forward_realtime(a);
    else
      return backward_realtime(a);
  }

  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, realtime_type type)
  {
    return do_realtime(a.structure(), a, type);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_REALTIME_HXX
