#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/standard_of.hh>
#include <vaucanson/algebra/implementation/series/krat.hh>
#include <vaucanson/algorithms/aut_to_exp.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void derived_terms_so_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);
  AUTOMATON_FREEMONOID_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);
  krat_t e = aut_to_exp(a);
  VCSN_BENCH_START;
  std::cout << "standard_of (current nb of states: "
	    <<  a.states().size() << "):" << std::endl;
  VCSN_BENCH_START;
  a = standard_of(e);
  VCSN_BENCH_STOP_AND_PRINT;
  std::cout << "determinize (current nb of states: "
	    <<  a.states().size() << "):" << std::endl;
  VCSN_BENCH_START;
  a = determinize(a);
  VCSN_BENCH_STOP_AND_PRINT;
  std::cout << "minimization_hopcroft (current nb of states: "
	    <<  a.states().size() << "):" << std::endl;
  VCSN_BENCH_START;
  a = minimization_hopcroft(a);
  VCSN_BENCH_STOP_AND_PRINT;
  VCSN_BENCH_STOP_AND_PRINT;
}
