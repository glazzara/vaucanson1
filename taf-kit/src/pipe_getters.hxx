// pipe_getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

automaton_t 
automaton_getter::operator() (automaton_t& a) const
{
  return a;
}

automaton_t 
automaton_getter::operator() (std::string& str) const
{
  std::istringstream is (str);

# ifndef WITH_TWO_ALPHABETS
  automaton_t a = make_automaton (alphabet_t ());
# else
  automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t ());
# endif // !WITH_TWO_ALPHABETS

  is >> automaton_loader (a, string_out (), XML ());
  return a;
}

automaton_t 
automaton_getter::operator() (int& i) const
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
      std::cerr << "Last command does not return an automaton"
		<< std::endl;
      exit (1);
    }

# ifndef WITH_TWO_ALPHABETS
  automaton_t a = make_automaton (alphabet_t ());
# else
  automaton_t a = make_automaton (first_alphabet_t (), second_alphabet_t ());
# endif // !WITH_TWO_ALPHABETS

  std::cin >> automaton_loader (a, string_out (), XML ());
  return a;
}

template<typename T>
automaton_t 
automaton_getter::operator()(T&) const
{
  std::cerr << "Last command does not return an automaton"
	    << std::endl;
  exit (1);
}


# ifndef WITH_TWO_ALPHABETS
rat_exp_getter::rat_exp_getter (alphabet_t a)
  : alphabet (a)
{
}

rat_exp_t
rat_exp_getter::operator() (std::string& str) const
{
  return make_rat_exp (alphabet, str);
}

rat_exp_t
rat_exp_getter::operator() (int& i) const
{
  std::string str;

  if (i != PIPE_GET_FROM_STDIN)
    {
      if (i == PIPE_BENCH)
	{
	  std::cerr << "Impossible to benchmark the sequence:\n"
		       "The first task reads from stdin."
		    << std::endl;
	  exit (1);
	}
      std::cerr << "Last command does not return a regular expression"
		<< std::endl;
      exit (1);
    }

  std::cin >> str;
  return make_rat_exp (alphabet, str);
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
  std::cerr << "Last command does not return a regular expression"
	    << std::endl;
  exit (1);
}
# endif // !WITH_TWO_ALPHABETS


# ifdef WITH_TWO_ALPHABETS
boolean_automaton::automaton_t
boolean_automaton_getter::operator()
  (boolean_automaton::automaton_t& a) const
{
  return a;
}

boolean_automaton::automaton_t
boolean_automaton_getter::operator() (std::string& str) const
{
  std::istringstream is (str);

  boolean_automaton::automaton_t a =
    boolean_automaton::make_automaton (first_alphabet_t());
  is >> automaton_loader (a, string_out (), XML ());
  return a;
}

boolean_automaton::automaton_t
boolean_automaton_getter::operator() (int& i) const
{
  if (i != PIPE_GET_FROM_STDIN)
    {
      std::cerr << "Last command does not return an automaton"
		<< std::endl;
      exit (1);
    }

  boolean_automaton::automaton_t a =
    boolean_automaton::make_automaton (first_alphabet_t ());

  std::cin >> automaton_loader (a, string_out (), XML ());
  return a;
}

template<typename T>
boolean_automaton::automaton_t
boolean_automaton_getter::operator() (T&) const
{
  std::cerr << "Last command does not return an automaton"
	    << std::endl;
  exit (1);
}
# endif // !WITH_TWO_ALPHABETS

#  if (false)
boolean_transducer::automaton_t
boolean_transducer_getter::operator()
  (boolean_transducer::automaton_t& a) const
{
  return a;
}

boolean_transducer::automaton_t
boolean_transducer_getter::operator() (std::string& str) const
{
  std::istringstream is (str);

  boolean_transducer::automaton_t a =
    boolean_transducer::make_automaton (first_alphabet_t());
  is >> automaton_loader (a, string_out (), XML ());
  return a;
}

boolean_transducer::automaton_t
boolean_transducer_getter::operator() (int& i) const
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
      std::cerr << "Last command does not return an automaton"
		<< std::endl;
      exit (1);
    }

  boolean_transducer::automaton_t a =
    boolean_transducer::make_automaton (first_alphabet_t ());

  std::cin >> automaton_loader (a, string_out (), XML ());
  return a;
}

template<typename T>
boolean_transducer::automaton_t
boolean_transducer_getter::operator() (T&) const
{
  std::cerr << "Last command does not return an automaton"
	    << std::endl;
  exit (1);
}
#endif // false

#endif /* !PIPE_GETTERS_HXX */
