#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/minimization_moore.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void minimization_debruijn_moore_bench(int n_value)
{
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = new_automaton(alpha);
  debruijn(n_value, an);

  VCSN_BENCH_START;
  minimization_moore(an);
  VCSN_BENCH_STOP_AND_PRINT;
}
