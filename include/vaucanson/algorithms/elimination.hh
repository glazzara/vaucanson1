// elimination.hh
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

#ifndef VCSN_ALGORITHMS_ELIMINATION_HH
# define VCSN_ALGORITHMS_ELIMINATION_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Returns the series which describes the language of the automaton.

  /*! This algorithm works on every kind of series. However, if,
    during the computation, it must take the star of it, it can
    fail. By passing a "generalized" automaton, that is an automaton
    with rational expression as label, you will be sure to have the
    algorithm succeed since we can always take the star of a rational
    expression. */
  template<typename A, typename T>
  typename Element<A, T>::series_elt_t
  elimination(const Element<A, T>& a);

  //! 'Elimination' with a function the choose the next state to remove.
  template<typename A, typename T, typename Chooser_>
  typename Element<A, T>::series_elt_t
  elimination(const Element<A, T>& a, const Chooser_& c);
  
  /*! @} */

} // vcsn

# include <vaucanson/algorithms/elimination.hxx>

#endif // VCSN_ALGORITHMS_ELIMINATION_HH
