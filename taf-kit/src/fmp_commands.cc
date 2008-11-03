// fmp_commands.cc: this file is part of the Vaucanson project.
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
 * @file   fmp_commands.cc
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
DEFINE_IS_PROPERTY_COMMAND (ltl);

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

// FIXME: this is a workaround against comma in template argument lists
// breaking the CODE macro.
namespace vcsn
{
typedef mute_ltl_to_pair<automaton_t::set_t,
	automaton_t::value_t> mute_ltl_to_pair_t;
}
DEFINE_COMMAND (NAME (ltl_to_pair)
		CODE (
		  automaton_t src = get_aut(args.args[1]);
		  vcsn::mute_ltl_to_pair_t::ret dst = ltl_to_pair(src))
		KEEP_AUTOMATON (dst)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (evaluation)
		CODE (automaton_t src = get_aut(args.args[1]))
		OUTPUT (
		  evaluation (src,
			      IOAUT_CONTEXT::make_rat_exp(src.structure().series().monoid().first_monoid().alphabet(),
				args.args[2], args.srep)) << std::endl)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (evaluation_fmp)
		CODE (
		      automaton_t src = get_aut(args.args[1]);
		  IOAUT_CONTEXT::automaton_t a = get_boolean_aut(args.args[2]);
		  IOAUT_CONTEXT::automaton_t res =
		  IOAUT_CONTEXT::make_automaton(src.structure().series().monoid().second_monoid().alphabet());
		  evaluation_fmp(src, a, res))
		KEEP_AUTOMATON (res)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (domain)
		CODE (
		  automaton_t src = get_aut(args.args[1]);
		  IOAUT_CONTEXT::automaton_t a =
		  IOAUT_CONTEXT::make_automaton(src.structure().series().monoid().first_monoid().alphabet());
		  domain(src, a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));

DEFINE_COMMAND (NAME (image)
		CODE (
		  automaton_t src = get_aut(args.args[1]);
		  IOAUT_CONTEXT::automaton_t a =
		  IOAUT_CONTEXT::make_automaton(src.structure().series().monoid().second_monoid().alphabet());
		  image(src, a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));

#ifdef RW_CONTEXT
DEFINE_COMMAND (NAME (to_rw)
		CODE (
		  automaton_t fmp = get_aut(args.args[1]);
		  automaton_t::monoid_t m = fmp.structure().series().monoid();
		  RW_CONTEXT::automaton_t a =
		  RW_CONTEXT::make_automaton(m.first_monoid().alphabet(),
					     m.second_monoid().alphabet());
		  fmp_to_rw(fmp, a))
		KEEP_AUTOMATON (a)
		RETURNVALUE (0));
#endif

DEFINE_COMMAND (NAME (intersection)
		CODE (
		  IOAUT_CONTEXT::automaton_t a =
		  get_boolean_aut(args.args[1]);
		  IOAUT_CONTEXT::alphabet_t A =
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

    //COMMAND_ENTRY (are_isomorphic, AutAut,
//		   "Test if `aut1' and `aut2' are isomorphic."),
    COMMAND_ENTRY (is_empty, Aut,
		   "Return whether `aut' is empty."),
    COMMAND_ENTRY (has_succ_comp, Aut,
		   "Return whether `aut' has successful computations"
		   " (trimmed `aut` is not empty)."),
    COMMAND_ENTRY (is_sub_normalized, Aut, "Test if `aut' is sub-normalized."),
    COMMAND_ENTRY (is_ltl, Aut, "Test if `aut' is letter-to-letter.")

    ),


  COMMAND_GROUP (
    "Generic algorithm for transducers:",

    COMMAND_ENTRY (eps_removal, Aut, "epsilon-removal algorithm."),
    COMMAND_ENTRY (eps_removal_sp, Aut, "epsilon-removal algorithm."),
    COMMAND_ENTRY (domain, Aut,
		   "Give the automaton that accepts all inputs accepted by `aut'."),
    COMMAND_ENTRY_CN (eval, evaluation, AutExp,
		      "Give the evaluation of `exp' against `aut'."),
    COMMAND_ENTRY_CN (eval-aut, evaluation_fmp, AutAut,
		      "Evaluate the language described by the\n\t"
		      IOAUT_NAME " automaton `aut2' on the transducer `aut1'."),
    COMMAND_ENTRY (ltl_to_pair, Aut,
		   "Give an automaton defined over a pair letter alphabet same as `aut'."),
    COMMAND_ENTRY (image, Aut,
		   "Give an automaton that accepts all output produced by `aut'."),
    COMMAND_ENTRY (transpose, Aut,
    		   "Give the transposed of the transducer `aut'."),
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
		   "Compose `aut1' and `aut2', two transducers,\n\t"
		   "preserve the number of paths."),
#ifdef RW_CONTEXT
    COMMAND_ENTRY (to_rw, Aut,
		   "Give the equivalent rational weight transducer of `aut'."),
#endif
    COMMAND_ENTRY (invert, Aut, "Give the inverse of `aut'."),
    COMMAND_ENTRY (intersection, Aut,
		   "Transform a " IOAUT_NAME " automaton into an fmp "
		   "transducer by\n\tcreating, for each word, "
		   "a pair containing twice this word.")
    ),

  {0, 0 ,0 ,0, 0}
};

LETTER_CONTEXT(automaton_t::monoid_t::first_monoid_t::letter_t)
