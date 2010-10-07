// cmd_pair.cc: this file is part of Vaucanson.
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
first_projection_command(const arguments_t& args)
{
  automaton_t src = get_aut(args, 1);
  vcsn::CONTEXT::projection_traits_t::first_projection_t a =
    vcsn::CONTEXT::projection_traits_t::first_projection(src);
  first_projection(src, a);
  g_res.keep(a);
  return 0;
}

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

BEGIN_COMMAND_GROUP(pair_commands,
		    "Algorithms for automata with alphabets of pairs:");
COMMAND_ENTRY(first_projection, Aut, "Give the first projection of `aut'.");
COMMAND_ENTRY(second_projection, Aut, "Give the second projection of `aut'.");
END_COMMAND_GROUP
