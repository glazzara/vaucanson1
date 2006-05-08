// common_commands.hh: this file is part of Vaucanson.
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
#ifndef COMMON_COMMANDS_HH
# define COMMON_COMMANDS_HH

/**
 * @file common_commands.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration and definition for all type of automata.
 */

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/dot_display.hh>
# include <vaucanson/tools/dot_dump.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::io;
using vcsn::xml::XML;

# include <cstdlib>
# include <iostream>

# include "getters.hh"
# include "edit_automaton.hh"
# include "commands.hh"
# include "commands_macros.hh"


  /*-------------------.
  | Command definition |
  `-------------------*/

DEFINE_IS_PROPERTY_COMMAND (normalized);

DEFINE_IS_PROPERTY_COMMAND (realtime);

DEFINE_IS_PROPERTY_COMMAND (standard);

DEFINE_ONE_ARG_COMMAND (ARG_KIND (exp)
			ALGO (standard_of));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (exp)
			ALGO (thompson_of));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (trim));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (transpose));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (realtime));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (coaccessible));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (accessible));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (normalize));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (minimization_hopcroft));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (minimization_moore));


DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (quotient)
				  ARG_KIND (aut)
				  ALGOS (quotient, realtime));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (closure)
				  ARG_KIND (aut)
				  ALGOS (accessible, closure));


DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (sum));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (product));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (concatenate));


DEFINE_COMMAND (NAME (derived_term_automaton)
		CODE (
		  rat_exp_t   e = get_exp (args.args[1]);
		  automaton_t a = make_automaton (get_alphabet (args.alphabet));
		  derived_term_automaton (a, e))
		OUTPUT (automaton_saver (a, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (aut_to_exp)
		CODE (/* Empty */)
		OUTPUT (aut_to_exp (get_aut (args.args[1]), DMChooser ())
			<< std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (are_isomorphic)
		CODE (bool b = are_isomorphic (get_aut (args.args[1]),
					       get_aut (args.args[2])))
		OUTPUT (b << std::endl)
		RETURNVALUE (b ? 0 : 1));

DEFINE_COMMAND (NAME (eval)
		CODE (/* Empty */)
		OUTPUT (
		  eval (realtime (get_aut (args.args[1])), args.args[2])
		  << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (is_empty)
		CODE (
		  int states = trim (get_aut (args.args[1])).states ().size ())
		OUTPUT_ON_VERBOSE (
		  (states ? "Entry is not empty\n" : "Entry is empty\n"))
		RETURNVALUE (states == 0 ? 0 : 1));

DEFINE_COMMAND (NAME (power)
		CODE (int n = atoi (args.args[2].c_str ());
		      automaton_t a = get_aut (args.args[1]);
		      automaton_t p (a);
		      for (int i = 1; i < n; ++i)
			p = product (p, a))
		OUTPUT (automaton_saver (p, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (expand)
		CODE (/* Empty */)
		OUTPUT (expand (get_exp (args.args[1])))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (info)
		CODE (automaton_t a = get_aut (args.args[1]))
		OUTPUT (
		  "States: " << a.states ().size () << std::endl
		  << "Transitions: " << a.transitions ().size () << std::endl
		  << "Initial states: " << a.initial ().size () << std::endl
		  << "Final states: " << a.final ().size () << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (standardize)
		CODE (automaton_t a = get_aut (args.args[1]);
		      standardize (a))
		OUTPUT (automaton_saver (a, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (display)
		CODE (
		  bool b = vcsn::tools::dot_display (get_aut(args.args[1]),
						     "A", true))
		OUTPUT ("")
		RETURNVALUE ((b ? 0 : 1)));

DEFINE_COMMAND (NAME (dump)
		CODE (
		  vcsn::tools::dot_dump (std::cout,
					 get_aut(args.args[1]),
					 "A"))
		OUTPUT ("")
		RETURNVALUE (0));

#endif /* !COMMON_COMMANDS_HH */
