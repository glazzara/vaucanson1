// element-full-test.cc
//
// VCSN_HEADER


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

  TEST_MSG("Instanciate an alphabet 'A'.");
  element_t a;
  TEST_MSG("Insert an 'a' in A.");  
  a.insert('a');
  
  test_design_pattern<S, T>();

  TEST(t, "'a' is in A."    , a.contains('a'));
  TEST(t, "'b' is not in A.", !a.contains('b'));
  TEST(t, "A is finite and its cardinal is one.",
       (a.is_finite()) && (a.size() == 1));
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

