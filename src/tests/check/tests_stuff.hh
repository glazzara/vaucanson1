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
    Tester(int verbose_level);

    bool all_passed();
    void ok(std::string test_label);
    void ko(std::string test_label);
  
    // FIXME: Add statistics stuff.

  private:
    unsigned int	passed;
    unsigned int	non_passed;
    int			verbose;
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
