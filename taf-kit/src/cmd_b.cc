// cmd_b.cc: this file is part of Vaucanson.
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

static int
is_complete_command(const arguments_t& args)
{
  bool b = is_complete(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is complete\n" : "Input is not complete\n");
  return !b;
}

static int
complete_command(const arguments_t& args)
{
  g_res.keep(complete(get_aut(args, 1)));
  return 0;
};

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

static int
derived_term_command(const arguments_t& args)
{
  rat_exp_t e = get_exp(args, 1);
  automaton_t a = make_automaton(get_alphabet(e),
				 *e.structure().monoid().representation(),
				 *e.structure().representation());
  derived_term_automaton(a, e);
  g_res.keep(a);
  return 0;
}

BEGIN_COMMAND_GROUP(b_commands,
	    "Algorithm specific to Boolean automata and rational expressions:");

COMMAND_ENTRY(is_complete, Aut,
	      "Return whether `aut' is complete.");
COMMAND_ENTRY(complete, Aut, "Give the complete version of `aut'.");
COMMAND_ENTRY(is_deterministic, Aut,
	      "Return whether `aut' is deterministic.");
COMMAND_ENTRY(determinize, Aut,
	      "Give the determinized automaton of `aut'.");
COMMAND_ENTRY(complement, Aut, "Complement `aut'.");

COMMAND_ENTRY_CN(minimize, minimization_hopcroft, Aut,
		 "Give the minimized of `aut' (Hopcroft algorithm).");
COMMAND_ENTRY_EXPERT_CN(minimize-moore, minimization_moore, Aut,
			"Give the minimized of `aut' (Moore algorithm).");
COMMAND_ENTRY(are_equivalent, AutAut,
	      "Return whether `aut1' and `aut2' are equivalent.");
COMMAND_ENTRY(derived_term, Exp,
	      "Build the derivate-term automaton for `exp'.");
END_COMMAND_GROUP
