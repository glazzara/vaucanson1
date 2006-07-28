// interface.cc: this file is part of the Vaucanson project.
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


/**
 * @file interface.cc
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Interface for TAF-Kit.
 */

#include "interface.hh"
#include "commands.hh"

  /*----------.
  | Interface |
  `----------*/

inline void write_with_dashs (const char* s)
{
  for (; *s; ++s)
    if (*s == '_')
      echo_ ("-");
    else
      echo_ (*s);
}

/// List all the commands.
void list_commands ()
{
  echo ("List of available commands:");
  for (const command_t* command = command_map; command->docstring; ++command)
    if (command->name)
    {
      echo_ ("   - ");
      write_with_dashs (command->name);
      if (command->n_params)
	echo_ (" " << command->params);
      echo (": " << command->docstring);
    }
    else
      echo (" * " << command->docstring);
}

/// Whether two strings are equal, modulo dashes and underscores.
inline bool equal_without_dashes (const char* s, const char* t)
{
  for (; *s and *t; ++s, ++t)
    if (*s != *t
	and *s != '-' and *s != '_'
	and *t != '-' and *t != '_')
      return false;
  return *s == 0 and *t == 0;
}

/**
 * Execute a command according to the program's arguments.
 *
 * @param args Arguments.
 *
 * @return -1 on wrong number of args, -2 on inexistent algo,
 *         the result of the command otherwise.
 */
int execute_command (const arguments_t& args)
{
  for (const command_t* command = command_map; command->docstring; ++command)
    if (command->name && equal_without_dashes (command->name, args.args[0]))
    {
      if (command->n_params != args.n_args - 1)
      {
	if (command->n_params)
	  warn (args.progname << ": wrong number of arguments for `"
		<< command->name << " " << command->params << "' (should be "
		<< command->n_params << ").");
	else
	  warn (args.progname << ": wrong number of arguments for `"
		<< command->name << "' (should be 0).");
	warn ("Try `" << args.progname << " --list-commands'"
	      << " for more information.");
	return -1;
      }
      return command->command (args);
    }
  warn (args.progname << ": command `" << args.args[0] << "' doesn't exist.");
  return -2;
}
