// parse/location.cc
//
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


