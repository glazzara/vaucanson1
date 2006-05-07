// commands.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
#ifndef COMMANDS_HH
# define COMMANDS_HH

/**
 * @file commands.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Command chooser interface.
 */

# include "common.hh"

int execute_command (const arguments_t&);

void list_commands ();


struct command_t
{
    const char*	name;
    int	(*command)(const arguments_t&);
    const char*	params;
    int		n_params;
    const char*	docstring;
};

#endif /* !COMMANDS_HH */
