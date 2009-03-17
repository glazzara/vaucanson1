// pipe_getters.hh: this file is part of the Vaucanson project.
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

#ifndef PIPE_GETTERS_HH
# define PIPE_GETTERS_HH

/**
 * @file pipe_getters.hh
 *
 * This file contains boost variant visitors and
 * is to be included within getters.hh
 */

# include <boost/variant.hpp>

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;

class automaton_getter
  : public boost::static_visitor<automaton_t>
{
public:
  automaton_getter (std::string& command, input_format_t);

  automaton_t operator() (automaton_t& a) const;
  automaton_t operator() (std::string& str) const;
  automaton_t operator() (command_output_status& i) const;

  template<typename T>
  automaton_t operator() (T&) const;

  std::string command;
  input_format_t f;
};

# ifndef WITH_TWO_ALPHABETS
class rat_exp_getter
  : public boost::static_visitor<rat_exp_t>
{
public:
  rat_exp_getter (alphabet_t, std::string& command,
		  input_format_t,
		  const monoid_rep_t& mrep,
		  const series_rep_t& srep);

  rat_exp_t operator() (std::string& str) const;
  rat_exp_t operator() (command_output_status& i) const;
  rat_exp_t operator() (rat_exp_t& e) const;

  template<typename T>
  rat_exp_t operator() (T&) const;

  alphabet_t alphabet;
  std::string command;
  const monoid_rep_t& mrep_;
  const series_rep_t& srep_;
  input_format_t f;
};
# endif // !WITH_TWO_ALPHABETS

# ifdef WITH_TWO_ALPHABETS
class boolean_automaton_getter
  : public boost::static_visitor<IOAUT_CONTEXT::automaton_t>
{
public:
  boolean_automaton_getter (std::string& command, input_format_t);

  IOAUT_CONTEXT::automaton_t
  operator() (IOAUT_CONTEXT::automaton_t& a) const;

  IOAUT_CONTEXT::automaton_t
  operator() (std::string& str) const;

  IOAUT_CONTEXT::automaton_t operator() (command_output_status& i) const;

  template<typename T>
  IOAUT_CONTEXT::automaton_t operator() (T&) const;

  std::string command;
  input_format_t f;
};
# endif // !WITH_TWO_ALPHABETS

#endif /* !PIPE_GETTERS_HH */
