// semiring-numerical-test.cc
//
//
// $Id$
// VCSN_HEADER

// goal : provide a first static tests for numerical semiring families.
// FIXME: it will be use in a tests generator.

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

# include <algebra/semiring/semiring-test.hh>

# include <check/tests_stuff.hh>


int main(int argc, char **argv)
{
  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);
  if (test_semiring<vcsn::algebra::NumericalSemiring, int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
