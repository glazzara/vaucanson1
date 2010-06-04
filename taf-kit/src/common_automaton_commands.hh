// common_automaton_commands.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009, 2010 The Vaucanson Group.
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
#ifndef COMMON_AUTOMATON_COMMANDS_HH
# define COMMON_AUTOMATON_COMMANDS_HH

/**
 * @file   common_automaton_commands.hh
 * @author Guillaume Leroi
 * @date   Mon Jul 24 16:57:33 2006
 *
 * @brief Commands declarations and definitions specific for automata.
 *
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/dot_display.hh>
# include <vaucanson/tools/dot_dump.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::tools;
using vcsn::xml::XML;

# include <cstdlib>
# include <iostream>

# include "getters.hh"
# include "edition_commands.hh"
# include "library_commands.hh"
# include "commands.hh"
# include "commands_macros.hh"


  /*---------------------------------------.
  | Command definition (RatExp excluded).  |
  `---------------------------------------*/

// FIXME: should also be available on FMP
static int
accessible_command(const arguments_t& args)
{
  g_res.keep(accessible(get_aut(args, 1)));
  return 0;
};

// FIXME: should also be available on FMP
static int
coaccessible_command(const arguments_t& args)
{
  g_res.keep(coaccessible(get_aut(args, 1)));
  return 0;
};

static int
is_ambiguous_command(const arguments_t& args)
{
  bool b = is_ambiguous(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is ambiguous\n" : "Input is not ambiguous\n");
  return !b;
}

static int
is_complete_command(const arguments_t& args)
{
  bool b = is_complete(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is complete\n" : "Input is not complete\n");
  return !b;
}

static int
is_realtime_command(const arguments_t& args)
{
  bool b = is_realtime(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is realtime\n" : "Input is not realtime\n");
  return !b;
}

// FIXME: should also work for FMP
static int
is_standard_command(const arguments_t& args)
{
  bool b = is_standard(get_aut(args, 1));
  if (args.verbose)
    g_res.stream << (b ? "Input is standard\n" : "Input is not standard\n");
  return !b;
};

static int
complete_command(const arguments_t& args)
{
  g_res.keep(complete(get_aut(args, 1)));
  return 0;
};

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
union_command(const arguments_t& args)
{
  g_res.keep(union_(get_aut(args, 1), get_aut(args, 2)));
  return 0;
};

static int
product_command(const arguments_t& args)
{
  g_res.keep(product(get_aut(args, 1), get_aut(args, 2)));
  return 0;
};

static int
concatenate_command(const arguments_t& args)
{
  g_res.keep(concatenate(get_aut(args, 1), get_aut(args, 2)));
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
standardize_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  standardize(a);
  g_res.keep(a);
  return 0;
}

# ifdef FIRST_PROJECTION_CONTEXT
static int
first_projection_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  vcsn::CONTEXT::projection_traits_t::first_projection_t a =
    vcsn::CONTEXT::projection_traits_t::first_projection(src);
  first_projection(src, a);
  g_res.keep(a);
  return 0;
}
# endif

# ifdef SECOND_PROJECTION_CONTEXT
static int
second_projection_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  vcsn::CONTEXT::projection_traits_t::second_projection_t a =
    vcsn::CONTEXT::projection_traits_t::second_projection(src);
  second_projection(src, a);
  g_res.keep(a);
  return 0;
}

# endif

static int
sum_of_standard_command (const arguments_t& args)
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
concat_of_standard_command (const arguments_t& args)
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
star_of_standard_command (const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  if (!is_standard(a))
    standardize(a);
  star_of_standard_here(a);
  g_res.keep(a);
  return 0;
};

# ifdef FIRST_PROJECTION_CONTEXT
#  define FIRST_PROJECTION_COMMAND_ENTRY \
COMMAND_ENTRY(first_projection, Aut, "Give the first projection of `aut'."),
# else
#  define FIRST_PROJECTION_COMMAND_ENTRY
# endif

# ifdef SECOND_PROJECTION_CONTEXT
#  define SECOND_PROJECTION_COMMAND_ENTRY \
COMMAND_ENTRY(second_projection, Aut, "Give the second projection of `aut'."),
# else
#  define SECOND_PROJECTION_COMMAND_ENTRY
# endif

# define USE_GENERIC_AUTOMATON_COMMAND_GROUP()				\
  COMMAND_GROUP(							\
    "Generic algorithms for automata:",					\
									\
    COMMAND_ENTRY(accessible, Aut,					\
		   "Give the maximal accessible subautomaton of `aut'."), \
    FIRST_PROJECTION_COMMAND_ENTRY					\
    SECOND_PROJECTION_COMMAND_ENTRY					\
    COMMAND_ENTRY(proper, Aut,						\
		  "Close `aut' over epsilon transitions."),		\
    COMMAND_ENTRY_EXPERT(proper_sp, Aut,				\
			 "Close `aut' over epsilon transitions."),	\
    COMMAND_ENTRY(coaccessible, Aut,					\
		  "Give the maximal coaccessible subautomaton of `aut'."), \
    COMMAND_ENTRY(complete, Aut, "Give the complete version of `aut'."), \
    COMMAND_ENTRY(concatenate, AutAut, "Concatenate `aut1' and `aut2'."), \
    /*  COMMAND_ENTRY(normalize, Aut,					\
        "Give the Thompson-normalized automaton of `aut'."), */		\
    COMMAND_ENTRY(power, AutInt, "Give the power of `aut' by `n'."),	\
    COMMAND_ENTRY(product, AutAut, "Give the product of `aut1' by `aut2'." ),	\
    COMMAND_ENTRY(quotient, Aut, "Give the quotient of `aut'."),	\
    COMMAND_ENTRY(realtime, Aut, "Give the realtime version of `aut'."), \
    COMMAND_ENTRY(standardize, Aut, "Give the standard automaton of `aut'."), \
    COMMAND_ENTRY(normalize, Aut, "Give the normalized automaton of `aut'."), \
    COMMAND_ENTRY(sum_of_standard, AutAut,				\
		   "Give the union of standard automata."),		\
    COMMAND_ENTRY(concat_of_standard, AutAut,				\
		   "Give the concatenation of standard automata."),	\
    COMMAND_ENTRY(star_of_standard, Aut,				\
		   "Give the star of automaton `aut'."),	\
    COMMAND_ENTRY(union, AutAut, "Give the union of `aut1' and `aut2'."),	\
    COMMAND_ENTRY(transpose, Aut, "Transpose the automaton `aut'."),	\
    COMMAND_ENTRY(trim, Aut, "Trim the automaton `aut'."),		\
    COMMAND_ENTRY(shortest, Aut, "Return one of the shortest accepted words."), \
    COMMAND_ENTRY(enumerate, AutInt, "Enumerate all accepted words of length <=n.") \
									\
    )									\


#endif // ! COMMON_AUTOMATON_COMMANDS_HH
