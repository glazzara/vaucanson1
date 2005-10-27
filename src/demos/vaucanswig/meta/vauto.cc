// vauto.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003 The Vaucanson Group.
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
#include "vauto.hh"
// #include <vaucanson/misc/unique.hcc>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

namespace vcsn
{
  void virtual_automaton::string_load(const std::string& in, const std::string& param)
  {
    std::istringstream is(in);
    return this->load(is, param);
  }

  std::string virtual_automaton::string_save(const std::string& param) const
  {
    std::ostringstream os;
    this->save(os, param);
    return os.str();
  }

  void virtual_automaton::dot_run(const char *fname, 
				  const char *cmd, 
				  const char *name) const
  {
    {
      std::ofstream of(fname);
      if (!of)
	throw std::runtime_error("could not open file for writing");
      this->save(of, std::string("dot:") + name);
    }
    system((std::string(cmd) + ' ' + fname).c_str());
  }

  void virtual_automaton::add_states(int nr)
  {
    if (nr < 0)
      throw std::runtime_error("negative number of states requested");
    for (int i = 0; i < nr; ++i)
      this->add_state();
  }

  virtual_automaton::~virtual_automaton() {}
}

