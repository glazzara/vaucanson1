// tests/tests_stuff.hh
//
// $Id$
// VCSN_HEADER
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
  
    // FIXME: Add statistics stuff.

  private:
    unsigned int	passed_;
    unsigned int	non_passed_;
    verbose_level_e	verbose_;
  };

} // tests

#define TEST_MSG(Label) \
  std::cout << "TEST: " << Label << std::endl;

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
