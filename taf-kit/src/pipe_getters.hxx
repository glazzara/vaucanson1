// pipe_getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008, 2009 The Vaucanson Group.
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

#ifndef PIPE_GETTERS_HXX
# define PIPE_GETTERS_HXX

/**
 * @file pipe_getters.hxx
 *
 * This file contains boost variant visitors and
 * is to be included within getters.hh
 */

using namespace vcsn::tools;

automaton_getter::automaton_getter (std::string& cmd, input_format_t fmt)
  : command (cmd),
    f (fmt)
{
}

automaton_t
automaton_getter::operator() (automaton_t& a) const
{
  return a;
}

automaton_t
automaton_getter::operator() (std::string& str) const
{
  std::istringstream is (str);

  // Representations will be build by the automaton loader.
# ifndef WITH_TWO_ALPHABETS
  automaton_t a = make_automaton (alphabet_t ());
# else
  automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t ());
# endif // !WITH_TWO_ALPHABETS

  switch (f)
    {
    case INPUT_TYPE_XML:
      is >> automaton_loader(a, string_out (), XML ());
      break;
# ifndef WITH_TWO_ALPHABETS
    case INPUT_TYPE_FSM:
      fsm_load(is, a);
      break;
# endif // !WITH_TWO_ALPHABETS
    default:
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
  return a;
}

automaton_t
automaton_getter::operator() (command_output_status& i) const
{
  if (i != PIPE_GET_FROM_STDIN)
    {
      if (i == PIPE_BENCH)
	{
	  std::cerr << "Impossible to benchmark the sequence:\n"
		       "The first task reads from stdin."
		    << std::endl;
	  exit (1);
	}
      std::cerr << command
		<< ": Incorrect input type"
		<< std::endl;
      exit (1);
    }

  // Representations will be build by the automaton loader.
# ifndef WITH_TWO_ALPHABETS
  automaton_t a = make_automaton (alphabet_t ());
# else
  automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t ());
# endif // !WITH_TWO_ALPHABETS

  switch (f)
    {
    case INPUT_TYPE_XML:
      std::cin >> automaton_loader(a, string_out (), XML ());
      break;
# ifndef WITH_TWO_ALPHABETS
    case INPUT_TYPE_FSM:
      fsm_load(std::cin, a);
      break;
# endif // !WITH_TWO_ALPHABETS
    default:
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
  return a;
}

template<typename T>
automaton_t
automaton_getter::operator()(T&) const
{
  std::cerr << command
	    << ": Incorrect input type"
	    << std::endl;
  exit (1);
}


# ifndef WITH_TWO_ALPHABETS
rat_exp_getter::rat_exp_getter(alphabet_t a, std::string& cmd,
			       input_format_t f,
			       const monoid_rep_t& mrep,
			       const series_rep_t& srep)
  : alphabet(a),
    command(cmd),
    mrep_(mrep),
    srep_(srep),
    f(f)
{
}

rat_exp_t
rat_exp_getter::operator() (std::string& str) const
{
  switch (f)
    {
    case INPUT_TYPE_XML:
      {
	alphabet_t	alphabet;
        monoid_t	monoid(alphabet, mrep_);
        semiring_t	semiring;
        series_set_t	series(semiring, monoid, srep_);
        rat_exp_t	e(series);
	std::istringstream is(str);
	is >> regexp_loader(e, string_out (), XML ());
	return e;
      }
    case INPUT_TYPE_EXP:
      break;
    default:
      std::cerr << "FATAL: Unsupported expression format." << std::endl;
      exit(1);
    }
  return make_rat_exp (alphabet, str, mrep_, srep_);
}

rat_exp_t
rat_exp_getter::operator() (command_output_status& i) const
{
  if (i != PIPE_GET_FROM_STDIN)
    {
      if (i == PIPE_BENCH)
	{
	  std::cerr << "Impossible to benchmark the sequence:\n"
		       "The first task reads from stdin."
		    << std::endl;
	  exit (1);
	}
      std::cerr << command
		<< ": Incorrect input type"
		<< std::endl;
      exit (1);
    }

  switch (f)
    {
    case INPUT_TYPE_XML:
      {
	alphabet_t	alphabet;
        monoid_t	monoid(alphabet, mrep_);
        semiring_t	semiring;
        series_set_t	series(semiring, monoid, srep_);
        rat_exp_t	e(series);
	std::cin >> regexp_loader(e, string_out (), XML ());
	return e;
      }
    case INPUT_TYPE_EXP:
      break;
    default:
      std::cerr << "FATAL: Unsupported expression format." << std::endl;
      exit(1);
    }

  std::string str;
  std::cin >> str;
  return make_rat_exp (alphabet, str, mrep_, srep_);
}

rat_exp_t
rat_exp_getter::operator() (rat_exp_t& e) const
{
  return e;
}

template<typename T>
rat_exp_t
rat_exp_getter::operator() (T&) const
{
  std::cerr << command
	    << ": Incorrect input type"
	    << std::endl;
  exit (1);
}
# endif // !WITH_TWO_ALPHABETS


# ifdef WITH_TWO_ALPHABETS
boolean_automaton_getter::boolean_automaton_getter (std::string& cmd,
						    input_format_t fmt)
  : command (cmd),
    f (fmt)
{
}

IOAUT_CONTEXT::automaton_t
boolean_automaton_getter::operator() (IOAUT_CONTEXT::automaton_t& a) const
{
  return a;
}

IOAUT_CONTEXT::automaton_t
boolean_automaton_getter::operator() (std::string& str) const
{
  std::istringstream is (str);

  // Representations will be build by the automaton loader.
  IOAUT_CONTEXT::automaton_t a =
    IOAUT_CONTEXT::make_automaton (first_alphabet_t());

  switch (f)
    {
    case INPUT_TYPE_XML:
      is >> automaton_loader(a, string_out (), XML ());
      break;
    case INPUT_TYPE_FSM:
      fsm_load(is, a);
      break;
    default:
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
  return a;
}

IOAUT_CONTEXT::automaton_t
boolean_automaton_getter::operator() (command_output_status& i) const
{
  if (i != PIPE_GET_FROM_STDIN)
    {
      std::cerr << command
		<< ": Incorrect input type"
		<< std::endl;
      exit (1);
    }

  // Representations will be build by the automaton loader.
  IOAUT_CONTEXT::automaton_t a =
    IOAUT_CONTEXT::make_automaton (first_alphabet_t ());

  switch (f)
    {
    case INPUT_TYPE_XML:
      std::cin >> automaton_loader(a, string_out (), XML ());
      break;
    case INPUT_TYPE_FSM:
      fsm_load(std::cin, a);
      break;
    default:
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
  return a;
}

template<typename T>
IOAUT_CONTEXT::automaton_t
boolean_automaton_getter::operator() (T&) const
{
  std::cerr << command
	    << ": Incorrect input type"
	    << std::endl;
  exit (1);
}
# endif // !WITH_TWO_ALPHABETS

#endif /* !PIPE_GETTERS_HXX */
