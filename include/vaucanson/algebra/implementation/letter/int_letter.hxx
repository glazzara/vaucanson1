// int_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2007, 2008, 2009 The Vaucanson Group.
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

# include <string>
# include <sstream>
# include <utility>
# include <climits>

# include <vaucanson/algebra/implementation/letter/int_letter.hh>

namespace vcsn
{
  namespace algebra
  {
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

      // We can not "project" an int letter.
      typedef undefined_type first_projection_t;
      typedef undefined_type second_projection_t;

      static
      std::pair<bool, int>
      literal_to_letter(const std::string& str)
      {
	std::stringstream sstr(str);

	// Disallow a leading '+' because it would be too confusing:
	// would '2+4' mean '2#+4' or '(2)+(4)'?
	if (str[0] == '+')
	  return std::make_pair(false, 0);

	int ret = 0;
	// Do not skip spaces when translating numbers, otherwise a
	// blank string such as " " would be translated into 0 without
	// any problem.
 	sstr >> std::noskipws >> ret;

	// Check if something is left in the stream.
	if (!sstr.eof())
	  return std::make_pair(false, 0);

	return std::make_pair(true, ret);
      }

      static
      std::string
      letter_to_literal(const int& c)
      {
	std::stringstream sstr;
	sstr << c;
	return sstr.str();
      }

      // An int is "simple" with dimension 1.
      static std::string kind() { return "simple"; }
      static int dim() { return 1; }

    };

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_INT_LETTER_HXX
