// str_words.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HH

// We will use std::basic_string as a `word' implementation.
# include <string>

# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabet_set.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------------------------------------.
    | Implementation of words with std::basic_string |
    `-----------------------------------------------*/

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

    template<typename A, typename St>
    St&
    op_rout(const FreeMonoid<A>& s,
	    St& st,
	    std::basic_string<typename A::letter_t>& v);

    template<typename A>
    const std::basic_string<typename A::letter_t>&
    identity_value(SELECTOR(algebra::FreeMonoid<A>),
		   SELECTOR(std::basic_string<typename A::letter_t>));

    // one can create words from a single character
    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>),
	       SELECTOR(std::basic_string<typename A::letter_t>),
	       const typename A::letter_t& c);

    // one can create words from its literal representation as std::string
    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>),
	       SELECTOR(std::basic_string<typename A::letter_t>),
	       const std::string& c);

    // one can create words from its literal representation as char*
    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(algebra::FreeMonoid<A>),
	       SELECTOR(std::basic_string<typename A::letter_t>),
	       const char* c);

    /*---------------------------------------------------------------------.
    | word_traits<FreeMonoid<A>, std::basic_string<typename A::letter_t> > |
    `---------------------------------------------------------------------*/

    /**
     * Meta information about the mixing of FreeMonoid with
     * std::basic_string.
     */
    template <typename A>
    struct word_traits<FreeMonoid<A>,
		       std::basic_string<typename A::letter_t> >
    {
      /// The type of the alphabet.
      typedef A alphabet_t;

      /// The type of the word.
      typedef Element<FreeMonoid<A>,
	      std::basic_string<typename alphabet_t::letter_t> > word_t;

      /// The value type of word.
      typedef typename word_t::value_t word_value_t;

      /// The type of the first projection alphabet.
      typedef typename alphabet_traits<typename alphabet_t::set_t,
				       typename alphabet_t::value_t>::
	first_projection_t first_projection_alphabet_t;

      /// The type of the second projection alphabet.
      typedef typename alphabet_traits<typename alphabet_t::set_t,
				       typename alphabet_t::value_t>::
	second_projection_t second_projection_alphabet_t;

      /// The type of the first projection monoid.
      typedef FreeMonoid<first_projection_alphabet_t> first_monoid_t;

      /// The type of the second projection monoid.
      typedef FreeMonoid<second_projection_alphabet_t> second_monoid_t;

      /// The type of the first projection word.
      typedef Element<first_monoid_t,
	      std::basic_string<typename first_projection_alphabet_t::
				letter_t> > first_projection_t;

      /// The value type of the first projection word.
      typedef typename first_projection_t::value_t first_projection_value_t;

      /// The type of the second projection word.
      typedef Element<second_monoid_t,
	      std::basic_string<typename second_projection_alphabet_t::
				letter_t> > second_projection_t;

      /// The value type of the second projection word.
      typedef typename second_projection_t::value_t second_projection_value_t;

      /// The first projection word maker.
      static first_projection_t first_projection(const first_monoid_t&,
						 const word_t&);
      static first_projection_value_t first_projection(const word_value_t&);

      /// The second projection word maker.
      static second_projection_t second_projection(const second_monoid_t&,
						   const word_t&);
      static second_projection_value_t second_projection(const word_value_t&);
    };

  } // ! algebra

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/implementation/monoid/str_words.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_STR_WORDS_HH
