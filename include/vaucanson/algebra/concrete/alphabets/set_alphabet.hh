// set_alphabet.hh
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
#ifndef VCSN_ALGEBRA_CONCRETE_ALPHABET_SET_ALPHABET_HH
# define VCSN_ALGEBRA_CONCRETE_ALPHABET_SET_ALPHABET_HH

# include <vaucanson/algebra/concrete/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {

    /*! @ingroup alphabet */ /*! @{ */

    /*---------------------------------------------.
    | alphabet_traits<SetAlphabets<L>,std::set<L>> |
    `---------------------------------------------*/
    //! meta information about the mixing of SetAlphabets with
    //! std::set.
    template<typename L>
    struct alphabet_traits<SetAlphabets<L>, std::set<L> >
    {
      //! The type of letter hold by the alphabet.
      typedef L			letter_t;
    };

    //! @}

  } // algebra
  
  /*! @ingroup alphabet */ /*! @{ */

  /*------------------------------------------.
  | MetaElement<SetAlphabets<L>, std::set<L>> |
  `------------------------------------------*/
  //! Services of every alphabet implemented with std::set.
  //! See MetaElement<AlphabetsBase<Self>, T>.
  template<typename L>
  struct MetaElement<SetAlphabets<L>, std::set<L> >
    : MetaElement<AlphabetsBase<SetAlphabets<L> >, std::set<L> >
  {
    //! An alphabet implemented with std::set is a dynamic value.
    static const bool dynamic_values = true;
  };
  
  //! @}

  template<typename L>
  bool op_contains(const SetAlphabets<L>& s, const std::set<L>& a);
  
  template<typename L>
  bool op_is_finite(const SetAlphabets<L>& s, const std::set<L>& a);
  
  template<typename L>
  bool op_contains_e(const SetAlphabets<L>& s, const std::set<L>& a, 
		     const L& v);
    
} // vcsn

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hxx>
 
#endif // VCSN_ALGEBRA_CONCRETE_ALPHABET_SET_ALPHABET_HH
