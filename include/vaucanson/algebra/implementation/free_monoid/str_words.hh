// str_words.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HH

# include <string>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>
# include <vaucanson/algebra/implementation/alphabets/set_alphabet.hh>

namespace vcsn {

  /*------------------------------------------.
  | Implementation of words with basic_string |
  `------------------------------------------*/

  template <typename A>
  void 
  op_in_mul(const algebra::FreeMonoid<A>& s, 
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src);
    
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const algebra::FreeMonoid<A>& s,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b);

  template<typename A>
  const std::basic_string<typename A::letter_t>&
  identity_value(SELECTOR(algebra::FreeMonoid<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>));

  // one can create words from a single character
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(algebra::FreeMonoid<A>),
	     SELECTOR(std::basic_string<typename A::letter_t>), const typename A::letter_t& c);

  
} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/implementation/free_monoid/str_words.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HH
