// element-full-test.cc
//
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>


using namespace vcsn;


template <typename S, typename T> 
bool test_alphabet(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  std::set<char> sample; 
  sample.insert('a');
  element_t a(sample);

  test_design_pattern<S, T>();
  TEST(t, "'a' Is contained in Alphabet", a.contains('a'));
  TEST(t, "'b' Is not contained in Alphabet", !a.contains('b'));

  return t.all_passed(); 
}



int main(int argc, char **argv)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

  if (test_alphabet<Alphabets, std::set<char> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

