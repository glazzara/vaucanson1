// alphabets.hh
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGEBRA_ALPHABETS_HH
# define ALGEBRA_ALPHABETS_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <set>

namespace vcsn {
  namespace algebra {

    /*-------------.
    | SetAlphabets<L> |
    `-------------*/
    // 
    // Structuring element to define an alphabet
    //

    template<typename L>
    struct SetAlphabets
      : AlphabetsBase<SetAlphabets<L> >
    {
	typedef L		canonical_letter_t;
    };

  } // algebra

    /*------------------------.
    | MetaSet<SetAlphabets<L> |
    `------------------------*/
    //
    // Meta information about the structuring element
    //

    template<typename L>
    struct MetaSet<SetAlphabets<L> >
    {
      // by default an alphabet is a static object
      static const bool		dynamic_set = false;
    };     

} // vcsn 


#endif // ALGEBRA_ALPHABETS_HH

