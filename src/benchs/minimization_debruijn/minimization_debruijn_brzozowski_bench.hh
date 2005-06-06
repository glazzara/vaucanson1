#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <iostream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void minimization_debruijn_brzozowski_bench(int n_value)
{
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = new_automaton(alpha);

  debruijn(n_value, an);
  VCSN_BENCH_START;
  automaton_t dn = determinize(transpose(determinize(transpose(an))));
  VCSN_BENCH_STOP_AND_PRINT;
}
