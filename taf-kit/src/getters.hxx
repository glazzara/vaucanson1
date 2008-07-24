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
 *         Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * This file contains the implementation of the getters.
 * @note Should not be put in a .cc file, as CONTEXT_* macros
 *	 could change from one compilation to another.
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/fsm_load.hh>
# include <string>
# include <cstdlib>
# include "getters.hh"
# include "pipe_getters.hh"
# include "pipe_writers.hh"
# include "pipe.hxx"
# include "pipe_getters.hxx"
# include "pipe_writers.hxx"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;

  /*---------------------------------------------.
  | Getters for alphabet, RatExp and automaton.  |
  `---------------------------------------------*/
# define DEFINE_GET_ALPHABET(Name, Type)			\
static Type Name (const std::vector<std::string>& al)		\
{								\
  Type a;							\
  if (al.empty())					\
  {								\
    warn ("Error: alphabet should be explicitly defined.");	\
    exit (-2);							\
  }								\
  for (std::vector<std::string>::const_iterator i = al.begin(); i != al.end(); ++i) \
    a.insert ((*i).c_str()[0]);					\
  return a;							\
}


/// Getter for alphabet.
# ifndef WITH_TWO_ALPHABETS

DEFINE_GET_ALPHABET(get_alphabet,alphabet_t);

# else

DEFINE_GET_ALPHABET (get_first_alphabet, first_alphabet_t);
DEFINE_GET_ALPHABET (get_second_alphabet, second_alphabet_t);

# endif

# ifndef WITH_TWO_ALPHABETS
/// Getter for RatExp.
static rat_exp_t get_exp_complete (const std::string& exp,
				   const std::vector<std::string>& alphabet,
				   const vcsn::algebra::token_representation_t& tok_rep)
{
# ifdef GLOBAL_RESULT
  if (exp == "-")
    {
      return boost::apply_visitor (rat_exp_getter (get_alphabet (alphabet),
						   GLOBAL_RESULT.name,
						   tok_rep),
				   GLOBAL_RESULT.output);
    }
# endif // !GLOBAL_RESULT

  return make_rat_exp (get_alphabet (alphabet), exp, tok_rep);
}
# endif // !WITH_TWO_ALPHABETS

/// Getter for automaton.
static automaton_t get_aut (const std::string& s)
{
# ifdef GLOBAL_RESULT
  if (s == "-")
    {
      automaton_t a = boost::apply_visitor
	(automaton_getter (GLOBAL_RESULT.name,
			   GLOBAL_RESULT.input_type), GLOBAL_RESULT.output);
      return a;
    }
# endif // !GLOBAL_RESULT

  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str ()));
  if (not is->fail ())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

# ifndef WITH_TWO_ALPHABETS
    automaton_t a = make_automaton (alphabet_t ());
# else
    automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t ());
# endif // !WITH_TWO_ALPHABETS

# ifdef GLOBAL_RESULT
    switch (GLOBAL_RESULT.input_type)
      {
      case INPUT_TYPE_XML:
	*is >> automaton_loader(a, string_out (), XML ());
	break;
# ifndef WITH_TWO_ALPHABETS
      case INPUT_TYPE_FSM:
	fsm_load(*is, a);
	break;
# endif // !WITH_TWO_ALPHABETS
      default:
	std::cerr << "FATAL: Could not load automaton." << std::endl;
	exit(1);
      }
# else
    *is >> automaton_loader(a, string_out (), XML ());
# endif // !GLOBAL_RESULT

    if (s != "-")
      delete is;
    return a;
  }
  else
  {
    std::cerr << "Error: cannot open `" << s << "'." << std::endl;
    exit (-3);
  }
}

#ifdef WITH_TWO_ALPHABETS
static boolean_automaton::automaton_t get_boolean_aut(std::string s)
{
# ifdef GLOBAL_RESULT
  if (s == "-")
  {
    boolean_automaton::automaton_t a =
      boost::apply_visitor(boolean_automaton_getter
			   (GLOBAL_RESULT.name, GLOBAL_RESULT.input_type),
			   GLOBAL_RESULT.output);
    return a;
  }
# endif // !GLOBAL_RESULT

  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    boolean_automaton::automaton_t a =
      boolean_automaton::make_automaton(first_alphabet_t());

# ifdef GLOBAL_RESULT
    switch (GLOBAL_RESULT.input_type)
      {
      case INPUT_TYPE_XML:
	*is >> automaton_loader(a, string_out (), XML ());
	break;
      case INPUT_TYPE_FSM:
	fsm_load(*is, a);
	break;
      default:
	std::cerr << "FATAL: Could not load automaton." << std::endl;
	exit(1);
      }
# else
    *is >> automaton_loader(a, string_out (), XML ());
# endif // !GLOBAL_RESULT

    if (s != "-")
      delete is;
    return a;
  }
  else
  {
    std::cerr << "FATAL: Could not load automaton." << std::endl;
    exit(1);
  }
}
#endif // !WITH_TWO_ALPHABETS

#endif // ! GETTERS_HXX
