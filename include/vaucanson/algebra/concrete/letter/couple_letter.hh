// couple_letter.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HH
# define VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HH

# include <string>
# include <iostream>

// Here is functions and traits used to manipulate letters
// which are couples

// FIXME: Only used function are defined in the char_traits.
// FIXME: So some functions and types are missing.

namespace std {

  //! To display a single pair
  //! It assumes that each element of the pair is printable
  //! (i.e. the operator << is defined on it)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, pair<U, V> p);

  //! To display a basic_string of pair (idem)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, basic_string<pair<U, V> > s);

  //! The char trait on pair (needed by basic_string for example)
  template <typename U, typename V>
  struct char_traits<pair<U, V> >
  {
    typedef pair<U, V> 	char_type;

    static int 
    compare(const char_type* __s1, const char_type* __s2, size_t __n);

    static char_type* 
    move(char_type* __s1, const char_type* __s2, size_t __n);

    static char_type* 
    copy(char_type* __s1, const char_type* __s2, size_t __n);

    static char_type* 
    assign(char_type* __s, size_t __n, char_type __a);
  };

} // std

# include <vaucanson/algebra/concrete/letter/couple_letter.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HH

