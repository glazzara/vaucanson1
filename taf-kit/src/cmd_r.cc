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
                         SELECT(monoid_elt_value_t)), -1);

  left_mult_of_standard_here(b, w);
  sum_of_standard_here(a, b);

  bool c = is_useless(reduce(a));
  if (args.verbose)
    g_res.stream << (c ? "Automata are equivalent\n" :
		     "Automata are not equivalent\n");
  return !c;
};



BEGIN_COMMAND_GROUP(r_commands,
		    "3. Algorithms for automata with weights in a field:");
COMMAND_ENTRY(reduce, Aut,
	      "Compute a minimal automaton equivalent to `aut'.");
COMMAND_ENTRY(are_equivalent, AutAut,
	      "Tell whether two automata are equivalent.");
END_COMMAND_GROUP
