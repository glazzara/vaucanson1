// location.cc: this file is part of the Vaucanson project.
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
#include "parse/location.hh"

Position 
Location::begin() const
{
  return Position(first_line, first_column);
}

Position 
Location::end() const
{
  return Position(last_line, last_column);
}

void 
Location::line(int lines)
{
  last_line += lines;
}

void 
Location::step()
{
  first_line   = last_line;
  first_column = last_column;
}

namespace std {

  std::ostream&
  operator<<(std::ostream& o, const Position& p)
  {
    o << p.last_line << '.' << p.last_column;
    return o;
  }
  
  
  std::ostream&
  operator<<(std::ostream& o, const Location& l)
  {
    o << (l.begin()) << ':' << (l.end());
    return o;
  }

} // std

