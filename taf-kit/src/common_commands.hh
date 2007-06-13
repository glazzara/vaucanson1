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
# include "edition_commands.hh"
# include "library_commands.hh"
# include "commands.hh"
# include "commands_macros.hh"


  /*---------------------------------------.
  | Command definition (RatExp excluded).  |
  `---------------------------------------*/


DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (trim));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (eps_removal)
				  ARG_KIND (aut)
				  ALGOS (accessible, eps_removal));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (eps_removal_sp)
				  ARG_KIND (aut)
				  ALGOS (accessible, eps_removal_sp));

DEFINE_COMMAND (NAME (are_isomorphic)
		CODE (bool b = are_isomorphic (get_aut (args.args[1]),
					       get_aut (args.args[2])))
		OUTPUT_ON_VERBOSE (
		  (b
		   ? "Automata are isomorphic\n"
		   : "Automata are not isomorphic\n"))
		RETURNVALUE (b ? 0 : 1));

DEFINE_COMMAND (NAME (is_empty)
		CODE (
		  int states = trim (get_aut (args.args[1])).states ().size ())
		OUTPUT_ON_VERBOSE (
		  (states ? "Entry is not empty\n" : "Entry is empty\n"))
		RETURNVALUE (states == 0 ? 0 : 1));

DEFINE_COMMAND (NAME (info)
		CODE (automaton_t a = get_aut (args.args[1]))
		OUTPUT (
		  "States: " << a.states ().size () << std::endl
		  << "Transitions: " << a.transitions ().size () << std::endl
		  << "Initial states: " << a.initial ().size () << std::endl
		  << "Final states: " << a.final ().size () << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (identity)
		CODE (automaton_t a = get_aut (args.args[1]))
		OUTPUT (automaton_saver (a, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (display)
		CODE (
		  bool b = vcsn::tools::dot_display (get_aut(args.args[1]),
						     "A", true))
		OUTPUT ("")
		RETURNVALUE ((b ? 0 : 1)));

DEFINE_COMMAND (NAME (dot_dump)
		CODE (
		  vcsn::tools::dot_dump (std::cout,
					 get_aut(args.args[1]),
					 "A"))
		OUTPUT ("")
		RETURNVALUE (0));

# define USE_IO_COMMAND_GROUP()						\
  COMMAND_GROUP (							\
    "Input/output work:",						\
									\
    COMMAND_ENTRY (define_automaton, File,				\
		   "Define an automaton from scratch."),		\
    COMMAND_ENTRY (display, Aut, "Display `aut'."),			\
    COMMAND_ENTRY (dot_dump, Aut,					\
		   "Dump dot output of `aut'."),			\
    COMMAND_ENTRY (dump_automaton, File, "Dump a predefined automaton."), \
    COMMAND_ENTRY (edit_automaton, File,				\
		   "Edit an existing automaton."),			\
    COMMAND_ENTRY (identity, Aut, "Return `aut'."),			\
    COMMAND_ENTRY (info, Aut, "Print useful infos about `aut'."),	\
    COMMAND_ENTRY (list_automata, Nil, "List predefined automata.")	\
									\
    )

#endif /* !COMMON_COMMANDS_HH */
