// parse/location.hh
//
//
#ifndef PARSE_LOCATION_HH
# define PARSE_LOCATION_HH

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

#endif // PARSE_LOCATION_HH
