// semiring-numerical-test.cc
//
//
// $Id$
// VCSN_HEADER

// goal : provide a first static tests for numerical semiring families.
// FIXME: it will be use in a tests generator.

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

# include <fundamental/design_pattern-test.hh>
# include <check/tests_stuff.hh>

template <class T>
bool test_numerical_semiring(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<NumericalSemiring, T> element_t;
  element_t e1;
  element_t z = e1.set().zero(SELECT(T));
  element_t o = e1.set().identity(SELECT(T));
  element_t e2;
  element_t e3(o);

  TEST(t, "commutativity of plus.", (e1 + e2) == (e2 + e1));
  TEST(t, "distributivity of mult with plus.", 
       (e1 + e2) * e3 == e2 * e3 + e1 * e3);
  TEST(t, "0 is a zero for mult.", 
       (e1 * z == z));

  TEST(t, "stareable works. (1)", e1.stareable() ? true  : false);
  TEST(t, "stareable works. (2)", e3.stareable() ? false : true);
  // FIXME: add some other tests.
  return t.all_passed();
}


int main(int argc, char **argv)
{
  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);
  if (test_numerical_semiring<int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
