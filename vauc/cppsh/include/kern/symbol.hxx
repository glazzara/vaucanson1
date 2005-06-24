// symbol.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HXX
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HXX

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

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HXX
