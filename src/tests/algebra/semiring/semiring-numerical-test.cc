// semiring-numerical-test.cc
//
//
// $Id$
// VCSN_HEADER

// goal : provide a first static tests for numerical semiring families.
// FIXME: it will be use in a tests generator.

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <check/tests_stuff.hh>

template <class T>
bool test_numerical_semiring(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  Element<NumericalSemiring, T> e1;
  Element<NumericalSemiring, T> e2;

  return t.all_passed();
}


int main(int argc, char **argv)
{
  tests::Tester t(1);
  if (test_numerical_semiring<int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
