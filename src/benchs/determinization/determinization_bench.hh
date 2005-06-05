#include <common/bench_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <iostream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::bench_automaton;

#include <common/bench_constructs.hh>

void determinization_bench(int n_states)
{
  if (not n_states)
    return;

  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);
  VCSN_BENCH_START;
  automaton_t ret = determinize(a);
  VCSN_BENCH_STOP_AND_PRINT;
}
