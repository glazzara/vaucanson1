// element-full-test.cc
//
// $Id$
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <tests/tests_stuff.hh>

struct A
{
  static void foo() {}
};

int main(int argc, char **argv)
{
  tests::Tester t(1);

  TEST(t, "Method A::foo()", 
  { 
    A::foo(); true; 
  }); 



  if (t.all_passed())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

