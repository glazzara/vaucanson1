#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>
#include <common/algorithm.hh>

void minimization_2n_brzozowski_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);
  a = determinize(a);

  VCSN_BENCH_START;
  determinize(transpose(determinize(transpose(a))));
  VCSN_BENCH_STOP_AND_PRINT;
}
