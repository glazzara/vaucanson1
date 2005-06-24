// location.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_PARSE_LOCATION_HH
# define VCSN_VAUC_MPP___SRC_PARSE_LOCATION_HH

# include <iostream>

/*---------.
| Position |
`---------*/
struct Position
{
  Position(int l = 0, int c = 0) :
    last_line(l),
    last_column(c)
  {}

  int last_line;
  int last_column;
};


/*---------.
| Location |
`---------*/
class Location
{
public :
  Location(const Position& begin = Position(), 
	   const Position& end = Position()) 
  {}

  Position begin() const;
  Position end() const;
  void line(int lines = 1);
  void step();

public :
//   Position	begin_;
//   Position	end_;
  int last_line;
  int last_column;
  int first_line;
  int first_column;
  char* text;
};

namespace std {
  std::ostream&
  operator<<(std::ostream& o, const Position& p);
  
  std::ostream&
  operator<<(std::ostream& o, const Location& l);

} // std

#endif // ! VCSN_VAUC_MPP___SRC_PARSE_LOCATION_HH
