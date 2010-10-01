// cmd_fmp.cc: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010 The Vaucanson Group.
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

#include "commands.hh"
#include "common.hh"
#include "getters.hh"


static int
inverse_command(const arguments_t& args)
{
  g_res.keep(invert(get_aut(args, 1)));
  return 0;
}

static int
is_subnormalized_command(const arguments_t& args)
{
  bool b = is_sub_normalized(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is subnormalized\n" :
		     "Input is not subnormalized\n");
  return !b;
}

static int
subnormalize_command(const arguments_t& args)
{
  g_res.keep(sub_normalize(get_aut(args, 1)));
  return 0;
}

static int
is_ltl_command(const arguments_t& args)
{
  bool b = is_ltl(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is letter-to-letter\n" :
		     "Input is not letter-to-letter\n");
  return !b;
}

static int
ltl_to_pair_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  vcsn::mute_ltl_to_pair<automaton_t::set_t,
			 automaton_t::value_t>::ret dst = ltl_to_pair(src);
  g_res.keep(dst);
  return 0;
}


static int
composition_command(const arguments_t& args)
{
  g_res.keep(compose(get_aut(args, 1), get_aut(args, 2)));
  return 0;
}

static int
composition_R_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  automaton_t b = get_aut(args, 2);

  if (!is_sub_normalized(a))
    sub_normalize_here(a);
  if (!is_sub_normalized(b))
    sub_normalize_here(b);

  g_res.keep(compose(a,b));
  return 0;
}

static int
u_composition_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  automaton_t b = get_aut(args, 2);

  if (!is_sub_normalized(a))
    sub_normalize_here(a);
  if (!is_sub_normalized(b))
    sub_normalize_here(b);

  g_res.keep(u_compose(a,b));
  return 0;
}

static int
composition_co_cover_command(const arguments_t& args)
{
  g_res.keep(composition_co_cover(get_aut(args, 1)));
  return 0;
}

static int
composition_cover_command(const arguments_t& args)
{
  g_res.keep(composition_cover(get_aut(args, 1)));
  return 0;
}

static int
pair_to_fmp_command(const arguments_t& args)
{
  vcsn::mute_ltl_to_pair<automaton_t::set_t,
			 automaton_t::value_t>::ret src = get_pair_aut(args, 1);
  automaton_t dst = pair_to_fmp(src);
  set_writing_data(dst, args);
  g_res.keep(dst);
  return 0;
}

static int
evaluation_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  IOAUT_CONTEXT::automaton_t a = get_boolean_aut(args, 2);
  IOAUT_CONTEXT::automaton_t res =
    IOAUT_CONTEXT::make_automaton
    (src.structure().series().monoid().second_monoid().alphabet(),
     *(src.structure().series().monoid().second_monoid().representation()),
     src.structure().series().representation()->second_representation());
  evaluation_fmp(src, a, res);
  g_res.keep(res);
  return 0;
}

static int
eval_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  g_res.stream <<
    evaluation(src,
	       IOAUT_CONTEXT::make_rat_exp
	       (src.structure().
		series().monoid().first_monoid().alphabet(), args.args[2],
		*(src.structure().series().monoid().first_monoid().representation()),
		src.structure().series().representation()->first_representation()))
	       << std::endl;
  return 0;
}


static int
partial_identity_command(const arguments_t& args)
{
  IOAUT_CONTEXT::automaton_t a = get_boolean_aut(args, 1);
  IOAUT_CONTEXT::alphabet_t A =
    a.structure().series().monoid().alphabet();
  series_rep_t new_srep = args.srep;
  new_srep.first_representation() =
    *(a.structure().series().representation());
  new_srep.second_representation() =
    *(a.structure().series().representation());
  automaton_t fmp =
    make_automaton(A, A, args.mrep,
		   *(a.structure().series().monoid().representation()),
		   *(a.structure().series().monoid().representation()),
                   new_srep);
  identity(a, fmp);
  g_res.keep(fmp);
  return 0;
}

BEGIN_COMMAND_GROUP(fmp_commands,
		    "Algorithms for automata on products of free monoïds:");
COMMAND_ENTRY(inverse, Aut, "Give the inverse of `aut'.");
COMMAND_ENTRY(is_subnormalized, Aut, "Tell whether `aut' is sub-normalized.");
COMMAND_ENTRY(subnormalize, Aut,
	      "Build the subnormalized transducer of `aut'.");
COMMAND_ENTRY(is_ltl, Aut, "Test if `aut' is letter-to-letter.");
COMMAND_ENTRY(ltl_to_pair, Aut,
      "Convert `Aut' into an automaton defined over a pair letter alphabet.");
COMMAND_ENTRY(pair_to_fmp, Aut,
	      "Convert an automata `Aut' using pair letters into an FMP."),

COMMAND_ENTRY(composition, AutAut,
	      "Compose two subnormalized transducers."),

COMMAND_ENTRY_EXPERT(composition_cover, Aut, "Outsplitting.");
COMMAND_ENTRY_EXPORT(composition_co_cover, Aut, "Insplitting.");
    COMMAND_ENTRY(u_compose, AutAut,
		  "Compose two transducers, preserving the number of paths.");

COMMAND_ENTRY(eval, evaluation, AutExp,
	      "Give the evaluation of `exp' against `aut'.");
COMMAND_ENTRY(evalutation, evaluation_fmp, AutAut,
	      "Evaluate the language described by the "
	      IOAUT_NAME " automaton `aut2' on the transducer `aut1'."),

COMMAND_ENTRY(composition_R, AutAut,
	      "Compose two transducers."),

#ifdef RW_CONTEXT
    COMMAND_ENTRY(to_rw, Aut,
		  "Give the equivalent rational weight transducer of `aut'.");
#endif
COMMAND_ENTRY(partial_identity, Aut,
	      "Transform a " IOAUT_NAME " automaton into an fmp "
	      "transducer by creating, for each word, "
	      "a pair containing twice this word.");
END_COMMAND_GROUP
