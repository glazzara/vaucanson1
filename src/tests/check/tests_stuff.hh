// tests/tests_stuff.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef TESTS_TESTS_STUFF_HH
# define TESTS_TESTS_STUFF_HH

# include <sstream>
# include <iostream>
# include <string>

namespace tests {

  enum verbose_level_e 
    {
      none,
      low,
      medium, 
      high
    };

  class Tester
  {
  public:
    Tester(verbose_level_e verbose_level);

    bool	     all_passed();
    void	     ok(std::string test_label);
    void	     ko(std::string test_label);
    verbose_level_e  verbose() const;

    static const unsigned  nb_col_msg;
    // FIXME: Add statistics stuff.

  private:
    unsigned int	passed_;
    unsigned int	non_passed_;
    verbose_level_e	verbose_;
  };

} // tests

#define TEST_MSG(Label) \
  std::cout << "TEST: * " << Label << std::endl;

#define TEST_RETURN(Tester) \
  if (Tester.all_passed())			\
    return EXIT_SUCCESS;			\
  else						\
    return EXIT_FAILURE;


#define TEST(Tester, Label, Code) \
{						\
  bool result = (Code);				\
  if (result) 					\
    Tester.ok(Label);				\
  else						\
    Tester.ko(Label);				\
}

#define SUCCESS_RATE(OutStr, success, over)	\
{						\
  std::ostringstream s;				\
  s << "(" << success << "/" << over << ")";	\
  OutStr = s.str();				\
}

#endif // TESTS_TESTS_STUFF_HH
