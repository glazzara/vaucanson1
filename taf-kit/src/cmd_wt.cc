// cmd_wt.cc: this file is part of Vaucanson.
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
#include <vaucanson/algorithms/characteristic.hh>

static int
transpose_command(const arguments_t& args)
{
  g_res.keep(transpose(get_aut(args, 1)));
  return 0;
}

static int
is_unambiguous_command(const arguments_t& args)
{
  bool b = is_ambiguous(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is ambiguous\n" : "Input is unambiguous\n");
  return !!b;
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

#ifdef FMPI_CONTEXT
static int
partial_identity_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  alphabet_t A = a.structure().series().monoid().alphabet();
  FMPI_CONTEXT::monoid_rep_t new_mrep;
  FMPI_CONTEXT::series_rep_t new_srep;
  new_srep.first_representation() =
    *(a.structure().series().representation());
  new_srep.second_representation() =
    *(a.structure().series().representation());
  FMPI_CONTEXT::automaton_t fmp =
    FMPI_CONTEXT::make_automaton(A, A, new_mrep,
		   *(a.structure().series().monoid().representation()),
		   *(a.structure().series().monoid().representation()),
                   new_srep);
  identity(a, fmp);
  g_res.keep(fmp);
  return 0;
}
#endif

static int
eval_command(const arguments_t& args)
{
  automaton_t a = realtime(get_aut (args, 1));
  semiring_elt_t b = eval(a, get_word(a, args.args[2])).value();
  g_res.stream << b << std::endl;
  return 0;
};

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
cat_E_command(const arguments_t& args)
{
  g_res.keep(get_exp(args, 1));
  return 0;
}

static int
expand_command(const arguments_t& args)
{
  g_res.keep(expand(get_exp(args, 1)));
  return 0;
}

static int
exp_to_aut_command(const arguments_t& args)
{
  rat_exp_t e = get_exp(args, 1);
  g_res.keep(standard_of(e));
  return 0;
}

static int
realtime_E_command(const arguments_t& args)
{
  g_res.keep(realtime(get_exp(args, 1)));
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

static int
characteristic_command(const arguments_t& args)
{
  BOOL_CONTEXT::automaton_t a = get_boolean_aut(args, 1);
# ifndef WITH_TWO_ALPHABETS
  automaton_t res =
    make_automaton(a.structure().series().monoid().alphabet());
# else
  automaton_t res =
    make_automaton(a.structure().series().monoid().first_monoid().alphabet());
# endif // !WITH_TWO_ALPHABETS
  characteristic(res, a);
  g_res.keep(res);
  return 0;
}


BEGIN_COMMAND_GROUP(cmd_gen,
      "2. Operations on weighted automata and expressions over free monoids:");
COMMAND_ENTRY(transpose, Aut, "Transpose the automaton `aut'.");
COMMAND_ENTRY(is_unambiguous, Aut,
	      "Return whether `aut' is unambiguous.");
COMMAND_ENTRY(is_realtime, Aut, "Tell whether `aut' is realtime.");
COMMAND_ENTRY(realtime, Aut, "Build a realtime version of `aut'.");
COMMAND_ENTRY(quotient, Aut, "Build the quotient of `aut'.");
#ifdef FMPI_CONTEXT
COMMAND_ENTRY(partial_identity, Aut,
	      "Transform an automaton into an FMP "
	      "transducer by creating, for each word, "
	      "a pair containing twice this word.");
#endif
COMMAND_ENTRY(eval, AutWord, "Evaluate `word' on `aut'.");
// Operations on expressions
COMMAND_ENTRY(standard, Exp, "Build the standard automaton for `exp'.");
COMMAND_ENTRY(thompson, Exp, "Build the Thompson automaton for `exp'.");
COMMAND_ENTRY(cat_E, Exp, "Return `exp' after trivial simplifications.");
COMMAND_ENTRY(expand, Exp, "Distribute product over addition in `exp'.");
COMMAND_ENTRY(exp_to_aut, Exp, "Build the standard automaton for `exp'.");
COMMAND_ENTRY_EXPERT(realtime_E, Exp, "Make `exp' realtime.");
COMMAND_ENTRY(product, AutAut, "Build the product of two automata.");
COMMAND_ENTRY(power, AutInt, "Build the `n'th power of `aut'.");
COMMAND_ENTRY(characteristic, Aut, "Build an automaton from the Boolean automaton `aut'.");
END_COMMAND_GROUP
