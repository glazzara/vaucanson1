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
		KEEP_AUTOMATON (compose(a,b))
		RETURNVALUE (0));


DEFINE_COMMAND (NAME (u_compose)
		CODE (
		  automaton_t a = get_aut(args.args[1]);
		  automaton_t b = get_aut(args.args[2]);

		  if (!is_sub_normalized(a))
		    sub_normalize_here(a);

		  if (!is_sub_normalized(b))
		    sub_normalize_here(b))
		KEEP_AUTOMATON (u_compose(a,b))
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (invert)
		CODE (
		  automaton_t a = get_aut(args.args[1]);
		  automaton_t fmp = invert(a))
		KEEP_AUTOMATON (fmp)
		RETURNVALUE (0));

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
		KEEP_AUTOMATON (res)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (domain)
		CODE (
		  boolean_automaton::automaton_t a =
		  boolean_automaton::make_automaton(get_first_alphabet(args.alphabet));
		  domain(get_aut(args.args[1]), a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (image)
		CODE (
		  boolean_automaton::automaton_t a =
		  boolean_automaton::make_automaton(get_second_alphabet(args.alphabet2));
		  image(get_aut(args.args[1]), a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (to_rt)
		CODE (
		  boolean_transducer::automaton_t a =
		  boolean_transducer::make_automaton(first_alphabet_t(),
						     second_alphabet_t());
		  fmp_to_realtime(get_aut(args.args[1]), a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));


DEFINE_COMMAND (NAME (intersection)
		CODE (
		  boolean_automaton::automaton_t a =
		  get_boolean_aut(args.args[1]);
		  boolean_automaton::alphabet_t A =
		  a.structure().series().monoid().alphabet();
		  automaton_t fmp = make_automaton(A,A);
		  identity(a, fmp))
		KEEP_AUTOMATON (fmp)
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
  USE_IO_COMMAND_GROUP (),

  COMMAND_GROUP (
    "Tests and evaluation on transducers:",

    COMMAND_ENTRY (are_isomorphic, AutAut,
		   "Test if `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Test if `aut' realizes the empty relation."),
    COMMAND_ENTRY (is_sub_normalized, Aut, "Test if `aut' is sub-normalized.")

    ),


  COMMAND_GROUP (
    "Generic algorithm for transducers:",

    COMMAND_ENTRY (eps_removal, Aut, "epsilon-removal algorithm."),
    COMMAND_ENTRY (domain, Aut,
		   "Give the automaton that accepts all inputs accepted by `aut'."),
    COMMAND_ENTRY_CN (eval, evaluation, AutExp,
		      "Give the evaluation of `exp' against `aut'."),
    COMMAND_ENTRY_CN (eval-aut, evaluation_fmp, Aut,
		      "Evaluate the language described by the Boolean automaton\n\t"
		      "`aut2' on the transducer `aut1'."),
    COMMAND_ENTRY (image, Aut,
		   "Give an automaton that accepts all output produced by `aut'."),
    //	  COMMAND_ENTRY (transpose, Aut,
    //		   "Give the transposed of the transducer `aut'."),
    COMMAND_ENTRY (trim, Aut, "Trim transducer `aut'.")

    ),


  COMMAND_GROUP (
    "Algorithms for transducers:",

    COMMAND_ENTRY (sub_normalize, Aut,
		   "Give the sub-normalized transducer of `aut'."),
    COMMAND_ENTRY (composition_cover, Aut, "Outsplitting."),
    COMMAND_ENTRY (composition_co_cover, Aut, "Insplitting."),
    COMMAND_ENTRY (compose, AutAut,
		   "Compose `aut1' and `aut2', two (sub-)normalized\n\ttransducers."),
    COMMAND_ENTRY (u_compose, AutAut,
		   "Compose `aut1' and `aut2', two Boolean transducers,\n\t"
		   "preserve the number of path."),
    COMMAND_ENTRY (to_rt, Aut,
		   "Give the equivalent realtime transducer of `aut'."),
    COMMAND_ENTRY (invert, Aut, "Give the inverse of `aut'."),
    COMMAND_ENTRY (intersection, Aut,
		   "Transform a Boolean automaton in a fmp transducer by\n\t"
		   "creating, for each word, a pair containing twice this word.")
    ),

  {0, 0 ,0 ,0, 0}
};
