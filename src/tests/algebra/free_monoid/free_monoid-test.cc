// free_monoid-test.cc
//
// $Id$
// VCSN_HEADER
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

# include <check/tests_stuff.hh>
# include <fundamental/design_pattern-test.hh>

template <typename S, typename T> 
bool test_free_monoid(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t a;
  TEST_MSG("Get the neural element of this free monoid.");
  element_t e = a.set().identity(SELECT(T));
  
  test_design_pattern<S, T>();
  TEST(t, "Neutral element on the right.", (a * e) == a);
  TEST(t, "Neutral element on the left." , (e * a) == a);
  TEST(t, "Mirror is idempotent.", mirror(mirror(a)) == a);

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

  if (test_free_monoid<vcsn::Words, std::string>(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

