// common_automaton_commands.hh: this file is part of Vaucanson.
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
#ifndef COMMON_AUTOMATON_COMMANDS_HH
# define COMMON_AUTOMATON_COMMANDS_HH

/**
 * @file   common_automaton_commands.hh
 * @author Guillaume Leroi
 * @date   Mon Jul 24 16:57:33 2006
 *
 * @brief Commands declarations and definitions specific for automata.
 *
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
# include "edition_commands.hh"
# include "library_commands.hh"
# include "commands.hh"
# include "commands_macros.hh"


  /*---------------------------------------.
  | Command definition (RatExp excluded).  |
  `---------------------------------------*/


DEFINE_IS_PROPERTY_COMMAND (ambiguous);

//DEFINE_IS_PROPERTY_COMMAND (normalized);

DEFINE_IS_PROPERTY_COMMAND (realtime);

//DEFINE_IS_PROPERTY_COMMAND (standard);

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (realtime));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (coaccessible));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (accessible));

//DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
//			ALGO (normalize));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (quotient)
				  ARG_KIND (aut)
				  ALGOS (quotient, realtime));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (sum));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (product));

DEFINE_TWO_ARGS_COMMAND (ARG_KIND (aut)
			 ALGO (concatenate));

DEFINE_COMMAND (NAME (eval)
		CODE (/* Empty */)
		OUTPUT (
		  eval (realtime (get_aut (args.args[1])),
			std::string (args.args[2])) << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (power)
		CODE (int n = atoi (args.args[2]);
		      automaton_t a = get_aut (args.args[1]);
		      automaton_t p (a);
		      for (int i = 1; i < n; ++i)
			p = product (p, a))
		OUTPUT (automaton_saver (p, string_out (), XML ()))
		RETURNVALUE (0));

//DEFINE_COMMAND (NAME (standardize)
//		CODE (automaton_t a = get_aut (args.args[1]);
//		      standardize (a))
//		OUTPUT (automaton_saver (a, string_out (), XML ()))
//		RETURNVALUE (0));

#endif // ! COMMON_AUTOMATON_COMMANDS_HH
