/*------------------------------------------------------------.
| include/kern/symbol.hh : cppsh kernel / single-storage syms |
`------------------------------------------------------------*/
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
#ifndef CPPSHK_SYMBOL_HH
#define CPPSHK_SYMBOL_HH

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

#endif
