// debug.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include "kern/debug.hh"
#include <fstream>
#include <iostream>

namespace cppsh
{
  namespace debug
  {
    static std::string path_;

    void change_dir(const std::string& f)
    { path_ = f; }

    void log(const std::string& domain,
	     const std::string& message)
    {
      std::string fname = path_ + domain + ".log";
      std::ofstream f(fname.c_str(),
		      std::ios::out | std::ios::app);
      if (f.is_open())
	f << message << std::endl;
    }

    void level_log(const std::string& domain,
		   size_t level,
		   const std::string& message)
    {
      std::string fname = path_ + domain + ".log";
      std::ofstream f(fname.c_str(),
		      std::ios::out | std::ios::app);
      if (f.is_open())
	f << "at " << level << ": " << message << std::endl;
    }
  }
}

