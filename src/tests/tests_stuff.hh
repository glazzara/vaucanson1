// tests/tests_stuff.hh
//
//
#ifndef TESTS_TESTS_STUFF_HH
# define TESTS_TESTS_STUFF_HH

# include <iostream>
# include <string>

namespace tests {

class Tester
{
public:
  Tester(int verbose_level) : 
    verbose(verbose_level),
    passed(0),
    non_passed(0)
  {}

  bool all_passed() 
  {
    return (non_passed == 0);
  }

  void ok(const std::string& test_label)
  {
    if (verbose == 1)
      std::cerr << "TEST: " << test_label << ": OK" << std::endl;
    passed++;
  }

  void ko(const std::string& test_label)
  {
    if (verbose == 1)
      std::cerr << "TEST: " << test_label << ": KO" << std::endl;
    non_passed++;
  }
  
  // FIXME: Add statistics stuff.

private:
  unsigned int	passed;
  unsigned int  non_passed;
  int		verbose;
};


} // tests

#define TEST(Tester, Label, Code) \
{						\
  bool result = (Code);				\
  if (result) 					\
    Tester.ok(Label);				\
  else						\
    Tester.ko(Label);				\
}


#endif // TESTS_TESTS_STUFF_HH
