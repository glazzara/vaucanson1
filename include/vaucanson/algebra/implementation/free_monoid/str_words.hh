// str_words.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
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


#  include <vaucanson/algebra/implementation/free_monoid/str_words.hxx>


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HH
