#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>
#include <common/algorithm.hh>

void minimization_2n_hopcroft_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);
  a = determinize(a);

  std::ofstream tmp_o_file("init_o_tmp.fsm");
  fsm_dump(tmp_o_file, a);
  tmp_o_file.close();

  VCSN_BENCH_START;
  minimization_hopcroft(a);
  VCSN_BENCH_STOP_AND_PRINT;
}