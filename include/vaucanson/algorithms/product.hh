// product.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_PRODUCT_HH
# define VCSN_ALGORITHMS_PRODUCT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn 
{
  
  /** \addtogroup algorithms */  /** @{ */
  
  //! Returns a fresh automaton that is the product of the two input ones.
  // INTERFACE: Automaton product(const Automaton& a1, const Automaton& a2) { return vcsn::product(*a1, *a2); }
  // INTERFACE: GenAutomaton product(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::product(*a1, *a2); }
  template<typename A, typename T, typename U>
  Element<A, T> 
  product(const Element<A, T>& lhs, const Element<A, U>& rhs);

  // INTERFACE: void diagonal_here(Automaton& a) { return vcsn::diagonal_here(*a); }
  // INTERFACE: void diagonal_here(GenAutomaton& a) { return vcsn::diagonal_here(*a); }

  // INTERFACE: Automaton diagonal(const Automaton& a) { return vcsn::diagonal(*a); }
  // INTERFACE: GenAutomaton diagonal(const GenAutomaton& a) { return vcsn::diagonal(*a); }
  
  /** @} */
  
} // vcsn

# include <vaucanson/algorithms/product.hxx>

#endif // VCSN_ALGORITHMS_PRODUCT_HH
