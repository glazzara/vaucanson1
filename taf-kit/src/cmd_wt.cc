// cmd_wt.cc: this file is part of Vaucanson.
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
transpose_command(const arguments_t& args)
{
  g_res.keep(transpose(get_aut(args, 1)));
  return 0;
}

static int
is_realtime_command(const arguments_t& args)
{
  bool b = is_realtime(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is realtime\n" : "Input is not realtime\n");
  return !b;
}


static int
realtime_command(const arguments_t& args)
{
  g_res.keep(realtime(get_aut(args, 1)));
  return 0;
};

static int
quotient_command(const arguments_t& args)
{
  g_res.keep(quotient(realtime(get_aut(args, 1))));
  return 0;
};

static int
eval_command(const arguments_t& args)
{
  automaton_t a = realtime(get_aut (args, 1));
  semiring_elt_t b = eval(a, get_word(a, args.args[2])).value();
  g_res.stream << b << std::endl;
  return 0;
};

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
standard_command(const arguments_t& args)
{
  rat_exp_t e = get_exp(args, 1);
  g_res.keep(standard_of(e));
  return 0;
}

static int
thompson_command(const arguments_t& args)
{
  rat_exp_t e = get_exp(args, 1);
  g_res.keep(thompson_of(e));
  return 0;
}

static int
product_command(const arguments_t& args)
{
  g_res.keep(product(get_aut(args, 1), get_aut(args, 2)));
  return 0;
}

static int
power_command(const arguments_t& args)
{
  int n = atoi(args.args[2]);
  automaton_t a = get_aut(args, 1);
  automaton_t p(a);
  for (int i = 1; i < n; ++i)
    p = product(p, a);
  g_res.keep(p);
  return 0;
}

BEGIN_COMMAND_GROUP(cmd_gen,
	 "Operations on weighted automata and expressions over free monoids:");
COMMAND_ENTRY(transpose, Aut, "Transpose the automaton `aut'.");
COMMAND_ENTRY(is_realtime, Aut, "Tell whether `aut' is realtime.");
COMMAND_ENTRY(realtime, Aut, "Build a realtime version of `aut'.");
COMMAND_ENTRY(quotient, Aut, "Build the quotient of `aut'.");
COMMAND_ENTRY(eval, AutWord, "Evaluate `word' on `aut'.");
COMMAND_ENTRY(shortest, Aut, "Return one of the shortest accepted words.");
COMMAND_ENTRY(enumerate, AutInt, "Enumerate all accepted words of length <=n.");
COMMAND_ENTRY(standard, Exp, "Build the standard automaton for `exp'.");
COMMAND_ENTRY(thompson, Exp, "Build the Thompson automaton for `exp'.");
COMMAND_ENTRY(product, AutAut, "Build the product of two automata.");
COMMAND_ENTRY(power, AutInt, "Build the `n'th power of `aut'.");
END_COMMAND_GROUP
