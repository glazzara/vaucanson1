// tropical_semiring.hxx
//
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and
//  Regis-Gianas.
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

#ifndef ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX
# define ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX

# include <vaucanson/algebra/concept/tropical_semiring.hh>
# include <limits>

namespace vcsn
{
  namespace algebra
  {
    template <class T>
    inline
    T
    TropicalMin::NonStareableInterval<T>::inf()
    {
      return -std::numeric_limits<T>::max();
    }
    
    template <class T>
    inline
    T
    TropicalMin::NonStareableInterval<T>::sup()
    {
      return T();
    }
    
    template <class T>
    inline
    T
    TropicalMax::NonStareableInterval<T>::inf()
    {
      return T();
    }

    template <class T>
    inline
    T
    TropicalMax::NonStareableInterval<T>::sup()
    {
      return std::numeric_limits<T>::max();
    }
    
  } // algebra

} // vcsn

#endif // ! ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HXX
