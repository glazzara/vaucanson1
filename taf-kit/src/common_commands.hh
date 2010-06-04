// common_commands.hh: this file is part of Vaucanson.
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
#ifndef COMMON_COMMANDS_HH
# define COMMON_COMMANDS_HH

/**
 * @file common_commands.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Commands declaration and definition for all type of automata.
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/dot_display.hh>
# include <vaucanson/algorithms/isomorph.hh>
# include <vaucanson/algorithms/is_empty.hh>
# include <vaucanson/algorithms/is_useless.hh>

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

static int
proper_command(const arguments_t& args)
{
  /* eps_removal() can leave unaccessible states.  This is
     unfortunate, and eventually want to fix eps_removal() instead of
     calling accessible here. */
  g_res.keep(accessible(eps_removal(get_aut(args, 1))));
  return 0;
}

//- proper_sp! aut
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
    g_res.stream << (b ? "Input is proper\n": "Input is not properd\n");
  return !b;
}

static int
transpose_command(const arguments_t& args)
{
  g_res.keep(transpose(get_aut(args, 1)));
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
info_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  g_res.stream << "States: " << a.states().size () << std::endl
	       << "Transitions: " << a.transitions().size () << std::endl
	       << "Initial states: " << a.initial().size () << std::endl
	       << "Final states: " << a.final().size () << std::endl;
  return 0;
}


static int
identity_command(const arguments_t& args)
{
  g_res.keep(get_aut(args, 1));
  return 0;
}

static int
display_command(const arguments_t& args)
{
  bool b = vcsn::tools::dot_display(get_aut(args, 1), "A", true);
  return !b;
}

# define USE_IO_COMMAND_GROUP()						\
  COMMAND_GROUP(							\
    "Input/output work:",						\
									\
    COMMAND_ENTRY(display, Aut, "Display `aut'."),			\
    COMMAND_ENTRY(edit, File, "Edit an automaton."),			\
    COMMAND_ENTRY(identity, Aut, "Return `aut'."),			\
    COMMAND_ENTRY(info, Aut, "Print useful infos about `aut'."),	\
    COMMAND_ENTRY(list_automata, Nil, "List predefined automata.")	\
    )

#endif /* !COMMON_COMMANDS_HH */
