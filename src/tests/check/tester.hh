// tester.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
//
#ifndef VCSN_TESTS_CHECK_TESTER_HH
# define VCSN_TESTS_CHECK_TESTER_HH

# include <sstream>
# include <fstream>
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


/// To avoid unprintable char printing.
template <typename T>
inline std::string printable(T t)
{
  std::ostringstream	basic_output;
  std::string		basic_output_s;
  std::ostringstream	printable_output;
  unsigned		n;

  basic_output << t;
  basic_output_s = basic_output.str();
  printable_output.setf(std::ios_base::hex, std::ios_base::basefield);
  for (std::string::const_iterator c = basic_output_s.begin();
       c != basic_output_s.end(); ++c)
  {
    n = static_cast<unsigned char>(*c);
    if (n < 0x10)
      printable_output << "0x0" << n;
    else
      if (n >= 0x20 and n < 0x7F)
	printable_output << *c;
      else
	printable_output << "0x" << n;
  }
  return printable_output.str();
}

#define TEST_MSG(Label) \
  std::cout << "TEST: * " << Label << std::endl;

#define TEST_GROUP(Label) \
  std::cout << "GROUP *** " << Label << " ***" << std::endl;

#define TEST_ASSERT(Code, Label) \
  std::cout << ((Code) ? "PASS" : "FAIL") << " * " << Label << std::endl; assert(Code);
#define TEST_XASSERT(Code, Label) \
  std::cout << ((Code) ? "PASS" : "XFAIL") << " * " << Label << std::endl;

#define TEST_FAIL_SAVE(TestName, Iteration, Data)			\
  {									\
    std::ostringstream s;						\
    s << "/tmp/" << TestName << "_" << Iteration << ".txt";		\
    std::ofstream f(s.str().c_str());					\
    f << Data;								\
    f.close();								\
    std::cout << "FAIL: Test failed at iteration "			\
	      << Iteration << std::endl;				\
    std::cout << "FAIL: Relevant information saved in " 		\
	      << s.str() << std::endl;					\
  }

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

#define EQTEST(Tester, Label, Code, V)			\
{							\
  bool result = ((Code) == (V));			\
  if (Tester.verbose() == tests::high)			\
    std::cout << printable(Code) << " =? "		\
	      << printable(V) << std::endl;		\
  if (result)						\
    Tester.ok(printable(Label));			\
  else							\
   {							\
     std::cout << "(" << printable(Code)		\
	       << " != " << printable(V)		\
               << ")" << std::endl;			\
     Tester.ko(Label);					\
   }							\
}

#define SUCCESS_RATE(OutStr, success, over)	\
{						\
  std::ostringstream s;				\
  s << "(" << success << "/" << over << ")";	\
  OutStr = s.str();				\
}

#endif // ! VCSN_TESTS_CHECK_TESTER_HH
