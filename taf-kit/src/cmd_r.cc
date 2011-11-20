// cmd_r.cc: this file is part of Vaucanson.
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
#include <vaucanson/algorithms/universal.hh>

static int
reduce_command(const arguments_t& args)
{
  g_res.keep(reduce(get_aut(args, 1)));
  return 0;
};

static int
are_equivalent_command(const arguments_t& args)
{
  automaton_t a = realtime(get_aut(args, 1));
  automaton_t b = realtime(get_aut(args, 2));

  standardize(a);
  standardize(b);

  series_set_elt_t w(a.structure().series());
  w.assoc(identity_value(SELECT(monoid_t),
                         SELECT(monoid_elt_value_t)),
	  zero_value(SELECT(semiring_t),
		     SELECT(semiring_elt_value_t)) -
	  identity_value(SELECT(semiring_t),
			 SELECT(semiring_elt_value_t)));

  left_mult_of_standard_here(b, w);
  sum_of_standard_here(a, b);

  bool c = is_useless(reduce(a));
  if (args.verbose)
    g_res.stream << (c ? "Automata are equivalent\n" :
		     "Automata are not equivalent\n");
  return !c;
};

static int
are_equivalent_E_command(const arguments_t& args)
{
  automaton_t a = standard_of(get_exp(args, 1));
  automaton_t b = standard_of(get_exp(args, 2));

  series_set_elt_t w(a.structure().series());
  w.assoc(identity_value(SELECT(monoid_t),
                         SELECT(monoid_elt_value_t)), -1);

  left_mult_of_standard_here(b, w);
  sum_of_standard_here(a, b);

  bool c = is_useless(reduce(a));
  if (args.verbose)
    g_res.stream << (c ? "Expressions are equivalent\n" :
		     "Expressions are not equivalent\n");
  return !c;
};

static int
universal_command(const arguments_t& args)
{
  g_res.keep(universal(get_aut(args, 1)));
  return 0;
}


BEGIN_COMMAND_GROUP(r_commands,
		    "3. Algorithms for automata with weights in a field:");
COMMAND_ENTRY(reduce, Aut, Aut,
	      "Compute a minimal automaton equivalent to `aut'.");
COMMAND_ENTRY(are_equivalent, AutAut, Boolean,
	      "Tell whether two automata realize the same series.");
COMMAND_ENTRY(are_equivalent_E, ExpExp, Boolean,
	      "Tell whether two expressions denote the same language.");
COMMAND_ENTRY(universal, Aut, Aut,
	      "Build the universal automaton of an automaton.")
END_COMMAND_GROUP
