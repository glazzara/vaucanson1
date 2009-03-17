// getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009 The Vaucanson Group.
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
 * @author Micha�l Cadilhac <michael.cadilhac@lrde.org>
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

static alphabet_t get_alphabet (const rat_exp_t& exp)
{
  return exp.structure().monoid().alphabet();
}

# else

DEFINE_GET_ALPHABET (get_first_alphabet, first_alphabet_t, "alphabet1");
DEFINE_GET_ALPHABET (get_second_alphabet, second_alphabet_t, "alphabet2");

# endif

# ifndef WITH_TWO_ALPHABETS
/// Getter for RatExp.
static rat_exp_t get_exp(const arguments_t& args, const int& n)
{
  const std::string& s = args.args[n];
  const std::vector<std::string>& alphabet = args.alphabet;

  // Build a monoid and a series with smart token representations.
  //
  // FIXME: ideally we should call get_alphabet() when s == "-" and we
  // are reading from STDIN, but it's not clear how to detect that
  // here.  When s == "-", there is more chances that we are reading
  // the output of the previous command and we should not force the
  // call to get_alphabet().
  alphabet_t alpha;
  monoid_t M((!alphabet.empty() ||
	      (s != "-" && global_result.input_exp_type == INPUT_TYPE_EXP))
	     ? get_alphabet(alphabet) : alpha);
  semiring_t S;
  series_set_t series(S, M);


  rat_exp_t	e(series);

  if (s == "-")
  {
    return boost::apply_visitor(rat_exp_getter(M.alphabet(),
					       global_result.name,
					       global_result.input_exp_type,
					       *(M.representation()),
					       *(series.representation())),
				global_result.output);
  }

  switch (global_result.input_exp_type)
  {
    case INPUT_TYPE_XML:
    {
      std::istream* is = new std::ifstream (s.c_str ());
      if (is->fail ())
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

	*is >> regexp_loader(e, string_out (), XML ());

	delete is;

	// Set the writing data before return.
	//set_writing_data(e, args); // FIXME ?

	return e;
      }
      else
      {
	std::cerr << "Error: cannot open `" << s << "'." << std::endl;
	exit (-3);
      }
      break;
    }
    case INPUT_TYPE_EXP:
    {
      set_monoid_writing_data_(*(M.representation()), args.mrep, args.cf);
      set_series_writing_data_(*(series.representation()), args.srep, args.cf);

      e = make_rat_exp(M.alphabet(),
		       s,
		       *(M.representation()),
		       *(series.representation()));

      break;
    }
    default:
      std::cerr << "FATAL: Could not load rational expression." << std::endl;
      exit(1);
  }

  return e;
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

  if (s == "-")
    {
      automaton_t a = boost::apply_visitor
	(automaton_getter (global_result.name,
			   global_result.input_aut_type), global_result.output);

      // Set the writing data before return.
      set_writing_data(a, args);

      return a;
    }

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
    automaton_t a = make_automaton(alphabet_t());
# else
    automaton_t a = make_automaton(first_alphabet_t(), second_alphabet_t());
# endif // !WITH_TWO_ALPHABETS

    switch (global_result.input_aut_type)
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

    if (s != "-")
      delete is;

    // Set the writing data before return.
    set_writing_data(a, args);

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

  if (s == "-")
  {
    IOAUT_CONTEXT::automaton_t a =
      boost::apply_visitor(boolean_automaton_getter
			   (global_result.name, global_result.input_aut_type),
			   global_result.output);

    // Set the writing data before return.
    set_boolean_writing_data(a, args);

    return a;
  }

  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    IOAUT_CONTEXT::automaton_t a =
      IOAUT_CONTEXT::make_automaton(first_alphabet_t());

    switch (global_result.input_aut_type)
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

    if (s != "-")
      delete is;

    // Set the writing data before return.
    set_boolean_writing_data(a, args);

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
# define SET_TOKEN(name) if (flags. name) { dst . name = src . name; }

template <typename T>
void set_monoid_writing_data_(T& dst, const T& src, const cmd_flags_t& flags)
{
  SET_TOKEN(empty)
  SET_TOKEN(concat)
}

template <typename T>
void set_series_writing_data_(T& dst, const T& src, const cmd_flags_t& flags)
{
  SET_TOKEN(open_par)
  SET_TOKEN(close_par)
  SET_TOKEN(plus)
  SET_TOKEN(times)
  SET_TOKEN(star)
  SET_TOKEN(open_weight)
  SET_TOKEN(close_weight)
  SET_TOKEN(spaces)
  SET_TOKEN(zero)
}

# undef SET_TOKEN

# ifdef WITH_TWO_ALPHABETS
void set_boolean_writing_data(IOAUT_CONTEXT::automaton_t& a,
			      const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep.first_representation(), args.cf1);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep1, args.cf1);
}
void set_writing_data(automaton_t& a, const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep, args.cf);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep, args.cf);

  set_series_writing_data_(a.structure().series().representation()->first_representation(),
			   args.srep.first_representation(), args.cf1);
  set_monoid_writing_data_(*(a.structure().series().monoid().first_monoid().representation()),
			   args.mrep1, args.cf1);

  set_series_writing_data_(a.structure().series().representation()->second_representation(),
			   args.srep.second_representation(), args.cf2);
  set_monoid_writing_data_(*(a.structure().series().monoid().second_monoid().representation()),
			   args.mrep2, args.cf2);
}
# else
void set_writing_data(automaton_t& a, const arguments_t& args)
{
  set_series_writing_data_(*(a.structure().series().representation()),
			   args.srep, args.cf);
  set_monoid_writing_data_(*(a.structure().series().monoid().representation()),
			   args.mrep, args.cf);
}
# endif // ! WITH_TWO_ALPHABETS

#endif // ! GETTERS_HXX
