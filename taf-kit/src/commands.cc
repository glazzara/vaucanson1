// commands.hxx: this file is part of Vaucanson.
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
#include <cassert>
#include <iostream>
#include "common.hh"
#include <sstream>

command_map::map_t&
command_map::map_()
{
  static map_t m_;
  return m_;
}

void
command_map::register_cmd(const char* section,
			  const char* name,
			  int (*command)(const arguments_t&),
			  command_params params,
			  const char* docstring,
			  bool expert)
{
  int n_params;
  switch (params)
    {
    case None:    n_params = 0; break;
    case Exp:     n_params = 1; break;
    case Aut:     n_params = 1; break;
    case AutExp:  n_params = 2; break;
    case AutAut:  n_params = 2; break;
    case AutInt:  n_params = 2; break;
    case AutWord: n_params = 2; break;
    }

  std::string s = name;
  for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    if (*i == '_')
      *i = '-';

  command_t p = { section, command, params, n_params, docstring, expert };
  map_()[s] = p;
}

const command_t*
command_map::lookup(const std::string& str)
{
  map_t& m_ = map_();

  std::string s = str;
  for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    if (*i == '_')
      *i = '-';

  map_t::const_iterator it = m_.find(s);
  if (it == m_.end())
    return 0;
  return &it->second;
}

/// List all the commands.
std::ostream&
command_map::list(std::ostream& ostr, bool expert)
{
  typedef std::map<std::string, std::ostringstream*> secmap_t;
  secmap_t secmap;

  map_t::const_iterator it;
  map_t& m_ = map_();

  for (it = m_.begin(); it != m_.end(); ++it)
    {
      const command_t* command = &it->second;

      if (command->expert && !expert)
	continue;

      std::string sec(command->section);
      secmap_t::const_iterator i = secmap.find(sec);
      std::ostringstream* out;
      if (i == secmap.end())
	secmap[sec] = out = new std::ostringstream;
      else
	out = i->second;

      *out << "   - " << it->first;
      switch (command->params)
	{
	case None: break;
	case Exp: *out << " exp"; break;
	case Aut: *out << " aut"; break;
	case AutExp: *out << " aut exp"; break;
	case AutAut: *out << " aut1 aut2"; break;
	case AutInt: *out << " aut n"; break;
	case AutWord: *out << " aut word"; break;
	}
      *out << ": " << command->docstring << std::endl;
    }

  ostr << "List of available commands:" << std::endl;
  secmap_t::const_iterator si;
  for (si = secmap.begin(); si != secmap.end(); ++si)
    {
      ostr << "  " << si->first << std::endl
	   << si->second->str();
      delete si->second;
    }
}


/**
 * Execute a command according to the program's arguments.
 *
 * @param args Arguments.
 *
 * @return -1 on wrong number of args, -2 on inexistent algo,
 *         the result of the command otherwise.
 */
int
command_map::execute(const arguments_t& args)
{
  const command_t* command = lookup(args.args[0]);

  if (!command)
    {
      warn(args.progname << ": command `"
	   << args.args[0] << "' doesn't exist.");
      return -2;
    }

  if (command->n_params != args.n_args - 1)
    {
      warn(args.progname << ": invalid number of arguments for `"
	   << args.args[0] << "' (should be " << command->n_params << ")");
      warn("Try `" << args.progname << " --list-commands'"
	   << " for more information.");
      return -1;
    }

  return command->command(args);
}
