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

  /*-----------------------------.
  | Define the set of commands.	 |
  `-----------------------------*/

const command_t command_map[] =
{
  COMMAND_GROUP (
    "Input/output work with automata:",

    COMMAND_ENTRY (define_automaton, File,
		   "Define an automaton from scratch."),
    COMMAND_ENTRY (display, Aut, "Display `aut'."),
    COMMAND_ENTRY (dot_dump, Aut, "Dump dot output of `aut'."),
    COMMAND_ENTRY (dump_automaton, File, "Dump a predefined automaton."),
    COMMAND_ENTRY (edit_automaton, File, "Edit an existing automaton."),
    COMMAND_ENTRY (identity, Aut, "Return `aut'."),
    COMMAND_ENTRY (info, Aut, "Print useful infos about `aut'."),
    COMMAND_ENTRY (list_automata, Nil, "List predefined automata.")

    ),

  COMMAND_GROUP (
    "Tests and evaluation on automata:",

    COMMAND_ENTRY (are_isomorphic, AutAut,
		   "Return whether `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (eval, AutWord, "Evaluate `word' on `aut'."),
    COMMAND_ENTRY (is_ambiguous, Aut,
		   "Return whether `aut' is ambiguous."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Return whether trimed `aut' is empty."),
    COMMAND_ENTRY (is_normalized, Aut,
		   "Return whether `aut' is normalized."),
    COMMAND_ENTRY (is_realtime, Aut,
		   "Return whether `aut' is realtime."),
    COMMAND_ENTRY (is_standard, Aut,
		   "Return whether `aut' is standard.")
    ),

  COMMAND_GROUP (
    "Generic algorithms for automata:",

    COMMAND_ENTRY (accessible, Aut,
		   "Give the maximal accessible subautomaton of `aut'."),
    COMMAND_ENTRY (closure, Aut,
		   "Give `aut' closed over epsilon transitions."),
    COMMAND_ENTRY_CN (co-accessible, coaccessible, Aut,
		      "Give the maximal coaccessible subautomaton of `aut'."),
    COMMAND_ENTRY (concatenate, AutAut, "Concatenate `aut1' and `aut2'."),
    COMMAND_ENTRY (normalize, Aut,
		   "Give the Thompson-normalized automaton of `aut'."),
    COMMAND_ENTRY (power, AutInt, "Give the power of `aut' by `n'."),
    COMMAND_ENTRY (product, AutAut, "Give the product of `aut1' by `aut2'." ),
    COMMAND_ENTRY (quotient, Aut, "Give the quotient of `aut'."),
    COMMAND_ENTRY (realtime, Aut, "Give the realtime version of `aut'."),
    COMMAND_ENTRY (standardize, Aut, "Give the standard automaton of `aut'."),
    COMMAND_ENTRY (sum, AutAut, "Give the sum of `aut1' and `aut2'."),
    COMMAND_ENTRY (transpose, Aut, "Transpose the automaton `aut'."),
    COMMAND_ENTRY (trim, Aut, "Trim the automaton `aut'.")

    ),

  COMMAND_GROUP (
    "Conversion between automata and expressions:",

    COMMAND_ENTRY (aut_to_exp, Aut,
		   "Give the automaton associated to `aut'."),
    COMMAND_ENTRY_CN (derived-term, derived_term_automaton, Exp,
		      "Use derivative to compute the automaton of `exp'."),
    COMMAND_ENTRY_CN (exp-to-aut, standard_of, Exp,
		      "Alias of `stardard'."),
    COMMAND_ENTRY (expand, Exp, "Expand `exp'."),
    COMMAND_ENTRY_CN (standard, standard_of, Exp,
		      "Give the standard automaton of `exp'."),
    COMMAND_ENTRY_CN (thompson, thompson_of, Exp,
		      "Give the Thompson automaton of `exp'.")
    ),

  {0, 0, 0, 0, 0}
};
