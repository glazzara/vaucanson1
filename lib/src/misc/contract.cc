// contract.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The
// Vaucanson Group.
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

#include <vaucanson/misc/contract.hh>

#  ifdef EXCEPTION_TRAPS
#   include <sstream>
#   include <stdexcept>
#  else // ! EXCEPTION_TRAPS
#   include <cstdlib>
#  endif // EXCEPTION_TRAP


namespace vcsn {
  namespace misc {
    namespace contract {

      void
      trap (const char *file, int line,
	    const char *location,
	    const std::string& message)
      {
#  ifdef EXCEPTION_TRAPS
	std::ostringstream os;
	os << file << ':' << line << ':'
	   << (location ? location : "")
	   << (location ? ": " : " ")
	   << message;
	throw std::logic_error (os.str ());
#  else // ! EXCEPTION_TRAPS
	std::cerr << file << ':' << line << ':'
		  << (location ? location : "")
		  << std::endl
		  << '\t' << message
		  << std::endl;
	abort ();
#  endif // EXCEPTION_TRAPS
      }
    }
  }
}
