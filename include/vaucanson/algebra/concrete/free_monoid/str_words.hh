// str_words.hh
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
#ifndef VCSN_ALGEBRA_CONCRETE_STR_WORDS_HH
# define VCSN_ALGEBRA_CONCRETE_STR_WORDS_HH

# include <string>
# include <vaucanson/algebra/concrete/free_monoid/words.hh>
# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

namespace vcsn {

  /*------------------------------------------.
  | Implementation of words with basic_string |
  `------------------------------------------*/

  template <typename A>
  void 
  op_in_mul(const SetWords<A>& s, 
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src);
    
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const SetWords<A>& s,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b);

  template<typename A>
  const std::basic_string<typename A::letter_t>&
  identity_value(SELECTOR(SetWords<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>));

  // one can create words from a single character
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(std::basic_string<typename A::letter_t>),
	     SELECTOR(SetWords<A>), const typename A::letter_t& c);

  template <class A>
  Element<SetWords<A>, std::basic_string<typename A::letter_t> >
  op_choose(const SetWords<A>& s, 
	    SELECTOR(std::basic_string<typename A::letter_t>));
  
} // vcsn

# include <vaucanson/algebra/concrete/free_monoid/str_words.hxx>

#endif //  ALGEBRA_STR_WORDS_HH
