// cmd_fmp.cc: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010, 2011 The Vaucanson Group.
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

static int
inverse_command(const arguments_t& args)
{
  g_res.keep(invert(get_aut(args, 1)));
  return 0;
}

static int
transpose_command(const arguments_t& args)
{
  g_res.keep(transpose(get_aut(args, 1)));
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
is_normalized_command(const arguments_t& args)
{
  bool b = is_normalized(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is normalized\n" : "Input is not normalized\n");
  return !b;
}

static int
normalize_command(const arguments_t& args)
{
  g_res.keep(normalize(get_aut(args, 1)));
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
domain_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  IOAUT_CONTEXT::automaton_t a =
    IOAUT_CONTEXT::make_automaton
    (src.structure().series().monoid().first_monoid().alphabet(),
     *(src.structure().series().monoid().first_monoid().representation()),
     src.structure().series().representation()->first_representation());
  domain(src, a);
  g_res.keep(a);
  return 0;
}

static int
image_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  IOAUT_CONTEXT::automaton_t a =
    IOAUT_CONTEXT::make_automaton
    (src.structure().series().monoid().second_monoid().alphabet(),
     *(src.structure().series().monoid().second_monoid().representation()),
     src.structure().series().representation()->second_representation());
  image(src, a);
  g_res.keep(a);
  return 0;
}

static int
evaluation_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  IOAUT_CONTEXT::automaton_t a = get_single_band_aut(args, 2);
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


#ifdef RW_CONTEXT
static int
to_rw_command(const arguments_t& args)
{
  automaton_t fmp = get_aut(args, 1);
  automaton_t::monoid_t m = fmp.structure().series().monoid();
  RW_CONTEXT::automaton_t a =
    // FIXME: we should use representations from the fmp
    // automaton.
    RW_CONTEXT::make_automaton(m.first_monoid().alphabet(),
			       m.second_monoid().alphabet());
  fmp_to_rw(fmp, a);
  g_res.keep(a);
  return 0;
}
#endif

BEGIN_COMMAND_GROUP(fmp_commands,
		    "5. Algorithms for automata on products of free monoïds:");
COMMAND_ENTRY(inverse, Aut, "Give the inverse of `aut'.");
COMMAND_ENTRY(transpose, Aut,
	      "Give the transposed of the transducer `aut'.");
COMMAND_ENTRY(is_subnormalized, Aut, "Tell whether `aut' is sub-normalized.");
COMMAND_ENTRY(subnormalize, Aut,
	      "Build a subnormalized transducer of `aut'.");
COMMAND_ENTRY_EXPERT(is_normalized, Aut,
	      "Return whether `aut' is normalized.");
COMMAND_ENTRY_EXPERT(normalize, Aut,
		     "Build a normalized transducer for `aut'.");
COMMAND_ENTRY(is_ltl, Aut, "Test if `aut' is letter-to-letter.");
COMMAND_ENTRY(ltl_to_pair, Aut,
      "Convert `Aut' into an automaton defined over a pair letter alphabet.");
COMMAND_ENTRY(composition, AutAut,
	      "Compose two subnormalized transducers.");
COMMAND_ENTRY_EXPERT(composition_cover, Aut, "Outsplitting.");
COMMAND_ENTRY_EXPERT(composition_co_cover, Aut, "Insplitting.");
    COMMAND_ENTRY(u_composition, AutAut,
		  "Compose two transducers, preserving the number of paths.");

COMMAND_ENTRY(domain, Aut,
	      "Give the automaton that accepts all inputs accepted by `aut'.");
COMMAND_ENTRY(image, Aut,
	      "Give an automaton that accepts all output produced by `aut'.");
COMMAND_ENTRY(composition_R, AutAut,
	      "Compose two transducers.");
COMMAND_ENTRY(evaluation, AutAut,
	      "Evaluate the language described by the "
	      IOAUT_NAME " automaton `aut2' on the transducer `aut1'.");
COMMAND_ENTRY(eval, AutExp,
	      "Give the evaluation of `exp' against `aut'.");

#ifdef RW_CONTEXT
COMMAND_ENTRY_EXPERT(to_rw, Aut,
	      "Give the equivalent rational weight transducer of `aut'.");
#endif
END_COMMAND_GROUP
