// product_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef PRODUCT_TEST_HH
# define PRODUCT_TEST_HH

# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/algorithms/complementary.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned product_test(tests::Tester& tg)
{  
  typedef Auto automaton_t;
  gen_auto_t gen(time(0x0));
  tests::Tester t(tg.verbose());

  const unsigned nb_test    = 30;
  unsigned success_identity = 0;
  unsigned success_null     = 0;

  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate(10, 20);
      
      auto_in_complete(a);
      a = determinize(a);  
      automaton_t ac = auto_complementary(a);
      automaton_t squared = auto_product(a,a);

      if ((squared.states().size() == a.states().size()) &&
	  (squared.edges().size() == a.edges().size()))
	success_identity++;
      
      if (trim(auto_product(a, ac)).states().size() == 0)
	success_null++;
    }
  
  std::string rate_identity;
  std::string rate_null;
  SUCCESS_RATE(rate_identity, success_identity, nb_test);
  TEST(t,"Square of a complete deterministic automaton." + rate_identity,
       success_identity == nb_test);
  SUCCESS_RATE(rate_null, success_null, nb_test);
  TEST(t, "Product of complete automaton and its complementary." +
       rate_null,
       success_null == nb_test);
  return t.all_passed();
}

#endif // PRODUCT_TEST_HH
