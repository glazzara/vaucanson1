// int_letter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH
# define VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>
# include <iostream>

namespace vcsn {
  // Specialization for integers.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::list<int>& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped);

} // vcsn

namespace std {

  ostream& operator<<(ostream& o, list<int> s);

}

#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/letter/int_letter.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH
