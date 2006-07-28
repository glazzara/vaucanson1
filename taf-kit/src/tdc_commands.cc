// tdc_commands.cc: this file is part of the Vaucanson project.
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
 * @file   tdc_commands.cc
 * @author Guillaume Leroi
 * @date   Thu Jul 20 17:24:46 2006
 *
 * Command declarations and definitions for transducers over free monoid
 * product.
 */

#include "commands.hh"
#include "common_commands.hh"

/*-------------------.
| Command definition |
`-------------------*/

DEFINE_IS_PROPERTY_COMMAND (sub_normalized);

DEFINE_COMMAND (NAME (compose)
		CODE (
		  automaton_t a = get_aut(args.args[1]);
		  automaton_t b = get_aut(args.args[2]);

		  if (!is_sub_normalized(a))
		    sub_normalize_here(a);

		  if (!is_sub_normalized(b))
		    sub_normalize_here(b))
		OUTPUT (
		  automaton_saver(compose(a,b),
				  string_out (),
				  XML ()))
		RETURNVALUE (0));


DEFINE_COMMAND (NAME (u_compose)
		CODE (
		  automaton_t a = get_aut(args.args[1]);
		  automaton_t b = get_aut(args.args[2]);

		  if (!is_sub_normalized(a))
		    sub_normalize_here(a);

		  if (!is_sub_normalized(b))
		    sub_normalize_here(b))
		OUTPUT (
		  automaton_saver(u_compose(a,b),
				  string_out (),
				  XML ()))
		RETURNVALUE (0));

// DEFINE_COMMAND (NAME (eval)
// 		CODE (
// 		  boolean_transducer::automaton_t a =
// 		  boolean_transducer::make_automaton(first_alphabet_t(),
// 						     second_alphabet_t());
// 		  fmp_to_realtime(get_aut(args.args[1]), a))
// 		OUTPUT (
// 		  eval (a, std::string (args.args[2])) << std::endl)
// 		RETURNVALUE (0));

DEFINE_COMMAND (NAME (evaluation)
		CODE (/* empty */)
		OUTPUT (
		  evaluation (get_aut(args.args[1]),
			      boolean_automaton::make_rat_exp(
				get_first_alphabet (args.alphabet),
				args.args[2])) << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (evaluation_fmp)
		CODE (
		  boolean_automaton::automaton_t a = get_boolean_aut(args.args[2]);
		  boolean_automaton::automaton_t res =
		  boolean_automaton::make_automaton(get_second_alphabet(args.alphabet2));
		  evaluation_fmp(get_aut(args.args[1]), a, res))
		OUTPUT (
		  automaton_saver(res, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (domain)
		CODE (
		  boolean_automaton::automaton_t a =
		  boolean_automaton::make_automaton(get_first_alphabet(args.alphabet));
		  domain(get_aut(args.args[1]), a))
		OUTPUT (
		  automaton_saver(a, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (image)
		CODE (
		  boolean_automaton::automaton_t a =
		  boolean_automaton::make_automaton(get_second_alphabet(args.alphabet2));
		  image(get_aut(args.args[1]), a))
		OUTPUT (
		  automaton_saver(a, string_out (), XML ()))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (to_rt)
		CODE (
		  boolean_transducer::automaton_t a =
		  boolean_transducer::make_automaton(first_alphabet_t(),
						     second_alphabet_t());
		  fmp_to_realtime(get_aut(args.args[1]), a))
		OUTPUT (
		  automaton_saver(a, string_out (), XML ()))
		RETURNVALUE (0));


DEFINE_COMMAND (NAME (intersection)
		CODE (
		  boolean_automaton::automaton_t a =
		  get_boolean_aut(args.args[1]);
		  automaton_t fmp = make_automaton(first_alphabet_t(),
						   second_alphabet_t());
		  identity(a, fmp))
		OUTPUT (
		  automaton_saver(fmp, string_out (), XML ()))
		RETURNVALUE (0));


DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (sub_normalize));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (composition_co_cover));

DEFINE_ONE_ARG_COMMAND (ARG_KIND (aut)
			ALGO (composition_cover));


/*-----------------------------.
| Define the set of commands.  |
`-----------------------------*/


const command_t command_map[] =
{
  COMMAND_GROUP (
    "Input/output work with transducers:",

    //COMMAND_ENTRY (define_automaton, File,
    //	   "Define an transducer from scratch."),
    COMMAND_ENTRY (display, Aut, "Display `aut'."),
    COMMAND_ENTRY (dot_dump, Aut, "Dump dot output of `aut'."),
    COMMAND_ENTRY (dump_automaton, File, "Dump a predefined automaton."),
    //COMMAND_ENTRY (edit_automaton, File,
    //	   "Edit an existing transducer."),
    COMMAND_ENTRY (list_automata, Nil, "List predefined automata."),
    COMMAND_ENTRY (identity, Aut, "Return `aut'."),
    COMMAND_ENTRY (info, Aut, "Print useful infos about `aut'.")),


  COMMAND_GROUP (
    "Tests and evaluation on transducers:",

    COMMAND_ENTRY (are_isomorphic, AutAut,
		   "Test if `aut1' and `aut2' are isomorphic."),
    //COMMAND_ENTRY (eval, AutWord, "Compute the evaluation of `word' by `aut'."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Test if `aut' realizes the empty relation."),
    COMMAND_ENTRY (is_sub_normalized, Aut, "Test if `aut' is sub-normalized.")),


  COMMAND_GROUP (
    "Generic algorithm for transducers:",

    COMMAND_ENTRY (eps_removal, Aut, "epsilon-removal algorithm."),
    COMMAND_ENTRY (compose, AutAut,
		   "Compute a the composition of `aut1' and `aut2'."),
    COMMAND_ENTRY (domain, Aut,
		   "Compute an automaton accepting all input accepted by `aut'."),
    COMMAND_ENTRY_CN (eval, evaluation, AutExp,
		      "Compute the evaluation of `exp' against `aut'."),
    COMMAND_ENTRY_CN (eval-aut, evaluation_fmp, AutAut,
		      "Compute a boolean automaton describing the words\n't produced "
		      "by the language described by a evaluated `aut1'."),
    COMMAND_ENTRY (image, Aut,
		   "Compute an automaton describing all output produced by the\n\t"
		   "transducer `aut'."),
    //    COMMAND_ENTRY (transpose, Aut,
    //		   "Compute the transposed of the transducer `aut'."),
    COMMAND_ENTRY (trim, Aut, "Trim transducer `aut'.")),


  COMMAND_GROUP (
    "Algoritms for transducers:",

    COMMAND_ENTRY (sub_normalize, Aut,
		   "Compute the sub-normalized transducer of `aut'."),
    COMMAND_ENTRY (composition_cover, Aut, "Outsplitting."),
    COMMAND_ENTRY (composition_co_cover, Aut, "Insplitting."),
    COMMAND_ENTRY (compose, AutAut,
		   "Compose `aut1' and `aut2', two (sub-)normalized\n\ttransducers."),
    COMMAND_ENTRY (u_compose, AutAut,
		   "Compose `aut1' and `aut2', two boolean transducers,\n\t"
		   "preserve the number of path."),
    COMMAND_ENTRY (to_rt, Aut,
		   "Compute the equivalent realtime transducer of `aut'."),
    COMMAND_ENTRY (intersection, Aut,
		   "Transform a boolean automaton in a fmp transducer by\n\t"
		   "creating, for each word, a pair contianing twice this word.")),
  {0, 0 ,0 ,0, 0}
};
