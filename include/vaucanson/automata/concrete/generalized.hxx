// generalized.hxx
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

#ifndef VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HXX
# define VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HXX

# include <vaucanson/automata/concrete/generalized.hh>

namespace vcsn {

  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from)
  {
    typename generalized_traits<Auto_>::automaton_t to(from.set());
    auto_copy(to, from);
    return to;
  }
  

} // vcsn

#endif // VAUCANSON_AUTOMATA_GENERALIZED_HXX
