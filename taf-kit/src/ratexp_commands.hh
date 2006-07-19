// ratexp_commands.hh: this file is part of Vaucanson.
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
#ifndef RATEXP_COMMANDS_HH
# define RATEXP_COMMANDS_HH

/**
 * @file ratexp_commands.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Command declarations and definitions for all the types of automata.
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
# include "commands.hh"
# include "commands_macros.hh"


  /*---------------------------------------------------.
  | Command definition of RatExp specific algorithms.  |
  `---------------------------------------------------*/

DEFINE_ONE_ARG_COMMAND (ARG_KIND (exp)
			ALGO (standard_of));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (exp)
			ALGO (thompson_of));

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

DEFINE_COMMAND (NAME (expand)
		CODE (/* Empty */)
		OUTPUT (expand (get_exp (args.args[1])))
		RETURNVALUE (0));

#endif /* !RATEXP_COMMANDS_HH */
