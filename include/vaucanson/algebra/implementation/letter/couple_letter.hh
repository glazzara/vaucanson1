// couple_letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH

# include <climits>
# include <string>
# include <iostream>

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

// Here are functions to manipulate pairs.

namespace vcsn
{

  namespace algebra
  {

    template <typename U, typename V>
    struct letter_traits< std::pair<U, V> >
    {
      enum
	{
	  /*
	   * Theoretically   cardinal   should   be   the   product   of
	   * letter_traits<U>::cardinal and letter_traits<V>::cardinal.
	   * But to  avoid overflows and for
	   * practical reasons, it is better to consider it infinite.
	   *
	   * FIXME: Maybe doing this is not a good idea?
	   */
	  cardinal = INT_MAX
	};
    };

  } // End of namespace algebra.
} // End of namespace vcsn.

namespace vcsn {
  // Specialization for pairs.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::basic_string< std::pair<U, V> >& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped);
}

namespace utility {

  /// To display a single pair
  /// It assumes that each element of the pair is printable
  /// (i.e. the operator << is defined on it)
  template <typename U, typename V>
  std::ostream& operator<<(std::ostream& o, std::pair<U, V> p);

  /// To display a basic_string of pair (idem)
  template <typename U, typename V, class Traits, class Allocator>
  std::ostream& operator<<(std::ostream& o,
    std::basic_string<std::pair<U, V>, Traits, Allocator> s);

  //! To read a single pair.
  template <typename U, typename V>
  std::istream& operator>>(std::istream& i, std::pair<U, V>& p);

} // utility

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/letter/couple_letter.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HH
