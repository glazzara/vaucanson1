// b_commands.cc: this file is part of the Vaucanson project.
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
 * @file b_commands.c
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration and definition for Boolean automata.
 */

#include "commands.hh"
#include "common_commands.hh"

  /*-------------------.
  | Command definition |
  `-------------------*/

DEFINE_IS_PROPERTY_COMMAND (complete);

DEFINE_IS_PROPERTY_COMMAND (deterministic);

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (complete));

DEFINE_ONE_ARG_COMMAND_TWO_ALGOS (NAME (determinize)
				  ARG_KIND (aut)
				  ALGOS (determinize, realtime));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (complement));

  /*-----------------------------.
  | Define the set of commands.  |
  `-----------------------------*/

static const command_t command_map[] =
{
  COMMAND_GROUP (
    "Input/output work with automata:",

    COMMAND_ENTRY_CN (define-automaton, define_automaton, File,
		      "Define an automaton from scratch."),
    COMMAND_ENTRY (display, Aut, "Display `aut'."),
    COMMAND_ENTRY_CN (edit-automaton, edit_automaton, File,
		      "Edit an existing automaton."),
    COMMAND_ENTRY (info, Aut, "Print useful infos about `aut'.")),

  COMMAND_GROUP (
    "Tests and evaluation on automata:",

    COMMAND_ENTRY_CN (are-isomorphic, are_isomorphic, AutAut,
		      "Return whether `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (eval, AutWord, "Evaluate `word' on `aut'."),
    COMMAND_ENTRY_CN (is-complete, is_complete, Aut,
		      "Return whether `aut' is complete."),
    COMMAND_ENTRY_CN (is-deterministic, is_deterministic, Aut,
		      "Return whether `aut' is deterministic."),
    COMMAND_ENTRY_CN (is-empty, is_empty, Aut,
		      "Return whether trimed `aut' is empty."),
    COMMAND_ENTRY_CN (is-normalized, is_normalized, Aut,
		      "Return whether `aut' is normalized."),
    COMMAND_ENTRY_CN (is-realtime, is_realtime, Aut,
		      "Return whether `aut' is realtime."),
    COMMAND_ENTRY_CN (is-standard, is_standard, Aut,
		      "Return whether `aut' is standard.")),

  COMMAND_GROUP (
    "Generic algorithms for automata:",

    COMMAND_ENTRY (accessible, Aut,
		   "Give the maximal accessible subautomaton of `aut'."),
    COMMAND_ENTRY (closure, Aut,
		   "Give `aut' closed over epsilon transitions."),
    COMMAND_ENTRY_CN (co-accessible, coaccessible, Aut,
		      "Give the maximal coaccessible subautomaton of `aut'."),
    COMMAND_ENTRY (complement, Aut, "Complement `aut1'."),
    COMMAND_ENTRY (complete, Aut, "Give the complete version of `aut1'."),
    COMMAND_ENTRY (concatenate, AutAut, "Concatenate `aut1' and `aut2'."),
    COMMAND_ENTRY (determinize, Aut,
		   "Give the determinized automaton of `aut'."),
    COMMAND_ENTRY_CN (minimize, minimization_hopcroft, Aut,
		      "Give the minimized of `aut' (Hopcroft algorithm)."),
    COMMAND_ENTRY_CN (minimize-moore, minimization_moore, Aut,
		      "Give the minimized of `aut' (Moore algorithm)."),
    COMMAND_ENTRY (normalize, Aut,
		   "Give the Thompson-normalized automaton of `aut'."),
    COMMAND_ENTRY (power, AutInt, "Give the power of `aut' by `n'."),
    COMMAND_ENTRY (product, AutAut, "Give the product of `aut1' by `aut2'." ),
    COMMAND_ENTRY (quotient, Aut, "Give the quotient of `aut'."),
    COMMAND_ENTRY (realtime, Aut, "Give the realtime version of `aut'."),
    COMMAND_ENTRY (standardize, Aut, "Give the standard automaton of `aut'."),
    COMMAND_ENTRY (sum, AutAut, "Give the sum of `aut1' and `aut2'."),
    COMMAND_ENTRY (transpose, Aut, "Transpose the automaton `aut'."),
    COMMAND_ENTRY (trim, Aut, "Trim the automaton `aut'.")),

  COMMAND_GROUP (
    "Conversion between automata and expressions:",

    COMMAND_ENTRY_CN (aut-to-exp, aut_to_exp, Aut,
		      "Give the automaton associated to `aut'."),
    COMMAND_ENTRY_CN (derived-term, derived_term_automaton, Exp,
		      "Use derivative to compute the automaton of `exp'."),
    COMMAND_ENTRY_CN (exp-to-aut, standard_of, Exp,
		      "Alias of `stardard_of'."),
    COMMAND_ENTRY (expand, Exp, "Expand `exp'."),
    COMMAND_ENTRY_CN (standard, standard_of, Exp,
		      "Give the standard automaton of `exp'."),
    COMMAND_ENTRY_CN (thompson, thompson_of, Exp,
		      "Give the Thompson automaton of `exp'.")),
  {0, 0, 0, 0, 0}
};


  /*----------.
  | Interface |
  `----------*/


/// List all the commands.
void list_commands ()
{
  echo ("List of available commands:");
  for (const command_t* command = command_map; command->docstring; ++command)
    if (command->name)
      echo ("   - " << command->name << " " << command->params
	    << ": " << command->docstring);
    else
      echo (" * " << command->docstring);
}

/**
 * Execute an command according to the program's arguments.
 *
 * @param args Arguments.
 *
 * @return -1 on wrong number of args, -2 on inexistent algo,
 *         the result of the command otherwise.
 */
int execute_command (const arguments_t& args)
{
  for (const command_t* command = command_map; command->docstring; ++command)
    if (command->name && command->name == args.args[0])
    {
      if (command->n_params != args.n_args - 1)
      {
	warn (args.progname << ": wrong number of arguments for `"
	      << command->name << " " << command->params << "' (should be "
	      << command->n_params << ").");
	warn ("Try `" << args.progname << " --list-commands'"
	      << " for more information.");
	return -1;
      }
      return command->command (args);
    }
  warn (args.progname << ": command `" << args.args[0] << "' doesn't exist.");
  return -2;
}
