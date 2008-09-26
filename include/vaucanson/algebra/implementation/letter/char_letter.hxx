// char_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HXX

# include <string>

# include <vaucanson/algebra/implementation/letter/char_letter.hh>

namespace vcsn {

  namespace algebra {

    template <>
    struct letter_traits<char>
    {
      // This letter type needs one char to be displayed.
      typedef misc::true_t is_char_letter;

      enum
      {
	// Here we use 255 and not 256 because random::generate<char>
	// does not generates 0 to avoid conflicts with 0 terminated
	// C strings. Therefore char alphabets will never hold more
	// than 255 different letters.
	cardinal = 255
      };

      // FIXME: use LETTER_DEFAULT
      static char default_joker()   { return '?'; }
      static char default_other()   { return '#'; }

      LETTER_DEFAULT(open_par, "(")
      LETTER_DEFAULT(close_par, ")")
      LETTER_DEFAULT(plus, "+")
      LETTER_DEFAULT(times, ".")
      LETTER_DEFAULT(star, "*")
      LETTER_DEFAULT(epsilon, "1")
      LETTER_DEFAULT(zero, "0")
      LETTER_DEFAULT(open_weight, "{")
      LETTER_DEFAULT(close_weight, "}")
      LETTER_DEFAULT(space, " ")

      static
      char
      literal_to_letter(const std::string& str)
      {
	precondition(str.size() == 1);
	return str[0];
      }

      static
      std::string
      letter_to_literal(const char& c)
      {
	std::string str;
	str = str + c;
	return str;
      }

      // A char is "simple" with dimension 1.
      static std::string kind() { return "simple"; }
      static int dim() { return 1; }

    };

    template <typename S, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>& set,
		  std::basic_string<char>& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer&)
    {
      typename std::string::const_iterator j = i;
      typename std::string::const_iterator k;

      while ((i != s.end()) && (set.alphabet().contains(*i)))
      {
	v += *i;
	++i;
      }
      return (i != j);
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_CHAR_LETTER_HXX
