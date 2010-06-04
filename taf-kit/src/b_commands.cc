// b_commands.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008, 2009, 2010 The Vaucanson Group.
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

static int
is_deterministic_command(const arguments_t& args)
{
  bool b = is_deterministic(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is deterministic\n" :
		     "Input is not neterministic\n");
  return !b;
}

static int
determinize_command(const arguments_t& args)
{
  g_res.keep(determinize(realtime(get_aut(args, 1))));
  return 0;
}

static int
complement_command(const arguments_t& args)
{
  g_res.keep(complement(get_aut(args, 1)));
  return 0;
}

static int
minimization_hopcroft_command(const arguments_t& args)
{
  g_res.keep(minimization_hopcroft(get_aut(args, 1)));
  return 0;
}

static int
minimization_moore_command(const arguments_t& args)
{
  g_res.keep(minimization_moore(get_aut(args, 1)));
  return 0;
}

static int
are_equivalent_command(const arguments_t& args)
{
  bool b = are_equivalent(get_aut(args, 1), get_aut(args, 2));
  if (args.verbose)
    g_res.stream << (b ? "Automata are equivalent\n" :
		     "Automata are not equivalent\n");
  return !b;
}

  /*-----------------------------.
  | Define the set of commands.	 |
  `-----------------------------*/

const command_t command_map[] =
{
  USE_IO_COMMAND_GROUP(),

  COMMAND_GROUP(
    "Tests and evaluation on automata:",

    COMMAND_ENTRY(are_equivalent, AutAut,
		   "Do `Aut1' and `Aut2' recognize the same language?"),
//    COMMAND_ENTRY(are_isomorphic, AutAut,
//		   "Return whether `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY(eval, AutWord, "Evaluate `word' on `aut'."),
    COMMAND_ENTRY(is_ambiguous, Aut,
		  "Return whether `aut' is ambiguous."),
    COMMAND_ENTRY(is_complete, Aut,
		  "Return whether `aut' is complete."),
    COMMAND_ENTRY(is_deterministic, Aut,
		  "Return whether `aut' is deterministic."),
    COMMAND_ENTRY(is_empty, Aut,
		  "Return whether `aut' is empty."),
    COMMAND_ENTRY(is_useless, Aut,
		  "Return whether `aut' has no successful computations"
		  " (trimmed `aut` is empty)."),
    COMMAND_ENTRY(is_proper, Aut,
		  "Return whether `aut' has no spontaneous transitions."),
    //    COMMAND_ENTRY(is_normalized, Aut,
    //		  "Return whether `aut' is normalized."),
    COMMAND_ENTRY(is_realtime, Aut,
		  "Return whether `aut' is realtime."),
    COMMAND_ENTRY(is_standard, Aut,
		  "Return whether `aut' is standard."),
    COMMAND_ENTRY(is_normalized, Aut,
		  "Return whether `aut' is normalized.")

    ),

  USE_GENERIC_AUTOMATON_COMMAND_GROUP(),

  COMMAND_GROUP(
    "Boolean automaton specific algorithms:",

    COMMAND_ENTRY(complement, Aut, "Complement `aut'."),
    COMMAND_ENTRY(determinize, Aut,
		  "Give the determinized automaton of `aut'."),
    COMMAND_ENTRY_CN(minimize, minimization_hopcroft, Aut,
		     "Give the minimized of `aut' (Hopcroft algorithm)."),
    COMMAND_ENTRY_EXPERT_CN(minimize-moore, minimization_moore, Aut,
			    "Give the minimized of `aut' (Moore algorithm).")
    ),

  USE_RATEXP_COMMAND_GROUP(),

  {0, 0, 0, 0, 0}
};

LETTER_CONTEXT(letter_t)
