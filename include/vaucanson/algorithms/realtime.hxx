// realtime.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

#ifndef ALGORITHMS_REALTIME_HXX
# define ALGORITHMS_REALTIME_HXX

# include <algorithm>
# include <set>
# include <queue>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/forward_realtime.hh>
# include <vaucanson/algorithms/backward_realtime.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algorithms/closure.hh>
# include <vaucanson/algorithms/reachable.hh>

namespace vcsn {

  /*------------.
  | is_realtime |
  `------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  bool
  do_is_realtime(const AutomataBase<A_>& a_set,
		 const Auto_&		   a)
  {
    for (typename Auto_::edge_iterator e = a.edges().begin();
	 e != a.edges().end();
	 ++e)
      if (a.serie_of(*e) == 
	  a.set().series().identity(SELECT(typename Auto_::serie_value_t)))
	return false;
    return true;
  }

  template<typename A, typename T>
  bool
  is_realtime(const Element<A, T>& a)
  {
    return do_is_realtime(a.set(), a);
  }
  
  /*--------------.
  | realtime_here |
  `--------------*/
  template<typename A, typename T>
  void
  realtime_here(Element<A, T>& a, bool type = true)
  {
    if (type)
      forward_realtime_here(a);
    else
      backward_realtime_here(a);
  }

  /*---------.
  | realtime |
  `---------*/
  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, bool type = true)
  {
    if (type)
      return forward_realtime_here(a);
    else
      return backward_realtime_here(a);
  }
  
} // vcsn

#endif // ALGORITHMS_REALTIME_HXX
