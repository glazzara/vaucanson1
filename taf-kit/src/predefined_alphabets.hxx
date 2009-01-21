// predefined_alphabets.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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

#ifndef PREDEFINED_ALPHABETS_HXX
# define PREDEFINED_ALPHABETS_HXX

# include <string>
# include <vector>

# include "predefined_alphabets.hh"

std::string build_default_eps(std::string alphabet)
{
  // Type helpers.
  typedef std::vector<std::string> ab_vect_t;

  parser_options<monoid_rep_t, series_rep_t> p_opts("ALPHABET=" + alphabet);
  ab_vect_t letters = p_opts.get_letters();

# ifdef WITH_TWO_ALPHABETS
  first_alphabet_t al;
# else
  alphabet_t al;
# endif

  for (ab_vect_t::const_iterator it = letters.begin();
       it != letters.end();
       ++it)
    al.insert(*it);

# ifdef WITH_TWO_ALPHABETS
  first_monoid_t M(al);
# else
  monoid_t M(al);
# endif

  return M.representation()->empty;
}

const char* build_predefined_string()
{
  static std::string output;

  // Build the string with dynamic values for empty word representations.
  output += "The following alphabets are predefined:\n"
	   "	 `letters': Use [a-z] as the alphabet, "
	 + build_default_eps(ALPHABET_AZ)
	 + " as empty word\n"
	 + "	 `alpha': Use [a-zA-Z] as the alphabet, "
	 + build_default_eps(ALPHABET_AZAZ)
	 + " as empty word\n"
	 + "	 `digits': Use [0-9] as the alphabet, "
	 + build_default_eps(ALPHABET_DIGITS)
	 + " as empty word\n"
	 + "	 `ascii': Use ascii characters as the alphabet, "
	 + build_default_eps(ALPHABET_ASCII)
	 + " as empty word\n";

  return output.c_str();
}

#endif /* !PREDEFINED_ALPHABETS_HXX */
