// cmd_io.cc: this file is part of Vaucanson.
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
#include "edition_commands.hh"
#include "library_commands.hh"

static int
data_command(const arguments_t& args)
{
  automaton_t a = get_aut(args, 1);
  g_res.stream << "States: " << a.states().size () << std::endl
	       << "Transitions: " << a.transitions().size () << std::endl
	       << "Initial states: " << a.initial().size () << std::endl
	       << "Final states: " << a.final().size () << std::endl;
  return 0;
}


static int
cat_command(const arguments_t& args)
{
  g_res.keep(get_aut(args, 1));
  return 0;
}

static int
cat_E_command(const arguments_t& args)
{
  g_res.keep(get_exp(args, 1));
  return 0;
}

static int
display_command(const arguments_t& args)
{
  return display_aut(get_aut(args, 1), args, 1);
}


BEGIN_COMMAND_GROUP(io_commands,
	    "Input/Output functions:");
COMMAND_ENTRY(data, Aut, "Print useful infos about `aut'.");
COMMAND_ENTRY(cat, Aut, "Return `aut'.");
COMMAND_ENTRY(cat_E, Exp, "Return `exp' after trivial simplifications.");
COMMAND_ENTRY(display, Aut, "Display `aut'.");
COMMAND_ENTRY(edit, Aut, "Create or edit an automaton interactively.");
COMMAND_ENTRY(list_automata, None, "List predefined automata.");
END_COMMAND_GROUP
