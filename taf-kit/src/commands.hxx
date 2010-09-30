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

std::map<std::string, command_t> command_map::map_;

void command_map::register_cmd(const char* section,
			       const char* name,
			       int (*command)(const arguments_t&),
			       command_param params,
			       const char* docstring,
			       bool expert = 0)
{
  int n_params;
  switch (params)
    {
    case PNone: n_params = 0; break;
    case PExp: n_params = 1; break;
    case PAut: n_params = 1; break;
    case PAutExp: n_params = 2; break;      
    case PAutAut: n_params = 2; break;
    case PAutInt: n_params = 2; break;
    case PAutWord: n_params = 2; break;      
    }

  command_t p = { section, command, params, n_params, docstring, expert };

  std::string s(name);

  map_[s] = p;
}

static const command_t& lookup(const std::string& str)
{
  map_t::const_iterator it = map_.find(str);
  assert(it != map_.end());
  return it->second;
}

