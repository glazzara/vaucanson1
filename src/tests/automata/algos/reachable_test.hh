// reachable.hh
//
// VCSN_HEADER

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>


# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>
# include <map>

# include <vaucanson/misc/ref.hh>

# include <vaucanson/tools/gen_random.hh>

# include <vaucanson/algorithms/reachable.hh>

# include <vaucanson/algorithms/moore.hh>
# include <vaucanson/misc/dot_dump.hh>

template <class Auto>
unsigned reachable_test(tests::Tester& t)
{
  using namespace vcsn;
 using namespace vcsn::algebra;
 using namespace vcsn::tools;
  
  typedef Auto automaton_t;
  
  gen_auto_t gen(time(0x0));

  const unsigned nb_tests = 10;
  
  std::filebuf fb;
  fb.open ("automaton.dot", std::ios::out);
  std::ostream os(&fb);

  for (unsigned i = 0; i < nb_tests; i++)
  {
      automaton_t auto_connex;
      auto_connex.create();
      auto_connex = gen.generate(3, 1);
      
      unsigned nb_state = auto_connex.states().size();

      for (unsigned i =0; i < 10; i++)
	auto_connex.add_state();

      //      misc::dot_dump(os, auto_final_reachable(auto_final_reachable(auto_connex)), "test");

      TEST(t, "Check is Reachabled", 
	   nb_state == auto_final_reachable(auto_start_reachable(auto_connex)).states().size());
      TEST(t, "Check is Idem Potent [Final]", 
	   auto_final_reachable(auto_connex).states().size() == 
	   auto_final_reachable(auto_final_reachable(auto_connex)).states().size());
      TEST(t, "Check is Idem Potent [Start]", 
	   auto_start_reachable(auto_connex).states().size() == 
	   auto_start_reachable(auto_start_reachable(auto_connex)).states().size());
  } 
  
  return EXIT_SUCCESS;
}
