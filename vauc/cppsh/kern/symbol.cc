/*----------------------------------------------------.
| kern/symbol.cc : cppsh kernel / single-storage syms |
`----------------------------------------------------*/
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
#include "kern/symbol.hh"
#include <set>
#ifdef DEBUG
#include "kern/debug.hh"
#include <sstream>
#endif

namespace cppsh
{
  namespace internals
  {
    class static_table
      : public std::set<std::string>
    {
#ifdef DEBUG
    public:
      static_table()
      { 
	std::ostringstream os;
	os << "Static symbol table initialized at: " << this;
	debug::log("symbol", os.str());
      }

      ~static_table()
      {
	std::ostringstream os;
	os << "Static symbol table destroyed at: " << this;
	debug::log("symbol", os.str());
      }
#endif
    };
      

    const std::string* 
    get_unique_string(const std::string& s)
    {
      static static_table table_;

      std::pair<std::set<std::string>::iterator, bool>
	i = table_.insert(s);
#ifdef DEBUG
      {
	std::ostringstream os;
	os << "table@" << &table_ << ": cache " << (i.second ? "miss" : "hit") << " for string@"
	   << &(*i.first) << ": " << *i.first;
	debug::log("symbol", os.str());
      }
#endif
      return &(*i.first);
    }
  }
}
