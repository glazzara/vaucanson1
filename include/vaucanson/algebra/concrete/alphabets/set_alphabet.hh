// set_alphabet.hh
//
// $Id$
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


#ifndef ALGEBRA_SET_ALPHABET_HH
# define ALGEBRA_SET_ALPHABET_HH

# include <vaucanson/algebra/concrete/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {


    /*-----------------------------------------------------------.
    | Definition of an alphabet implementation based on std::set |
    `-----------------------------------------------------------*/
    template<typename L>
    struct alphabet_traits<SetAlphabets<L>, std::set<L> >
    {
      typedef L			letter_t;
    };

  } // algebra

    template<typename L>
    struct MetaElement<SetAlphabets<L>, std::set<L> >
      : MetaElement<AlphabetsBase<SetAlphabets<L> >, std::set<L> >
    {
      static const bool dynamic_values = true;
    };

    template<typename L>
    bool op_contains(const SetAlphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_is_finite(const SetAlphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_contains_e(const SetAlphabets<L>& s, const std::set<L>& a, 
		       const L& v);

  /*----------------------------------.
  | Define some useful alphabet stuff |
  `----------------------------------*/
    typedef algebra::SetAlphabets<char>				Alphabets;
    typedef Element<Alphabets, std::set<char> >			Alphabet;

} // vcsn

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hxx>
 
#endif // ALGEBRA_SET_ALPHABET_HH
