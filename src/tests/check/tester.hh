// tester.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_TESTS_CHECK_TESTER_HH
# define VCSN_TESTS_CHECK_TESTER_HH

# include <sstream>
# include <iostream>
# include <string>

namespace tests {

  enum verbose_level 
    {
      none,
      low,
      medium, 
      high
    };

  class Tester
  {
  public:
    Tester();
    Tester(verbose_level l);

    bool	     all_passed();
    void	     ok(std::string test_label);
    void	     ko(std::string test_label);
    verbose_level    verbose() const;

    static const unsigned  nb_col_msg;
    // FIXME: Add statistics stuff.

  private:
    unsigned int	passed_;
    unsigned int	failed_;
    verbose_level	verbose_;
  };

} // tests

#define TEST_MSG(Label) \
  std::cout << "TEST: * " << Label << std::endl;

#define TEST_GROUP(Label) \
  std::cout << "GROUP *** " << Label << " ***" << std::endl;

#define TEST_ASSERT(Code, Label) \
  std::cout << ((Code) ? "PASS" : "FAIL") << " * " << Label << std::endl; assert(Code);
#define TEST_XASSERT(Code, Label) \
  std::cout << ((Code) ? "PASS" : "XFAIL") << " * " << Label << std::endl;
  

#define TEST_RETURN(Tester) \
  if (Tester.all_passed())			\
    return EXIT_SUCCESS;			\
  else						\
    return EXIT_FAILURE;


#define TEST(Tester, Label, Code)		\
{						\
  bool result = (Code);				\
  if (result)					\
    Tester.ok(Label);				\
  else						\
   {						\
     std::cout << "(" << #Code << " is false)"	\
               << std::endl;			\
     Tester.ko(Label);				\
   }						\
}

#define EQTEST(Tester, Label, Code, V)		\
{						\
  bool result = ((Code) == (V));		\
  if (result)					\
    Tester.ok(Label);				\
  else						\
   {						\
     std::cout << "(" << #Code << " != " << #V  \
               << ")"				\
               << std::endl;			\
     Tester.ko(Label);				\
   }						\
}

#define SUCCESS_RATE(OutStr, success, over)	\
{						\
  std::ostringstream s;				\
  s << "(" << success << "/" << over << ")";	\
  OutStr = s.str();				\
}

#endif // VCSN_TESTS_CHECK_TESTER_HH
