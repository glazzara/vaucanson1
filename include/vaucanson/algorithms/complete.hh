// complete.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_COMPLETE_HH
# define VCSN_ALGORITHMS_COMPLETE_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Complete the automaton to have an output for every letters in each state.
  template <typename A, typename T>
  void
  auto_in_complete(Element<A, T>&);

  //! Return the automaton which has an output for every letters in each state.
  template <typename A, typename T>
  Element<A, T>
  auto_complete(const Element<A, T>&);

  //! Return true if the automaton is complete.
  template <class A, class T>
  bool
  is_complete(const Element<A, T>& e);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/complete.hxx>

#endif // VCSN_ALGORITHMS_COMPLETE_HH
