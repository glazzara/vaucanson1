#include <common/bench_automaton.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::bench_automaton;

#include <common/algorithm.hh>
#include <common/bench_constructs.hh>

void minimization_debruijn_hopcroft_bench(int n_value)
{
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = new_automaton(alpha);

  debruijn(n_value, an);

  std::ofstream tmp_o_file("init_o_tmp.fsm");
  fsm_dump(tmp_o_file, an);
  tmp_o_file.close();

  VCSN_BENCH_START;
  automaton_t dn = minimization_hopcroft(an);
  VCSN_BENCH_STOP_AND_PRINT;
}
