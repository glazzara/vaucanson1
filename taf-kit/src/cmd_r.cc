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

static int
reduce_command(const arguments_t& args)
{
  g_res.keep(reduce(get_aut(args, 1)));
  return 0;
};

BEGIN_COMMAND_GROUP(r_commands,
		    "3. Algorithms for automata with weights in a field:");
COMMAND_ENTRY(reduce, Aut,
	      "Compute a minimal automaton equivalent to `aut'.");
END_COMMAND_GROUP
