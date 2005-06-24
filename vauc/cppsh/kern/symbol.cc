// symbol.cc: this file is part of the Vaucanson project.
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

