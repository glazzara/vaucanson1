// alphabets.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_ALPHABETS_HH
# define VCSN_ALGEBRA_ALPHABETS_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <set>

namespace vcsn {

  namespace algebra {

    /*! @ingroup alphabet */ /*! @{ */

    /*----------------.
    | AlphabetSet<L> |
    `----------------*/
    //! Static implementation of alphabet structural element.
    template<typename L>
    struct AlphabetSet
      : AlphabetSetBase<AlphabetSet<L> >
    {
      //! The type of letter hold by the alphabets.
      typedef L		letter_t;
    };
    
    //! @}

  } // algebra

  //! @{
  
  /*! @ingroup alphabet */ /*! @{ */

  /*------------------------.
  | dynamic_traits<AlphabetSet<L> |
  `------------------------*/
  //! meta information about AlphabetSet.
  template<typename L>
  struct dynamic_traits<algebra::AlphabetSet<L> >
    : dynamic_traits<algebra::AlphabetSetBase<L> >
  { };     

  //! @}

} // vcsn 

#endif // VCSN_ALGEBRA_ALPHABETS_HH

