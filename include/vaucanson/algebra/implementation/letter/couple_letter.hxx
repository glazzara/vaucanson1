// couple_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson
// Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX

# include <string>
# include <sstream>
# include <utility>
# include <climits>
# include <vector>

# include <vaucanson/algebra/implementation/letter/couple_letter.hh>

namespace vcsn
{
  namespace algebra
  {
    template <typename U, typename V>
    struct letter_traits< std::pair<U, V> >
    {
      // we only consider letters of the form (u, v)
      typedef misc::true_t is_char_letter;

      enum
      {
	/*
	 * Theoretically   cardinal	should	 be   the   product   of
	 * letter_traits<U>::cardinal and letter_traits<V>::cardinal.
	 * But to  avoid overflows and for
	 * practical reasons, it is better to consider it infinite.
	 *
	 * FIXME: Maybe doing this is not a good idea?
	 */
	cardinal = INT_MAX
      };

      // A pair letter has two projections available: U and V.
      typedef U first_projection_t;
      typedef V second_projection_t;

      static
      std::pair<bool, std::pair<U, V> >
      literal_to_letter(const std::string& str)
      {
	// Check for a basic well formed pair: (x,y).
	if (str.size() < 5 || str[0] != '(' || *(str.end() - 1) != ')')
	  return std::make_pair(false, std::make_pair(0, 0));

	// Split the string on commas.
	typedef std::vector<std::string> tokens_t;
	typedef tokens_t::const_iterator tokens_iter_t;
	std::string delim = ",";
	std::string buff(str.begin() + 1, str.end() - 1);

	std::string::size_type last_pos = buff.find_first_not_of(delim, 0);
	std::string::size_type pos = buff.find_first_of(delim, last_pos);

	tokens_t tokens;

	while (std::string::npos != pos || std::string::npos != last_pos)
	{
	  // Push new token.
	  tokens.push_back(buff.substr(last_pos, pos - last_pos));
	  // Update positions.
	  last_pos = buff.find_first_not_of(delim, pos);
	  pos = buff.find_first_of(delim, last_pos);
	}

	if (tokens.size() != 2)
	  return std::make_pair(false, std::make_pair(0, 0));

	std::pair<bool, U> fc = algebra::letter_traits<U>::literal_to_letter(tokens[0]);
	std::pair<bool, V> sc = algebra::letter_traits<V>::literal_to_letter(tokens[1]);

	if (!(fc.first && sc.first))
	  return std::make_pair(false, std::make_pair(0, 0));

	return std::make_pair(true, std::make_pair(fc.second, sc.second));
      }

      static
      std::string
      letter_to_literal(const std::pair<U, V>& c)
      {
	std::stringstream sstr;
	sstr << '(' << c.first << ',' << c.second << ')';
	return sstr.str();
      }

      // A pair is a "tuple" with dimension 2.
      static std::string kind() { return "tuple"; }
      static int dim() { return 2; }

    };

  } // ! algebra

} // ! vcsn

namespace std
{
  template <typename U, typename V>
  std::ostream& operator<<(std::ostream& s, const std::pair<U, V>& letter)
  {
    s << vcsn::algebra::letter_traits<std::pair<U, V> >::letter_to_literal(letter);
    return s;
  }

} // ! std

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
