// couple_letter.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HH
# define VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HH

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>
# include <iostream>

// Here is functions and traits used to manipulate letters
// which are couples

// FIXME: Only used function are defined in the char_traits.
// FIXME: So some functions and types are missing.

namespace vcsn {
  // Specialization for pairs.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::string<std::pair<U,V> >& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped);
}

namespace std {

  //! To display a single pair
  //! It assumes that each element of the pair is printable
  //! (i.e. the operator << is defined on it)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, pair<U, V> p);

  //! To display a basic_string of pair (idem)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, basic_string<pair<U, V> > s);

  //! To read a single pair.
  template <typename U, typename V>
  istream& operator>>(istream& i, pair<U, V>& p);

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


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/concrete/letter/couple_letter.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HH
