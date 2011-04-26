// cmd_gen.cc: this file is part of Vaucanson.
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
#include <vaucanson/algorithms/is_useless.hh>

//-- Graph functions

static int
accessible_command(const arguments_t& args)
{
  g_res.keep(accessible(get_aut(args, 1)));
  return 0;
}

static int
coaccessible_command(const arguments_t& args)
{
  g_res.keep(coaccessible(get_aut(args, 1)));
  return 0;
}

static int
trim_command(const arguments_t& args)
{
  g_res.keep(trim(get_aut(args, 1)));
  return 0;
}

static int
is_empty_command(const arguments_t& args)
{
  bool b = is_empty(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is empty\n" : "Input is not empty\n");
  return !b;
}

static int
is_useless_command(const arguments_t& args)
{
  bool b = is_useless(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input has no successful computation\n" :
			     "Input has a successful computation\n");
  return !b;
}

//-- Transformations of automata

static int
proper_command(const arguments_t& args)
{
  /* eps_removal() can leave unaccessible states.  This is
     unfortunate, and eventually we want to fix eps_removal() instead
     of calling accessible here. */
  g_res.keep(accessible(eps_removal(get_aut(args, 1))));
  return 0;
}

static int
proper_sp_command(const arguments_t& args)
{
  /* eps_removal() can leave unaccessible states.  This is
     unfortunate, and eventually want to fix eps_removal() instead of
     calling accessible here. */
  g_res.keep(accessible(eps_removal_sp(get_aut(args, 1))));
  return 0;
}

static int
is_proper_command(const arguments_t& args)
{
  bool b = is_proper(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is proper\n": "Input is not proper\n");
  return !b;
}

static int
is_standard_command(const arguments_t& args)
{
  bool b = is_standard(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is standard\n": "Input is not standard\n");
  return !b;
}

static int
standardize_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  standardize(a);
  g_res.keep(a);
  return 0;
}

// Operations on automata

static int
union_command(const arguments_t& args)
{
  g_res.keep(union_(get_aut(args, 1), get_aut(args, 2)));
  return 0;
};

static int
sum_command(const arguments_t& args)
{
  g_res.keep(sum_of_standard(get_aut(args, 1), get_aut(args, 2)));
  return 0;
};

static int
concatenate_command(const arguments_t& args)
{
  g_res.keep(concat_of_standard(get_aut(args, 1), get_aut(args, 2)));
  return 0;
};

static int
star_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  //if (!is_standard(a))
  //standardize(a);
  star_of_standard_here(a);
  g_res.keep(a);
  return 0;
};

static int
left_mult_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);

  series_set_elt_t w(a.structure().series());
  w.assoc(identity_value(SELECT(monoid_t),
			 SELECT(monoid_elt_value_t)), get_weight(args, 2));

  left_mult_of_standard_here(a, w);
  g_res.keep(a);
  return 0;
};

static int
right_mult_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);

  series_set_elt_t w(a.structure().series());
  w.assoc(identity_value(SELECT(monoid_t),
			 SELECT(monoid_elt_value_t)), get_weight(args, 2));

  right_mult_of_standard_here(a, w);
  g_res.keep(a);
  return 0;
};

static int
aut_to_exp_command(const arguments_t& args)
{
  rat_exp_t e = aut_to_exp(get_aut(args, 1), HChooser());
  g_res.keep(e);
  return 0;
}

static int
aut_to_exp_DM_command(const arguments_t& args)
{
  rat_exp_t e = aut_to_exp(get_aut(args, 1), DMChooser());
  g_res.keep(e);
  return 0;
}

static int
aut_to_exp_SO_command(const arguments_t& args)
{
  rat_exp_t e = aut_to_exp(get_aut(args, 1), DefaultChooser());
  g_res.keep(e);
  return 0;
}

static int
sum_S_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  automaton_t b = get_aut(args, 2);
  if (!is_standard(a))
    standardize(a);
  if (!is_standard(b))
    standardize(b);
  sum_of_standard_here(a, b);
  g_res.keep(a);
  return 0;
};

static int
cauchy_S_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  automaton_t b = get_aut(args, 2);
  if (!is_standard(a))
    standardize(a);
  if (!is_standard(b))
    standardize(b);
  concat_of_standard_here(a, b);
  g_res.keep(a);
  return 0;
};

static int
star_S_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  if (!is_standard(a))
    standardize(a);
  star_of_standard_here(a);
  g_res.keep(a);
  return 0;
};



BEGIN_COMMAND_GROUP(cmd_gen,
		    "1. Operations on all automata and rational expressions:");
// Graphs
COMMAND_ENTRY(accessible, Aut, "Compute the accessible part of `aut'.");
COMMAND_ENTRY(coaccessible, Aut, "Compute the co-accessible part of `aut'.");
COMMAND_ENTRY(trim, Aut, "Compute the trim part of `aut'.");
COMMAND_ENTRY(is_empty, Aut, "Tell whether `aut' is empty.'")
COMMAND_ENTRY(is_useless, Aut,
	      "Tell whether `aut' has a successful compitation.");
// Transformations
COMMAND_ENTRY(proper, Aut, "Compute a proper automaton equivalent to "
	      "`aut' by eliminating spontaneous transitions.");
COMMAND_ENTRY(is_proper, Aut,
	      "Return whether `aut' has no spontaneous transitions.");
COMMAND_ENTRY_EXPERT(proper_sp, Aut, "Compute a proper automaton "
		     "equivalent to `aut' using shorter paths.");
COMMAND_ENTRY(is_standard, Aut, "Tell whethwe `aut' is standard");
COMMAND_ENTRY(standardize, Aut, "Give the standard automaton of `aut'.");
// Operations
COMMAND_ENTRY(union, AutAut,
		 "Build the union of two automata.");
COMMAND_ENTRY(sum, AutAut,
	      "Build the sum of two standard automata.");
COMMAND_ENTRY(concatenate, AutAut,
	      "Build the concatenation of two standard automata.");
COMMAND_ENTRY(star, Aut,
	      "Build the star of a standard automaton.");
COMMAND_ENTRY(left_mult, AutWeight,
	      "Build the left-product of `aut' and `weight'.");
COMMAND_ENTRY(right_mult, AutWeight,
	      "Build the right-product of `aut' and `weight'.");
COMMAND_ENTRY(aut_to_exp, Aut,
	      "Build an expression denoting the behaviour of `aut' (Naive heuristic).");
COMMAND_ENTRY(aut_to_exp_SO, Aut,
	      "Build an expression denoting the behaviour of `aut' (State order).");
COMMAND_ENTRY(aut_to_exp_DM, Aut,
	      "Build an expression denoting the behaviour of `aut' (Delgado & Morais heuristic).");
// Operations on behaviors
COMMAND_ENTRY(sum_S, AutAut,
	      "Build a standard sum of two automata.");
COMMAND_ENTRY(cauchy_S, AutAut,
	      "Build a standard Cauchy product of two automata.");
COMMAND_ENTRY(star_S, Aut,
	      "Build a standard star of an automaton.");
END_COMMAND_GROUP
