// int_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HXX

# include <sstream>
# include <limits.h>

# include <vaucanson/algebra/implementation/letter/int_letter.hh>

namespace vcsn {

  namespace algebra {

    template <>
    struct letter_traits<int>
    {
      // This letter type needs more than one char to be displayed.
      typedef misc::false_t is_char_letter;

      enum
      {
	// Here we use UINT_MAX and not UINT_MAX + 1 because an enum cannot
	// hold UINT_MAX + 1.
	cardinal = UINT_MAX
      };

      LETTER_DEFAULT(open_par, "(")
      LETTER_DEFAULT(close_par, ")")
      LETTER_DEFAULT(plus, "+")
      LETTER_DEFAULT(times, ".")
      LETTER_DEFAULT(star, "*")
      LETTER_DEFAULT(epsilon, "e")
      LETTER_DEFAULT(zero, "z")
      LETTER_DEFAULT(open_weight, "{")
      LETTER_DEFAULT(close_weight, "}")
      LETTER_DEFAULT(space, " ")

      static
      int
      literal_to_letter(const std::string& str)
      {
	std::stringstream sstr(str);
	int ret;
	sstr >> ret;
	return ret;
      }

      static
      std::string
      letter_to_literal(const int& c)
      {
	std::stringstream sstr;
	sstr << c;
	std::string str;
	sstr >> str;
	return str;
      }
    };

    template <typename S, typename CharContainer>
    bool op_parse(const algebra::FreeMonoidBase<S>& set,
		  std::basic_string<int>& v,
		  const std::string& s,
		  typename std::string::const_iterator& i,
		  const CharContainer&)
    {
      typename std::string::const_iterator j = i;
      typename std::string::const_iterator k;
      typename std::string::const_iterator back;

      while (i != s.end()) {
	std::string out;
	back = i;

	while ((i != s.end()) && (((*i >= '0') && (*i <= '9'))) || (*i == '#'))
	  if (*i == '#') {
	    ++i;
	    break;
	  }
	  else {
	    out += *i;
	    ++i;
	  }

	int value;
	std::istringstream is(out);
	is >> value;
	if (!set.alphabet().contains(value)) {
	  i = back;
	  break ;
	}
	v.push_back(value);
      }
      return (i != j);
    }

  } // ! algebra

} // ! vcsn

namespace std {

  inline
  ostream& operator<<(ostream& o, basic_string<int> s)
  {
    basic_string<int>::const_iterator i;
    basic_string<int>::const_iterator j;

    for (i = s.begin(); i != s.end(); ) {
      o << *i;
      i++;
      if (i != s.end())
	o << "#";
    }

    return o;
  }

} // ! std

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HXX
