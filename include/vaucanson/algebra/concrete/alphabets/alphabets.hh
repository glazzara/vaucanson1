// alphabets.hh
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

#ifndef VCSN_ALGEBRA_ALPHABETS_HH
# define VCSN_ALGEBRA_ALPHABETS_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <set>

namespace vcsn {

  namespace algebra {

    /*! @ingroup alphabet */ /*! @{ */

    /*----------------.
    | SetAlphabets<L> |
    `----------------*/
    //! Static implementation of alphabet structural element.
    template<typename L>
    struct SetAlphabets
      : AlphabetsBase<SetAlphabets<L> >
    {
      //! The type of letter hold by the alphabets.
      typedef L		letter_t;
    };
    
    //! @}

  } // algebra

  //! @{
  
  /*! @ingroup alphabet */ /*! @{ */

  /*------------------------.
  | MetaSet<SetAlphabets<L> |
  `------------------------*/
  //! meta information about SetAlphabets.
  template<typename L>
  struct MetaSet<SetAlphabets<L> >
  {
    //! The set of alphabet is a static structure.
    static const bool		dynamic_set = false;
  };     

  //! @}

} // vcsn 

#endif // VCSN_ALGEBRA_ALPHABETS_HH

