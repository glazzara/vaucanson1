// realtime.hh
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

#ifndef ALGORITHMS_REALTIME_HH
# define ALGORITHMS_REALTIME_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*------------.
  | is_realtime |
  `------------*/
  template<typename A, typename T>
  bool
  is_realtime(const Element<A, T>& a);

  /*------------.
  | in_realtime |
  `------------*/
  template<typename A, typename T>
  void
  in_realtime(Element<A, T>& a);

  /*---------.
  | realtime |
  `---------*/
  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/realtime.hxx>

#endif // ALGORITHMS_REALTIME_HH

