// cmd_b.cc: this file is part of Vaucanson.
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
#include <vaucanson/algorithms/universal.hh>

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
intersection_command(const arguments_t& args)
{
  g_res.keep(product(realtime(get_aut(args, 1)), realtime(get_aut(args, 2))));
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
are_equivalent_E_command(const arguments_t& args)
{
  bool b = are_equivalent(standard_of(get_exp(args, 1)),
			  standard_of(get_exp(args, 2)));
  if (args.verbose)
    g_res.stream << (b ? "Expressions are equivalent\n" :
		     "Expressions are not equivalent\n");
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

static int
shortest_command(const arguments_t& args)
{
  automaton_t a = get_aut (args, 1);
  monoid_elt_t w(a.structure().series().monoid());
  bool b = shortest(a, w);
  if (b)
    g_res.stream << w << std::endl;
  return !b;
}

static int
enumerate_command(const arguments_t& args)
{
  std::list<monoid_elt_t> res;
  enumerate(get_aut (args, 1), get_unsigned(args, 2), res);
  for(std::list<monoid_elt_t>::const_iterator i =
	res.begin(); i != res.end(); ++i)
    g_res.stream << *i << std::endl;
  return 0;
}

static int
prefix_command(const arguments_t& args)
{
  g_res.keep(prefix(get_aut(args, 1)));
  return 0;
}

static int
suffix_command(const arguments_t& args)
{
  g_res.keep(suffix(get_aut(args, 1)));
  return 0;
}

static int
factor_command(const arguments_t& args)
{
  g_res.keep(factor(get_aut(args, 1)));
  return 0;
}

static int
universal_command(const arguments_t& args)
{
  g_res.keep(universal(get_aut(args, 1)));
  return 0;
}


BEGIN_COMMAND_GROUP(b_commands,
	"4. Algorithms specific to Boolean automata and rational expressions:");

COMMAND_ENTRY(is_complete, Aut, Boolean,
	      "Return whether `aut' is complete.");
COMMAND_ENTRY(complete, Aut, Aut, "Give the complete version of `aut'.");
COMMAND_ENTRY(is_deterministic, Aut, Boolean,
	      "Return whether `aut' is deterministic.");
COMMAND_ENTRY(determinize, Aut, Aut,
	      "Give the determinized automaton of `aut'.");
COMMAND_ENTRY(complement, Aut, Aut, "Complement `aut'.");

COMMAND_ENTRY_CN(minimize, minimization_hopcroft, Aut, Aut,
		 "Give the minimized of `aut' (Hopcroft algorithm).");
COMMAND_ENTRY_EXPERT_CN(minimize-moore, minimization_moore, Aut, Aut,
			"Give the minimized of `aut' (Moore algorithm).");
COMMAND_ENTRY(intersection, AutAut, Aut,
	      "Build the intersection of two automata.");
COMMAND_ENTRY(are_equivalent, AutAut, Boolean,
	      "Return whether `aut1' and `aut2' realize the same series.");
COMMAND_ENTRY(are_equivalent_E, ExpExp, Boolean,
	      "Return whether `exp1' and `exp2' denote the same language.");
COMMAND_ENTRY(derived_term, Exp, Aut,
	      "Build the derivate-term automaton for `exp'.");
COMMAND_ENTRY(shortest, Aut, Text,
	      "Return one of the shortest accepted words.");
COMMAND_ENTRY(enumerate, AutInt, Text,
	      "Enumerate all accepted words of length <=n.");
COMMAND_ENTRY(prefix, Aut, Aut,
	      "Build an automaton which accepts any prefix of Aut.");
COMMAND_ENTRY(suffix, Aut, Aut,
	      "Build an automaton which accepts any suffix of Aut.");
COMMAND_ENTRY(factor, Aut, Aut,
	      "Build an automaton which accepts any factor of Aut.");
COMMAND_ENTRY(universal, Aut, Aut,
	      "Build the universal automaton of an automaton.");
END_COMMAND_GROUP
