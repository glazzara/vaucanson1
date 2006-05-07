// getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

#ifndef GETTERS_HXX
# define GETTERS_HXX

/**
 * @file getters.hxx
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * This file contains the implementation of the getters.
 * @note Should not be put in a .cc file, as CONTEXT_* macros
 *	 could change from one compilation to another.
 */

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/xml/XML.hh>
# include <string>
# include "getters.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;

  /*---------------------------------------------.
  | Getters for alphabet, RatExp and automaton.  |
  `---------------------------------------------*/

/// Getter for alphabet.
static alphabet_t get_alphabet (const char* alphabet)
{
  alphabet_t	a;

  if (not (alphabet and alphabet[0]))
  {
    warn ("Error: alphabet should be explicitly defined.");
    exit (-2);
  }

  for (int i = 0; alphabet[i]; ++i)
    a.insert (alphabet[i]);
  return a;
}

/// Getter for RatExp.
static rat_exp_t get_exp_complete (const std::string& exp,
				   const char* alphabet,
				   char /* @bug epsilon */)
{
  return make_rat_exp (get_alphabet (alphabet), exp);
}


/// Getter for automaton.
static automaton_t get_aut (const std::string& s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str ()));
  if (not is->fail ())
  {
    using namespace vcsn::io;
    using namespace vcsn::xml;

    automaton_t a = make_automaton (get_alphabet ("dummy"));
    *is >> automaton_loader (a, string_out (), XML ());

    if (s != "-")
      delete is;
    return a;
  }
  else
  {
    std::cerr << "Error: could not load automaton." << std::endl;
    exit (-3);
  }
}

#endif // ! GETTERS_HXX
