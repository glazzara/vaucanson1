// semiring-tropical-test.cc
//
//
// $Id$
// VCSN_HEADER

// goal : provide a first static tests for tropical semiring families.
// FIXME: it will be use in a tests generator.

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hh>

# include <algebra/semiring/semiring-test.hh>

# include <check/tests_stuff.hh>

using namespace vcsn::algebra;

int main(int argc, char **argv)
{
  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);
  if (test_semiring<TropicalSemiring<TropicalMax>, int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
