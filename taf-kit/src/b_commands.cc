// b_commands.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008 The Vaucanson Group.
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


/**
 * @file b_commands.c
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration and definition for Boolean automata.
 */

#include "commands.hh"
#include "ratexp_commands.hh"
#include "common_commands.hh"
#include "common_automaton_commands.hh"

  /*-------------------.
  | Command definition |
  `-------------------*/

DEFINE_IS_PROPERTY_COMMAND (deterministic);

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (determinize)
				  ARG_KIND (aut)
				  ALGOS (determinize, realtime));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (complement));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (minimization_hopcroft));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (minimization_moore));

DEFINE_COMMAND (NAME (are_equivalent)
		CODE (bool b = are_equivalent (get_aut (args, 1),
					       get_aut (args, 2)))
		OUTPUT_ON_VERBOSE (
		  (b
		   ? "Automata are equivalent\n"
		   : "Automata are not equivalent\n"))
		RETURNVALUE (b ? 0 : 1));

  /*-----------------------------.
  | Define the set of commands.	 |
  `-----------------------------*/

const command_t command_map[] =
{
  USE_IO_COMMAND_GROUP (),

  COMMAND_GROUP (
    "Tests and evaluation on automata:",

    COMMAND_ENTRY (are_equivalent, AutAut,
		   "Do `Aut1' and `Aut2' recognize the same language?"),
//    COMMAND_ENTRY (are_isomorphic, AutAut,
//		   "Return whether `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (eval, AutWord, "Evaluate `word' on `aut'."),
    COMMAND_ENTRY (is_ambiguous, Aut,
		   "Return whether `aut' is ambiguous."),
    COMMAND_ENTRY (is_complete, Aut,
		   "Return whether `aut' is complete."),
    COMMAND_ENTRY (is_deterministic, Aut,
		   "Return whether `aut' is deterministic."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Return whether `aut' is empty."),
    COMMAND_ENTRY (has_succ_comp, Aut,
		   "Return whether `aut' has successful computations"
		   " (trimmed `aut` is not empty)."),
    //    COMMAND_ENTRY (is_normalized, Aut,
    //		   "Return whether `aut' is normalized."),
    COMMAND_ENTRY (is_realtime, Aut,
		   "Return whether `aut' is realtime."),
    COMMAND_ENTRY (is_standard, Aut,
		   "Return whether `aut' is standard.")

    ),

  USE_GENERIC_AUTOMATON_COMMAND_GROUP (),

  COMMAND_GROUP (
    "Boolean automaton specific algorithms:",

    COMMAND_ENTRY (complement, Aut, "Complement `aut'."),
    COMMAND_ENTRY (determinize, Aut,
		   "Give the determinized automaton of `aut'."),
    COMMAND_ENTRY_CN (minimize, minimization_hopcroft, Aut,
		      "Give the minimized of `aut' (Hopcroft algorithm)."),
    COMMAND_ENTRY_CN (minimize-moore, minimization_moore, Aut,
		      "Give the minimized of `aut' (Moore algorithm).")
    ),

  USE_RATEXP_COMMAND_GROUP (),

  {0, 0, 0, 0, 0}
};

LETTER_CONTEXT(letter_t)
