/*---------------------------------------------.
| kern/debug.cc : cppsh kernel / debug support |
`---------------------------------------------*/
//     Copyright (C) 2002  LRDE.

//     libcppshk is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.

//     libcppshk is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.

//     You should have received a copy of the GNU Lesser General Public
//     License along with this library; if not, write to the Free Software
//     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
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
