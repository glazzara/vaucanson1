/*-------------------------------------------------------------.
| include/kern/symbol.hxx : cppsh kernel / single-storage syms |
`-------------------------------------------------------------*/
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
#ifndef CPPSH_SYMBOL_HXX
#define CPPSH_SYMBOL_HXX

#include "kern/symbol.hh"
#include <iostream>

namespace cppsh
{
  namespace internals
  {
    const std::string* 
    get_unique_string(const std::string& s);
  }


  inline Symbol::Symbol(const std::string& s)
    : value_(internals::get_unique_string(s))
  { }

  inline Symbol::Symbol(const char* str)
    : value_(internals::get_unique_string(str))
  { }

  inline Symbol::Symbol(const Symbol& other)
    : value_(other.value_)
  { }

  inline Symbol&
  Symbol::operator=(const Symbol& other)
  { value_ = other.value_; return *this; }
    

  inline const std::string&
  Symbol::value() const
  { return *value_; }

  inline bool 
  operator==(const Symbol& a, const Symbol& b)
  { return &(a.value()) == &(b.value()); }

  inline bool
  operator!=(const Symbol& a, const Symbol& b)
  { return &(a.value()) != &(b.value()); }

  inline bool
  operator<(const Symbol& a, const Symbol& b)
  { return a.value() < b.value(); }

  inline bool
  operator>(const Symbol& a, const Symbol& b)
  { return b < a; }

  inline bool
  operator>=(const Symbol& a, const Symbol& b)
  { return !(a < b); }

  inline bool
  operator<=(const Symbol& a, const Symbol& b)
  { return !(b < a); }

  inline std::ostream&
  operator<<(std::ostream& out, const Symbol& s)
  { return out << s.value(); }

}

#endif
