// semiring-tropical-test.cc
//
//
// $Id$
// VCSN_HEADER

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/semiring/tropical_semiring.hh>

# include <algebra/semiring/semiring-test.hh>

# include <check/tests_stuff.hh>

using namespace vcsn::algebra;

int main(int argc, char **argv)
{
  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);
  if (test_semiring<TropicalSemiring<TropicalMax>, int>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
