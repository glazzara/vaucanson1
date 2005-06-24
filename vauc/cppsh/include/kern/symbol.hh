// symbol.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HH
# define VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HH

#include <string>

namespace cppsh
{
  class Symbol
  {
  public:
    Symbol(const std::string& s);
    Symbol(const char *str);
    Symbol(const Symbol& other);

    Symbol& operator=(const Symbol& other);
    const std::string& value() const;

  protected:
    const std::string* value_;
  };

  inline bool operator==(const Symbol&, const Symbol&);
  inline bool operator!=(const Symbol&, const Symbol&);
  inline bool operator<(const Symbol&, const Symbol&);
  inline bool operator>(const Symbol&, const Symbol&);
  inline bool operator<=(const Symbol&, const Symbol&);
  inline bool operator>=(const Symbol&, const Symbol&);

  inline std::ostream& operator<<(std::ostream&, const Symbol&);

#define VERY_EQUAL_SYMBOLS(S1, S2) \
  (((S1) == (S2)) && ((S1).value() == (S2).value()))


}

#include "kern/symbol.hxx"

#endif // ! VCSN_VAUC_CPPSH_INCLUDE_KERN_SYMBOL_HH
