// z_commands.cc: this file is part of the Vaucanson project.
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


/**
 * @file z_commands.c
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration and definition for Z weighted automata.
 */

#include "commands.hh"
#include "ratexp_commands.hh"
#include "common_commands.hh"
#include "common_automaton_commands.hh"

  /*-----------------------------.
  | Define the set of commands.	 |
  `-----------------------------*/

const command_t command_map[] =
{
  USE_IO_COMMAND_GROUP (),

  COMMAND_GROUP (
    "Tests and evaluation on automata:",

    COMMAND_ENTRY (are_isomorphic, AutAut,
		   "Return whether `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (eval, AutWord, "Evaluate `word' on `aut'."),
    COMMAND_ENTRY (is_ambiguous, Aut,
		   "Return whether `aut' is ambiguous."),
    COMMAND_ENTRY (is_complete, Aut,
		   "Return whether `aut' is complete."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Return whether trimed `aut' is empty."),
    //    COMMAND_ENTRY (is_normalized, Aut,
    //		   "Return whether `aut' is normalized."),
    COMMAND_ENTRY (is_realtime, Aut,
		   "Return whether `aut' is realtime."),
    COMMAND_ENTRY (is_standard, Aut,
		   "Return whether `aut' is standard.")
    ),

  USE_GENERIC_AUTOMATON_COMMAND_GROUP (),

  USE_RATEXP_COMMAND_GROUP (),

  {0, 0, 0, 0, 0}
};
