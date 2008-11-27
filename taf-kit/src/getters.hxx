// getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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
# include "library_commands.hh"
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
# define DEFINE_GET_ALPHABET(Name, Type, Opt)				\
static Type Name (const std::vector<std::string>& al)			\
{									\
  Type a;								\
  if (al.empty())							\
  {									\
    warn ("Error: alphabet should be explicitly defined using --" Opt);	\
    exit (-2);								\
  }									\
  for (std::vector<std::string>::const_iterator i = al.begin();		\
       i != al.end(); ++i)						\
    a.insert (*i);							\
  return a;								\
}


/// Getter for alphabet.
# ifndef WITH_TWO_ALPHABETS

DEFINE_GET_ALPHABET(get_alphabet, alphabet_t, "alphabet");

# else

DEFINE_GET_ALPHABET (get_first_alphabet, first_alphabet_t, "alphabet1");
DEFINE_GET_ALPHABET (get_second_alphabet, second_alphabet_t, "alphabet2");

# endif

# ifndef WITH_TWO_ALPHABETS
/// Getter for RatExp.
static rat_exp_t get_exp(const arguments_t& args, const int& n)
{
  const std::string& exp = args.args[n];
  const std::vector<std::string>& alphabet = args.alphabet;
  const monoid_rep_t& mrep = args.mrep;
  const series_rep_t& srep = args.srep;

# ifdef GLOBAL_RESULT
  if (exp == "-")
    {
      return boost::apply_visitor (rat_exp_getter (get_alphabet (alphabet),
						   GLOBAL_RESULT.name,
						   mrep, srep),
				   GLOBAL_RESULT.output);
    }
# endif // !GLOBAL_RESULT

  return make_rat_exp (get_alphabet (alphabet), exp, mrep, srep);
}


template <class S, class T>
static std::basic_string<letter_t>
get_word(Element<S, T>& aut, const std::string& s)
{
  Element<monoid_t, std::basic_string<letter_t> > w(aut.structure().series().monoid());

  if (!parse_word(w, s).first)
    {
      std::cerr << "FATAL: Cannot parse " << s << std::endl;
      exit(1);
    }
  return w.value();
}

# endif // !WITH_TWO_ALPHABETS

/// Getter for automaton.
static automaton_t get_aut (const arguments_t& args, int n)
{
  const std::string& s = args.args[n];

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

  // If we failed to open S, try to open the file in our search path.
  if (is->fail () && s != "-")
  {
    const std::list<std::string>& path = get_automata_path(args);

    std::list<std::string>::const_iterator i;
    for (i = path.begin(); i != path.end(); ++i)
      {
	delete is;
	std::string file = *i + "/" + s;
	is = new std::ifstream (file.c_str ());
	if (not is->fail())
	  break;
      }
  }

  if (not is->fail ())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

# ifndef WITH_TWO_ALPHABETS
    automaton_t a = make_automaton (alphabet_t (), args.mrep, args.srep);
# else
    automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t (), args.mrep, args.mrep1, args.mrep2, args.srep);
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
static IOAUT_CONTEXT::automaton_t get_boolean_aut(const arguments_t& args, const int& n)
{
  const std::string& s = args.args[n];

# ifdef GLOBAL_RESULT
  if (s == "-")
  {
    IOAUT_CONTEXT::automaton_t a =
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

    IOAUT_CONTEXT::automaton_t a =
      IOAUT_CONTEXT::make_automaton(first_alphabet_t(), args.mrep1,
				    args.srep.first_representation());

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

// Set the representations provided on the command line.
# define SET_TOKEN(exp, name, rep) \
if (args.cf. name) \
a.structure().series() exp name = args. rep . name

# ifdef WITH_TWO_ALPHABETS
void set_writing_data(automaton_t& a, const arguments_t& args)
{
  SET_TOKEN(.representation()->, open_par, srep);
  SET_TOKEN(.representation()->, close_par, srep);
  SET_TOKEN(.representation()->, plus, srep);
  SET_TOKEN(.representation()->, times, srep);
  SET_TOKEN(.representation()->, star, srep);
  SET_TOKEN(.representation()->, open_weight, srep);
  SET_TOKEN(.representation()->, close_weight, srep);
  SET_TOKEN(.representation()->, spaces, srep);
  SET_TOKEN(.representation()->, zero, srep);

  SET_TOKEN(.monoid().representation()->, empty, mrep);
  SET_TOKEN(.monoid().representation()->, concat, mrep);

  SET_TOKEN(.representation()->first_representation()., open_par, srep);
  SET_TOKEN(.representation()->first_representation()., close_par, srep);
  SET_TOKEN(.representation()->first_representation()., plus, srep);
  SET_TOKEN(.representation()->first_representation()., times, srep);
  SET_TOKEN(.representation()->first_representation()., star, srep);
  SET_TOKEN(.representation()->first_representation()., open_weight, srep);
  SET_TOKEN(.representation()->first_representation()., close_weight, srep);
  SET_TOKEN(.representation()->first_representation()., spaces, srep);
  SET_TOKEN(.representation()->first_representation()., zero, srep);

  SET_TOKEN(.monoid().first_monoid().representation()->, empty, mrep1);
  SET_TOKEN(.monoid().second_monoid().representation()->, concat, mrep1);

  SET_TOKEN(.representation()->first_representation()., open_par, srep);
  SET_TOKEN(.representation()->first_representation()., close_par, srep);
  SET_TOKEN(.representation()->first_representation()., plus, srep);
  SET_TOKEN(.representation()->first_representation()., times, srep);
  SET_TOKEN(.representation()->first_representation()., star, srep);
  SET_TOKEN(.representation()->first_representation()., open_weight, srep);
  SET_TOKEN(.representation()->first_representation()., close_weight, srep);
  SET_TOKEN(.representation()->first_representation()., spaces, srep);
  SET_TOKEN(.representation()->first_representation()., zero, srep);

  SET_TOKEN(.monoid().first_monoid().representation()->, empty, mrep2);
  SET_TOKEN(.monoid().second_monoid().representation()->, concat, mrep2);
}
# else
void set_writing_data(automaton_t& a, const arguments_t& args)
{
  SET_TOKEN(.representation()->, open_par, srep);
  SET_TOKEN(.representation()->, close_par, srep);
  SET_TOKEN(.representation()->, plus, srep);
  SET_TOKEN(.representation()->, times, srep);
  SET_TOKEN(.representation()->, star, srep);
  SET_TOKEN(.representation()->, open_weight, srep);
  SET_TOKEN(.representation()->, close_weight, srep);
  SET_TOKEN(.representation()->, spaces, srep);
  SET_TOKEN(.representation()->, zero, srep);

  SET_TOKEN(.monoid().representation()->, empty, mrep);
  SET_TOKEN(.monoid().representation()->, concat, mrep);
}
# endif // ! WITH_TWO_ALPHABETS

# undef SET_TOKEN

#endif // ! GETTERS_HXX
