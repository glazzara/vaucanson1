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

#ifndef NO_PREDEF_ALPHABETS
namespace {
  const struct alphabet
  {
    const char*	name;
    const char*	alphabet;
    const char* shortdef;
  } predefined_alphabets[] = {
    { "letters",
      "abcdefghijklmnopqrstuvwxyz",
      "[a-z]" },
    { "alpha",
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
      "[a-zA-Z]" },
    { "digits",
      "0123456789",
      "[0-9]" },
    { "ascii",
      "\\ \"!#$%&'\\(\\)*+\\,-./0123456789\\:;<\\=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_`abcdefghijklmnopqrstuvwxyz{|}~",
      "all ascii characters" },
    { 0, 0 } };
}
#endif

const char* alphabet_lookup(const char* name)
{
#ifndef NO_PREDEF_ALPHABETS
  for (const alphabet* alpha = predefined_alphabets; alpha->name; ++alpha)
    if (strcasecmp(alpha->name, name) == 0)
      return alpha->alphabet;
#endif
  return name;
}


static
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
#ifndef NO_PREDEF_ALPHABETS
  // Build the string with dynamic values for empty word representations.
  output += "The following alphabets are predefined:\n";

  const struct alphabet* p;
  for (p = predefined_alphabets; p->name; ++p)
    {
      output += "\t `";
      output += p->name;
      output += "': Use ";
      output += p->shortdef;
      output += " as the alphabet and `";
      output += build_default_eps(p->alphabet);
      output += "' as empty word\n";
    }
#endif
  return output.c_str();
}

#endif /* !PREDEFINED_ALPHABETS_HXX */
